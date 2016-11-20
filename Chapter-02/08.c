/*
 * Write a function rightrot(x,n) that returns the value of the integer
 * x rotated to the right by n bit positions.
 */

#include <stdio.h>
#include <stdlib.h>

int get_bits(unsigned);
unsigned rightrot(unsigned, int);

int main(void) {
	printf("rightrot(0xCF,2): %u\n", rightrot(0xCF,2));
	return EXIT_SUCCESS;
}

/* get_bits returns the number of bit contained in an int */
int get_bits(unsigned n) {
	int i = 2;
	int index = 1;
	while (i <= n) {
		i = i*2;
		index++;
	}
	return index;
}

unsigned rightrot(unsigned x, int n) {
	int index = get_bits(x);

	unsigned q;
	/* The rightmost n bits of x */
    q = x & ((1 << n)-1);

    return (x >> n) + (q << (index - n));
}