// Write a program `entab` that replaces strings of blanks by the minimum number
// of tabs and blanks to achieve the same spacing. Use the same tab stops as for
// `detab`. When either a tab or a single blank would suffice to reach a tab
// stop, which should be given preference?

#include <stdio.h>

#define SPACES 4

int main()
{
    int i, c, cc;
    cc = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            ++cc;
        } else if (cc < SPACES) {
            for (i = 0; i < cc; ++i) {
                putchar(' ');
                cc = 0;
            }
            putchar(c);
        }

        if (cc == SPACES) {
            putchar('\t');
            cc = 0;
        }
    }
    return 0;
}
