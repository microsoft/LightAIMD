/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef UTIL_H
#define UTIL_H
#include <time.h>
#include "numeric_types.h"

void get_cpu_time(struct timespec *t);
void get_wall_time(struct timespec *t);
f64 diff_time_ms(struct timespec *t1, struct timespec *t2);
void sleep_ms(f64 ms);
void sleep_1ms();
void sleep_5ms();
void current_time_str(char *s, u64 s_size);

#endif
