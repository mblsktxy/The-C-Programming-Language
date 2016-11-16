/*
 * In a two's complement number representation, our version of itoa does
 * not handle the largest negative number, that is, the value of n equal
 * to -(2^(wordsize - 1)). Explain why not. Modify it to print that
 * value correctly regardless of the machine on which it runs.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

void itoa(int, char *);
void reverse(char *);

int main(void) 
{
	int n = INT_MIN;
	char s[15];
	itoa(n,s);

	printf("%s\n", s);

	return EXIT_SUCCESS;
}

/* itoa:  convert n to characters in s */
void itoa(int n, char s[])
{
    int i, sign;

    sign = n;
    i = 0;
    do {        /* generate digits in reverse order */
        s[i++] = abs(n % 10) + '0';     /* get next digit */
    } while (n /= 10);                  /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

/* reverse:  reverse string s in place */
void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}