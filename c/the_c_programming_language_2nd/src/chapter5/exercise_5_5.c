// Write versions of the library functions `strncpy`, `strncat`, and `strncmp`,
// which operate on at most the first `n` characters of their argument strings.
// For example, `strncpy(s, t, n)` copies at most `n` characters of `t` to `s`.
// Full descriptions are in Appendix B.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mstrncpy(char *s, char *t, int n);
void mstrncat(char *s, char *t, int n);
int mstrncmp(char *s, char *t, int n);

void test_cpy(void);
void test_cat(void);
void test_cmp(void);

int main()
{
    test_cpy();
    test_cat();
    test_cmp();

    return 0;
}

void test_cpy(void)
{
    char s[] = "Hello";
    char t[] = " World";

    mstrncpy(s, t, 3);
    printf("strncpy: %s\n", s);
}

void test_cat(void)
{
    char s[12] = "Hello";
    char t[] = " World";

    mstrncat(s, t, 3);
    printf("strncat: %s\n", s);
}

void test_cmp(void)
{
    int r;
    char s[] = "Hello";
    char t[] = "World";

    r = mstrncmp(s, t, 3);
    printf("strncmp(\"%s\", \"%s\") -> %d\n", s, t, r);
}

void mstrncpy(char *s, char *t, int n)
{
    while (n-- > 0)
        *s++ = *t++;
}

void mstrncat(char *s, char *t, int n)
{
    while (*s++)
        ;
    s--;
    while (n-- > 0)
        *s++ = *t++;
}

int mstrncmp(char *s, char *t, int n)
{
    while (*s == *t) {
        if (*s == '\0' || --n <= 0)
            return 0;
        s++;
        t++;
    }

    return *s - *t;
}
