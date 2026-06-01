// Write a program to remove all comments from a C program. Don't forget to
// handle quoted strings and character constants properly. C comments do not
// nest.

#include <stdio.h>

#define NOP        0
#define SL_COMMENT 1
#define ML_COMMENT 2
#define STRING     3

int state = NOP;

void sl_comment_state(int c);
void ml_comment_state(int c);
void string_state(int c);
void default_state(int c);

int main()
{
    extern int state;
    int        c;

    while ((c = getchar()) != EOF) {
        if (state == SL_COMMENT)
            sl_comment_state(c);
        else if (state == ML_COMMENT)
            ml_comment_state(c);
        else if (state == STRING)
            string_state(c);
        else
            default_state(c);
    }

    return 0;
}

void sl_comment_state(int c)
{
    extern int state;

    if (c == '\n') {
        putchar(c);
        state = NOP;
    }
}

void ml_comment_state(int c)
{
    extern int state;
    int        nc;

    if (c == '*') {
        nc = getchar();
        if (nc == EOF) {
            putchar(c);
        } else if (nc == '/') {
            state = NOP;
        }
    }
}

void string_state(int c)
{
    extern int state;
    int        nc;

    if (c == '\\') {
        nc = getchar();
        if (nc == EOF) {
            putchar(c);
        } else {
            putchar(c);
            putchar(nc);
        }
    } else if (c == '"') {
        putchar(c);
        state = NOP;
    } else {
        putchar(c);
    }
}

void default_state(int c)
{
    extern int state;
    int        nc;

    if (c == '/') {
        nc = getchar();
        if (nc == EOF) {
            putchar(c);
        } else if (nc == '/') {
            state = SL_COMMENT;
        } else if (nc == '*') {
            state = ML_COMMENT;
        } else {
            putchar(c);
            putchar(nc);
        }
    } else if (c == '"') {
        putchar(c);
        state = STRING;
    } else {
        putchar(c);
    }
}
