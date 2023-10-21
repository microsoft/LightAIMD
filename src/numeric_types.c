/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <float.h>
#include <stdio.h>
#include "numeric_types.h"

void print_numeric_type_sizes()
{
    printf("sizeof(void*): %lu\n", sizeof(void*));
    printf("\n");

    printf("sizeof(_Bool): %lu\n", sizeof(_Bool));

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
}

void print_machine_epsilon()
{
    printf("FLT_EPSILON: %.16e\n", FLT_EPSILON);
    printf("DBL_EPSILON: %.16e\n", DBL_EPSILON);
    printf("LDBL_EPSILON: %.16Le\n", LDBL_EPSILON);
}

#ifdef MODULE_TEST
#include <stdio.h>
int main(void)
{
    print_numeric_type_sizes();
    print_machine_epsilon();
    return 0;
}
#endif
