#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    /* legal escape sequences */
    printf("audible alert (bell) BEL   \\a     %d\n" , '\a');
    printf("backspace            BS    \\b     %d\n" , '\b');
    printf("horizontal tab       HT    \\t     %d\n" , '\t');
    printf("newline              LF    \\n    %d\n"  , '\n');
    printf("vertical tab         VT    \\v    %d\n"  , '\v');
    printf("formfeed             FF    \\f    %d\n"  , '\f');
    printf("carriage return      CR    \\r    %d\n"  , '\r');
    printf("double quote         \"     \\\"    %d\n", '\"');
    printf("single quote         \'     \\\'    %d\n", '\'');
    printf("question mark        ?     \\?    %d\n"  , '\?');
    printf("backslash            \\     \\\\    %d\n", '\\');
    printf("\n");
    printf("forty-two in octal   0%o   \\52   %d\n"  , '\52' , '\52');
    printf("forty-two in hex     0x%X  \\x2A  %d\n"  , '\x2A', '\x2A');
    printf("\n");
    /* illegal escape sequence */
    printf("invalid escape sequence    \\c    %d (%c)\n" , '\c', '\c');
    return EXIT_SUCCESS;
}
