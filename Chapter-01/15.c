/*
 * Rewrite the temperature conversion program of Section 1.2 to use a
 * function for conversion.
 */

#include <stdio.h>
#include <stdlib.h>

float ftoc(float);

int main(void) 
{
	int fahr;

	printf("=========\n");  
    printf("  F     C\n");
    printf("=========\n");

    for (fahr = 0; fahr <= 300; fahr += 20)
    	printf("%3d %5.1f\n", fahr, ftoc(fahr));

    return EXIT_SUCCESS;
}

float ftoc(float f)
{
    float c = (5.0/9.0) * (f-32.0);
    return c;
}