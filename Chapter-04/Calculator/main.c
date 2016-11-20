/*
 * Add commands for handling vaiables. (It's easy to provide twenty-six
 * variables with single-letter names.) Add a variable for the most recently
 * printed value.
 *
 * ------------------------------
 * Use string pattern like below:
 * 3 5 + =t last 7 4 - * =m last
 *
 */

#include <stdio.h>
#include <stdlib.h>  /* for atof() */
#include <math.h>    /* for fmod(), sin(), cos(), exp(), pow() */
#include <ctype.h>   /* for tolower() */
#include <string.h>  /* for strcmp() */
#include "calc.h"

#define MAXOP 100    /* max size of operand or operator */

/* reverse Polish calculator */
int main(void) {
    int type, v;
    double op2;
    char s[MAXOP];
    double last;           /* variable for the most recently printed variable */
    double variables[26];  /* 26 variables with single-letter names(a-z) */

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case MATHFUNC:
                if (strcmp(s, "sin") == 0)
                    push(sin(pop()));
                else if (strcmp(s, "cos") == 0)
                    push(cos(pop()));
                else if (strcmp(s, "exp") == 0)
                    push(exp(pop()));
                else if (strcmp(s, "pow") == 0) {
                    op2 = pop();
                    push(pow(pop(), op2));
                }
                else if (strcmp(s, "last") == 0) {
                    printf("the most recently printed value is %g\n", last);
                }
                else 
                    printf("error: unknown command %s\n", s);
                break;
            case VARIABLE:
                v = tolower(s[0]);
                last = variables[v - 'a'] = pop();
                push(last);
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '%':
                op2 = pop();
                if (op2 != 0.0)
                    push(fmod(pop(), op2));
                else 
                    printf("error: zero divisor\n");
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }

    return EXIT_SUCCESS;
}