// Write the function `strend(s, t)`, which returns `1` if the string `t` occurs
// at the end of the string `s`, and zero otherwise.

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool strend(char *s, char *t);

int main()
{
    int r;
    char s[] = "Hello World";
    char t[] = "World";

    r = strend(s, t);

    if (r)
        printf("%s was found in %s\n", t, s);
    else
        printf("%s was not found in %s\n", t, s);

    return 0;
}

bool strend(char *s, char *t)
{
    int i = strlen(t);

    while (*s++)
        ;
    s--;
    while (*t++)
        ;
    t--;

    while (i > 0) {
        if (*t == *s) {
            t--;
            s--;
            i--;
        } else {
            return false;
        }
    }

    return i == 0;
}
