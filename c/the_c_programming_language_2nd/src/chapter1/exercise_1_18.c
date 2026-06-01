#include <stdbool.h>
#include <stdio.h>

#define MAXLINE 1000

int getline(char line[], int maxline);
int trimline(char line[], int maxline);
bool myisblank(char c);

int main()
{
    int len;
    char line[MAXLINE];

    while ((len = getline(line, MAXLINE)) > 0)
        if ((len = trimline(line, len)) > 0)
            printf("%.*s\n", len, line);

    return 0;
}

int getline(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';
    return i;
}

int trimline(char line[], int maxline)
{
    int i;
    for (i = maxline - 1; i >= 0 && myisblank(line[i]); --i)
        ;
    ++i;
    line[i] = '\n';
    return i;
}

bool myisblank(char c)
{
    return c == '\n' || c == ' ' || c == '\t';
}
