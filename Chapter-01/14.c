#include <stdio.h>
#include <stdlib.h>

#define TABLELEN 128 /* number of characters in ASCII-I */

int main(void)
{
    int c, nchar[TABLELEN];

    for (c = 0; c != TABLELEN; c++)
        nchar[c] = 0;

    while ((c = getchar()) != EOF)
        nchar[c]++;

    /* Horizontal histogram */
    for (c = 0; c != TABLELEN; c++) {
        if (nchar[c] > 0) {
            if (c == '\b')          /* backspace */
                printf("\\b");
            else if (c == '\n')     /* new line*/
                printf("\\n");
            else if (c == '\t')     /* (horizontal) tab */
                printf("\\t");
            else                    /* all other nchar */
                printf("%2c", c);
            printf(" (%3d): %3d\n", c, nchar[c]);
        }
    }
    return EXIT_SUCCESS;
}