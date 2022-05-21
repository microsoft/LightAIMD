/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "numeric_types.h"

/*
 * Note: rand() returns an integer value in [​0, RAND_MAX], (0 and RAND_MAX included)
 * rand() behaves as if it was seeded with srand(1) if srand() is not called
 */

/*
 * Return a f64 value in [0, 1]
 */
f64 rand_uniform()
{
    return (double) rand() / RAND_MAX;
}

void rand_standard_normal(f64 *values, u64 count)
{
    if (count == 0)
    {
        return;
    }

    u64 _count = (count + 1) / 2;

    u64 p = 0;

    for (u64 i = 0; i < _count; ++i)
    {
        f64 u1 = rand_uniform();
        f64 u2 = rand_uniform();

        f64 u1_ = sqrt(-2.0 * log(u1));
        f64 u2_ = 2.0 * M_PI * u2;

        values[p] = u1_ * cos(u2_);
        ++p;
        if (p == count)
        {
            return;
        }

        values[p] = u1_ * sin(u2_);
        ++p;
        if (p == count)
        {
            return;
        }
    }
}

#ifdef MODULE_TEST
int main(void)
{
    f64 values[100] = {0};
    rand_standard_normal(values, 99);

    for (u64 i = 0; i < 100; ++i)
    {
        printf("%.5f,", values[i]);
    }
    printf("\n");
    return 0;
}
#endif
