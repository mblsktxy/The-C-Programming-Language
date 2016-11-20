/*
 * Write a function setbits(x,p,n,y) that returns x with the n bits that
 * begin at position p set to the rightmost n bits of y, leaving the
 * other bits unchanged.
 */

#include <stdio.h>
#include <stdlib.h>

unsigned setbits(unsigned, int, int, unsigned);

int main(void) {
	printf("setbits(0xff, 5, 2, 0x2): %u\n", setbits(0xff, 5, 2, 0x2));
	return EXIT_SUCCESS;
}

unsigned setbits(unsigned x, int p, int n, unsigned y) {
    unsigned i, mask, j;
    /* The rightmost n bits of y. */
    i = y & ~(1 << n);
    /* A mask with n zeros that begin at position p. */
    mask = ~(((1 << n)-1) << (p+1-n));
    /* Make rightmost n bits of p zero ... */
    j = mask & x;
    /* ... and replace them with the rightmost n bits of y. */
    return j | i << (p+1-n);
}