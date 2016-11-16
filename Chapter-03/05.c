/*
 * Write the function itob(n,s,b) that converts the integer n into a
 * base b character representation in the string s. In particular,
 * itob(n,s,16) formats n as a hexadecimal integer in s.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void itob(int, char *, int);
void reverse(char *);

int main(void) 
{
	char s[15];
	itob(100,s,2);
	printf("%s\n", s);
	itob(100,s,10);
	printf("%s\n", s);
	itob(15,s,16);
	printf("%s\n", s);

	return EXIT_SUCCESS;
}

/* itob:  convert n to characters in s */
void itob(int n, char s[], int b)
{
    int i, sign;
    char base[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    if (b < 2 || b > strlen(base))
        return;     /* not a valid base */

    sign = n;
    i = 0;
    do {            /* generate symbols in reverse order */
        s[i++] = base[abs(n % b)];   /* get next symbols */
    } while (n /= b);                /* delete it */
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