/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#include "mm.h"
#include "utf8.h"

/* UTF-8 encoding
 * 0xxxxxxx
 * 110xxxxx 10xxxxxx
 * 1110xxxx 10xxxxxx 10xxxxxx
 * 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
 * Reference: https://en.wikipedia.org/wiki/UTF-8
 */
static u8 const one_byte_mask = 0x80;
static u8 const one_byte_signature = 0x00;
static u8 const two_byte_mask = 0xE0;
static u8 const two_byte_signature = 0xC0;
static u8 const three_byte_mask = 0xF0;
static u8 const three_byte_signature = 0xE0;
static u8 const four_byte_mask = 0xF8;
static u8 const four_byte_signature = 0xF0;

u64 utf8_len(void const* buffer, u64 buffer_size)
{
    u64 len = 0;

    u8 const* p = buffer;
    u8 const* end = (u8 const*)buffer + buffer_size;
    while (p < end)
    {
        if (one_byte_signature == (*p & one_byte_mask))
        {
            ++len;
            ++p;
            continue;
        }

        if (two_byte_signature == (*p & two_byte_mask))
        {
            if (p + 1 >= end)
            {
                return len;
            }
            ++len;
            p += 2;
            continue;
        }

        if (three_byte_signature == (*p & three_byte_mask))
        {
            if (p + 2 >= end)
            {
                return len;
            }
            ++len;
            p += 3;
            continue;
        }

        if (four_byte_signature == (*p & four_byte_mask))
        {
            if (p + 3 >= end)
            {
                return len;
            }
            ++len;
            p += 4;
            continue;
        }
    }

    return len;
}

void utf8_codepoint(void const* buffer, u64 buffer_size, u32* codepoints, u64 codepoints_size)
{
    u64 codepoint_index = 0;

    u8 const* p = buffer;
    u8 const* end = (u8 const*)buffer + buffer_size;
    while (p < end)
    {
        if (one_byte_signature == (*p & one_byte_mask))
        {
            if (codepoint_index >= codepoints_size)
            {
                return;
            }
            codepoints[codepoint_index] = *p;
            ++codepoint_index;
            ++p;
            continue;
        }

        if (two_byte_signature == (*p & two_byte_mask))
        {
            if (p + 1 >= end)
            {
                return;
            }
            if (codepoint_index >= codepoints_size)
            {
                return;
            }
            codepoints[codepoint_index] = (*p & 0x1F) << 6 | (*(p + 1) & 0x3F);
            ++codepoint_index;
            p += 2;
            continue;
        }

        if (three_byte_signature == (*p & three_byte_mask))
        {
            if (p + 2 >= end)
            {
                return;
            }
            if (codepoint_index >= codepoints_size)
            {
                return;
            }
            codepoints[codepoint_index] = (*p & 0x0F) << 12 | (*(p + 1) & 0x3F) << 6 | (*(p + 2) & 0x3F);
            ++codepoint_index;
            p += 3;
            continue;
        }

        if (four_byte_signature == (*p & four_byte_mask))
        {
            if (p + 3 >= end)
            {
                return;
            }
            if (codepoint_index >= codepoints_size)
            {
                return;
            }
            codepoints[codepoint_index] = (*p & 0x07) << 18 | (*(p + 1) & 0x3F) << 12 | (*(p + 2) & 0x3F) << 6 | (*(p + 3) & 0x3F);
            ++codepoint_index;
            p += 4;
            continue;
        }
    }
}

void utf8_codepoints_to_cstr(u32* codepoints, u64 codepoints_len, char** cstr)
{
    u8* buffer = x_malloc(codepoints_len + 1);
    for (u64 i = 0; i < codepoints_len; ++i)
    {
        buffer[i] = (u8)codepoints[i];
    }
    buffer[codepoints_len] = '\0';
    *cstr = (char*)buffer;
}

void utf8_cstr_to_codepoints(char const* cstr, u32** codepoints, u64* codepoints_len)
{
    u64 cstr_len = strlen(cstr);
    u32* buffer = x_malloc(cstr_len * sizeof(u32));
    for (u64 i = 0; i < cstr_len; ++i)
    {
        buffer[i] = (u32)cstr[i];
    }
    *codepoints = buffer;
    *codepoints_len = cstr_len;
}

u32 utf8_cmp_codepoints(u32 const* codepoints1, u64 codepoints1_len, u32 const* codepoints2, u64 codepoints2_len)
{
    if (codepoints1_len != codepoints2_len)
    {
        return 0;
    }

    for (u64 i = 0; i < codepoints1_len; ++i)
    {
        if (codepoints1[i] != codepoints2[i])
        {
            return 0;
        }
    }

    return 1;
}

u32 utf8_cmp_codepoints_with_cstr(u32* codepoints, u64 codepoints_len, char const* cstr)
{
    u64 cstr_len = strlen(cstr);
    if (codepoints_len != cstr_len)
    {
        return 0;
    }

    for (u64 i = 0; i < codepoints_len; ++i)
    {
        if (codepoints[i] != (u32)cstr[i])
        {
            return 0;
        }
    }

    return 1;
}

i64 utf8_codepoints_to_i64(u32* codepoints, u64 codepoints_len)
{
    u8 buffer[codepoints_len + 1];  // len(ULLONG_MAX) == 20
    for (u64 i = 0; i < codepoints_len; ++i)
    {
        buffer[i] = (u8)codepoints[i];
    }
    buffer[codepoints_len] = '\0';

    char* end;
    i64 value = strtoll((char*)buffer, &end, 10);
    return value;
}

u64 utf8_codepoints_to_u64(u32* codepoints, u64 codepoints_len)
{
    u8 buffer[codepoints_len + 1];  // len(ULLONG_MAX) == 20
    for (u64 i = 0; i < codepoints_len; ++i)
    {
        buffer[i] = (u8)codepoints[i];
    }
    buffer[codepoints_len] = '\0';

    char* end;
    u64 value = strtoull((char*)buffer, &end, 10);
    return value;
}

f64 utf8_codepoints_to_f64(u32* codepoints, u64 codepoints_len)
{
    u8 buffer[codepoints_len + 1];  // len(ULLONG_MAX) == 20
    for (u64 i = 0; i < codepoints_len; ++i)
    {
        buffer[i] = (u8)codepoints[i];
    }
    buffer[codepoints_len] = '\0';

    char* end;
    f64 value = strtod((char*)buffer, &end);
    return value;
}

void utf8_encode(u32 codepoint, char* utf8_str)
{
    if (codepoint < 0x80)
    {
        utf8_str[0] = codepoint;
        utf8_str[1] = '\0';
    }
    else if (codepoint < 0x800)
    {
        utf8_str[0] = 0xC0 | (codepoint >> 6);
        utf8_str[1] = 0x80 | (codepoint & 0x3F);
        utf8_str[2] = '\0';
    }
    else if (codepoint < 0x10000)
    {
        utf8_str[0] = 0xE0 | (codepoint >> 12);
        utf8_str[1] = 0x80 | ((codepoint >> 6) & 0x3F);
        utf8_str[2] = 0x80 | (codepoint & 0x3F);
        utf8_str[3] = '\0';
    }
    else
    {
        utf8_str[0] = 0xF0 | (codepoint >> 18);
        utf8_str[1] = 0x80 | ((codepoint >> 12) & 0x3F);
        utf8_str[2] = 0x80 | ((codepoint >> 6) & 0x3F);
        utf8_str[3] = 0x80 | (codepoint & 0x3F);
        utf8_str[4] = '\0';
    }
}

void utf8_print_codepoints(u32* codepoints, u64 codepoints_len, char* end)
{
    setlocale(LC_ALL, "");
    for (u64 i = 0; i < codepoints_len; ++i)
    {
        char utf8_str[8];
        utf8_encode(codepoints[i], utf8_str);
        printf("%s", utf8_str);
    }
    printf("%s", end);
}

#ifdef MODULE_TEST
#include <stdio.h>
int main(void)
{
    /* Seven utf-8 characters: 1 one-byte char, 2 two-bytes chars, 3 three-bytes chars, 1 four-bytes char */
    u8 const s[] = {0x24, 0xc2, 0xa3, 0xd0, 0x98, 0xe0, 0xa4, 0xb9, 0xe2,
                    0x82, 0xac, 0xed, 0x95, 0x9c, 0xf0, 0x90, 0x8d, 0x88};
    u64 len = utf8_len(s, sizeof(s));
    u32 codepoints[len];
    utf8_codepoint(s, sizeof(s), codepoints, len);
    printf("len: %lu\n", len);
    for (u64 i = 0; i < len; ++i)
    {
        printf("codepoint: %04lX\n", codepoints[i]);
    }

    utf8_print_codepoints(codepoints, len, "\n");

    return 0;
}
#endif
