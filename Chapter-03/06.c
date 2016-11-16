/*
 * Write a version of itoa that accepts three arguments instead of two.
 * The third argument is a minimum field width; the converted number
 * must be padded with blanks on the left if necessary to make it wide
 * enough.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void itoa(int, char *, int);
void reverse(char *);

int main(void)
{
    char s[15];
    itoa(100, s, 10);
    printf("%s\n", s);
    itoa(10000, s, 10);
    printf("%s\n", s);

    return EXIT_SUCCESS;
}

/* itoa:  comvert n to characters in base b in s */
void itoa(int n, char s[], int w)
{
    int i, sign;
        
    sign = n;
    i = 0;
    do {            /* generate symbols in reverse order */
        s[i++] = abs(n % 10) + '0';   /* get next symbols */
    } while (n /= 10);                   /* delete it */
    if (sign < 0)
        s[i++] = '-';
    while (i < w)
    	s[i++] = ' ';
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
