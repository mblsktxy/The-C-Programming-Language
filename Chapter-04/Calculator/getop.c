#include <stdio.h>
#include <ctype.h>   /* for isdigit(), isalpha() */
#include "calc.h"

/* getop: get next operator or numberic operand 
 * 
 * -------
 * Logic :
 * if c is ' ' or '\t':
 *     do nothing, nelnect
 * if c is charater:
 *     get_the_whole_string
 *     return MATHFUNC
 * if c is number:
 *     get_the_whole_number
 *     return NUMBER
 * if c is '-':
 *     if next is number:
 *         get_the_whole_number
 *         return NUMBER
 *     else
 *         return c
 * if c is '.':
 *     if next is number:
 *         get_the_whole_number_without_judging_'.'_again
 *         return NUMBER
 *     else
 *         return c
 * if c is '=':
 *     if next is character:
 *         s = next character
 *         return VARIABLE
 *     else
 *         return c; 
 * if c is other thing:
 *     return c
 */
int getop(char s[]) {
    int i, c, c1;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    i = 0;
    if (isalpha(c)) {
        while (isalpha(s[++i] = c = getch()))
            ;
        s[i] = '\0';  
        ungetch(c);
        return MATHFUNC;
    } else if (isdigit(c)) {
        while (isdigit(s[++i] = c = getch()))
            ;
        if (c == '.')
            while (isdigit(s[++i] = c = getch()))
                ;
        s[i] = '\0';
        ungetch(c);
        return NUMBER; 
    } else if (c == '-') {
        c1 = getch();
        ungetch(c1);
        if (isdigit(c1)) {
            while (isdigit(s[++i] = c = getch()))
                ;
            if (c == '.')
                while (isdigit(s[++i] = c = getch()))
                    ;
            s[i] = '\0';
            ungetch(c);
            return NUMBER;
        } else 
            return c;
    } else if (c == '.') {
        c1 = getch();
        ungetch(c1);
        if (isdigit(c1)) {
            while (isdigit(s[++i] = c = getch()))
                ;
            s[i] = '\0';
            ungetch(c);
            return NUMBER;
        } else
            return c;
    } else if (c == '=') {
        c1 = getch();
        ungetch(c1);
        if (isalpha(c1)) {
            s[0] = getch();
            s[1] = '\0';
            return VARIABLE;
        } else
            return c;
    }
    else 
        return c;
}