/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <time.h>
#include <math.h>
#include "numeric_types.h"

/* measures the time during which the processor is actively working on a task */
void get_cpu_time(struct timespec *t)
{
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, t);
}

/* measures actual wall-clock time */
void get_wall_time(struct timespec *t)
{
    clock_gettime(CLOCK_MONOTONIC, t);
}

f64 diff_time_ms(struct timespec *t1, struct timespec *t2)
{
    return (t2->tv_sec - t1->tv_sec) * 1e3 + (t2->tv_nsec - t1->tv_nsec) * 1e-6;
}

void sleep_ms(f64 ms)
{
    f64 integral_part;
    modf(ms * 1e-3, &integral_part);

    struct timespec ts;
    ts.tv_sec = (i64) integral_part;

    f64 nanosec = ms * 1e6 - (ts.tv_sec * 1e9);
    ts.tv_nsec = (i32)nanosec;
    nanosleep(&ts, NULL);
}

void sleep_1ms()
{
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 1e6;
    nanosleep(&ts, NULL);
}

void sleep_5ms()
{
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 5e6;
    nanosleep(&ts, NULL);
}

/* Get the current time, not thread-safe */
void current_time_str(char *s, u64 s_size)
{
    time_t t = time(NULL);
    strftime(s, s_size, "%Y-%m-%d %H:%M:%S", localtime(&t));
}

#ifdef MODULE_TEST
#include <stdio.h>
int main(void)
{
    char time_s[32];
    current_time_str(time_s, 32);
    printf("current time: %s\n", time_s);
    struct timespec time_start, time_end;
    get_wall_time(&time_start);
    sleep_ms(1);
    sleep_1ms();
    get_wall_time(&time_end);

    printf("time: %.3f\n", diff_time_ms(&time_start, &time_end));
}
#endif
