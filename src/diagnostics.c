/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "diagnostics.h"
#include "mm.h"
#include "f64_util.h"

void print_f64_array(f64 *A, u64 count, u64 col_size, int precision)
{
    u64 nrow = count / col_size;
    u64 last_row = count % col_size;

    for (u64 j = 0; j < col_size; ++j)
    {
        printf("%*lu ", precision + 7, j);
    }
    printf("\n");

    u64 ndash = col_size * (precision + 8) - 1;
    for (u64 j = 0; j < ndash; ++j)
    {
        printf("-");
    }
    printf("\n");

    for (u64 i = 0; i < nrow; ++i)
    {
        for (u64 j = 0; j < col_size; ++j)
        {
            printf("%*.*e ", precision + 7, precision, A[i * col_size + j]);
        }
        printf("\n");
    }

    for (u64 j = 0; j < last_row; ++j)
    {
        printf("%*.*e ", precision + 7, precision, A[nrow * col_size + j]);
    }
    printf("\n");

    for (u64 j = 0; j < ndash; ++j)
    {
        printf("-");
    }
    printf("\n");
}

void print_f64_array_with_label(f64 *A, u64 count, u64 col_size, int precision, char const *label)
{
    printf("%s:\n", label);
    print_f64_array(A, count, col_size, precision);
}

void print_u32_array(u32 *A, u64 count, u64 col_size)
{
    u64 nrow = count / col_size;
    u64 last_row = count % col_size;

    u64 ndash = col_size * 6 - 1;
    for (u64 j = 0; j < ndash; ++j)
    {
        printf("-");
    }
    printf("\n");

    for (u64 i = 0; i < nrow; ++i)
    {
        for (u64 j = 0; j < col_size; ++j)
        {
            printf("%lu ", A[i * col_size + j]);
        }
        printf("\n");
    }

    for (u64 j = 0; j < last_row; ++j)
    {
        printf("%lu ", A[nrow * col_size + j]);
    }
    printf("\n");

    for (u64 j = 0; j < ndash; ++j)
    {
        printf("-");
    }
    printf("\n");
}

void print_u32_array_with_label(u32 *A, u64 count, u64 col_size, char const *label)
{
    printf("%s:\n", label);
    print_u32_array(A, count, col_size);
}

void print_f64_values_within_bounds(f64 *A, u64 count, f64 lower_bound, f64 upper_bound, u64 col_size, int precision, i64 max_count)
{
    u64 nrow = count / col_size;
    u64 last_row = count % col_size;

    u64 count_threshold = U64_MAX;
    if(max_count > -1)
    {
        count_threshold = max_count;
    }
    u64 total_count = 0;

    for (u64 j = 0; j < col_size; ++j)
    {
        printf("%*lu ", precision + 7, j);
    }
    printf("\n");

    u64 ndash = col_size * (precision + 8) - 1;
    for (u64 j = 0; j < ndash; ++j)
    {
        printf("-");
    }
    printf("\n");

    for (u64 i = 0; i < nrow; ++i)
    {
        u64 valid_value_count = 0;
        for (u64 j = 0; j < col_size; ++j)
        {
            f64 value = A[i * col_size + j];
            if (value >= lower_bound && value <= upper_bound)
            {
                printf("%lu:%*.*e ", i * col_size + j, precision + 7, precision, value);
                ++valid_value_count;
            }
        }
        if (valid_value_count)
        {
            printf("\n");
        }
        total_count += valid_value_count;
        if (total_count >= count_threshold)
        {
            goto end;
        }
    }

    u64 valid_value_count = 0;
    for (u64 j = 0; j < last_row; ++j)
    {
        f64 value = A[nrow * col_size + j];
        if(value >= lower_bound && value <= upper_bound)
        {
            printf("%lu:%*.*e ", nrow * col_size + j, precision + 7, precision, value);
            ++valid_value_count;
            ++total_count;
        }
    }
    if(valid_value_count)
    {
        printf("\n");
    }

    end:
    for (u64 j = 0; j < ndash; ++j)
    {
        printf("-");
    }
    printf("\n");
}

void inspect_nan(f64 *A, u64 count, u64 col_size, i64 max_count, char const * array_label)
{
    printf("checking %s for nan values ...\n", array_label);

    u64 count_threshold = U64_MAX;
    if(max_count > -1)
    {
        count_threshold = max_count;
    }

    u64 total_count = 0;
    u64 col_count = 0;
    for(u64 i = 0; i < count; ++i)
    {
        if(isnan(A[i]))
        {
            printf("%lu:nan ", i);
            ++total_count;
            ++col_count;
        }

        if (col_count == col_size)
        {
            printf("\n");
            col_count = 0;
        }

        if(total_count >= count_threshold)
        {
            break;
        }
    }
    if (col_count != col_size && total_count > 0)
    {
        printf("\n");
    }

    if(total_count == 0)
    {
        printf("No nan has been found.\n");
    }
}

void dump_f64_array(f64 *A, u64 count, char const *file_name)
{
    FILE *fp = fopen(file_name, "wb");
    fwrite(&count, sizeof(u64), 1, fp);
    fwrite(A, sizeof(f64) * count, 1, fp);
    fclose(fp);
}

f64 *load_f64_array(char const *file_name)
{
    FILE *fp = fopen(file_name, "rb");
    u64 count;
    fread(&count, sizeof(f64), 1, fp);
    f64 *A = x_malloc(count * sizeof(f64));
    fread(A, count * sizeof(f64), 1, fp);
    return A;
}

i64 compare_f64_arrays(f64 *A, f64 *B, u64 count)
{
    for(u64 i = 0; i < count; ++i)
    {
        if (A[i] < B[i])
        {
            return -1;
        }
        if(A[i] > B[i])
        {
            return 1;
        }
    }
    return 0;
}

void print_f64_diff(f64 value, f64 expected, char const* label)
{
    printf("---------------------------------\n");
    printf("%s:\n", label);
    printf("   value: %.14e\n", value);
    printf("expected: %.14e\n", expected);
    printf("    diff: %.14e\n", fabs(value - expected));
    printf("matched digits: %ld\n", compare_f64_values(value, expected));
    printf("---------------------------------\n");
}

#ifdef MODULE_TEST
int main(void)
{
    log_tm_println(0, "%d\n", 3141592);
    log_dbg_println(0, "%f\n", 3.141592);

    f64 A[34];
    for(i64 i = 0; i < 34; ++i)
    {
        A[i] = i * 0.1;
        if (i % 3 == 1)
        {
            A[i] = -i * 0.1;
        }

        if (i % 5 == 0)
        {
            A[i] = NAN;
        }
    }
    print_f64_array(A, 34, 10, 3);

    print_f64_array(A, 34, 5, 10);

    print_f64_values_within_bounds(A, 34, 0.1, 3.0, 5, 10, 3);

    inspect_nan(A, 34, 5, 10, "A");

    /* test dump and load f64 array */
    dump_f64_array(A, 34, "A.bin");
    printf("f64 array has been dumped to A.bin\n");
    f64 *B =  load_f64_array("A.bin");
    printf("%ld\n", compare_f64_arrays(A, B, 34));
    if(remove("A.bin") == 0)
    {
        printf("A.bin is removed.\n");
    }
    return 0;
}
#endif
