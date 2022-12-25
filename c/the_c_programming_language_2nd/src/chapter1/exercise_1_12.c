// Write a program that prints its input one word per line.

#include <stdio.h>

#define IN  1 // inside a word
#define OUT 2 // outside a word

int main()
{
    int c, state;

    state = OUT;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (state == IN)
                putchar('\n');

            state = OUT;
        } else if (state == OUT) {
            state = IN;
        }

        if (state == IN)
            putchar(c);
    }
    return 0;
}
