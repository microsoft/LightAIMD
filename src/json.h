/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef JSON_H
#define JSON_H

#include "numeric_types.h"

#define JSON_NONVALUE_TYPE 0
#define JSON_VALUE_TYPE_LITERAL 1
#define JSON_VALUE_TYPE_NUMBER 2
#define JSON_VALUE_TYPE_STRING 3
#define JSON_VALUE_TYPE_ARRAY 4
#define JSON_VALUE_TYPE_OBJECT 5

#define JSON_LITERAL_TRUE 1
#define JSON_LITERAL_FALSE 0
#define JSON_LITERAL_NULL -1

#define JSON_NUMBER_TYPE_INTEGER 0
#define JSON_NUMBER_TYPE_DECIMAL 1

// JSON is specified by RFC 7159.
struct json
{
    u32 *codepoints; // utf8 code points for the json value
    u64 length;      // length of codepoints (for literal, number, and string), array, object

    i64 type;           // type of the json value
    struct json *child; // point to the first json value in the array or object
    struct json *next;  // point to the next json value in the same array or object
};

struct json_token
{
    u64 type;
    u64 start; // inclusive: the index of the first codepoint of the token
    u64 end;   // exclusive: the index of the first codepoint after the token
};

u64 unescape_json_string(u32 *utf8_codepoints, u64 utf8_codepoints_len, u32 *unescaped_codepoints);
void read_json_into_codepoints_ot(char const *json_path, u32 **utf8_codepoints, u64 *utf8_codepoints_len);
u64 json_tokenize_ot(u32 *utf8_codepoints, u64 utf8_codepoints_len, struct json_token **output_tokens);
struct json *decode_json_tokens_ot(u32 *utf8_codepoints, struct json_token *tokens, u64 *token_idx, u64 tokens_len);
void free_json(struct json *json);
struct json *find_json_obj_member_by_codepoints(struct json *json_obj, u32 const *codepoints, u64 codepoints_len);
struct json *find_json_obj_member_by_name(struct json *json_obj, char const *name);
void print_json(struct json *json);

#endif
