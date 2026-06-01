// Rewrite the function `lower`, which converts upper case letters to lower
// case, with a conditional expression instead of `if-else`.

#include <stdio.h>

int lower(int c);

int main()
{
    printf("%c\n", lower('A'));
    printf("%c\n", lower('Z'));
    printf("%c\n", lower('C'));
    printf("%c\n", lower('R'));
    printf("%c\n", lower('a'));
    printf("%c\n", lower('z'));
    printf("%c\n", lower('c'));
    printf("%c\n", lower('r'));
    return 0;
}

int lower(int c)
{
    return ('A' <= c && c <= 'Z') ? c + 'a' - 'A' : c;
}
