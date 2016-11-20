/*
 * Rewrite the function lower, which converts upper case letters to
 * lower case, with a conditional expression instead of if-else. 
 */

#include <stdio.h>
#include <stdlib.h>

int lower(int c);

int main(void) {
    putchar(lower('R'));
    putchar('\n');
    return EXIT_SUCCESS;
}

int lower(int c) {
    return ('A' <= c && c <= 'Z') ? c - 'A' + 'a' : c;
}