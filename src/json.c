/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include "io.h"
#include "mm.h"
#include "utf8.h"
#include "json.h"

#include <stdio.h>
#include <string.h>

// structural characters
static u32 const UTF8_LEFT_SQUARE_BRACKET = 0x5B;
static u32 const UTF8_RIGHT_SQUARE_BRACKET = 0x5D;
static u32 const UTF8_LEFT_CURLY_BRACKET = 0x7B;
static u32 const UTF8_RIGHT_CURLY_BRACKET = 0x7D;
static u32 const UTF8_COLON = 0x3A;
static u32 const UTF8_COMMA = 0x2C;

// whitespace characters
static u32 const UTF8_SPACE = 0x20;
static u32 const UTF8_TAB = 0x09;
static u32 const UTF8_NEWLINE = 0x0A;
static u32 const UTF8_CARRIAGE_RETURN = 0x0D;

// number characters
static u32 const UTF8_MINUS = 0x2D;
static u32 const UTF8_PLUS = 0x2B;
static u32 const UTF8_ZERO = 0x30;
static u32 const UTF8_ONENINE[] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39}; // 1-9
static u32 const UTF8_PERIOD = 0x2E;
static u32 const UTF8_e = 0x65;
static u32 const UTF8_E = 0x45;

// string characters
static u32 const UTF8_QUOTATION_MARK = 0x22;
static u32 const UTF8_BACKSLASH = 0x5C;
static u32 const UTF8_SLASH = 0x2F;
static u32 const UTF8_BACKSPACE = 0x08;
static u32 const UTF8_FORM_FEED = 0x0C;

// control characters
static u32 const UTF8_b = 0x62;
static u32 const UTF8_f = 0x66;
static u32 const UTF8_n = 0x6E;
static u32 const UTF8_r = 0x72;
static u32 const UTF8_t = 0x74;
static u32 const UTF8_u = 0x75;

// literals
static u32 const UTF8_FALSE[] = {0x66, 0x61, 0x6C, 0x73, 0x65};
static u32 const UTF8_TRUE[] = {0x74, 0x72, 0x75, 0x65};
static u32 const UTF8_NULL[] = {0x6E, 0x75, 0x6C, 0x6C};

// token types
static u64 const JSON_TOKEN_TYPE_STRUCTURAL = 0;
static u64 const JSON_TOKEN_TYPE_LITERAL = 1;
static u64 const JSON_TOKEN_TYPE_NUMBER = 2;
static u64 const JSON_TOKEN_TYPE_STRING = 3;

/*
 * Takes as input a string of UTF-8 code points that may contain backslash and quotation mark escape sequences, escape them and returns the length of the unescaped string.
 * utf8_codepoints is the string of UTF-8 code points.
 * utf8_codepoints_len is the length of the utf8_codepoints array.
 * unescaped_codepoints is the array for holding the unescaped UTF-8 code points, with the same size as utf8_codepoints.
 * unescaped_codepoints_len is the length of the unescaped_codepoints array.
 */
u64 unescape_json_string(u32 *utf8_codepoints, u64 utf8_codepoints_len, u32 *unescaped_codepoints)
{
    u64 escaped_cp_idx = 0;   // escaped codepoint index
    u64 unescaped_cp_idx = 0; // unescaped codepoint index
    while (escaped_cp_idx < utf8_codepoints_len)
    {
        u32 codepoint = utf8_codepoints[escaped_cp_idx++];
        if (codepoint != UTF8_BACKSLASH)
        {
            unescaped_codepoints[unescaped_cp_idx++] = codepoint;
            continue;
        }

        codepoint = utf8_codepoints[escaped_cp_idx++];
        if (codepoint == UTF8_QUOTATION_MARK || codepoint == UTF8_BACKSLASH)
        {
            unescaped_codepoints[unescaped_cp_idx++] = codepoint;
            continue;
        }
        else
        {
            printf("Error: invalid escape sequence\n");
        }
    }

    return unescaped_cp_idx;
}

static u64 unescape_control_chars(u32 *utf8_codepoints, u64 utf8_codepoints_len, u32 *unescaped_codepoints)
{
    u64 escaped_cp_idx = 0;   // escaped codepoint index
    u64 unescaped_cp_idx = 0; // unescaped codepoint index
    while (escaped_cp_idx < utf8_codepoints_len)
    {
        u32 codepoint = utf8_codepoints[escaped_cp_idx++];
        if (codepoint != UTF8_BACKSLASH)
        {
            unescaped_codepoints[unescaped_cp_idx++] = codepoint;
            continue;
        }

        codepoint = utf8_codepoints[escaped_cp_idx++];

        if (codepoint == UTF8_QUOTATION_MARK || codepoint == UTF8_BACKSLASH)
        {
            unescaped_codepoints[unescaped_cp_idx++] = UTF8_BACKSLASH;
            unescaped_codepoints[unescaped_cp_idx++] = codepoint;
            continue;
        }

        switch (codepoint)
        {
        case (i32)UTF8_SLASH: // the type conversion is to make some old compilers happy
        {
            unescaped_codepoints[unescaped_cp_idx++] = UTF8_SLASH;
            break;
        }
        case (i32)UTF8_b:
        {
            unescaped_codepoints[unescaped_cp_idx++] = UTF8_BACKSPACE;
            break;
        }
        case (i32)UTF8_f:
        {
            unescaped_codepoints[unescaped_cp_idx++] = UTF8_FORM_FEED;
            break;
        }
        case (i32)UTF8_n:
        {
            unescaped_codepoints[unescaped_cp_idx++] = UTF8_NEWLINE;
            break;
        }
        case (i32)UTF8_r:
        {
            unescaped_codepoints[unescaped_cp_idx++] = UTF8_CARRIAGE_RETURN;
            break;
        }
        case (i32)UTF8_t:
        {
            unescaped_codepoints[unescaped_cp_idx++] = UTF8_TAB;
            break;
        }
        case (i32)UTF8_u:
        {
            // unescape unicode character \u hex hex hex hex
            u8 hex[5];
            hex[4] = '\0';
            for (u64 i = 0; i < 4; ++i)
            {
                hex[i] = (u8)utf8_codepoints[escaped_cp_idx++];
            }

            u32 unicode_codepoint = strtoul((char *)hex, NULL, 16);
            unescaped_codepoints[unescaped_cp_idx++] = unicode_codepoint;

            break;
        }
        }
    }

    return unescaped_cp_idx;
}

/*
 * Reads a JSON file into an array of UTF-8 code points.
 * json_path is the path to the JSON file.
 * codepoints [out] is the array for holding the UTF-8 code points
 * codepoints_len [out] is the length of the codepoints array.
 * _ot (ownership transfer) indicates that the function will transfer the ownership of the allocated buffer to the caller.
 */
void read_json_into_codepoints_ot(char const *json_path, u32 **utf8_codepoints, u64 *utf8_codepoints_len)
{
    void *buffer;
    u64 file_size;
    read_file_to_buffer_ot(json_path, &buffer, &file_size);

    u64 len = utf8_len(buffer, file_size);
    u32 *codepoints = x_malloc(sizeof(u32) * len);
    utf8_codepoint(buffer, file_size, codepoints, len);
    x_free(buffer);

    u32 *codepoints_unescaped = x_malloc(sizeof(u32) * len);
    len = unescape_control_chars(codepoints, len, codepoints_unescaped);
    x_free(codepoints);

    *utf8_codepoints = codepoints_unescaped;
    *utf8_codepoints_len = len;
}

static bool is_digit(u32 codepoint)
{
    return codepoint >= UTF8_ZERO && codepoint <= UTF8_ONENINE[8];
}

static bool is_sign(u32 codepoint)
{
    return codepoint == UTF8_MINUS || codepoint == UTF8_PLUS;
}

/*
 * json literals: true, false, null
 */
static u64 json_literal_token(u32 *utf8_codepoints, u64 idx, u64 utf8_codepoints_len)
{
    u64 len = 0;
    u64 i = idx;
    if ((i + 4) > utf8_codepoints_len) // a json literal is at least 4 code points long
    {
        return 0;
    }

    u32 codepoint = utf8_codepoints[i];
    if (codepoint == UTF8_NULL[0])
    {
        if (memcmp(&utf8_codepoints[i], UTF8_NULL, sizeof(UTF8_NULL)) == 0)
        {
            len = 4;
            return len;
        }
    }
    else if (codepoint == UTF8_TRUE[0])
    {
        if (memcmp(&utf8_codepoints[i], UTF8_TRUE, sizeof(UTF8_TRUE)) == 0)
        {
            len = 4;
            return len;
        }
    }
    else if (codepoint == UTF8_FALSE[0])
    {
        if ((i + 5) > utf8_codepoints_len) // false is 5 code points long
        {
            return 0;
        }

        if (memcmp(&utf8_codepoints[i], UTF8_FALSE, sizeof(UTF8_FALSE)) == 0)
        {
            len = 5;
            return len;
        }
    }

    return 0;
}

/*
 * json_string_token takes a string of UTF-8 code points and returns the length of the string token.
 * utf8_codepoints is the string of UTF-8 code points.
 * idx is the index of the first code point of the string token.
 * utf8_codepoints_len is the length of the utf8_codepoints array.
 * returns the length of the number token.
 */
static u64 json_number_token(u32 *utf8_codepoints, u64 idx, u64 utf8_codepoints_len)
{
    u64 len = 0;
    u64 i = idx;

    while (i < utf8_codepoints_len)
    {
        u32 codepoint = utf8_codepoints[i];
        if (is_sign(codepoint) || is_digit(codepoint) || codepoint == UTF8_PERIOD || codepoint == UTF8_e || codepoint == UTF8_E)
        {
            ++i;
            ++len;
            continue;
        }
        else
        {
            break;
        }
    }
    return len;
}

u64 json_tokenize_ot(u32 *utf8_codepoints, u64 utf8_codepoints_len, struct json_token **output_tokens)
{
    u64 idx = 0;

    struct json_token *tokens = x_malloc(sizeof(struct json_token) * utf8_codepoints_len);
    u64 token_idx = 0;

    while (idx < utf8_codepoints_len)
    {
        u32 codepoint = utf8_codepoints[idx];

        if (codepoint == UTF8_SPACE || codepoint == UTF8_TAB || codepoint == UTF8_NEWLINE || codepoint == UTF8_CARRIAGE_RETURN)
        {
            ++idx;
            continue;
        }

        if (codepoint == UTF8_LEFT_SQUARE_BRACKET ||
            codepoint == UTF8_RIGHT_SQUARE_BRACKET ||
            codepoint == UTF8_LEFT_CURLY_BRACKET ||
            codepoint == UTF8_RIGHT_CURLY_BRACKET ||
            codepoint == UTF8_COLON ||
            codepoint == UTF8_COMMA)
        {
            struct json_token *structural_token = &tokens[token_idx++];
            structural_token->type = JSON_TOKEN_TYPE_STRUCTURAL;
            structural_token->start = idx;
            ++idx;
            structural_token->end = idx;
        }

        if (codepoint == UTF8_QUOTATION_MARK)
        {
            struct json_token *string_token = &tokens[token_idx++];
            string_token->type = JSON_TOKEN_TYPE_STRING;
            idx++;
            string_token->start = idx;
            while (utf8_codepoints[idx] != UTF8_QUOTATION_MARK)
            {
                if (utf8_codepoints[idx] == UTF8_BACKSLASH)
                {
                    ++idx;
                }
                ++idx;
            }
            string_token->end = idx;
            idx++;
        }

        if (codepoint == UTF8_MINUS || is_digit(codepoint))
        {
            struct json_token *number_token = &tokens[token_idx++];
            number_token->type = JSON_TOKEN_TYPE_NUMBER;
            number_token->start = idx;
            idx += json_number_token(utf8_codepoints, idx, utf8_codepoints_len);
            number_token->end = idx;
        }

        u64 literal_token_len = json_literal_token(utf8_codepoints, idx, utf8_codepoints_len);
        if (literal_token_len > 0)
        {
            struct json_token *literal_token = &tokens[token_idx++];
            literal_token->type = JSON_TOKEN_TYPE_LITERAL;
            literal_token->start = idx;
            idx += literal_token_len;
            literal_token->end = idx;
        }
    }

    *output_tokens = tokens;

    return token_idx;
}

static u64 token_type2value_type(u64 token_type, u32 first_codepoint)
{
    if (token_type == JSON_TOKEN_TYPE_LITERAL)
    {
        return JSON_VALUE_TYPE_LITERAL;
    }
    if (token_type == JSON_TOKEN_TYPE_NUMBER)
    {
        return JSON_VALUE_TYPE_NUMBER;
    }
    if (token_type == JSON_TOKEN_TYPE_STRING)
    {
        return JSON_VALUE_TYPE_STRING;
    }

    if (token_type == JSON_TOKEN_TYPE_STRUCTURAL)
    {
        if (first_codepoint == UTF8_LEFT_SQUARE_BRACKET)
        {
            return JSON_VALUE_TYPE_ARRAY;
        }
        if (first_codepoint == UTF8_LEFT_CURLY_BRACKET)
        {
            return JSON_VALUE_TYPE_OBJECT;
        }
    }

    return JSON_NONVALUE_TYPE;
}

/*
 * This function parses a JSON string encoded in UTF-8 code points into a JSON struct.
 * utf8_codepoints is the string of UTF-8 code points.
 * utf8_codepoints_len is the length of the utf8_codepoints array.
 * returns a pointer to the JSON struct.
 * Note this is a recursive function.
 */
struct json *decode_json_tokens_ot(u32 *utf8_codepoints, struct json_token *tokens, u64 *token_idx, u64 tokens_len)
{
    if (*token_idx >= tokens_len)
    {
        return NULL;
    }

    struct json_token *token = &tokens[*token_idx];

    u64 value_type = token_type2value_type(token->type, utf8_codepoints[token->start]);
    if (value_type == JSON_NONVALUE_TYPE)
    {
        return NULL;
    }

    struct json *json = x_malloc(sizeof(struct json));
    json->type = value_type;
    json->child = NULL;
    json->next = NULL;

    if (json->type == JSON_VALUE_TYPE_LITERAL || json->type == JSON_VALUE_TYPE_STRING || json->type == JSON_VALUE_TYPE_NUMBER)
    {
        json->codepoints = &utf8_codepoints[token->start];
        json->length = token->end - token->start;
        ++(*token_idx);
        return json;
    }

    if (json->type == JSON_VALUE_TYPE_ARRAY)
    {
        json->length = 0;
        ++(*token_idx);
        struct json *child = NULL;
        struct json *next = NULL;
        do
        {
            child = decode_json_tokens_ot(utf8_codepoints, tokens, token_idx, tokens_len);

            if (NULL == child)
            {
                struct json_token *current_token = &tokens[*token_idx];
                if (current_token->type == JSON_TOKEN_TYPE_STRUCTURAL && utf8_codepoints[current_token->start] == UTF8_RIGHT_SQUARE_BRACKET)
                {
                    ++(*token_idx);
                    break;
                }
                else if (current_token->type == JSON_TOKEN_TYPE_STRUCTURAL && utf8_codepoints[current_token->start] == UTF8_COMMA)
                {
                    ++(*token_idx);
                    continue;
                }
                else
                {
                    printf("Error: invalid JSON array.\n");
                    x_free(json);
                    return NULL;
                }
            }
            else
            {
                if (NULL == json->child)
                {
                    json->child = child;
                }
                else
                {
                    next->next = child;
                }
                next = child;
                ++(json->length);
            }
        } while (1);

        return json;
    }

    if (json->type == JSON_VALUE_TYPE_OBJECT)
    {
        json->length = 0;
        ++(*token_idx);
        struct json *child = NULL;
        struct json *next = NULL;

        do
        {
            child = decode_json_tokens_ot(utf8_codepoints, tokens, token_idx, tokens_len);
            if (NULL == child)
            {
                struct json_token *current_token = &tokens[*token_idx];
                if (current_token->type == JSON_TOKEN_TYPE_STRUCTURAL && utf8_codepoints[current_token->start] == UTF8_RIGHT_CURLY_BRACKET)
                {
                    ++(*token_idx);
                    break;
                }
                else if (current_token->type == JSON_TOKEN_TYPE_STRUCTURAL && utf8_codepoints[current_token->start] == UTF8_COMMA)
                {
                    ++(*token_idx);
                    continue;
                }
                else
                {
                    printf("Error: invalid JSON object.\n");
                    x_free(json);
                    return NULL;
                }
            }
            else
            {
                if (child->type == JSON_VALUE_TYPE_STRING)
                {
                    ++(*token_idx);
                    struct json *value = decode_json_tokens_ot(utf8_codepoints, tokens, token_idx, tokens_len);
                    if (NULL == value)
                    {
                        printf("Error: invalid json member value object.\n");
                        return NULL;
                    }
                    else
                    {
                        child->next = value;
                        if (NULL == json->child)
                        {
                            json->child = child;
                        }
                        else
                        {
                            next->next = child;
                        }

                        next = value;

                        ++(json->length);
                    }
                }
                else
                {
                    printf("Error: invalid json member name json object.\n");
                    x_free(json);
                    return NULL;
                }
            }

        } while (1);

        return json;
    }

    return json;
}

void free_json(struct json *json)
{
    if (json->type == JSON_VALUE_TYPE_ARRAY || json->type == JSON_VALUE_TYPE_OBJECT)
    {
        struct json *child = json->child;
        while (child != NULL)
        {
            struct json *next = child->next;
            free_json(child);
            child = next;
        }
    }
    x_free(json);
}

struct json *find_json_obj_member_by_codepoints(struct json *json_obj, u32 const *codepoints, u64 codepoints_len)
{
    struct json *child = json_obj->child;

    while (child != NULL)
    {
        if (cmp_utf8_codepoints(child->codepoints, child->length, codepoints, codepoints_len))
        {
            return child->next;
        }
        child = child->next;
        if (child != NULL)
        {
            child = child->next; // skip the value
        }
    }
    return NULL;
}

struct json *find_json_obj_member_by_name(struct json *json_obj, char const *name)
{
    struct json *child = json_obj->child;

    while (child != NULL)
    {
        if (cmp_utf8_with_cstr(child->codepoints, child->length, name))
        {
            return child->next;
        }
        child = child->next;
        if (child != NULL)
        {
            child = child->next; // skip the value
        }
    }
    return NULL;
}

void print_json(struct json *json)
{
    if (json->type == JSON_VALUE_TYPE_ARRAY)
    {
        printf("[");
        struct json *child = json->child;
        while (child != NULL)
        {
            print_json(child);
            child = child->next;
            if (child != NULL)
            {
                printf(", ");
            }
        }
        printf("]");
    }
    else if (json->type == JSON_VALUE_TYPE_OBJECT)
    {
        printf("{");
        struct json *child = json->child;
        u64 idx = 0;
        while (child != NULL)
        {
            print_json(child);
            idx++;
            child = child->next;
            if (child != NULL)
            {
                if (idx % 2 == 0)
                {
                    printf(", ");
                }
                else
                {
                    printf(": ");
                }
            }
        }
        printf("}");
    }
    else if (json->type == JSON_VALUE_TYPE_LITERAL)
    {
        char *literal = NULL;
        utf8tocstr(json->codepoints, json->length, &literal);
        printf("%s", literal);
        x_free(literal);
    }
    else if (json->type == JSON_VALUE_TYPE_NUMBER)
    {
        char *number = NULL;
        utf8tocstr(json->codepoints, json->length, &number);
        printf("%s", number);
        x_free(number);
    }
    else if (json->type == JSON_VALUE_TYPE_STRING)
    {
        u32 *unescaped_codepoints = x_malloc(sizeof(u32) * json->length);
        unescape_json_string(json->codepoints, json->length, unescaped_codepoints);

        char *string = NULL;
        utf8tocstr(unescaped_codepoints, json->length, &string);
        x_free(unescaped_codepoints);

        printf("\"%s\"", string);
        x_free(string);
    }
    else
    {
        printf("Error: invalid JSON value type.\n");
    }
}

#ifdef MODULE_TEST
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <libgen.h>

void print_json_tokens(u32 *utf8_codepoints, struct json_token *tokens, u64 tokens_len)
{
    for (u64 i = 0; i < tokens_len; ++i)
    {
        struct json_token *token = &tokens[i];
        printf("token %lu (%lu): ", i, token->type);
        for (u64 j = token->start; j < token->end; ++j)
        {
            printf("%c", (char)utf8_codepoints[j]);
        }
        printf("\n");
        if (i > 64)
        {
            printf("...");
            break;
        }
    }
}

int test_unescape_string()
{
    u32 utf8_codepoints[] = {UTF8_BACKSLASH, UTF8_QUOTATION_MARK, UTF8_BACKSLASH, UTF8_BACKSLASH, UTF8_SLASH, UTF8_BACKSLASH, UTF8_b, UTF8_BACKSLASH, UTF8_f, UTF8_BACKSLASH, UTF8_n, UTF8_BACKSLASH, UTF8_r, UTF8_BACKSLASH, UTF8_t, UTF8_BACKSLASH};
    u64 utf8_codepoints_len = sizeof(utf8_codepoints) / sizeof(u32);
    printf("utf8_codepoints_len: %lu\n", utf8_codepoints_len);
    u32 *unescaped_codepoints = x_malloc(sizeof(u32) * utf8_codepoints_len);
    u64 unescaped_codepoints_len = unescape_control_chars(utf8_codepoints, utf8_codepoints_len, unescaped_codepoints);
    printf("unescaped_codepoints_len: %lu\n", unescaped_codepoints_len);

    printf("unescaped_codepoints: \n");
    for (u64 i = 0; i < unescaped_codepoints_len; ++i)
    {
        printf("%04lX ", unescaped_codepoints[i]);
    }

    printf("\n");

    x_free(unescaped_codepoints);

    return 0;
}

int test_read_json_file(char *program_path)
{
    char buffer[PATH_MAX];
    char parent_dir_buffer[PATH_MAX];
    char json_file[PATH_MAX + 128];
    char json_file_abspath[PATH_MAX];

    if (realpath(program_path, buffer) == NULL)
    {
        perror("Error finding absolute file path");
        return 1;
    }

    // Get the parent directory path
    char *parentDir = dirname(buffer);
    if (realpath(parentDir, parent_dir_buffer) == NULL)
    {
        perror("Error finding parent directory path");
        return 1;
    }

    sprintf(json_file, "%s/../../../sample/sample.json", parent_dir_buffer);

    if (realpath(json_file, json_file_abspath) == NULL)
    {
        perror("Error finding absolute file path for basis set directory");
        return 1;
    }

    printf("reading json_file: %s\n", json_file_abspath);

    u32 *codepoints;
    u64 codepoints_len;
    read_json_into_codepoints_ot(json_file_abspath, &codepoints, &codepoints_len);
    for (u64 i = 0; i < codepoints_len; ++i)
    {
        printf("%c", (char)codepoints[i]);
        if (i > 256)
        {
            printf("...");
            break;
        }
    }
    printf("\n");
    printf("codepoints_len: %lu\n", codepoints_len);
    printf("---------------------------------\n");

    struct json_token *tokens;
    u64 tokens_len = json_tokenize_ot(codepoints, codepoints_len, &tokens);
    printf("tokens_len: %lu\n", tokens_len);
    print_json_tokens(codepoints, tokens, tokens_len);
    printf("---------------------------------\n");

    u64 token_index = 0;
    struct json *json = decode_json_tokens_ot(codepoints, tokens, &token_index, tokens_len);
    print_json(json);

    free_json(json);
    x_free(tokens);
    x_free(codepoints);
    printf("\n");
    return 0;
}

int main(int argc, char *argv[])
{
    test_read_json_file(argv[0]);
    test_unescape_string();

    print_mm_status();
    return 0;
}
#endif
