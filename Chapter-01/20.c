/*
 * Write a program detab that replaces tabs in the input with the proper
 * number of blanks to space to the next tab stop. Assume a fixed set of
 * tab stops, say every n columns. Should n be a variable or a symbolic
 * parameter?
 */

#include <stdio.h>
#include <stdlib.h>

#define TABWIDTH 8

int main(void) {
	int c, i, col;

	col = 0;
	while ((c = getchar()) != EOF) {
		if (c == '\t') {
			for (i = 0; i != TABWIDTH - col % TABWIDTH; i++)
				printf(" ");
			col = col + TABWIDTH - col % TABWIDTH;
		} else {
			putchar(c);
			col++;
			if (c == '\n')
				col = 0;
		}
	}
}