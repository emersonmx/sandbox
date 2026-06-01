// Rewrite the temperature conversion program of Section 1.2 to use a function
// for conversion.

#include <stdio.h>

float fahrenheit_to_celsius(float value);

int main()
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;
    while (fahr <= upper) {
        celsius = fahrenheit_to_celsius(fahr);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
    return 0;
}

float fahrenheit_to_celsius(float value)
{
    return (5.0 / 9.0) * (value - 32.0);
}
