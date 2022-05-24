/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "numeric_types.h"
#include "scf.h"
#include "sample.h"
#include "molecule.h"
#include "time_util.h"
#include "error_code.h"
#include "dft_matrices.h"
#include "molecular_grid.h"
#include "dft.h"
#include "math_util.h"
#include "cpp_bridge.h"
#include "cmd_line_args.h"
#include "libxc_bridge.h"
#include "diagnostics.h"
#include "mm.h"
#include "molecular_integral.h"
#include "einsum.h"
#include "velocity_init.h"
#include "thermostat.h"
#include "md.h"
#include "energy_gradient.h"

void calculate_density_matrix(struct dft_context *dft_ctx)
{
    struct scf_context *ctx = dft_ctx->scf_ctx;
    struct molecular_grid_desc *mgd = dft_ctx->mgd;
    u64 N = ctx->n_basis_funcs;
    f64 *F = ctx->F;

    for (u64 i = 0; i < N; ++i)
    {
        u64 iN = i * N;
        for (u64 j = 0; j < N; ++j)
        {
            u64 iNj = iN + j;
            F[iNj] = ctx->H[iNj] + mgd->J[iNj] + mgd->XC[iNj];

            if (mgd->hyb_coef > 0.0)
            {
                F[iNj] -= mgd->K[iNj] * mgd->hyb_coef * 0.5;
            }
        }
    }

    diis_update_fock(ctx);

    generalized_eigh_veconly(ctx->diis_F, ctx->S, ctx->C, N);

    u64 nocc = ctx->mol->n_electrons >> 1;
    matslice(ctx->C, ctx->COO, N, N, nocc);

    /*
     * In theory, we should use the conjugate transpose of COO,
     * for the case we are dealing with, COO is a real matrix, we just take its transpose
     * Ref: modern quantum chemistry (Szabo and Ostlund), eq 3.145
     */
    transpose(tag_conjugate(ctx->COO), ctx->COOT, N, nocc);

    /*
     * Calculating density matrix P from C
     * einsum_mn_np__mp(C_occ, C_occ_T) * 2.0
     * Ref: modern quantum chemistry (Szabo and Ostlund), eq 3.145
     */
    if (ctx->damping)
    {
        f64 *P_ = mgd->NxN;
        einsum_mn_np__mp(ctx->COO, ctx->COOT, P_, N, nocc, N);
        mat_scalar_multiply(P_, P_, N, N, 2.0);

        f64 *P = ctx->P;
        for (u64 i = 0; i < N; ++i)
        {
            u64 iN = i * N;
            for (u64 j = 0; j < N; ++j)
            {
                u64 iNj = iN + j;
                P[iNj] = (1.0 - ctx->damping_factor) * P_[iNj] + ctx->damping_factor * P[iNj];
            }
        }
    }
    else
    {
        f64 *P = ctx->P;
        einsum_mn_np__mp(ctx->COO, ctx->COOT, P, N, nocc, N);
        mat_scalar_multiply(P, P, N, N, 2.0);
    }
}

struct dft_context *dft_initialize(struct scf_context *scf_ctx, struct cmd_line_args *args)
{
    struct timespec time_start, time_end;
    get_wall_time(&time_start);

    struct dft_context *ctx = x_malloc(sizeof(struct dft_context));
    struct molecular_grid_desc *mgd = x_malloc(sizeof(struct molecular_grid_desc));
    ctx->mgd = mgd;
    ctx->scf_ctx = scf_ctx;
    scf_ctx->dft_ctx = ctx;
    mgd->radial_grid_level = args->radial_grid_level;
    mgd->lebedev_level = args->lebedev_level;
    mgd->scf_ctx = scf_ctx;

    build_molecular_grid(mgd);
    console_printf(scf_ctx->silent, "Number of basis functions: %lu\n", scf_ctx->n_basis_funcs);
    console_printf(scf_ctx->silent, "Number of grid points: %lu\n", mgd->grid_size);

    calc_bfvalues_derivatives(mgd);
    calc_rho_sigma_lapl_tau(mgd);

    /* initialize functionals */
    i32 func_ids[2] = {args->x_functional_id, args->c_functional_id};
    i32 is_polarized[2] = {0, 0};
    libxc_initialize(func_ids, is_polarized, 2);

    mgd->x_functional_id = args->x_functional_id;
    mgd->c_functional_id = args->c_functional_id;
    mgd->xc_type = get_xc_type(args->x_functional_id, args->c_functional_id);
    console_printf(scf_ctx->silent, "XC: %lu %lu with merged type %lu\n", mgd->x_functional_id, mgd->c_functional_id, mgd->xc_type);

    get_wall_time(&time_end);
    console_printf(scf_ctx->silent, "dft_initialize took %.3f ms\n", diff_time_ms(&time_start, &time_end));

    return ctx;
}

void dft_scf_iterate(struct dft_context *ctx)
{
    struct scf_context *scf_ctx = ctx->scf_ctx;
    struct molecular_grid_desc *mgd = ctx->mgd;
    u64 step = 0;
    ctx->total_energy = 0.0;
    f64 energy_last = 0.0;
    f64 energy_delta = 0.0;
    scf_ctx->converged = 0;
    console_printf(scf_ctx->silent, "\nStarting DFT SCF loop\n");
    struct timespec time_start, time_end;
    for (; step < scf_ctx->n_max_iteration; ++step)
    {
        log_tm_print(scf_ctx->silent, "Step %lu\n", step + 1);

        energy_last = ctx->total_energy;

        calc_rho_sigma_lapl_tau(mgd);

        if (libxc_hyb_coef(mgd->x_functional_id))
        {
            get_wall_time(&time_start);
            build_JK_matrices(mgd);
            get_wall_time(&time_end);
            console_printf(scf_ctx->silent, "build_JK_matrices took %.3f ms\n", diff_time_ms(&time_start, &time_end));
        }
        else
        {
            get_wall_time(&time_start);
            build_J_matrix(mgd);
            get_wall_time(&time_end);
            console_printf(scf_ctx->silent, "build_J_matrix took %.3f ms\n", diff_time_ms(&time_start, &time_end));
        }

        get_wall_time(&time_start);
        build_xc_matrix_with_grid(mgd);
        get_wall_time(&time_end);
        console_printf(scf_ctx->silent, "build_xc_matrix_with_grid took %.3f ms\n", diff_time_ms(&time_start, &time_end));

        get_wall_time(&time_start);
        dft_total_energy(ctx);
        get_wall_time(&time_end);
        console_printf(scf_ctx->silent, "dft_total_energy took %.3f ms\n", diff_time_ms(&time_start, &time_end));

        get_wall_time(&time_start);
        calculate_density_matrix(ctx);
        get_wall_time(&time_end);
        console_printf(scf_ctx->silent, "calculate_density_matrix took %.3f ms\n", diff_time_ms(&time_start, &time_end));

        energy_delta = fabs(ctx->total_energy - energy_last);
        if (energy_delta < scf_ctx->converge_threshold)
        {
            scf_ctx->converged = 1;
            break;
        }
    }
    printf("SCF took %lu steps to converge\n", step);
}

void dft_total_energy(struct dft_context *ctx)
{
    struct scf_context *scf_ctx = ctx->scf_ctx;
    struct molecular_grid_desc *mgd = ctx->mgd;
    u64 N = scf_ctx->n_basis_funcs;

    f64 single_electron_energy = einsum_mn_nm(scf_ctx->P, scf_ctx->H, N, N);
    f64 electronic_repulsion_energy = einsum_mn_nm(scf_ctx->P, mgd->J, N, N) * 0.5;

    ctx->total_energy = single_electron_energy + electronic_repulsion_energy + scf_ctx->nuclear_repulsion_energy + mgd->xc_energy;
    log_tm_print(scf_ctx->silent, "total energy: %.16e = %.16e (core) + %.16e (J) + %.16e (K) + %.16e (XC) + %.16e (NRE)\n\n",
                 ctx->total_energy,
                 single_electron_energy,
                 electronic_repulsion_energy,
                 mgd->hf_exchange_energy,
                 mgd->xc_energy,
                 scf_ctx->nuclear_repulsion_energy);
}

void dft_finalize(struct dft_context *ctx)
{
    struct molecular_grid_desc *mgd = ctx->mgd;

    x_free(mgd->global_coords);
    x_free(mgd->local_coords);
    x_free(mgd->weights);
    x_free(mgd->becke_weights);
    x_free(mgd->bf_values);
    x_free(mgd->bf_derivative_x);
    x_free(mgd->bf_derivative_y);
    x_free(mgd->bf_derivative_z);
    x_free(mgd->bf_laplacian);
    x_free(mgd->V);
    x_free(mgd->V_fuzzy_cell);

    x_free(mgd->lebedev_grid);
    x_free(mgd->lebedev_weights);

    x_free(mgd->atomic_grid_descs);

    x_free(mgd->J);
    x_free(mgd->K);
    x_free(mgd->XC);
    x_free(mgd->VXC_x);
    x_free(mgd->VXC_y);
    x_free(mgd->VXC_z);

    x_free(mgd->densities);
    x_free(mgd->density_derivative_x);
    x_free(mgd->density_derivative_y);
    x_free(mgd->density_derivative_z);
    x_free(mgd->densities_sigma);
    x_free(mgd->lapl);
    x_free(mgd->tau);
    x_free(mgd->exc_x);
    x_free(mgd->vrho_x);
    x_free(mgd->exc_c);
    x_free(mgd->vrho_c);
    x_free(mgd->vsigma_x);
    x_free(mgd->vlapl_x);
    x_free(mgd->vtau_x);
    x_free(mgd->vsigma_c);
    x_free(mgd->vlapl_c);
    x_free(mgd->vtau_c);

    x_free(mgd->bf_derivative_xx);
    x_free(mgd->bf_derivative_yy);
    x_free(mgd->bf_derivative_zz);
    x_free(mgd->bf_derivative_xy);
    x_free(mgd->bf_derivative_xz);
    x_free(mgd->bf_derivative_yz);

    x_free(mgd->d_sigma_x);
    x_free(mgd->d_sigma_y);
    x_free(mgd->d_sigma_z);

    x_free(mgd->d_lapl_x);
    x_free(mgd->d_lapl_y);
    x_free(mgd->d_lapl_z);

    x_free(mgd->d_tau_x);
    x_free(mgd->d_tau_y);
    x_free(mgd->d_tau_z);

    x_free(mgd->bf_v);
    x_free(mgd->weighted_vrho);

    x_free(mgd->weighted_vsigma_rho_dx);
    x_free(mgd->weighted_vsigma_rho_dy);
    x_free(mgd->weighted_vsigma_rho_dz);
    x_free(mgd->bf_v_dx);
    x_free(mgd->bf_v_dy);
    x_free(mgd->bf_v_dz);

    x_free(mgd->NxN);
    x_free(mgd->MxN);
    x_free(mgd->Mx1);
    x_free(mgd->MxN_2);

    x_free(mgd);

    x_free(ctx);

    libxc_finalize();
}

void scf_config_dft(struct scf_context *ctx)
{
    ctx->JK_screening_threshold = 1e-8;
    ctx->converge_threshold = 1e-12;
    ctx->n_max_iteration = 1000;
    ctx->direct_scf = 1;
    ctx->density_init_method = DENSITY_INIT_HCORE;
}

void single_point_energy(struct cmd_line_args *args)
{
    struct scf_context *scf_ctx = scf_initialize(args, scf_config_dft);
    struct dft_context *dft_ctx = dft_initialize(scf_ctx, args);

    dft_scf_iterate(dft_ctx);
    if (args->check_results)
    {
        check_total_energy(dft_ctx->total_energy, args->check_results);
    }

    dft_finalize(dft_ctx);
    scf_finalize(scf_ctx);
}

void single_point_forces(struct cmd_line_args *args)
{
    struct scf_context *scf_ctx = scf_initialize(args, scf_config_dft);
    struct dft_context *dft_ctx = dft_initialize(scf_ctx, args);

    dft_scf_iterate(dft_ctx);
    energy_dwrt_nuc(scf_ctx);
    if (args->check_results)
    {
        check_total_energy(dft_ctx->total_energy, args->check_results);
        check_forces((f64 *)(scf_ctx->mol->forces), args->check_results);
    }

    dft_finalize(dft_ctx);
    scf_finalize(scf_ctx);
}

void calc_forces_on_nuclei(struct cmd_line_args *args, struct md_context *md_ctx)
{
    struct scf_context *scf_ctx = NULL;
    if (md_ctx->step > 0)
    {
        scf_ctx = scf_initialize(args, scf_config_md);
        memcpy(scf_ctx->P, md_ctx->density_matrix, scf_ctx->N2_f64);
    }
    else
    {
        scf_ctx = scf_initialize(args, scf_config_dft);
    }

    struct dft_context *dft_ctx = dft_initialize(scf_ctx, args);
    dft_scf_iterate(dft_ctx);
    energy_dwrt_nuc(scf_ctx);
    dft_finalize(dft_ctx);

    memcpy(md_ctx->density_matrix, scf_ctx->P, scf_ctx->N2_f64);
    scf_finalize(scf_ctx);
}

int main(int argc, char *argv[])
{
    struct timespec time_start, time_end;
    get_wall_time(&time_start);

    struct cmd_line_args args;
    parse_cmd_line_args(argc, argv, &args);

    if (!args.silent)
    {
        print_molecule(args.mol);
    }

    if (args.job_type == JOB_TYPE_SPE)
    {
        single_point_energy(&args);
    }
    if (args.job_type == JOB_TYPE_SPF)
    {
        single_point_forces(&args);
    }
    if (args.job_type == JOB_TYPE_BOMD)
    {
        struct scf_context *ctx = scf_initialize(&args, scf_config_dft);
        u64 n_basis_funcs = ctx->n_basis_funcs;
        scf_finalize(ctx);

        struct md_context *md_ctx = md_initialize(&args, calc_forces_on_nuclei, n_basis_funcs, "dft");
        md_simulate(&args, md_ctx);
        md_finalize(md_ctx);
    }

    free_molecule(args.mol);

    get_wall_time(&time_end);
    console_printf(0, "The whole program took %.3f ms\n", diff_time_ms(&time_start, &time_end));

    if (!args.silent)
    {
        print_mm_status();
    }

    return 0;
}
