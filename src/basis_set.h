/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef BASIS_SET_H
#define BASIS_SET_H

#include "numeric_types.h"

char *load_basis_set_from_file(char const *basis_set_filepath, u64 n_selected_elements, u64 *selected_elements);

#endif
