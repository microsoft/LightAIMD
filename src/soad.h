/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef SOAD_H
#define SOAD_H
#include "numeric_types.h"

void soad_initialize_density_matrix(f64* density_matrix, u64 n_atomic_orbitals, u64* atomic_nums, u64 n_atoms);

#endif
