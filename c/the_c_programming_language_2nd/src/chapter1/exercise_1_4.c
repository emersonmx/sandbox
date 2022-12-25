// Write a program to print the corresponding Celsius to Fahrenheit table.

#include <stdio.h>

// print Fahrenheit-Celsius table
// for fahr = 0, 20, ..., 300; floating-point version
int main()
{
    float fahr, celsius;
    int lower, upper, step;

    lower = -20; // lower limit of temperature table
    upper = 150; // upper limit
    step = 10; // step size

    celsius = lower;
    printf("Celsius    Fahrenheit\n");
    while (celsius <= upper) {
        fahr = celsius * (9.0 / 5.0) + 32.0;
        printf("%7.0f %13.1f\n", celsius, fahr);
        celsius = celsius + step;
    }

    return 0;
}
