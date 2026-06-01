#include <stdio.h>

void shellsort(int v[], int n);

int main()
{
    int v[] = {3, 2, 5, 4, 1, 6, 7, 8, 9, 0};
    int size = sizeof(v) / sizeof(v[0]);
    shellsort(v, size);

    for (int i = 0; i < size; ++i) {
        printf("%d\n", v[i]);
    }

    return 0;
}

// shellsort: sort v[0]...v[n-1] into increasing order
void shellsort(int v[], int n)
{
    int temp;

    for (int gap = n / 2; gap > 0; gap /= 2)
        for (int i = gap; i < n; ++i)
            for (int j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap) {
                temp = v[j];
                v[j] = v[j + gap];
                v[j + gap] = temp;
            }
}
