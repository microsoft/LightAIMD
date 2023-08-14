/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef SPECIAL_FUNC_H
#define SPECIAL_FUNC_H
#include "numeric_types.h"
#include "cuda_helper.h"

u64 factorial(u64 n);
__device__ f64 boys_func(f64 n, f64 x);
__device__ i64 double_factorial(i64 n);

#endif
