// Write a function `rightrot(x, n)` that returns the value of the integer `x`
// rotated to the right by `n` bit positions.

#include <stdio.h>

unsigned rightrot(unsigned x, int n);
int length(void);

int main()
{
    unsigned x = 206; // 11001110
    unsigned r = rightrot(x, 2); // 10110011

    printf("%u\n", (unsigned)r);
    return 0;
}

unsigned rightrot(unsigned x, int n)
{
    unsigned rb = x << (length() - n);
    return (x >> n) | rb;
}

int length(void)
{
    int i;
    unsigned l = (unsigned)~0;

    for (i = 1; (l = l >> 1) > 0; ++i)
        ;
    return i;
}
