/*
 * Write a program to remove trailing blanks and tabs from each line
 * of input, and to delete entirely blank lines.
 */
 
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000

int get_line(char line[], int maxline);

int main(void)
{
    char line[MAXLINE];    /* current input line */
    int len;
    int i;

    while ((len = get_line(line, MAXLINE)) > 0) {
        for (i = len-2; i >= 0; i--) {
            if (line[i] != ' ' && line[i] != '\t')
                break;
        }
        if ( i!= -1) {
            line[i+1] = '\n';
            line[i+2] = '\0';
            printf("%s", line);
        }
    }
    return EXIT_SUCCESS;
}

/* get_line:  read a line into s, return length */
int get_line(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}