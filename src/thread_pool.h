/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <pthread.h>
#include "numeric_types.h"

typedef void (*task_func_t)(void *);

#define THREADPOOL_WORKER_STOP 1

struct threadpool_task
{
    task_func_t task_func;
    void *p_argument;
};

struct threadpool_worker_desc
{
    u64 worker_id;
    pthread_t worker;

    u64 n_tasks;
    u64 current_task;
    u64 task_queue_size;
    /* each worker has its own task queue */
    struct threadpool_task *task_queue;

    pthread_mutex_t task_queue_mutex;
    pthread_cond_t cond_var_task_arrival;
    pthread_cond_t cond_var_task_slot_available;
    u64 worker_state;
    struct threadpool_context *tp_ctx;
};

struct threadpool_context
{
    u64 n_workers;
    struct threadpool_worker_desc *worker_descs;
    atomic_u64 n_active_tasks;
};

struct threadpool_context *threadpool_initialize(u64 threadpool_size, u64 task_queue_size);
void threadpool_finalize(struct threadpool_context *tp_ctx);
void threadpool_add_task(struct threadpool_context *tp_ctx, u64 worker_id, task_func_t task_func, void *p_argument);
void threadpool_wait_job_done(struct threadpool_context *tp_ctx);

#endif
