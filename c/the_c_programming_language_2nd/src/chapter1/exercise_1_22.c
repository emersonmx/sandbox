// Write a program to "fold" long input lines into two or more shorter lines
// after the last non-blank character that occurs before the `n`-th column of
// input. Make sure your program does something intelligent with very long
// lines, and if there are no blanks or tabs before the speciefied column.

#include <stdbool.h>
#include <stdio.h>

#define LINE_SIZE 80

bool m_isblank(char c);

int main()
{
    int c, cc, sc;

    cc = 0;
    sc = 0;
    while ((c = getchar()) != EOF) {
        if (m_isblank(c)) {
            ++sc;
            if (cc == LINE_SIZE - 1) {
                putchar('\n');
                cc = 0;
                sc = 0;
            } else if (cc > 0 && sc == 1) {
                putchar(c);
                ++cc;
            }
        } else {
            sc = 0;
            if (cc == LINE_SIZE) {
                putchar('\n');
                putchar(c);
                cc = 1;
            } else {
                putchar(c);
                ++cc;
            }
        }
    }
    return 0;
}

bool m_isblank(char c)
{
    return c == ' ' || c == '\t';
}
