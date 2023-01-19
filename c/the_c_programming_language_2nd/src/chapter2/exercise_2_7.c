// Write a function `invert(x, p, n)` that returns `x` with the `n` bits that
// begin at position `p` inverted (i.e., `1` has changed into `0` and vice
// versa), leaving the others unchanged.

#include <stdio.h>

unsigned invert(unsigned x, int p, int n);

int main()
{
    unsigned x = 215; // 11010111
    unsigned r = invert(x, 5, 4); // 11101011

    printf("%u\n", (unsigned)r);
    return 0;
}

unsigned invert(unsigned x, int p, int n)
{
    unsigned base = ~(~0 << n);
    int length = p + 1 - n;
    return x ^ (base << length);
}
