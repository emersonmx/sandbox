// Write the function `strrindex(s, t)`, which returns the position of the
// rightmost occurrence of `t` in `s`, or `-1` if there is none.

#include <stdio.h>

#define MAXSIZE 1000

int getline(char line[], int maxline);
int strrindex(char s[], char p[]);

int main()
{
    int found = 0;
    char line[MAXSIZE];
    char pattern[] = "ould";

    getline(line, MAXSIZE);

    found = strrindex(line, pattern);
    printf("Found the right index at %d of the line below.\n", found);
    printf("%s", line);

    for (int i = 0; i < found; ++i)
        printf("-");
    printf("^\n");

    return found;
}

int getline(char line[], int maxline)
{
    int c, i;

    i = 0;
    while (--maxline > 0 && (c = getchar()) != EOF && c != '\n')
        line[i++] = c;

    if (c == '\n')
        line[i++] = c;
    line[i] = '\0';
    return i;
}

int strrindex(char s[], char p[])
{
    int i, j, k;
    int result = -1;

    for (i = 0; s[i] != '\0'; ++i) {
        for (j = i, k = 0; p[k] != '\0' && s[j] == p[k]; ++j, ++k)
            ;
        if (k > 0 && p[k] == '\0')
            result = i;
    }
    return result;
}
