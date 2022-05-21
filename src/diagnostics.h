/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H
#include <stdio.h>
#include "numeric_types.h"
#include "time_util.h"

#define log_tm_print(silent, format, args...) do{if(!silent){char time_s[32];current_time_str(time_s, 32);printf("[%s] ", time_s);printf(format, ##args);}}while(0)
#define log_dbg_print(silent, format, args...) do{if(!silent){char time_s[32];current_time_str(time_s, 32);printf("[%s] %s %s %d: ", time_s, __FILE__, __func__, __LINE__);printf(format, ##args);}}while(0)
#define log_tm_println(silent, format, args...) do{if(!silent){char time_s[32];current_time_str(time_s, 32);printf("[%s] ", time_s);printf(format, ##args);printf("\n");}}while(0)
#define log_dbg_println(silent, format, args...) do{if(!silent){char time_s[32];current_time_str(time_s, 32);printf("[%s] %s %s %d: ", time_s, __FILE__, __func__, __LINE__);printf(format, ##args);printf("\n");}}while(0)

#define console_printf(silent, format, args...) do{if(!silent){printf(format, ##args);}}while(0)

void print_f64_array(f64 *A, u64 count, u64 col_size, int precision);
void print_f64_array_with_label(f64 *A, u64 count, u64 col_size, int precision, char const *label);
void print_u32_array(u32 *A, u64 count, u64 col_size);
void print_u32_array_with_label(u32 *A, u64 count, u64 col_size, char const *label);
void print_f64_values_within_bounds(f64 *A, u64 count, f64 lower_bound, f64 upper_bound, u64 col_size, int precision, i64 max_count);
void inspect_nan(f64 *A, u64 count, u64 col_size, i64 max_count, char const * array_label);
void print_f64_diff(f64 value, f64 expected, char const* label);

#endif
