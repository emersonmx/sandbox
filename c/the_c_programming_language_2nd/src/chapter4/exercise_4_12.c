// Adapt the ideas of `printd` to write a recursive version of `itoa`; that is,
// convert an integer into a string by calling a recursive routine.

#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 100

void itoa(int n, char s[]);

int main()
{
    int n = 8723;
    char s[MAXLEN];

    itoa(n, s);
    printf("%s\n", s);

    return 0;
}

void itoa(int n, char s[])
{
    static int i;

    if (n / 10) {
        itoa(n / 10, s);
    } else {
        i = 0;
        if (n < 0)
            s[i++] = '-';
    }

    s[i++] = abs(n) % 10 + '0';
    s[i] = '\0';
}
