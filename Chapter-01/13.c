/*
 * Write a program to print a histogram of the lengths of words in it's
 * input. It is easy to draw a histogram with the bars horizontal; a
 * vertical orientation is more challenging.
 * 
 * ------
 * Logic:
 * A: c is a regular character 
 * if A and state == IN: lword++
 * if A and state == OUT: lword++, state = IN
 * if not A and state == IN: if lword <= MAXWORDLEN:
                                 nword[lword-1]++, lword = 0
                             else:
                                 nword[MAXWORDLEN]++, lword = 0
 * if not A and state == OUT: state = OUT
 */

#include <stdio.h>
#include <stdlib.h>

#define IN  1  /* inside a word */
#define OUT 0  /* outside a word */
#define MAXWORDLEN 15

int main(void) {
    int c, state;
    int i, j;
    int lword = 0;
    int nword[MAXWORDLEN+1];

    for (i = 0; i != MAXWORDLEN+1; i++)
        nword[i] = 0;
    state = OUT;

    while ((c = getchar()) != EOF) {
        if (c != ' ' && c != '\n' && c != '\t') {
            lword++;
            if (state == OUT)
                state = IN;
        } 
        else if (state == IN) {
            if (lword <= MAXWORDLEN) {
                nword[lword-1]++;
                lword = 0;
            }
            else{
                nword[MAXWORDLEN]++;
                lword = 0;
            }
        } 
        else {
            state = OUT;
        }
    }

    /* Horizontal histogram */
    printf("Horizontal histogram:\n");

    for (i = 0; i != MAXWORDLEN+1; i++) {
        if (i != MAXWORDLEN)
            printf("%3d: ", i+1);
        else
            printf(">%2d: ", MAXWORDLEN);

        for (j = 0; j != nword[i]; j++)
            putchar('#');
        putchar('\n');
    }

    /* Vertical histogram */
    printf("\nVertical histogram:\n");

    /* Find maximum of the number of words */
    int max_nword = 0;
    for (i = 0; i != MAXWORDLEN+1; i++) {
        if (nword[i] > max_nword)
            max_nword = nword[i];
    }

    for (i = 0; i != max_nword; i++) {
        for (j = 0; j!= MAXWORDLEN+1; j++) {
            if (nword[j] >= max_nword - i)
                printf("   #");
            else
                printf("    ");
        }
        printf("\n");
    }

    for (j = 0; j != MAXWORDLEN+1; j++)
        printf("----");
    printf("\n");

    for (j = 0; j != MAXWORDLEN; j++)
        printf("%4d", j+1);
    printf(" >%2d\n", MAXWORDLEN);


}
