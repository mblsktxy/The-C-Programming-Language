/*
 * Add commands to print the top element of the stack without popping,
 * to duplicate it, and to swap the top two elements. Add a command to
 * clear the stack.
 */

#include <stdio.h>
#include <stdlib.h>

void push(double);
double pop(void);
void show_top(void);
void duplicate_top(void);
void swap_top(void);
void clear(void);

int main(void) {
    push(3.4343);
    push(6.54);
    duplicate_top();
    show_top();
    swap_top();
    clear();
    show_top();

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

/* show_top: prints the top element of the stack without popping */
void show_top(void) {
    if (sp > 0)
        printf("top element of stack: %g\n", val[sp-1]);
    else
        printf("error: stack empty\n");
}

/* duplicate: duplicates the top element of the stack */
void duplicate_top(void) {
	if (sp > 0) {
    	double tmp = pop();
    	push(tmp);
    	push(tmp);
    }
    else
    	printf("error: stack emtpy\n");
}

/* swap: swap the two top elements of the stack */
void swap_top(void) {
	if (sp > 1) {
    	double tmp1 = pop();
    	double tmp2 = pop();
    	push(tmp1);
    	push(tmp2);
    }
    else 
    	printf("error: not enough elements in stack\n"); 
}

/* clear: clear the stack */
void clear(void) {
    sp = 0;
}