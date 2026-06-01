// Write a program to check a C program for rudimentary syntax errors like
// unbalanced parentheses, brackets and braces. Don't forget about quotes, both
// single and double, escape sequences, and comments. (This program is hard if
// you do it in full generality.)

#include <stdio.h>

int match_any(int r);
int match_brackets(int s, int e, int r);
int match_quotes(int r, char q);
int match_comments(int r);
int match_ends(int r, int c);

int main()
{
    int r;

    r = match_any(0);
    printf("\nValid? ");

    if (r != 0) {
        printf("no...\n");
        return 1;
    }

    printf("Yes!\n");
    return 0;
}

int match_any(int r)
{
    int c, nc;

    while ((c = getchar()) != EOF) {
        if (c == '(') {
            r = match_brackets(c, ')', ++r);
        } else if (c == '[') {
            r = match_brackets(c, ']', ++r);
        } else if (c == '{') {
            r = match_brackets(c, '}', ++r);
        } else if (c == '"') {
            r = match_quotes(++r, c);
        } else if (c == '\'') {
            r = match_quotes(++r, c);
        } else if (c == '/') {
            nc = getchar();
            if (nc == EOF)
                return 1;
            else if (nc == '*')
                r = match_comments(++r);
        } else {
            r = match_ends(r, c);
        }
    }

    return r;
}

int match_brackets(int s, int e, int r)
{
    int c, nc;

    putchar(s);
    while ((c = getchar()) != EOF) {
        if (c == e) {
            putchar(e);
            return --r;
        } else if (c == '(') {
            r = match_brackets(c, ')', ++r);
        } else if (c == '[') {
            r = match_brackets(c, ']', ++r);
        } else if (c == '{') {
            r = match_brackets(c, '}', ++r);
        } else if (c == '"') {
            r = match_quotes(++r, c);
        } else if (c == '\'') {
            r = match_quotes(++r, c);
        } else if (c == '/') {
            nc = getchar();
            if (nc == EOF)
                return 1;
            else if (nc == '*')
                r = match_comments(++r);
        } else {
            r = match_ends(r, c);
        }
    }

    return r;
}

int match_quotes(int r, char q)
{
    int c, nc;

    putchar(q);
    while ((c = getchar()) != EOF) {
        if (c == q) {
            putchar(q);
            return --r;
        } else if (c == '\\') {
            nc = getchar();
            if (nc == EOF)
                return r;
        }
    }

    return r;
}

int match_comments(int r)
{
    int c, nc;

    printf("/*");
    while ((c = getchar()) != EOF) {
        if (c == '*') {
            nc = getchar();
            if (nc == EOF) {
                return r;
            } else if (nc == '/') {
                printf("*/");
                return --r;
            }
        }
    }

    return r;
}

int match_ends(int r, int c)
{
    int nc;
    if (c == ')' || c == ']' || c == '}') {
        putchar(c);
        ++r;
    } else if (c == '*') {
        nc = getchar();
        if (nc == EOF) {
            return r;
        } else if (nc == '/') {
            printf("*/");
            return ++r;
        }
    }
    return r;
}
