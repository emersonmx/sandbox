// Write the function `any(s1, s2)`, which returns the first location in the
// string `s1` where any character from the string `s2` occurs, or `-1` if `s1`
// contains no characters from `s2`. (The standard library function `strpbrk`
// does the same job but returns a pointer to the locations.)

#include <stdio.h>

int any(char s1[], char s2[]);
int any_char(char s1[], int c);

int main()
{
    char t[] = "aaaabbbbbccccccdddddeeeeffffgg";
    char h[] = "Abc";

    printf("Any of %s was found at %s on position %d\n", h, t, any(t, h));
    return 0;
}

int any(char s1[], char s2[])
{
    int r;

    for (int i = 0; s2[i] != '\0'; ++i)
        if ((r = any_char(s1, s2[i])) >= 0)
            return r;
    return -1;
}

int any_char(char s[], int c)
{
    for (int i = 0; s[i] != '\0'; ++i)
        if (s[i] == c)
            return i;

    return -1;
}
