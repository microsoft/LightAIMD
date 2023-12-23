/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <math.h>
#include <stddef.h>
#include "numeric_types.h"
#include "cuda_helper.h"

__device__ static f64 hermite_coef_n5_5_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_n4_4_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_n4_5_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_n4_5_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_n3_3_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_n3_4_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_n3_4_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_n3_5_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_n3_5_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_n3_5_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_n2_2_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_n2_3_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_n2_3_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_n2_4_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_n2_4_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_n2_4_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_n2_5_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_n2_5_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_n2_5_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_n2_5_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_n1_1_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_n1_2_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_n1_2_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_n1_3_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_n1_3_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_n1_3_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_n1_4_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_n1_4_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_n1_4_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_n1_4_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_n1_5_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_n1_5_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_n1_5_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_n1_5_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_n1_5_4(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_0_1_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v2 = 1.0 / v2;
    return _v2 * v3 * v5 * v6;
}

__device__ static f64 hermite_coef_0_1_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 5.0000000000000000e-01 * _v4 * v6;
}

__device__ static f64 hermite_coef_0_2_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (_v2 * _v2 * v3 * v3 * v5 * v5 * v6 + 5.0000000000000000e-01 * _v4 * v6);
}

__device__ static f64 hermite_coef_0_2_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return _v4 * _v2 * v3 * v5 * v6;
}

__device__ static f64 hermite_coef_0_2_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 2.5000000000000000e-01 * _v4 * _v4 * v6;
}

__device__ static f64 hermite_coef_0_3_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (_v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 1.5000000000000000e+00 * _v4 * _v2 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_0_3_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (1.5000000000000000e+00 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * v6);
}

__device__ static f64 hermite_coef_0_3_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return 7.5000000000000000e-01 * _v4 * _v4 * _v2 * v3 * v5 * v6;
}

__device__ static f64 hermite_coef_0_3_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 1.2500000000000000e-01 * _v4 * _v4 * _v4 * v6;
}

__device__ static f64 hermite_coef_0_4_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (_v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 3.0000000000000000e+00 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * v6);
}

__device__ static f64 hermite_coef_0_4_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (2.0000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 3.0000000000000000e+00 * _v4 * _v4 * _v2 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_0_4_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (1.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * _v4 * v6);
}

__device__ static f64 hermite_coef_0_4_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return 5.0000000000000000e-01 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6;
}

__device__ static f64 hermite_coef_0_4_4(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 6.2500000000000000e-02 * _v4 * _v4 * _v4 * _v4 * v6;
}

__device__ static f64 hermite_coef_0_5_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (_v2 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 5.0000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 3.7500000000000000e+00 * _v4 * _v4 * _v2 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_0_5_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (2.5000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 7.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + 1.8750000000000000e+00 * _v4 * _v4 * _v4 * v6);
}

__device__ static f64 hermite_coef_0_5_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (2.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 3.7500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_0_5_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (1.2500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + 6.2500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * v6);
}

__device__ static f64 hermite_coef_0_5_4(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return 3.1250000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6;
}

__device__ static f64 hermite_coef_0_5_5(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 3.1250000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * v6;
}

__device__ static f64 hermite_coef_1_n1_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_1_0_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    return -1.0000000000000000e+00 * _v1 * v3 * v5 * v6;
}

__device__ static f64 hermite_coef_1_0_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 5.0000000000000000e-01 * _v4 * v6;
}

__device__ static f64 hermite_coef_1_1_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.0000000000000000e+00 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 5.0000000000000000e-01 * _v4 * v6);
}

__device__ static f64 hermite_coef_1_1_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-5.0000000000000000e-01 * _v4 * _v1 * v3 * v5 * v6 + 5.0000000000000000e-01 * _v4 * _v2 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_1_1_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 2.5000000000000000e-01 * _v4 * _v4 * v6;
}

__device__ static f64 hermite_coef_1_2_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.0000000000000000e+00 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + _v4 * _v2 * v3 * v5 * v6 + -5.0000000000000000e-01 * _v4 * _v1 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_1_2_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.0000000000000000e+00 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * v6 + 5.0000000000000000e-01 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_1_2_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-2.5000000000000000e-01 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 5.0000000000000000e-01 * _v4 * _v4 * _v2 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_1_2_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 1.2500000000000000e-01 * _v4 * _v4 * _v4 * v6;
}

__device__ static f64 hermite_coef_1_3_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.0000000000000000e+00 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 1.5000000000000000e+00 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -1.5000000000000000e+00 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * v6);
}

__device__ static f64 hermite_coef_1_3_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.5000000000000000e+00 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 2.2500000000000000e+00 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -7.5000000000000000e-01 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 5.0000000000000000e-01 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_1_3_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-7.5000000000000000e-01 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * _v4 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_1_3_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.2500000000000000e-01 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 3.7500000000000000e-01 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_1_3_4(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 6.2500000000000000e-02 * _v4 * _v4 * _v4 * _v4 * v6;
}

__device__ static f64 hermite_coef_1_4_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.0000000000000000e+00 * _v2 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 2.0000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -3.0000000000000000e+00 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 3.0000000000000000e+00 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -7.5000000000000000e-01 * _v4 * _v4 * _v1 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_1_4_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-2.0000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 4.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -3.0000000000000000e+00 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 1.8750000000000000e+00 * _v4 * _v4 * _v4 * v6 + 5.0000000000000000e-01 * _v4 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_1_4_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 3.0000000000000000e+00 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -7.5000000000000000e-01 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_1_4_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-5.0000000000000000e-01 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 6.2500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_1_4_4(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-6.2500000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 2.5000000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_1_4_5(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 3.1250000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * v6;
}

__device__ static f64 hermite_coef_1_5_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.0000000000000000e+00 * _v2 * _v2 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 2.5000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -5.0000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 7.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -3.7500000000000000e+00 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 1.8750000000000000e+00 * _v4 * _v4 * _v4 * v6);
}

__device__ static f64 hermite_coef_1_5_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-2.5000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 7.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -7.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 9.3750000000000000e+00 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -1.8750000000000000e+00 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 5.0000000000000000e-01 * _v4 * _v2 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_1_5_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-2.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 7.5000000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -3.7500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 2.8125000000000000e+00 * _v4 * _v4 * _v4 * _v4 * v6 + 1.2500000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_1_5_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.2500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 3.1250000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -6.2500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 1.2500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_1_5_4(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-3.1250000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 4.6875000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * v6 + 6.2500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_1_5_5(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-3.1250000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 1.5625000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_1_5_6(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 1.5625000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6;
}

__device__ static f64 hermite_coef_2_n2_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_2_n1_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_2_n1_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_2_0_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v4 = 1.0 / v4;
    return (_v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 5.0000000000000000e-01 * _v4 * v6);
}

__device__ static f64 hermite_coef_2_0_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v4 = 1.0 / v4;
    return -1.0000000000000000e+00 * _v4 * _v1 * v3 * v5 * v6;
}

__device__ static f64 hermite_coef_2_0_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 2.5000000000000000e-01 * _v4 * _v4 * v6;
}

__device__ static f64 hermite_coef_2_1_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (_v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 5.0000000000000000e-01 * _v4 * _v2 * v3 * v5 * v6 + -1.0000000000000000e+00 * _v4 * _v1 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_2_1_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (5.0000000000000000e-01 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * v6 + -1.0000000000000000e+00 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_2_1_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-5.0000000000000000e-01 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 2.5000000000000000e-01 * _v4 * _v4 * _v2 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_2_1_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 1.2500000000000000e-01 * _v4 * _v4 * _v4 * v6;
}

__device__ static f64 hermite_coef_2_2_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (_v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 5.0000000000000000e-01 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -2.0000000000000000e+00 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 5.0000000000000000e-01 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * v6);
}

__device__ static f64 hermite_coef_2_2_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (_v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 1.5000000000000000e+00 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -1.5000000000000000e+00 * _v4 * _v4 * _v1 * v3 * v5 * v6 + -1.0000000000000000e+00 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_2_2_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (2.5000000000000000e-01 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * _v4 * v6 + -1.0000000000000000e+00 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 2.5000000000000000e-01 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_2_2_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-2.5000000000000000e-01 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 2.5000000000000000e-01 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_2_2_4(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 6.2500000000000000e-02 * _v4 * _v4 * _v4 * _v4 * v6;
}

__device__ static f64 hermite_coef_2_3_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (_v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 5.0000000000000000e-01 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -3.0000000000000000e+00 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 1.5000000000000000e+00 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 2.2500000000000000e+00 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -1.5000000000000000e+00 * _v4 * _v4 * _v1 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_2_3_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (1.5000000000000000e+00 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 2.2500000000000000e+00 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -4.5000000000000000e+00 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 1.8750000000000000e+00 * _v4 * _v4 * _v4 * v6 + -1.0000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_2_3_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (7.5000000000000000e-01 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 2.2500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -1.5000000000000000e+00 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + -1.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 2.5000000000000000e-01 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_2_3_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (1.2500000000000000e-01 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 6.2500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * v6 + -7.5000000000000000e-01 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 3.7500000000000000e-01 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_2_3_4(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.2500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 1.8750000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_2_3_5(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 3.1250000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * v6;
}

__device__ static f64 hermite_coef_2_4_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (_v2 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 5.0000000000000000e-01 * _v4 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -4.0000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 3.0000000000000000e+00 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 4.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -6.0000000000000000e+00 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 1.8750000000000000e+00 * _v4 * _v4 * _v4 * v6);
}

__device__ static f64 hermite_coef_2_4_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (2.0000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 3.0000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -9.0000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 3.0000000000000000e+00 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 7.5000000000000000e+00 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -3.7500000000000000e+00 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + -1.0000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_2_4_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (1.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 4.5000000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -6.0000000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 2.8125000000000000e+00 * _v4 * _v4 * _v4 * _v4 * v6 + -2.0000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 2.5000000000000000e-01 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_2_4_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (5.0000000000000000e-01 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 2.5000000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -1.2500000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + -1.5000000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 5.0000000000000000e-01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_2_4_4(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (6.2500000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 4.6875000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * v6 + -5.0000000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 3.7500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_2_4_5(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-6.2500000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 1.2500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_2_4_6(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 1.5625000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6;
}

__device__ static f64 hermite_coef_2_5_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (_v2 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 5.0000000000000000e-01 * _v4 * _v2 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -5.0000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 5.0000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 7.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -1.5000000000000000e+01 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 3.7500000000000000e+00 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 9.3750000000000000e+00 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -3.7500000000000000e+00 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_2_5_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (2.5000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 3.7500000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -1.5000000000000000e+01 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 7.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 1.8750000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -1.8750000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 1.8750000000000000e+00 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 6.5625000000000000e+00 * _v4 * _v4 * _v4 * _v4 * v6 + -1.0000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_2_5_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (2.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 7.5000000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -1.5000000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 3.7500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 1.4062500000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -5.6250000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + -2.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 2.5000000000000000e-01 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_2_5_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (1.2500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 6.2500000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -6.2500000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 6.2500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 3.2812500000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * v6 + -2.5000000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 6.2500000000000000e-01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_2_5_4(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (3.1250000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 2.3437500000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -9.3750000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + -1.2500000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 6.2500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_2_5_5(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (3.1250000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 3.2812500000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6 + -3.1250000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 3.1250000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_2_5_6(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-3.1250000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 7.8125000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_2_5_7(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 7.8125000000000000e-03 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6;
}

__device__ static f64 hermite_coef_3_n3_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_3_n2_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_3_n2_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_3_n1_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_3_n1_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_3_n1_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_3_0_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v4 = 1.0 / v4;
    return (-1.0000000000000000e+00 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -1.5000000000000000e+00 * _v4 * _v1 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_3_0_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v4 = 1.0 / v4;
    return (1.5000000000000000e+00 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * v6);
}

__device__ static f64 hermite_coef_3_0_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v4 = 1.0 / v4;
    return -7.5000000000000000e-01 * _v4 * _v4 * _v1 * v3 * v5 * v6;
}

__device__ static f64 hermite_coef_3_0_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 1.2500000000000000e-01 * _v4 * _v4 * _v4 * v6;
}

__device__ static f64 hermite_coef_3_1_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.0000000000000000e+00 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -1.5000000000000000e+00 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 1.5000000000000000e+00 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * v6);
}

__device__ static f64 hermite_coef_3_1_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-5.0000000000000000e-01 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -2.2500000000000000e+00 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 1.5000000000000000e+00 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * _v2 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_3_1_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (7.5000000000000000e-01 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * _v4 * v6 + -7.5000000000000000e-01 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_3_1_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-3.7500000000000000e-01 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 1.2500000000000000e-01 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_3_1_4(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 6.2500000000000000e-02 * _v4 * _v4 * _v4 * _v4 * v6;
}

__device__ static f64 hermite_coef_3_2_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.0000000000000000e+00 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -1.5000000000000000e+00 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 3.0000000000000000e+00 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 1.5000000000000000e+00 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -5.0000000000000000e-01 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -2.2500000000000000e+00 * _v4 * _v4 * _v1 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_3_2_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.0000000000000000e+00 * _v4 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -4.5000000000000000e+00 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 2.2500000000000000e+00 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 1.8750000000000000e+00 * _v4 * _v4 * _v4 * v6 + 1.5000000000000000e+00 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_3_2_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-2.5000000000000000e-01 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -2.2500000000000000e+00 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 1.5000000000000000e+00 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 1.5000000000000000e+00 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -7.5000000000000000e-01 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_3_2_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (3.7500000000000000e-01 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 6.2500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * v6 + -7.5000000000000000e-01 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 1.2500000000000000e-01 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_3_2_4(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.8750000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 1.2500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_3_2_5(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 3.1250000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * v6;
}

__device__ static f64 hermite_coef_3_3_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.0000000000000000e+00 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -1.5000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 4.5000000000000000e+00 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 2.2500000000000000e+00 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -1.5000000000000000e+00 * _v4 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -6.7500000000000000e+00 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 2.2500000000000000e+00 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 1.8750000000000000e+00 * _v4 * _v4 * _v4 * v6);
}

__device__ static f64 hermite_coef_3_3_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.5000000000000000e+00 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -6.7500000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 6.7500000000000000e+00 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 5.6250000000000000e+00 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -7.5000000000000000e-01 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -5.6250000000000000e+00 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 1.5000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_3_3_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-7.5000000000000000e-01 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -6.7500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 2.2500000000000000e+00 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 2.8125000000000000e+00 * _v4 * _v4 * _v4 * _v4 * v6 + 2.2500000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 2.2500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -7.5000000000000000e-01 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_3_3_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.2500000000000000e-01 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -1.8750000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 1.1250000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 1.8750000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -1.1250000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 1.2500000000000000e-01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_3_3_4(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (1.8750000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 4.6875000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * v6 + -5.6250000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 1.8750000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_3_3_5(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-9.3750000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 9.3750000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_3_3_6(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 1.5625000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6;
}

__device__ static f64 hermite_coef_3_4_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.0000000000000000e+00 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -1.5000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 6.0000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 3.0000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -3.0000000000000000e+00 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -1.3500000000000000e+01 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 9.0000000000000000e+00 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 7.5000000000000000e+00 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -7.5000000000000000e-01 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -5.6250000000000000e+00 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_3_4_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-2.0000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -9.0000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 1.3500000000000000e+01 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 1.1250000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -3.0000000000000000e+00 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -2.2500000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 5.6250000000000000e+00 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 6.5625000000000000e+00 * _v4 * _v4 * _v4 * _v4 * v6 + 1.5000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_3_4_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -1.3500000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 9.0000000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 1.1250000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -7.5000000000000000e-01 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -8.4375000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 3.0000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 3.0000000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -7.5000000000000000e-01 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_3_4_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-5.0000000000000000e-01 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -7.5000000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 1.8750000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 3.2812500000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * v6 + 2.2500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 3.7500000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -1.5000000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 1.2500000000000000e-01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_3_4_4(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-6.2500000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -1.4062500000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 1.8750000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -1.1250000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 2.5000000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_3_4_5(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (9.3750000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 3.2812500000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6 + -3.7500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 1.8750000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_3_4_6(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-4.6875000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 6.2500000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_3_4_7(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 7.8125000000000000e-03 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6;
}

__device__ static f64 hermite_coef_3_5_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.0000000000000000e+00 * _v2 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -1.5000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 7.5000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 3.7500000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -5.0000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -2.2500000000000000e+01 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 2.2500000000000000e+01 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 1.8750000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -3.7500000000000000e+00 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -2.8125000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 5.6250000000000000e+00 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 6.5625000000000000e+00 * _v4 * _v4 * _v4 * _v4 * v6);
}

__device__ static f64 hermite_coef_3_5_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-2.5000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -1.1250000000000000e+01 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 2.2500000000000000e+01 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 1.8750000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -7.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -5.6250000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 2.8125000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 3.2812500000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -1.8750000000000000e+00 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -1.9687500000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 1.5000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_3_5_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-2.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -2.2500000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 2.2500000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 2.8125000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -3.7500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -4.2187500000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 8.4375000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 1.3125000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * v6 + 3.7500000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 3.7500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -7.5000000000000000e-01 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_3_5_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.2500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -1.8750000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 9.3750000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 1.6406250000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -6.2500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -9.8437500000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 3.7500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 6.2500000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -1.8750000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 1.2500000000000000e-01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_3_5_4(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-3.1250000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -7.0312500000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 1.4062500000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 3.2812500000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6 + 1.8750000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 4.6875000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -1.8750000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 3.1250000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_3_5_5(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-3.1250000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -9.8437500000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 4.6875000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 1.6406250000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -9.3750000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 3.1250000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_3_5_6(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (4.6875000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 2.1875000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6 + -2.3437500000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 1.5625000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_3_5_7(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-2.3437500000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 3.9062500000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_3_5_8(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 3.9062500000000000e-03 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6;
}

__device__ static f64 hermite_coef_4_n4_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_4_n3_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_4_n3_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_4_n2_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_4_n2_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_4_n2_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_4_n1_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_4_n1_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_4_n1_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_4_n1_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_4_0_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v4 = 1.0 / v4;
    return (_v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 3.0000000000000000e+00 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * v6);
}

__device__ static f64 hermite_coef_4_0_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v4 = 1.0 / v4;
    return (-2.0000000000000000e+00 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -3.0000000000000000e+00 * _v4 * _v4 * _v1 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_4_0_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v4 = 1.0 / v4;
    return (1.5000000000000000e+00 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * _v4 * v6);
}

__device__ static f64 hermite_coef_4_0_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v4 = 1.0 / v4;
    return -5.0000000000000000e-01 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6;
}

__device__ static f64 hermite_coef_4_0_4(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 6.2500000000000000e-02 * _v4 * _v4 * _v4 * _v4 * v6;
}

__device__ static f64 hermite_coef_4_1_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (_v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 3.0000000000000000e+00 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -2.0000000000000000e+00 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -3.0000000000000000e+00 * _v4 * _v4 * _v1 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_4_1_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (5.0000000000000000e-01 * _v4 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 4.5000000000000000e+00 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 1.8750000000000000e+00 * _v4 * _v4 * _v4 * v6 + -2.0000000000000000e+00 * _v4 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -3.0000000000000000e+00 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_4_1_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.0000000000000000e+00 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -3.0000000000000000e+00 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 1.5000000000000000e+00 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_4_1_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (7.5000000000000000e-01 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 6.2500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * v6 + -5.0000000000000000e-01 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_4_1_4(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-2.5000000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 6.2500000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_4_1_5(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 3.1250000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * v6;
}

__device__ static f64 hermite_coef_4_2_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (_v2 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 3.0000000000000000e+00 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -4.0000000000000000e+00 * _v4 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -6.0000000000000000e+00 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 5.0000000000000000e-01 * _v4 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 4.5000000000000000e+00 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 1.8750000000000000e+00 * _v4 * _v4 * _v4 * v6);
}

__device__ static f64 hermite_coef_4_2_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (_v4 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 9.0000000000000000e+00 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 3.7500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -3.0000000000000000e+00 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -7.5000000000000000e+00 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + -2.0000000000000000e+00 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -3.0000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_4_2_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (2.5000000000000000e-01 * _v4 * _v4 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 4.5000000000000000e+00 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 2.8125000000000000e+00 * _v4 * _v4 * _v4 * _v4 * v6 + -2.0000000000000000e+00 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -6.0000000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 1.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_4_2_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-5.0000000000000000e-01 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -2.5000000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 1.5000000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 1.2500000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -5.0000000000000000e-01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_4_2_4(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (3.7500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 4.6875000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * v6 + -5.0000000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 6.2500000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_4_2_5(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.2500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 6.2500000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_4_2_6(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 1.5625000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6;
}

__device__ static f64 hermite_coef_4_3_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (_v2 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 3.0000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -6.0000000000000000e+00 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -9.0000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 1.5000000000000000e+00 * _v4 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 1.3500000000000000e+01 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 5.6250000000000000e+00 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -3.0000000000000000e+00 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -7.5000000000000000e+00 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_4_3_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (1.5000000000000000e+00 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 1.3500000000000000e+01 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 5.6250000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -9.0000000000000000e+00 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -2.2500000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 1.1250000000000000e+01 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 6.5625000000000000e+00 * _v4 * _v4 * _v4 * _v4 * v6 + -2.0000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -3.0000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_4_3_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (7.5000000000000000e-01 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 1.3500000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 8.4375000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -3.0000000000000000e+00 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -1.1250000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + -3.0000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -9.0000000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 1.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_4_3_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (1.2500000000000000e-01 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 3.7500000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 3.2812500000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * v6 + -1.5000000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -7.5000000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 2.2500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 1.8750000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -5.0000000000000000e-01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_4_3_4(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-2.5000000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -1.8750000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 1.1250000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 1.4062500000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -7.5000000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 6.2500000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_4_3_5(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (1.8750000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 3.2812500000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6 + -3.7500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 9.3750000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_4_3_6(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-6.2500000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 4.6875000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_4_3_7(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 7.8125000000000000e-03 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6;
}

__device__ static f64 hermite_coef_4_4_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (_v2 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 3.0000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -8.0000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -1.2000000000000000e+01 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 3.0000000000000000e+00 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 2.7000000000000000e+01 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 1.1250000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -1.2000000000000000e+01 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -3.0000000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 1.1250000000000000e+01 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 6.5625000000000000e+00 * _v4 * _v4 * _v4 * _v4 * v6);
}

__device__ static f64 hermite_coef_4_4_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (2.0000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 1.8000000000000000e+01 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 7.5000000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -1.8000000000000000e+01 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -4.5000000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 3.0000000000000000e+00 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 4.5000000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 2.6250000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -7.5000000000000000e+00 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -2.6250000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + -2.0000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -3.0000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_4_4_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (1.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 2.7000000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 1.6875000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -1.2000000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -4.5000000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 1.6875000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 1.3125000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * v6 + -4.0000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -1.2000000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 1.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_4_4_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (5.0000000000000000e-01 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 1.5000000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 1.3125000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -2.5000000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -1.3125000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + -3.0000000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -1.5000000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 3.0000000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 2.5000000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -5.0000000000000000e-01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_4_4_4(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (6.2500000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 2.8125000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 3.2812500000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6 + -1.0000000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -7.5000000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 2.2500000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 2.8125000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -1.0000000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 6.2500000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_4_4_5(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.2500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -1.3125000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 1.3125000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -7.5000000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 1.2500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_4_4_6(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (9.3750000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 2.1875000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6 + -2.5000000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 9.3750000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_4_4_7(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-3.1250000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 3.1250000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_4_4_8(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 3.9062500000000000e-03 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6;
}

__device__ static f64 hermite_coef_4_5_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (_v2 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 3.0000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -1.0000000000000000e+01 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -1.5000000000000000e+01 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 5.0000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 4.5000000000000000e+01 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 1.8750000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -3.0000000000000000e+01 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -7.5000000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 3.7500000000000000e+00 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 5.6250000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 3.2812500000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -7.5000000000000000e+00 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -2.6250000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_4_5_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (2.5000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 2.2500000000000000e+01 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 9.3750000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -3.0000000000000000e+01 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -7.5000000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 7.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 1.1250000000000000e+02 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 6.5625000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -3.7500000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -1.3125000000000000e+02 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 1.8750000000000000e+00 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 3.9375000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 2.9531250000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * v6 + -2.0000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -3.0000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_4_5_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (2.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 4.5000000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 2.8125000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -3.0000000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -1.1250000000000000e+02 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 3.7500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 8.4375000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 6.5625000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -1.1250000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -5.2500000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + -5.0000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -1.5000000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 1.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 7.5000000000000000e-01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_4_5_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (1.2500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 3.7500000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 3.2812500000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -1.2500000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -6.5625000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 6.2500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 1.9687500000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 1.9687500000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6 + -5.0000000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -2.5000000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 3.7500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 3.1250000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -5.0000000000000000e-01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_4_5_4(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (3.1250000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 1.4062500000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 1.6406250000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -1.8750000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -1.3125000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + -2.5000000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -1.8750000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 3.7500000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 4.6875000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -1.2500000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 6.2500000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_4_5_5(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (3.1250000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 1.9687500000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 2.9531250000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6 + -6.2500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -6.5625000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 1.8750000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 3.2812500000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -1.2500000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 1.5625000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_4_5_6(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-6.2500000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -8.7500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 4.6875000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 1.0937500000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -6.2500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 1.5625000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_4_5_7(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (4.6875000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 1.4062500000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6 + -1.5625000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 7.8125000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_4_5_8(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.5625000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 1.9531250000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_4_5_9(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 1.9531250000000000e-03 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6;
}

__device__ static f64 hermite_coef_5_n5_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_5_n4_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_5_n4_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_5_n3_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_5_n3_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_5_n3_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_5_n2_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_5_n2_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_5_n2_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_5_n2_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_5_n1_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_5_n1_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_5_n1_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_5_n1_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_5_n1_4(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    return 0.0000000000000000e+00;
}

__device__ static f64 hermite_coef_5_0_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v4 = 1.0 / v4;
    return (-1.0000000000000000e+00 * _v1 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -5.0000000000000000e+00 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -3.7500000000000000e+00 * _v4 * _v4 * _v1 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_5_0_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v4 = 1.0 / v4;
    return (2.5000000000000000e+00 * _v4 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 7.5000000000000000e+00 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 1.8750000000000000e+00 * _v4 * _v4 * _v4 * v6);
}

__device__ static f64 hermite_coef_5_0_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v4 = 1.0 / v4;
    return (-2.5000000000000000e+00 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -3.7500000000000000e+00 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_5_0_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v4 = 1.0 / v4;
    return (1.2500000000000000e+00 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 6.2500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * v6);
}

__device__ static f64 hermite_coef_5_0_4(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v4 = 1.0 / v4;
    return -3.1250000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6;
}

__device__ static f64 hermite_coef_5_0_5(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 3.1250000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * v6;
}

__device__ static f64 hermite_coef_5_1_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.0000000000000000e+00 * _v2 * _v1 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -5.0000000000000000e+00 * _v4 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -3.7500000000000000e+00 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 2.5000000000000000e+00 * _v4 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 7.5000000000000000e+00 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 1.8750000000000000e+00 * _v4 * _v4 * _v4 * v6);
}

__device__ static f64 hermite_coef_5_1_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-5.0000000000000000e-01 * _v4 * _v1 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -7.5000000000000000e+00 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -9.3750000000000000e+00 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 2.5000000000000000e+00 * _v4 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 7.5000000000000000e+00 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 1.8750000000000000e+00 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_5_1_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (1.2500000000000000e+00 * _v4 * _v4 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 7.5000000000000000e+00 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 2.8125000000000000e+00 * _v4 * _v4 * _v4 * _v4 * v6 + -2.5000000000000000e+00 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -3.7500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_5_1_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.2500000000000000e+00 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -3.1250000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 1.2500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 6.2500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_5_1_4(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (6.2500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 4.6875000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * v6 + -3.1250000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_5_1_5(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.5625000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 3.1250000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_5_1_6(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 1.5625000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6;
}

__device__ static f64 hermite_coef_5_2_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.0000000000000000e+00 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -5.0000000000000000e+00 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -3.7500000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 5.0000000000000000e+00 * _v4 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 1.5000000000000000e+01 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 3.7500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -5.0000000000000000e-01 * _v4 * _v1 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -7.5000000000000000e+00 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -9.3750000000000000e+00 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_5_2_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.0000000000000000e+00 * _v4 * _v2 * _v1 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -1.5000000000000000e+01 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -1.8750000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 3.7500000000000000e+00 * _v4 * _v4 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 1.8750000000000000e+01 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 6.5625000000000000e+00 * _v4 * _v4 * _v4 * _v4 * v6 + 2.5000000000000000e+00 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 7.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 1.8750000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_5_2_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-2.5000000000000000e-01 * _v4 * _v4 * _v1 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -7.5000000000000000e+00 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -1.4062500000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 2.5000000000000000e+00 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 1.5000000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 5.6250000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -2.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -3.7500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_5_2_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (6.2500000000000000e-01 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 6.2500000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 3.2812500000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * v6 + -2.5000000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -6.2500000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 1.2500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 6.2500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_5_2_4(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-6.2500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -2.3437500000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 1.2500000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 9.3750000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -3.1250000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_5_2_5(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (3.1250000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 3.2812500000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6 + -3.1250000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 3.1250000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_5_2_6(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-7.8125000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 3.1250000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_5_2_7(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 7.8125000000000000e-03 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6;
}

__device__ static f64 hermite_coef_5_3_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.0000000000000000e+00 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -5.0000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -3.7500000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 7.5000000000000000e+00 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 2.2500000000000000e+01 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 5.6250000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -1.5000000000000000e+00 * _v4 * _v2 * _v1 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -2.2500000000000000e+01 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -2.8125000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 3.7500000000000000e+00 * _v4 * _v4 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 1.8750000000000000e+01 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 6.5625000000000000e+00 * _v4 * _v4 * _v4 * _v4 * v6);
}

__device__ static f64 hermite_coef_5_3_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.5000000000000000e+00 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -2.2500000000000000e+01 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -2.8125000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 1.1250000000000000e+01 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 5.6250000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 1.9687500000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -7.5000000000000000e-01 * _v4 * _v4 * _v1 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -1.8750000000000000e+01 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -3.2812500000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 2.5000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 7.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 1.8750000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_5_3_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-7.5000000000000000e-01 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -2.2500000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -4.2187500000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 3.7500000000000000e+00 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 2.8125000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 1.3125000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * v6 + 3.7500000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 2.2500000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 8.4375000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -2.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -3.7500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_5_3_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.2500000000000000e-01 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -6.2500000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -1.6406250000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 1.8750000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 1.8750000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 9.8437500000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -3.7500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -9.3750000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 1.2500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 6.2500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_5_3_4(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (3.1250000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 4.6875000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 3.2812500000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6 + -1.8750000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -7.0312500000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 1.8750000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 1.4062500000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -3.1250000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_5_3_5(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-3.1250000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -1.6406250000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 9.3750000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 9.8437500000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -4.6875000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 3.1250000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_5_3_6(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (1.5625000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 2.1875000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6 + -2.3437500000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 4.6875000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_5_3_7(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-3.9062500000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 2.3437500000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_5_3_8(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 3.9062500000000000e-03 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6;
}

__device__ static f64 hermite_coef_5_4_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.0000000000000000e+00 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -5.0000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -3.7500000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 1.0000000000000000e+01 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 3.0000000000000000e+01 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 7.5000000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -3.0000000000000000e+00 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -4.5000000000000000e+01 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -5.6250000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 1.5000000000000000e+01 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 7.5000000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 2.6250000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -7.5000000000000000e-01 * _v4 * _v4 * _v1 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -1.8750000000000000e+01 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -3.2812500000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_5_4_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-2.0000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -3.0000000000000000e+01 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -3.7500000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 2.2500000000000000e+01 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 1.1250000000000000e+02 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 3.9375000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -3.0000000000000000e+00 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -7.5000000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -1.3125000000000000e+02 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 9.3750000000000000e+00 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 6.5625000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 2.9531250000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * v6 + 2.5000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 7.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 1.8750000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_5_4_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -4.5000000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -8.4375000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 1.5000000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 1.1250000000000000e+02 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 5.2500000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -7.5000000000000000e-01 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -2.8125000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -6.5625000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 5.0000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 3.0000000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 1.1250000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -2.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -3.7500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_5_4_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-5.0000000000000000e-01 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -2.5000000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -6.5625000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 3.1250000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 3.2812500000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 1.9687500000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6 + 3.7500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 3.7500000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 1.9687500000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -5.0000000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -1.2500000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 1.2500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 6.2500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_5_4_4(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-6.2500000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -4.6875000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -1.6406250000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 1.2500000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 1.8750000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 1.3125000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -3.7500000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -1.4062500000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 2.5000000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 1.8750000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -3.1250000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_5_4_5(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (1.5625000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 3.2812500000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 2.9531250000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6 + -1.2500000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -6.5625000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 1.8750000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 1.9687500000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -6.2500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 3.1250000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_5_4_6(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.5625000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -1.0937500000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 6.2500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 8.7500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -4.6875000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 6.2500000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_5_4_7(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (7.8125000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 1.4062500000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6 + -1.5625000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 4.6875000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_5_4_8(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.9531250000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 1.5625000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_5_4_9(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 1.9531250000000000e-03 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6;
}

__device__ static f64 hermite_coef_5_5_0(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.0000000000000000e+00 * _v2 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -5.0000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -3.7500000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 1.2500000000000000e+01 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 3.7500000000000000e+01 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 9.3750000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -5.0000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -7.5000000000000000e+01 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -9.3750000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 3.7500000000000000e+01 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 1.8750000000000000e+02 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 6.5625000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -3.7500000000000000e+00 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -9.3750000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -1.6406250000000000e+02 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 9.3750000000000000e+00 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 6.5625000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 2.9531250000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * v6);
}

__device__ static f64 hermite_coef_5_5_1(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-2.5000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -3.7500000000000000e+01 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -4.6875000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 3.7500000000000000e+01 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 1.8750000000000000e+02 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 6.5625000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -7.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -1.8750000000000000e+02 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -3.2812500000000000e+02 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 4.6875000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 3.2812500000000000e+02 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 1.4765625000000000e+02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -1.8750000000000000e+00 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -6.5625000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -1.4765625000000000e+02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 2.5000000000000000e+00 * _v4 * _v2 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 7.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 1.8750000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_5_5_2(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-2.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -7.5000000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -1.4062500000000000e+02 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 3.7500000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 2.8125000000000000e+02 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 1.3125000000000000e+02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -3.7500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -1.4062500000000000e+02 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -3.2812500000000000e+02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 1.4062500000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 1.3125000000000000e+02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 7.3828125000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6 + 6.2500000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 3.7500000000000000e+01 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 1.4062500000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -2.5000000000000000e+00 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -3.7500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_5_5_3(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-1.2500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -6.2500000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -1.6406250000000000e+02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 1.5625000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 1.6406250000000000e+02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 9.8437500000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -6.2500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -3.2812500000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -9.8437500000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 6.2500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 6.2500000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 3.2812500000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -6.2500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -1.5625000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 1.2500000000000000e+00 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 6.2500000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_5_5_4(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-3.1250000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -2.3437500000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -8.2031250000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 2.3437500000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 3.2812500000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 2.4609375000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6 + 3.1250000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 4.6875000000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 3.2812500000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -6.2500000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + -2.3437500000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 3.1250000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6 + 2.3437500000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -3.1250000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_5_5_5(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-3.1250000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -3.2812500000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -1.4765625000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 7.8125000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 1.6406250000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 1.4765625000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -3.1250000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + -1.6406250000000000e+01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 3.1250000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 3.2812500000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -7.8125000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6 + 3.1250000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_5_5_6(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (7.8125000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 2.1875000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 2.4609375000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6 + -7.8125000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + -5.4687500000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 1.5625000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 2.1875000000000000e+00 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6 + -7.8125000000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6 + 7.8125000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v3 * v5 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_5_5_7(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-7.8125000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + -7.0312500000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 3.9062500000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 7.0312500000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6 + -3.9062500000000000e-01 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v1 * v3 * v3 * v3 * v5 * v5 * v5 * v6 + 7.8125000000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * _v2 * v3 * v3 * v3 * v5 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_5_5_8(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (3.9062500000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * _v1 * v3 * v3 * v5 * v5 * v6 + 8.7890625000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6 + -9.7656250000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v1 * v3 * v3 * v5 * v5 * v6 + 3.9062500000000000e-02 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * _v2 * v3 * v3 * v5 * v5 * v6);
}

__device__ static f64 hermite_coef_5_5_9(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v1 = 1.0 / v1;
    f64 _v2 = 1.0 / v2;
    f64 _v4 = 1.0 / v4;
    return (-9.7656250000000000e-03 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v1 * v3 * v5 * v6 + 9.7656250000000000e-03 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v2 * v3 * v5 * v6);
}

__device__ static f64 hermite_coef_5_5_10(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6)
{
    f64 _v4 = 1.0 / v4;
    return 9.7656250000000000e-04 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * _v4 * v6;
}

typedef f64 (*hermite_coef_func)(f64 v1, f64 v2, f64 v3, f64 v4, f64 v5, f64 v6);

__device__ static hermite_coef_func hermite_coef_funcs[11][11][11] =
{
    {
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_n5_5_0,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
    },
    {
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_n4_4_0,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_n4_5_0,
            hermite_coef_n4_5_1,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
    },
    {
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_n3_3_0,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_n3_4_0,
            hermite_coef_n3_4_1,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_n3_5_0,
            hermite_coef_n3_5_1,
            hermite_coef_n3_5_2,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
    },
    {
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_n2_2_0,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_n2_3_0,
            hermite_coef_n2_3_1,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_n2_4_0,
            hermite_coef_n2_4_1,
            hermite_coef_n2_4_2,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_n2_5_0,
            hermite_coef_n2_5_1,
            hermite_coef_n2_5_2,
            hermite_coef_n2_5_3,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
    },
    {
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_n1_1_0,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_n1_2_0,
            hermite_coef_n1_2_1,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_n1_3_0,
            hermite_coef_n1_3_1,
            hermite_coef_n1_3_2,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_n1_4_0,
            hermite_coef_n1_4_1,
            hermite_coef_n1_4_2,
            hermite_coef_n1_4_3,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_n1_5_0,
            hermite_coef_n1_5_1,
            hermite_coef_n1_5_2,
            hermite_coef_n1_5_3,
            hermite_coef_n1_5_4,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
    },
    {
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_0_1_0,
            hermite_coef_0_1_1,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_0_2_0,
            hermite_coef_0_2_1,
            hermite_coef_0_2_2,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_0_3_0,
            hermite_coef_0_3_1,
            hermite_coef_0_3_2,
            hermite_coef_0_3_3,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_0_4_0,
            hermite_coef_0_4_1,
            hermite_coef_0_4_2,
            hermite_coef_0_4_3,
            hermite_coef_0_4_4,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_0_5_0,
            hermite_coef_0_5_1,
            hermite_coef_0_5_2,
            hermite_coef_0_5_3,
            hermite_coef_0_5_4,
            hermite_coef_0_5_5,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
    },
    {
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_1_n1_0,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_1_0_0,
            hermite_coef_1_0_1,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_1_1_0,
            hermite_coef_1_1_1,
            hermite_coef_1_1_2,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_1_2_0,
            hermite_coef_1_2_1,
            hermite_coef_1_2_2,
            hermite_coef_1_2_3,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_1_3_0,
            hermite_coef_1_3_1,
            hermite_coef_1_3_2,
            hermite_coef_1_3_3,
            hermite_coef_1_3_4,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_1_4_0,
            hermite_coef_1_4_1,
            hermite_coef_1_4_2,
            hermite_coef_1_4_3,
            hermite_coef_1_4_4,
            hermite_coef_1_4_5,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_1_5_0,
            hermite_coef_1_5_1,
            hermite_coef_1_5_2,
            hermite_coef_1_5_3,
            hermite_coef_1_5_4,
            hermite_coef_1_5_5,
            hermite_coef_1_5_6,
            NULL,
            NULL,
            NULL,
            NULL,
        },
    },
    {
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_2_n2_0,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_2_n1_0,
            hermite_coef_2_n1_1,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_2_0_0,
            hermite_coef_2_0_1,
            hermite_coef_2_0_2,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_2_1_0,
            hermite_coef_2_1_1,
            hermite_coef_2_1_2,
            hermite_coef_2_1_3,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_2_2_0,
            hermite_coef_2_2_1,
            hermite_coef_2_2_2,
            hermite_coef_2_2_3,
            hermite_coef_2_2_4,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_2_3_0,
            hermite_coef_2_3_1,
            hermite_coef_2_3_2,
            hermite_coef_2_3_3,
            hermite_coef_2_3_4,
            hermite_coef_2_3_5,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_2_4_0,
            hermite_coef_2_4_1,
            hermite_coef_2_4_2,
            hermite_coef_2_4_3,
            hermite_coef_2_4_4,
            hermite_coef_2_4_5,
            hermite_coef_2_4_6,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_2_5_0,
            hermite_coef_2_5_1,
            hermite_coef_2_5_2,
            hermite_coef_2_5_3,
            hermite_coef_2_5_4,
            hermite_coef_2_5_5,
            hermite_coef_2_5_6,
            hermite_coef_2_5_7,
            NULL,
            NULL,
            NULL,
        },
    },
    {
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_3_n3_0,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_3_n2_0,
            hermite_coef_3_n2_1,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_3_n1_0,
            hermite_coef_3_n1_1,
            hermite_coef_3_n1_2,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_3_0_0,
            hermite_coef_3_0_1,
            hermite_coef_3_0_2,
            hermite_coef_3_0_3,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_3_1_0,
            hermite_coef_3_1_1,
            hermite_coef_3_1_2,
            hermite_coef_3_1_3,
            hermite_coef_3_1_4,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_3_2_0,
            hermite_coef_3_2_1,
            hermite_coef_3_2_2,
            hermite_coef_3_2_3,
            hermite_coef_3_2_4,
            hermite_coef_3_2_5,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_3_3_0,
            hermite_coef_3_3_1,
            hermite_coef_3_3_2,
            hermite_coef_3_3_3,
            hermite_coef_3_3_4,
            hermite_coef_3_3_5,
            hermite_coef_3_3_6,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_3_4_0,
            hermite_coef_3_4_1,
            hermite_coef_3_4_2,
            hermite_coef_3_4_3,
            hermite_coef_3_4_4,
            hermite_coef_3_4_5,
            hermite_coef_3_4_6,
            hermite_coef_3_4_7,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_3_5_0,
            hermite_coef_3_5_1,
            hermite_coef_3_5_2,
            hermite_coef_3_5_3,
            hermite_coef_3_5_4,
            hermite_coef_3_5_5,
            hermite_coef_3_5_6,
            hermite_coef_3_5_7,
            hermite_coef_3_5_8,
            NULL,
            NULL,
        },
    },
    {
        {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_4_n4_0,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_4_n3_0,
            hermite_coef_4_n3_1,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_4_n2_0,
            hermite_coef_4_n2_1,
            hermite_coef_4_n2_2,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_4_n1_0,
            hermite_coef_4_n1_1,
            hermite_coef_4_n1_2,
            hermite_coef_4_n1_3,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_4_0_0,
            hermite_coef_4_0_1,
            hermite_coef_4_0_2,
            hermite_coef_4_0_3,
            hermite_coef_4_0_4,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_4_1_0,
            hermite_coef_4_1_1,
            hermite_coef_4_1_2,
            hermite_coef_4_1_3,
            hermite_coef_4_1_4,
            hermite_coef_4_1_5,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_4_2_0,
            hermite_coef_4_2_1,
            hermite_coef_4_2_2,
            hermite_coef_4_2_3,
            hermite_coef_4_2_4,
            hermite_coef_4_2_5,
            hermite_coef_4_2_6,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_4_3_0,
            hermite_coef_4_3_1,
            hermite_coef_4_3_2,
            hermite_coef_4_3_3,
            hermite_coef_4_3_4,
            hermite_coef_4_3_5,
            hermite_coef_4_3_6,
            hermite_coef_4_3_7,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_4_4_0,
            hermite_coef_4_4_1,
            hermite_coef_4_4_2,
            hermite_coef_4_4_3,
            hermite_coef_4_4_4,
            hermite_coef_4_4_5,
            hermite_coef_4_4_6,
            hermite_coef_4_4_7,
            hermite_coef_4_4_8,
            NULL,
            NULL,
        },
        {
            hermite_coef_4_5_0,
            hermite_coef_4_5_1,
            hermite_coef_4_5_2,
            hermite_coef_4_5_3,
            hermite_coef_4_5_4,
            hermite_coef_4_5_5,
            hermite_coef_4_5_6,
            hermite_coef_4_5_7,
            hermite_coef_4_5_8,
            hermite_coef_4_5_9,
            NULL,
        },
    },
    {
        {
            hermite_coef_5_n5_0,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_5_n4_0,
            hermite_coef_5_n4_1,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_5_n3_0,
            hermite_coef_5_n3_1,
            hermite_coef_5_n3_2,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_5_n2_0,
            hermite_coef_5_n2_1,
            hermite_coef_5_n2_2,
            hermite_coef_5_n2_3,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_5_n1_0,
            hermite_coef_5_n1_1,
            hermite_coef_5_n1_2,
            hermite_coef_5_n1_3,
            hermite_coef_5_n1_4,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_5_0_0,
            hermite_coef_5_0_1,
            hermite_coef_5_0_2,
            hermite_coef_5_0_3,
            hermite_coef_5_0_4,
            hermite_coef_5_0_5,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_5_1_0,
            hermite_coef_5_1_1,
            hermite_coef_5_1_2,
            hermite_coef_5_1_3,
            hermite_coef_5_1_4,
            hermite_coef_5_1_5,
            hermite_coef_5_1_6,
            NULL,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_5_2_0,
            hermite_coef_5_2_1,
            hermite_coef_5_2_2,
            hermite_coef_5_2_3,
            hermite_coef_5_2_4,
            hermite_coef_5_2_5,
            hermite_coef_5_2_6,
            hermite_coef_5_2_7,
            NULL,
            NULL,
            NULL,
        },
        {
            hermite_coef_5_3_0,
            hermite_coef_5_3_1,
            hermite_coef_5_3_2,
            hermite_coef_5_3_3,
            hermite_coef_5_3_4,
            hermite_coef_5_3_5,
            hermite_coef_5_3_6,
            hermite_coef_5_3_7,
            hermite_coef_5_3_8,
            NULL,
            NULL,
        },
        {
            hermite_coef_5_4_0,
            hermite_coef_5_4_1,
            hermite_coef_5_4_2,
            hermite_coef_5_4_3,
            hermite_coef_5_4_4,
            hermite_coef_5_4_5,
            hermite_coef_5_4_6,
            hermite_coef_5_4_7,
            hermite_coef_5_4_8,
            hermite_coef_5_4_9,
            NULL,
        },
        {
            hermite_coef_5_5_0,
            hermite_coef_5_5_1,
            hermite_coef_5_5_2,
            hermite_coef_5_5_3,
            hermite_coef_5_5_4,
            hermite_coef_5_5_5,
            hermite_coef_5_5_6,
            hermite_coef_5_5_7,
            hermite_coef_5_5_8,
            hermite_coef_5_5_9,
            hermite_coef_5_5_10,
        },
    },
};

__device__ f64 hermite_coef_reduced(i64 i, i64 j, i64 t, f64 a, f64 b, f64 Q, f64 sum_a_b, f64 ab_reduced, f64 Kab)
{
    return hermite_coef_funcs[i + 5][j + 5][t](a, b, Q, sum_a_b, ab_reduced, Kab);
}
