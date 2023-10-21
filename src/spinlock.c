/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <stdio.h>
#include "numeric_types.h"

void spinlock_lock(volatile atomic_bool* lck)
{
    while (1)
    {
        if (!atomic_exchange_explicit(lck, 1, memory_order_acquire))
        {
            return;
        }

        while (atomic_load_explicit(lck, memory_order_relaxed))
        {
            __builtin_ia32_pause();
        }
    }
}

void spinlock_unlock(volatile atomic_bool* lck)
{
    atomic_store_explicit(lck, 0, memory_order_release);
}

#ifdef MODULE_TEST
int main(void)
{
    volatile atomic_bool lck = 0;
    for (u64 i = 0; i < 10000; ++i)
    {
        spinlock_lock(&lck);
        spinlock_unlock(&lck);
    }
    return 0;
}
#endif
