/* 
 * An alternate organization uses getline to rad an entire input line;
 * this makes getch and ungetch unnecessary. Revise the calculator to
 * use this approach.
 * 
 * ------------------------------
 * Use string pattern like below:
 * 3 5 + =t last 7 4 - * =m last
 *
 */

#include <stdio.h>
#include <stdlib.h>   /* for atof() */
#include <ctype.h>    /* for isdigit(), isalpha() */
#include <math.h>     /* for fmod(), sin(), cos(), exp(), pow() */
#include <string.h>   /* for strcmp() */

#define MAXLINE 1000  /* max size of a single line */
#define MAXOP 100     /* max size of operand or operator */
#define NUMBER '0'    /* signal that a number was found */
#define MATHFUNC '1'  /* signal that a math function was found */
#define VARIABLE '2'  /* signal that a variable was found */

int getop(char []);
void push(double);
double pop(void);
int getline_manual(char *, int);

char line[MAXLINE];
int lineindex = 0;

/* reverse Polish calculator */
int main(void)
{
    int type;
    int v;
    double op2;
    char s[MAXOP];
    double last;           /* variable for the most recently printed variable */
    double variables[26];  /* 26 variables with single-letter names(a-z) */

    while (getline_manual(line, MAXLINE) > 0) {
        lineindex = 0;
    	while ((type = getop(s)) != '\0') {
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
    }

    return EXIT_SUCCESS;
}

#define MAXVAL 100   /* maximum depth of val stack */

int sp = 0;          /* next free stack position */
double val[MAXVAL];  /* value stack */

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else 
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

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

int getop(char s[])
{
    int i, c, c1;

    while ((s[0] = c = line[lineindex++]) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    i = 0;
    if (isalpha(c)) {
        while (isalpha(s[++i] = c = line[lineindex++]))
            ;
        s[i] = '\0';  
        lineindex--;
        return MATHFUNC;
    } else if (isdigit(c)) {
        while (isdigit(s[++i] = c = line[lineindex++]))
            ;
        if (c == '.')
            while (isdigit(s[++i] = c = line[lineindex++]))
                ;
        s[i] = '\0';
        lineindex--;
        return NUMBER; 
    } else if (c == '-') {
        c1 = line[lineindex++];
        lineindex--;
        if (isdigit(c1)) {
            while (isdigit(s[++i] = c = line[lineindex++]))
                ;
            if (c == '.')
                while (isdigit(s[++i] = c = line[lineindex++]))
                    ;
            s[i] = '\0';
            lineindex--;
            return NUMBER;
        } else 
            return c;
    } else if (c == '.') {
        c1 = line[lineindex++];
        lineindex--;
        if (isdigit(c1)) {
            while (isdigit(s[++i] = c = line[lineindex++]))
                ;
            s[i] = '\0';
            lineindex--;
            return NUMBER;
        } else
            return c;
    } else if (c == '=') {
        c1 = line[lineindex++];
        lineindex--;
        if (isalpha(c1)) {
            s[0] = line[lineindex++];
            s[1] = '\0';
            return VARIABLE;
        } else
            return c;
    }
    else 
        return c;
}

/* getline_manual: get line into s, return length */
int getline_manual(char s[], int lim) {
	int c, i;

	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}