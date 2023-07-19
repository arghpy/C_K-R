#include <stdio.h>


main()
{
    int c, sp;
    sp = 0;

    while ((c = getchar()) != EOF) {
        if ((c == ' ' || c == '\t') && sp < 1) {
            ++sp;
            c = '\n';
        }
        else if ((c == ' ' || c == '\t') && sp >= 1)
            continue;
        else if (c != ' ' || c != '\t')
            sp = 0;
        putchar(c);
    }
}
