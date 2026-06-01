// Write a function `reverse(s)` that reverses the character string `s`. Use it
// to write a program that reverses its input a line at a time.

#include <stdbool.h>
#include <stdio.h>

#define MAXLINE 1000

int  getline(char line[], int maxline);
void reverse(char line[], int maxline);

int main()
{
    int  len;
    char line[MAXLINE];

    while ((len = getline(line, MAXLINE)) > 0) {
        line[--len] = '\0'; // remove newline
        reverse(line, len);
        printf("%.*s\n", len, line);
    }

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

void reverse(char line[], int maxline)
{
    char aux;

    for (int i = 0; i < maxline / 2; ++i) {
        aux = line[i];
        line[i] = line[maxline - i - 1];
        line[maxline - i - 1] = aux;
    }
}
