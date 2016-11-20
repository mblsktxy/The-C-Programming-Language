/*
 * Write a routine ungets(s) that will push back an entire string onto
 * the input. Should ungets know about buf and bufp, or should it just
 * use ungetch?
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getch(void);
void ungetch(int);
void ungets(char []);

int main(void) {
	char s[] = "test string";

    ungets("test string");
    for (int i = 0; i < strlen(s); i++)
    	putchar(getch());
    putchar('\n');

    return EXIT_SUCCESS;
}

#define BUFSIZE 100

char buf[BUFSIZE];     /* buffer for ungetch */
int bufp = 0;          /* next free position in buf */

int getch(void) {      /* get a (possibly pushed-back) character */
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {  /* push character back on input */
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

void ungets(char s[]) {    
  	int l = strlen(s);

  	while (l)
    	ungetch(s[--l]);
}
