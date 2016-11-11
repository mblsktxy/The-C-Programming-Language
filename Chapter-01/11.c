/*
 * How would you test the word count program? What kinds of
 * input are most likely to uncover bugs if there are any?
 */

#include <stdio.h>
#include <stdlib.h>

#define IN 1
#define OUT 0

int main()
{
	int c, nl, nw, nc, state;

	state = OUT;
	nl = nw = nc = 0;
	while ((c = getchar()) != EOF) {
		++nc;
		if (c == '\n')
			++nl;
		if (c == ' ' || c == '\n' || c == '\t')
			state = OUT;
		else if (state == OUT) {
			state = IN;
			++nw;
		}
	}
	printf("Number of lines: %d\n", nl);
	printf("Number of words: %d\n", nw);
	printf("Number of characters: %d\n", nc);

	return EXIT_SUCCESS;
}