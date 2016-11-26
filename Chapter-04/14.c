/*
 * Define a macro swap(t,x,y) that interchanges two arguments of 
 * type t. (Block structure will help.)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define swap(t, x, y) {t tmp; tmp = x; x = y; y = tmp;}

int main(void) {
    int ia = 20, ib = 35;
    printf("Before swap: %d, %d\n", ia, ib);
    swap(int, ia, ib);
    printf(" After swap: %d, %d\n", ia, ib);

    double da = 0.3432, db = 348.24;
    printf("Before swap: %g, %g\n", da, db);
    swap(double, da, db);
    printf(" After swap: %g, %g\n", da, db);

    return EXIT_SUCCESS;
}