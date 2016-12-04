/* 
 * Rewrite appropriate programs from earlier chapters and exercises with
 * pointers instead of array indexing. Good possibilites include getline
 * (Chapter 1 and 4), atoi, itoa, and their variants (Chapter 2, 3, and 4),
 * reverse (Chapter 3), and strindex and getop (Chapter 4).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getline_manual(char *, int);
int atoi_manual(char *);
void itoa(int, char *);
void reverse(char *);
int strindex(char *, char *);
int getop(char *);

int main(void) {
	char *s1 = "12345";
	printf("%d\n", atoi_manual(s1));

	char s2[10];
	itoa(1234, s2);
	printf("%s\n", s2);

	/* note that here we cannot declare s3 as *s3 = "abcdefg", 
	   because we need to change the values of s3[i] */
	char s3[10] = "abcdefg";  
	reverse(s3);
	printf("%s\n", s3);
	
	char *s4 = "abcdefgh";
	char *s5 = "def";
	printf("%d\n", strindex(s4, s5));

	return EXIT_SUCCESS;
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

/* atoi:  convert string s to integer */
int atoi_manual(char *s) {
	int val = 0;

	for (; *s; s++)
		val = 10 * val + (*s - '0');
	return val;
}

/* itoa:  convert n to characters in s */
void itoa(int n, char *s) {
    int sign;
    char *p = s;

    sign = n;
    do {        /* generate digits in reverse order */
        *p++ = abs(n % 10) + '0';     /* get next digit */
    } while (n /= 10);                  /* delete it */
    if (sign < 0)
        *p++ = '-';
    *p = '\0';
    reverse(s);
}

/* reverse: reverse string s in place */
void reverse(char *s) {
	char *p = s;
	int temp;
	size_t n, i;

	while (*p++)
		;
	p -= 2;

	while (s < p) {
		temp = *s;
		*s++ = *p;
		*p-- = temp;
	}
}

/* strindex: return index of t in s, -1 if none */
int strindex(char *s, char *t) {
	char *i, *j, *k;

	for (i = s; *i; i++) {
		for (j = i, k = t; *k && *j == *k; j++, k++)
			;
		if (*k == '\0')
			return i-s;
	}
	return -1;
}

// /* getop:  get next operator or numeric operand */
// int getop(char *s)
// {
//     char c;
    
//     while ((*s = c = getch()) == ' ' || c == '\t')
//     	;
//     *++s = '\0';
//     if (!isdigit(c) && c != '.')
//         return c;       /* not a number */
//     s--;                /* remove the \0 */
//     if (isdigit(c))     /* collect intiger part */
//         while (isdigit(*++s = c = getch()))
//         	;
//     if (c == '.')       /* collect fraction part */
//         while (isdigit(*++s = c = getch()))
//         	;
//     *s = '\0';
//     if (c != EOF)
//         ungetch(c);
//     return NUMBER;
// }