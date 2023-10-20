/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "constants.h"
#include "vec3d.h"
#include "lebedev_grid.h"
#include "matrix.h"
#include "time_util.h"
#include "molecule.h"
#include "molecular_grid.h"
#include "scf.h"
#include "diagnostics.h"
#include "mm.h"
#include "radial_grid.h"
#include "einsum.h"
#include "thread_pool.h"
#include "standard_grid.h"
#include "cmd_line_args.h"

/*
 * In what follows, we use the following prefixes to indicate different types of variables:
 * gd_  : grid descriptor
 * agd_ : atomic grid descriptor
 * mgd_ : molecular grid descriptor
 */

struct task_func_bfvalues_derivatives_arg
{
    struct molecular_grid_desc* mgd;
    struct basis_func* bf;
    u64 M;
    u64 N;
    u64 i;
};

static void task_func_bfvalues_derivatives(void* p_arg)
{
    struct task_func_bfvalues_derivatives_arg* arg = (struct task_func_bfvalues_derivatives_arg*)p_arg;

    struct molecular_grid_desc* mgd = arg->mgd;
    struct basis_func* bf = arg->bf;
    u64 M = arg->M;
    u64 N = arg->N;
    u64 i = arg->i;

    f64* xx = mgd->bf_derivative_xx;
    f64* yy = mgd->bf_derivative_yy;
    f64* zz = mgd->bf_derivative_zz;
    f64* xy = mgd->bf_derivative_xy;
    f64* xz = mgd->bf_derivative_xz;
    f64* yz = mgd->bf_derivative_yz;

    for (u64 k = 0; k < M; ++k)
    {
        struct vec3d* glb_coord = mgd->global_coords + k;

        mgd->bf_values[k * N + i] = basis_funcs_value(bf, glb_coord);
        basis_funcs_first_derivative(bf,
                                     glb_coord,
                                     mgd->bf_derivative_x + k * N + i,
                                     mgd->bf_derivative_y + k * N + i,
                                     mgd->bf_derivative_z + k * N + i);
        mgd->bf_laplacian[k * N + i] = basis_func_laplacian(bf, glb_coord);
        basis_funcs_second_derivative(bf, glb_coord, xx + k * N + i, yy + k * N + i, zz + k * N + i, xy + k * N + i, xz + k * N + i, yz + k * N + i);
    }

    x_free(p_arg);
}

void calc_bfvalues_derivatives(struct molecular_grid_desc* mgd)
{
    struct scf_context* scf_ctx = mgd->scf_ctx;
    u64 M = mgd->grid_size;
    u64 N = scf_ctx->n_basis_funcs;

    for (u64 i = 0; i < N; ++i)
    {
        struct basis_func* bf = scf_ctx->basis_funcs + i;

        struct task_func_bfvalues_derivatives_arg* arg = x_malloc(sizeof(struct task_func_bfvalues_derivatives_arg));
        arg->mgd = mgd;
        arg->bf = bf;
        arg->M = M;
        arg->N = N;
        arg->i = i;
        threadpool_add_task(scf_ctx->tp_ctx, i % (scf_ctx->tp_ctx->n_workers), task_func_bfvalues_derivatives, arg);
    }

    threadpool_wait_job_done(scf_ctx->tp_ctx);
}

/*
 * calculates the densitry: rho, the contracted gradients of the density: sigma,
 * the laplacian of the density: lapl, the kinetic energy density: tau
 */
void calc_rho_sigma_lapl_tau(struct molecular_grid_desc* mgd)
{
    struct timespec time_start, time_end;
    get_wall_time(&time_start);

    struct scf_context* scf_ctx = mgd->scf_ctx;
    u64 M = mgd->grid_size;
    u64 N = scf_ctx->n_basis_funcs;

    f64* P = scf_ctx->P;

    f64* bf_values = mgd->bf_values;
    f64* bf_gradidents_x = mgd->bf_derivative_x;
    f64* bf_gradidents_y = mgd->bf_derivative_y;
    f64* bf_gradidents_z = mgd->bf_derivative_z;
    f64* bf_laplacian = mgd->bf_laplacian;

    f64* rho = mgd->densities;
    f64* sigma_x = mgd->density_derivative_x;
    f64* sigma_y = mgd->density_derivative_y;
    f64* sigma_z = mgd->density_derivative_z;
    f64* lapl = mgd->lapl;
    f64* tau = mgd->tau;

    f64* M1 = mgd->MxN;
    f64* M2 = mgd->MxN_2;

    /* calc rho */
    einsum_mn_np__mp_parallel(bf_values, P, M1, M, N, N, scf_ctx->tp_ctx);
    einsum_mn_mn__m(bf_values, M1, rho, M, N);

    /*
     * In theory, we should use the transpose of the matrix P (PT) in some of the equations.
     * Currently, the program is designed to work with symmetric density matrix only, therefore
     * PT = P
     */
    f64* PT = tag_transpose(P);

    /* calc sigma_x */
    einsum_mn_mn__m(M1, bf_gradidents_x, sigma_x, M, N);
    mat_scalar_multiply(sigma_x, sigma_x, M, 1, 2.0);
    einsum_mn_np__mp_parallel(bf_gradidents_x, PT, M2, M, N, N, scf_ctx->tp_ctx);
    einsum_mn_mn__m(M2, bf_gradidents_x, tau, M, N);

    /* calc sigma_y */
    einsum_mn_mn__m(M1, bf_gradidents_y, sigma_y, M, N);
    mat_scalar_multiply(sigma_y, sigma_y, M, 1, 2.0);
    einsum_mn_np__mp_parallel(bf_gradidents_y, PT, M2, M, N, N, scf_ctx->tp_ctx);

    for (u64 i = 0; i < M; ++i)
    {
        f64 value = 0.0;
        u64 in = i * N;
        for (u64 j = 0; j < N; ++j)
        {
            value += M2[in + j] * bf_gradidents_y[in + j];
        }
        tau[i] += value;
    }

    /* calc sigma_z */
    einsum_mn_mn__m(M1, bf_gradidents_z, sigma_z, M, N);
    mat_scalar_multiply(sigma_z, sigma_z, M, 1, 2.0);
    einsum_mn_np__mp_parallel(bf_gradidents_z, PT, M2, M, N, N, scf_ctx->tp_ctx);

    for (u64 i = 0; i < M; ++i)
    {
        f64 value = 0.0;
        u64 in = i * N;
        for (u64 j = 0; j < N; ++j)
        {
            value += M2[in + j] * bf_gradidents_z[in + j];
        }
        tau[i] += value;

        mgd->densities_sigma[i] = sigma_x[i] * sigma_x[i] + sigma_y[i] * sigma_y[i] + sigma_z[i] * sigma_z[i];
    }

    einsum_mn_mn__m(M1, bf_laplacian, lapl, M, N);
    mat_add(lapl, tau, lapl, M, 1);
    mat_scalar_multiply(lapl, lapl, M, 1, 2.0);
    mat_scalar_multiply(tau, tau, M, 1, 0.5);

    mat_scalar_multiply(rho, rho, M, 1, 2.0);

    f64 density_sum = 0.0;
    for (int i = 0, ag_offset = 0; i < scf_ctx->mol->n_atoms; ++i)
    {
        struct atomic_grid_desc* gd = mgd->atomic_grid_descs + i;
        for (int j = 0; j < gd->grid_size; ++j)
        {
            density_sum += mgd->weights[ag_offset + j] * mgd->densities[ag_offset + j];
        }
        ag_offset += gd->grid_size;
    }

    f64 correction_factor = scf_ctx->mol->n_electrons / density_sum;
    for (u64 i = 0; i < mgd->grid_size; ++i)
    {
        mgd->densities[i] *= correction_factor;
    }

    get_wall_time(&time_end);
    console_printf(scf_ctx->silent, "calc_rho_sigma_lapl_tau took %.3f ms\n", diff_time_ms(&time_start, &time_end));
}

struct task_func_calc_integration_weights_arg
{
    struct atomic_grid_desc* gd;
    u64 ag_offset;
};

static void task_func_calc_integration_weights(void* p_arg)
{
    struct task_func_calc_integration_weights_arg* arg = (struct task_func_calc_integration_weights_arg*)p_arg;
    struct atomic_grid_desc* gd = arg->gd;
    u64 ag_offset = arg->ag_offset;
    struct molecular_grid_desc* mgd = gd->mgd;

    f64 pi_n_1 = M_PI / (f64)(gd->num_radial_points + 1);
    u64 grid_point_idx = 0;
    for (i64 i = 1; i <= gd->num_radial_points; ++i)
    {
        /*
         * Calculates the abscissa of the Gauss-Chebyshev integration
         * Ref: Handbook of mathematical functions, p889, 25.4.40
         * x_i is in [-1, 1]
         *
         * Ref: An adaptive numerical integrator for molecular integrals, JCP 108, 1998
         */

        f64 x1 = i * pi_n_1;
        f64 sin_x1 = sin(x1);
        f64 xi = (gd->num_radial_points - 1.0 - (i - 1.0) * 2) / (gd->num_radial_points + 1.0) + (1 + 2.0 / 3.0 * sin_x1 * sin_x1) * sin(2 * x1) / M_PI;
        f64 r = 1 - log(1 + xi) * ONE_OVER_LN2;

        /*
         * An adaptive numerical integrator for molecular integrals, eq 10
         */
        f64 radial_weight = 16.0 / 3.0 / (gd->num_radial_points + 1.0) * pow(sin_x1, 4.0) * ONE_OVER_LN2 / (xi + 1) * 4 * M_PI * r * r;

        for (u64 a = 0; a < gd->num_angular_points; ++a)
        {
            struct vec3d* local_coord = mgd->local_coords + ag_offset + grid_point_idx;
            struct vec3d* global_coord = mgd->global_coords + ag_offset + grid_point_idx;
            local_coord->x = mgd->lebedev_grid[a * 3 + 0] * r;
            local_coord->y = mgd->lebedev_grid[a * 3 + 1] * r;
            local_coord->z = mgd->lebedev_grid[a * 3 + 2] * r;

            global_coord->x = local_coord->x + gd->nucleus_coord.x;
            global_coord->y = local_coord->y + gd->nucleus_coord.y;
            global_coord->z = local_coord->z + gd->nucleus_coord.z;

            mgd->weights[ag_offset + grid_point_idx] = radial_weight * mgd->lebedev_weights[a];
            ++grid_point_idx;
        }
    }

    x_free(p_arg);
}

static void task_func_calc_integration_weights_standard_grid(void* p_arg)
{
    struct task_func_calc_integration_weights_arg* arg = (struct task_func_calc_integration_weights_arg*)p_arg;
    struct atomic_grid_desc* gd = arg->gd;
    u64 ag_offset = arg->ag_offset;
    struct molecular_grid_desc* mgd = gd->mgd;

    f64 pi_n_1 = M_PI / (f64)(gd->num_radial_points + 1);
    u64 grid_point_idx = 0;
    for (i64 i = 1; i <= gd->num_radial_points; ++i)
    {
        /*
         * Calculates the abscissa of the Gauss-Chebyshev integration
         * Ref: Handbook of mathematical functions, p889, 25.4.40
         * x_i is in [-1, 1]
         *
         * Ref: An adaptive numerical integrator for molecular integrals, JCP 108, 1998
         */

        f64 x1 = i * pi_n_1;
        f64 sin_x1 = sin(x1);
        f64 xi = (gd->num_radial_points - 1.0 - (i - 1.0) * 2) / (gd->num_radial_points + 1.0) + (1 + 2.0 / 3.0 * sin_x1 * sin_x1) * sin(2 * x1) / M_PI;
        f64 r = 1 - log(1 + xi) * ONE_OVER_LN2;

        /*
         * An adaptive numerical integrator for molecular integrals, eq 10
         */
        f64 radial_weight = 16.0 / 3.0 / (gd->num_radial_points + 1.0) * pow(sin_x1, 4.0) * ONE_OVER_LN2 / (xi + 1) * 4 * M_PI * r * r;

        u64 num_angular_points = get_standard_grid_angular_point_num_by_radial_point_idx(gd->atomic_num, mgd->grid_scheme, i - 1);
        u64 lebedev_level = lebedev_num_points_to_level(num_angular_points);
        f64* lebedev_grid = x_malloc(num_angular_points * 3 * sizeof(f64));
        f64* lebedev_weights = x_malloc(num_angular_points * sizeof(f64));
        lebedev_gen_grid(lebedev_grid, lebedev_weights, lebedev_level);
        for (u64 a = 0; a < num_angular_points; ++a)
        {
            struct vec3d* local_coord = mgd->local_coords + ag_offset + grid_point_idx;
            struct vec3d* global_coord = mgd->global_coords + ag_offset + grid_point_idx;
            local_coord->x = lebedev_grid[a * 3 + 0] * r;
            local_coord->y = lebedev_grid[a * 3 + 1] * r;
            local_coord->z = lebedev_grid[a * 3 + 2] * r;

            global_coord->x = local_coord->x + gd->nucleus_coord.x;
            global_coord->y = local_coord->y + gd->nucleus_coord.y;
            global_coord->z = local_coord->z + gd->nucleus_coord.z;

            mgd->weights[ag_offset + grid_point_idx] = radial_weight * lebedev_weights[a];
            ++grid_point_idx;
        }
        x_free(lebedev_grid);
        x_free(lebedev_weights);
    }

    x_free(p_arg);
}

struct task_func_calc_becke_weights_arg
{
    struct atomic_grid_desc* gd;
    u64 ag_offset;
    u64 n;
};

static void task_func_calc_becke_weights(void* p_arg)
{
    struct task_func_calc_becke_weights_arg* arg = (struct task_func_calc_becke_weights_arg*)p_arg;
    struct atomic_grid_desc* gd = arg->gd;
    u64 ag_offset = arg->ag_offset;
    u64 n = arg->n;
    struct molecular_grid_desc* mgd = gd->mgd;
    struct molecule* mol = mgd->scf_ctx->mol;

    for (u64 k = 0; k < gd->grid_size; ++k)
    {
        f64 denom = 0.0;
        f64 nom = 0.0;
        struct vec3d* gp_coord = mgd->global_coords + ag_offset + k;

        // loop over all atoms to get Pn(r)
        for (u64 i = 0; i < mol->n_atoms; ++i)
        {
            struct vec3d* coord_i = mol->coords + i;
            f64 wprod = 1.0;

            for (u64 j = 0; j < mol->n_atoms; ++j)
            {
                if (j != i)
                {
                    struct vec3d* coord_j = mol->coords + j;

                    /* becke1988: JCP 88 (1988), p2549 */
                    struct vec3d tmp;
                    vec3d_subtract(gp_coord, coord_i, &tmp);
                    f64 r_i = sqrt(vec3d_norm_squared(&tmp));
                    vec3d_subtract(gp_coord, coord_j, &tmp);
                    f64 r_j = sqrt(vec3d_norm_squared(&tmp));
                    vec3d_subtract(coord_j, coord_i, &tmp);
                    f64 r_ij = sqrt(vec3d_norm_squared(&tmp));

                    /* becke1988, eq 11 */
                    f64 mu = (r_i - r_j) / r_ij;

                    // becke1988, eq 20, making f(mu) sharp by 3 iterations
                    for (u64 kk = 0; kk < 3; ++kk)
                    {
                        mu = 3.0 / 2.0 * mu - 0.5 * pow(mu, 3.0);
                    }

                    /* becke1988, eq 21 and eq 13 */
                    wprod *= 0.5 * (1.0 - mu);
                }
            }

            denom += wprod;
            if (i == n)
            {
                nom = wprod;
            }
        }

        // becke1988, eq 22
        f64 becke_weight = nom / denom;
        mgd->weights[ag_offset + k] *= becke_weight;
        mgd->becke_weights[ag_offset + k] = becke_weight;
    }

    x_free(p_arg);
}

void build_molecular_grid(struct molecular_grid_desc* mgd)
{
    struct timespec time_start, time_end;
    get_wall_time(&time_start);

    struct scf_context* scf_ctx = mgd->scf_ctx;
    struct molecule* mol = scf_ctx->mol;

    /*
     * Build lebedev grid, which is the angular part of the molecular grid.
     * The output consists of two parts:
     *   lebedev_grid is a set of (x, y, z)
     *   lebedev_weights the corresponding weights for the grid points
     */
    mgd->num_angular_points = lebedev_num_points(mgd->lebedev_level);
    mgd->lebedev_grid = x_malloc(mgd->num_angular_points * 3 * sizeof(f64));
    mgd->lebedev_weights = x_malloc(mgd->num_angular_points * sizeof(f64));
    lebedev_gen_grid(mgd->lebedev_grid, mgd->lebedev_weights, mgd->lebedev_level);

    mgd->atomic_grid_descs = x_malloc(mol->n_atoms * sizeof(struct atomic_grid_desc));
    mgd->grid_size = 0;
    for (u64 i = 0; i < mol->n_atoms; ++i)
    {
        struct atomic_grid_desc* gd = mgd->atomic_grid_descs + i;
        gd->mgd = mgd;

        /*
         * In theory, each gd can have its own num_radial_points, num_angular_points, and max_angular_number
         * We will implement and improve the atomic adjustments later.
         */
        gd->atomic_num = mol->atomic_nums[i];

        if (mgd->grid_scheme == GRID_SCHEME_FULL)
        {
            gd->num_radial_points = get_num_radial_points(mgd->radial_grid_level, mol->atomic_nums[i]);
            gd->num_angular_points = mgd->num_angular_points;
            gd->grid_size = gd->num_radial_points * gd->num_angular_points;
        }

        if (mgd->grid_scheme == GRID_SCHEME_SG2 || mgd->grid_scheme == GRID_SCHEME_SG3)
        {
            gd->num_radial_points = get_standard_grid_radial_point_num(gd->atomic_num, mgd->grid_scheme);
            gd->grid_size = get_standard_grid_point_num(gd->atomic_num, mgd->grid_scheme);
        }

        struct vec3d* nucleus_coord = mol->coords + i;
        gd->nucleus_coord.x = nucleus_coord->x;
        gd->nucleus_coord.y = nucleus_coord->y;
        gd->nucleus_coord.z = nucleus_coord->z;

        mgd->grid_size += gd->grid_size;
    }

    console_printf(mgd->scf_ctx->silent, "Molecular grid size: %lu\n", mgd->grid_size);

    u64 M = mgd->grid_size;
    u64 N = scf_ctx->n_basis_funcs;

    mgd->global_coords = x_malloc(M * sizeof(struct vec3d));
    mgd->local_coords = x_malloc(M * sizeof(struct vec3d));
    mgd->weights = x_malloc(M * sizeof(f64));
    mgd->becke_weights = x_malloc(M * sizeof(f64));

    mgd->V = x_malloc(M * sizeof(f64));
    mgd->V_fuzzy_cell = x_malloc(M * sizeof(f64));
    mgd->J = x_malloc(N * N * sizeof(f64));
    mgd->K = x_malloc(N * N * sizeof(f64));
    mgd->XC = x_calloc(N * N, sizeof(f64));
    mgd->VXC_x = x_calloc(N * N, sizeof(f64));
    mgd->VXC_y = x_calloc(N * N, sizeof(f64));
    mgd->VXC_z = x_calloc(N * N, sizeof(f64));

    mgd->densities = x_malloc(M * sizeof(f64));
    mgd->density_derivative_x = x_malloc(M * sizeof(f64));
    mgd->density_derivative_y = x_malloc(M * sizeof(f64));
    mgd->density_derivative_z = x_malloc(M * sizeof(f64));
    mgd->densities_sigma = x_malloc(M * sizeof(f64));
    mgd->lapl = x_malloc(M * sizeof(f64));
    mgd->tau = x_malloc(M * sizeof(f64));
    mgd->exc_x = x_malloc(M * sizeof(f64));
    mgd->vrho_x = x_malloc(M * sizeof(f64));
    mgd->exc_c = x_malloc(M * sizeof(f64));
    mgd->vrho_c = x_malloc(M * sizeof(f64));
    mgd->vsigma_x = x_malloc(M * sizeof(f64));
    mgd->vlapl_x = x_malloc(M * sizeof(f64));
    mgd->vtau_x = x_malloc(M * sizeof(f64));
    mgd->vsigma_c = x_malloc(M * sizeof(f64));
    mgd->vlapl_c = x_malloc(M * sizeof(f64));
    mgd->vtau_c = x_malloc(M * sizeof(f64));

    mgd->d_sigma_x = x_malloc(M * sizeof(f64));
    mgd->d_sigma_y = x_malloc(M * sizeof(f64));
    mgd->d_sigma_z = x_malloc(M * sizeof(f64));

    mgd->d_lapl_x = x_malloc(M * sizeof(f64));
    mgd->d_lapl_y = x_malloc(M * sizeof(f64));
    mgd->d_lapl_z = x_malloc(M * sizeof(f64));

    mgd->d_tau_x = x_malloc(M * sizeof(f64));
    mgd->d_tau_y = x_malloc(M * sizeof(f64));
    mgd->d_tau_z = x_malloc(M * sizeof(f64));

    mgd->weighted_vrho = x_malloc(M * sizeof(f64));

    mgd->weighted_vsigma_rho_dx = x_malloc(M * sizeof(f64));
    mgd->weighted_vsigma_rho_dy = x_malloc(M * sizeof(f64));
    mgd->weighted_vsigma_rho_dz = x_malloc(M * sizeof(f64));

    mgd->NxN = x_malloc(N * N * sizeof(f64));
    mgd->Mx1 = x_malloc(M * sizeof(f64));

    for (u64 n = 0, ag_offset = 0; n < mol->n_atoms; ++n)
    {
        struct atomic_grid_desc* gd = mgd->atomic_grid_descs + n;

        struct task_func_calc_integration_weights_arg* arg = x_malloc(sizeof(struct task_func_calc_integration_weights_arg));
        arg->gd = gd;
        arg->ag_offset = ag_offset;
        if (mgd->grid_scheme == GRID_SCHEME_FULL)
        {
            threadpool_add_task(scf_ctx->tp_ctx, n % (scf_ctx->tp_ctx->n_workers), task_func_calc_integration_weights, arg);
        }
        if (mgd->grid_scheme == GRID_SCHEME_SG2 || mgd->grid_scheme == GRID_SCHEME_SG3)
        {
            threadpool_add_task(scf_ctx->tp_ctx, n % (scf_ctx->tp_ctx->n_workers), task_func_calc_integration_weights_standard_grid, arg);
        }

        ag_offset += gd->grid_size;
    }
    threadpool_wait_job_done(scf_ctx->tp_ctx);

    for (u64 n = 0, ag_offset = 0; n < mol->n_atoms; ++n)
    {
        struct atomic_grid_desc* gd = mgd->atomic_grid_descs + n;

        struct task_func_calc_becke_weights_arg* arg = x_malloc(sizeof(struct task_func_calc_becke_weights_arg));
        arg->gd = gd;
        arg->ag_offset = ag_offset;
        arg->n = n;
        threadpool_add_task(scf_ctx->tp_ctx, n % (scf_ctx->tp_ctx->n_workers), task_func_calc_becke_weights, arg);

        ag_offset += gd->grid_size;
    }
    threadpool_wait_job_done(scf_ctx->tp_ctx);

    mgd->bf_values = x_malloc(M * N * sizeof(f64));
    mgd->bf_derivative_x = x_malloc(M * N * sizeof(f64));
    mgd->bf_derivative_y = x_malloc(M * N * sizeof(f64));
    mgd->bf_derivative_z = x_malloc(M * N * sizeof(f64));
    mgd->bf_laplacian = x_malloc(M * N * sizeof(f64));
    mgd->bf_derivative_xx = x_malloc(M * N * sizeof(f64));
    mgd->bf_derivative_yy = x_malloc(M * N * sizeof(f64));
    mgd->bf_derivative_zz = x_malloc(M * N * sizeof(f64));
    mgd->bf_derivative_xy = x_malloc(M * N * sizeof(f64));
    mgd->bf_derivative_xz = x_malloc(M * N * sizeof(f64));
    mgd->bf_derivative_yz = x_malloc(M * N * sizeof(f64));

    mgd->bf_v = x_malloc(M * N * sizeof(f64));
    mgd->bf_v_dx = x_malloc(M * N * sizeof(f64));
    mgd->bf_v_dy = x_malloc(M * N * sizeof(f64));
    mgd->bf_v_dz = x_malloc(M * N * sizeof(f64));
    mgd->MxN = x_malloc(M * N * sizeof(f64));
    mgd->MxN_2 = x_malloc(M * N * sizeof(f64));

    get_wall_time(&time_end);
    console_printf(scf_ctx->silent, "build_molecular_grid took %.3f ms\n", diff_time_ms(&time_start, &time_end));
}

f64 cal_rho_sum_with_grid(struct molecular_grid_desc* mgd)
{
    f64 total_rho = 0.0;
    for (u64 i = 0; i < mgd->grid_size; ++i)
    {
        total_rho += mgd->weights[i] * mgd->densities[i];
    }
    return total_rho;
}
