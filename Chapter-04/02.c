/*
 * Extend atof to handle scientific notation of the form 123.45e-6 
 * where a floating-point number may be followed by e or E and an
 * optionally signed exponent.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINE 100

int getline_manual(char *, int);

/* find all lines matching pattern */
int main(void) {
	double sum, atof_manual(char *);
	char line[MAXLINE];
	int getline_manual(char *, int);

	while (getline_manual(line, MAXLINE) > 0)
		printf("\t%g\n", sum += atof_manual(line));
	
	return EXIT_SUCCESS;
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


/* atof_manual: convert string s to double */
double atof_manual(char s[]) {
	double val, power, power_expression;
	int i, j, sign_number, sign_power;

	for (i = 0; isspace(s[i]); i++) /* skip white space */
		;
	sign_number = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power /= 10.0;
	}
	if (s[i] == 'e' || s[i] == 'E')
		i++;
	sign_power = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (power_expression = 0.0; isdigit(s[i]); i++)
		power_expression = 10 * power_expression + (s[i] - '0');
	if (sign_power == 1)
		for (j = 0; j < power_expression; j++)
			power *= 10.0;
	else 
		for (j = 0; j < power_expression; j++)
			power /= 10.0;
	return sign_number * val * power;
}
