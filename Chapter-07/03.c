/*
 * Revise minprintf to handle more of the other facilities of printf.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void minprintf(char *, ...);

int main(void) {
    int a = 10; 
    float b = 12.345;
    minprintf("minprintf: %d, %f\n", a, b);
    return EXIT_SUCCESS;    
}

/* minprintf:  minimal printf with variable argument list */
void minprintf(char *fmt, ...)
{
    va_list ap;   /* points to each unnamed arg in turn */
    char *p, *sval;
    int ival;
    double dval;
    
    va_start(ap, fmt); /* make ap point to 1st unnamed arg */
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
            case 'd':
            case 'i':
                ival = va_arg(ap, int);
                printf("%d", ival);
                break;
            case 'o':
                ival = va_arg(ap, int);
                printf("%o", ival);
                break;
            case 'x':
                ival = va_arg(ap, int);
                printf("%x", ival);
                break;
            case 'X':
                ival = va_arg(ap, int);
                printf("%X", ival);
                break;
            case 'u':
                ival = va_arg(ap, int);
                printf("%u", ival);
                break;
            case 'c':
                ival = va_arg(ap, int);
                printf("%c", ival);
                break;
            case 'f':
                dval = va_arg(ap, double);
                printf("%f", dval);
                break;
            case 'e':
                dval = va_arg(ap, double);
                printf("%e", dval);
                break;
            case 'E':
                dval = va_arg(ap, double);
                printf("%E", dval);
                break;
            case 's':
                for (sval = va_arg(ap, char *); *sval; sval++)
                    putchar(*sval);
                break;
            default:
                putchar(*p);
                break;
        }
    }
    va_end(ap);
}