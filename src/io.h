/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef IO_H
#define IO_H
#include "numeric_types.h"

void filename_stem(const char *path, char *stem);
u64 ensure_dir_exists(char const *path);

#endif
