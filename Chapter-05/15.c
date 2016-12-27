/*
 * Add the option -f to fold upper and lower case together, so that case
 * distinctions are not made dring sorting; for example, a and A compare 
 * equal.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>   /* for use of tolower() */

#define MAXLINES 5000   /* max #lines to be sorted */
#define MAXLEN 1000     /* max length of any input line */

char *lineptr[MAXLINES];  /* pointers to text lines */

int readlines(char **, int);
void writelines(char **, int);

void qsort_manual(void **, int, int, int (*comp)(void *, void *), int);
int numcmp(char *, char *);
int strcmp_casefolding(char *, char *);

/* sort input lines */
int main(char argc, char **argv) {
    int nlines;           /* number of input lines read */
    int numeric = 0;      /* 1 if numeric sort */
    int reversing = 0;    /* 1 if sorting in reverse order */
    int casefolding = 0;  /* 1 if case distinctions are not made */ 
    int c;

    // if (argc > 1 && strcmp(argv[1], "-n") == 0)
    //     numeric = 1;
    while ((--argc > 0) && (**++argv == '-'))
    	while (c = *++argv[0])
    		switch (c) {
    		case 'n':
    			numeric = 1;
    			break;
    		case 'r':
    			reversing = 1;
    			break;
    		case 'f':
    			casefolding = 1;
    			break;
    		default:
    			printf("sort: illegal operation %c\n", c);
    			argc = 0;
    			break;
    		}

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort_manual((void **) lineptr, 0, nlines-1, 
              		 (int (*)(void*, void*))(numeric ? numcmp : (casefolding ? strcmp_casefolding : strcmp)),
              		 reversing);
        writelines(lineptr, nlines);
        return EXIT_SUCCESS;
    } else {
        printf("input too big to sort\n");
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

/*qsort_manual: sort v[left]...v[right] into increasing order */
void qsort_manual(void *v[], int left, int right, int (*comp)(void *, void *), int order) {
	int i, last;
	void swap(void **, int, int);

	if (left >= right)   /* do nothing if array contains */
		return;          /* fewer than tow elements */
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left + 1; i <= right; i++) 
		if (order == 0 && (*comp)(v[i],v[left]) < 0)
			swap(v, ++last, i);
		else if (order == 1 && (*comp)(v[i],v[left]) > 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort_manual(v, left, last-1, comp, order);
	qsort_manual(v, last+1, right, comp, order);
}

int numcmp(char *s1, char *s2) {
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

int strcmp_casefolding(char *s1, char *s2) {
	for (; tolower(*s1) == tolower(*s2); s1++, s2++)
        if (*s1 == '\0')
            return 0;
	return tolower(*s1) - tolower(*s2);
}

void swap(void *v[], int i, int j) {
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}