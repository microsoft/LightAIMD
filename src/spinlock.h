/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef SPINLOCK_H
#define SPINLOCK_H

void spinlock_lock(volatile atomic_bool *lck);
void spinlock_unlock(volatile atomic_bool *lck);

#endif
