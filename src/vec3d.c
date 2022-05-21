/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <math.h>
#include "vec3d.h"

/* c = a - b */
void vec3d_subtract(struct vec3d *a, struct vec3d *b, struct vec3d *c)
{
    c->x = a->x - b->x;
    c->y = a->y - b->y;
    c->z = a->z - b->z;
}

f64 vec3d_norm_squared(struct vec3d const *v)
{
    return (v->x * v->x) + (v->y * v->y) + (v->z * v->z);
}

#ifdef MODULE_TEST
int main(void)
{
    return 0;
}
#endif
