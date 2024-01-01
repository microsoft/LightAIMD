/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <stdio.h>
#include <string.h>
#include "mm.h"
#include "utf8.h"
#include "json.h"
#include "basis_set.h"

static u32 const UTF8_CODEPOINTS_ELEMENTS[] = {'e', 'l', 'e', 'm', 'e', 'n', 't', 's'};                                                 // elements
static u32 const UTF8_CODEPOINTS_ELECTRON_SHELLS[] = {'e', 'l', 'e', 'c', 't', 'r', 'o', 'n', '_', 's', 'h', 'e', 'l', 'l', 's'};       // electron_shells
static u32 const UTF8_CODEPOINTS_EXPONENTS[] = {'e', 'x', 'p', 'o', 'n', 'e', 'n', 't', 's'};                                           // exponents
static u32 const UTF8_CODEPOINTS_COEFFICIENTS[] = {'c', 'o', 'e', 'f', 'f', 'i', 'c', 'i', 'e', 'n', 't', 's'};                         // coefficients
static u32 const UTF8_CODEPOINTS_ANGULAR_MOMENTUM[] = {'a', 'n', 'g', 'u', 'l', 'a', 'r', '_', 'm', 'o', 'm', 'e', 'n', 't', 'u', 'm'}; // angular_momentum

char* load_basis_set_from_file(char const* basis_set_filepath, u64 n_selected_elements, u64* selected_elements)
{
    u64 filepath_len = strlen(basis_set_filepath);
    u64 sanitized_filepath_len = filepath_len * 4 + 1; // replace '*' with "_st_"
    char* sanitized_filepath = x_malloc(sanitized_filepath_len);

    u64 filepath_idx = 0;
    u64 sanitized_filepath_idx = 0;
    while (filepath_idx <= filepath_len) // include the null terminator
    {
        if (basis_set_filepath[filepath_idx] == '*')
        {
            sanitized_filepath[sanitized_filepath_idx++] = '_';
            sanitized_filepath[sanitized_filepath_idx++] = 's';
            sanitized_filepath[sanitized_filepath_idx++] = 't';
            sanitized_filepath[sanitized_filepath_idx++] = '_';
            ++filepath_idx;
        }
        else
        {
            sanitized_filepath[sanitized_filepath_idx++] = basis_set_filepath[filepath_idx++];
        }
    }

    u32* codepoints;
    u64 codepoints_len;
    json_read_into_codepoints_ot(sanitized_filepath, &codepoints, &codepoints_len);
    x_free(sanitized_filepath);
    struct json_token* tokens;
    u64 tokens_len = json_tokenize_ot(codepoints, codepoints_len, &tokens);
    u64 token_index = 0;
    struct json* json = json_decode_tokens_ot(codepoints, tokens, &token_index, tokens_len);
    x_free(tokens);

    u64 bc = sizeof(u64); /* byte count, initial value: space for number of elements */
    u64 n_found_elements = 0;
    struct json* elements = json_find_obj_member_by_codepoints(json, UTF8_CODEPOINTS_ELEMENTS, sizeof(UTF8_CODEPOINTS_ELEMENTS) / sizeof(u32));

    struct json* element = elements->child;
    while (element != NULL)
    {
        u64 Z = utf8_codepoints_to_u64(element->codepoints, element->length);
        u64* s = selected_elements;
        u64 found = 0;
        for (u64 r = 0; r < n_selected_elements; ++r)
        {
            if (Z == *s)
            {
                found = 1;
            }
            ++s;
        }

        if (found)
        {
            ++n_found_elements;
            bc += sizeof(u64) * 2;
            struct json* electron_shells = json_find_obj_member_by_codepoints(element->next, UTF8_CODEPOINTS_ELECTRON_SHELLS, sizeof(UTF8_CODEPOINTS_ELECTRON_SHELLS) / sizeof(u32));
            struct json* electron_shell = electron_shells->child;
            while (electron_shell != NULL)
            {
                struct json* exponents = json_find_obj_member_by_codepoints(electron_shell, UTF8_CODEPOINTS_EXPONENTS, sizeof(UTF8_CODEPOINTS_EXPONENTS) / sizeof(u32));
                u64 n_exponents = exponents->length;
                struct json* angular_momentum = json_find_obj_member_by_codepoints(electron_shell, UTF8_CODEPOINTS_ANGULAR_MOMENTUM, sizeof(UTF8_CODEPOINTS_ANGULAR_MOMENTUM) / sizeof(u32));
                struct json* am = angular_momentum->child;
                while (am != NULL)
                {
                    u64 k = utf8_codepoints_to_u64(am->codepoints, am->length);
                    u64 n_orbitals = ((k + 1) * (k + 2)) >> 1;
                    bc += n_orbitals * (sizeof(u64) * 4 + n_exponents * sizeof(f64) * 2);
                    am = am->next;
                }
                electron_shell = electron_shell->next;
            }
        }

        element = element->next;
        if (element != NULL)
        {
            element = element->next; // skip the value
        }
    }

    u64* buffer = (u64*)x_malloc(bc);
    u64* p = buffer;
    *p = n_found_elements;
    ++p;

    element = elements->child;
    while (element != NULL)
    {
        u64 Z = utf8_codepoints_to_u64(element->codepoints, element->length);
        u64* s = selected_elements;
        u64 found = 0;
        for (u64 r = 0; r < n_selected_elements; ++r)
        {
            if (Z == *s)
            {
                found = 1;
            }
            ++s;
        }

        if (found)
        {
            *p = Z;
            ++p;
            u64* n_orbitals_p = p;
            ++p; // skip the n_orbitals as we do not know its value yet
            u64 n_orbitals = 0;
            struct json* electron_shells = json_find_obj_member_by_codepoints(element->next, UTF8_CODEPOINTS_ELECTRON_SHELLS, sizeof(UTF8_CODEPOINTS_ELECTRON_SHELLS) / sizeof(u32));
            struct json* electron_shell = electron_shells->child;
            while (electron_shell != NULL)
            {
                struct json* exponents = json_find_obj_member_by_codepoints(electron_shell, UTF8_CODEPOINTS_EXPONENTS, sizeof(UTF8_CODEPOINTS_EXPONENTS) / sizeof(u32));
                u64 n_exponents = exponents->length;
                struct json* coefficients = json_find_obj_member_by_codepoints(electron_shell, UTF8_CODEPOINTS_COEFFICIENTS, sizeof(UTF8_CODEPOINTS_COEFFICIENTS) / sizeof(u32));
                u64 am_index = 0;
                struct json* angular_momentum = json_find_obj_member_by_codepoints(electron_shell, UTF8_CODEPOINTS_ANGULAR_MOMENTUM, sizeof(UTF8_CODEPOINTS_ANGULAR_MOMENTUM) / sizeof(u32));
                struct json* am = angular_momentum->child;
                while (am != NULL)
                {
                    u64 k = utf8_codepoints_to_u64(am->codepoints, am->length);

                    for (i64 l = k; l >= 0; --l)
                    {
                        for (i64 m = k - l; m >= 0; --m)
                        {
                            u64 n = k - l - m;
                            *p = l;
                            ++p;
                            *p = m;
                            ++p;
                            *p = n;
                            ++p;
                            *p = n_exponents;
                            ++p;

                            struct json* exponent = exponents->child;
                            while (exponent != NULL)
                            {
                                *((f64*)p) = utf8_codepoints_to_f64(exponent->codepoints, exponent->length);
                                ++p;
                                exponent = exponent->next;
                            }

                            struct json* coefficient = coefficients->child;
                            u64 coefficient_index = 0;
                            while (coefficient != NULL)
                            {
                                if (coefficient_index == am_index)
                                {
                                    struct json* coeff = coefficient->child;
                                    while (coeff != NULL)
                                    {
                                        *((f64*)p) = utf8_codepoints_to_f64(coeff->codepoints, coeff->length);
                                        ++p;
                                        coeff = coeff->next;
                                    }
                                    break;
                                }
                                coefficient = coefficient->next;
                                ++coefficient_index;
                            }
                            ++n_orbitals;
                        }
                    }

                    am = am->next;
                    ++am_index;
                }
                electron_shell = electron_shell->next;
            }
            *n_orbitals_p = n_orbitals;
        }

        element = element->next;
        if (element != NULL)
        {
            element = element->next; // skip the value
        }
    }

    json_free(json);
    x_free(codepoints);
    return (char*)buffer;
}

#ifdef MODULE_TEST
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <libgen.h>

int test_read_basis_set_file(char* program_path)
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
    char* parentDir = dirname(buffer);
    if (realpath(parentDir, parent_dir_buffer) == NULL)
    {
        perror("Error finding parent directory path");
        return 1;
    }

    sprintf(json_file, "%s/../../../basis-set/sto-3g.json", parent_dir_buffer);

    if (realpath(json_file, json_file_abspath) == NULL)
    {
        perror("Error finding absolute file path for basis set directory");
        return 1;
    }

    printf("reading json_file: %s\n", json_file_abspath);

    u64 selected_elements[] = {1, 3};
    char* basis_set_buffer = load_basis_set_from_file(json_file_abspath, 2, selected_elements);
    x_free(basis_set_buffer);

    printf("\n");
    return 0;
}

int main(int argc, char* argv[])
{
    test_read_basis_set_file(argv[0]);

    print_mm_status();
    return 0;
}
#endif
