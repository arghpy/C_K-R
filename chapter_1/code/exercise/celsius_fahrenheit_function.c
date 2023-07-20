#include <stdio.h>


#define LOWER   0
#define UPPER   300
#define STEP    20

float conversion(int );

main()
{
    for (int fahr = 0; fahr <= UPPER; fahr = fahr + STEP)
        printf("%3d %6.1f\n", fahr, conversion(fahr));

    return 0;
}

float conversion(int temp)
{
    return (5.0 / 9.0) * (temp - 32);
}
