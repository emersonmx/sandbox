#include <stdio.h>

int main()
{
    int c, s;

    s = 0;
    while ((c = getchar()) != EOF) {
        // I know... but the book still didn't show the "||" :b
        if (c == ' ') {
            ++s;
        }
        if (c == '\t') {
            ++s;
        }
        if (c == '\n') {
            ++s;
        }
    }

    printf("%d\n", s);
    return 0;
}
