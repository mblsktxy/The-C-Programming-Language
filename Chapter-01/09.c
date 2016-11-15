/*
 * Write a program to copy its input to its output, replacing each string
 * of one or more blanks by a sinle blank.
 *
 * ----------------------------------- 
 * The logic involved in this problem:
 * state BLANK indicates the previous input is a blank
 * state NOTBLANK indicates the previous input is not a blank
 * A: c is a blank
 * 
 * if A and state == BLANK:
 * if A and state == NOTBLANK: state = BLANK
 * if not A and state == BLANK: print ' ', print c, state = NOTBLANK 
 * if not A and state == NOTBLANK: print c
 */

#include <stdio.h>
#include <stdlib.h>

#define BLANK 1
#define NOTBLANK 0

int main(void)
{
    int c, state;

    state = NOTBLANK;

    while ((c = getchar()) != EOF) {
        if (c != ' ') {
            if (state == NOTBLANK)
                putchar(c);
            else {
                putchar(' ');
                putchar(c);
                state = NOTBLANK;
            }
        }
        else {
            if (state == NOTBLANK)
                state = BLANK;
        }
    }

    return EXIT_SUCCESS;
}