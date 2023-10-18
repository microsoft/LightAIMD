/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef LAPACKE_BRIDGE_H
#define LAPACKE_BRIDGE_H

#include "numeric_types.h"

i64 solve_generalized_eigenvalue_symmetric(f64 *A, f64 *B, f64 *V, u64 N);
i64 mat_fractional_power(f64 *A, f64 *B, u64 N, f64 p);
i64 solve_linear_system_symmetric(f64 *A, f64 *b, f64 *x, u64 N);

#endif
