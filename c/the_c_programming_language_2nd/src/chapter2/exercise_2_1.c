// Write a program to determine the ranges of `char`, `short`, `int` and `long`
// variables, both `signed` and `unsigned`, by printing appropriate values from
// standard headers and by direct computation. Harder if you compute them:
// determine the ranges of the various floating-point types.

#include <float.h>
#include <limits.h>
#include <stdio.h>

int main()
{
    printf("char: [%+d,%+d]\n", CHAR_MIN, CHAR_MAX);
    printf("signed char: [%+d,%+d]\n", SCHAR_MIN, SCHAR_MAX);
    printf("unsigned char: [%u,%u]\n", 0, UCHAR_MAX);

    printf("short: [%+d,%+d]\n", SHRT_MIN, SHRT_MAX);
    printf("signed short: [%+d,%+d]\n", SHRT_MIN, SHRT_MAX);
    printf("unsigned short: [%u,%u]\n", 0, USHRT_MAX);

    printf("int: [%+d,%+d]\n", INT_MIN, INT_MAX);
    printf("signed int: [%+d,%+d]\n", INT_MIN, INT_MAX);
    printf("unsigned int: [%u,%u]\n", 0, UINT_MAX);

    printf("long: [%+ld,%+ld]\n", LONG_MIN, LONG_MAX);
    printf("signed long: [%+ld,%+ld]\n", LONG_MIN, LONG_MAX);
    printf("unsigned long: [%lu,%lu]\n", 0UL, ULONG_MAX);

    return 0;
}
