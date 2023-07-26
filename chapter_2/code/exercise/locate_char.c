#include <stdio.h>
#include <string.h>

int any(char s1[], char s2[])
{
    for (int i = 0; i < strlen(s2); i++) {
        for (int j = 0; j < strlen(s1); j++) {
            if (s2[i] == s1[j]) {
                printf("%c at %d\n", s1[j], j);
                return j;
            }
        }  
    }
    return -1;
}

int main()
{
    char s[] = "stazi";
    char t[] = "maine";

    any(s, t);
    printf("%s\n", strpbrk(s, t));
    return 0;
}
