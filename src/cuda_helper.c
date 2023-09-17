/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include "cuda_helper.h"
#ifdef USE_CUDA

#ifdef __cplusplus
extern "C"
{
#endif

    int cuda_get_device_count()
    {
        int device_count = 0;
        cudaGetDeviceCount(&device_count);
        return device_count;
    }

    void cuda_configure()
    {
        int cuda_device_count = cuda_get_device_count();
        for (int i = 0; i < cuda_device_count; ++i)
        {
            cudaSetDevice(i);
            cudaDeviceSetLimit(cudaLimitStackSize, 8 * 1024);
        }
    }

    void cuda_sync_all()
    {
        int cuda_device_count = cuda_get_device_count();
        for (int i = 0; i < cuda_device_count; ++i)
        {
            cudaSetDevice(i);
            cudaDeviceSynchronize();
        }
    }

#ifdef __cplusplus
}
#endif

#endif
