/*
 * Write the function htoi(s), which converts a string of hexadecimal
 * digits (including an optional 0x or 0X) into its equivalent integer
 * value. The allowable digits are 0 through 9, a through f, and A
 * through F. 
 */

#include <stdio.h>
#include <stdlib.h>

int htoi(char s[]);

int main(void)
{
    char s[1024];
    int i, c;
    for (i = 0; (c = getchar()) != '\n'; i++)
        s[i] = c;
    s[i] = '\0';
    printf("%s: %d\n", s, htoi(s));
    return EXIT_SUCCESS;
}

/* htoi:  convert hexdicimal string s to integer */
int htoi(char s[])
{
    int i;
    int c, n;

    n = 0;
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
        for (i = 2; (c = s[i]) != '\0'; ++i) {
            if (c >= '0' && c <= '9')
                n = n*16 + c - '0';
            else if (c >= 'a' && c <= 'f')
                n = n*16 + 10 + c - 'a';
            else if (c >= 'A' && c <= 'F')
                n = n*16 + 10 + c - 'A'; 
        }
        return n;
    }
}