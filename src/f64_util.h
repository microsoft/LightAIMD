/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef F64_UTIL_H
#define F64_UTIL_H

#include "numeric_types.h"

i32 round_f64_to_string(f64 value, i64 n, char* buff, i32 size);
i64 compare_f64_values(f64 value, f64 expected);

#endif
