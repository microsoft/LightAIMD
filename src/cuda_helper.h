/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include "numeric_types.h"

#ifndef __host__
#define __host__
#endif

#ifndef __device__
#define __device__
#endif

#ifndef __global__
#define __global__
#endif

#define MAX_GPU_COUNT 128
#define THREAD_PER_BLOCK 128

#ifdef USE_CUDA
#include <cuda_runtime.h>
#include <cuda.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

int cuda_get_device_count();
void cuda_configure();
void cuda_sync_all();

#ifdef __cplusplus
}
#endif
