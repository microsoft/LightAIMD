/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef NUMERIC_TYPES_H
#define NUMERIC_TYPES_H

#include <stddef.h>
#include <stdint.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;
typedef double f64;

typedef float _Complex c32;
typedef double _Complex c64;
typedef long double _Complex c128;

#ifndef __STDC_NO_ATOMICS__

#ifdef __cplusplus
#include <atomic>
#define _Atomic(X) std::atomic<X>
typedef std::atomic_bool atomic_bool;
typedef std::atomic_int8_t atomic_i8;
typedef std::atomic_int16_t atomic_i16;
typedef std::atomic_int32_t atomic_i32;
typedef std::atomic_int64_t atomic_i64;
typedef std::atomic_uint8_t atomic_u8;
typedef std::atomic_uint16_t atomic_u16;
typedef std::atomic_uint32_t atomic_u32;
typedef std::atomic_uint64_t atomic_u64;
#else
#include <stdatomic.h>
typedef _Atomic(int8_t) atomic_i8;
typedef _Atomic(int16_t) atomic_i16;
typedef _Atomic(int32_t) atomic_i32;
typedef _Atomic(int64_t) atomic_i64;
typedef _Atomic(uint8_t) atomic_u8;
typedef _Atomic(uint16_t) atomic_u16;
typedef _Atomic(uint32_t) atomic_u32;
typedef _Atomic(uint64_t) atomic_u64;
#endif

#endif

#define B64_MEMBERS            \
    i8 i8_value;               \
    u8 u8_value;               \
    i16 i16_value;             \
    u16 u16_value;             \
    i32 i32_value;             \
    u32 u32_value;             \
    i64 i64_value;             \
    u64 u64_value;             \
    f32 f32_value;             \
    f64 f64_value;             \
    i8 i8_array[8];            \
    u8 u8_array[8];            \
    i16 i16_array[4];          \
    u16 u16_array[4];          \
    i32 i32_array[2];          \
    u32 u32_array[2];          \
    void* pointer

union b64
{
    B64_MEMBERS;
};

void numeric_type_print_sizes();
u64 f64_is_close(f64 a, f64 b);
u64 f64_is_zero(f64 a);

#define U32_MAX 0xFFFFFFFF
#define U64_MAX 0xFFFFFFFFFFFFFFFF

#endif
