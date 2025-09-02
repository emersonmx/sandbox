// Write a function `setbits(x, p, n, y)` that returns `x` with the `n` bits
// that begin at position `p` set to the rightmost `n` bits of `y`, leaving the
// other bits unchanged.

#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);

int main()
{
    unsigned x = 255; // 11111111
    unsigned y = 24; // 00011000
    unsigned r = setbits(x, 5, 4, y); // 11011011

    printf("%u\n", (unsigned) r);
    return 0;
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    unsigned base = ~(~0 << n);
    int length = p + 1 - n;

    return (x & ~(base << length)) | (y & base << length);
}
