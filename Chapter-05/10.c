/* 
 * Write the program expr, which evaluates a reverse Polish expression
 * from the command line, where each operator or operand is a separate
 * argument. For example, 
 *     expr 2 3 5 + *
 * evaluates 2 x (3+5).
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

void push(double);
double pop(void);

int main(int argc, char *argv[]) {
	double op2;
	char **p;

	while (--argc > 0) {
//		printf("argc = %d\n", argc);
		p = ++argv;
		if (isdigit((*p)[0])) {
			push(atof(*p)); 
		}
		else if ((*p)[0] == '+')
			push(pop() + pop());
		else if ((*p)[0] == 'x')  // there seems to be some problem when using '*'
			push(pop() * pop());  // in terminal, argc crashes. 
		else if ((*p)[0] == '-') {
			op2 = pop();
            push(pop() - op2);
        } else if ((*p)[0] == '/') {
        	op2 = pop();
        	if (op2 != 0.0)
        		push(pop() / op2);
        	else
        		printf("error: zero divisor\n");
        } else if ((*p)[0] == '%') {
        	op2 = pop();
        	if (op2 != 0.0)
        		push(fmod(pop(), op2));
        	else 
        		printf("error: zero divisor\n");
    	} else 
    		printf("unknown command\n");
    }

 	printf("\t%.8g\n", pop());

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