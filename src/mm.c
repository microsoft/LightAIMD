/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <stdio.h>
#include "mm.h"
#include "spinlock.h"

static u64 total_allocated_memory = 0;
// static u64 total_freed_memory = 0;
static u64 malloc_count = 0;
static u64 calloc_count = 0;
static u64 free_count = 0;

static volatile atomic_bool mm_malloc_lock = 0;
static volatile atomic_bool mm_calloc_lock = 0;
static volatile atomic_bool mm_free_lock = 0;

void *x_malloc(u64 size)
{
    spinlock_lock(&mm_malloc_lock);
    ++malloc_count;
    total_allocated_memory += size;
    spinlock_unlock(&mm_malloc_lock);
    return malloc(size);
}

void *x_calloc(u64 count, u64 size)
{
    spinlock_lock(&mm_calloc_lock);
    ++calloc_count;
    total_allocated_memory += count * size;
    spinlock_unlock(&mm_calloc_lock);
    return calloc(count, size);
}

void x_free(void *ptr)
{
    spinlock_lock(&mm_free_lock);
    ++free_count;
    spinlock_unlock(&mm_free_lock);

    if (ptr == NULL)
    {
        printf("Warning: NULL pointer is being freed.\n");
    }

    free(ptr);
}

void print_mm_status()
{
    printf("----------------- Memory Management Summary -----------------\n");
    u64 total_alloc_times = malloc_count + calloc_count;
    printf("Alloc %lu times: %lu bytes (%.2f MB)\n", total_alloc_times, total_allocated_memory, (f64)total_allocated_memory / (1024.0 * 1024.0));
    printf("Free %lu times\n", free_count);
    if (total_alloc_times == free_count)
    {
        printf("Status: OK\n");
    }
    else
    {
        printf("Warning: alloc times and free times don't match.\n");
    }
    printf("-------------------------------------------------------------\n");
}
