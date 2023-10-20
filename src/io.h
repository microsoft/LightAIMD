/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef IO_H
#define IO_H
#include "numeric_types.h"

void filename_stem(const char* path, char* stem);
u64 ensure_dir_exists(char const* path);
/*
 * Read the contents of a file into a buffer.
 * A buffer is allocated by this function and must be freed by the caller.
 * _ot (ownership transfer) indicates that the function will transfer the ownership of the allocated buffer to the caller.
 */
void read_file_to_buffer_ot(char const* file_path, void** buffer, u64* buffer_size);

#endif
