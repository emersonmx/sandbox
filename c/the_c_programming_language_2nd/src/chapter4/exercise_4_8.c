// Suppose that there will never be more than one character of pushback. Modify
// `getch` and `ungetch` accordingly.

#include <stdio.h>

char buf = 0;

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

/* getch: get a (possibly) pushed back character */
int getch(void)
{
    int c;

    if (buf == 0)
        c = getchar();
    else
        c = buf;

    buf = 0;
    return c;
}

/* ungetch: push a character back into input */
void ungetch(int c)
{
    if (buf == 0)
        buf = c;
    else
        printf("ungetch: too many characters\n");
}
