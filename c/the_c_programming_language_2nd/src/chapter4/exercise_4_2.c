// Extend `atof` to handle scientific notation of the form `123.45e-6` where a
// floating-point number may be followerd by `e` or `E` and an optionally signed
// exponent.

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

double matof(char s[]);

int main()
{
    printf("%.10f\n", matof("123.45e-6"));
    printf("%.10f\n", matof("123.45E-6"));
    printf("%.10f\n", matof("123.45e+6"));
    printf("%.10f\n", matof("123.45E+6"));
}

double matof(char s[])
{
    double val, power;
    int i, sign, sign_exp, exp;

    for (i = 0; isspace(s[i]); i++)
        ;

    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;

    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;

    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    if (s[i] == 'e' || s[i] == 'E') {
        i++;

        sign_exp = (s[i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-')
            i++;

        for (exp = 0; isdigit(s[i]); i++)
            exp = 10.0 * exp + (s[i] - '0');

        if (sign_exp == 1)
            for (i = exp; i > 0; --i, val *= 10.0)
                ;
        else
            for (i = exp; i > 0; --i, val /= 10.0)
                ;
    }

    return sign * val / power;
}
