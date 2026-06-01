#include <stdio.h>
#include <string.h>

int main()
{
    char d[] = " \t\n";
    char s[] = "\t  1 -2 3 4\n";
    char *t = strtok(s, d);

    while (t) {
        printf("%s\n", t);
        t = strtok(NULL, d);
    }

    printf("%s\n", t);
    return 0;
}
