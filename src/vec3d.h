/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef VECTOR_H
#define VECTOR_H
#include "numeric_types.h"

struct vec3d
{
    f64 x;
    f64 y;
    f64 z;
};

void vec3d_subtract(struct vec3d *a, struct vec3d *b, struct vec3d *c);
f64 vec3d_norm_squared(struct vec3d const *v);

#endif
