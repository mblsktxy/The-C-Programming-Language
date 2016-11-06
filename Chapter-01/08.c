#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int c, nb, nt, nl;

    nb = nt = nl = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ')
            ++nb;
        else if (c == '\t')
            ++nt;
        else if (c == '\n')
            ++nl;
    }
    printf("Number of blanks: %d\n", nb);
    printf("Number of tabs: %d\n", nt);
    printf("Number of newlines: %d\n", nl);
    
    return EXIT_SUCCESS;
}