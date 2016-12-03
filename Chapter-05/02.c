/*
 * Write getfloat, the floating-point analog of getint. What type does
 * getfloat return as its function value?
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 10

int getch(void);
void ungetch(int);
int getfloat(float *);

int main(void) {
	int n, i;
	float array[SIZE];

	for (n = 0; n < SIZE && (i = getfloat(&array[n])) != EOF; n++) {
        if (i)
            printf("array[%d]: %f\n", n, array[n]);
        else
            printf("error: not a number\n");
	}

	return EXIT_SUCCESS;
}

/* getfloat:  get next float number from input into *pn
 * treat '+', '-', and '.' as 0
 * treat 10. as 10
 * treat .1 as 0.1
 * 
 * ------
 * Logic:
 * if c is ' ':
 *     do nothing, nelnect
 * if c is number:
 *     get_the_whole_number
 *     return 0
 * if c is '-' or '+':
 *     if next is number:
 *         get_the_whole_number
 *         return 0
 *     else
 *         return c
 * if c is '.':
 *     if next is number:
 *         get_the_whole_number_without_judging_'.'_again
 *         return 0
 *     else
 *         return c
 * if c is other thing:
 *     return c
 */
int getfloat(float *pn)
{
    int c, sign, noDigitsAfterDot;

    while (isspace(c = getch()))  /* skip white space */
        ;

    if (isdigit(c)) {
        for (*pn = 0; isdigit(c); c = getch())
            *pn = 10 * *pn + (c - '0');
        if (c == '.') {
            if (isdigit(c = getch())) {
                for (noDigitsAfterDot = 0; isdigit(c); c = getch(), noDigitsAfterDot++)
                    *pn = 10 * *pn + (c - '0');
                while (noDigitsAfterDot != 0) {
                    *pn /= 10.;
                    noDigitsAfterDot--;
                }
                ungetch(c);
                return c;
            } else {
                ungetch(c);
                return c;
            }
        } else {
            ungetch(c);
            return c;
        }
    } else if (c == '-' || c == '+') {
        sign = (c == '+') ? 1 : -1;
        if (isdigit(c = getch())) {
            for (*pn = 0; isdigit(c); c = getch()) 
                *pn = 10 * *pn + (c - '0');
            if (c == '.') {
                if (isdigit(c = getch())) {
                    for (noDigitsAfterDot = 0; isdigit(c); c = getch(), noDigitsAfterDot++)
                        *pn = 10 * *pn + (c - '0');
                    while (noDigitsAfterDot != 0) {
                        *pn /= 10.;
                        noDigitsAfterDot--;
                    }
                    ungetch(c);
                    *pn *= sign;
                    return c;
                } else {
                    ungetch(c);
                    *pn *= sign;
                    return c;
                }
            } else {
                ungetch(c);
                *pn *= sign;
                return c;
            }
        } else {
            *pn = 0.;
            ungetch(c);
            return c;
        }
    } else if (c == '.') {
        if (isdigit(c = getch())) {
            for (noDigitsAfterDot = 0, *pn = 0; isdigit(c); c = getch(), noDigitsAfterDot++)
                *pn = 10 * *pn + (c - '0');
            while (noDigitsAfterDot != 0) {
                *pn /= 10.;
                noDigitsAfterDot--;
            }
            ungetch(c);
            return c;
        } else {
            *pn = 0.;
            ungetch(c);
            return c;
        }
    } else {
        ungetch(c);
        return 0;
    }
}

#define BUFSIZE 100

char buf[BUFSIZE];    /* buffer for ungetch */
int bufp = 0;         /* next free position in guf */

int getch(void) {     /* get a (possibly pushed back) character */
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) { /* push character back on input */
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else 
        buf[bufp++] = c;
}