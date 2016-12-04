/* 
 * Write the function strend(s,t), which returns 1 if the string t 
 * occurs at the end of the string s, and zero otherwise.
 */

#include <stdio.h>
#include <stdlib.h>

int strend(char *, char *);

int main(void) {
	char s1[15] = "absdefg";
	char s2[15] = "defg";
	char s3[15] = "fdas";

	printf("%d\n", strend(s1, s2));
	printf("%d\n", strend(s1, s3));
	return EXIT_SUCCESS;
}

int strend(char *s, char *t) {
	char *p = t;
	size_t i;
	size_t n;

	while (*s)  /* go to the end of string s */
		s++; 
	while (*p)  /* go to the end of string t */
		p++;
	n = p - t;  /* get the length of string t */

	for (i = 0; i < n; i++)
		if (*--s != *--p)
			return 0;
	return 1;
}