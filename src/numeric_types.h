/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef NUMERIC_TYPES_H
#define NUMERIC_TYPES_H

#include <stdint.h>

#include "config.h"

#ifdef PREFER_FAST_TYPE

#define i8 int_fast8_t
#define i16 int_fast16_t
#define i32 int_fast32_t
#define i64 int_fast64_t

#define u8 uint_fast8_t
#define u16 uint_fast16_t
#define u32 uint_fast32_t
#define u64 uint_fast64_t

#elif PREFER_COMPACT_TYPE

#define i8 int_least8_t
#define i16 int_least16_t
#define i32 int_least32_t
#define i64 int_least64_t

#define u8 uint_least8_t
#define u16 uint_least16_t
#define u32 uint_least32_t
#define u64 uint_least64_t

#endif

#define U64_MAX 18446744073709551615ull

#define f32 float
#define f64 double

#define c32 float _Complex
#define c64 double _Complex
#define c128 long double _Complex

#ifndef __STDC_NO_ATOMICS__
#include <stdatomic.h>

#ifdef PREFER_FAST_TYPE

#define atomic_i8 atomic_int_fast8_t
#define atomic_i16 atomic_int_fast16_t
#define atomic_i32 atomic_int_fast32_t
#define atomic_i64 atomic_int_fast64_t

#define atomic_u8 atomic_uint_fast8_t
#define atomic_u16 atomic_uint_fast16_t
#define atomic_u32 atomic_uint_fast32_t
#define atomic_u64 atomic_uint_fast64_t

#elif PREFER_COMPACT_TYPE

#define atomic_i8 atomic_int_least8_t
#define atomic_i16 atomic_int_least16_t
#define atomic_i32 atomic_int_least32_t
#define atomic_i64 atomic_int_least64_t

#define atomic_u8 atomic_uint_least8_t
#define atomic_u16 atomic_uint_least16_t
#define atomic_u32 atomic_uint_least32_t
#define atomic_u64 atomic_uint_least64_t

#endif

#endif

#endif

void print_numeric_type_sizes();
