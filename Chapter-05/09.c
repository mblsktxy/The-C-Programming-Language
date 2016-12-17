/*
 * Rewrite the routines day_of_year and month_day with pointers
 * instead of indexing.
 */

#include <stdio.h>
#include <stdlib.h>

int day_of_year(int, int, int);
int month_day(int, int, int *, int *);

int main(void)
{
    int year, month, day, yearday;
    int valid, pmonth, pday;

    year = 2016;
    month = 12;
    day = 15;
    valid = day_of_year(year, month, day);
    if (valid)
        printf("%d-%d-%d: day %dth of the year.\n", year, month, day, valid);
    else
        printf("%d-%d-%d: invalid!\n", year, month, day);

    year = 2016;
    month = 12;
    day = 32;
    valid = day_of_year(year, month, day);
    if (valid)
        printf("%d-%d-%d: day %dth of the year.\n", year, month, day, valid);
    else
        printf("%d-%d-%d: invalid!\n", year, month, day);
        
    year = 2016;
    yearday = 60;
    valid = month_day(year, yearday, &pmonth, &pday);
    if (valid)
        printf("day %dth of year %d is %d-%d.\n", yearday, year, pmonth, pday);
    else
        printf("day %dth of year %d do not exsits!\n", yearday, year);

    year = 2016;
    yearday = 367;
    valid = month_day(year, yearday, &pmonth, &pday);
    if (valid)
        printf("day %dth of year %d is %d-%d.\n", yearday, year, pmonth, pday);
    else
        printf("day %dth of year %d do not exsits!\n", yearday, year);

    return EXIT_SUCCESS;
}

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day) {
	int i, leap;

	if (month < 1 || month > 12 || day < 1)
		return 0;

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	if (day > *(*(daytab+leap)+month))
		return 0;
	for (i = 1; i < month; i++)
		day += *(*(daytab+leap)+i);
	return day;
}

/* month_day: set month, day from day of year */
int month_day(int year, int yearday, int *pmonth, int *pday) {
	int i, leap;

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	if (yearday < 1 || yearday > (leap ? 366 : 365))
		return 0;
	for (i = 1; yearday> *(*(daytab+leap)+i); i++)
		yearday -= *(*(daytab+leap)+i);
	*pmonth = i;
	*pday = yearday;
	return 1;
}