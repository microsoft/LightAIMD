/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/sysinfo.h>

#include "thread_pool.h"
#include "time_util.h"
#include "mm.h"

void *threadpool_worker(void *p_args)
{
    struct threadpool_worker_desc *desc = (struct threadpool_worker_desc *)p_args;

    do
    {
        pthread_mutex_lock(&(desc->task_queue_mutex));

        if (desc->worker_state == THREADPOOL_WORKER_STOP)
        {
            break;
        }

        /* check task availability */
        if (desc->n_tasks == 0)
        {
            pthread_cond_wait(&(desc->cond_var_task_arrival), &(desc->task_queue_mutex));
        }

        if (desc->worker_state == THREADPOOL_WORKER_STOP)
        {
            break;
        }

        /* get a task */
        struct threadpool_task *task = desc->task_queue + desc->current_task;
        task_func_t task_func = task->task_func;
        void *p_argument = task->p_argument;

        pthread_mutex_unlock(&(desc->task_queue_mutex));

        /* do the work */
        task_func(p_argument);

        pthread_mutex_lock(&(desc->task_queue_mutex));
        desc->current_task = (desc->current_task + 1) % desc->task_queue_size;
        --(desc->n_tasks);
        if (desc->n_tasks < desc->task_queue_size)
        {
            /* pthread_cond_signal() has no effect if there are no threads currently blocked on the condition variable */
            pthread_cond_signal(&(desc->cond_var_task_slot_available));
        }
        pthread_mutex_unlock(&(desc->task_queue_mutex));

        --(desc->tp_ctx->n_active_tasks);

    } while (1);

    pthread_mutex_unlock(&(desc->task_queue_mutex));
    return NULL;
}

struct threadpool_context *threadpool_initialize(u64 threadpool_size, u64 task_queue_size)
{
    u64 n_workers = threadpool_size;
    if (threadpool_size == 0)
    {
        n_workers = (u64)get_nprocs();
    }

    struct threadpool_context *tp_ctx = x_malloc(sizeof(struct threadpool_context));
    tp_ctx->worker_descs = x_malloc(n_workers * sizeof(struct threadpool_worker_desc));
    tp_ctx->n_workers = n_workers;
    tp_ctx->n_active_tasks = 0;
    for (u64 t = 0; t < n_workers; ++t)
    {
        struct threadpool_worker_desc *worker_desc = tp_ctx->worker_descs + t;
        worker_desc->worker_id = t;
        worker_desc->task_queue = x_malloc(task_queue_size * sizeof(struct threadpool_task));
        worker_desc->n_tasks = 0;
        worker_desc->current_task = 0;
        worker_desc->task_queue_size = task_queue_size;
        worker_desc->worker_state = 0;
        worker_desc->tp_ctx = tp_ctx;

        pthread_mutex_init(&(worker_desc->task_queue_mutex), NULL);
        pthread_cond_init(&(worker_desc->cond_var_task_arrival), NULL);
        pthread_cond_init(&(worker_desc->cond_var_task_slot_available), NULL);
        pthread_create(&(worker_desc->worker), NULL, threadpool_worker, (void *)worker_desc);
    }

    return tp_ctx;
}

void threadpool_finalize(struct threadpool_context *tp_ctx)
{
    for (u64 t = 0; t < tp_ctx->n_workers; ++t)
    {
        struct threadpool_worker_desc *desc = tp_ctx->worker_descs + t;
        pthread_mutex_lock(&(desc->task_queue_mutex));
        desc->worker_state = THREADPOOL_WORKER_STOP;
        pthread_cond_signal(&(desc->cond_var_task_arrival));
        pthread_mutex_unlock(&(desc->task_queue_mutex));

        pthread_join(desc->worker, NULL);
        x_free(desc->task_queue);
        pthread_mutex_destroy(&(desc->task_queue_mutex));
        pthread_cond_destroy(&(desc->cond_var_task_arrival));
        pthread_cond_destroy(&(desc->cond_var_task_slot_available));
    }
    x_free(tp_ctx->worker_descs);
    x_free(tp_ctx);
}

void threadpool_add_task(struct threadpool_context *tp_ctx, u64 worker_id, task_func_t task_func, void *p_argument)
{
    struct threadpool_worker_desc *desc = tp_ctx->worker_descs + worker_id;
    pthread_mutex_lock(&(desc->task_queue_mutex));

    if (desc->n_tasks == desc->task_queue_size)
    {
        pthread_cond_wait(&(desc->cond_var_task_slot_available), &(desc->task_queue_mutex));
    }

    u64 task_slot_index = (desc->current_task + desc->n_tasks) % desc->task_queue_size;

    desc->task_queue[task_slot_index].task_func = task_func;
    desc->task_queue[task_slot_index].p_argument = p_argument;

    ++(desc->n_tasks);

    pthread_cond_signal(&(desc->cond_var_task_arrival));
    pthread_mutex_unlock(&(desc->task_queue_mutex));
    ++(tp_ctx->n_active_tasks);
}

void threadpool_wait_job_done(struct threadpool_context *tp_ctx)
{
    while (tp_ctx->n_active_tasks)
    {
        sleep_5ms();
    }
}

#ifdef MODULE_TEST
#include <stdatomic.h>
atomic_uint_fast64_t counter = 0;
void test_task_func(void *p_args)
{
    ++counter;
}

int main(void)
{
    struct threadpool_context *ctx = threadpool_initialize(0, 4096);

    for (u64 i = 0; i < 65536; ++i)
    {
        threadpool_add_task(ctx, i % 24, test_task_func, (void *)i);
    }

    threadpool_wait_job_done(ctx);

    printf("%lu\n", counter);

    threadpool_finalize(ctx);
    return 0;
}
#endif
