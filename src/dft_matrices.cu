/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <stdio.h>
#include "numeric_types.h"
#include "basis_func.h"
#include "molecular_integral.h"
#include "cuda_helper.h"

extern "C"
{
    __global__ void cg_electron_repulsion_integral_cuda_kernel(struct basis_func* basis_func_buff, u32* basis_func_index_buff, u64 count, f64* result)
    {
        u64 i = blockIdx.x * blockDim.x + threadIdx.x;
        if (i < count)
        {
            result[i] = cg_electron_repulsion_integral(basis_func_buff + basis_func_index_buff[i * 4],
                        basis_func_buff + basis_func_index_buff[i * 4 + 1],
                        basis_func_buff + basis_func_index_buff[i * 4 + 2],
                        basis_func_buff + basis_func_index_buff[i * 4 + 3]);
        }
    }

    void cg_electron_repulsion_integral_cuda(struct basis_func* basis_func_buff, u32* basis_func_index_buff, u64 count, f64* result)
    {
        u64 device_count = (u64)cuda_get_device_count();

        u64 task_count[MAX_GPU_COUNT];
        for (u64 i = 0; i < device_count; ++i)
        {
            task_count[i] = count / device_count;
        }
        for (u64 i = 0; i < count % device_count; ++i)
        {
            task_count[i] += 1;
        }

        u64 offset = 0;
        for (u64 i = 0; i < device_count; ++i)
        {
            cudaSetDevice(i);
            cg_electron_repulsion_integral_cuda_kernel<<<(task_count[i] + THREAD_PER_BLOCK - 1) / THREAD_PER_BLOCK, THREAD_PER_BLOCK>>>(basis_func_buff, &basis_func_index_buff[4 * offset], task_count[i], &result[offset]);
            offset += task_count[i];
        }

        cuda_sync_all();
    }
}
