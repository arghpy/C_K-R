#include <stdio.h>
#include <string.h>

#define MAXLINES 5000           /* max #lines to be sorted */
#define MAXLEN 1000             /* max length of any input line */
#define ALLOCSIZE 1000      /* size of available space */

static char allocbuf[ALLOCSIZE];    /* storage for alloc */
static char *allocp = allocbuf;     /* next free position */

char *lineptr[MAXLINES];        /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void myqsort(char *lineptr[], int left, int right);

int mygetline(char *, int);
int mystrcmp(char *s, char *t);
char *alloc(int);

/* sort input lines */
int main()
{
    int nlines;                 /* number of input lines read */

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        myqsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = mygetline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len - 1] = '\0';           /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    int i;

    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

int mygetline(char *s, int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i]  = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

/* myqsort: sort v[left]...v[right] into increasing order */
void myqsort(char *v[], int left, int right)
{
    int i, last;
    void myswap(char *v[], int i, int j);

    if (left >= right)          /* do nothing if array contains */
        return;                 /* fwer than two elements */

    myswap(v, left, (left + right)/2);

    last = left;

    for (i = left + 1; i <= right; i++)
        if (mystrcmp(v[i], v[left]) < 0)
            myswap(v, ++last, i);
    myswap(v, left, last);
    myqsort(v, left, last - 1);
    myqsort(v, last + 1, right);
}

/* myswap: interchange v[i] and v[j] */
void myswap(char *v[], int i, int j)
{
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* mystrcmp: return < 0 if s < t, 0 if s == t, > 0 if s > t */
int mystrcmp(char *s, char *t)
{
    int i;

    for (i = 0; s[i] == t[i]; i++)
        if (s[i] == '\0')
            return 0;

    return s[i] - t[i];
}

char *alloc(int n)      /* return pointer to n characters */
{
    if (allocbuf + ALLOCSIZE - allocp >= n) {   /* it fits */
        allocp += n;
        return allocp - n;  /* old p */
    } else
        return 0;
}

