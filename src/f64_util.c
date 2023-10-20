/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "numeric_types.h"

i32 char_to_digit(char c)
{
    i32 ascii_code = (i32)c;
    return ascii_code - 48; // the ascii code for 0 is 48
}

char digit_to_char(i32 d)
{
    i32 ascii_code = d + 48;
    return (char)ascii_code;
}

/*
 * Get the index of dot (.) in a string representing a f64 number
 * e.g. "-7.496469771270e+01"
 */
i32 pos_of_dot(char* s, i32 size)
{
    for (i32 i = 0; i < size; ++i)
    {
        if (s[i] == '.')
        {
            return i;
        }
    }
    return -1;
}

i32 get_exponent(char* s, i32 size)
{
    for (i32 i = 0; i < size; ++i)
    {
        if (s[i] == 'e' || s[i] == 'E')
        {
            return atoi(s + i + 1);
        }
    }
    return 0;
}

i32 f64_sign(f64 value)
{
    if (value > 0.0)
    {
        return 1;
    }
    if (value < 0.0)
    {
        return -1;
    }
    return 0;
}

/*
 * Round a f64 value to a %.ne string.
 * 0 <= n <= 14
 * Why do we need such a function?
 * As decimals cannot be accurately represented as f64,
 * snprintf(...) will not output desirable results for some numbers
 * such as -7.49646977125e+01.
 * TODO: test boundary cases
 */
i32 round_f64_to_string(f64 value, i64 n, char* buff, i32 size)
{
    char const* fmt_ = "%%.%lde";
    int buff_size_ = snprintf(NULL, 0, fmt_, n);
    char buff_[buff_size_ + 1]; // +1 for terminating null
    snprintf(buff_, sizeof(buff_), fmt_, n);

    char const* fmt = buff_;

    int buff_size = snprintf(NULL, 0, fmt, value);

    if (buff == NULL)
    {
        return buff_size;
    }

    snprintf(buff, size, fmt, value);
    if (n == 16)
    {
        return size - 1;
    }

    char const* value_fmt = "%.15e";
    int value_buff_size = snprintf(NULL, 0, value_fmt, value);
    char value_buff[value_buff_size + 1]; // +1 for terminating null
    snprintf(value_buff, sizeof(value_buff), value_fmt, value);

    i32 dot_pos = pos_of_dot(value_buff, value_buff_size);
    i32 last_digit_index = dot_pos + n;

    if (char_to_digit(value_buff[last_digit_index + 1]) > 4)
    {
        i32 exponent = last_digit_index + get_exponent(value_buff, value_buff_size);
        f64 value_ = value + f64_sign(value) * pow(10, -exponent);
        snprintf(buff, size, fmt, value_);
        return size - 1;
    }

    return size - 1;
}

/*
 * Return the number of fraction digits that match in scientific notation.
 */
i64 compare_f64_values(f64 value, f64 expected)
{
    for (i64 n = 16; n >= 0; --n)
    {
        i32 value_buff_size = round_f64_to_string(value, n, NULL, 0);
        char value_buff[value_buff_size + 1];
        round_f64_to_string(value, n, value_buff, sizeof(value_buff));

        i32 expected_buff_size = round_f64_to_string(expected, n, NULL, 0);
        char expected_buff[expected_buff_size + 1];
        round_f64_to_string(expected, n, expected_buff, sizeof(expected_buff));

        if (!strcmp(value_buff, expected_buff))
        {
            return n;
        }
    }
    return -1;
}
