/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H
#include "numeric_types.h"

void functional_lda_x(f64 const* rho, f64* exc, f64* vrho, u64 num_points);
void functional_lda_c_vwn(f64 const* rho, f64* exc, f64* vrho, u64 num_points);

#endif
