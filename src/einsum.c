/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "numeric_types.h"
#include "mm.h"
#include "scf.h"
#include "thread_pool.h"

/*
 * C = einsum('mn,np->mp', A, B)
 * A: m x n; B: n x p; C: m x p
 */
void einsum_mn_np__mp(f64* A, f64* B, f64* C, u64 m, u64 n, u64 p)
{
    for (u64 i = 0; i < m; ++i)
    {
        u64 in = i * n;
        for (u64 j = 0; j < p; ++j)
        {
            f64 ij = 0.0;
            for (u64 k = 0; k < n; ++k)
            {
                ij += A[in + k] * B[k * p + j];
            }
            C[i * p + j] = ij;
        }
    }
}

struct task_func_einsum_mn_np__mp_arg
{
    f64* A;
    f64* B;
    f64* C;
    u64 m;
    u64 n;
    u64 p;
    u64 j;
};

void task_func_einsum_mn_np__mp(void* p_arg)
{
    struct task_func_einsum_mn_np__mp_arg* arg = (struct task_func_einsum_mn_np__mp_arg*)p_arg;
    f64* A = arg->A;
    f64* B = arg->B;
    f64* C = arg->C;
    u64 m = arg->m;
    u64 n = arg->n;
    u64 p = arg->p;
    u64 j = arg->j;

    for (u64 i = 0; i < m; ++i)
    {
        f64 ij = 0.0;
        for (u64 k = 0; k < n; ++k)
        {
            ij += A[i * n + k] * B[k * p + j];
        }
        C[i * p + j] = ij;
    }

    x_free(p_arg);
}

void einsum_mn_np__mp_parallel(f64* A, f64* B, f64* C, u64 m, u64 n, u64 p, struct threadpool_context* tp_ctx)
{
    for (u64 j = 0; j < p; ++j)
    {
        struct task_func_einsum_mn_np__mp_arg* arg = x_malloc(sizeof(struct task_func_einsum_mn_np__mp_arg));
        arg->A = A;
        arg->B = B;
        arg->C = C;
        arg->m = m;
        arg->n = n;
        arg->p = p;
        arg->j = j;

        threadpool_add_task(tp_ctx, j % (tp_ctx->n_workers), task_func_einsum_mn_np__mp, arg);
    }
    threadpool_wait_job_done(tp_ctx);
}

/*
 * Calculates A.T X B
 * A: m x n; B: m x n;
 * C = einsum('mn,mp->np', A, B)
 */
void einsum_mn_mp__np(f64* A, f64* B, f64* C, u64 m, u64 n, u64 p)
{
    for (u64 i = 0; i < n; ++i)
    {
        for (u64 j = 0; j < p; ++j)
        {
            f64 ij = 0.0;
            for (u64 k = 0; k < m; ++k)
            {
                ij += A[k * n + i] * B[k * p + j];
            }
            C[i * n + j] = ij;
        }
    }
}

struct task_func_einsum_mn_mp__np_arg
{
    f64* A;
    f64* B;
    f64* C;
    u64 m;
    u64 n;
    u64 p;
    u64 i;
};

void task_func_einsum_mn_mp__np(void* p_arg)
{
    struct task_func_einsum_mn_mp__np_arg* arg = (struct task_func_einsum_mn_mp__np_arg*)p_arg;

    for (u64 j = 0; j < arg->p; ++j)
    {
        f64 ij = 0.0;
        for (u64 k = 0; k < arg->m; ++k)
        {
            ij += arg->A[k * arg->n + arg->i] * arg->B[k * arg->p + j];
        }
        arg->C[arg->i * arg->n + j] = ij;
    }

    x_free(p_arg);
}

void einsum_mn_mp__np_parallel(f64* A, f64* B, f64* C, u64 m, u64 n, u64 p, struct threadpool_context* tp_ctx)
{
    for (u64 i = 0; i < n; ++i)
    {
        struct task_func_einsum_mn_mp__np_arg* arg = x_malloc(sizeof(struct task_func_einsum_mn_mp__np_arg));
        arg->A = A;
        arg->B = B;
        arg->C = C;
        arg->m = m;
        arg->n = n;
        arg->p = p;
        arg->i = i;
        threadpool_add_task(tp_ctx, i % (tp_ctx->n_workers), task_func_einsum_mn_mp__np, arg);
    }
    threadpool_wait_job_done(tp_ctx);
}

/*
 * D = einsum('mn,mp,m->np', A, B, C)
 */
void einsum_mn_mp_m__np(f64* A, f64* B, f64* C, f64* D, u64 m, u64 n, u64 p)
{
    for (u64 i = 0; i < n; ++i)
    {
        for (u64 j = 0; j < p; ++j)
        {
            f64 ij = 0.0;
            for (u64 k = 0; k < m; ++k)
            {
                ij += A[k * n + i] * B[k * p + j] * C[k];
            }
            D[i * n + j] = ij;
        }
    }
}

/*
 * The 'addition assignment +=' version of 'mn,mp,m->np'
 * D += einsum('mn,mp,m->np', A, B, C)
 */
void einsumaa_mn_mp_m__np(f64* A, f64* B, f64* C, f64* D, u64 m, u64 n, u64 p)
{
    for (u64 i = 0; i < n; ++i)
    {
        for (u64 j = 0; j < p; ++j)
        {
            f64 ij = 0.0;
            for (u64 k = 0; k < m; ++k)
            {
                ij += A[k * n + i] * B[k * p + j] * C[k];
            }
            D[i * n + j] += ij;
        }
    }
}

/*
 * C = einsum('mn,mn->m', A, B)
 */
void einsum_mn_mn__m(f64* A, f64* B, f64* C, u64 m, u64 n)
{
    for (u64 i = 0; i < m; ++i)
    {
        f64 value = 0;
        u64 in = i * n;
        for (u64 j = 0; j < n; ++j)
        {
            value += A[in + j] * B[in + j];
        }
        C[i] = value;
    }
}

/*
 * einsum('mn,nm->', A, B)
 */
f64 einsum_mn_nm(f64* A, f64* B, u64 m, u64 n)
{
    f64 result = 0.0;
    for (u64 i = 0; i < m; ++i)
    {
        u64 in = i * n;
        for (u64 j = 0; j < n; ++j)
        {
            result += A[in + j] * B[j * m + i];
        }
    }
    return result;
}

#ifdef MODULE_TEST
int main(void)
{
    if (1)
    {
        f64 A[] = {0.32005659, 0.59122189, 0.02301279, 0.68163162, 0.88728637, 0.48753426};
        f64 B[] = {0.2156739, 0.34255082, 0.60567311, 0.07933593, 0.50933051, 0.48606763};
        f64 C[] = {0.1, 0.2, 0.3};
        f64 D[] = {0.0, 0.0, 0.0, 0.0}; // dim: 2 X 2

        einsum_mn_mp_m__np(A, B, C, D, 3, 2, 2);

        for (u64 i = 0; i < 4; ++i)
        {
            printf("D[%lu] = %.8f\n", i, D[i]);
        }

        printf("mn,nm-> : %.16f\n", einsum_mn_nm(A, B, 3, 2));
    }

    if (1)
    {
        f64 A[] = {0.32005659, 0.59122189, 0.02301279, 0.68163162, 0.88728637, 0.48753426};
        f64 B[] = {0.2156739, 0.34255082, 0.60567311, 0.07933593, 0.50933051, 0.48606763};
        f64 C[9];

        einsum_mn_np__mp(A, B, C, 3, 2, 3);

        for (u64 i = 0; i < 9; ++i)
        {
            printf("%lu: %f\n", i, C[i]);
        }
    }

    return 0;
}
#endif
