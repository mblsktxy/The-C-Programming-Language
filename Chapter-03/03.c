/*
 * Write a function expand(s1,s2) that expands shorthand notations like
 * a-z in the string s1 into the equivalent complete list abc...xyz in
 * s2. Allow for letters of either case and digits, and be prepared to
 * handle cases like a-b-c and a-z0-9 and -a-z. Arrange that a leading
 * or trailing - is taken literally.
 *
 * ------
 * Logic:
 * if s1[i] = '-':
 *     if i == 0 or s1[i+1] == '\0':
 *         s2[j++] = s1[i++]
 *     else if valid_shorthand(s1[i-1], s1[i+1]):
 *         update(s2)
 *     else 
 *         s2[j++] = s1[i++];
 * else
 *     s2[j++] = s1[j++];
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void expand(char*, char*);
bool valid_shorthand(char, char);

int main(void) {
    char s1[512] = "-a-z 0-9 a-d-f a-f-g-i -0-2 some text 1-1 WITH CAPITALS! 0-0 5-3 -";
    char s2[512];
    expand(s1, s2);
    printf("%s\n", s2);
    
    return EXIT_SUCCESS;
}

void expand(char s1[], char s2[]) {
	int i, j, k;

	i = j = 0;
	while(s1[i] != '\0') {
		if (s1[i] == '-') {
			if (i == 0 || s1[i+1] == '\0')
				s2[j++] = s1[i++];
			else if (valid_shorthand(s1[i-1], s1[i+1])) {
				if (s1[i-1] != s1[i+1]) {
					for (k = 1; k < s1[i+1] - s1[i-1]; k++)
						s2[j++] = s1[i-1] + k;
					i++;
				} else
					i += 2;
			} else
				s2[j++] = s1[i++];
		} else
			s2[j++] = s1[i++];
	}
	s2[j] = '\0';
}

bool valid_shorthand(char c1, char c2) {
	if (c1 >= 'a' && c1 <= 'z' && c2 >= c1 && c2 <= 'z')
		return true;
	if (c1 >= 'A' && c1 <= 'Z' && c2 >= c1 && c2 <= 'Z') 
		return true;
	if (c1 >= '0' && c1 <= '9' && c2 >= c1 && c2 <= '9')
		return true;
	else
		return false;  
}