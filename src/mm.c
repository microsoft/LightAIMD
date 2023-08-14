/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <stdio.h>
#include <string.h>
#include "mm.h"
#include "spinlock.h"
#include "cuda_helper.h"

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

#ifdef USE_CUDA
    void *ptr;
    cudaMallocManaged(&ptr, size, cudaMemAttachGlobal);
    return ptr;
#else
    return malloc(size);
#endif
}

void *x_calloc(u64 count, u64 size)
{
    u64 _size = count * size;
    spinlock_lock(&mm_calloc_lock);
    ++calloc_count;
    total_allocated_memory += _size;
    spinlock_unlock(&mm_calloc_lock);

#ifdef USE_CUDA
    void *ptr;
    cudaMallocManaged(&ptr, _size, cudaMemAttachGlobal);
    memset(ptr, 0, _size);
    return ptr;
#else
    return calloc(count, size);
#endif
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

#ifdef USE_CUDA
    cudaFree(ptr);
#else
    free(ptr);
#endif
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
