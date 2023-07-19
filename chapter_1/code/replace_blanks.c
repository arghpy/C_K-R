#include <stdio.h>


main()
{
    int c;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            c = '\\';
            putchar(c);
            c = 'b';
            putchar(c);
        }
        else if (c == '\t') {
            c = '\\';
            putchar(c);
            c = 't';
            putchar(c);
        }
        else if (c == '\\') {
            putchar(c);
            c = '\\';
            putchar(c);
        }
        else
            putchar(c);

    }
}
