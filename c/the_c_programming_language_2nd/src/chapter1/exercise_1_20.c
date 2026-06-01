// Write a program `detab` that replaces tabs in the input with the proper
// number of blanks to space to the next tab stop. Assume a fixed set of tab
// stops, say every `n` columns. Should `n` be a variable or a symbolic
// parameter?

#include <stdio.h>

#define SPACES 4

int main()
{
    int c;
    while ((c = getchar()) != EOF)
        if (c == '\t')
            for (int i = 0; i < SPACES; ++i)
                putchar(' ');
        else
            putchar(c);
    return 0;
}
