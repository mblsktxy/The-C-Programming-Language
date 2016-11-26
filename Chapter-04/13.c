/* 
 * Write a recursive version of the function reverse(s), which reverses
 * the string s in place.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char *, int, int);

int main(void) {
    char s[50] = "Hello, world!";
    
    printf("Original s: %s\n", s);
    reverse(s, 0, strlen(s) - 1);
    printf("Reverse s: %s\n", s);
    reverse(s, 0, strlen(s) - 1);
    printf("Reverse again: %s\n", s);

    return EXIT_SUCCESS;
}

void reverse(char s[], int i, int j) {
	int tmp;

    tmp = s[i];
    s[i] = s[j];
    s[j] = tmp;

    if (i < j)
		reverse(s, ++i, --j);
}