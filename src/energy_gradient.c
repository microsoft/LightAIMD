/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <math.h>
#include <string.h>

#include "numeric_types.h"
#include "scf.h"
#include "dft.h"
#include "dft_matrices.h"
#include "molecular_grid.h"
#include "molecular_integral.h"
#include "math_util.h"
#include "einsum.h"
#include "mm.h"
#include "time_util.h"
#include "diagnostics.h"
#include "spinlock.h"

struct task_func_energy_dwrt_nuc_arg
{
    struct scf_context *ctx;
    struct molecular_grid_desc *mgd;
    struct vec3d *coord_n;
    u64 n_atoms;
    u64 n;
    u64 N;
    f64 hyb_coef;
};

static void vec3d_addto(f64 *a, f64 *b)
{
    b[0] += a[0];
    b[1] += a[1];
    b[2] += a[2];
}

static void vec3d_subtractfrom(f64 *a, f64 *b, f64 k)
{
    b[0] -= k * a[0];
    b[1] -= k * a[1];
    b[2] -= k * a[2];
}

struct task_func_eri_dwrt_nuc_arg
{
    struct scf_context *ctx;
    f64 *dF_x;
    f64 *dF_y;
    f64 *dF_z;
    u64 n;
    u64 i;
    u64 j;
    u64 k;
    u64 l;
    u64 i_j;
    u64 k_l;
    u64 ij_kl;
    f64 hyb_coef;
};

void task_func_eri_dwrt_nuc(void *p_arg)
{
    struct task_func_eri_dwrt_nuc_arg *arg = (struct task_func_eri_dwrt_nuc_arg *)p_arg;
    struct scf_context *ctx = arg->ctx;
    f64 *dF_x = arg->dF_x;
    f64 *dF_y = arg->dF_y;
    f64 *dF_z = arg->dF_z;
    u64 n = arg->n;
    u64 i = arg->i;
    u64 j = arg->j;
    u64 k = arg->k;
    u64 l = arg->l;
    u64 i_j = arg->i_j;
    u64 k_l = arg->k_l;
    u64 ij_kl = arg->ij_kl;
    f64 hyb_coef = arg->hyb_coef;

    volatile atomic_bool *L = ctx->LOCK;
    u64 N = ctx->n_basis_funcs;
    u64 iN = i * N;
    u64 iNj = iN + j;
    u64 iNk = iN + k;
    u64 jN = j * N;
    u64 jNk = jN + k;
    u64 kN = k * N;
    u64 kNj = kN + j;

    f64 value[] = {0.0, 0.0, 0.0};
    f64 xyz[] = {0.0, 0.0, 0.0};
    if (ctx->atom_bf_map[n * N + i])
    {
        cg_electron_repulsion_integral_dwrt_nuc(ctx->basis_funcs + i, ctx->basis_funcs + j,
                                                ctx->basis_funcs + k, ctx->basis_funcs + l,
                                                1, xyz);
        value[0] += xyz[0];
        value[1] += xyz[1];
        value[2] += xyz[2];
    }
    if (ctx->atom_bf_map[n * N + j])
    {
        cg_electron_repulsion_integral_dwrt_nuc(ctx->basis_funcs + i, ctx->basis_funcs + j,
                                                ctx->basis_funcs + k, ctx->basis_funcs + l,
                                                2, xyz);
        value[0] += xyz[0];
        value[1] += xyz[1];
        value[2] += xyz[2];
    }
    if (ctx->atom_bf_map[n * N + k])
    {
        cg_electron_repulsion_integral_dwrt_nuc(ctx->basis_funcs + i, ctx->basis_funcs + j,
                                                ctx->basis_funcs + k, ctx->basis_funcs + l,
                                                3, xyz);
        value[0] += xyz[0];
        value[1] += xyz[1];
        value[2] += xyz[2];
    }
    if (ctx->atom_bf_map[n * N + l])
    {
        cg_electron_repulsion_integral_dwrt_nuc(ctx->basis_funcs + i, ctx->basis_funcs + j,
                                                ctx->basis_funcs + k, ctx->basis_funcs + l,
                                                4, xyz);
        value[0] += xyz[0];
        value[1] += xyz[1];
        value[2] += xyz[2];
    }

    f64 prefactor = i_j * k_l * ij_kl;

    value[0] *= prefactor;
    value[1] *= prefactor;
    value[2] *= prefactor;

    /* Coulomb */
    spinlock_lock(L + iNj);
    dF_x[iNj] += value[0] * ctx->P[kN + l];
    spinlock_unlock(L + iNj);
    spinlock_lock(L + kN + l);
    dF_x[kN + l] += value[0] * ctx->P[iNj];
    spinlock_unlock(L + kN + l);

    /* Exchange */
    spinlock_lock(L + iNk);
    dF_x[iNk] -= value[0] * ctx->P[jN + l] * 0.25 * hyb_coef;
    spinlock_unlock(L + iNk);
    spinlock_lock(L + jN + l);
    dF_x[jN + l] -= value[0] * ctx->P[iNk] * 0.25 * hyb_coef;
    spinlock_unlock(L + jN + l);
    spinlock_lock(L + iN + l);
    dF_x[iN + l] -= value[0] * ctx->P[jNk] * 0.25 * hyb_coef;
    spinlock_unlock(L + iN + l);
    spinlock_lock(L + kNj);
    dF_x[kNj] -= value[0] * ctx->P[iN + l] * 0.25 * hyb_coef;
    spinlock_unlock(L + kNj);

    /* Coulomb */
    spinlock_lock(L + iNj);
    dF_y[iNj] += value[1] * ctx->P[kN + l];
    spinlock_unlock(L + iNj);
    spinlock_lock(L + kN + l);
    dF_y[kN + l] += value[1] * ctx->P[iNj];
    spinlock_unlock(L + kN + l);

    /* Exchange */
    spinlock_lock(L + iNk);
    dF_y[iNk] -= value[1] * ctx->P[jN + l] * 0.25 * hyb_coef;
    spinlock_unlock(L + iNk);
    spinlock_lock(L + jN + l);
    dF_y[jN + l] -= value[1] * ctx->P[iNk] * 0.25 * hyb_coef;
    spinlock_unlock(L + jN + l);
    spinlock_lock(L + iN + l);
    dF_y[iN + l] -= value[1] * ctx->P[jNk] * 0.25 * hyb_coef;
    spinlock_unlock(L + iN + l);
    spinlock_lock(L + kNj);
    dF_y[kNj] -= value[1] * ctx->P[iN + l] * 0.25 * hyb_coef;
    spinlock_unlock(L + kNj);

    /* Coulomb */
    spinlock_lock(L + iNj);
    dF_z[iNj] += value[2] * ctx->P[kN + l];
    spinlock_unlock(L + iNj);
    spinlock_lock(L + kN + l);
    dF_z[kN + l] += value[2] * ctx->P[iNj];
    spinlock_unlock(L + kN + l);

    /* Exchange */
    spinlock_lock(L + iNk);
    dF_z[iNk] -= value[2] * ctx->P[jN + l] * 0.25 * hyb_coef;
    spinlock_unlock(L + iNk);
    spinlock_lock(L + jN + l);
    dF_z[jN + l] -= value[2] * ctx->P[iNk] * 0.25 * hyb_coef;
    spinlock_unlock(L + jN + l);
    spinlock_lock(L + iN + l);
    dF_z[iN + l] -= value[2] * ctx->P[jNk] * 0.25 * hyb_coef;
    spinlock_unlock(L + iN + l);
    spinlock_lock(L + kNj);
    dF_z[kNj] -= value[2] * ctx->P[iN + l] * 0.25 * hyb_coef;
    spinlock_unlock(L + kNj);

    x_free(p_arg);
}

void task_func_energy_dwrt_nuc(void *p_arg)
{
    struct task_func_energy_dwrt_nuc_arg *arg = (struct task_func_energy_dwrt_nuc_arg *)p_arg;
    struct scf_context *ctx = arg->ctx;
    struct molecular_grid_desc *mgd = arg->mgd;
    struct vec3d *coord_n = arg->coord_n;
    u64 n_atoms = arg->n_atoms;
    u64 n = arg->n;
    u64 N = arg->N;
    u64 N2 = N * N;
    u64 N2_f64 = N2 * sizeof(f64);
    f64 hyb_coef = arg->hyb_coef;

    /* allocate the buffers for storing the derivatives */
    f64 *dS_x = x_malloc(N2_f64);
    f64 *dT_x = x_malloc(N2_f64);
    f64 *dV_x = x_malloc(N2_f64);
    f64 *dF_x = x_malloc(N2_f64);
    f64 *M1_x = x_malloc(N2_f64);
    f64 *M2_x = x_malloc(N2_f64);

    f64 *dS_y = x_malloc(N2_f64);
    f64 *dT_y = x_malloc(N2_f64);
    f64 *dV_y = x_malloc(N2_f64);
    f64 *dF_y = x_malloc(N2_f64);
    f64 *M1_y = x_malloc(N2_f64);
    f64 *M2_y = x_malloc(N2_f64);

    f64 *dS_z = x_malloc(N2_f64);
    f64 *dT_z = x_malloc(N2_f64);
    f64 *dV_z = x_malloc(N2_f64);
    f64 *dF_z = x_malloc(N2_f64);
    f64 *M1_z = x_malloc(N2_f64);
    f64 *M2_z = x_malloc(N2_f64);

    f64 xyz[] = {0.0, 0.0, 0.0};

    for (u64 i = 0; i < N; ++i)
    {
        u64 iN = i * N;
        for (u64 j = 0; j < i + 1; ++j)
        {
            f64 ds[] = {0.0, 0.0, 0.0};
            f64 dt[] = {0.0, 0.0, 0.0};
            f64 dv[] = {0.0, 0.0, 0.0};

            if (ctx->atom_bf_map[n * N + i])
            {
                cg_overlap_integral_dwrt_nuc(ctx->basis_funcs + i, ctx->basis_funcs + j, 1, xyz);
                vec3d_addto(xyz, ds);
                cg_kinetic_integral_dwrt_nuc(ctx->basis_funcs + i, ctx->basis_funcs + j, 1, xyz);
                vec3d_addto(xyz, dt);
            }

            if (ctx->atom_bf_map[n * N + j])
            {
                cg_overlap_integral_dwrt_nuc(ctx->basis_funcs + i, ctx->basis_funcs + j, 2, xyz);
                vec3d_addto(xyz, ds);
                cg_kinetic_integral_dwrt_nuc(ctx->basis_funcs + i, ctx->basis_funcs + j, 2, xyz);
                vec3d_addto(xyz, dt);
            }

            // Hellmann-Feynman force
            cg_nuclear_attraction_integral_dwrt_nuc(ctx->basis_funcs + i, ctx->basis_funcs + j, coord_n->x, coord_n->y, coord_n->z, xyz);
            vec3d_subtractfrom(xyz, dv, ctx->mol->atomic_nums[n]);
            for (u64 m = 0; m < n_atoms; ++m)
            {
                struct vec3d *coord_m = ctx->mol->coords + m;

                /*
                 * Derivatives with respect to the orbital centers
                 */
                if (ctx->atom_bf_map[n * N + i])
                {
                    cg_nuclear_attraction_integral_dwrt_orb_center(ctx->basis_funcs + i, ctx->basis_funcs + j, coord_m->x, coord_m->y, coord_m->z, 1, xyz);
                    vec3d_subtractfrom(xyz, dv, ctx->mol->atomic_nums[m]);
                }
                if (ctx->atom_bf_map[n * N + j])
                {
                    cg_nuclear_attraction_integral_dwrt_orb_center(ctx->basis_funcs + i, ctx->basis_funcs + j, coord_m->x, coord_m->y, coord_m->z, 2, xyz);
                    vec3d_subtractfrom(xyz, dv, ctx->mol->atomic_nums[m]);
                }
            }

            dS_x[iN + j] = ds[0];
            dS_x[j * N + i] = ds[0];
            dT_x[iN + j] = dt[0];
            dT_x[j * N + i] = dt[0];
            dV_x[iN + j] = dv[0];
            dV_x[j * N + i] = dv[0];

            dS_y[iN + j] = ds[1];
            dS_y[j * N + i] = ds[1];
            dT_y[iN + j] = dt[1];
            dT_y[j * N + i] = dt[1];
            dV_y[iN + j] = dv[1];
            dV_y[j * N + i] = dv[1];

            dS_z[iN + j] = ds[2];
            dS_z[j * N + i] = ds[2];
            dT_z[iN + j] = dt[2];
            dT_z[j * N + i] = dt[2];
            dV_z[iN + j] = dv[2];
            dV_z[j * N + i] = dv[2];
        }
    }

    f64 d_nuclear_repulsion[] = {0.0, 0.0, 0.0};
    for (u64 m = 0; m < n_atoms; ++m)
    {
        /*
         * D[Z1 Z2 / Sqrt[(x-x0)^2 + (y-y0)^2 + (z-z0)^2], x] =
         * -(((x-x0) Z1 Z2)/((x-x0)^2+(y-y0)^2+(z-z0)^2)^(3/2))
         */

        struct vec3d *coord_m = ctx->mol->coords + m;

        f64 dx = coord_n->x - coord_m->x;
        f64 dy = coord_n->y - coord_m->y;
        f64 dz = coord_n->z - coord_m->z;

        f64 rab = sqrt(dx * dx + dy * dy + dz * dz);

        if (rab > 1e-10)
        {
            u64 Za = ctx->mol->atomic_nums[n];
            u64 Zb = ctx->mol->atomic_nums[m];
            f64 Zab = Za * Zb / (rab * rab * rab);

            d_nuclear_repulsion[0] -= dx * Zab;
            d_nuclear_repulsion[1] -= dy * Zab;
            d_nuclear_repulsion[2] -= dz * Zab;
        }
    }

    memset(dF_x, 0, N2_f64);
    memset(dF_y, 0, N2_f64);
    memset(dF_z, 0, N2_f64);
    struct threadpool_context *alt_tp_ctx = threadpool_initialize(0, 4096);
    for (u64 i = 0; i < N; ++i)
    {
        u64 iN = i * N;
        for (u64 j = 0; j <= i; ++j)
        {
            u64 jN = j * N;
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
                        struct task_func_eri_dwrt_nuc_arg *arg = x_malloc(sizeof(struct task_func_eri_dwrt_nuc_arg));
                        arg->ctx = ctx;
                        arg->dF_x = dF_x;
                        arg->dF_y = dF_y;
                        arg->dF_z = dF_z;
                        arg->n = n;
                        arg->i = i;
                        arg->j = j;
                        arg->k = k;
                        arg->l = l;
                        arg->i_j = i_j;
                        arg->k_l = k_l;
                        arg->ij_kl = ij_kl;
                        arg->hyb_coef = hyb_coef;
                        threadpool_add_task(alt_tp_ctx, (iN * N * N + jN * N + kN + l) % (alt_tp_ctx->n_workers), task_func_eri_dwrt_nuc, arg);
                    }
                }
            }
        }
    }
    threadpool_wait_job_done(alt_tp_ctx);
    threadpool_finalize(alt_tp_ctx);

    f64 force[] = {0.0, 0.0, 0.0};

    /* x */
    mat_add(dT_x, dV_x, M1_x, N, N); // M1: dH

    transpose(dF_x, M2_x, N, N);
    mat_add(dF_x, M2_x, M2_x, N, N);
    mat_scalar_multiply(M2_x, dF_x, N, N, 0.25);

    mat_add(M1_x, dF_x, dF_x, N, N);
    mat_add(M1_x, dF_x, dF_x, N, N);

    mat_multiply(tag_transpose(ctx->P), dF_x, dF_x, N, N);
    force[0] = 0.5 * matsum(dF_x, N, N);

    /* y */
    mat_add(dT_y, dV_y, M1_y, N, N); // M1: dH

    transpose(dF_y, M2_y, N, N);
    mat_add(dF_y, M2_y, M2_y, N, N);
    mat_scalar_multiply(M2_y, dF_y, N, N, 0.25);

    mat_add(M1_y, dF_y, dF_y, N, N);
    mat_add(M1_y, dF_y, dF_y, N, N);

    mat_multiply(tag_transpose(ctx->P), dF_y, dF_y, N, N);
    force[1] = 0.5 * matsum(dF_y, N, N);

    /* z */
    mat_add(dT_z, dV_z, M1_z, N, N); // M1: dH

    transpose(dF_z, M2_z, N, N);
    mat_add(dF_z, M2_z, M2_z, N, N);
    mat_scalar_multiply(M2_z, dF_z, N, N, 0.25);

    mat_add(M1_z, dF_z, dF_z, N, N);
    mat_add(M1_z, dF_z, dF_z, N, N);

    mat_multiply(tag_transpose(ctx->P), dF_z, dF_z, N, N);
    force[2] = 0.5 * matsum(dF_z, N, N);

    if (mgd)
    {
        f64 xc_force[] = {0.0, 0.0, 0.0};
        for (u64 i = 0; i < N; ++i)
        {
            if (ctx->atom_bf_map[n * N + i])
            {
                u64 iN = i * N;
                for (u64 j = 0; j < N; ++j)
                {
                    xc_force[0] += mgd->VXC_x[iN + j] * ctx->P[iN + j] * 2.0;
                    xc_force[1] += mgd->VXC_y[iN + j] * ctx->P[iN + j] * 2.0;
                    xc_force[2] += mgd->VXC_z[iN + j] * ctx->P[iN + j] * 2.0;
                }
            }
        }
        force[0] += xc_force[0];
        force[1] += xc_force[1];
        force[2] += xc_force[2];
    }

    f64 *M1 = M1_x;
    f64 *M2 = M2_x;
    einsum_mn_np__mp(ctx->F, ctx->P, M1, N, N, N);
    einsum_mn_np__mp(ctx->P, M1, M2, N, N, N);

    force[0] -= 0.5 * einsum_mn_nm(dS_x, M2, N, N);
    force[0] += d_nuclear_repulsion[0];
    ctx->mol->forces[n].x = -force[0];

    force[1] -= 0.5 * einsum_mn_nm(dS_y, M2, N, N);
    force[1] += d_nuclear_repulsion[1];
    ctx->mol->forces[n].y = -force[1];

    force[2] -= 0.5 * einsum_mn_nm(dS_z, M2, N, N);
    force[2] += d_nuclear_repulsion[2];
    ctx->mol->forces[n].z = -force[2];

    x_free(dS_x);
    x_free(dT_x);
    x_free(dV_x);
    x_free(dF_x);
    x_free(M1_x);
    x_free(M2_x);

    x_free(dS_y);
    x_free(dT_y);
    x_free(dV_y);
    x_free(dF_y);
    x_free(M1_y);
    x_free(M2_y);

    x_free(dS_z);
    x_free(dT_z);
    x_free(dV_z);
    x_free(dF_z);
    x_free(M1_z);
    x_free(M2_z);

    x_free(p_arg);
}

void energy_dwrt_nuc(struct scf_context *ctx)
{
    struct timespec time_start, time_end;
    get_wall_time(&time_start);

    f64 hyb_coef = 1.0;
    struct molecular_grid_desc *mgd = NULL;
    if (ctx->dft_ctx)
    {
        mgd = ctx->dft_ctx->mgd;
        calc_xc_gradients(mgd);
        hyb_coef = mgd->hyb_coef;
    }

    u64 n_atoms = ctx->mol->n_atoms;
    u64 N = ctx->n_basis_funcs;
    struct threadpool_context *tp_ctx = ctx->tp_ctx;

    for (u64 n = 0; n < n_atoms; ++n)
    {
        struct vec3d *coord_n = ctx->mol->coords + n;
        struct task_func_energy_dwrt_nuc_arg *arg = x_malloc(sizeof(struct task_func_energy_dwrt_nuc_arg));
        arg->ctx = ctx;
        arg->mgd = mgd;
        arg->coord_n = coord_n;
        arg->n_atoms = n_atoms;
        arg->n = n;
        arg->N = N;
        arg->hyb_coef = hyb_coef;
        threadpool_add_task(tp_ctx, n % (tp_ctx->n_workers), task_func_energy_dwrt_nuc, arg);
    }
    threadpool_wait_job_done(tp_ctx);

    get_wall_time(&time_end);
    console_printf(ctx->silent, "energy_dwrt_nuc took %.3f ms\n", diff_time_ms(&time_start, &time_end));
}
