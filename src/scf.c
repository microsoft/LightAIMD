/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "molecule.h"
#include "scf.h"
#include "cpp_bridge.h"
#include "basis_func.h"
#include "molecular_integral.h"
#include "math_util.h"
#include "time_util.h"
#include "soad.h"
#include "spinlock.h"
#include "diagnostics.h"
#include "mm.h"
#include "einsum.h"

/* define all the available density matrix intialization method */
const u64 DENSITY_INIT_SOAD = 1;
const u64 DENSITY_INIT_HCORE = 2;
const u64 DENSITY_INIT_USER_PROVIDED = 3;

void print_basis_func_struct(struct basis_func *bf)
{
    printf("l: %lu m: %lu n: %lu\n", bf->l, bf->m, bf->n);
    printf("n_exponents: %lu\n", bf->n_exponents);

    for (u64 i = 0; i < bf->n_exponents; ++i)
    {
        printf("exponents: %.10e\n", bf->exponents[i]);
        printf("coefficients: %.10e\n", bf->coefficients[i]);
        printf("primitive normalization factors: %.10e\n", bf->normalization_factors[i]);
    }

    printf("origin: (%.8e, %.8e, %.8e)\n", bf->x0, bf->y0, bf->z0);
    printf("\n");
}

void print_scf_context(struct scf_context *ctx)
{
    struct vec3d cc;
    center_of_charge(ctx->mol, &cc);
    printf("center of charge: (%.15f, %.15f, %.15f)\n", cc.x, cc.y, cc.z);
    printf("nuclear repulsion energy: %.15f\n", ctx->nuclear_repulsion_energy);

    u64 N = ctx->n_basis_funcs;

    printf("Total number of basis functions: %lu\n\n", N);
    for (u64 i = 0; i < N; ++i)
    {
        printf("basic function %lu\n", i);
        print_basis_func_struct(ctx->basis_funcs + i);
    }

    for (u64 i = 0; i < N; ++i)
    {
        printf("contracted_bf_normalization_factor: %.9f\n", ctx->basis_funcs[i].contracted_bf_normalization_factor);
    }

    if (!ctx->direct_scf)
    {
        for (u64 i = 0; i < N; ++i)
        {
            for (u64 j = 0; j < N; ++j)
            {
                for (u64 k = 0; k < N; ++k)
                {
                    for (u64 l = 0; l < N; ++l)
                    {
                        f64 val = ctx->TwoE[i * N * N * N + j * N * N + k * N + l];
                        if (val > 1.0)
                        {
                            printf("TwoE[%lu, %lu, %lu, %lu]: %.9f\n", i, j, k, l, val);
                        }
                    }
                }
            }
        }
    }

    f64 *P = ctx->P;
    printf("P:\n");
    f64 p_ = 0.0;
    for (u64 p = 0; p < N; ++p)
    {
        for (u64 q = 0; q < N; ++q)
        {
            printf("%lu-%lu: %f ", p, q, P[p * N + q]);
            p_ += P[p * N + q];
        }
        printf("\n");
    }
    printf("P.sum(): %.6f\n", p_);

    printf("SCF Energy: %.6f\n", ctx->energy);
}

static f64 calc_nuclear_repulsion_energy(struct molecule *mol)
{
    f64 nre = 0.0;
    for (u64 i = 0; i < mol->n_atoms; ++i)
    {
        for (u64 j = i + 1; j < mol->n_atoms; ++j)
        {
            nre += mol->atomic_nums[i] * mol->atomic_nums[j] / sqrt((mol->coords[i].x - mol->coords[j].x) * (mol->coords[i].x - mol->coords[j].x) + (mol->coords[i].y - mol->coords[j].y) * (mol->coords[i].y - mol->coords[j].y) + (mol->coords[i].z - mol->coords[j].z) * (mol->coords[i].z - mol->coords[j].z));
        }
    }
    return nre;
}

static void initialize_density_matrix_with_H_core(struct scf_context *ctx)
{
    u64 N = ctx->n_basis_funcs;
    generalized_eigh_veconly(ctx->H, ctx->S, ctx->C, N);

    u64 nocc = ctx->mol->n_electrons >> 1;
    matslice(ctx->C, ctx->COO, N, N, nocc);

    /*
     * In theory, we should use the conjugate transpose of COO,
     * for RHF here, COO is a real matrix, we just take its transpose
     * Ref: modern quantum chemistry (Szabo and Ostlund), eq 3.145
     */
    transpose(ctx->COO, ctx->COOT, N, nocc);

    /*
     * Calculating density matrix P from C
     * Note: in theory, we should do einsum_mn_np__mp(C_occ, C_occ_T) * 2.0
     * As we are going to use 0.5 * P in calculating the total HF energy,
     * here we just do einsum_mn_np__mp(C_occ, C_occ_T),
     * this effectively makes ctx->P == density_matrix * 0.5
     * Ref: modern quantum chemistry (Szabo and Ostlund), eq 3.145
     */
    einsum_mn_np__mp(ctx->COO, ctx->COOT, ctx->P, N, nocc, N);
}

static void build_basis_funcs(struct scf_context *ctx, char const *basis_set_filename)
{
    struct molecule *mol = ctx->mol;
    u64 *p_elements = mol_elements(mol);
    u64 n_elements = *p_elements;
    log_tm_println(ctx->silent, "Loading basis set %s\n", basis_set_filename);
    ctx->basis_funcs_buff = load_basis_set(basis_set_filename, n_elements, (p_elements + 1));
    x_free(p_elements);

    u64 *element2basisfuncs[128] = {0};

    u64 *p = (u64 *)ctx->basis_funcs_buff;
    ++p; // skip u64 n_elements = *p;
    for (u64 i = 0; i < n_elements; ++i)
    {
        u64 atomic_num = *p;
        ++p;

        element2basisfuncs[atomic_num] = p;

        u64 n_basis_funcs = *p;
        ++p;

        for (u64 j = 0; j < n_basis_funcs; ++j)
        {
            // u64 l = *p;
            ++p;
            // u64 m = *p;
            ++p;
            // u64 n = *p;
            ++p;

            u64 n_exponents = *p;
            ++p;
            for (u64 k = 0; k < n_exponents; ++k)
            {
                // double exponent = *((double *)p);
                ++p;
            }
            for (u64 k = 0; k < n_exponents; ++k)
            {
                // double coefficient = *((double *)p);
                ++p;
            }
        }
    }

    u64 N = 0;
    for (u64 i = 0; i < mol->n_atoms; ++i)
    {
        u64 *pbf = element2basisfuncs[mol->atomic_nums[i]];
        u64 n_basis_funcs = *pbf;
        N += n_basis_funcs;
    }

    ctx->n_basis_funcs = N;

    ctx->basis_funcs = x_calloc(N, sizeof(struct basis_func));
    ctx->atom_bf_map = x_calloc(ctx->mol->n_atoms * N, sizeof(u32));
    u64 bf_index = 0; // basis function index
    for (u64 i = 0; i < mol->n_atoms; ++i)
    {
        u64 *pbf = element2basisfuncs[mol->atomic_nums[i]];
        u64 n_basis_funcs = *pbf;
        ++pbf;

        for (u64 j = 0; j < n_basis_funcs; ++j)
        {
            struct basis_func *bf = ctx->basis_funcs + bf_index;
            ctx->atom_bf_map[i * N + bf_index] = 1;
            bf->l = *pbf;
            ++pbf;

            bf->m = *pbf;
            ++pbf;

            bf->n = *pbf;
            ++pbf;

            bf->n_exponents = *pbf;
            ++pbf;

            bf->exponents = (f64 *)pbf;
            pbf += bf->n_exponents;

            bf->coefficients = (f64 *)pbf;
            pbf += bf->n_exponents;

            bf->x0 = mol->coords[i].x;
            bf->y0 = mol->coords[i].y;
            bf->z0 = mol->coords[i].z;

            bf->normalization_factors = x_malloc(bf->n_exponents * sizeof(f64));
            for (u64 k = 0; k < bf->n_exponents; ++k)
            {
                bf->normalization_factors[k] = normalize_gaussian_primitive(bf->exponents[k], bf->l, bf->m, bf->n);
            }

            bf->contracted_bf_normalization_factor = normalize_contracted_gaussian_func(bf->n_exponents, bf->l, bf->m, bf->n, bf->exponents, bf->coefficients, bf->normalization_factors);

            for (u64 k = 0; k < bf->n_exponents; ++k)
            {
                bf->coefficients[k] *= bf->contracted_bf_normalization_factor;
            }

            ++bf_index;
        }
    }
}

void free_basis(struct scf_context *ctx)
{
    u64 N = ctx->n_basis_funcs;
    for (u64 i = 0; i < N; ++i)
    {
        struct basis_func *bf = ctx->basis_funcs + i;
        x_free(bf->normalization_factors);
    }

    x_free(ctx->basis_funcs);
    /* free the memory buffer containing basis funcs */
    x_free(ctx->basis_funcs_buff);
}

struct task_func_stv_arg
{
    struct scf_context *ctx;
    f64 *S;
    f64 *T;
    f64 *V;
    u64 i;
    u64 j;
};

static void task_func_stv(void *p_arg)
{
    struct task_func_stv_arg *arg = (struct task_func_stv_arg *)p_arg;
    struct scf_context *ctx = arg->ctx;
    f64 *S = arg->S;
    f64 *T = arg->T;
    f64 *V = arg->V;
    u64 i = arg->i;
    u64 j = arg->j;
    u64 N = ctx->n_basis_funcs;
    u64 Ni = N * i;
    struct molecule *mol = ctx->mol;

    /* S and T matrices are symmetric */
    f64 s = cg_overlap_integral(ctx->basis_funcs + i, ctx->basis_funcs + j);
    S[Ni + j] = s;
    S[N * j + i] = s;

    f64 t = cg_kinetic_integral(ctx->basis_funcs + i, ctx->basis_funcs + j);
    T[Ni + j] = t;
    T[N * j + i] = t;

    f64 v = 0.0;
    for (u64 k = 0; k < mol->n_atoms; ++k)
    {
        v -= mol->atomic_nums[k] * cg_nuclear_attraction_integral(ctx->basis_funcs + i, ctx->basis_funcs + j, mol->coords[k].x, mol->coords[k].y, mol->coords[k].z);
    }
    V[Ni + j] = v;
    V[N * j + i] = v;
    x_free(p_arg);
}

static void build_one_electron_integrals(struct scf_context *ctx)
{
    u64 N = ctx->n_basis_funcs;
    u64 N2 = N * N;
    u64 N2_f64 = N2 * sizeof(f64);

    /* Build one-electron integrals */
    log_tm_println(ctx->silent, "Start building S T V matries.");
    /* Overlap matrix */
    f64 *S = x_malloc(N2_f64);
    /* Kinetic energy */
    f64 *T = x_malloc(N2_f64);
    /* Nucleus-electron attraction */
    f64 *V = x_malloc(N2_f64);

    for (u64 i = 0; i < N; ++i)
    {
        u64 Ni = N * i;
        for (u64 j = 0; j < i + 1; ++j)
        {
            struct task_func_stv_arg *arg = x_malloc(sizeof(struct task_func_stv_arg));
            arg->ctx = ctx;
            arg->S = S;
            arg->T = T;
            arg->V = V;
            arg->i = i;
            arg->j = j;
            threadpool_add_task(ctx->tp_ctx, (Ni + j) % (ctx->tp_ctx->n_workers), task_func_stv, arg);
        }
    }

    threadpool_wait_job_done(ctx->tp_ctx);
    log_tm_println(ctx->silent, "S T V matries have been built.");
    ctx->S = S;

    ctx->H = x_malloc(N2 * sizeof(f64));
    for (u64 i = 0; i < N2; ++i)
    {
        ctx->H[i] = T[i] + V[i];
    }

    x_free(V);
    x_free(T);
}

struct task_func_screen_arg
{
    struct scf_context *ctx;
    u64 i;
    u64 j;
    u64 ij;
};

static void task_func_screen(void *p_arg)
{
    struct task_func_screen_arg *arg = (struct task_func_screen_arg *)p_arg;
    struct scf_context *ctx = arg->ctx;
    u64 i = arg->i;
    u64 j = arg->j;
    u64 ij = arg->ij;
    ctx->ScreeningMatrix[ij] = cg_electron_repulsion_integral(ctx->basis_funcs + i, ctx->basis_funcs + j, ctx->basis_funcs + i, ctx->basis_funcs + j);
    x_free(p_arg);
}

static void build_two_electron_integrals(struct scf_context *ctx)
{
    u64 N = ctx->n_basis_funcs;
    u64 N2 = N * N;
    u64 N3 = N2 * N;
    u64 N4 = N3 * N;

    /* Build two-electron integrals */
    if (ctx->direct_scf)
    {
        /* lower triangular matrix */
        ctx->ScreeningMatrix = x_malloc(((N * (N + 1)) >> 1) * sizeof(f64));
        for (u64 i = 0; i < N; ++i)
        {
            for (u64 j = 0; j <= i; ++j)
            {
                struct task_func_screen_arg *arg = x_malloc(sizeof(struct task_func_screen_arg));
                arg->ctx = ctx;
                arg->i = i;
                arg->j = j;
                arg->ij = (i * (i + 1) >> 1) + j;
                threadpool_add_task(ctx->tp_ctx, arg->ij % (ctx->tp_ctx->n_workers), task_func_screen, arg);
            }
        }
        threadpool_wait_job_done(ctx->tp_ctx);
    }
    else
    {
        /*
          Ref: Handbook of computational quantum chemistry, p138, p275
        */
        struct timespec time_start, time_end;
        get_wall_time(&time_start);

        ctx->TwoE = x_malloc(N4 * sizeof(f64));
        for (u64 i = 0; i < N; ++i)
        {
            u64 iN = i * N;
            u64 iN2 = i * N2;
            u64 iN3 = i * N3;
            for (u64 j = 0; j <= i; ++j)
            {
                u64 jN = j * N;
                u64 jN2 = j * N2;
                u64 jN3 = j * N3;
                u64 ij = ((i * (i + 1)) >> 1) + j;
                for (u64 k = 0; k < N; ++k)
                {
                    u64 kN = k * N;
                    u64 kN2 = k * N2;
                    u64 kN3 = k * N3;
                    for (u64 l = 0; l <= k; ++l)
                    {
                        u64 lN = l * N;
                        u64 lN2 = l * N2;
                        u64 lN3 = l * N3;
                        u64 kl = ((k * (k + 1)) >> 1) + l;
                        if (ij >= kl)
                        {
                            f64 val = cg_electron_repulsion_integral(ctx->basis_funcs + i, ctx->basis_funcs + j,
                                                                     ctx->basis_funcs + k, ctx->basis_funcs + l);
                            ctx->TwoE[iN3 + jN2 + kN + l] = val;
                            ctx->TwoE[kN3 + lN2 + iN + j] = val;
                            ctx->TwoE[jN3 + iN2 + lN + k] = val;
                            ctx->TwoE[lN3 + kN2 + jN + i] = val;
                            ctx->TwoE[jN3 + iN2 + kN + l] = val;
                            ctx->TwoE[lN3 + kN2 + iN + j] = val;
                            ctx->TwoE[iN3 + jN2 + lN + k] = val;
                            ctx->TwoE[kN3 + lN2 + jN + i] = val;
                        }
                    }
                }
            }
        }

        get_wall_time(&time_end);
        printf("Building two electron repulsion integrals took %.3f ms\n", diff_time_ms(&time_start, &time_end));

        free_basis(ctx);
    }
}

struct scf_context *scf_initialize(struct cmd_line_args *args, scf_config_func_pointer config_func)
{
    struct timespec time_start, time_end;
    get_wall_time(&time_start);

    struct molecule *mol = args->mol;
    char const *basis_set_filename = args->basis_set;

    struct scf_context *ctx = x_calloc(1, sizeof(struct scf_context));
    ctx->delta_energy = DBL_MAX;
    ctx->density_rmsd = DBL_MAX;
    config_func(ctx);
    ctx->mol = mol;
    ctx->damping = args->damping;
    ctx->silent = args->silent;

    build_basis_funcs(ctx, basis_set_filename);

    u64 N = ctx->n_basis_funcs;
    u64 N2 = N * N;
    u64 N2_f64 = N2 * sizeof(f64);
    ctx->N2 = N2;
    ctx->N2_f64 = N2_f64;

    /* initialize threadpool */
    ctx->tp_ctx = threadpool_initialize(0, 4096);
    ctx->LOCK = x_calloc(N2, sizeof(atomic_bool));

    ctx->nuclear_repulsion_energy = calc_nuclear_repulsion_energy(mol);

    build_one_electron_integrals(ctx);

    ctx->P = x_calloc(N2, sizeof(f64));
    /* allocate matrix buffers for SCF procedure */
    ctx->C = x_malloc(N2_f64);
    ctx->COO = x_malloc(N2_f64);
    ctx->COOT = x_malloc(N2_f64);

    if (ctx->density_init_method == DENSITY_INIT_SOAD)
    {
        soad_initialize_density_matrix(ctx->P, N, mol->atomic_nums, mol->n_atoms);
    }
    if (ctx->density_init_method == DENSITY_INIT_HCORE)
    {
        initialize_density_matrix_with_H_core(ctx);
    }

    mat_scalar_multiply(ctx->P, ctx->P, N, N, 2.0);
    console_printf(ctx->silent, "Initial density sum: %.16e\n", matsum(ctx->P, N, N));

    ctx->NxN_1 = x_malloc(ctx->N2_f64);
    ctx->NxN_2 = x_malloc(ctx->N2_f64);
    ctx->NxN_3 = x_malloc(ctx->N2_f64);

    build_two_electron_integrals(ctx);

    /* allocate other matrices needed in scf iteration */
    ctx->F = x_malloc(ctx->N2_f64);
    ctx->P_last = x_calloc(ctx->N2, sizeof(f64));

    ctx->diis_subspace_size = args->diis_subspace_size;
    ctx->diis_ring_buff_head = 0;
    ctx->diis_history_size = 0;
    ctx->diis_fock_matrices = x_malloc(ctx->N2_f64 * ctx->diis_subspace_size);
    ctx->diis_error_matrices = x_malloc(ctx->N2_f64 * ctx->diis_subspace_size);
    ctx->diis_FPS = x_malloc(ctx->N2_f64);
    ctx->diis_SPF = x_malloc(ctx->N2_f64);
    ctx->diis_B = x_malloc((ctx->diis_subspace_size + 1) * (ctx->diis_subspace_size + 1) * sizeof(f64));
    ctx->diis_ordinate_vector = x_malloc((ctx->diis_subspace_size + 1) * sizeof(f64));
    ctx->diis_coefficients = x_malloc((ctx->diis_subspace_size + 1) * sizeof(f64));
    ctx->diis_F = x_malloc(ctx->N2_f64);

    ctx->damping_factor = 0.5;

    get_wall_time(&time_end);
    console_printf(ctx->silent, "scf_initialize took %.3f ms\n", diff_time_ms(&time_start, &time_end));

    return ctx;
}

void diis_update_fock(struct scf_context *ctx)
{
    u64 N = ctx->n_basis_funcs;
    einsum_mn_np__mp(ctx->F, ctx->P, ctx->NxN_1, N, N, N);
    einsum_mn_np__mp(ctx->NxN_1, ctx->S, ctx->diis_FPS, N, N, N);

    transpose(tag_conjugate(ctx->diis_FPS), ctx->diis_SPF, N, N);

    fractional_matrix_power(ctx->S, ctx->NxN_1, N, -0.5);
    mat_subtract(ctx->diis_FPS, ctx->diis_SPF, ctx->NxN_2, N, N);

    einsum_mn_np__mp(ctx->NxN_1, ctx->NxN_2, ctx->NxN_3, N, N, N);
    einsum_mn_np__mp(ctx->NxN_3, ctx->NxN_1, ctx->NxN_2, N, N, N); // NxN_2: error matrix in an orthonormal basis

    memcpy(ctx->diis_fock_matrices + ctx->N2 * ctx->diis_ring_buff_head, ctx->F, ctx->N2_f64);
    memcpy(ctx->diis_error_matrices + ctx->N2 * ctx->diis_ring_buff_head, ctx->NxN_2, ctx->N2_f64);
    ctx->diis_ring_buff_head = (ctx->diis_ring_buff_head + 1) % ctx->diis_subspace_size;

    ctx->diis_history_size += 1;
    if (ctx->diis_history_size > ctx->diis_subspace_size)
    {
        ctx->diis_history_size = ctx->diis_subspace_size;
    }

    u64 diis_ring_buff_tail = (ctx->diis_ring_buff_head - ctx->diis_history_size + ctx->diis_subspace_size) % ctx->diis_subspace_size;

    for (u64 i = 0; i < ctx->diis_history_size; ++i)
    {
        for (u64 j = 0; j <= i; ++j)
        {
            u64 idx_i = (diis_ring_buff_tail + i) % ctx->diis_subspace_size;
            u64 idx_j = (diis_ring_buff_tail + j) % ctx->diis_subspace_size;

            transpose(tag_conjugate(ctx->diis_error_matrices + idx_i * ctx->N2), ctx->NxN_1, N, N);
            einsum_mn_np__mp(ctx->NxN_1, ctx->diis_error_matrices + idx_j * ctx->N2, ctx->NxN_2, N, N, N);
            f64 value = mattrace(ctx->NxN_2, N);

            ctx->diis_B[i * (ctx->diis_history_size + 1) + j] = value;
            ctx->diis_B[j * (ctx->diis_history_size + 1) + i] = value;
        }
    }

    for (u64 i = 0; i < ctx->diis_history_size + 1; ++i)
    {
        ctx->diis_B[i * (ctx->diis_history_size + 1) + ctx->diis_history_size] = -1.0;
        ctx->diis_B[ctx->diis_history_size * (ctx->diis_history_size + 1) + i] = -1.0;
    }
    ctx->diis_B[(ctx->diis_history_size + 1) * (ctx->diis_history_size + 1) - 1] = 0.0;

    memset(ctx->diis_ordinate_vector, 0, ctx->diis_history_size * sizeof(f64));
    ctx->diis_ordinate_vector[ctx->diis_history_size] = -1.0;

    solve_linear_system(ctx->diis_B, ctx->diis_ordinate_vector, ctx->diis_coefficients, ctx->diis_history_size + 1);

    memset(ctx->diis_F, 0, ctx->N2_f64);

    for (u64 i = 0; i < ctx->diis_history_size; ++i)
    {
        u64 idx_i = (diis_ring_buff_tail + i) % ctx->diis_subspace_size;
        mat_scalar_multiply(ctx->diis_fock_matrices + idx_i * ctx->N2, ctx->NxN_1, N, N, ctx->diis_coefficients[i]);
        mat_add(ctx->diis_F, ctx->NxN_1, ctx->diis_F, N, N);
    }
}

void scf_finalize(struct scf_context *ctx)
{
    x_free(ctx->NxN_1);
    x_free(ctx->NxN_2);
    x_free(ctx->NxN_3);
    if (ctx->direct_scf)
    {
        x_free(ctx->ScreeningMatrix);
        free_basis(ctx);
    }
    else
    {
        x_free(ctx->TwoE);
    }
    x_free(ctx->C);
    x_free(ctx->COO);
    x_free(ctx->COOT);
    x_free(ctx->F);
    x_free(ctx->H);
    x_free(ctx->P);
    x_free(ctx->P_last);

    x_free(ctx->diis_fock_matrices);
    x_free(ctx->diis_error_matrices);
    x_free(ctx->diis_FPS);
    x_free(ctx->diis_SPF);
    x_free(ctx->diis_B);
    x_free(ctx->diis_ordinate_vector);
    x_free(ctx->diis_coefficients);
    x_free(ctx->diis_F);

    x_free(ctx->S);
    x_free((void *)ctx->LOCK);
    threadpool_finalize(ctx->tp_ctx);

    x_free(ctx->atom_bf_map);
    x_free(ctx);
}
