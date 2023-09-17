/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <math.h>
#include <stdio.h>

#include "numeric_types.h"
#include "constants.h"
#include "scf.h"
#include "special_func.h"
#include "molecular_integral.h"

/*
 * This file contains the routines for calculating integrals based on Cartesian Gaussians.
 * In what follows, we use the following prefixes to indicate different types of variables:
 *  x0_   : the center of a Gaussian function (x dimension)
 *  y0_   : the center of a Gaussian function (y dimension)
 *  z0_   : the center of a Gaussian function (z dimension)
 *  pg_   : primitive Gaussian functions
 *  cg_   : contracted Gaussian functions
 *  amn_  : angular momentum numbers
 *  num_  : the number of items
 *  gpc_  : Gaussian product center
 *  gexp_ : Gaussian exponent
 *  dwrt_ : derivative with respect to
 * Ref: Gaussian basis set and molecular integrals (integral chapter)
 * Ref: Molecular electronic structure theory (purple book)
 */

/*
 * Calculates the Hermite expansion coefficients E.
 * The suffixes _a and _b indicates Gaussian a and b
 * num_nodes : the number of nodes in the Hermite Gaussian
 * relative_separation : the separation between the two Gaussian centers, integral chapter, eq 63; purple book eq 9.2.14
 */
__device__ static f64 hermite_coef(f64 gexp_a, f64 gexp_b, i64 amn_a, i64 amn_b, i64 num_nodes, f64 relative_separation)
{
    // integral chapter, eq 64; purple book, eq 9.2.11
    f64 gexp_a_b = gexp_a + gexp_b;
    // integral chapter, eq 66; purple book, eq 9.2.12
    f64 gexp_reduced = gexp_a * gexp_b / gexp_a_b;

    // purple book, eq 9.5.5
    if ((num_nodes < 0) || (num_nodes > (amn_a + amn_b)))
    {
        return 0.0;
    }

    if ((amn_a == 0) && (amn_b == 0) && (num_nodes == 0))
    {
        // integral chapter, eq 73; purple book, eq 9.5.8, eq 9.2.15
        return exp(-gexp_reduced * relative_separation * relative_separation);
    }

    if (amn_b == 0)
    {
        // integral chapter, eq 74
        return (1 / (2 * gexp_a_b)) * hermite_coef(gexp_a, gexp_b, amn_a - 1, amn_b, num_nodes - 1, relative_separation) - (gexp_reduced * relative_separation / gexp_a) * hermite_coef(gexp_a, gexp_b, amn_a - 1, amn_b, num_nodes, relative_separation) + (num_nodes + 1) * hermite_coef(gexp_a, gexp_b, amn_a - 1, amn_b, num_nodes + 1, relative_separation);
    }

    // integral chapter, eq 75
    return (1 / (2 * gexp_a_b)) * hermite_coef(gexp_a, gexp_b, amn_a, amn_b - 1, num_nodes - 1, relative_separation) + (gexp_reduced * relative_separation / gexp_b) * hermite_coef(gexp_a, gexp_b, amn_a, amn_b - 1, num_nodes, relative_separation) + (num_nodes + 1) * hermite_coef(gexp_a, gexp_b, amn_a, amn_b - 1, num_nodes + 1, relative_separation);
}

__device__ static f64 hermite_coef_dwrt_nuc(f64 gexp_a, f64 gexp_b, i64 amn_a, i64 amn_b, i64 num_nodes, f64 relative_separation, i64 q, i64 r)
{
    if (q == 1)
    {
        // integral chapter, eq 32, 41 or 44
        return 2 * gexp_a * hermite_coef(gexp_a, gexp_b, amn_a + 1, amn_b, num_nodes, relative_separation) - amn_a * hermite_coef(gexp_a, gexp_b, amn_a - 1, amn_b, num_nodes, relative_separation);
    }

    if (r == 1)
    {
        // integral chapter, eq 32, 41 or 44
        return 2 * gexp_b * hermite_coef(gexp_a, gexp_b, amn_a, amn_b + 1, num_nodes, relative_separation) - amn_b * hermite_coef(gexp_a, gexp_b, amn_a, amn_b - 1, num_nodes, relative_separation);
    }

    return 0.0;
}

/*
 * Hermite Coulomb integral R(P,C) that handles the electrostatic potential at C
 * due to a Gaussian charge distribution centered at P.
 * Ref: purple book, eq 9.9.9
 */
__device__ static f64 hermite_coulomb_integral(i64 t, i64 u, i64 v, i64 order, f64 p, f64 PCx, f64 PCy, f64 PCz, f64 separation_pc)
{
    f64 result = 0.0;
    if ((t == 0) && (u == 0) && (v == 0))
    {
        result += pow(-2 * p, order) * boys_func(order, p * separation_pc * separation_pc);
    }
    else
    {
        if ((t == 0) && (u == 0))
        {
            if (v > 1)
            {
                result += (v - 1) * hermite_coulomb_integral(t, u, v - 2, order + 1, p, PCx, PCy, PCz, separation_pc);
            }
            result += PCz * hermite_coulomb_integral(t, u, v - 1, order + 1, p, PCx, PCy, PCz, separation_pc);
        }
        else
        {
            if (t == 0)
            {
                if (u > 1)
                {
                    result += (u - 1) * hermite_coulomb_integral(t, u - 2, v, order + 1, p, PCx, PCy, PCz, separation_pc);
                }
                result += PCy * hermite_coulomb_integral(t, u - 1, v, order + 1, p, PCx, PCy, PCz, separation_pc);
            }
            else
            {
                if (t > 1)
                {
                    result += (t - 1) * hermite_coulomb_integral(t - 2, u, v, order + 1, p, PCx, PCy, PCz, separation_pc);
                }
                result += PCx * hermite_coulomb_integral(t - 1, u, v, order + 1, p, PCx, PCy, PCz, separation_pc);
            }
        }
    }
    return result;
}

/* Overlap integral for two primitive Gaussian functions */
__device__ static f64 pg_overlap_integral(f64 gexp_a, u64 amn_x_a, u64 amn_y_a, u64 amn_z_a, f64 x0_a, f64 y0_a, f64 z0_a,
                                          f64 gexp_b, u64 amn_x_b, u64 amn_y_b, u64 amn_z_b, f64 x0_b, f64 y0_b, f64 z0_b)
{
    return hermite_coef(gexp_a, gexp_b, amn_x_a, amn_x_b, 0, x0_a - x0_b) *
           hermite_coef(gexp_a, gexp_b, amn_y_a, amn_y_b, 0, y0_a - y0_b) *
           hermite_coef(gexp_a, gexp_b, amn_z_a, amn_z_b, 0, z0_a - z0_b) *
           pow(M_PI / (gexp_a + gexp_b), 1.5);
}

/*
 * The axis_mask array is used to select the axis along which the derivative is calculated.
 */
__device__ static f64 pg_overlap_integral_dwrt_nuc(f64 gexp_a, u64 amn_x_a, u64 amn_y_a, u64 amn_z_a, f64 x0_a, f64 y0_a, f64 z0_a,
                                                   f64 gexp_b, u64 amn_x_b, u64 amn_y_b, u64 amn_z_b, f64 x0_b, f64 y0_b, f64 z0_b,
                                                   u64 *axis_mask, u64 center)
{
    u64 C = (center == 1) ? 1 : 0;
    u64 D = (center == 2) ? 1 : 0;

    f64 term_1 = axis_mask[0] ? hermite_coef_dwrt_nuc(gexp_a, gexp_b, amn_x_a, amn_x_b, 0, x0_a - x0_b, C, D) : hermite_coef(gexp_a, gexp_b, amn_x_a, amn_x_b, 0, x0_a - x0_b);
    f64 term_2 = axis_mask[1] ? hermite_coef_dwrt_nuc(gexp_a, gexp_b, amn_y_a, amn_y_b, 0, y0_a - y0_b, C, D) : hermite_coef(gexp_a, gexp_b, amn_y_a, amn_y_b, 0, y0_a - y0_b);
    f64 term_3 = axis_mask[2] ? hermite_coef_dwrt_nuc(gexp_a, gexp_b, amn_z_a, amn_z_b, 0, z0_a - z0_b, C, D) : hermite_coef(gexp_a, gexp_b, amn_z_a, amn_z_b, 0, z0_a - z0_b);

    return term_1 * term_2 * term_3 * pow(M_PI / (gexp_a + gexp_b), 1.5);
}

/* Calculates overlap S between two contracted Gaussian functions */
__device__ f64 cg_overlap_integral(struct basis_func *a, struct basis_func *b)
{
    f64 result = 0.0;

    for (u64 i = 0; i < a->n_exponents; ++i)
    {
        for (u64 j = 0; j < b->n_exponents; ++j)
        {
            result += a->normalization_factors[i] * b->normalization_factors[j] *
                      a->coefficients[i] * b->coefficients[j] *
                      pg_overlap_integral(a->exponents[i], a->l, a->m, a->n, a->x0, a->y0, a->z0,
                                          b->exponents[j], b->l, b->m, b->n, b->x0, b->y0, b->z0);
        }
    }

    return result;
}

/*
 * Overlap derivative integral
 */
__device__ void cg_overlap_integral_dwrt_nuc(struct basis_func *a, struct basis_func *b, u64 center, f64 *xyz)
{
    for (u64 axis_idx = 0; axis_idx < 3; ++axis_idx)
    {
        u64 axis_mask[3] = {0, 0, 0};
        axis_mask[axis_idx] = 1;
        f64 result = 0.0;
        for (u64 i = 0; i < a->n_exponents; ++i)
        {
            for (u64 j = 0; j < b->n_exponents; ++j)
            {
                result += a->normalization_factors[i] * b->normalization_factors[j] *
                          a->coefficients[i] * b->coefficients[j] *
                          pg_overlap_integral_dwrt_nuc(a->exponents[i], a->l, a->m, a->n, a->x0, a->y0, a->z0,
                                                       b->exponents[j], b->l, b->m, b->n, b->x0, b->y0, b->z0,
                                                       axis_mask, center);
            }
        }
        xyz[axis_idx] = result;
    }
}

/* Calculates kinetic energy integral between two primitive Gaussian functions */
__device__ static f64 pg_kinetic_integral(f64 gexp_a, u64 amn_x_a, u64 amn_y_a, u64 amn_z_a, f64 x0_a, f64 y0_a, f64 z0_a,
                                          f64 gexp_b, u64 amn_x_b, u64 amn_y_b, u64 amn_z_b, f64 x0_b, f64 y0_b, f64 z0_b)
{
    f64 gexp_b_sq2 = 2 * gexp_b * gexp_b;

    f64 t_x = (2 * amn_x_b + 1) * gexp_b * hermite_coef(gexp_a, gexp_b, amn_x_a, amn_x_b, 0, x0_a - x0_b) -
              gexp_b_sq2 * hermite_coef(gexp_a, gexp_b, amn_x_a, amn_x_b + 2, 0, x0_a - x0_b) -
              0.5 * amn_x_b * (amn_x_b - 1) * hermite_coef(gexp_a, gexp_b, amn_x_a, amn_x_b - 2, 0, x0_a - x0_b);
    t_x *= hermite_coef(gexp_a, gexp_b, amn_y_a, amn_y_b, 0, y0_a - y0_b);
    t_x *= hermite_coef(gexp_a, gexp_b, amn_z_a, amn_z_b, 0, z0_a - z0_b);

    f64 t_y = (2 * amn_y_b + 1) * gexp_b * hermite_coef(gexp_a, gexp_b, amn_y_a, amn_y_b, 0, y0_a - y0_b) -
              gexp_b_sq2 * hermite_coef(gexp_a, gexp_b, amn_y_a, amn_y_b + 2, 0, y0_a - y0_b) -
              0.5 * amn_y_b * (amn_y_b - 1) * hermite_coef(gexp_a, gexp_b, amn_y_a, amn_y_b - 2, 0, y0_a - y0_b);
    t_y *= hermite_coef(gexp_a, gexp_b, amn_x_a, amn_x_b, 0, x0_a - x0_b);
    t_y *= hermite_coef(gexp_a, gexp_b, amn_z_a, amn_z_b, 0, z0_a - z0_b);

    f64 t_z = (2 * amn_z_b + 1) * gexp_b * hermite_coef(gexp_a, gexp_b, amn_z_a, amn_z_b, 0, z0_a - z0_b) -
              gexp_b_sq2 * hermite_coef(gexp_a, gexp_b, amn_z_a, amn_z_b + 2, 0, z0_a - z0_b) -
              0.5 * amn_z_b * (amn_z_b - 1) * hermite_coef(gexp_a, gexp_b, amn_z_a, amn_z_b - 2, 0, z0_a - z0_b);
    t_z *= hermite_coef(gexp_a, gexp_b, amn_x_a, amn_x_b, 0, x0_a - x0_b);
    t_z *= hermite_coef(gexp_a, gexp_b, amn_y_a, amn_y_b, 0, y0_a - y0_b);

    return (t_x + t_y + t_z) * pow(M_PI / (gexp_a + gexp_b), 1.5);
}

__device__ static f64 pg_kinetic_integral_dwrt_nuc(f64 gexp_a, u64 amn_x_a, u64 amn_y_a, u64 amn_z_a, f64 x0_a, f64 y0_a, f64 z0_a,
                                                   f64 gexp_b, u64 amn_x_b, u64 amn_y_b, u64 amn_z_b, f64 x0_b, f64 y0_b, f64 z0_b,
                                                   u64 *axis_mask, u64 center)
{
    f64 gexp_b_sq2 = 2 * gexp_b * gexp_b;

    u64 C = (center == 1) ? 1 : 0;
    u64 D = (center == 2) ? 1 : 0;

    f64 t_x = (2 * amn_x_b + 1) * gexp_b * (axis_mask[0] ? hermite_coef_dwrt_nuc(gexp_a, gexp_b, amn_x_a, amn_x_b, 0, x0_a - x0_b, C, D) : hermite_coef(gexp_a, gexp_b, amn_x_a, amn_x_b, 0, x0_a - x0_b)) -
              gexp_b_sq2 * (axis_mask[0] ? hermite_coef_dwrt_nuc(gexp_a, gexp_b, amn_x_a, amn_x_b + 2, 0, x0_a - x0_b, C, D) : hermite_coef(gexp_a, gexp_b, amn_x_a, amn_x_b + 2, 0, x0_a - x0_b)) -
              0.5 * amn_x_b * (amn_x_b - 1) * (axis_mask[0] ? hermite_coef_dwrt_nuc(gexp_a, gexp_b, amn_x_a, amn_x_b - 2, 0, x0_a - x0_b, C, D) : hermite_coef(gexp_a, gexp_b, amn_x_a, amn_x_b - 2, 0, x0_a - x0_b));

    f64 t_y = (2 * amn_y_b + 1) * gexp_b * (axis_mask[1] ? hermite_coef_dwrt_nuc(gexp_a, gexp_b, amn_y_a, amn_y_b, 0, y0_a - y0_b, C, D) : hermite_coef(gexp_a, gexp_b, amn_y_a, amn_y_b, 0, y0_a - y0_b)) -
              gexp_b_sq2 * (axis_mask[1] ? hermite_coef_dwrt_nuc(gexp_a, gexp_b, amn_y_a, amn_y_b + 2, 0, y0_a - y0_b, C, D) : hermite_coef(gexp_a, gexp_b, amn_y_a, amn_y_b + 2, 0, y0_a - y0_b)) -
              0.5 * amn_y_b * (amn_y_b - 1) * (axis_mask[1] ? hermite_coef_dwrt_nuc(gexp_a, gexp_b, amn_y_a, amn_y_b - 2, 0, y0_a - y0_b, C, D) : hermite_coef(gexp_a, gexp_b, amn_y_a, amn_y_b - 2, 0, y0_a - y0_b));

    f64 t_z = (2 * amn_z_b + 1) * gexp_b * (axis_mask[2] ? hermite_coef_dwrt_nuc(gexp_a, gexp_b, amn_z_a, amn_z_b, 0, z0_a - z0_b, C, D) : hermite_coef(gexp_a, gexp_b, amn_z_a, amn_z_b, 0, z0_a - z0_b)) -
              gexp_b_sq2 * (axis_mask[2] ? hermite_coef_dwrt_nuc(gexp_a, gexp_b, amn_z_a, amn_z_b + 2, 0, z0_a - z0_b, C, D) : hermite_coef(gexp_a, gexp_b, amn_z_a, amn_z_b + 2, 0, z0_a - z0_b)) -
              0.5 * amn_z_b * (amn_z_b - 1) * (axis_mask[2] ? hermite_coef_dwrt_nuc(gexp_a, gexp_b, amn_z_a, amn_z_b - 2, 0, z0_a - z0_b, C, D) : hermite_coef(gexp_a, gexp_b, amn_z_a, amn_z_b - 2, 0, z0_a - z0_b));

    t_y *= (axis_mask[0] ? hermite_coef_dwrt_nuc(gexp_a, gexp_b, amn_x_a, amn_x_b, 0, x0_a - x0_b, C, D) : hermite_coef(gexp_a, gexp_b, amn_x_a, amn_x_b, 0, x0_a - x0_b));
    t_z *= (axis_mask[0] ? hermite_coef_dwrt_nuc(gexp_a, gexp_b, amn_x_a, amn_x_b, 0, x0_a - x0_b, C, D) : hermite_coef(gexp_a, gexp_b, amn_x_a, amn_x_b, 0, x0_a - x0_b));

    t_x *= (axis_mask[1] ? hermite_coef_dwrt_nuc(gexp_a, gexp_b, amn_y_a, amn_y_b, 0, y0_a - y0_b, C, D) : hermite_coef(gexp_a, gexp_b, amn_y_a, amn_y_b, 0, y0_a - y0_b));
    t_z *= (axis_mask[1] ? hermite_coef_dwrt_nuc(gexp_a, gexp_b, amn_y_a, amn_y_b, 0, y0_a - y0_b, C, D) : hermite_coef(gexp_a, gexp_b, amn_y_a, amn_y_b, 0, y0_a - y0_b));

    t_x *= (axis_mask[2] ? hermite_coef_dwrt_nuc(gexp_a, gexp_b, amn_z_a, amn_z_b, 0, z0_a - z0_b, C, D) : hermite_coef(gexp_a, gexp_b, amn_z_a, amn_z_b, 0, z0_a - z0_b));
    t_y *= (axis_mask[2] ? hermite_coef_dwrt_nuc(gexp_a, gexp_b, amn_z_a, amn_z_b, 0, z0_a - z0_b, C, D) : hermite_coef(gexp_a, gexp_b, amn_z_a, amn_z_b, 0, z0_a - z0_b));

    return (t_x + t_y + t_z) * pow(M_PI / (gexp_a + gexp_b), 1.5);
}

/* Calculates kinetic energy between two contracted Gaussian functions */
__device__ f64 cg_kinetic_integral(struct basis_func *a, struct basis_func *b)
{
    f64 result = 0.0;

    for (u64 i = 0; i < a->n_exponents; ++i)
    {
        for (u64 j = 0; j < b->n_exponents; ++j)
        {
            result += a->normalization_factors[i] * b->normalization_factors[j] *
                      a->coefficients[i] * b->coefficients[j] *
                      pg_kinetic_integral(a->exponents[i], a->l, a->m, a->n, a->x0, a->y0, a->z0,
                                          b->exponents[j], b->l, b->m, b->n, b->x0, b->y0, b->z0);
        }
    }

    return result;
}

__device__ void cg_kinetic_integral_dwrt_nuc(struct basis_func *a, struct basis_func *b, u64 center, f64 *xyz)
{
    for (u64 axis_idx = 0; axis_idx < 3; ++axis_idx)
    {
        u64 axis_mask[3] = {0, 0, 0};
        axis_mask[axis_idx] = 1;

        f64 result = 0.0;
        for (u64 i = 0; i < a->n_exponents; ++i)
        {
            for (u64 j = 0; j < b->n_exponents; ++j)
            {
                result += a->normalization_factors[i] * b->normalization_factors[j] *
                          a->coefficients[i] * b->coefficients[j] *
                          pg_kinetic_integral_dwrt_nuc(a->exponents[i], a->l, a->m, a->n, a->x0, a->y0, a->z0,
                                                       b->exponents[j], b->l, b->m, b->n, b->x0, b->y0, b->z0,
                                                       axis_mask, center);
            }
        }
        xyz[axis_idx] = result;
    }
}

/* Calculates nuclear attraction integral with respect to a center C (usually the nucleus) */
__device__ static f64 pg_nuclear_attraction_integral(f64 gexp_a, u64 amn_x_a, u64 amn_y_a, u64 amn_z_a, f64 x0_a, f64 y0_a, f64 z0_a,
                                                     f64 gexp_b, u64 amn_x_b, u64 amn_y_b, u64 amn_z_b, f64 x0_b, f64 y0_b, f64 z0_b,
                                                     f64 x0_c, f64 y0_c, f64 z0_c)
{
    f64 gexp_a_b = gexp_a + gexp_b;
    /* gaussian product center */
    f64 gpc_x = (gexp_a * x0_a + gexp_b * x0_b) / gexp_a_b;
    f64 gpc_y = (gexp_a * y0_a + gexp_b * y0_b) / gexp_a_b;
    f64 gpc_z = (gexp_a * z0_a + gexp_b * z0_b) / gexp_a_b;

    f64 dx_gpc_c = gpc_x - x0_c;
    f64 dy_gpc_c = gpc_y - y0_c;
    f64 dz_gpc_c = gpc_z - z0_c;

    f64 separation_gpc_c = sqrt(dx_gpc_c * dx_gpc_c + dy_gpc_c * dy_gpc_c + dz_gpc_c * dz_gpc_c);

    f64 result = 0.0;

    for (u64 t = 0; t < amn_x_a + amn_x_b + 1; ++t)
    {
        for (u64 u = 0; u < amn_y_a + amn_y_b + 1; ++u)
        {
            for (u64 v = 0; v < amn_z_a + amn_z_b + 1; ++v)
            {
                result += hermite_coef(gexp_a, gexp_b, amn_x_a, amn_x_b, t, x0_a - x0_b) *
                          hermite_coef(gexp_a, gexp_b, amn_y_a, amn_y_b, u, y0_a - y0_b) *
                          hermite_coef(gexp_a, gexp_b, amn_z_a, amn_z_b, v, z0_a - z0_b) *
                          hermite_coulomb_integral(t, u, v, 0, gexp_a_b, dx_gpc_c, dy_gpc_c, dz_gpc_c, separation_gpc_c);
            }
        }
    }

    result *= 2 * M_PI / gexp_a_b;

    return result;
}

__device__ static f64 pg_nuclear_attraction_integral_dwrt_nuc(f64 gexp_a, u64 amn_x_a, u64 amn_y_a, u64 amn_z_a, f64 x0_a, f64 y0_a, f64 z0_a,
                                                              f64 gexp_b, u64 amn_x_b, u64 amn_y_b, u64 amn_z_b, f64 x0_b, f64 y0_b, f64 z0_b,
                                                              f64 x0_c, f64 y0_c, f64 z0_c,
                                                              u64 *axis_mask)
{
    f64 gexp_a_b = gexp_a + gexp_b;
    f64 gpc_x = (gexp_a * x0_a + gexp_b * x0_b) / gexp_a_b;
    f64 gpc_y = (gexp_a * y0_a + gexp_b * y0_b) / gexp_a_b;
    f64 gpc_z = (gexp_a * z0_a + gexp_b * z0_b) / gexp_a_b;

    f64 dx_gpc_c = gpc_x - x0_c;
    f64 dy_gpc_c = gpc_y - y0_c;
    f64 dz_gpc_c = gpc_z - z0_c;

    f64 separation_gpc_c = sqrt(dx_gpc_c * dx_gpc_c + dy_gpc_c * dy_gpc_c + dz_gpc_c * dz_gpc_c);

    f64 result = 0.0;

    u64 t_upper = amn_x_a + amn_x_b + 1;
    u64 u_upper = amn_y_a + amn_y_b + 1;
    u64 v_upper = amn_z_a + amn_z_b + 1;

    for (i64 t = 0; t < t_upper; ++t)
    {
        for (i64 u = 0; u < u_upper; ++u)
        {
            for (i64 v = 0; v < v_upper; ++v)
            {
                result -= hermite_coef(gexp_a, gexp_b, amn_x_a, amn_x_b, t, x0_a - x0_b) *
                          hermite_coef(gexp_a, gexp_b, amn_y_a, amn_y_b, u, y0_a - y0_b) *
                          hermite_coef(gexp_a, gexp_b, amn_z_a, amn_z_b, v, z0_a - z0_b) *
                          hermite_coulomb_integral(t + axis_mask[0], u + axis_mask[1], v + axis_mask[2], 0, gexp_a_b, gpc_x - x0_c, gpc_y - y0_c, gpc_z - z0_c, separation_gpc_c);
            }
        }
    }

    result *= 2 * M_PI / gexp_a_b;
    return result;
}

__device__ static f64 pg_nuclear_attraction_integral_dwrt_orb_center(f64 gexp_a, u64 amn_x_a, u64 amn_y_a, u64 amn_z_a, f64 x0_a, f64 y0_a, f64 z0_a,
                                                                     f64 gexp_b, u64 amn_x_b, u64 amn_y_b, u64 amn_z_b, f64 x0_b, f64 y0_b, f64 z0_b,
                                                                     f64 x0_c, f64 y0_c, f64 z0_c,
                                                                     u64 *axis_mask, u64 center)
{
    f64 gexp_a_b = gexp_a + gexp_b;
    f64 gpc_x = (gexp_a * x0_a + gexp_b * x0_b) / gexp_a_b;
    f64 gpc_y = (gexp_a * y0_a + gexp_b * y0_b) / gexp_a_b;
    f64 gpc_z = (gexp_a * z0_a + gexp_b * z0_b) / gexp_a_b;

    f64 dx_gpc_c = gpc_x - x0_c;
    f64 dy_gpc_c = gpc_y - y0_c;
    f64 dz_gpc_c = gpc_z - z0_c;

    f64 separation_gpc_c = sqrt(dx_gpc_c * dx_gpc_c + dy_gpc_c * dy_gpc_c + dz_gpc_c * dz_gpc_c);

    f64 result = 0.0;

    u64 t_upper = amn_x_a + amn_x_b + 1;
    u64 u_upper = amn_y_a + amn_y_b + 1;
    u64 v_upper = amn_z_a + amn_z_b + 1;

    u64 C = (center == 1) ? 1 : 0;
    u64 D = (center == 2) ? 1 : 0;

    for (i64 t = 0; t < t_upper + axis_mask[0]; ++t)
    {
        for (i64 u = 0; u < u_upper + axis_mask[1]; ++u)
        {
            for (i64 v = 0; v < v_upper + axis_mask[2]; ++v)
            {
                f64 term_1 = axis_mask[0] ? hermite_coef_dwrt_nuc(gexp_a, gexp_b, amn_x_a, amn_x_b, t, x0_a - x0_b, C, D) : hermite_coef(gexp_a, gexp_b, amn_x_a, amn_x_b, t, x0_a - x0_b);
                f64 term_2 = axis_mask[1] ? hermite_coef_dwrt_nuc(gexp_a, gexp_b, amn_y_a, amn_y_b, u, y0_a - y0_b, C, D) : hermite_coef(gexp_a, gexp_b, amn_y_a, amn_y_b, u, y0_a - y0_b);
                f64 term_3 = axis_mask[2] ? hermite_coef_dwrt_nuc(gexp_a, gexp_b, amn_z_a, amn_z_b, v, z0_a - z0_b, C, D) : hermite_coef(gexp_a, gexp_b, amn_z_a, amn_z_b, v, z0_a - z0_b);

                result += term_1 * term_2 * term_3 *
                          hermite_coulomb_integral(t, u, v, 0, gexp_a_b, dx_gpc_c, dy_gpc_c, dz_gpc_c, separation_gpc_c);
            }
        }
    }

    result *= 2 * M_PI / gexp_a_b;
    return result;
}

/* Calculates nuclear-electron attraction V */
__device__ f64 cg_nuclear_attraction_integral(struct basis_func *a, struct basis_func *b, f64 x0_c, f64 y0_c, f64 z0_c)
{
    f64 result = 0.0;

    for (u64 i = 0; i < a->n_exponents; ++i)
    {
        for (u64 j = 0; j < b->n_exponents; ++j)
        {
            result += a->normalization_factors[i] * b->normalization_factors[j] *
                      a->coefficients[i] * b->coefficients[j] *
                      pg_nuclear_attraction_integral(a->exponents[i], a->l, a->m, a->n, a->x0, a->y0, a->z0,
                                                     b->exponents[j], b->l, b->m, b->n, b->x0, b->y0, b->z0,
                                                     x0_c, y0_c, z0_c);
        }
    }

    return result;
}

__device__ void cg_nuclear_attraction_integral_dwrt_nuc(struct basis_func *a, struct basis_func *b,
                                                        f64 x0_c, f64 y0_c, f64 z0_c, f64 *xyz)
{
    for (u64 axis_idx = 0; axis_idx < 3; ++axis_idx)
    {
        u64 axis_mask[3] = {0, 0, 0};
        axis_mask[axis_idx] = 1;

        f64 result = 0.0;
        for (u64 i = 0; i < a->n_exponents; ++i)
        {
            for (u64 j = 0; j < b->n_exponents; ++j)
            {
                result += a->normalization_factors[i] * b->normalization_factors[j] *
                          a->coefficients[i] * b->coefficients[j] *
                          pg_nuclear_attraction_integral_dwrt_nuc(a->exponents[i], a->l, a->m, a->n, a->x0, a->y0, a->z0,
                                                                  b->exponents[j], b->l, b->m, b->n, b->x0, b->y0, b->z0,
                                                                  x0_c, y0_c, z0_c,
                                                                  axis_mask);
            }
        }
        xyz[axis_idx] = result;
    }
}

/*
 * Calculates the derivative of nuclear attraction with respect to the orbital centers
 */
__device__ void cg_nuclear_attraction_integral_dwrt_orb_center(struct basis_func *a, struct basis_func *b,
                                                               f64 x0_c, f64 y0_c, f64 z0_c, u64 center, f64 *xyz)
{
    for (u64 axis_idx = 0; axis_idx < 3; ++axis_idx)
    {
        u64 axis_mask[3] = {0, 0, 0};
        axis_mask[axis_idx] = 1;

        f64 result = 0.0;
        for (u64 i = 0; i < a->n_exponents; ++i)
        {
            for (u64 j = 0; j < b->n_exponents; ++j)
            {
                result += a->normalization_factors[i] * b->normalization_factors[j] *
                          a->coefficients[i] * b->coefficients[j] *
                          pg_nuclear_attraction_integral_dwrt_orb_center(a->exponents[i], a->l, a->m, a->n, a->x0, a->y0, a->z0,
                                                                         b->exponents[j], b->l, b->m, b->n, b->x0, b->y0, b->z0,
                                                                         x0_c, y0_c, z0_c,
                                                                         axis_mask, center);
            }
        }
        xyz[axis_idx] = result;
    }
}

/* Calculates electron-electron repulsion integral */
__device__ static f64 pg_electron_repulsion_integral(f64 gexp_a, u64 amn_x_a, u64 amn_y_a, u64 amn_z_a, f64 x0_a, f64 y0_a, f64 z0_a,
                                                     f64 gexp_b, u64 amn_x_b, u64 amn_y_b, u64 amn_z_b, f64 x0_b, f64 y0_b, f64 z0_b,
                                                     f64 gexp_c, u64 amn_x_c, u64 amn_y_c, u64 amn_z_c, f64 x0_c, f64 y0_c, f64 z0_c,
                                                     f64 gexp_d, u64 amn_x_d, u64 amn_y_d, u64 amn_z_d, f64 x0_d, f64 y0_d, f64 z0_d)
{
    f64 gexp_a_b = gexp_a + gexp_b;
    f64 gexp_c_d = gexp_c + gexp_d;

    // purple book, eq 9.2.12
    f64 gexp_reduced = gexp_a_b * gexp_c_d / (gexp_a_b + gexp_c_d);

    /* Gaussian product center coordinates */
    f64 gpc_ab_x = (gexp_a * x0_a + gexp_b * x0_b) / gexp_a_b;
    f64 gpc_ab_y = (gexp_a * y0_a + gexp_b * y0_b) / gexp_a_b;
    f64 gpc_ab_z = (gexp_a * z0_a + gexp_b * z0_b) / gexp_a_b;

    /* Gaussian product center coordinates */
    f64 gpc_cd_x = (gexp_c * x0_c + gexp_d * x0_d) / gexp_c_d;
    f64 gpc_cd_y = (gexp_c * y0_c + gexp_d * y0_d) / gexp_c_d;
    f64 gpc_cd_z = (gexp_c * z0_c + gexp_d * z0_d) / gexp_c_d;

    f64 dx_gpc = gpc_ab_x - gpc_cd_x;
    f64 dy_gpc = gpc_ab_y - gpc_cd_y;
    f64 dz_gpc = gpc_ab_z - gpc_cd_z;
    f64 gpc_separation = sqrt(dx_gpc * dx_gpc + dy_gpc * dy_gpc + dz_gpc * dz_gpc);

    u64 p_upper = amn_x_a + amn_x_b + 1;
    u64 q_upper = amn_y_a + amn_y_b + 1;
    u64 r_upper = amn_z_a + amn_z_b + 1;
    u64 s_upper = amn_x_c + amn_x_d + 1;
    u64 t_upper = amn_y_c + amn_y_d + 1;
    u64 u_upper = amn_z_c + amn_z_d + 1;

    f64 result = 0.0;
    for (u64 p = 0; p < p_upper; ++p)
        for (u64 q = 0; q < q_upper; ++q)
            for (u64 r = 0; r < r_upper; ++r)
                for (u64 s = 0; s < s_upper; ++s)
                    for (u64 t = 0; t < t_upper; ++t)
                        for (u64 u = 0; u < u_upper; ++u)
                        {
                            result += hermite_coef(gexp_a, gexp_b, amn_x_a, amn_x_b, p, x0_a - x0_b) *
                                      hermite_coef(gexp_a, gexp_b, amn_y_a, amn_y_b, q, y0_a - y0_b) *
                                      hermite_coef(gexp_a, gexp_b, amn_z_a, amn_z_b, r, z0_a - z0_b) *
                                      hermite_coef(gexp_c, gexp_d, amn_x_c, amn_x_d, s, x0_c - x0_d) *
                                      hermite_coef(gexp_c, gexp_d, amn_y_c, amn_y_d, t, y0_c - y0_d) *
                                      hermite_coef(gexp_c, gexp_d, amn_z_c, amn_z_d, u, z0_c - z0_d) *
                                      pow(-1, s + t + u) *
                                      hermite_coulomb_integral(p + s, q + t, r + u, 0,
                                                               gexp_reduced, dx_gpc, dy_gpc, dz_gpc, gpc_separation);
                        }

    result *= 2 * pow(M_PI, 2.5) / (gexp_a_b * gexp_c_d * sqrt(gexp_a_b + gexp_c_d));

    return result;
}

__device__ static f64 pg_electron_repulsion_integral_dwrt_nuc(f64 gexp_a, u64 amn_x_a, u64 amn_y_a, u64 amn_z_a, f64 x0_a, f64 y0_a, f64 z0_a,
                                                              f64 gexp_b, u64 amn_x_b, u64 amn_y_b, u64 amn_z_b, f64 x0_b, f64 y0_b, f64 z0_b,
                                                              f64 gexp_c, u64 amn_x_c, u64 amn_y_c, u64 amn_z_c, f64 x0_c, f64 y0_c, f64 z0_c,
                                                              f64 gexp_d, u64 amn_x_d, u64 amn_y_d, u64 amn_z_d, f64 x0_d, f64 y0_d, f64 z0_d,
                                                              u64 *axis_mask,
                                                              u64 center)
{
    f64 gexp_a_b = gexp_a + gexp_b;
    f64 gexp_c_d = gexp_c + gexp_d;

    // purple book, eq 9.2.12
    f64 gexp_reduced = gexp_a_b * gexp_c_d / (gexp_a_b + gexp_c_d);

    /* Gaussian product center coordinates */
    f64 gpc_ab_x = (gexp_a * x0_a + gexp_b * x0_b) / gexp_a_b;
    f64 gpc_ab_y = (gexp_a * y0_a + gexp_b * y0_b) / gexp_a_b;
    f64 gpc_ab_z = (gexp_a * z0_a + gexp_b * z0_b) / gexp_a_b;

    /* Gaussian product center coordinates */
    f64 gpc_cd_x = (gexp_c * x0_c + gexp_d * x0_d) / gexp_c_d;
    f64 gpc_cd_y = (gexp_c * y0_c + gexp_d * y0_d) / gexp_c_d;
    f64 gpc_cd_z = (gexp_c * z0_c + gexp_d * z0_d) / gexp_c_d;

    f64 dx_gpc = gpc_ab_x - gpc_cd_x;
    f64 dy_gpc = gpc_ab_y - gpc_cd_y;
    f64 dz_gpc = gpc_ab_z - gpc_cd_z;
    f64 gpc_separation = sqrt(dx_gpc * dx_gpc + dy_gpc * dy_gpc + dz_gpc * dz_gpc);

    f64 result = 0.0;

    u64 p_upper = amn_x_a + amn_x_b + 1;
    u64 q_upper = amn_y_a + amn_y_b + 1;
    u64 r_upper = amn_z_a + amn_z_b + 1;
    u64 s_upper = amn_x_c + amn_x_d + 1;
    u64 t_upper = amn_y_c + amn_y_d + 1;
    u64 u_upper = amn_z_c + amn_z_d + 1;

    u64 A = (center < 3) ? 1 : 0;
    u64 B = (center > 2) ? 1 : 0;
    u64 C = (center == 1 || center == 3) ? 1 : 0;
    u64 D = (center == 2 || center == 4) ? 1 : 0;

    for (u64 p = 0; p < p_upper + axis_mask[0] * A; ++p)
        for (u64 q = 0; q < q_upper + axis_mask[1] * A; ++q)
            for (u64 r = 0; r < r_upper + axis_mask[2] * A; ++r)
                for (u64 s = 0; s < s_upper + axis_mask[0] * B; ++s)
                    for (u64 t = 0; t < t_upper + axis_mask[1] * B; ++t)
                        for (u64 u = 0; u < u_upper + axis_mask[2] * B; ++u)
                        {
                            f64 term_1 = (axis_mask[0] & A) ? hermite_coef_dwrt_nuc(gexp_a, gexp_b, amn_x_a, amn_x_b, p, x0_a - x0_b, C, D) : hermite_coef(gexp_a, gexp_b, amn_x_a, amn_x_b, p, x0_a - x0_b);
                            f64 term_2 = (axis_mask[1] & A) ? hermite_coef_dwrt_nuc(gexp_a, gexp_b, amn_y_a, amn_y_b, q, y0_a - y0_b, C, D) : hermite_coef(gexp_a, gexp_b, amn_y_a, amn_y_b, q, y0_a - y0_b);
                            f64 term_3 = (axis_mask[2] & A) ? hermite_coef_dwrt_nuc(gexp_a, gexp_b, amn_z_a, amn_z_b, r, z0_a - z0_b, C, D) : hermite_coef(gexp_a, gexp_b, amn_z_a, amn_z_b, r, z0_a - z0_b);
                            f64 term_4 = (axis_mask[0] & B) ? hermite_coef_dwrt_nuc(gexp_c, gexp_d, amn_x_c, amn_x_d, s, x0_c - x0_d, C, D) : hermite_coef(gexp_c, gexp_d, amn_x_c, amn_x_d, s, x0_c - x0_d);
                            f64 term_5 = (axis_mask[1] & B) ? hermite_coef_dwrt_nuc(gexp_c, gexp_d, amn_y_c, amn_y_d, t, y0_c - y0_d, C, D) : hermite_coef(gexp_c, gexp_d, amn_y_c, amn_y_d, t, y0_c - y0_d);
                            f64 term_6 = (axis_mask[2] & B) ? hermite_coef_dwrt_nuc(gexp_c, gexp_d, amn_z_c, amn_z_d, u, z0_c - z0_d, C, D) : hermite_coef(gexp_c, gexp_d, amn_z_c, amn_z_d, u, z0_c - z0_d);

                            result += term_1 * term_2 * term_3 * term_4 * term_5 * term_6 *
                                      pow(-1, s + t + u) *
                                      hermite_coulomb_integral(p + s, q + t, r + u, 0, gexp_reduced, dx_gpc, dy_gpc, dz_gpc, gpc_separation);
                        }

    result *= 2 * pow(M_PI, 2.5) / (gexp_a_b * gexp_c_d * sqrt(gexp_a_b + gexp_c_d));
    return result;
}

/* Calculates electron repulsion integrals */
__device__ f64 cg_electron_repulsion_integral(struct basis_func *a, struct basis_func *b, struct basis_func *c, struct basis_func *d)
{
    f64 result = 0.0;

    for (u64 i1 = 0; i1 < a->n_exponents; ++i1)
    {
        for (u64 i2 = 0; i2 < b->n_exponents; ++i2)
        {
            for (u64 i3 = 0; i3 < c->n_exponents; ++i3)
            {
                for (u64 i4 = 0; i4 < d->n_exponents; ++i4)
                {
                    result += a->normalization_factors[i1] * b->normalization_factors[i2] *
                              c->normalization_factors[i3] * d->normalization_factors[i4] *
                              a->coefficients[i1] * b->coefficients[i2] *
                              c->coefficients[i3] * d->coefficients[i4] *
                              pg_electron_repulsion_integral(a->exponents[i1], a->l, a->m, a->n, a->x0, a->y0, a->z0,
                                                             b->exponents[i2], b->l, b->m, b->n, b->x0, b->y0, b->z0,
                                                             c->exponents[i3], c->l, c->m, c->n, c->x0, c->y0, c->z0,
                                                             d->exponents[i4], d->l, d->m, d->n, d->x0, d->y0, d->z0);
                }
            }
        }
    }

    return result;
}

__device__ void cg_electron_repulsion_integral_dwrt_nuc(struct basis_func *a, struct basis_func *b, struct basis_func *c, struct basis_func *d, u64 center, f64 *xyz)
{
    for (u64 axis_idx = 0; axis_idx < 3; ++axis_idx)
    {
        u64 axis_mask[3] = {0, 0, 0};
        axis_mask[axis_idx] = 1;

        f64 result = 0.0;
        for (u64 i1 = 0; i1 < a->n_exponents; ++i1)
        {
            for (u64 i2 = 0; i2 < b->n_exponents; ++i2)
            {
                for (u64 i3 = 0; i3 < c->n_exponents; ++i3)
                {
                    for (u64 i4 = 0; i4 < d->n_exponents; ++i4)
                    {
                        result += a->normalization_factors[i1] * b->normalization_factors[i2] *
                                  c->normalization_factors[i3] * d->normalization_factors[i4] *
                                  a->coefficients[i1] * b->coefficients[i2] *
                                  c->coefficients[i3] * d->coefficients[i4] *
                                  pg_electron_repulsion_integral_dwrt_nuc(a->exponents[i1], a->l, a->m, a->n, a->x0, a->y0, a->z0,
                                                                          b->exponents[i2], b->l, b->m, b->n, b->x0, b->y0, b->z0,
                                                                          c->exponents[i3], c->l, c->m, c->n, c->x0, c->y0, c->z0,
                                                                          d->exponents[i4], d->l, d->m, d->n, d->x0, d->y0, d->z0,
                                                                          axis_mask, center);
                    }
                }
            }
        }
        xyz[axis_idx] = result;
    }
}

#ifdef MODULE_TEST

#ifdef __NVCC__
__global__ static void pg_electron_repulsion_integral_kernel(f64 gexp_a, u64 amn_x_a, u64 amn_y_a, u64 amn_z_a, f64 x0_a, f64 y0_a, f64 z0_a,
                                                             f64 gexp_b, u64 amn_x_b, u64 amn_y_b, u64 amn_z_b, f64 x0_b, f64 y0_b, f64 z0_b,
                                                             f64 gexp_c, u64 amn_x_c, u64 amn_y_c, u64 amn_z_c, f64 x0_c, f64 y0_c, f64 z0_c,
                                                             f64 gexp_d, u64 amn_x_d, u64 amn_y_d, u64 amn_z_d, f64 x0_d, f64 y0_d, f64 z0_d,
                                                             f64 *output)
{
    *output = pg_electron_repulsion_integral(gexp_a, amn_x_a, amn_y_a, amn_z_a, x0_a, y0_a, z0_a,
                                             gexp_b, amn_x_b, amn_y_b, amn_z_b, x0_b, y0_b, z0_b,
                                             gexp_c, amn_x_c, amn_y_c, amn_z_c, x0_c, y0_c, z0_c,
                                             gexp_d, amn_x_d, amn_y_d, amn_z_d, x0_d, y0_d, z0_d);
}
#endif

int main(void)
{
#ifdef __CUDACC__
    printf("__CUDACC__ defined\n");
#endif

#ifdef __NVCC__
    size_t pValue;
    cudaDeviceGetLimit(&pValue, cudaLimitStackSize);
    printf("cudaDeviceGetLimit(cudaLimitStackSize) = %zu\n", pValue);

    cudaDeviceSetLimit(cudaLimitStackSize, 8 * 1024);

    cudaDeviceGetLimit(&pValue, cudaLimitStackSize);
    printf("cudaDeviceGetLimit(cudaLimitStackSize) = %zu\n", pValue);

    f64 *output;
    cudaMallocManaged(&output, 32, cudaMemAttachGlobal);

    pg_electron_repulsion_integral_kernel<<<1, 1>>>(1.0, 0, 0, 0, 0.0, 0.0, 0.0,
                                                    1.0, 0, 0, 0, 0.0, 0.0, 0.0,
                                                    1.0, 0, 0, 0, 0.0, 0.0, 0.0,
                                                    1.0, 0, 0, 0, 0.0, 0.0, 0.0,
                                                    output);
    cudaDeviceSynchronize();
    printf("output = %.16e\n", *output);
    cudaFree(output);
#else
    printf("%.16e\n", hermite_coef(130.70932, 130.70932, 0, 0, 0, 0.0));
    printf("%.16e\n", hermite_coef(0.623914, 1.169596, 0, 0, 0, 1.494187));
    printf("%.16e\n", hermite_coef(0.623914, 1.169596, 0, 0, 0, -1.494187));
    printf("%.16e\n", pg_electron_repulsion_integral(1.0, 0, 0, 0, 0.0, 0.0, 0.0,
                                                     1.0, 0, 0, 0, 0.0, 0.0, 0.0,
                                                     1.0, 0, 0, 0, 0.0, 0.0, 0.0,
                                                     1.0, 0, 0, 0, 0.0, 0.0, 0.0));
#endif
}
#endif
