// ```c
// for (i=0; i<lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
//     s[i] = c;
// ```
//
// Write a loop equivalent to the `for` loop above withou using `&&` or `||`.
#include <stdio.h>

int main()
{
    int c;
    int lim = 20;
    char s[lim];

    for (int i = 0; i < lim - 1; ++i) {
        c = getchar();
        if (c == '\n')
            break;
        if (c == EOF)
            break;
        s[i] = c;
    }

    printf("%.*s\n", lim, s);

    return 0;
}
