/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "numeric_types.h"
#include "matrix.h"
#include "mm.h"

void transpose(f64* A, f64* B, u64 m, u64 n)
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

void mat_add_A_AT(f64* A, f64* B, u64 m, u64 n)
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

void mat_scalar_multiply(f64* A, f64* B, u64 m, u64 n, f64 c)
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

void mat_add(f64* A, f64* B, f64* C, u64 m, u64 n)
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

void mat_subtract(f64* A, f64* B, f64* C, u64 m, u64 n)
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

void mat_multiply(f64* A, f64* B, f64* C, u64 m, u64 n)
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

f64 matsum(f64* A, u64 m, u64 n)
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

f64 matnorm(f64* A, u64 m, u64 n)
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
f64 mattrace(f64* A, u64 m)
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
void matslice(f64* A, f64* B, u64 N, u64 m, u64 n)
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

u64 is_symmetric(f64* A, u64 m, u64 n)
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

/*
 * Cholesky–Banachiewicz algorithm
 * Ref: https://en.wikipedia.org/wiki/Cholesky_decomposition
 */
void cholesky_decompose(f64* A, f64* L, u64 n)
{
    memset(L, 0, n * n * sizeof(f64));
    for (u64 i = 0; i < n; ++i)
    {
        u64 in = i * n;
        for (u64 j = 0; j < i + 1; ++j)
        {
            f64 sum = 0;
            u64 jn = j * n;
            for (u64 k = 0; k < j; ++k)
            {
                sum += L[in + k] * L[jn + k];
            }
            L[in + j] = (i == j) ? sqrt(A[in + i] - sum) : (1.0 / L[jn + j] * (A[in + j] - sum));
        }
    }
}

void inverse_lower_triangular(u64 n, f64 L[][n], f64 L_inverse[][n])
{
    memset(L_inverse, 0, n * n * sizeof(f64));
    for (u64 i = 0; i < n; i++)
    {
        for (u64 j = 0; j < n; j++)
        {
            if (i == j)
            {
                L_inverse[i][j] = 1 / L[i][j];
            }
            else if (i > j)
            {
                f64 sum = 0;
                for (u64 k = j; k < i; k++)
                {
                    sum += L[i][k] * L_inverse[k][j];
                }
                L_inverse[i][j] = -sum / L[i][i];
            }
        }
    }
}

void matprint(f64* A, u64 m, u64 n)
{
    for (u64 i = 0; i < m; ++i)
    {
        u64 in = i * n;
        printf("%lu: ", i);
        for (u64 j = 0; j < n; ++j)
        {
            printf("%21.14e, ", A[in + j]);
        }
        printf("\n");
    }
}

/* print the m x n upper-left submatrix */
void submatprint(f64* A, u64 n_cols, u64 m, u64 n)
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
void einsum_mn_np__mp(f64* A, f64* B, f64* C, u64 m, u64 n, u64 p);

int test_cholesky_decompose()
{
    f64 F[7][7] = {
        {-5.2611320069251000e-01, -3.4557056578982825e-01, -1.0855199057640517e+00, -9.5527204487693984e-01, 3.5131251855208537e-18, -3.5406867540913306e-01, 3.8607960650126749e-01},
        {-3.4557056578982825e-01, -5.2611320069251000e-01, -1.0855199057640514e+00, -9.5527204487693984e-01, -4.5585376351376927e-17, -3.5406867540913306e-01, -3.8607960650126727e-01},
        {-1.0855199057640517e+00, -1.0855199057640514e+00, -2.0238136751750282e+01, -5.1628988962874072e+00, -2.4970069155071695e-18, -2.8238380318442714e-02, -4.2500739705864210e-17},
        {-9.5527204487693984e-01, -9.5527204487693984e-01, -5.1628988962874072e+00, -2.4333957318475483e+00, 4.0663713195749033e-18, -1.0956991499644125e-01, 3.0639541469921448e-16},
        {3.5131251855208537e-18, -4.5585376351376927e-17, -2.4970069155071695e-18, 4.0663713195749033e-18, -3.8891796505481430e-01, -1.1147763543782036e-16, -7.6762761984471445e-17},
        {-3.5406867540913306e-01, -3.5406867540913306e-01, -2.8238380318442714e-02, -1.0956991499644125e-01, -1.1147763543782036e-16, -3.2717123523978875e-01, 2.5673880865644773e-16},
        {3.8607960650126749e-01, -3.8607960650126727e-01, -4.2500739705864210e-17, 3.0639541469921448e-16, -7.6762761984471445e-17, 2.5673880865644773e-16, -2.9083674614854393e-01}
    };

    f64 S[7][7] = {
        {1.0000000000000000e+00, 2.2870034924425992e-01, 4.8973322893555903e-02, 4.4835728647441092e-01, 0.0000000000000000e+00, 2.3156639380392935e-01, -2.9989746082803970e-01},
        {2.2870034924425992e-01, 1.0000000000000000e+00, 4.8973322893555903e-02, 4.4835728647441092e-01, 0.0000000000000000e+00, 2.3156639380392935e-01, 2.9989746082803970e-01},
        {4.8973322893555903e-02, 4.8973322893555903e-02, 1.0000000000000000e+00, 2.3670392057272621e-01, 0.0000000000000000e+00, 0.0000000000000000e+00, 0.0000000000000000e+00},
        {4.4835728647441092e-01, 4.4835728647441092e-01, 2.3670392057272621e-01, 9.9999999999999978e-01, 0.0000000000000000e+00, 0.0000000000000000e+00, 0.0000000000000000e+00},
        {0.0000000000000000e+00, 0.0000000000000000e+00, 0.0000000000000000e+00, 0.0000000000000000e+00, 9.9999999999999956e-01, 0.0000000000000000e+00, 0.0000000000000000e+00},
        {2.3156639380392935e-01, 2.3156639380392935e-01, 0.0000000000000000e+00, 0.0000000000000000e+00, 0.0000000000000000e+00, 9.9999999999999956e-01, 0.0000000000000000e+00},
        {-2.9989746082803970e-01, 2.9989746082803970e-01, 0.0000000000000000e+00, 0.0000000000000000e+00, 0.0000000000000000e+00, 0.0000000000000000e+00, 9.9999999999999956e-01}
    };

    f64 L[7][7];
    cholesky_decompose((f64*)S, (f64*)L, 7);

    f64 U[7][7];
    transpose((f64*)L, (f64*)U, 7, 7);

    printf("L: \n");
    matprint((f64*)L, 7, 7);
    printf("\n\n");

    printf("U: \n");
    matprint((f64*)U, 7, 7);
    printf("\n\n");

    f64 S2[7][7];
    einsum_mn_np__mp((f64*)L, (f64*)U, (f64*)S2, 7, 7, 7);
    printf("L * U: \n");
    matprint((f64*)S2, 7, 7);
    printf("\n\n");

    printf("S: \n");
    matprint((f64*)S, 7, 7);
    printf("\n\n");

    f64 L_inverse[7][7];
    inverse_lower_triangular(7, L, L_inverse);
    printf("L_inverse: \n");
    matprint((f64*)L_inverse, 7, 7);
    printf("\n\n");

    f64 L2[7][7];
    einsum_mn_np__mp((f64*)L, (f64*)L_inverse, (f64*)L2, 7, 7, 7);
    printf("L * L_inverse: \n");
    matprint((f64*)L2, 7, 7);
    printf("\n\n");

    f64 U_inverse[7][7];
    transpose((f64*)L_inverse, (f64*)U_inverse, 7, 7);
    printf("U_inverse: \n");
    matprint((f64*)U_inverse, 7, 7);
    printf("\n\n");

    f64 U2[7][7];
    einsum_mn_np__mp((f64*)U, (f64*)U_inverse, (f64*)U2, 7, 7, 7);
    printf("U * U_inverse: \n");
    matprint((f64*)U2, 7, 7);
    printf("\n\n");

    f64 F2[7][7];
    einsum_mn_np__mp((f64*)L_inverse, (f64*)F, (f64*)F2, 7, 7, 7);
    f64 F3[7][7];
    einsum_mn_np__mp((f64*)F2, (f64*)U_inverse, (f64*)F3, 7, 7, 7);

    printf("F3: \n");
    matprint((f64*)F3, 7, 7);

    return 0;
}

int main(void)
{
    test_cholesky_decompose();

    if (1)
    {
        f64* A = x_malloc(sizeof(f64) * 6);
        f64* B = x_malloc(sizeof(f64) * 6);
        f64* C = x_malloc(sizeof(f64) * 9);

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
