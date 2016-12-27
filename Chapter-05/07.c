/*
 * Rewrite readlines to store lines in an array supplied by main, rather
 * than calling alloc to maintain storage. How much faster is the program?
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000   /* max #lines to be sorted */
#define MAXLEN 1000     /* max length of any input line */

/* lineptr is an array of MAXLINES elements, each element of which
 * is a pointer to a char. */
char *lineptr[MAXLINES];  /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort_manual(char *lineptr[], int left, int right);

/* sort input lines */
int main(void) {
	int nlines;   /* number of input lines read */
	char s[MAXLINES][MAXLEN];
	int i;

	for (i = 0; i < MAXLINES; ++i) {
        *(lineptr+i) = s[i];
	}

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsort_manual(lineptr, 0, nlines-1);
		writelines(lineptr, nlines);
		return EXIT_SUCCESS;
	} else {
		printf("error: input too big to sort\n");
		return EXIT_FAILURE;
	}
}

int getline_manual(char *, int);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines) {
	int len, nlines;
	char line[MAXLEN];

	nlines = 0;
	while ((len = getline_manual(line, MAXLEN)) > 0)
		if (nlines >= maxlines)
			return -1;
		else {
			line[len-1] = '\0';  /* delete newline */
			strcpy(lineptr[nlines++], line);
		}
	return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines) {
	int i;

	for (i = 0; i < nlines; i++) 
		printf("%s\n", lineptr[i]);
}

// /* writelines: write output lines*/
// int writelines(char *lineptr[], int nlines) {
// 	while (nlines-- > 0) 
// 		printf("%s\n", *lineptr++);
// }

/* getline_manual: get line into s, return length */
int getline_manual(char *s, int lim) {
	int c;
	char *p = s;

	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		*p++ = c;
	if (c == '\n')
		*p++ = c;
	*p = '\0';
	return p - s;
}

/* qsort_manual: sort v[left]...v[right] into increasing order */
void qsort_manual(char *v[], int left, int right) {
	int i, last;
	void swap(char *v[], int i, int j);

	if (left >= right)    /* do nothing if array contains */
		return;           /* fewer than two elements */
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++) 
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort_manual(v, left, last-1);
	qsort_manual(v, last+1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j) {
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}