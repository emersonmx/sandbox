// Rewrite the routines `day_of_year` and `month_day` with pointers instead of
// indexing.

#include <stdio.h>

static char daytab[][13] = {
    { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
    { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
};

// day_of_year: set day of year from month & day
int day_of_year(int year, int month, int day)
{
    int i, leap;
    char *p;

    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

    if (month < 1 || month > 12)
        return -1;
    if (day < 1 || day > daytab[leap][month])
        return -1;

    p = &daytab[leap][1];
    for (i = 1; i < month; i++) {
        day += *p;
        p++;
    }

    return day;
}

// month_day: set month, day from day of year
void month_day(int year, int yearday, int *month, int *day)
{
    int i, leap;
    char *p;

    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

    if (year < 1 || yearday < 1 || yearday > (leap ? 366 : 365)) {
        *month = -1;
        *day = -1;
        return;
    }

    p = &daytab[leap][1];
    for (i = 1; yearday > daytab[leap][i]; i++) {
        yearday -= *p;
        p++;
    }

    *month = i;
    *day = yearday;
}

int main()
{
    int month, day;

    printf("day_of_year: %d\n", day_of_year(2023, 2, 31));

    printf("day_of_year: %d\n", day_of_year(2023, 3, 5));
    printf("day_of_year: %d\n", day_of_year(2024, 3, 5));

    month_day(2023, 366, &month, &day);
    printf("month_day: %d %d\n", month, day);
    month_day(2023, 64, &month, &day);
    printf("month_day: %d %d\n", month, day);
    month_day(2024, 65, &month, &day);
    printf("month_day: %d %d\n", month, day);

    return 0;
}
