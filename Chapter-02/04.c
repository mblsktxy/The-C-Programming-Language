/*
 * Write an alternate version of squeeze(s1,s2) that deletes each
 * character in the string s1 that matches any character in the string s2. 
 */

#include <stdio.h>
#include <stdlib.h>

#define FOUND_A_MATCH 1
#define NO_MATCH 0

void squeeze(char *, char *);

int main(void) 
{
	char s1[] = "abcddef";
	char s2[] = "abd"; 
	squeeze(s1, s2);
	printf("%s\n", s1);
}

void squeeze(char s1[], char s2[])
{
	int i, j, k;
	int state;

	k = 0;
	for (i = 0; s1[i] != '\0'; i++) {
		state = NO_MATCH;
		for (j = 0; s2[j] != '\0'; j++) {
			if (s1[i] == s2[j]) {
				state = FOUND_A_MATCH;
				break;
			}
		}
		if (state == NO_MATCH)
			s1[k++] = s1[i];
	}
	s1[k] = '\0';
}
