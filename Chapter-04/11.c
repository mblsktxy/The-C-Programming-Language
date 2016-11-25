/* 
 * Modify getop so that it doesn't need to use ungetch. Hint: use
 * an internal static variable.
 */

#include <stdio.h>
#include <stdlib.h>  /* for atof() */
#include <ctype.h>   /* for isdigit(), isalpha() */
#include <math.h>    /* for fmod(), sin(), cos(), exp(), pow() */
#include <string.h>  /* for strcmp() */

#define MAXOP 100    /* max size of operand or operator */
#define NUMBER '0'   /* signal that a number was found */
#define MATHFUNC '1' /* signal that a math function was found */
#define VARIABLE '2' /* signal that a variable was found */

int getop(char []);
void push(double);
double pop(void);

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

#define MAXVAL 100   /* maximum depth of val stack */

int sp = 0;          /* next free stack position */
double val[MAXVAL];  /* value stack */

/* push: push f onto value stack */
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else 
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

#define STACKEMPTY 0
#define STACKFULL 1

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
 * 
 * ------------------------------------------------------
 * Logic for getting the next character and updating buff
 * if buff == -2:
 *     c = getchar()
 * else:
 *     c = buff
 *     buff = -2 
 *
 * ----------------------------------------------------------------------
 * Logic for updating buff when encounter a character of a different type
 * if c is not same type:
 *     buff = c
 */
int getop(char s[]) {
    int i, c, c1;
    static int buff = -2; // use -2 instead of -1, since EOF is -1

    while (1) {
        if (buff == -2)
            c = getchar();
        else {
            c = buff;
            buff = -2;
        } 
        if (c != ' ' && c != '\t')
            break;
    }
    if (buff == -1) {
        return EOF;
    }

    s[0] = c;
    i = 0;
    if (isalpha(c)) {
        while (1) {
            s[++i] = c = getchar(); // do not need to check buff, since buff is -2 now
            if (!isalpha(c)) {
                buff = c;
                break;
            }
        }
        s[i] = '\0';
        return MATHFUNC;
    } else if (isdigit(c)) {
        while (1) {
            s[++i] = c = getchar(); // do not need to check buff, since buff is -2 now
            if (!isdigit(c)) {
                if (c == '.') {
                    s[++i] = c = getchar();
                    if (!isdigit(c)) {
                        buff = c;
                        break;
                    }
                } else {
                    buff = c;
                    break;
                }
            }
        }
        s[i] = '\0';
        return NUMBER;
    } else if (c == '-') {
        c1 = getchar();
        buff = c1;
        if (isdigit(c1)) {
            while (1) {
                if (buff == -2)  // need to check buff now
                    c = getchar();
                else {
                    c = buff;
                    buff = -2;
                }
                s[++i] = c;
                if (!isdigit(c)) {
                    if (c == '.') {
                        s[++i] = c = getchar();
                        if (!isdigit(c)) {
                            buff = c;
                            break;
                        }
                    } else {
                        buff = c;
                        break;
                    }
                }
            }
            s[i] = '\0';
            return NUMBER;
        } else 
            return c;
    } else if (c == '.') {
        c1 = getchar();
        buff = c1;
        if (isdigit(c1)) {
            while (1) {
                if (buff == -2) 
                    c = getchar();
                else {
                    c = buff;
                    buff = -2;
                }
                s[++i] = c;
                if (!isdigit(c)) {
                    buff = c;
                    break;
                }
            }
            s[i] = '\0';
            return NUMBER;
        } else 
            return c;
    } else if (c == '=') {
        c1 = getchar();
        buff = c1;
        if (isalpha(c1)) {
            if (buff == -2) 
                    c = getchar();
                else {
                    c = buff;
                    buff = -2;
                }
            s[0] = c;
            s[1] = '\0';
            return VARIABLE;
        } else 
            return c;
    } else
        return c;
}