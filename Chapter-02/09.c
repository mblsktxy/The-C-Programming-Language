/*
 * In a two's complement number system, x &= (x-1) deletes the rightmost
 * 1-bit in x. Explain why. Use this observation to write a faster
 * version of bitcount.
 *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * Original bitcount:
 * // bitcount: count 1 bits in x
 * int bitcount(unsigned x) {
 *     int b;
 *     for (b = 0; x != 0; x >>= 1) 
 *         if (x & 01)
 *             b++;
 *     return b;	
 * }
 */

#include <stdio.h>
#include <stdlib.h>

int bitcount(unsigned x);

int main(void)
{
    printf("%d\n", bitcount(0xFF));
    return EXIT_SUCCESS;
}

/* bitcount:  count set bits in x */
int bitcount(unsigned x)
{
    int b;
    for (b = 0; x != 0; x &= (x-1))
        b++;
    return b;
}