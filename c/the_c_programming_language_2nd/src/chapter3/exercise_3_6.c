// Write a version of `itoa` that accepts three arguments instead of two. The
// third argument is a minimum field width; the converted number must be padded
// with blanks on the left if necessary to make it wide enough.

#include <stdio.h>
#include <string.h>

#define MAXSIZE 1000

void reverse(char s[]);
void itoa(int n, char s[], int w);

int main()
{
    int  n;
    char s[MAXSIZE];

    n = -46973;

    itoa(n, s, 10);

    printf("%s\n", s);

    return 0;
}

void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s) - 1; i < j; ++i, --j)
        c = s[i], s[i] = s[j], s[j] = c;
}

void itoa(int n, char s[], int w)
{
    int i, sign;

    i = 0;
    if ((sign = n) < 0)
        n = -n;

    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0)
        s[i++] = '-';

    while (i < w)
        s[i++] = ' ';
    s[i] = '\0';

    reverse(s);
}
