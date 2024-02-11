/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <float.h>
#include <stdio.h>
#include <math.h>
#include "numeric_types.h"

void numeric_type_print_sizes()
{
    printf("sizeof(void*): %lu\n", sizeof(void*));
    printf("\n");

#ifdef __cplusplus
    printf("sizeof(bool): %lu\n", sizeof(bool));
#else
    printf("sizeof(_Bool): %lu\n", sizeof(_Bool));
#endif

    printf("sizeof(char): %lu\n", sizeof(char));
    printf("sizeof(signed char): %lu\n", sizeof(signed char));
    printf("sizeof(unsigned char): %lu\n", sizeof(unsigned char));
    printf("\n");

    printf("sizeof(short): %lu\n", sizeof(short));
    printf("sizeof(unsigned short): %lu\n", sizeof(unsigned short));
    printf("sizeof(int): %lu\n", sizeof(int));
    printf("sizeof(unsigned int): %lu\n", sizeof(unsigned int));
    printf("sizeof(long): %lu\n", sizeof(long));
    printf("sizeof(unsigned long): %lu\n", sizeof(unsigned long));
    printf("sizeof(long long): %lu\n", sizeof(long long));
    printf("sizeof(unsigned long long): %lu\n", sizeof(unsigned long long));
    printf("\n");

    printf("sizeof(float): %lu\n", sizeof(float));
    printf("sizeof(double): %lu\n", sizeof(double));
    printf("sizeof(long double): %lu\n", sizeof(long double));
    printf("\n");

    printf("sizeof(float _Complex): %lu\n", sizeof(float _Complex));
    printf("sizeof(double _Complex): %lu\n", sizeof(double _Complex));
    printf("sizeof(long double _Complex): %lu\n", sizeof(long double _Complex));
    printf("\n");

    printf("sizeof integer char constant ('a'): %lu\n", sizeof('a'));
    printf("sizeof char in string (\"a\"): %lu\n", sizeof("a"[0]));
    printf("sizeof 1ul: %lu\n", sizeof(1ul));
    printf("sizeof 1ull: %lu\n", sizeof(1ull));
    printf("\n");

    printf("max u64: %lu\n", U64_MAX);
    printf("\n");
}

void print_machine_epsilon()
{
    printf("FLT_EPSILON: %.16e\n", FLT_EPSILON);
    printf("DBL_EPSILON: %.16e\n", DBL_EPSILON);
    printf("LDBL_EPSILON: %.16Le\n", LDBL_EPSILON);
    printf("\n");
}

static f64 const F64_RELATIVE_TOLERANCE = 1e-14;
static f64 const F64_ABSOLUTE_TOLERANCE = 1e-14;

u64 f64_is_close(f64 a, f64 b)
{
    return fabs(a - b) <= fmax(F64_RELATIVE_TOLERANCE* fmax(fabs(a), fabs(b)), F64_ABSOLUTE_TOLERANCE);
}

u64 f64_is_zero(f64 a)
{
    return fabs(a) == 0.0;
}

#ifdef MODULE_TEST
#include <stdio.h>
int main(void)
{
    numeric_type_print_sizes();
    print_machine_epsilon();
    return 0;
}
#endif
