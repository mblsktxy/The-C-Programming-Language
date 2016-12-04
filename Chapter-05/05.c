/* 
 * Write versions of the library functions strncopy, strncat, and strncmp,
 * which operate on at most the first n characters of their augument
 * strings. For example, strncopy(s,t,n) copies at most n characters of t
 * to s. Full descriptions are in Appendix B.
 */

#include <stdio.h>
#include <stdlib.h>

char *strncopy_manual(char *, char *, int);
char *strncat_manual(char *, char *, int);
int strncmp_manual(char *, char *, int);

int main(void) {
	char s1[15] = "abcdefg";
	char s2[15] = "zyxwvu";
	printf("%s\n", strncopy_manual(s1, s2, 3));

	char s3[15] = "abcdefg";
	char s4[15] = "zyxwvu";
	printf("%s\n", strncat_manual(s3, s4, 4));

	char s5[15] = "abcdefg";
	char s6[15] = "abcm";
	printf("%d\n", strncmp_manual(s5, s6, 3));
	printf("%d\n", strncmp_manual(s5, s6, 4));
	printf("%d\n", strncmp_manual(s5, s6, 6));

	return EXIT_SUCCESS;
}

/* 
 * copy at most n characters of string ct to s; return s.
 * Pad with '\0's if t has fewer than n characters. 
 */
char *strncopy_manual(char *s, char *ct, int n) {
	char *p = s;
	int i;

	for (i = 0; i < n; i++) {
		*p++ = *ct++;
		if (*ct == '\0') {
			*p = '\0';
			return s;
		}
	}
	return s;
}

/* 
 * concatenate at most n characters of string ct to string
 * s, terminate s with '\0'; return s.
 */
char *strncat_manual(char *s, char *ct, int n) {
	char *p = s;

	while (*p++)
		;
	p--;
	while (n-- > 0 && (*p++ = *ct++))
		;
	*p = '\0';
	return s;
}

/* 
 * compare at most n characters of string cs to string ct;
 * return <0 if cs < ct, 0 if cs == ct, or >0 if cs > ct.
 */
int strncmp_manual(char *cs, char *ct, int n) {
	while (n-- > 0 && *cs && *ct) {
		if (*cs != *ct)
			return *cs - *ct;
		cs++;
		ct++;
	}
	return 0;
}