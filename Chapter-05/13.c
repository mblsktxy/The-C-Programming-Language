/* 
 * Write the program tail, which prints the last n lines of its input.
 * By default, n is 10, let us say, but it can be changed by an optional
 * augument, so that
 *     tail -n
 * prints the last n lines. The program should behave rationally no matter
 * how unreasonable the input or the value of n. Write the program so it
 * makes the best use of available storage; lines should be stored as in 
 * the sorting program of Section 5.6, not in a two-dimensional array of
 * fixed size.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000      /* max #lines of input */
#define MAXLEN 1000        /* max length of any input line */
#define DEFAULTTAILNUM 10

int readlines(char **, int);
void writelines(char **, int);

char *lineptr[MAXLINES];

int main(char argc, char *argv[]) {
	int nlines;  /* number of input lines read */
	int tailnum, p;

	tailnum = DEFAULTTAILNUM;
	if (argc > 1 && **++argv == '-')
		if ((p = atoi(++(*argv))) > 0)
			tailnum = p;

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		if (nlines < tailnum)
			tailnum = nlines;
		writelines(lineptr + nlines - tailnum, tailnum);
		return EXIT_SUCCESS;
	} else {
		printf("error: input too big to sort\n");
		return EXIT_FAILURE;
	}
}

int getline_manual(char *, int);
char *alloc(int);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines) {
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ((len = getline_manual(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len-1] = '\0';  /* delete newline */
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}

/* writelines: write output lines*/
void writelines(char *lineptr[], int nlines) {
	while (nlines-- > 0) 
		printf("%s\n", *lineptr++);
}

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

#define ALLOCSIZE 10000  /* size of available space */

static char allocbuf[ALLOCSIZE];  /* storage for alloc */
static char *allocp = allocbuf;   /* next free position */

/* alloc: return pointer to n characters */
char *alloc(int n) {
	if (allocbuf + ALLOCSIZE - allocp >= n) {
		allocp += n;
		return allocp - n;
	} else
		return 0;
}

/* afree: free storage pointed to by p */
void afree(char *p) {
	if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
		allocp = p;
}