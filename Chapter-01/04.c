/*
 * Write a program to print the corresponding Celsius to Fahrenheit
 * table.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;      /* lower limit of temperature table */
    upper = 300;    /* upper limit */
    step = 20;      /* step size */

    printf("=======\n");  
    printf("  C   F\n");
    printf("=======\n");

    celsius = lower;
    while (celsius <= upper) {
        fahr = celsius * (9.0/5.0) + 32.0;
        printf("%3.0f %3.0f\n", celsius, fahr);
        celsius = celsius + step;
    }
    return EXIT_SUCCESS;
}
