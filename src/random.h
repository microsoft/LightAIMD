/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef RANDOM_H
#define RANDOM_H
#include "numeric_types.h"

f64 rand_uniform();
void rand_standard_normal(f64* values, u64 count);

#endif
