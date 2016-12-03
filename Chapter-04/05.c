/*
 * Add access to library functions like sin, exp, and pow. See <math.h>
 * in Appecdix B, Section 4.
 */

#include <stdio.h>
#include <stdlib.h>  /* for atof() */
#include <ctype.h>   /* for isdigit(), isalpha() */
#include <math.h>    /* for fmod(), sin(), cos(), exp(), pow() */
#include <string.h>  /* for strcmp() */

#define MAXOP 100    /* max size of operand or operator */
#define NUMBER '0'   /* signal that a number was found */
#define MATHFUNC '1' /* signal that a math function was found */

int getop(char []);
void push(double);
double pop(void);

/* reverse Polish calculator */
int main(void) {
    int type;
    double op2;
    char s[MAXOP];

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
            else 
                printf("error: unknown command %s\n", s);
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

int getch(void);
void ungetch(int);

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
    } else 
        return c;
}

#define BUFSIZE 100

char buf[BUFSIZE];    /* buffer for ungetch */
int bufp = 0;         /* next free position in guf */

int getch(void) {     /* get a (possibly pushed back) character */
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) { /* push character back on input */
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else 
        buf[bufp++] = c;
}