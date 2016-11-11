/*
 * Revise the main routine of the longest-line program so it will
 * correctly print the length of arbitrarily long input lines, and as
 * much as possible of the text.
 */

#include <stdio.h>
#include <stdlib.h>

/* 
 * Logic:
 * A: output from get_line includes '\n'
 *    which is equivalent to line[len-1] == '\n'
 * state == NEW: the start of a new line
 * state == OLD: in the middle of a line
 *
 * if A and state == NEW: 
 *      line_length = len
 *      if line_length > max:
 *          max = line_length
 *          copy(longest, line)
 * if A and state == OLD: 
 *      line_length += len
 *      if line_length > max:
 *          max = line_length
 *      state = NEW
 * if not A and state == NEW: 
 *      line_length = len
 *      copy(longest, line)
 *      state = OLD
 * if not A and state == OLD: 
 *      line_length += len
 */

#define MAXLINE 10    /* maximum input line size */
#define NEW 1
#define OLD 0

int get_line(char line[], int maxline);
void copy(char to[], char from[]);

int main(void)
{
    int len;                /* current line length */
    int max;                /* maximum length seen so far */
    int line_length;        /* record the potential length of a line */
    int state;              /* record the previous state */
    char line[MAXLINE];     /* current input line */
    char longest[MAXLINE];  /* longest line saved here */

    max = 0;
    state = NEW;

    while ((len = get_line(line, MAXLINE)) > 0) {
        if (line[len-1] == '\n') {
            if (state == NEW) {
                line_length = len;
                if (line_length > max) {
                    max = line_length;
                    copy(longest, line);
                } 
            } else {
                line_length += len;
                if (line_length > max)
                    max = line_length;
                state = NEW;
            }
        } else if (state == NEW) {
            line_length = len;
            copy(longest, line);
            state = OLD;
        } else
            line_length += len;
    } 
    if (max > 0) {   /* there was a line */
        printf("%s", longest);
        if (longest[max-1] != '\n')
            putchar('\n');
        printf("%d characters\n", max);
    }
    return EXIT_SUCCESS;
}

/* get_line:  read a line into s, return length 
 * this line does not include the '\0' character
 */
int get_line(char s[], int lim)
{
    int c, i;

    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

/* copy:  copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}