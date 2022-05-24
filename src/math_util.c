/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "numeric_types.h"
#include "math_util.h"
#include "mm.h"

void transpose(f64 *A, f64 *B, u64 m, u64 n)
{
    for (u64 i = 0; i < m; ++i)
    {
        u64 in = i * n;
        for (u64 j = 0; j < n; ++j)
        {
            B[j * m + i] = A[in + j];
        }
    }
}

void mat_add_A_AT(f64 *A, f64 *B, u64 m, u64 n)
{
    for (u64 i = 0; i < m; ++i)
    {
        u64 in = i * n;
        for (u64 j = 0; j < n; ++j)
        {
            u64 ij = in + j;
            B[ij] = A[ij] + A[j * n + i];
        }
    }
}

void mat_scalar_multiply(f64 *A, f64 *B, u64 m, u64 n, f64 c)
{
    for (u64 i = 0; i < m; ++i)
    {
        u64 in = i * n;
        for (u64 j = 0; j < n; ++j)
        {
            u64 ij = in + j;
            B[ij] = A[ij] * c;
        }
    }
}

void mat_add(f64 *A, f64 *B, f64 *C, u64 m, u64 n)
{
    for (u64 i = 0; i < m; ++i)
    {
        u64 in = i * n;
        for (u64 j = 0; j < n; ++j)
        {
            u64 ij = in + j;
            C[ij] = A[ij] + B[ij];
        }
    }
}

void mat_subtract(f64 *A, f64 *B, f64 *C, u64 m, u64 n)
{
    for (u64 i = 0; i < m; ++i)
    {
        u64 in = i * n;
        for (u64 j = 0; j < n; ++j)
        {
            u64 ij = in + j;
            C[ij] = A[ij] - B[ij];
        }
    }
}

void mat_multiply(f64 *A, f64 *B, f64 *C, u64 m, u64 n)
{
    for (u64 i = 0; i < m; ++i)
    {
        u64 in = i * n;
        for (u64 j = 0; j < n; ++j)
        {
            u64 ij = in + j;
            C[ij] = A[ij] * B[ij];
        }
    }
}

f64 matsum(f64 *A, u64 m, u64 n)
{
    f64 sum = 0;
    for (u64 i = 0; i < m; ++i)
    {
        u64 in = i * n;
        for (u64 j = 0; j < n; ++j)
        {
            sum += A[in + j];
        }
    }
    return sum;
}

f64 matnorm(f64 *A, u64 m, u64 n)
{
    f64 sum = 0;
    for (u64 i = 0; i < m; ++i)
    {
        u64 in = i * n;
        for (u64 j = 0; j < n; ++j)
        {
            u64 ij = in + j;
            sum += A[ij] * A[ij];
        }
    }
    return sqrt(sum);
}

/* calculates the trace of the square matrix A */
f64 mattrace(f64 *A, u64 m)
{
    f64 value = 0.0;
    for (u64 i = 0; i < m; ++i)
    {
        value += A[i * m + i];
    }
    return value;
}

/*
A is an (M, N) matrix, M is not used.
The resulting matrix B is (m, n), where m <= M, n <= N.
*/
void matslice(f64 *A, f64 *B, u64 N, u64 m, u64 n)
{
    for (u64 i = 0; i < m; ++i)
    {
        u64 in = i * n;
        u64 iN = i * N;
        for (u64 j = 0; j < n; ++j)
        {
            B[in + j] = A[iN + j];
        }
    }
}

u64 is_symmetric(f64 *A, u64 m, u64 n)
{
    for (u64 i = 0; i < m; ++i)
    {
        u64 in = i * n;
        for (u64 j = 0; j < n; ++j)
        {
            if (A[in + j] != A[j * n + i])
            {
                return 0;
            }
        }
    }
    return 1;
}

void matprint(f64 *A, u64 m, u64 n)
{
    for (u64 i = 0; i < m; ++i)
    {
        u64 in = i * n;
        printf("%lu: ", i);
        for (u64 j = 0; j < n; ++j)
        {
            printf("%21.14e ", A[in + j]);
        }
        printf("\n");
    }
}

/* print the m x n upper-left submatrix */
void submatprint(f64 *A, u64 n_cols, u64 m, u64 n)
{
    for (u64 i = 0; i < m; ++i)
    {
        u64 in = i * n_cols;
        printf("%lu: ", i);
        for (u64 j = 0; j < n; ++j)
        {
            printf("%21.14e ", A[in + j]);
        }
        printf("\n");
    }
}

#ifdef MODULE_TEST
int main(void)
{
    if (1)
    {
        f64 *A = x_malloc(sizeof(f64) * 6);
        f64 *B = x_malloc(sizeof(f64) * 6);
        f64 *C = x_malloc(sizeof(f64) * 9);

        for (u64 i = 0; i < 6; ++i)
        {
            A[i] = i;
            B[i] = i;
        }

        matslice(A, B, 3, 2, 2);

        for (u64 i = 0; i < 4; ++i)
        {
            printf("B[%lu]:%f\n", i, B[i]);
        }

        transpose(A, B, 2, 3);

        for (u64 i = 0; i < 6; ++i)
        {
            printf("B[%lu]:%f\n", i, B[i]);
        }

        for (u64 i = 0; i < 9; ++i)
        {
            C[i] = i;
        }

        x_free(C);
        x_free(B);
        x_free(A);
    }

    return 0;
}
#endif
