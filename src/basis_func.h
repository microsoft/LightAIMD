/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef BASIS_FUNC_H
#define BASIS_FUNC_H
#include "numeric_types.h"
#include "vec3d.h"

#ifdef __cplusplus
extern "C"
{
#endif

    struct basis_func
    {
        /* angular quantum numbers */
        u64 l;
        u64 m;
        u64 n;

        u64 n_exponents;
        f64 *exponents;
        f64 *coefficients;
        f64 *normalization_factors; /* primitive normalization factors */
        f64 contracted_bf_normalization_factor;

        /* origin */
        f64 x0;
        f64 y0;
        f64 z0;
    };

    double normalize_gaussian_primitive(double alpha, u64 l, u64 m, u64 n);
    double normalize_contracted_gaussian_func(u64 n_primitives, u64 l, u64 m, u64 n, double *exponents, double *coefficients, double *primitive_normalization_factor);

    f64 basis_funcs_value(struct basis_func *bf, struct vec3d *v);
    void basis_funcs_first_derivative(struct basis_func *bf, struct vec3d *v, f64 *x, f64 *y, f64 *z);
    void basis_funcs_second_derivative(struct basis_func *bf, struct vec3d *v,
                                       f64 *xx, f64 *yy, f64 *zz, f64 *xy, f64 *xz, f64 *yz);
    f64 basis_func_laplacian(struct basis_func *bf, struct vec3d *v);
    void basis_funcs_third_derivative(struct basis_func *bf, struct vec3d *v,
                                  f64 *xxx, f64 *xyy, f64 *xzz,
                                  f64 *yyy, f64 *yxx, f64 *yzz,
                                  f64 *zzz, f64 *zxx, f64 *zyy);
    void print_basis_func(struct basis_func *bf);
    void print_basis_funcs_buffer(const char *buffer);

#ifdef __cplusplus
}
#endif
#endif
