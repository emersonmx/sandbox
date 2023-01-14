#include <stdio.h>

#define V_SIZE 100000

int binsearch(int x, int v[], int n);

int main()
{
    int v[V_SIZE], num, index;

    for (int i = 0; i < V_SIZE; ++i)
        v[i] = i;

    num = 12387;
    index = binsearch(num, v, V_SIZE);

    printf("binsearch() found %d at the %d position\n", num, index);

    return 0;
}

// binsearch: find x in v[0] <= v[1] <= ... <= v[n-1]
int binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}
