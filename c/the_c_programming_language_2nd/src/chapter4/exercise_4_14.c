// Define a macro `swap(t,x,y)` that interchanges two arguments of type `t.
// (Block structure will help.)`

#include <stdio.h>

#define swap(t, x, y)                                                          \
    {                                                                          \
        t aux;                                                                 \
        aux = x;                                                               \
        x = y;                                                                 \
        y = aux;                                                               \
    }

void test_ints(void);
void test_doubles(void);

int main()
{
    test_ints();
    test_doubles();

    return 0;
}

void test_ints(void)
{
    int a = 42;
    int b = 34;

    printf("BEFORE\n");
    printf("a = %d\n", a);
    printf("b = %d\n", b);

    swap(int, a, b);

    printf("AFTER\n");
    printf("a = %d\n", a);
    printf("b = %d\n", b);
}

void test_doubles(void)
{
    double a = 42.12344;
    double b = 34.5234;

    printf("BEFORE\n");
    printf("a = %f\n", a);
    printf("b = %f\n", b);

    swap(double, a, b);

    printf("AFTER\n");
    printf("a = %f\n", a);
    printf("b = %f\n", b);
}
