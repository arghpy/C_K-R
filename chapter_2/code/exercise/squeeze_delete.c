#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void squeeze_delete(char s[], char t[])
{
    char *rez;
    int counter = 0;
    for (int i = 0; i < strlen(s); i++) {
        rez = malloc(strlen(t) * sizeof(char) + 1);
        for (int j = 0; j < strlen(t); j++) {
            if (s[i] != t[j]) {
                rez[counter] = t[j];
                counter++;
            }
        }  
        rez[counter] = '\0';
        counter = 0;
        strcpy(t, rez);
        free(rez);
    }
}

int main()
{
    char s[] = "astazi";
    char t[] = "mainie";
    squeeze_delete(s, t);

    printf("%s\n", t);
    return 0;
}
