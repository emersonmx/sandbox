// Write a pointer version of the function `strcat` that we showed in Chapter 2:
// `strcat(s, t)` copies the string `t` to the end of `s`.

#include <stdio.h>

void mstrcat(char *s, char *t);

int main()
{
    char s[12] = "Hello";
    char t[] = " World";

    mstrcat(s, t);

    printf("%s\n", s);

    return 0;
}

// mstrcat: concatenate t to end of s; s must be big enough
void mstrcat(char *s, char *t)
{
    while (*s++)
        ;
    s--;
    while ((*s++ = *t++))
        ;
}
