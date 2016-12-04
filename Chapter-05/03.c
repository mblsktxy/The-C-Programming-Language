/* 
 * Write a pointer version of the function strcat that we showed in
 * Chapter 2: strcat(s,t) copies the string t the end of s.
 */

#include <stdio.h>
#include <stdlib.h>

void strcat_manual(char *, char *);

int main(void) {
	char s[15] = "hello, ";
	char t[15] = "world!";

	strcat_manual(s, t);
	printf("%s\n", s);

	return EXIT_SUCCESS;
}

void strcat_manual(char *s, char *t) {
	while (*s++)
		;
	s--;
	while (*s++ = *t++)
		;
	*s = '\0';
}