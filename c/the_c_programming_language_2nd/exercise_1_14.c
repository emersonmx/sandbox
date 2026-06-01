#include <stdio.h>

#define SIZE 92

int main()
{
    int c, histogram[SIZE];

    for (int i = 0; i < SIZE; ++i)
        histogram[i] = 0;

    while ((c = getchar()) != EOF)
        if (c >= '!' && c <= '}') {
            histogram[c - '!'] += 1;
        }

    printf("HISTOGRAM OF THE FREQUENCIES OF DIFFERENT CHARACTERS\n");
    for (int i = 0; i < SIZE; ++i) {
        printf("%2c: ", (i + 1) + '!');
        for (int j = 0; j < histogram[i]; ++j)
            putchar('#');

        putchar('\n');
    }

    return 0;
}
