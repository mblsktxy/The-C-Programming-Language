/*
 * Write a program to copy its input to its output, replacing each tab
 * by \t, each backspace by \b, and each backslash by \\. This makes
 * tabs and backspaces visible in a unambiguous way.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int c;

	while ((c = getchar()) != EOF) {
		if (c == '\t')
			printf("\\t");
		else if (c == '\b') 
			printf("\\b");
		else if (c == '\\')
			printf("\\\\");
		else 
			printf("%c", c);
	}

	return EXIT_SUCCESS;
}