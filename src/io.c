/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#include "numeric_types.h"

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

#ifdef MODULE_TEST
#include <stdio.h>
int main(void)
{
    ensure_dir_exists("output");

    char stem[256];
    filename_stem("sample/h2o.xyz", stem);
    printf("stem: %s\n", stem);
    return 0;
}
#endif
