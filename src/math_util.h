/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef MATH_UTIL_H
#define MATH_UTIL_H

void transpose(f64 *A, f64 *B, u64 m, u64 n);
void mat_add_A_AT(f64 *A, f64 *B, u64 m, u64 n);

/* element wise */
void mat_scalar_multiply(f64 *A, f64 *B, u64 m, u64 n, f64 c);
void mat_add(f64 *A, f64 *B, f64 *C, u64 m, u64 n);
void mat_subtract(f64 *A, f64 *B, f64 *C, u64 m, u64 n);
void mat_multiply(f64 *A, f64 *B, f64 *C, u64 m, u64 n);

f64 matsum(f64 *A, u64 m, u64 n);
f64 matnorm(f64 *A, u64 m, u64 n);
f64 mattrace(f64 *A, u64 m);
void matslice(f64 *A, f64 *B, u64 N, u64 m, u64 n);

u64 is_symmetric(f64 *A, u64 m, u64 n);

void matprint(f64 *A, u64 m, u64 n);
void submatprint(f64 *A, u64 n_cols, u64 m, u64 n);

/*
 * The following are some tag functions.
 * A tag function does nothing; it only serves as a comment, note, or tag.
 * Sometimes, we in thoery need to perform an operation;
 * however, the operation does not have an actual effect because of the input
 * has a certain form, such as a hermitian matrix.
 * In this case, we just call a do-nothing tag function to indicate the operation
 * we need to take.
 */

inline f64 *tag_conjugate(f64 *A)
{
    return A;
}

inline f64 *tag_transpose(f64 *A)
{
    return A;
}
#endif
