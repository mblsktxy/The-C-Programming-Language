/*
 * As written, getint treats a + or - not followed by a digit as a valid
 * representation of zero. Fix it to push such a character back on the
 * input.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 10

int getch(void);
void ungetch(int);
int getint(int *);

int main(void) {
	int n, i;
	int array[SIZE];

	for (n = 0; n < SIZE && (i = getint(&array[n])) != EOF; n++) {
        if (i)
            printf("array[%d]: %d\n", n, array[n]);
        else
            printf("error: not a number\n");
	}

	return EXIT_SUCCESS;
}

/* getint:  get next integer from input into *pn */
int getint(int *pn)
{
    int c, sign;

    while (isspace(c = getch()))  /* skip white space */
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);  /* it's not a number */
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
        if (!isdigit(c)) { /* + or - not followed by a digit */
            ungetch(c);                      /* ungetch non-digit */
            ungetch(sign == 1 ? '+' : '-');  /* ungetch + or - */
            return 0;
        }
    }
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
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