/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <string>
#include <thread>
#include <fstream>
#include <iostream>
#include <regex>

#include <Eigen/Eigenvalues>
#include <Eigen/LU>
#include <unsupported/Eigen/MatrixFunctions>
#include <nlohmann/json.hpp>

#include "numeric_types.h"
#include "mm.h"

typedef Eigen::Matrix<f64, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> Matrixf64;
typedef Eigen::Matrix<f64, Eigen::Dynamic, 1> Vectorf64;

extern "C"
{
    u64 num_of_concurrent_threads()
    {
        return (u64)std::thread::hardware_concurrency();
    }

    void cartesian_shell_pairs(u64 n)
    {
        for (i64 i = n; i >= 0; --i)
        {
            for (i64 j = n - i; j >= 0; --j)
            {
                printf("(%lu, %lu, %lu)\n", i, j, n - i - j);
            }
        }
    }

    char *load_basis_set(char const *basis_set_filename, u64 n_elements, u64 *elements)
    {
        std::string sanitized_file_path = std::regex_replace(std::string(basis_set_filename), std::regex("\\*"), "_st_");
        std::ifstream fs_json(sanitized_file_path);
        auto basis_set = nlohmann::json::parse(fs_json);

        u64 bc = sizeof(u64); /* byte count, initial value: space for number of elements */
        u64 n_found_elements = 0;
        for (auto const &element : basis_set["elements"].items())
        {
            auto Z = std::stoull(element.key());
            u64 *s = elements;
            u64 found = 0;
            for (u64 r = 0; r < n_elements; ++r)
            {
                if (Z == *s)
                {
                    found = 1;
                }
                ++s;
            }

            if (found)
            {
                ++n_found_elements;
                /* space for atomic number, number of orbitals */
                bc += sizeof(u64) * 2;
                for (auto const &shell : element.value()["electron_shells"])
                {
                    u64 n_exponents = shell["exponents"].size();
                    for (auto const &am : shell["angular_momentum"])
                    {
                        u64 k = (u64)am;
                        u64 n_orbitals = ((k + 1) * (k + 2)) >> 1;
                        /* space for angular quantum numbers, n_exponents, exponents, and coefficients */
                        bc += n_orbitals * (sizeof(u64) * 4 + n_exponents * sizeof(f64) * 2);
                    }
                }
            }
        }

        u64 *buffer = (u64 *)x_malloc(bc);
        u64 *p = buffer;
        *p = n_found_elements;
        ++p;
        for (auto const &element : basis_set["elements"].items())
        {
            auto Z = std::stoull(element.key());
            u64 *s = elements;
            u64 found = 0;
            for (u64 r = 0; r < n_elements; ++r)
            {
                if (Z == *s)
                {
                    found = 1;
                }
                ++s;
            }
            if (found)
            {
                *p = Z;
                ++p;
                u64 *n_orbitals_p = p;
                ++p; // skip the n_orbitals as we do not know its value yet
                u64 n_orbitals = 0;
                for (auto const &shell : element.value()["electron_shells"])
                {
                    u64 n_exponents = shell["exponents"].size();
                    u64 am_index = 0;
                    for (auto const &am : shell["angular_momentum"])
                    {
                        u64 k = (u64)am;
                        for (i64 l = k; l >= 0; --l)
                        {
                            for (i64 m = k - l; m >= 0; --m)
                            {
                                u64 n = k - l - m;
                                *p = l;
                                ++p;
                                *p = m;
                                ++p;
                                *p = n;
                                ++p;
                                *p = n_exponents;
                                ++p;
                                for (std::string const exponent : shell["exponents"])
                                {
                                    *((f64 *)p) = std::stod(exponent);
                                    ++p;
                                }
                                for (std::string const coefficient : shell["coefficients"][am_index])
                                {
                                    *((f64 *)p) = std::stod(coefficient);
                                    ++p;
                                }
                                ++n_orbitals;
                                // std::cout << Z << " " << l << m << n << std::endl;
                            }
                        }
                        ++am_index;
                    }
                }
                *n_orbitals_p = n_orbitals;
            }
        }
        return (char *)buffer;
    }

    void eigh_veconly(f64 *A, f64 *V, u64 N)
    {
        auto M = Eigen::Map<Matrixf64>(A, N, N);
        Eigen::SelfAdjointEigenSolver<Matrixf64> gen_eig_solver(M);
        auto pvec = gen_eig_solver.eigenvectors().data();

        // transpose and copy to V (pvec is a column-major matrix)
        for (u64 i = 0; i < N; ++i)
        {
            u64 iN = i * N;
            for (u64 j = 0; j < N; ++j)
            {
                V[j * N + i] = pvec[iN + j];
            }
        }
    }

    void generalized_eigh_veconly(f64 *A, f64 *B, f64 *V, u64 N)
    {
        auto MA = Eigen::Map<Matrixf64>(A, N, N);
        auto MB = Eigen::Map<Matrixf64>(B, N, N);
        Eigen::GeneralizedSelfAdjointEigenSolver<Matrixf64> gen_eig_solver(MA, MB);
        auto pvec = gen_eig_solver.eigenvectors().data();

        // transpose and copy to V (pvec is a column-major matrix)
        for (u64 i = 0; i < N; ++i)
        {
            u64 iN = i * N;
            for (u64 j = 0; j < N; ++j)
            {
                V[j * N + i] = pvec[iN + j];
            }
        }
    }

    /*
     * LU factorization with partial pivoting
     * A: square matrix
     * Ax = b
     */
    void LUP(f64 *A, f64 *b, f64 *x, u64 N)
    {
        auto MA = Eigen::Map<Matrixf64>(A, N, N);
        auto Mb = Eigen::Map<Vectorf64>(b, N);
        Eigen::PartialPivLU<Matrixf64> pplu(MA);
        Vectorf64 px(pplu.solve(Mb));
        memcpy(x, px.data(), N * sizeof(f64));
    }

    /*
     * A: N X N (input matrix)
     * B: N X N (output matrix)
     * p: fractional power
     */
    void fractional_matrix_power(f64 *A, f64 *B, u64 N, f64 p)
    {
        auto M = Eigen::Map<Matrixf64>(A, N, N);
        auto FMP = M.pow(p).eval();
        memcpy(B, FMP.data(), N * N * sizeof(f64));
    }

    void solve_linear_system(f64 *A, f64 *b, f64 *x, u64 N)
    {
        auto MA = Eigen::Map<Matrixf64>(A, N, N);
        auto Mb = Eigen::Map<Vectorf64>(b, N);
        Eigen::ColPivHouseholderQR<Matrixf64> decomposition(MA);
        Vectorf64 px(decomposition.solve(Mb));
        memcpy(x, px.data(), N * sizeof(f64));
    }
}

#ifdef MODULE_TEST
int main(void)
{
    printf("number of concurrent cpu threads: %lu\n", num_of_concurrent_threads());

    if (1)
    {
        f64 A[] = {1, 2, 3, 5};
        f64 b[] = {1, 2};
        f64 x[] = {0, 0};

        solve_linear_system(A, b, x, 2);

        for (u64 i = 0; i < 2; ++i)
        {
            printf("%.3f\n", x[i]);
        }
        printf("\n");
    }

    if (1)
    {
        f64 MA[] = {1, 3, 1, 4};
        f64 MB[] = {0, 0, 0, 0};

        fractional_matrix_power(MA, MB, 2, -0.5);

        for (u64 i = 0; i < 4; ++i)
        {
            printf("%.3f    %.3f\n", MA[i], MB[i]);
        }
    }

    if (1)
    {
        Matrixf64 A(2, 2);
        A << 1, 2, 3, 4;
        std::cout << A * A << std::endl;

        u64 elements[] = {1, 6, 7, 8};
        load_basis_set("basis-set/sto-3g.json", 4, elements);

        Matrixf64 M(5, 5);
        M << 34, -4, -10, -7, 2,
            -4, 7, 2, 12, 0,
            -10, 2, 44, 2, -19,
            -7, 12, 2, 79, -34,
            2, 0, -19, -34, 29;
        std::cout << M << std::endl;
        Eigen::SelfAdjointEigenSolver<Matrixf64> gen_eig_solver(M);
        auto w = gen_eig_solver.eigenvalues();
        auto eigenvec = gen_eig_solver.eigenvectors();
        std::cout << w << "\n"
                  << eigenvec << std::endl;

        for (u64 k = 0; k < 4; ++k)
        {
            cartesian_shell_pairs(k);
            printf("\n");
        }
    }
    return 0;
}
#endif
