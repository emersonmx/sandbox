// Write an alternate version of `squeeze(s1, s2)` that deletes each character
// in `s1` that matches any character in the *string* `s2`.

#include <stdio.h>

#define TEST_STRING "aabbbccddddefffggggggghhhhhhh"

void squeeze(char s1[], char s2[]);
void squeeze_char(char s[], int c);

int main()
{
    char old[] = TEST_STRING;
    char new[] = TEST_STRING;
    squeeze(new, "acfh");
    printf("%s -> %s\n", old, new);
    return 0;
}

void squeeze(char s1[], char s2[])
{
    for (int i = 0; s2[i] != '\0'; ++i)
        squeeze_char(s1, s2[i]);
}

void squeeze_char(char s[], int c)
{
    int i, j;

    for (i = j = 0; s[i] != '\0'; ++i)
        if (s[i] != c)
            s[j++] = s[i];
    s[j] = '\0';
}
