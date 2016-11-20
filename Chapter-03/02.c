/*
 * Write a function escape(s,t) that converts characters like newline
 * and tab into visible escape sequences like \n and \t as it copies the
 * string t to s. Use a switch. Write a function for the other direction
 * as well, converting escape sequences into the real characters. 
 */

#include <stdio.h>
#include <stdlib.h>

#define SLASH 1
#define NONSLASH 0

void escape(char s[], char t[]) {
	int i, j;

	for (i = j = 0; t[i] != '\0'; i++) {
		switch (t[i]) {
			case '\n':
				s[j++] = '\\';
				s[j++] = 'n';
				break;
			case '\t':
				s[j++] = '\\';
				s[j++] = 't';
				break;
			default:
				s[j++] = t[i];
				break;
		}
	}
	s[j] = '\0';
}

void unescape(char s[], char t[]) {
	int i, j;
	int state;

	state == NONSLASH;
	for (i = j = 0; s[i] != '\0'; i++) {
		switch (s[i]) {
			case '\\':
				state = SLASH;
				break;
			case 'n':
				if (state == SLASH)
					t[j++] = '\n';
				else
					t[j++] = s[i];
				state = NONSLASH;
				break;
			case 't':
				if (state == SLASH)
					t[j++] = '\t';
				else
					t[j++] = s[i];
				state = NONSLASH;
				break;
			default:
				t[j++] = s[i];
				state = NONSLASH;
				break;
		}
	}
	t[j] = '\0';
}

int main(void) {
    int i;
    char c, s[1024], t[1024];
    
    i = 0;
    while ((c = getchar()) != EOF)
        t[i++] = c;
    t[i] = '\0';
    
    printf("%s\n", t);
    escape(s, t);
    printf("%s\n", s);
    unescape(s, t);
    printf("%s\n", t);
    
    return EXIT_SUCCESS;
}