#include <stdio.h>

#define IN         1
#define OUT        2
#define SIZE       10
#define LONG_WORDS 0

int main()
{
    int c, wl, state;
    int histogram[SIZE];

    state = OUT;
    wl = 0;

    for (int i = 0; i < SIZE; ++i)
        histogram[i] = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (wl > 0) {
                if (wl < SIZE)
                    histogram[wl] += 1;
                else
                    histogram[LONG_WORDS] += 1;
            }

            wl = 0;
            state = OUT;
        } else if (state == OUT) {
            state = IN;
        }

        if (state == IN)
            ++wl;
    }

    printf("HISTOGRAM OF THE LENGTHS OF WORDS\n");
    for (int i = 1; i < SIZE; ++i) {
        printf("%5d: ", i);
        for (int j = 0; j < histogram[i]; ++j)
            putchar('#');

        putchar('\n');
    }

    printf("%4d+: ", SIZE);
    for (int i = 0; i < histogram[LONG_WORDS]; ++i)
        putchar('#');

    putchar('\n');

    return 0;
}
