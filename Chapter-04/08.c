/* 
 * Suppose that there will never be more than one character of pushback.
 * Modify getch and ungetch accordingly.
 */

#include <stdio.h>
#include <stdlib.h>

#define STACKEMPTY 0
#define STACKFULL 1

int getch(void);
void ungetch(int);

int main(void) {
    ungetch('a');
    ungetch('t');
    ungetch('9');
    putchar(getch());
    putchar(getch());
    putchar('\n');

    return EXIT_SUCCESS;
}

int state = STACKEMPTY;  /* buffer empty when initialized*/
char buf;

int getch(void) {        /* get a (possibly pushed-back) character */
	if (state == STACKEMPTY)
		return getchar();
	else {
		state = STACKEMPTY;
		return buf;
	}
}

void ungetch(int c) {    /* push character back on input */
	if (state == STACKEMPTY) {
    	buf = c;
    	state = STACKFULL;
    }
    else
    	printf("ungetch: stack is full\n");
}