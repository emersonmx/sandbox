// Write a recursive version of the function `reverse(s)`, which reverses the
// string `s` in place.

#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

void getline(char line[], int limit);
void reverse(char s[]);

int main()
{
    char s[MAXLINE];

    getline(s, MAXLINE);
    reverse(s);
    printf("%s\n", s);

    return 0;
}

void getline(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    if (c == '\n')
        s[i++] = c;

    s[i] = '\0';
}

void reverse(char s[])
{
    static int i = 0;
    static int len;

    int j;
    char c;

    if (i == 0)
        len = strlen(s);

    j = len - (i + 1);

    if (i < j) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
        i++;
        reverse(s);

    } else {
        i = 0;
    }
}
