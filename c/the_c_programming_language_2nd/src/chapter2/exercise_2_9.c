// In a two's complement number system, `x &= (x - 1)` deletes the rightmost
// 1-bit in `x`. Explain why. Use this observation to write a faster version of
// `bitcount`.
//
// Answer: This is due to two reasons:
// - the AND operator returns `1` only when all values are true and `0`
//   otherwise.
// - and when doing `x - 1`, the bits from the rightmost `1` to the least
//   significant bit will be inverted.
// Example:
//   11110000 & (11110000 - 1)
//   11110000 & 11101111
//   11100000
//
// Thus, using the `x &= (x - 1)` operation in the `bitcount` function results
// in a simpler and faster version, but makes it harder to understand the
// function. Therefore, I prefer the previous version because it is more
// explicit what is done :)

#include <stdio.h>

int bitcount(unsigned x);

int main()
{
    int x = 179; // 10110011
    printf("%d `1` bits in %d\n", bitcount(x), x);
    return 0;
}

// bitcout: count 1 bits in x
int bitcount(unsigned x)
{
    int b;

    for (b = 0; x != 0; x &= (x - 1))
        ++b;

    return b;
}
