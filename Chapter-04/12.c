/*
 * Adapt the ideas of printd to write a recursive version of itoa; that
 * is, convert an integer into a string by calling a recursive routine.
 */

#include <stdio.h>
#include <stdlib.h>

void itoa(int, char *);
void itoa_execute(int, char *);
int i; // global variable representing index of s

int main(void) {
    char s[50];
    
    itoa(1000, s);
    printf("%d is converted to %s\n", 1000, s);
    itoa(-4353, s);
    printf("%d is converted to %s\n", -4353, s);

    return EXIT_SUCCESS;
}

void itoa(int n, char s[]) {
    i = 0;
    itoa_execute(n, s);
    s[i] = '\0';
}

void itoa_execute(int n, char s[]) {
    if (n < 0) {
    	s[0] = '-';
        i = 1;
        n = -n; 
    }
    if (n / 10)
    	itoa_execute(n / 10, s);
    s[i++] = '0' + n % 10;
}