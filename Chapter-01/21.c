/*
 * Write a program entab that replaces strings of blanks with the
 * minimum number of tabs and blanks to achieve the same spacing. Use
 * the same stops as for detab. When either a tab or a single blank
 * would suffice to reach a tab stop, which should be given preference?
 *
 * ------ 
 * Logic:
 * A: c is a regular character (character except ' ' and '\t')
 * REGULAR: indicates that input is a regular character
 * NONREGULAR: indicates that input is either a ' ' or '\t'

 * if A and REGULAR: print c, col++
 * if A and NONREGULAR: state = REGULAR, col++, entab(last_regular_col, col), print c
 * if not A and REGULAR: state = NONREGULAR, last_regular_col = col, update_col(c)
 * if not A and NONREGULAR: update_col(c)
 */

#include <stdio.h>
#include <stdlib.h>

#define TABWIDTH 8
#define REGULAR 1
#define NONREGULAR 0

int update_col(int, int);
void entab(int, int);

int main(void) {
    int c, i, state;
    int col, last_regular_col;

    col = 0;
    last_regular_col = 0;
    state = REGULAR; // state is not important here, can be either REGULAR or NONREGULAR

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            col = 0;
            last_regular_col = 0;
        } else if (c != ' ' && c != '\t') {
            if (state == REGULAR) {
                putchar(c);
                col = update_col(c, col);
            } else {
                state = REGULAR;
                col = update_col(c, col);
                entab(last_regular_col, col);
                putchar(c);
            }
        } else if (state == REGULAR) {
            state = NONREGULAR;
            last_regular_col = col;
            col = update_col(c, col);
        } else {
            col = update_col(c, col);
        }
    }
    return EXIT_SUCCESS;
}

int update_col(int c, int col) {
    if (c != '\t') {
        col++;
        return col;
    } else {
        col = col + TABWIDTH - col % TABWIDTH;
        return col;
    }
}

void entab(int last_regular_col, int col) {
    int index1, index2;
    int i, j;

    index1 = (last_regular_col - last_regular_col % TABWIDTH) / TABWIDTH;
    index2 = (col - col % TABWIDTH) / TABWIDTH;
    if (index2 != index1) {
        for (i = 0; i < index2 - index1; i++)
            putchar('\t');
        for (j = 1; j < col % TABWIDTH; j++)
            putchar(' ');
    } else {
        for (j = 1; j < col - last_regular_col; j++)
            putchar(' ');
    }
}