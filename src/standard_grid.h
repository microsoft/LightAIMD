/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include "numeric_types.h"
#include "cmd_line_args.h"

extern u64 STANDARD_GRID_SG2[119][10];
extern u64 STANDARD_GRID_SG3[119][18];

u64 get_standard_grid_point_num(u64 z, u64 grid_scheme);
u64 get_standard_grid_radial_point_num(u64 z, u64 grid_scheme);
u64 get_standard_grid_angular_point_num_by_radial_point_idx(u64 z, u64 grid_scheme, u64 radial_point_idx);
