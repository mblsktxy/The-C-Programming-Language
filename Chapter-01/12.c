/*
 * Write a program that prints its input one word per line.
 */

#include <stdio.h>
#include <stdlib.h>

/* 
 * The logic involved in this problem:
 * state IN indicates the previous input is in the word
 * state OUT indicates the previous input is not in the word
 * A: c is a regular character
 * 
 * if A and state == OUT: print c, state = IN
 * if A and state == IN: print c
 * if not A and state == OUT: 
 * if not A and state == IN: print \n, state = OUT 
 */

#define IN 1
#define OUT 0

int main(void)
{
	int c, state;

	state = OUT;

	/* This reflects the whole logic */
	// while ((c = getchar()) != EOF) {
	// 	if ((c != ' ' && c != '\n' && c != '\t') && state == OUT) {
	// 		putchar(c);
	// 		state = IN;
	// 	}
	// 	else if ((c != ' ' && c != '\n' && c != '\t') && state == IN) {
	// 		putchar(c);
	// 	}
	// 	else if ((c == ' ' || c == '\n' || c == '\t') && state == IN) {
	// 		putchar('\n');
	// 		state = OUT;
	// 	}
	// }

	/* This reflects the simplified logic */
	while ((c = getchar()) != EOF) {
		if (c != ' ' && c != '\n' && c != '\t') {
			putchar(c);
			if (state == OUT) {
				state = IN;				
			}
		}
		else if (state == IN) {
			putchar('\n');
			state = OUT;
		}
	}

	return EXIT_SUCCESS;
}