/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef LEBEDEV_GRID_H
#define LEBEDEV_GRID_H
#include "numeric_types.h"

u64 lebedev_num_points(u64 level);
u64 lebedev_num_points_to_level(u64 num_points);
u64 lebedev_gen_grid(f64 *grid, f64 *weights, u64 level);

#endif
