/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <stdio.h>
#include <math.h>
#include "numeric_types.h"
#include "constants.h"
#include "vec3d.h"
#include "basis_func.h"
#include "special_func.h"

double normalize_gaussian_primitive(double alpha, u64 l, u64 m, u64 n)
{
    /* Just different variants
    return sqrt(pow(2, 2 * (l + m + n) + 1.5) * pow(alpha, l + m + n + 1.5) / double_factorial(2 * l - 1) / double_factorial(2 * m - 1) / double_factorial(2 * n - 1) / pow(M_PI, 1.5));
    return sqrt(pow(2, 2 * (l + m + n) + 1.5) * pow(alpha, l + m + n + 1.5) / (double_factorial(2 * l - 1) * double_factorial(2 * m - 1) * double_factorial(2 * n - 1) * pow(M_PI, 1.5)));
    return pow(2, l + m + n + 0.75) * pow(alpha, 0.5 * (l + m + n) + 0.75) / sqrt(double_factorial(2 * l - 1) * double_factorial(2 * m - 1) * double_factorial(2 * n - 1) * pow(M_PI, 1.5));
    */
    return pow(2, l + m + n + 0.75) * pow(alpha, 0.5 * (l + m + n) + 0.75) / sqrt(double_factorial(2 * l - 1) * double_factorial(2 * m - 1) * double_factorial(2 * n - 1) * POW_PI_1_DOT_5);
}

double normalize_contracted_gaussian_func(u64 n_primitives, u64 l, u64 m, u64 n, double *exponents, double *coefficients, double *primitive_normalization_factor)
{
    u64 L = l + m + n;
    double N = 0.0;
    for (u64 i = 0; i < n_primitives; ++i)
    {
        for (u64 j = 0; j < n_primitives; ++j)
        {
            N += primitive_normalization_factor[i] * primitive_normalization_factor[j] * coefficients[i] * coefficients[j] / pow(exponents[i] + exponents[j], L + 1.5);
        }
    }

    return pow(N * POW_PI_1_DOT_5 * double_factorial(2 * l - 1) * double_factorial(2 * m - 1) * double_factorial(2 * n - 1) / pow(2.0, L), -0.5);
}

f64 basis_funcs_value(struct basis_func *bf, struct vec3d *v)
{
    struct vec3d vt = {bf->x0, bf->y0, bf->z0};
    vec3d_subtract(v, &vt, &vt);
    f64 r_sq = vec3d_norm_squared(&vt);

    /* + 1e-100 to avoid division by zero */
    f64 x_x0 = v->x - bf->x0 + 1e-100;
    f64 y_y0 = v->y - bf->y0 + 1e-100;
    f64 z_z0 = v->z - bf->z0 + 1e-100;

    f64 value = 0.0;
    for (u64 k = 0; k < bf->n_exponents; ++k)
    {
        value += bf->coefficients[k] *
                 bf->normalization_factors[k] *
                 pow(x_x0, bf->l) *
                 pow(y_y0, bf->m) *
                 pow(z_z0, bf->n) *
                 exp(-(bf->exponents[k] * r_sq));
    }

    return value;
}

void basis_funcs_first_derivative(struct basis_func *bf, struct vec3d *v, f64 *x, f64 *y, f64 *z)
{
    /* + 1e-30 to avoid division by zero */
    f64 x_x0 = v->x - bf->x0 + 1e-100;
    f64 y_y0 = v->y - bf->y0 + 1e-100;
    f64 z_z0 = v->z - bf->z0 + 1e-100;
    f64 r_sq = x_x0 * x_x0 + y_y0 * y_y0 + z_z0 * z_z0;

    f64 xg = 0.0;
    f64 yg = 0.0;
    f64 zg = 0.0;
    for (u64 k = 0; k < bf->n_exponents; ++k)
    {
        f64 alpha = bf->exponents[k];
        f64 value = bf->coefficients[k] *
                    bf->normalization_factors[k] *
                    pow(x_x0, bf->l) *
                    pow(y_y0, bf->m) *
                    pow(z_z0, bf->n) *
                    exp(-(alpha * r_sq));
        xg += value * (bf->l / x_x0 - 2 * alpha * x_x0);
        yg += value * (bf->m / y_y0 - 2 * alpha * y_y0);
        zg += value * (bf->n / z_z0 - 2 * alpha * z_z0);
    }
    *x = xg;
    *y = yg;
    *z = zg;
}

/* calculates the second derivative of contracted Gaussian basis function bf.
 * output: xx, yy, zz, xy, xz, yz
 * Note: yx = xy, zx = xz, zy = yz, therefore yx, zx and zy are omitted.
 */
void basis_funcs_second_derivative(struct basis_func *bf, struct vec3d *v,
                                   f64 *xx, f64 *yy, f64 *zz, f64 *xy, f64 *xz, f64 *yz)
{
    /* + 1e-100 to avoid division by zero */
    f64 x_x0 = v->x - bf->x0 + 1e-100;
    f64 y_y0 = v->y - bf->y0 + 1e-100;
    f64 z_z0 = v->z - bf->z0 + 1e-100;
    f64 r_sq = x_x0 * x_x0 + y_y0 * y_y0 + z_z0 * z_z0;

    f64 x_x0_sq = x_x0 * x_x0;
    f64 y_y0_sq = y_y0 * y_y0;
    f64 z_z0_sq = z_z0 * z_z0;

    f64 x_x0_y_y0 = x_x0 * y_y0;
    f64 x_x0_z_z0 = x_x0 * z_z0;
    f64 y_y0_z_z0 = y_y0 * z_z0;

    f64 xxg = 0.0;
    f64 yyg = 0.0;
    f64 zzg = 0.0;
    f64 xyg = 0.0;
    f64 xzg = 0.0;
    f64 yzg = 0.0;
    for (u64 k = 0; k < bf->n_exponents; ++k)
    {
        f64 alpha = bf->exponents[k];
        f64 value = bf->coefficients[k] *
                    bf->normalization_factors[k] *
                    pow(x_x0, bf->l) *
                    pow(y_y0, bf->m) *
                    pow(z_z0, bf->n) *
                    exp(-(alpha * r_sq));

        f64 xx_prefactor = bf->l * bf->l - bf->l * (4 * alpha * x_x0_sq + 1) + 2 * alpha * (2 * alpha * x_x0_sq - 1) * x_x0_sq;
        f64 yy_prefactor = bf->m * bf->m - bf->m * (4 * alpha * y_y0_sq + 1) + 2 * alpha * (2 * alpha * y_y0_sq - 1) * y_y0_sq;
        f64 zz_prefactor = bf->n * bf->n - bf->n * (4 * alpha * z_z0_sq + 1) + 2 * alpha * (2 * alpha * z_z0_sq - 1) * z_z0_sq;

        f64 xy_prefactor = (2 * alpha * x_x0_sq - bf->l) * (2 * alpha * y_y0_sq - bf->m);
        f64 xz_prefactor = (2 * alpha * x_x0_sq - bf->l) * (2 * alpha * z_z0_sq - bf->n);
        f64 yz_prefactor = (2 * alpha * y_y0_sq - bf->m) * (2 * alpha * z_z0_sq - bf->n);

        xxg += xx_prefactor * value / x_x0_sq;
        yyg += yy_prefactor * value / y_y0_sq;
        zzg += zz_prefactor * value / z_z0_sq;

        xyg += xy_prefactor * value / x_x0_y_y0;
        xzg += xz_prefactor * value / x_x0_z_z0;
        yzg += yz_prefactor * value / y_y0_z_z0;
    }
    *xx = xxg;
    *yy = yyg;
    *zz = zzg;
    *xy = xyg;
    *xz = xzg;
    *yz = yzg;
}

f64 basis_func_laplacian(struct basis_func *bf, struct vec3d *v)
{
    /* + 1e-100 to avoid division by zero */
    f64 x_x0 = v->x - bf->x0 + 1e-100;
    f64 y_y0 = v->y - bf->y0 + 1e-100;
    f64 z_z0 = v->z - bf->z0 + 1e-100;
    f64 r_sq = x_x0 * x_x0 + y_y0 * y_y0 + z_z0 * z_z0;

    f64 x_x0_sq = x_x0 * x_x0;
    f64 y_y0_sq = y_y0 * y_y0;
    f64 z_z0_sq = z_z0 * z_z0;

    f64 result = 0.0;
    for (u64 k = 0; k < bf->n_exponents; ++k)
    {
        f64 alpha = bf->exponents[k];
        f64 value = bf->coefficients[k] *
                    bf->normalization_factors[k] *
                    pow(x_x0, bf->l) *
                    pow(y_y0, bf->m) *
                    pow(z_z0, bf->n) *
                    exp(-(alpha * r_sq));

        f64 xx_prefactor = bf->l * bf->l - bf->l * (4 * alpha * x_x0_sq + 1) + 2 * alpha * (2 * alpha * x_x0_sq - 1) * x_x0_sq;
        f64 yy_prefactor = bf->m * bf->m - bf->m * (4 * alpha * y_y0_sq + 1) + 2 * alpha * (2 * alpha * y_y0_sq - 1) * y_y0_sq;
        f64 zz_prefactor = bf->n * bf->n - bf->n * (4 * alpha * z_z0_sq + 1) + 2 * alpha * (2 * alpha * z_z0_sq - 1) * z_z0_sq;

        result += xx_prefactor * value / x_x0_sq;
        result += yy_prefactor * value / y_y0_sq;
        result += zz_prefactor * value / z_z0_sq;
    }
    return result;
}

void basis_funcs_third_derivative(struct basis_func *bf, struct vec3d *v,
                                  f64 *xxx, f64 *xyy, f64 *xzz,
                                  f64 *yyy, f64 *yxx, f64 *yzz,
                                  f64 *zzz, f64 *zxx, f64 *zyy)
{
    /* + 1e-60 to avoid division by zero */
    f64 x_x0 = v->x - bf->x0 + 1e-60;
    f64 y_y0 = v->y - bf->y0 + 1e-60;
    f64 z_z0 = v->z - bf->z0 + 1e-60;
    f64 r_sq = x_x0 * x_x0 + y_y0 * y_y0 + z_z0 * z_z0;

    f64 x_x0_sq = x_x0 * x_x0;
    f64 y_y0_sq = y_y0 * y_y0;
    f64 z_z0_sq = z_z0 * z_z0;

    f64 x_x0_3 = x_x0_sq * x_x0;
    f64 y_y0_3 = y_y0_sq * y_y0;
    f64 z_z0_3 = z_z0_sq * z_z0;

    f64 x_x0_4 = x_x0_sq * x_x0_sq;
    f64 y_y0_4 = y_y0_sq * y_y0_sq;
    f64 z_z0_4 = z_z0_sq * z_z0_sq;

    f64 xxx_ = 0.0;
    f64 xyy_ = 0.0;
    f64 xzz_ = 0.0;
    f64 yxx_ = 0.0;
    f64 yyy_ = 0.0;
    f64 yzz_ = 0.0;
    f64 zxx_ = 0.0;
    f64 zyy_ = 0.0;
    f64 zzz_ = 0.0;

    for (u64 k = 0; k < bf->n_exponents; ++k)
    {
        f64 alpha = bf->exponents[k];
        f64 value = bf->coefficients[k] *
                    bf->normalization_factors[k] *
                    pow(x_x0, bf->l) *
                    pow(y_y0, bf->m) *
                    pow(z_z0, bf->n) *
                    exp(-(alpha * r_sq));

        f64 alpha_sq = alpha * alpha;

        f64 xxx_prefactor = bf->l * bf->l * bf->l - 3 * bf->l * bf->l * (2 * alpha * x_x0_sq + 1) + 2 * bf->l * (6 * alpha_sq * x_x0_4 + 1) - 4 * alpha_sq * (2 * alpha * x_x0_sq - 3) * x_x0_4;
        f64 yyy_prefactor = bf->m * bf->m * bf->m - 3 * bf->m * bf->m * (2 * alpha * y_y0_sq + 1) + 2 * bf->m * (6 * alpha_sq * y_y0_4 + 1) - 4 * alpha_sq * (2 * alpha * y_y0_sq - 3) * y_y0_4;
        f64 zzz_prefactor = bf->n * bf->n * bf->n - 3 * bf->n * bf->n * (2 * alpha * z_z0_sq + 1) + 2 * bf->n * (6 * alpha_sq * z_z0_4 + 1) - 4 * alpha_sq * (2 * alpha * z_z0_sq - 3) * z_z0_4;
        xxx_ += xxx_prefactor * value / x_x0_3;
        yyy_ += yyy_prefactor * value / y_y0_3;
        zzz_ += zzz_prefactor * value / z_z0_3;

        f64 xx_prefactor = bf->l * bf->l - bf->l * (4 * alpha * x_x0_sq + 1) + 2 * alpha * (2 * alpha * x_x0_sq - 1) * x_x0_sq;
        f64 yy_prefactor = bf->m * bf->m - bf->m * (4 * alpha * y_y0_sq + 1) + 2 * alpha * (2 * alpha * y_y0_sq - 1) * y_y0_sq;
        f64 zz_prefactor = bf->n * bf->n - bf->n * (4 * alpha * z_z0_sq + 1) + 2 * alpha * (2 * alpha * z_z0_sq - 1) * z_z0_sq;

        xyy_ += (bf->l - 2 * alpha * x_x0_sq) * yy_prefactor / (x_x0 * y_y0_sq);
        xzz_ += (bf->l - 2 * alpha * x_x0_sq) * zz_prefactor / (x_x0 * z_z0_sq);

        yxx_ += (bf->m - 2 * alpha * y_y0_sq) * xx_prefactor / (y_y0 * x_x0_sq);
        yzz_ += (bf->m - 2 * alpha * y_y0_sq) * zz_prefactor / (y_y0 * z_z0_sq);

        zxx_ += (bf->n - 2 * alpha * z_z0_sq) * xx_prefactor / (z_z0 * x_x0_sq);
        zyy_ += (bf->n - 2 * alpha * z_z0_sq) * yy_prefactor / (z_z0 * y_y0_sq);
    }

    *xxx = xxx_;
    *xyy = xyy_;
    *xzz = xzz_;
    *yxx = yxx_;
    *yyy = yyy_;
    *yzz = yzz_;
    *zxx = zxx_;
    *zyy = zyy_;
    *zzz = zzz_;
}

void print_basis_func(struct basis_func *bf)
{
    printf("center: (%.6e %.6e %.6e)\n", bf->x0, bf->y0, bf->z0);
    printf("l: %lu m: %lu n: %lu n_exponents: %lu\n", bf->l, bf->m, bf->n, bf->n_exponents);

    for (u64 k = 0; k < bf->n_exponents; ++k)
    {
        printf("%lu: coeff:%.6e exponent:%.6e norm_factor:%.6e\n", k, bf->coefficients[k], bf->exponents[k], bf->normalization_factors[k]);
    }
}

void print_basis_funcs_buffer(const char *buffer)
{
    u64 *p = (u64 *)buffer;
    u64 n_elements = *p;
    ++p;

    printf("\n");
    printf("n_elements: %lu\n\n", n_elements);
    for (u64 i = 0; i < n_elements; ++i)
    {
        u64 atomic_num = *p;
        ++p;
        printf("atomic_num: %lu\n", atomic_num);
        u64 n_basis_funcs = *p;
        ++p;
        printf("n_basis_funcs: %lu\n", n_basis_funcs);
        for (u64 j = 0; j < n_basis_funcs; ++j)
        {
            u64 l = *p;
            ++p;
            u64 m = *p;
            ++p;
            u64 n = *p;
            ++p;

            printf("angular_momentum: %lu %lu %lu\n", l, m, n);

            u64 n_exponents = *p;
            ++p;
            printf("n_exponents: %lu\n", n_exponents);
            printf("exponents   :");
            for (u64 k = 0; k < n_exponents; ++k)
            {
                f64 exponent = *((f64 *)p);
                ++p;
                printf("%19.12e ", exponent);
            }
            printf("\ncoefficients:");
            for (u64 k = 0; k < n_exponents; ++k)
            {
                f64 coefficient = *((f64 *)p);
                ++p;
                printf("%19.12e ", coefficient);
            }
            printf("\n");
        }
        printf("\n");
    }
}

#ifdef MODULE_TEST
int main(void)
{
    if (1)
    {
        printf("%.17f\n", normalize_gaussian_primitive(1, 1, 1, 1));
        printf("%.17f\n", normalize_gaussian_primitive(0.1688554, 0, 0, 0));
        printf("%.17f\n", normalize_gaussian_primitive(5.0331513, 1, 0, 0));

        u64 n_primitives = 3;
        u64 l = 1;
        u64 m = 0;
        u64 n = 0;
        double exponents[] = {5.0331513, 1.1695961, 0.380389};
        double coefficients[] = {0.15591627, 0.60768372, 0.39195739};
        double norms[] = {10.745832583524919, 1.7337440244052482, 0.42581898941828655};

        printf("%.17f\n", normalize_contracted_gaussian_func(n_primitives, l, m, n, exponents, coefficients, norms));
    }

    if (1)
    {
        f64 exponents[] = {1.0, 2.0};
        f64 coefficients[] = {0.5, 0.5};
        f64 normalization_factors[] = {1.0, 1.0};

        struct basis_func bf;
        bf.l = 1;
        bf.m = 1;
        bf.n = 1;
        bf.n_exponents = 2;
        bf.coefficients = coefficients;
        bf.exponents = exponents;
        bf.normalization_factors = normalization_factors;
        bf.x0 = 0.5;
        bf.y0 = 0.5;
        bf.z0 = 0.5;

        struct vec3d v;
        f64 x, y, z, xx, yy, zz, xy, xz, yz;
        for (u64 i = 0; i < 10; ++i)
        {
            v.x = 0.2 + i * 0.1;
            v.y = 1.0 + i * 0.1;
            v.z = 1.2 + i * 0.1;

            printf("x,y,z: %.4f, %.4f, %.4f\n", v.x, v.y, v.z);
            basis_funcs_first_derivative(&bf, &v, &x, &y, &z);
            printf("first derivative x,y,z: %.16f, %.16f, %.16f\n", x, y, z);

            basis_funcs_second_derivative(&bf, &v, &xx, &yy, &zz, &xy, &xz, &yz);
            printf("second derivative xx,yy,zz | xy,xz,yz: %.16f, %.16f, %.16f, | %.16f, %.16f, %.16f\n", xx, yy, zz, xy, xz, yz);

            printf("laplacian: %.16f\n\n", basis_func_laplacian(&bf, &v));
        }
    }
    return 0;
}
#endif
