/*
 * Write the function strrindex(s,t), which returns the position of the
 * rightmost occurrence of t in s, or -1 if there is none. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

int getline_manual(char *, int);
int strrindex(char *, char *);

char pattern[] = "ould"; /* pattern to search for */

/* find all lines matching pattern */
int main(void) {
	char line[MAXLINE];
	int found = 0;
	int index;

	while (getline_manual(line, MAXLINE) > 0)
		if ((index = strrindex(line, pattern)) >= 0) {
			printf("%s", line);
			printf("%d\n", index);
			found++;
		}
}

/* getline_manual: get line into s, return length */
int getline_manual(char s[], int lim) {
	int c, i;

	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

/*strrindex: return index of the rightmost occurrence of t in s, -1 if none */
int strrindex(char s[], char t[]) {
	int i, j, k;
	for (i = strlen(s)-1; i >= 0; i--) {
		for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
			;
		if (k > 0 && t[k] == '\0')
			return i;
	}
	return -1;
}