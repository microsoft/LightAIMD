/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef EINSUM_H
#define EINSUM_H
#include "numeric_types.h"
#include "thread_pool.h"

void einsum_mn_np__mp(f64* A, f64* B, f64* C, u64 m, u64 n, u64 p);
void einsum_mn_np__mp_parallel(f64* A, f64* B, f64* C, u64 m, u64 n, u64 p, struct threadpool_context* tp_ctx);
void einsum_mn_mp__np(f64* A, f64* B, f64* C, u64 m, u64 n, u64 p);
void einsum_mn_mp__np_parallel(f64* A, f64* B, f64* C, u64 m, u64 n, u64 p, struct threadpool_context* tp_ctx);
void einsum_mn_mp_m__np(f64* A, f64* B, f64* C, f64* D, u64 m, u64 n, u64 p);
void einsumaa_mn_mp_m__np(f64* A, f64* B, f64* C, f64* D, u64 m, u64 n, u64 p);
void einsum_mn_mn__m(f64* A, f64* B, f64* C, u64 m, u64 n);
f64 einsum_mn_nm(f64* A, f64* B, u64 m, u64 n);
#endif
