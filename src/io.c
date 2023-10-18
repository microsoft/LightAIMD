/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "numeric_types.h"
#include "mm.h"

void filename_stem(const char *path, char *stem)
{
    char const *p = path;
    u64 idx = 0;
    while (1)
    {
        if (path[idx] == '\0')
        {
            break;
        }
        if (path[idx] == '/' || path[idx] == '\\')
        {
            p = path + idx + 1;
        }
        ++idx;
    }

    idx = 0;
    u64 dot_idx = 0;

    while (1)
    {
        if (p[idx] == '\0')
        {
            break;
        }
        if (p[idx] == '.')
        {
            dot_idx = idx;
        }
        ++idx;
    }

    memcpy(stem, p, dot_idx);
}

u64 ensure_dir_exists(char const *path)
{
    struct stat status;
    stat(path, &status);

    if (S_ISDIR(status.st_mode))
    {
        return 1;
    }

    if (!mkdir(path, 0777))
    {
        stat(path, &status);
        if (S_ISDIR(status.st_mode))
        {
            return 1;
        }
    }
    return 0;
}

void read_file_to_buffer_ot(char const *file_path, void **buffer, u64 *buffer_size)
{
    FILE *fp = fopen(file_path, "rb");
    if (NULL == fp)
    {
        return;
    }

    fseek(fp, 0, SEEK_END);
    *buffer_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    *buffer = x_malloc(*buffer_size);
    if (NULL == *buffer)
    {
        fclose(fp);
        return;
    }

    if (fread(*buffer, 1, *buffer_size, fp) != *buffer_size)
    {
        x_free(*buffer);
        *buffer = NULL;
        *buffer_size = 0;
    }
    fclose(fp);
}

#ifdef MODULE_TEST
int main(void)
{
    ensure_dir_exists("output");

    char stem[256];
    filename_stem("sample/h2o.xyz", stem);
    printf("stem: %s\n", stem);
    return 0;
}
#endif
