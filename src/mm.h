/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H

#include <stdlib.h>
#include "numeric_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void *x_malloc(u64 size);
    void *x_calloc(u64 count, u64 size);
    void x_free(void *ptr);
    void print_mm_status();

#ifdef __cplusplus
}
#endif
#endif
