#include <stdio.h>


main()
{
    int c, sp;
    sp = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ' && sp < 1)
            ++sp;
        else if (c == ' ' && sp >= 1)
            continue;
        else if (c != ' ')
            sp = 0;
        putchar(c);
    }
}
