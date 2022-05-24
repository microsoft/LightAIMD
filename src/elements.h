/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef ELEMENTS_H
#define ELEMENTS_H
#include "numeric_types.h"

extern char *ELEMENTS[];
extern char *ATOMIC_NAMES[];
extern double STANDARD_ATOMIC_WEIGHTS[];

u64 atomic_symbol_to_num(char const *sym);
f64 atomic_num_to_mass(u64 Z);

#endif
