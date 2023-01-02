// Write the function `htoi(s)`, which converts a string of hexadecimal digits
// (including an optional `0x` or `0X`) into its equivlent integer value. The
// allowable digits are `0` through `9`, `a` through `f`, and `A` through `F`.

#include <ctype.h>
#include <stdio.h>

int htoi(char s[]);

int main()
{
    int n;

    n = htoi("0x55");
    printf("%d\n", n);

    n = htoi("0xff");
    printf("%d\n", n);

    n = htoi("0xFF");
    printf("%d\n", n);

    n = htoi("55");
    printf("%d\n", n);

    n = htoi("ff");
    printf("%d\n", n);

    n = htoi("FF");
    printf("%d\n", n);

    return 0;
}

int htoi(char s[])
{
    int c, i, n;

    i = n = 0;
    if (s[i] == '0' && tolower(s[i + 1]) == 'x')
        i = 2;

    for (; (c = tolower(s[i])) != '\0'; ++i) {
        if (isdigit(c)) {
            n = 16 * n + (c - '0');
        } else if ('a' <= c && c <= 'f') {
            n = 16 * n + (c - 'a' + 10);
        } else {
            break;
        }
    }

    return n;
}
