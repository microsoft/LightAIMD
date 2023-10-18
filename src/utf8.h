/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef UTF8_H
#define UTF8_H

#include "numeric_types.h"

u64 utf8_len(void const *buffer, u64 buffer_size);
void utf8_codepoint(void const *buffer, u64 buffer_size, u32 *codepoints, u64 codepoints_size);
void utf8tocstr(u32 *codepoints, u64 codepoints_len, char **cstr);
u32 cmp_utf8_codepoints(u32 const *codepoints1, u64 codepoints1_len, u32 const *codepoints2, u64 codepoints2_len);
u32 cmp_utf8_with_cstr(u32 *codepoints, u64 codepoints_len, char const *cstr);
i64 utf8toi64(u32 *codepoints, u64 codepoints_len);
u64 utf8tou64(u32 *codepoints, u64 codepoints_len);
f64 utf8tof64(u32 *codepoints, u64 codepoints_len);

#endif
