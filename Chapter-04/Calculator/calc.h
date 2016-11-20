#define NUMBER '0'   /* signal that a number was found */
#define MATHFUNC '1' /* signal that a math function was found */
#define VARIABLE '2' /* signal that a variable was found */

void push(double);
double pop(void);
int getop(char []);
int getch(void);
void ungetch(int);