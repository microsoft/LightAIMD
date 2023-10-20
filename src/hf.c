/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "constants.h"
#include "numeric_types.h"
#include "scf.h"
#include "sample.h"
#include "molecule.h"
#include "matrix.h"
#include "time_util.h"
#include "error_code.h"
#include "thread_pool.h"
#include "molecular_integral.h"
#include "spinlock.h"
#include "lapacke_bridge.h"
#include "cmd_line_args.h"
#include "mm.h"
#include "diagnostics.h"
#include "einsum.h"
#include "velocity_init.h"
#include "thermostat.h"
#include "md.h"
#include "energy_gradient.h"
#include "cuda_helper.h"

/* F = h + J - 0.5K */
static void hf_build_fock_with_precomputed_eri(struct scf_context* ctx)
{
    u64 N = ctx->n_basis_funcs;
    u64 N2 = N * N;
    u64 N3 = N2 * N;

    f64* A = ctx->TwoE;
    f64* P = ctx->P;
    f64* F = ctx->F;
    f64* H = ctx->H;

    for (u64 p = 0; p < N; ++p)
    {
        u64 pN = p * N;

        /*
         * We use q <= p for symmetric Fock matrix,
         * for the general case, we need to use q < N.
         */
        for (u64 q = 0; q <= p; ++q)
        {
            u64 qN = q * N;
            u64 pN3_qN2 = p * N3 + q * N2;
            u64 pN3_qN = p * N3 + qN;
            u64 pNq = pN + q;
            f64 c = 0.0;
            f64 d = 0.0;
            for (u64 r = 0; r < N; ++r)
            {
                u64 rN = r * N;
                u64 rN2 = r * N2;
                for (u64 s = 0; s < N; ++s)
                {
                    // u64 sNr = s * N + r;
                    u64 rNs = rN + s;
                    c += A[pN3_qN2 + rN + s] * P[rNs]; /* Coulombic, assuming P is symmetric */

                    /*
                     * Ref: modern quantum chemistry, eq 3.154
                     * The following is equavilent to
                     * d += A[pN3_qN + s * N2 + r] * P[rNs];
                     */
                    d += A[pN3_qN + rN2 + s] * P[rNs]; /* Exchange, assuming P is symmetric */
                }
            }
            F[pNq] = c - 0.5 * d + H[pNq];
            F[qN + p] = F[pNq]; /* for symmetric Fock matrix */
        }
    }
}

struct task_func_eri_arg
{
    struct scf_context* ctx;
    f64* F;
    f64* P;
    u64 i;
    u64 j;
    u64 k;
    u64 l;
    u64 i_j;
    u64 k_l;
    u64 ij_kl;
};

static void task_func_eri(void* p_arg)
{
    struct task_func_eri_arg* arg = (struct task_func_eri_arg*)p_arg;
    struct scf_context* ctx = arg->ctx;
    volatile atomic_bool* L = ctx->LOCK;
    f64* F = arg->F;
    f64* P = arg->P;
    u64 i = arg->i;
    u64 j = arg->j;
    u64 k = arg->k;
    u64 l = arg->l;
    u64 i_j = arg->i_j;
    u64 k_l = arg->k_l;
    u64 ij_kl = arg->ij_kl;
    u64 N = ctx->n_basis_funcs;
    u64 iN = i * N;
    u64 iNj = iN + j;
    u64 iNk = iN + k;
    u64 jN = j * N;
    u64 jNk = jN + k;
    u64 kN = k * N;
    u64 kNj = kN + j;

    f64 val = cg_electron_repulsion_integral(ctx->basis_funcs + i, ctx->basis_funcs + j,
              ctx->basis_funcs + k, ctx->basis_funcs + l) *
              i_j * k_l * ij_kl;

    /* Coulomb */
    spinlock_lock(L + iNj);
    F[iNj] += val * P[kN + l];
    spinlock_unlock(L + iNj);
    spinlock_lock(L + kN + l);
    F[kN + l] += val * P[iNj];
    spinlock_unlock(L + kN + l);

    /* Exchange */
    spinlock_lock(L + iNk);
    F[iNk] -= val * P[jN + l] * 0.25;
    spinlock_unlock(L + iNk);
    spinlock_lock(L + jN + l);
    F[jN + l] -= val * P[iNk] * 0.25;
    spinlock_unlock(L + jN + l);
    spinlock_lock(L + iN + l);
    F[iN + l] -= val * P[jNk] * 0.25;
    spinlock_unlock(L + iN + l);
    spinlock_lock(L + kNj);
    F[kNj] -= val * P[iN + l] * 0.25;
    spinlock_unlock(L + kNj);
    x_free(p_arg);
}

/* F = h + (G + G.T) * 0.25 */
static void hf_build_fock_direct(struct scf_context* ctx)
{
    /*log_tm_println("starting building fock ...");*/
    f64* P = ctx->P;
    f64* F = ctx->F;
    f64* H = ctx->H;

    u64 N = ctx->n_basis_funcs;
    memset(F, 0, N * N * sizeof(f64));

    for (u64 i = 0; i < N; ++i)
    {
        u64 iN = i * N;

        for (u64 j = 0; j <= i; ++j)
        {
            u64 jN = j * N;

            /* ij gives a total order for iterating i and j (i<N and j<=i) */
            u64 ij = ((i * (i + 1)) >> 1) + j;
            f64 i_j = 2.0;
            if (i == j)
            {
                i_j = 1.0;
            }

            for (u64 k = 0; k < N; ++k)
            {
                u64 kN = k * N;

                for (u64 l = 0; l <= k; ++l)
                {
                    /* kl gives a total order for iterating k and l (k<N and l<=k) */
                    u64 kl = ((k * (k + 1)) >> 1) + l;
                    f64 k_l = 2.0;
                    if (k == l)
                    {
                        k_l = 1.0;
                    }
                    f64 ij_kl = 2.0;
                    if (i == k && j == l)
                    {
                        ij_kl = 1.0;
                    }

                    if (ij >= kl)
                    {
                        f64 bound = sqrt(ctx->ScreeningMatrix[ij]) * sqrt(ctx->ScreeningMatrix[kl]);

                        f64 pmax = 0.0;
                        f64 ps[] = {fabs(2.0 * P[i * N + j]), fabs(2.0 * P[k * N + l]), fabs(0.5 * P[i * N + k]), fabs(0.5 * P[i * N + l]), fabs(0.5 * P[j * N + k]), fabs(0.5 * P[j * N + l])};

                        for (u64 t = 0; t < 6; ++t)
                        {
                            if (ps[t] > pmax)
                            {
                                pmax = ps[t];
                            }
                        }

                        if ((bound * pmax) < ctx->JK_screening_threshold)
                        {
                            continue;
                        }

                        struct task_func_eri_arg* arg = x_malloc(sizeof(struct task_func_eri_arg));
                        arg->ctx = ctx;
                        arg->F = F;
                        arg->P = P;
                        arg->i = i;
                        arg->j = j;
                        arg->k = k;
                        arg->l = l;
                        arg->i_j = i_j;
                        arg->k_l = k_l;
                        arg->ij_kl = ij_kl;
                        threadpool_add_task(ctx->tp_ctx, (iN * N * N + jN * N + kN + l) % (ctx->tp_ctx->n_workers), task_func_eri, arg);
                    }
                }
            }
        }
    }

    threadpool_wait_job_done(ctx->tp_ctx);

    f64* M = ctx->NxN_1;
    transpose(F, M, N, N);
    mat_add(F, M, M, N, N);
    mat_scalar_multiply(M, F, N, N, 0.25);
    mat_add(H, F, F, N, N);
    /*log_tm_println("fock has been built.");*/
}

static void hf_build_fock(struct scf_context* ctx)
{
    u64 N = ctx->n_basis_funcs;
    u64 N2 = N * N;
    memcpy(ctx->F, ctx->H, N2 * sizeof(f64));

    if (ctx->direct_scf)
    {
        hf_build_fock_direct(ctx);
    }
    else
    {
        hf_build_fock_with_precomputed_eri(ctx);
    }
}

static void hf_initialize(struct scf_context* ctx)
{
    hf_build_fock(ctx);
    memcpy(ctx->diis_F, ctx->F, ctx->N2_f64);
}

void hf_scf_config(struct scf_context* ctx)
{
    ctx->JK_screening_threshold = 1e-8;
    ctx->converge_threshold = 1e-12;
    ctx->n_max_iteration = 100;
    ctx->direct_scf = 1;
    ctx->density_init_method = DENSITY_INIT_SOAD;
}

static void hf_total_energy(struct scf_context* ctx)
{
    /*
     * E = 0.5 * P_vu * (H_uv + F_uv) + NRE
     * In theory, we should use the transpose of the matrix P (P.T)
     * However, as P is symmetric here, we can just use P instead
     * Ref: modern quantum chemistry (Szabo and Ostlund), eq 3.184
     * Ref: quantum chemistry (7ed), eq 14.45
     */
    u64 N = ctx->n_basis_funcs;
    mat_add(ctx->H, ctx->F, ctx->NxN_1, N, N);
    // mat_multiply(tag_transpose(ctx->P), ctx->F, ctx->M, N, N);

    ctx->energy = 0.5 * einsum_mn_nm(ctx->P, ctx->NxN_1, N, N) + ctx->nuclear_repulsion_energy;
}

static void hf_scf_iterate(struct scf_context* ctx)
{
    console_printf(ctx->silent, "\nStarting HF SCF loop\n");
    u64 N = ctx->n_basis_funcs;
    u64 N2 = N * N;

    struct timespec time_start, time_end;
    get_wall_time(&time_start);

    u64 step = 0;
    for (; step < ctx->n_max_iteration; ++step)
    {
        if (step != 0)
        {
            ctx->energy_last = ctx->energy;
            if (ctx->direct_scf)
            {
                // log_dbg_print(ctx->silent, "Build Fock (direct), step %lu, start\n", step);
                hf_build_fock_direct(ctx);
                // log_dbg_print(ctx->silent, "Build Fock (direct), step %lu, end\n", step);
            }
            else
            {
                // log_dbg_print(ctx->silent, "Build Fock with precomputed ERI, step %lu, start\n", step);
                hf_build_fock_with_precomputed_eri(ctx);
                // log_dbg_print(ctx->silent, "Build Fock with precomputed ERI, step %lu, end\n", step);
            }
            // log_dbg_print(ctx->silent, "DIIS update fock, step %lu, start\n", step);
            diis_update_fock(ctx);
            // log_dbg_print(ctx->silent, "DIIS update fock, step %lu, end\n", step);
        }

        /* Solving FC = eSC */
        // log_dbg_print(ctx->silent, "Solving FC = eSC, step %lu, start\n", step);
        // generalized_eigh_veconly(ctx->diis_F, ctx->S, ctx->C, N);
        solve_generalized_eigenvalue_symmetric(ctx->diis_F, ctx->S, ctx->C, N);
        // log_dbg_print(ctx->silent, "Solving FC = eSC, step %lu, end\n", step);

        u64 nocc = ctx->mol->n_electrons >> 1;
        matslice(ctx->C, ctx->COO, N, N, nocc);

        /*
          In theory, we should use the conjugate transpose of COO,
          for RHF here, COO is a real matrix, we just take its transpose
          Ref: modern quantum chemistry (Szabo and Ostlund), eq 3.145
        */
        transpose(tag_conjugate(ctx->COO), ctx->COOT, N, nocc);

        /*
         * Calculating density matrix P from C
         * einsum_mn_np__mp(C_occ, C_occ_T) * 2.0
         * Ref: modern quantum chemistry (Szabo and Ostlund), eq 3.145
         */
        einsum_mn_np__mp(ctx->COO, ctx->COOT, ctx->P, N, nocc, N);
        mat_scalar_multiply(ctx->P, ctx->P, N, N, 2.0);

        hf_total_energy(ctx);

        if (step != 0)
        {
            /* Damping */
            if (ctx->damping)
            {
                mat_scalar_multiply(ctx->P_last, ctx->NxN_1, N, N, ctx->damping_factor);
                mat_scalar_multiply(ctx->P, ctx->NxN_2, N, N, 1.0 - ctx->damping_factor);
                mat_add(ctx->NxN_1, ctx->NxN_2, ctx->P, N, N);
            }

            ctx->delta_energy = fabs(ctx->energy - ctx->energy_last);
            mat_scalar_multiply(ctx->P_last, ctx->P_last, N, N, -1.0);
            mat_add(ctx->P, ctx->P_last, ctx->P_last, N, N);
            ctx->density_rmsd = matnorm(ctx->P_last, N, N);
        }

        log_tm_print(ctx->silent, "Step %2lu: energy:%20.13e, energy_diff:%19.12e, rmsd:%19.12e\n", step, ctx->energy, ctx->delta_energy, ctx->density_rmsd);
        if (ctx->density_rmsd < ctx->converge_threshold && ctx->delta_energy < ctx->converge_threshold)
        {
            console_printf(ctx->silent, "Converged.\n");
            break;
        }

        memcpy(ctx->P_last, ctx->P, N2 * sizeof(f64));
    }

    printf("SCF took %lu steps to converge\n", step);

    get_wall_time(&time_end);
    f64 scf_time = diff_time_ms(&time_start, &time_end);
    console_printf(ctx->silent, "SCF took %.3f ms (%.3f ms/step)\n", scf_time, scf_time / (step + 1));
}

void hf_single_point_energy(struct cmd_line_args* args)
{
    log_dbg_print(args->silent, "HF single point energy calculation\n");
    struct scf_context* ctx = scf_initialize(args, hf_scf_config);
    hf_initialize(ctx);
    hf_scf_iterate(ctx);
    if (args->check_results)
    {
        check_total_energy(ctx->energy, args->check_results);
    }
    scf_finalize(ctx);
}

void hf_single_point_forces(struct cmd_line_args* args)
{
    struct scf_context* ctx = scf_initialize(args, hf_scf_config);
    hf_initialize(ctx);
    hf_scf_iterate(ctx);
    energy_dwrt_nuc(ctx);
    if (args->check_results)
    {
        check_total_energy(ctx->energy, args->check_results);
        check_forces((f64*)(ctx->mol->forces), args->check_results);
    }
    scf_finalize(ctx);
}

void hf_calc_forces_on_nuclei(struct cmd_line_args* args, struct md_context* md_ctx)
{
    struct scf_context* ctx = scf_initialize(args, hf_scf_config);

    hf_initialize(ctx);
    hf_scf_iterate(ctx);
    energy_dwrt_nuc(ctx);

    scf_finalize(ctx);
}

#ifdef MODULE_TEST
int main(int argc, char* argv[])
{
#ifdef USE_CUDA
    cuda_configure();
#endif

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
        hf_single_point_energy(&args);
    }
    if (args.job_type == JOB_TYPE_SPF)
    {
        hf_single_point_forces(&args);
    }
    if (args.job_type == JOB_TYPE_BOMD)
    {
        struct scf_context* ctx = scf_initialize(&args, hf_scf_config);
        u64 n_basis_funcs = ctx->n_basis_funcs;
        scf_finalize(ctx);

        struct md_context* md_ctx = md_initialize(&args, hf_calc_forces_on_nuclei, n_basis_funcs, "hf");
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
#endif
