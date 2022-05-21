/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dft_matrices.h"
#include "basis_func.h"
#include "molecule.h"
#include "math_util.h"
#include "cpp_bridge.h"
#include "functional.h"
#include "libxc_bridge.h"
#include "spinlock.h"
#include "thread_pool.h"
#include "diagnostics.h"
#include "molecular_integral.h"
#include "mm.h"
#include "einsum.h"
#include "time_util.h"

struct task_func_build_K_arg
{
    struct scf_context *ctx;
    f64 *K;
    f64 *P;
    u64 i;
    u64 j;
    u64 k;
    u64 l;
    u64 i_j;
    u64 k_l;
    u64 ij_kl;
};

void task_func_build_K(void *p_arg)
{
    struct task_func_build_K_arg *arg = (struct task_func_build_K_arg *)p_arg;
    struct scf_context *ctx = arg->ctx;
    volatile atomic_bool *L = ctx->LOCK;
    f64 *K = arg->K;
    f64 *P = arg->P;
    u64 i = arg->i;
    u64 j = arg->j;
    u64 k = arg->k;
    u64 l = arg->l;
    u64 i_j = arg->i_j;
    u64 k_l = arg->k_l;
    u64 ij_kl = arg->ij_kl;
    u64 N = ctx->n_basis_funcs;
    u64 iN = i * N;
    u64 iNk = iN + k;
    u64 jN = j * N;
    u64 jNk = jN + k;
    u64 kN = k * N;
    u64 kNj = kN + j;

    f64 val = cg_electron_repulsion_integral(ctx->basis_funcs + i, ctx->basis_funcs + j,
                  ctx->basis_funcs + k, ctx->basis_funcs + l) *
              i_j * k_l * ij_kl;

    /* Exchange */
    spinlock_lock(L + iNk);
    K[iNk] += val * P[jN + l] * 0.25;
    spinlock_unlock(L + iNk);
    spinlock_lock(L + jN + l);
    K[jN + l] += val * P[iNk] * 0.25;
    spinlock_unlock(L + jN + l);
    spinlock_lock(L + iN + l);
    K[iN + l] += val * P[jNk] * 0.25;
    spinlock_unlock(L + iN + l);
    spinlock_lock(L + kNj);
    K[kNj] += val * P[iN + l] * 0.25;
    spinlock_unlock(L + kNj);
    x_free(p_arg);
}

void build_K_matrix(struct molecular_grid_desc *mgd)
{
    struct scf_context *ctx = mgd->scf_ctx;
    u64 N = ctx->n_basis_funcs;

    f64 *P = ctx->P;
    f64 *K = mgd->K;
    memset(K, 0, N * N * sizeof(f64));

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
                        f64 ps[] = {fabs(4 * P[i * N + j]), fabs(4 * P[k * N + l]), fabs(P[i * N + k]), fabs(P[i * N + l]), fabs(P[j * N + k]), fabs(P[j * N + l])};

                        for (u64 t = 0; t < 6; ++t)
                        {
                            if (ps[t] > pmax)
                            {
                                pmax = ps[t];
                            }
                        }

                        if ((bound * pmax) < ctx->JK_screening_threshold)
                        {
                            //printf("skipping %lu,%lu,%lu,%lu\n", i, j, k, l);
                            continue;
                        }

                        struct task_func_build_K_arg *arg = x_malloc(sizeof(struct task_func_build_K_arg));
                        arg->ctx = ctx;
                        arg->K = K;
                        arg->P = P;
                        arg->i = i;
                        arg->j = j;
                        arg->k = k;
                        arg->l = l;
                        arg->i_j = i_j;
                        arg->k_l = k_l;
                        arg->ij_kl = ij_kl;
                        threadpool_add_task(ctx->tp_ctx, (iN * N * N + jN * N + kN + l) % (ctx->tp_ctx->n_workers), task_func_build_K, arg);
                    }
                }
            }
        }
    }

    threadpool_wait_job_done(ctx->tp_ctx);

    f64 *M = ctx->NxN_1;
    transpose(K, M, N, N);
    mat_add(K, M, M, N, N);
    mat_scalar_multiply(M, K, N, N, 0.5);
}

struct task_func_build_J_arg
{
    struct scf_context *ctx;
    f64 *J;
    f64 *P;
    u64 i;
    u64 j;
    u64 k;
    u64 l;
    u64 i_j;
    u64 k_l;
    u64 ij_kl;
};

void task_func_build_J(void *p_arg)
{
    struct task_func_build_J_arg *arg = (struct task_func_build_J_arg *)p_arg;
    struct scf_context *ctx = arg->ctx;
    volatile atomic_bool *L = ctx->LOCK;
    f64 *J = arg->J;
    f64 *P = arg->P;
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
    u64 kN = k * N;

    f64 val = cg_electron_repulsion_integral(ctx->basis_funcs + i, ctx->basis_funcs + j,
                  ctx->basis_funcs + k, ctx->basis_funcs + l) *
              i_j * k_l * ij_kl;

    /* Coulomb */
    spinlock_lock(L + iNj);
    J[iNj] += val * P[kN + l];
    spinlock_unlock(L + iNj);
    spinlock_lock(L + kN + l);
    J[kN + l] += val * P[iNj];
    spinlock_unlock(L + kN + l);
    x_free(p_arg);
}

void build_J_matrix(struct molecular_grid_desc *mgd)
{
    struct scf_context *ctx = mgd->scf_ctx;
    u64 N = ctx->n_basis_funcs;

    f64 *P = ctx->P;
    f64 *J = mgd->J;
    memset(J, 0, N * N * sizeof(f64));

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
                        f64 ps[] = {fabs(4 * P[i * N + j]), fabs(4 * P[k * N + l]), fabs(P[i * N + k]), fabs(P[i * N + l]), fabs(P[j * N + k]), fabs(P[j * N + l])};

                        for (u64 t = 0; t < 6; ++t)
                        {
                            if (ps[t] > pmax)
                            {
                                pmax = ps[t];
                            }
                        }

                        if ((bound * pmax) < ctx->JK_screening_threshold)
                        {
                            //printf("skipping %lu,%lu,%lu,%lu\n", i, j, k, l);
                            continue;
                        }

                        struct task_func_build_J_arg *arg = x_malloc(sizeof(struct task_func_build_J_arg));
                        arg->ctx = ctx;
                        arg->J = J;
                        arg->P = P;
                        arg->i = i;
                        arg->j = j;
                        arg->k = k;
                        arg->l = l;
                        arg->i_j = i_j;
                        arg->k_l = k_l;
                        arg->ij_kl = ij_kl;
                        threadpool_add_task(ctx->tp_ctx, (iN * N * N + jN * N + kN + l) % (ctx->tp_ctx->n_workers), task_func_build_J, arg);
                    }
                }
            }
        }
    }

    threadpool_wait_job_done(ctx->tp_ctx);

    f64 *M = ctx->NxN_1;
    transpose(J, M, N, N);
    mat_add(J, M, M, N, N);
    mat_scalar_multiply(M, J, N, N, 0.25);
}

struct task_func_build_JK_arg
{
    struct scf_context *ctx;
    f64 *J;
    f64 *K;
    f64 *P;
    u64 i;
    u64 j;
    u64 k;
    u64 l;
    u64 i_j;
    u64 k_l;
    u64 ij_kl;
};

void task_func_build_JK(void *p_arg)
{
    struct task_func_build_JK_arg *arg = (struct task_func_build_JK_arg *)p_arg;
    struct scf_context *ctx = arg->ctx;
    volatile atomic_bool *L = ctx->LOCK;
    f64 *J = arg->J;
    f64 *K = arg->K;
    f64 *P = arg->P;
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
    J[iNj] += val * P[kN + l];
    spinlock_unlock(L + iNj);
    spinlock_lock(L + kN + l);
    J[kN + l] += val * P[iNj];
    spinlock_unlock(L + kN + l);

    /* Exchange */
    spinlock_lock(L + iNk);
    K[iNk] += val * P[jN + l] * 0.25;
    spinlock_unlock(L + iNk);
    spinlock_lock(L + jN + l);
    K[jN + l] += val * P[iNk] * 0.25;
    spinlock_unlock(L + jN + l);
    spinlock_lock(L + iN + l);
    K[iN + l] += val * P[jNk] * 0.25;
    spinlock_unlock(L + iN + l);
    spinlock_lock(L + kNj);
    K[kNj] += val * P[iN + l] * 0.25;
    spinlock_unlock(L + kNj);

    x_free(p_arg);
}

void build_JK_matrices(struct molecular_grid_desc* mgd)
{
    struct scf_context* ctx = mgd->scf_ctx;
    u64 N = ctx->n_basis_funcs;

    f64* P = ctx->P;
    f64* J = mgd->J;
    f64* K = mgd->K;
    memset(J, 0, N * N * sizeof(f64));
    memset(K, 0, N * N * sizeof(f64));

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
                        f64 ps[] = { fabs(4 * P[i * N + j]), fabs(4 * P[k * N + l]), fabs(P[i * N + k]), fabs(P[i * N + l]), fabs(P[j * N + k]), fabs(P[j * N + l]) };

                        for (u64 t = 0; t < 6; ++t)
                        {
                            if (ps[t] > pmax)
                            {
                                pmax = ps[t];
                            }
                        }

                        if ((bound * pmax) < ctx->JK_screening_threshold)
                        {
                            //printf("skipping %lu,%lu,%lu,%lu\n", i, j, k, l);
                            continue;
                        }

                        struct task_func_build_JK_arg* arg = x_malloc(sizeof(struct task_func_build_JK_arg));
                        arg->ctx = ctx;
                        arg->J = J;
                        arg->K = K;
                        arg->P = P;
                        arg->i = i;
                        arg->j = j;
                        arg->k = k;
                        arg->l = l;
                        arg->i_j = i_j;
                        arg->k_l = k_l;
                        arg->ij_kl = ij_kl;
                        threadpool_add_task(ctx->tp_ctx, (iN * N * N + jN * N + kN + l) % (ctx->tp_ctx->n_workers), task_func_build_JK, arg);
                    }
                }
            }
        }
    }

    threadpool_wait_job_done(ctx->tp_ctx);

    f64* M = ctx->NxN_1;
    transpose(J, M, N, N);
    mat_add(J, M, M, N, N);
    mat_scalar_multiply(M, J, N, N, 0.25);

    M = ctx->NxN_1;
    transpose(K, M, N, N);
    mat_add(K, M, M, N, N);
    mat_scalar_multiply(M, K, N, N, 0.5);
}

void build_xc_matrix_with_grid(struct molecular_grid_desc *mgd)
{
    struct scf_context *scf_ctx = mgd->scf_ctx;
    u64 N = scf_ctx->n_basis_funcs;

    /* input variables */
    f64 *rho = mgd->densities;
    f64 *sigma = mgd->densities_sigma;
    f64 *lapl = mgd->lapl;
    f64 *tau = mgd->tau;

    /* output variable */
    f64 *exc_x = mgd->exc_x;
    f64 *vrho_x = mgd->vrho_x;
    f64 *exc_c = mgd->exc_c;
    f64 *vrho_c = mgd->vrho_c;

    f64 *XC = mgd->XC;
    f64 *NxN = mgd->NxN;
    f64 *bf_v = mgd->bf_v;
    f64 *weighted_vrho = mgd->weighted_vrho;
    f64 *MxN = mgd->MxN;
    f64 *Mx1 = mgd->Mx1;

    struct timespec time_start, time_end;

    mgd->hf_exchange_energy = 0.0;
    if (mgd->x_functional_id)
    {
        /* built-in x functional */
        //functional_lda_x(rho, exc_x, vrho_x, mgd->grid_size);

        get_wall_time(&time_start);
        libxc_exc_vxc(mgd->x_functional_id, mgd->grid_size, rho, sigma, lapl, tau,
                      exc_x, vrho_x, mgd->vsigma_x, mgd->vlapl_x, mgd->vtau_x);
        get_wall_time(&time_end);
        console_printf(scf_ctx->silent, "libxc_exc_vxc (x) took %.3f ms\n", diff_time_ms(&time_start, &time_end));

        f64 hyb_coef = libxc_hyb_coef(mgd->x_functional_id);
        if (hyb_coef > 0.0)
        {
            einsum_mn_np__mp(scf_ctx->P, mgd->K, NxN, N, N, N);
            mgd->hf_exchange_energy = -0.25 * mattrace(NxN, N) * hyb_coef;
        }
        mgd->hyb_coef = hyb_coef;
    }
    else
    {
        memset(exc_x, 0, mgd->grid_size * sizeof(f64));
        memset(vrho_x, 0, mgd->grid_size * sizeof(f64));
        memset(mgd->vsigma_x, 0, mgd->grid_size * sizeof(f64));
        memset(mgd->vtau_x, 0, mgd->grid_size * sizeof(f64));
    }

    if (mgd->c_functional_id)
    {
        /* built-in c functional */
        //functional_lda_c_vwn(rho, exc_c, vrho_c, mgd->grid_size);

        get_wall_time(&time_start);
        libxc_exc_vxc(mgd->c_functional_id, mgd->grid_size, rho, sigma, lapl, tau,
                      exc_c, vrho_c, mgd->vsigma_c, mgd->vlapl_c, mgd->vtau_c);
        get_wall_time(&time_end);
        console_printf(scf_ctx->silent, "libxc_exc_vxc (c) took %.3f ms\n", diff_time_ms(&time_start, &time_end));
    }
    else
    {
        memset(exc_c, 0, mgd->grid_size * sizeof(f64));
        memset(vrho_c, 0, mgd->grid_size * sizeof(f64));
        memset(mgd->vsigma_c, 0, mgd->grid_size * sizeof(f64));
        memset(mgd->vtau_c, 0, mgd->grid_size * sizeof(f64));
    }

    mgd->xc_energy = mgd->hf_exchange_energy;
    for (u64 i = 0; i < mgd->grid_size; ++i)
    {
        /*
         * E_{xc} = integrate[rho e(rho, ...) dxdydz]
         * Following the libxc convention,
         * exc is the e(rho, ...) part.
         * Therefore, an additional rho[i] term is needed.
         */
        mgd->xc_energy += mgd->weights[i] * (exc_x[i] + exc_c[i]) * rho[i];
    }

    mat_add(mgd->vrho_x, mgd->vrho_c, Mx1, mgd->grid_size, 1);
    mat_multiply(mgd->weights, Mx1, weighted_vrho, mgd->grid_size, 1);
    mat_scalar_multiply(weighted_vrho, weighted_vrho, mgd->grid_size, 1, 0.5);

    if (mgd->xc_type == XC_TYPE_LDA)
    {
        /*
        for (u64 p = 0; p < mgd->grid_size; ++p)
        {
            u64 pN = p * N;
            for (u64 i = 0; i < N; ++i)
            {
                u64 pN_i = pN + i;
                bf_v[pN_i] = mgd->bf_values[pN_i] * weighted_vrho[p];
            }
        }
        einsum_mn_mp__np(mgd->bf_values, bf_v, XC, mgd->grid_size, N, N);
        */

        /* derivatives wrt nuclear coordinates begin */
        /*
        einsum_mn_mp__np(mgd->bf_derivative_x, bf_v, mgd->VXC_x, mgd->grid_size, N, N);
        einsum_mn_mp__np(mgd->bf_derivative_y, bf_v, mgd->VXC_y, mgd->grid_size, N, N);
        einsum_mn_mp__np(mgd->bf_derivative_z, bf_v, mgd->VXC_z, mgd->grid_size, N, N);
        for (u64 p = 0; p < mgd->grid_size; ++p)
        {
            u64 pN = p * N;
            for (u64 i = 0; i < N; ++i)
            {
                u64 pN_i = pN + i;
                mgd->bf_v_dx[pN_i] = mgd->bf_derivative_x[pN_i] * weighted_vrho[p];
                mgd->bf_v_dy[pN_i] = mgd->bf_derivative_y[pN_i] * weighted_vrho[p];
                mgd->bf_v_dz[pN_i] = mgd->bf_derivative_z[pN_i] * weighted_vrho[p];
            }
        }
        einsum_mn_mp__np(mgd->bf_v_dx, mgd->bf_values, NxN, mgd->grid_size, N, N);
        mat_add(mgd->VXC_x, NxN, mgd->VXC_x, N, N);
        einsum_mn_mp__np(mgd->bf_v_dy, mgd->bf_values, NxN, mgd->grid_size, N, N);
        mat_add(mgd->VXC_y, NxN, mgd->VXC_y, N, N);
        einsum_mn_mp__np(mgd->bf_v_dz, mgd->bf_values, NxN, mgd->grid_size, N, N);
        mat_add(mgd->VXC_z, NxN, mgd->VXC_z, N, N);
        */
        /* derivatives wrt nuclear coordinates end */

        // For the LDA case, we adopt the following alternative implementation
        einsum_mn_mp_m__np(mgd->bf_values, mgd->bf_values, weighted_vrho, XC, mgd->grid_size, N, N);

        /* derivatives wrt nuclear coordinates begin */
        /*
        einsum_mn_mp_m__np(mgd->bf_derivative_x, mgd->bf_values, weighted_vrho, mgd->VXC_x, mgd->grid_size, N, N);
        einsum_mn_mp_m__np(mgd->bf_derivative_y, mgd->bf_values, weighted_vrho, mgd->VXC_y, mgd->grid_size, N, N);
        einsum_mn_mp_m__np(mgd->bf_derivative_z, mgd->bf_values, weighted_vrho, mgd->VXC_z, mgd->grid_size, N, N);

        mat_scalar_multiply(mgd->VXC_x, mgd->VXC_x, N, N, 2.0);
        mat_scalar_multiply(mgd->VXC_y, mgd->VXC_y, N, N, 2.0);
        mat_scalar_multiply(mgd->VXC_z, mgd->VXC_z, N, N, 2.0);
        */
        /* derivatives wrt nuclear coordinates end */
    }

    if (mgd->xc_type == XC_TYPE_GGA || mgd->xc_type == XC_TYPE_MGGA)
    {
        f64 *weighted_vsigma_rho_dx = mgd->weighted_vsigma_rho_dx;
        f64 *weighted_vsigma_rho_dy = mgd->weighted_vsigma_rho_dy;
        f64 *weighted_vsigma_rho_dz = mgd->weighted_vsigma_rho_dz;

        /* Mx1 = v_sigma_x + vsigma_c */
        mat_add(mgd->vsigma_x, mgd->vsigma_c, Mx1, mgd->grid_size, 1);

        mat_multiply(mgd->weights, Mx1, weighted_vsigma_rho_dx, mgd->grid_size, 1);
        mat_multiply(weighted_vsigma_rho_dx, mgd->density_derivative_x, weighted_vsigma_rho_dx, mgd->grid_size, 1);
        mat_scalar_multiply(weighted_vsigma_rho_dx, weighted_vsigma_rho_dx, mgd->grid_size, 1, 2.0);

        mat_multiply(mgd->weights, Mx1, weighted_vsigma_rho_dy, mgd->grid_size, 1);
        mat_multiply(weighted_vsigma_rho_dy, mgd->density_derivative_y, weighted_vsigma_rho_dy, mgd->grid_size, 1);
        mat_scalar_multiply(weighted_vsigma_rho_dy, weighted_vsigma_rho_dy, mgd->grid_size, 1, 2.0);

        mat_multiply(mgd->weights, Mx1, weighted_vsigma_rho_dz, mgd->grid_size, 1);
        mat_multiply(weighted_vsigma_rho_dz, mgd->density_derivative_z, weighted_vsigma_rho_dz, mgd->grid_size, 1);
        mat_scalar_multiply(weighted_vsigma_rho_dz, weighted_vsigma_rho_dz, mgd->grid_size, 1, 2.0);

        for (u64 p = 0; p < mgd->grid_size; ++p)
        {
            u64 pN = p * N;
            for (u64 i = 0; i < N; ++i)
            {
                u64 pN_i = pN + i;
                bf_v[pN_i] = mgd->bf_values[pN_i] * weighted_vrho[p] + mgd->bf_derivative_x[pN_i] * weighted_vsigma_rho_dx[p] + mgd->bf_derivative_y[pN_i] * weighted_vsigma_rho_dy[p] + mgd->bf_derivative_z[pN_i] * weighted_vsigma_rho_dz[p];
            }
        }

        get_wall_time(&time_start);
        //einsum_mn_mp__np(mgd->bf_values, bf_v, XC, mgd->grid_size, N, N);
        einsum_mn_mp__np_parallel(mgd->bf_values, bf_v, XC, mgd->grid_size, N, N, scf_ctx->tp_ctx);
        get_wall_time(&time_end);
        console_printf(scf_ctx->silent, "einsum_mn_mp__np took %.3f ms\n", diff_time_ms(&time_start, &time_end));

        /* derivatives wrt nuclear coordinates begin */
        /*
        einsum_mn_mp__np(mgd->bf_derivative_x, bf_v, mgd->VXC_x, mgd->grid_size, N, N);
        einsum_mn_mp__np(mgd->bf_derivative_y, bf_v, mgd->VXC_y, mgd->grid_size, N, N);
        einsum_mn_mp__np(mgd->bf_derivative_z, bf_v, mgd->VXC_z, mgd->grid_size, N, N);

        for (u64 p = 0; p < mgd->grid_size; ++p)
        {
            u64 pN = p * N;
            for (u64 i = 0; i < N; ++i)
            {
                u64 pN_i = pN + i;
                mgd->bf_v_dx[pN_i] = mgd->bf_derivative_x[pN_i] * weighted_vrho[p] +
                                                    mgd->bf_derivative_xx[pN_i] * weighted_vsigma_rho_dx[p] +
                                                    mgd->bf_derivative_xy[pN_i] * weighted_vsigma_rho_dy[p] +
                                                    mgd->bf_derivative_xz[pN_i] * weighted_vsigma_rho_dz[p];

                mgd->bf_v_dy[pN_i] = mgd->bf_derivative_y[pN_i] * weighted_vrho[p] +
                                                    mgd->bf_derivative_xy[pN_i] * weighted_vsigma_rho_dx[p] +
                                                    mgd->bf_derivative_yy[pN_i] * weighted_vsigma_rho_dy[p] +
                                                    mgd->bf_derivative_yz[pN_i] * weighted_vsigma_rho_dz[p];

                mgd->bf_v_dz[pN_i] = mgd->bf_derivative_z[pN_i] * weighted_vrho[p] +
                                                    mgd->bf_derivative_xz[pN_i] * weighted_vsigma_rho_dx[p] +
                                                    mgd->bf_derivative_yz[pN_i] * weighted_vsigma_rho_dy[p] +
                                                    mgd->bf_derivative_zz[pN_i] * weighted_vsigma_rho_dz[p];
            }
        }

        einsum_mn_mp__np(mgd->bf_v_dx, mgd->bf_values, NxN, mgd->grid_size, N, N);
        mat_add(mgd->VXC_x, NxN, mgd->VXC_x, N, N);
        einsum_mn_mp__np(mgd->bf_v_dy, mgd->bf_values, NxN, mgd->grid_size, N, N);
        mat_add(mgd->VXC_y, NxN, mgd->VXC_y, N, N);
        einsum_mn_mp__np(mgd->bf_v_dz, mgd->bf_values, NxN, mgd->grid_size, N, N);
        mat_add(mgd->VXC_z, NxN, mgd->VXC_z, N, N);
        */
        /* derivatives wrt nuclear coordinates end */

        if (mgd->xc_type == XC_TYPE_MGGA)
        {
            f64 *weighted_vtau = Mx1;
            mat_add(mgd->vtau_x, mgd->vtau_c, weighted_vtau, mgd->grid_size, 1);
            mat_multiply(mgd->weights, weighted_vtau, weighted_vtau, mgd->grid_size, 1);
            mat_scalar_multiply(weighted_vtau, weighted_vtau, mgd->grid_size, 1, 0.25);

            for (u64 i = 0; i < mgd->grid_size; ++i)
            {
                f64 value = weighted_vtau[i];
                u64 iN = i * N;
                for (u64 j = 0; j < N; ++j)
                {
                    MxN[iN + j] = value * mgd->bf_derivative_x[iN + j];
                }
            }
            einsum_mn_mp__np_parallel(mgd->bf_derivative_x, MxN, NxN, mgd->grid_size, N, N, scf_ctx->tp_ctx);
            mat_add(XC, NxN, XC, N, N);

            /* derivatives wrt nuclear coordinates begin */
            /*
            einsum_mn_mp__np(mgd->bf_derivative_xx, MxN, NxN, mgd->grid_size, N, N); // partial_{xx}
            mat_add(mgd->VXC_x, NxN, mgd->VXC_x, N, N);
            einsum_mn_mp__np(mgd->bf_derivative_xy, MxN, NxN, mgd->grid_size, N, N); // partial_{yx}
            mat_add(mgd->VXC_y, NxN, mgd->VXC_y, N, N);
            einsum_mn_mp__np(mgd->bf_derivative_xz, MxN, NxN, mgd->grid_size, N, N); // partial_{zx}
            mat_add(mgd->VXC_z, NxN, mgd->VXC_z, N, N);

            for (u64 i = 0; i < mgd->grid_size; ++i)
            {
                f64 value = weighted_vtau[i];
                u64 iN = i * N;
                for (u64 j = 0; j < N; ++j)
                {
                    u64 iN_j = iN + j;
                    mgd->bf_v_dx[iN_j] = value * mgd->bf_derivative_xx[iN_j]; // partial_{xx}
                    mgd->bf_v_dy[iN_j] = value * mgd->bf_derivative_xy[iN_j]; // partial_{yx}
                    mgd->bf_v_dz[iN_j] = value * mgd->bf_derivative_xz[iN_j]; // partial_{zx}
                }
            }
            einsum_mn_mp__np(mgd->bf_v_dx, mgd->bf_derivative_x, NxN, mgd->grid_size, N, N);
            mat_add(mgd->VXC_x, NxN, mgd->VXC_x, N, N);
            einsum_mn_mp__np(mgd->bf_v_dy, mgd->bf_derivative_x, NxN, mgd->grid_size, N, N);
            mat_add(mgd->VXC_y, NxN, mgd->VXC_y, N, N);
            einsum_mn_mp__np(mgd->bf_v_dz, mgd->bf_derivative_x, NxN, mgd->grid_size, N, N);
            mat_add(mgd->VXC_z, NxN, mgd->VXC_z, N, N);
            */
            /* derivatives wrt nuclear coordinates end */

            for (u64 i = 0; i < mgd->grid_size; ++i)
            {
                f64 value = weighted_vtau[i];
                u64 iN = i * N;
                for (u64 j = 0; j < N; ++j)
                {
                    MxN[iN + j] = value * mgd->bf_derivative_y[iN + j];
                }
            }
            einsum_mn_mp__np_parallel(mgd->bf_derivative_y, MxN, NxN, mgd->grid_size, N, N, scf_ctx->tp_ctx);
            mat_add(XC, NxN, XC, N, N);

            /* derivatives wrt nuclear coordinates begin */
            /*
            einsum_mn_mp__np(mgd->bf_derivative_xy, MxN, NxN, mgd->grid_size, N, N); // partial_{xy}
            mat_add(mgd->VXC_x, NxN, mgd->VXC_x, N, N);
            einsum_mn_mp__np(mgd->bf_derivative_yy, MxN, NxN, mgd->grid_size, N, N); // partial_{yy}
            mat_add(mgd->VXC_y, NxN, mgd->VXC_y, N, N);
            einsum_mn_mp__np(mgd->bf_derivative_yz, MxN, NxN, mgd->grid_size, N, N); // partial_{zy}
            mat_add(mgd->VXC_z, NxN, mgd->VXC_z, N, N);

            for (u64 i = 0; i < mgd->grid_size; ++i)
            {
                f64 value = weighted_vtau[i];
                u64 iN = i * N;
                for (u64 j = 0; j < N; ++j)
                {
                    u64 iN_j = iN + j;
                    mgd->bf_v_dx[iN_j] = value * mgd->bf_derivative_xy[iN_j]; // partial_{xy}
                    mgd->bf_v_dy[iN_j] = value * mgd->bf_derivative_yy[iN_j]; // partial_{yy}
                    mgd->bf_v_dz[iN_j] = value * mgd->bf_derivative_yz[iN_j]; // partial_{zy}
                }
            }
            einsum_mn_mp__np(mgd->bf_v_dx, mgd->bf_derivative_y, NxN, mgd->grid_size, N, N);
            mat_add(mgd->VXC_x, NxN, mgd->VXC_x, N, N);
            einsum_mn_mp__np(mgd->bf_v_dy, mgd->bf_derivative_y, NxN, mgd->grid_size, N, N);
            mat_add(mgd->VXC_y, NxN, mgd->VXC_y, N, N);
            einsum_mn_mp__np(mgd->bf_v_dz, mgd->bf_derivative_y, NxN, mgd->grid_size, N, N);
            mat_add(mgd->VXC_z, NxN, mgd->VXC_z, N, N);
            */
            /* derivatives wrt nuclear coordinates end */

            for (u64 i = 0; i < mgd->grid_size; ++i)
            {
                f64 value = weighted_vtau[i];
                u64 iN = i * N;
                for (u64 j = 0; j < N; ++j)
                {
                    MxN[iN + j] = value * mgd->bf_derivative_z[iN + j];
                }
            }
            einsum_mn_mp__np_parallel(mgd->bf_derivative_z, MxN, NxN, mgd->grid_size, N, N, scf_ctx->tp_ctx);
            mat_add(XC, NxN, XC, N, N);

            /* derivatives wrt nuclear coordinates begin */
            /*
            einsum_mn_mp__np(mgd->bf_derivative_xz, MxN, NxN, mgd->grid_size, N, N); // partial_{xz}
            mat_add(mgd->VXC_x, NxN, mgd->VXC_x, N, N);
            einsum_mn_mp__np(mgd->bf_derivative_yz, MxN, NxN, mgd->grid_size, N, N); // partial_{yz}
            mat_add(mgd->VXC_y, NxN, mgd->VXC_y, N, N);
            einsum_mn_mp__np(mgd->bf_derivative_zz, MxN, NxN, mgd->grid_size, N, N); // partial_{zz}
            mat_add(mgd->VXC_z, NxN, mgd->VXC_z, N, N);

            for (u64 i = 0; i < mgd->grid_size; ++i)
            {
                f64 value = weighted_vtau[i];
                u64 iN = i * N;
                for (u64 j = 0; j < N; ++j)
                {
                    u64 iN_j = iN + j;
                    mgd->bf_v_dx[iN_j] = value * mgd->bf_derivative_xz[iN_j]; // partial_{xz}
                    mgd->bf_v_dy[iN_j] = value * mgd->bf_derivative_yz[iN_j]; // partial_{yz}
                    mgd->bf_v_dz[iN_j] = value * mgd->bf_derivative_zz[iN_j]; // partial_{zz}
                }
            }
            einsum_mn_mp__np(mgd->bf_v_dx, mgd->bf_derivative_z, NxN, mgd->grid_size, N, N);
            mat_add(mgd->VXC_x, NxN, mgd->VXC_x, N, N);
            einsum_mn_mp__np(mgd->bf_v_dy, mgd->bf_derivative_z, NxN, mgd->grid_size, N, N);
            mat_add(mgd->VXC_y, NxN, mgd->VXC_y, N, N);
            einsum_mn_mp__np(mgd->bf_v_dz, mgd->bf_derivative_z, NxN, mgd->grid_size, N, N);
            mat_add(mgd->VXC_z, NxN, mgd->VXC_z, N, N);
            */
            /* derivatives wrt nuclear coordinates end */
        }
    }

    /*
     * In theory, XC + conjugate(XC).T
     * For real matrix, just XC + XC.T
     */
    mat_add_A_AT(XC, NxN, N, N);
    memcpy(XC, NxN, N * N * sizeof(f64));

    /* derivatives wrt nuclear coordinates begin */
    /*
    mat_scalar_multiply(mgd->VXC_x, mgd->VXC_x, N, N, -1.0);
    mat_scalar_multiply(mgd->VXC_y, mgd->VXC_y, N, N, -1.0);
    mat_scalar_multiply(mgd->VXC_z, mgd->VXC_z, N, N, -1.0);
    */
    /* derivatives wrt nuclear coordinates end */
}

void calc_xc_gradients(struct molecular_grid_desc *mgd)
{
    struct scf_context *scf_ctx = mgd->scf_ctx;
    u64 N = scf_ctx->n_basis_funcs;

    /* output variable */
    f64 *NxN = mgd->NxN;
    f64 *bf_v = mgd->bf_v;
    f64 *weighted_vrho = mgd->weighted_vrho;
    f64 *MxN = mgd->MxN;
    f64 *Mx1 = mgd->Mx1;

    mat_add(mgd->vrho_x, mgd->vrho_c, Mx1, mgd->grid_size, 1);
    mat_multiply(mgd->weights, Mx1, weighted_vrho, mgd->grid_size, 1);
    mat_scalar_multiply(weighted_vrho, weighted_vrho, mgd->grid_size, 1, 0.5);

    if (mgd->xc_type == XC_TYPE_LDA)
    {
        /*
        for (u64 p = 0; p < mgd->grid_size; ++p)
        {
            u64 pN = p * N;
            for (u64 i = 0; i < N; ++i)
            {
                u64 pN_i = pN + i;
                bf_v[pN_i] = mgd->bf_values[pN_i] * weighted_vrho[p];
            }
        }
        einsum_mn_mp__np(mgd->bf_values, bf_v, XC, mgd->grid_size, N, N);
        */

        /* derivatives wrt nuclear coordinates begin */
        /*
        einsum_mn_mp__np(mgd->bf_derivative_x, bf_v, mgd->VXC_x, mgd->grid_size, N, N);
        einsum_mn_mp__np(mgd->bf_derivative_y, bf_v, mgd->VXC_y, mgd->grid_size, N, N);
        einsum_mn_mp__np(mgd->bf_derivative_z, bf_v, mgd->VXC_z, mgd->grid_size, N, N);
        for (u64 p = 0; p < mgd->grid_size; ++p)
        {
            u64 pN = p * N;
            for (u64 i = 0; i < N; ++i)
            {
                u64 pN_i = pN + i;
                mgd->bf_v_dx[pN_i] = mgd->bf_derivative_x[pN_i] * weighted_vrho[p];
                mgd->bf_v_dy[pN_i] = mgd->bf_derivative_y[pN_i] * weighted_vrho[p];
                mgd->bf_v_dz[pN_i] = mgd->bf_derivative_z[pN_i] * weighted_vrho[p];
            }
        }
        einsum_mn_mp__np(mgd->bf_v_dx, mgd->bf_values, NxN, mgd->grid_size, N, N);
        mat_add(mgd->VXC_x, NxN, mgd->VXC_x, N, N);
        einsum_mn_mp__np(mgd->bf_v_dy, mgd->bf_values, NxN, mgd->grid_size, N, N);
        mat_add(mgd->VXC_y, NxN, mgd->VXC_y, N, N);
        einsum_mn_mp__np(mgd->bf_v_dz, mgd->bf_values, NxN, mgd->grid_size, N, N);
        mat_add(mgd->VXC_z, NxN, mgd->VXC_z, N, N);
        */
        /* derivatives wrt nuclear coordinates end */

        // For the LDA case, we adopt the following alternative implementation
        //einsum_mn_mp_m__np(mgd->bf_values, mgd->bf_values, weighted_vrho, XC, mgd->grid_size, N, N);

        /* derivatives wrt nuclear coordinates begin */
        einsum_mn_mp_m__np(mgd->bf_derivative_x, mgd->bf_values, weighted_vrho, mgd->VXC_x, mgd->grid_size, N, N);
        einsum_mn_mp_m__np(mgd->bf_derivative_y, mgd->bf_values, weighted_vrho, mgd->VXC_y, mgd->grid_size, N, N);
        einsum_mn_mp_m__np(mgd->bf_derivative_z, mgd->bf_values, weighted_vrho, mgd->VXC_z, mgd->grid_size, N, N);

        mat_scalar_multiply(mgd->VXC_x, mgd->VXC_x, N, N, 2.0);
        mat_scalar_multiply(mgd->VXC_y, mgd->VXC_y, N, N, 2.0);
        mat_scalar_multiply(mgd->VXC_z, mgd->VXC_z, N, N, 2.0);
        /* derivatives wrt nuclear coordinates end */
    }

    if (mgd->xc_type == XC_TYPE_GGA || mgd->xc_type == XC_TYPE_MGGA)
    {
        f64 *weighted_vsigma_rho_dx = mgd->weighted_vsigma_rho_dx;
        f64 *weighted_vsigma_rho_dy = mgd->weighted_vsigma_rho_dy;
        f64 *weighted_vsigma_rho_dz = mgd->weighted_vsigma_rho_dz;

        /* Mx1 = v_sigma_x + vsigma_c */
        mat_add(mgd->vsigma_x, mgd->vsigma_c, Mx1, mgd->grid_size, 1);

        mat_multiply(mgd->weights, Mx1, weighted_vsigma_rho_dx, mgd->grid_size, 1);
        mat_multiply(weighted_vsigma_rho_dx, mgd->density_derivative_x, weighted_vsigma_rho_dx, mgd->grid_size, 1);
        mat_scalar_multiply(weighted_vsigma_rho_dx, weighted_vsigma_rho_dx, mgd->grid_size, 1, 2.0);

        mat_multiply(mgd->weights, Mx1, weighted_vsigma_rho_dy, mgd->grid_size, 1);
        mat_multiply(weighted_vsigma_rho_dy, mgd->density_derivative_y, weighted_vsigma_rho_dy, mgd->grid_size, 1);
        mat_scalar_multiply(weighted_vsigma_rho_dy, weighted_vsigma_rho_dy, mgd->grid_size, 1, 2.0);

        mat_multiply(mgd->weights, Mx1, weighted_vsigma_rho_dz, mgd->grid_size, 1);
        mat_multiply(weighted_vsigma_rho_dz, mgd->density_derivative_z, weighted_vsigma_rho_dz, mgd->grid_size, 1);
        mat_scalar_multiply(weighted_vsigma_rho_dz, weighted_vsigma_rho_dz, mgd->grid_size, 1, 2.0);

        for (u64 p = 0; p < mgd->grid_size; ++p)
        {
            u64 pN = p * N;
            for (u64 i = 0; i < N; ++i)
            {
                u64 pN_i = pN + i;
                bf_v[pN_i] = mgd->bf_values[pN_i] * weighted_vrho[p] + mgd->bf_derivative_x[pN_i] * weighted_vsigma_rho_dx[p] + mgd->bf_derivative_y[pN_i] * weighted_vsigma_rho_dy[p] + mgd->bf_derivative_z[pN_i] * weighted_vsigma_rho_dz[p];
            }
        }

        //einsum_mn_mp__np(mgd->bf_values, bf_v, XC, mgd->grid_size, N, N);

        /* derivatives wrt nuclear coordinates begin */
        einsum_mn_mp__np_parallel(mgd->bf_derivative_x, bf_v, mgd->VXC_x, mgd->grid_size, N, N, scf_ctx->tp_ctx);
        einsum_mn_mp__np_parallel(mgd->bf_derivative_y, bf_v, mgd->VXC_y, mgd->grid_size, N, N, scf_ctx->tp_ctx);
        einsum_mn_mp__np_parallel(mgd->bf_derivative_z, bf_v, mgd->VXC_z, mgd->grid_size, N, N, scf_ctx->tp_ctx);

        for (u64 p = 0; p < mgd->grid_size; ++p)
        {
            u64 pN = p * N;
            for (u64 i = 0; i < N; ++i)
            {
                u64 pN_i = pN + i;
                mgd->bf_v_dx[pN_i] = mgd->bf_derivative_x[pN_i] * weighted_vrho[p] +
                                                    mgd->bf_derivative_xx[pN_i] * weighted_vsigma_rho_dx[p] +
                                                    mgd->bf_derivative_xy[pN_i] * weighted_vsigma_rho_dy[p] +
                                                    mgd->bf_derivative_xz[pN_i] * weighted_vsigma_rho_dz[p];

                mgd->bf_v_dy[pN_i] = mgd->bf_derivative_y[pN_i] * weighted_vrho[p] +
                                                    mgd->bf_derivative_xy[pN_i] * weighted_vsigma_rho_dx[p] +
                                                    mgd->bf_derivative_yy[pN_i] * weighted_vsigma_rho_dy[p] +
                                                    mgd->bf_derivative_yz[pN_i] * weighted_vsigma_rho_dz[p];

                mgd->bf_v_dz[pN_i] = mgd->bf_derivative_z[pN_i] * weighted_vrho[p] +
                                                    mgd->bf_derivative_xz[pN_i] * weighted_vsigma_rho_dx[p] +
                                                    mgd->bf_derivative_yz[pN_i] * weighted_vsigma_rho_dy[p] +
                                                    mgd->bf_derivative_zz[pN_i] * weighted_vsigma_rho_dz[p];
            }
        }

        einsum_mn_mp__np_parallel(mgd->bf_v_dx, mgd->bf_values, NxN, mgd->grid_size, N, N, scf_ctx->tp_ctx);
        mat_add(mgd->VXC_x, NxN, mgd->VXC_x, N, N);
        einsum_mn_mp__np_parallel(mgd->bf_v_dy, mgd->bf_values, NxN, mgd->grid_size, N, N, scf_ctx->tp_ctx);
        mat_add(mgd->VXC_y, NxN, mgd->VXC_y, N, N);
        einsum_mn_mp__np_parallel(mgd->bf_v_dz, mgd->bf_values, NxN, mgd->grid_size, N, N, scf_ctx->tp_ctx);
        mat_add(mgd->VXC_z, NxN, mgd->VXC_z, N, N);
        /* derivatives wrt nuclear coordinates end */

        if (mgd->xc_type == XC_TYPE_MGGA)
        {
            f64 *weighted_vtau = Mx1;
            mat_add(mgd->vtau_x, mgd->vtau_c, weighted_vtau, mgd->grid_size, 1);
            mat_multiply(mgd->weights, weighted_vtau, weighted_vtau, mgd->grid_size, 1);
            mat_scalar_multiply(weighted_vtau, weighted_vtau, mgd->grid_size, 1, 0.25);

            for (u64 i = 0; i < mgd->grid_size; ++i)
            {
                f64 value = weighted_vtau[i];
                u64 iN = i * N;
                for (u64 j = 0; j < N; ++j)
                {
                    MxN[iN + j] = value * mgd->bf_derivative_x[iN + j];
                }
            }
            //einsum_mn_mp__np(mgd->bf_derivative_x, MxN, NxN, mgd->grid_size, N, N);
            //mat_add(XC, NxN, XC, N, N);

            /* derivatives wrt nuclear coordinates begin */
            einsum_mn_mp__np_parallel(mgd->bf_derivative_xx, MxN, NxN, mgd->grid_size, N, N, scf_ctx->tp_ctx); // partial_{xx}
            mat_add(mgd->VXC_x, NxN, mgd->VXC_x, N, N);
            einsum_mn_mp__np_parallel(mgd->bf_derivative_xy, MxN, NxN, mgd->grid_size, N, N, scf_ctx->tp_ctx); // partial_{yx}
            mat_add(mgd->VXC_y, NxN, mgd->VXC_y, N, N);
            einsum_mn_mp__np_parallel(mgd->bf_derivative_xz, MxN, NxN, mgd->grid_size, N, N, scf_ctx->tp_ctx); // partial_{zx}
            mat_add(mgd->VXC_z, NxN, mgd->VXC_z, N, N);

            for (u64 i = 0; i < mgd->grid_size; ++i)
            {
                f64 value = weighted_vtau[i];
                u64 iN = i * N;
                for (u64 j = 0; j < N; ++j)
                {
                    u64 iN_j = iN + j;
                    mgd->bf_v_dx[iN_j] = value * mgd->bf_derivative_xx[iN_j]; // partial_{xx}
                    mgd->bf_v_dy[iN_j] = value * mgd->bf_derivative_xy[iN_j]; // partial_{yx}
                    mgd->bf_v_dz[iN_j] = value * mgd->bf_derivative_xz[iN_j]; // partial_{zx}
                }
            }
            einsum_mn_mp__np_parallel(mgd->bf_v_dx, mgd->bf_derivative_x, NxN, mgd->grid_size, N, N, scf_ctx->tp_ctx);
            mat_add(mgd->VXC_x, NxN, mgd->VXC_x, N, N);
            einsum_mn_mp__np_parallel(mgd->bf_v_dy, mgd->bf_derivative_x, NxN, mgd->grid_size, N, N, scf_ctx->tp_ctx);
            mat_add(mgd->VXC_y, NxN, mgd->VXC_y, N, N);
            einsum_mn_mp__np_parallel(mgd->bf_v_dz, mgd->bf_derivative_x, NxN, mgd->grid_size, N, N, scf_ctx->tp_ctx);
            mat_add(mgd->VXC_z, NxN, mgd->VXC_z, N, N);
            /* derivatives wrt nuclear coordinates end */

            for (u64 i = 0; i < mgd->grid_size; ++i)
            {
                f64 value = weighted_vtau[i];
                u64 iN = i * N;
                for (u64 j = 0; j < N; ++j)
                {
                    MxN[iN + j] = value * mgd->bf_derivative_y[iN + j];
                }
            }
            //einsum_mn_mp__np(mgd->bf_derivative_y, MxN, NxN, mgd->grid_size, N, N);
            //mat_add(XC, NxN, XC, N, N);

            /* derivatives wrt nuclear coordinates begin */
            einsum_mn_mp__np_parallel(mgd->bf_derivative_xy, MxN, NxN, mgd->grid_size, N, N, scf_ctx->tp_ctx); // partial_{xy}
            mat_add(mgd->VXC_x, NxN, mgd->VXC_x, N, N);
            einsum_mn_mp__np_parallel(mgd->bf_derivative_yy, MxN, NxN, mgd->grid_size, N, N, scf_ctx->tp_ctx); // partial_{yy}
            mat_add(mgd->VXC_y, NxN, mgd->VXC_y, N, N);
            einsum_mn_mp__np_parallel(mgd->bf_derivative_yz, MxN, NxN, mgd->grid_size, N, N, scf_ctx->tp_ctx); // partial_{zy}
            mat_add(mgd->VXC_z, NxN, mgd->VXC_z, N, N);

            for (u64 i = 0; i < mgd->grid_size; ++i)
            {
                f64 value = weighted_vtau[i];
                u64 iN = i * N;
                for (u64 j = 0; j < N; ++j)
                {
                    u64 iN_j = iN + j;
                    mgd->bf_v_dx[iN_j] = value * mgd->bf_derivative_xy[iN_j]; // partial_{xy}
                    mgd->bf_v_dy[iN_j] = value * mgd->bf_derivative_yy[iN_j]; // partial_{yy}
                    mgd->bf_v_dz[iN_j] = value * mgd->bf_derivative_yz[iN_j]; // partial_{zy}
                }
            }
            einsum_mn_mp__np_parallel(mgd->bf_v_dx, mgd->bf_derivative_y, NxN, mgd->grid_size, N, N, scf_ctx->tp_ctx);
            mat_add(mgd->VXC_x, NxN, mgd->VXC_x, N, N);
            einsum_mn_mp__np_parallel(mgd->bf_v_dy, mgd->bf_derivative_y, NxN, mgd->grid_size, N, N, scf_ctx->tp_ctx);
            mat_add(mgd->VXC_y, NxN, mgd->VXC_y, N, N);
            einsum_mn_mp__np_parallel(mgd->bf_v_dz, mgd->bf_derivative_y, NxN, mgd->grid_size, N, N, scf_ctx->tp_ctx);
            mat_add(mgd->VXC_z, NxN, mgd->VXC_z, N, N);
            /* derivatives wrt nuclear coordinates end */

            for (u64 i = 0; i < mgd->grid_size; ++i)
            {
                f64 value = weighted_vtau[i];
                u64 iN = i * N;
                for (u64 j = 0; j < N; ++j)
                {
                    MxN[iN + j] = value * mgd->bf_derivative_z[iN + j];
                }
            }
            //einsum_mn_mp__np(mgd->bf_derivative_z, MxN, NxN, mgd->grid_size, N, N);
            //mat_add(XC, NxN, XC, N, N);

            /* derivatives wrt nuclear coordinates begin */
            einsum_mn_mp__np_parallel(mgd->bf_derivative_xz, MxN, NxN, mgd->grid_size, N, N, scf_ctx->tp_ctx); // partial_{xz}
            mat_add(mgd->VXC_x, NxN, mgd->VXC_x, N, N);
            einsum_mn_mp__np_parallel(mgd->bf_derivative_yz, MxN, NxN, mgd->grid_size, N, N, scf_ctx->tp_ctx); // partial_{yz}
            mat_add(mgd->VXC_y, NxN, mgd->VXC_y, N, N);
            einsum_mn_mp__np_parallel(mgd->bf_derivative_zz, MxN, NxN, mgd->grid_size, N, N, scf_ctx->tp_ctx); // partial_{zz}
            mat_add(mgd->VXC_z, NxN, mgd->VXC_z, N, N);

            for (u64 i = 0; i < mgd->grid_size; ++i)
            {
                f64 value = weighted_vtau[i];
                u64 iN = i * N;
                for (u64 j = 0; j < N; ++j)
                {
                    u64 iN_j = iN + j;
                    mgd->bf_v_dx[iN_j] = value * mgd->bf_derivative_xz[iN_j]; // partial_{xz}
                    mgd->bf_v_dy[iN_j] = value * mgd->bf_derivative_yz[iN_j]; // partial_{yz}
                    mgd->bf_v_dz[iN_j] = value * mgd->bf_derivative_zz[iN_j]; // partial_{zz}
                }
            }
            einsum_mn_mp__np_parallel(mgd->bf_v_dx, mgd->bf_derivative_z, NxN, mgd->grid_size, N, N, scf_ctx->tp_ctx);
            mat_add(mgd->VXC_x, NxN, mgd->VXC_x, N, N);
            einsum_mn_mp__np_parallel(mgd->bf_v_dy, mgd->bf_derivative_z, NxN, mgd->grid_size, N, N, scf_ctx->tp_ctx);
            mat_add(mgd->VXC_y, NxN, mgd->VXC_y, N, N);
            einsum_mn_mp__np_parallel(mgd->bf_v_dz, mgd->bf_derivative_z, NxN, mgd->grid_size, N, N, scf_ctx->tp_ctx);
            mat_add(mgd->VXC_z, NxN, mgd->VXC_z, N, N);
            /* derivatives wrt nuclear coordinates end */
        }
    }

    /* derivatives wrt nuclear coordinates begin */
    mat_scalar_multiply(mgd->VXC_x, mgd->VXC_x, N, N, -1.0);
    mat_scalar_multiply(mgd->VXC_y, mgd->VXC_y, N, N, -1.0);
    mat_scalar_multiply(mgd->VXC_z, mgd->VXC_z, N, N, -1.0);
    /* derivatives wrt nuclear coordinates end */
}
