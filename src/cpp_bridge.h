/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef CPP_BRIDGE_H
#define CPP_BRIDGE_H

#include "numeric_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

    u64 num_of_concurrent_threads();
    char *load_basis_set(char const *basis_set_filename, u64 n_elements, u64 *elements);
    void eigh_veconly(f64 *A, f64 *V, u64 N);
    void generalized_eigh_veconly(f64 *A, f64 *B, f64 *V, u64 N);
    void LUP(f64 *A, f64 *b, f64 *x, u64 N);
    void fractional_matrix_power(f64 *A, f64 *B, u64 N, f64 p);
    void solve_linear_system(f64 *A, f64 *b, f64 *x, u64 N);

#ifdef __cplusplus
}
#endif
#endif
