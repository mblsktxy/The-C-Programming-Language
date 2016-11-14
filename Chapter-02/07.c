/*
 * Write a function invert(x,p,n) that returns x with the n bits that
 * begin at position p inverted (i.e., 1 changed into 0 and vice versa),
 * leaving the others unchanged. 
 */

#include <stdio.h>
#include <stdlib.h>

unsigned invert(unsigned, int, int);

int main(void)
{
	printf("invert(0xFF,5,2): %u\n", invert(0xFF,5,2));
	return EXIT_SUCCESS;
}

unsigned invert(unsigned x, int p, int n) {
	unsigned mask;
	/* A mask with n ones that begin at position p. */
	mask = ((1 << n)-1) << (p-n+1);
	return mask ^ x;
}