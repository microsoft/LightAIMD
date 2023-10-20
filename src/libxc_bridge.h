/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef LIBXC_BRIDGE_H
#define LIBXC_BRIDGE_H
#include "numeric_types.h"

extern const u64 XC_TYPE_LDA;
extern const u64 XC_TYPE_GGA;
extern const u64 XC_TYPE_MGGA;

void libxc_initialize(i32* func_ids, i32* is_polarized, u64 func_count);
void libxc_finalize();
f64 libxc_hyb_coef(u64 func_id);
u64 get_xc_type(u64 x_functional_id, u64 c_functional_id);
void libxc_exc_vxc(u64 func_id, u64 num_points, f64 const* rho, f64 const* sigma, f64 const* lapl, f64 const* tau,
                   f64* exc, f64* vrho, f64* vsigma, f64* vlapl, f64* vtau);
#endif
