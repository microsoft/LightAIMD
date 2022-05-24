/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef MOLECULAR_INTEGRAL_H
#define MOLECULAR_INTEGRAL_H
#include "numeric_types.h"

f64 cg_overlap_integral(struct basis_func *a, struct basis_func *b);
f64 cg_kinetic_integral(struct basis_func *a, struct basis_func *b);
f64 cg_nuclear_attraction_integral(struct basis_func *a, struct basis_func *b, f64 c_x, f64 c_y, f64 c_z);
f64 cg_electron_repulsion_integral(struct basis_func *a, struct basis_func *b, struct basis_func *c, struct basis_func *d);

void cg_overlap_integral_dwrt_nuc(struct basis_func *a, struct basis_func *b, u64 center, f64 *xyz);
void cg_kinetic_integral_dwrt_nuc(struct basis_func *a, struct basis_func *b, u64 center, f64 *xyz);
void cg_nuclear_attraction_integral_dwrt_nuc(struct basis_func *a, struct basis_func *b, f64 x0_c, f64 y0_c, f64 z0_c, f64 *xyz);
void cg_nuclear_attraction_integral_dwrt_orb_center(struct basis_func *a, struct basis_func *b, f64 x0_c, f64 y0_c, f64 z0_c, u64 center, f64 *xyz);
void cg_electron_repulsion_integral_dwrt_nuc(struct basis_func *a, struct basis_func *b, struct basis_func *c, struct basis_func *d, u64 center, f64 *xyz);
#endif
