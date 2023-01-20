// Our `getch` and `ungetch` do not handle a pushed-back EOF correctly. Decide
// what their properties ought to be if an `EOF` is pushed back, then implement
// you design.

#include <stdio.h>

#define BUFSIZE 100

char buf[BUFSIZE]; // buffer for ungetch
int bufp = 0; // next free position in buf

int getch(void);
void ungetch(int c);

int main(void)
{
    int c;

    c = '*';

    ungetch(c);

    while ((c = getch()) != EOF)
        putchar(c);

    return 0;
}

int getch(void) // get a (possibly pushed back) character
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) // push character back on input
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
