/*
 * Write a loop equivalent to the for loop above without using && or ||.
 * 
 * ------------------
 * The original loop:
 * for (i=0;i<lim-1 && (c=getchar()) != '\n' && c != EOF; i++)
 *     s[i] = c;
 */

#include <stdio.h>
#include <stdlib.h>

#define LIMIT 512

int main(void)
{
    int i;
    int c, lim;
    char s[LIMIT];

    lim = LIMIT;
    i = 0;
    while (i < lim-1) {
        c = getchar();
        if (c == '\n')
            break;
        else if (c == EOF)
            break;
        else
            s[i++] = c;
    }
    s[i] = '\0';
    printf("%s\n", s);

    return EXIT_SUCCESS;
}