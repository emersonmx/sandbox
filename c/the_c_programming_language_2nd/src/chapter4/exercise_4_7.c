// Write a routine `ungets(s)` that will push back an entire string onto the
// input. Should `ungets` know about `buf` and `bufp`, or should it just use
// `ungetch`?

#include <stdio.h>
#include <string.h>

#define MAXBUF  100
#define MAXLINE 100

int bufp = 0;
int buf[MAXBUF];

int getch(void);
void ungetch(int c);
void ungets(char s[]);
void getline(char line[], int maxline);

int main(void)
{
    char line[MAXLINE];
    int c;

    getline(line, MAXLINE);

    ungets(line);

    while ((c = getch()) != EOF)
        putchar(c);

    return 0;
}

void getline(char line[], int maxline)
{
    int i, c;

    for (i = 0; i < maxline - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        line[i] = c;

    if (c == '\n')
        line[i++] = c;

    line[i] = '\0';
}

void ungets(char s[])
{
    for (int i = strlen(s) - 1; i >= 0; --i)
        ungetch(s[i]);
}

void ungetch(int c)
{
    if (bufp >= MAXBUF)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}
