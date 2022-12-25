#include <stdio.h>

int main()
{
    int c, s;
    s = 0;
    while ((c = getchar()) != EOF) {
        if (c != ' ') {
            putchar(c);
            s = 0;
        }
        if (c == ' ') {
            if (s == 0) {
                putchar(c);
            }
            ++s;
        }
    }
    return 0;
}
