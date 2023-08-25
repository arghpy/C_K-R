# Chapter 5: Pointers and Arrays


A pointer is a variable that contains the address of a variable. Pointers are
much used in C, partly because they are sometimes the only way to express a 
computation, and partly because they usually lead to more compact and 
efficient code than can be obtained in other ways. Pointers and arrays are
closely related; this chapter also explores this relationship and shows how
to exploit it.


Pointers have been lumped with the **goto** statement as a marvelous way
to create impossible-to-understand programs. This is certainly true when
they are used carelessly, and it is easy to create pointers that point 
somewhere unexpected. With discipline, however, pointers can also be used
to acheve clarity and simplicity. This is the aspect that we will try to
illustrate.


The main change in ANSI C is to make explicit the rules about how pointers
can be manipulated, in effect mandating what good programmers already practice
and good compilers already enforce. In addition, the type **void \*** (pointer
to void) replaces **char *** as the proper type for a generic pointer.
and good compilers already enforce. In addition, the type **void *** (pointer
to void) replaces **char \*** as the proper type for a generic pointer.


## 5.1 Pointers and Addresses


A typical machine has an array of consecutivelly numbered or addresses 
memory cells that may be manipulated individually or in contigous groups.
One common situation is that any byte can be a char, a pair of one-byte cells
can be treated as a short integer, and four adjacent bytes form a long. A 
pointer is a group of cells (often two or four) that can hold an address.


The unary operator `&` gives the address of an object, so the statement 
`p = &c;` assigns the address of c to the variable p, and p is said to 
"point" to c. The & operator only applies to objects in memeory: variables and
array elements. It cannot be applied to expressions, constants, or register
variables.


The unary operator `*` is the *indirection* or *dereferencing* operator; when
applied to a pointer, it accesses the object the pointer points to. Suppose
that x and y are integers and ip is a pointer to int. This artificial 
sequence shows how to declare a pointer and how to use & and *:


```
int x = 1, y = 2, z[10];
int *ip;        // ip is a pointer to int

ip = &x;        // ip now points to x
y = *ip;        // y is now 1
*ip = 0;        // x is now 0
ip = &z[0];     // ip now points to z[0]
```


The declarations of x, y and z are what we've seen all along. The declaration
of the pointer ip, `int *ip;` is intended as a mnemonic; it says that the 
expression `*ip` is an *int*. The syntax of the declaration for a variable 
mimics the syntax of expressions in which the variable might appear. This 
reasoning applies to function declarations as well. For example, 
`double *dp, atof(char *);` says that in an expression *dp and atof(s) have
values of type double, and that the argument of atof is a pointer to char.


You should also note the implication that a pointer is constrained to point
to a particular kind of object: every pointer point to a specific data type.
(Therer is one exception: a "pointer to void" is used to hold any type of
pointer byt cannot be dereferenced itself.)


If ip points to the integer x, then *ip can occur in any context where x
coudls, so `*ip = *ip + 10;` increments *ip by 10.


The unary operators * and & bind more tightly than arithmetic operators, so
the assignment `y = *ip + 1;` takes whatever ip points at, adds 1, and 
assigns the result to y, while `*ip += 1` increments what ip points to, as do
`++*ip` and `(*ip)++`.


The parantheses are necessary in this last example; without them, the
expression would increment ip insteaad of what it points to, because unary
operators like * and ++ associate right to left.


finally, since pointers are variables, they can be used without dereferencing.
For example, if **iq** is another pointer to int, `iq = ip` copies the 
contents of ip into iq, thus making iq point to whatever ip pointed to.


## 5.2 Pointers and Function Arguments


Since C passes arguments to functions by value, there is no direct way for
the called function to alter a variable in the calling function. For instance,
a sorting routine might exchange two out-of-order elements with a function
called **swap**. It is not enough to write `swap(a, b);` where the **swap**
function is defined as:


```
void swap(int x, int y)
{
    int temp;

    temp = x;
    x = y;
    y = temp;
}
```

Because of call by value, **swap** can't effect the arguments a and b in the
routine that called it. The function above **only swaps copies** of a and b.


The way to obtain the desired effect is for the calling program to pass 
`pointers` to the values to be changed: `swap(&a, &b);`.


Since the operator `&` produces the address of a variable, `&a` is a pointer
to a. In swap itself, the parameters are declared to be pointers, and the 
operands are accessed indifrectly through them.


```
void swap(int *px, int *py)
{
    int temp;

    temp = *px;
    *px = *py;
    *py = temp;
}
```


Pointer arguments enable a function to access and change objects in the 
function that called it. As an example, consider a function `getint` that
performs free-format input conversion by breaking a stream of characters
into integer values, one integer per call. `getint` has to return  the value
it found and also signal end of file when there is no more input. These values
have to be passed back by separate paths, for no matter what value is used
for EOF, that could also be the value of an input integer.


One solution is to have `getint` return end of file status as its function
value, while using pointer argument to store the converted integer back in 
the calling function. This is the scheme used by `scanf` as well.


The following loop fills an array with integers by calls to `getint`:

```
int n, array[SIZE], getint(int *);

for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
    ;
```

Each call sets `array[n]` to the next integer found in the input and 
increments `n`. Notice that it is essential to pass the address of `array[n]`
to `getint`. Otherwise there is no way for `getint` to communicate the
converted integer back to the caller.


Our version of `getint` return EOF for end of file, zero if the next input
is not a number, and a positive value if the input contains a valid number.


**Program:**[ getint](code/getint.c)


Throughout `getint`, `*pn` is used as an ordinary `int` variable. We have also
used `getch` and `ungetch` so the one extra character that must be read
can be pushed back onto the input.


## 5.4 Pointers and Arrays


In C, there is a strong relationship between pointers and arrays, strong
enough that pointers and arrays should be discussed simultaneously. Any 
operation that can be achieved by array subscripting can also be done with
pointers. The pointer version will in general be faster but, at least to the
uninitiated, somewhat harder to understand.


The declaration `int a[10];` defines an array a of size 10, that is, a block
of 10 consectutive objects named a[0], a[1], ...., a[9].


The notation a[i] refers to the i-th element of the array. If `pa` is a 
pointer to an integer, declared as `int *pa;` then the assignment 
`pa = &a[0];` sets `pa` to point to element zero of a; that is, pa contains
the address of a[0].


Now the assignment `x = *pa;` will copy the contests of a[0] into x.


If `pa` points to a particular element of an array, then by definition 
`pa + 1` points to the next element, `pa + i` points i elements after `pa`,
and `pa - i` points to i elements before. Thus, if `pa` points to a[0], 
`*(pa + 1)` refers to the contents of a[1], pa + i is the address of a[i], 
and *(pa + i) is the contents of a[i].


These remarks are true regardless of the type or size of the variables in the
array a. The meaning of "adding 1 to a pointer" and by extension, all pointer
arithmetic, is that `pa + 1` points to the next object, and `pa + i` points
to the i-th object beyond `pa`.


The correspondence between indexing and pointer arithmetic is very close. By
definition, the value of a variable or expression of type array is the address
of element zero of the array. Thus after the assignment `pa = &a[0]`, `pa` and
`a` have identical values. Since the name of an array is a synonym for the
location of the initial element, the assignment `pa = &a[0]` can also be
written as `pa = a;`.


Rather more surprising, at least at first sight, is the fact that a reference
to `a[i]` can also be written as `*(a + i)`. In evaluating `a[i]`, C converts
it to `*(a + i)` immediately; the two forms are equivalent. Applying the
operator `&` to both parts of this equivalence, it follows that `&a[i]` and
`a + i` are also identical: `a + i` is the address of the `i-th` element 
beyond `a`. As the other side of this coin, if `pa` is a pointer, expressions
may use it with a subscript; `pa[i]` is identical to `*(pa + i)`. In short, 
an array and index expression is equivalent to one written as a pointer
and offset.


There is one difference between an array name and a pointer that must be
kept in mind. A pointer is a variable, so `pa = a` and `pa++` are legal.
But an array name is not a variable; contructions like `a = pa` and `a++`
are illegal.


When an array name is passed to a function, what is passed is the location
of the initial element. Within the called function, this argument is a 
local variable, and so an array name parameter is a pointer, that is, a 
variable containing an address. We can use this fact to write another version
of strlen, which computes the length of a string.


```
/* strlen: return length of a string s */
int strlen(char *s)
{
    int n;

    for (n = 0; *s != '\0'; s++)
        n++;

    return n;
}
```


Since `s` is a pointer, incrementing it is perfectly legal; `s++` has no 
effect on the character string in the function that called `strlen`, but 
merely increments `strlen`'s private copy of the pointer. That means that
calls like:

```
strlen("hello, world");     // string constatn
strlen(array);              // char array[100]
strlen(ptr);                // char *ptr
```

all work.


As formal parameters in a function definition, `char s[]` and `char *s` are
equivalent; we prefer the latter because it says more explicitly that the
parameter is a pointer. When an array name is passed to a function, the 
function can at its convenience believe that it has been handed either an 
array or a pointer, and manipulate it accordingly. It can even use both
notations if it seems appropiate and clear.


It is possible to pass part of an array to a function, by passing a pointer
to the beginning of the subarray. For example. if `a` is an array, `f(&a[2])`
and `f(a + 2)` both pass to the function `f` the address of the subarray
that start at `a[2]`. Within `f`, the parameter declaration can read
`f(int arr[]) {...}` or `f(int *arr) {...}`. So as far as `f` is concerned, 
the fact that the parameter refers to part of a larger array is of no
consequence.


If one is sure that the elements exist, it is also possible to index backwards
in an array; `p[-1], p[-2]` and so on are syntactically legal, and refer to
the elements that immediately precede `p[0]`. Of course, it is illegal to
refer to objects that are not within the array bounds.


## 5.4 Address Arithmetic


If `p` is a pointer to some element of an array, then `p++` increments `p`
to point to the next element, and `p += i` increments it to point `i` 
elements beyond where it currently does. These and similar constructions 
are the simplest forms of pointer or address arithmetic.


C is consistent and regular in its appraoch to address arithmetic; its 
integration of pointers, arrays, and address arithmetic is one of the 
strengths of the language. Let us illustrate by writing a rudimentray 
storage allocator. There are two routines. The first, `alloc(n)`, returns
a pointer `p` to `n`-consecutive character positions, which can be used
by the caller of `alloc` for storing characters. The second, `afree(p)`
, releases the storage thys acquired so it can be re-used later. The
routines are "rudimentary" because the calls to `afree` must be made in the
opposite order to the calls made on `alloc`. That is, the storage
managed by `alloc` and `afree` is a stack, or last-in, first-out list. The
standard library provides analogous functions called `malloc` and `free` that
have no such restrictions; in Section 8.7 we will show how they can be 
implemented.


The easiest implementation is to have `alloc` hand out pieces of a large
character array that we will call `allocbuf`. This array is private to
`alloc` and `afree`. Since they deal in pointers, not array indices, no other
routine need know the name of the array, which can be decalred `static` in 
the source file containing `alloc` and `afree`, and thus be invisible outside
it. In practical implementations, the array may well not even have a name;
it might instead be obtained by calling `malloc` or by asking the operating
system for a pointer to some unnamed block of storage.


The other informatino needed is how much of `allocbuf` has been used. We use
a pointer, called `allocp`, that points to the next free element. When `alloc`
is asked for `n` characters, it checks to see if there is enough room left in
`allocbuf`. If so, `alloc` returns the current value of `allocp` (i.e., the
beginning of the free block), then increments it by `n` to point to the next
free area. If there is no room, `alloc` returns zero. `afree(p)` merely sets
`allocp` to `p` if `p` is inside `allocbuf`.


```
#define ALLOCSIZE 1000      /* size of available space */

static char allocbuf[ALLOCSIZE];    /* storage for alloc */
static char *allocp = allocbuf;     /* next free position */

char *alloc(int n)      /* return pointer to n characters */
{
    if (allocbuf + ALLOCSIZE - allocp >= n) {   /* it fits */
        allocp += n;
        return allocp - n;  /* old p */
    } else
        return 0;
}

void afree(char *p)         /* free storage pointed to by p */
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}
```


In general a pointer can be initialized just as any other variable can, though
normally the only meaningful values are zero or an expression involving the 
addresses of previously defined data of appropriate type. The declaration
`static char *allocp = allocbuf;` defines `allocp` to be a character pointer
and initializes it to point to the beginning of `allocbuf`, which is the 
next free position when the program starts. This could have also been written
as `static char *allocp = &allocbuf[0];` since the array name *is* the 
address of the zeroth element. The test `if (allocbuf + ALLOCSIZE - allocp
>= n) { /* it fits */ }` checks if there's enough room to satisfy a request
for n characters. If there is, the new value of `allocp` would be at most one
beyond the end of `allocbuf`. If the request can be satisfied, `alloc` returns
a pointer to the beginning of a vlock of characters (notice the declaration
of the function itself). If not, `alloc` must return some signal that no
space is left. C guarantees that zero is never a valid address for data, so
a return value of zero can be used to signal an abnormal event, in this case,
no space.


Pointers and integers are not interchangeable. Zero is the sole exception: the
constant zero may be assigned to a pointer, and a pointer may be compared
with the constant zero. The symbolic constant `NULL` is often used in place
of zero, as a mnemonic to indicate more clearly that this is a special value
for a pointer. `NULL` is defined in `<stdio.h>`. We will use `NULL` 
henceforth.


Pointers may be compared under certain circumstances. If `p` and `q` point to
members of the same array, then relations like `==, !=, <, >=` etc, work 
properly. For example, `p < q` is true if `p` points to an earlier member of
the array than `q` does. Any pointer can be meaningfully compared for 
equality or inequality with zero. But the behavior is undefined for arithmetic
or comparisions with pointers that do not point to members of the same array.
(There is one exception: the address of the first element past the end of
an array can be used in pointer arithmetic.)


Second, we have already observed that a pointer and an integer may be added
or subtracted. The construction `p + n` means the address of the n-th object
beyond the one p currently points to. this is tru regardless of the kind
of object p points to; n is scaled according to the size of the objects p
points to, which is determined by the declaration of p. If an `int` is four
bytes, for example. the `int` will be scaled by four.


Pointer substraction is also valid: if `p` and `q` point to elements of the
same array, and `p < q`, then `q - p + 1` is the number of elements from
`p` to `q` inclusive. This fact can be used to write yet another version of
`strlen`:

```
/* strlen: return length of string s */
int strlen(char *s)
{
    char *p = s;

    while (*p != '0')
        p++;
    
    return p - s;
}
```


In its declaration, `p` is initialized to `s`, that is, to point to the first
character of the string. In the `while` loop, each character in turn is
examined until the `'\0'` at the end is seen. Because `p` points to 
characters, `p++` advances `p` to the next character each time, and `p - s`
gives the number of characters advanced over, that is, the string length.
(The number of characters in the string could be too large to store in an 
int. The header `<stddef.h>` defines a type `ptrdiff_t` that is large enough
to hold the signed difference of two pointer values. If we were being very
cautious, however, we would use `size_t` for the return type of strlen, to
match the standard library version. `size_t` is the unsigned integer type
returned by the `sizeof` operator).


Pointer arithmetic is consistent: if we had been dealing with floats, which
occupy more storage than chars, and if p were a pointer to floart, p++ would
advance to the next float. Thus we could write another version of alloc
that maintains floats instead of chars, merely by changing char to float
throughout alloc and afree. All the pointer manipulations automatically
take into account the size of the object pointed to.


The valid pointer operations are assignment of pointers of the same type,
adding or subtracting a pointer and an integer, subtracting or comparing two
pointers to memebers of the same array, and assigning or comparing to zero.
All other pointer arithmetic is illegal. It is not legal to add two pointers,
or to multiply or divide or shift or mask the, or to add float or double to
them, or even, except for `void *`, to assign a pointer of one type to a 
pointer of another type without a cast.


## 5.5 Character Pointers and Functions


A **string constant**, written as "I am a string" is an array of characters. 
In the internal representation, the array is terminated with the null 
character '\0' so that programs can find the end. The length in storage
is thus one more than the number of characters between the double quotes.


Perhaps the most common occurence of string constants is as arguments to
functions, as in `printf("hello, world\n")`. When a character string like
this appears in a program, access to it is through a character pointer;
`printf` receives a pointer to the beginning of the character array. That is,
a string constant is accessed by a a pointer to its first element.


String constants need not be function arguments. If `pmessage` is delcared
as `char *pmessage;` then the statement `pmessage = "now is the time";` 
assigns to `pmessage` a pointer to the character array. This is **not** a
string copy; only pointers are involved. C does not provide any operators 
for processing an entire string of characters as a unit.


There is an important difference between these definitions:

```
char amessage[] = "now is the time";    // an array
char *pmessage = "now is the time";     // a pointer
```

`amessage` is an array, just big enough to hold the sequence of characters 
and '\0' that initializes it. Individual characters within the array may
be changed but `amessage` will always refer to the same storage. On the other
hand, `pmessage` is a pointer, initialized to point to a string constant; the
pointer may subsequently be modified to point elsewhere, but the result is 
undefined if you try to modify the string contents.


We will illustrate more asepects of pointers and arrays by studying versions
of two useful functions adapted from the standard library. The first function
is `strcpy(s, t)`, which copies the string `t` to the string `s`. It would
be nice just to say `s = t` but this copies the pointer, not the characters.
To copy the characters, we need a loop. The array version is first:

```
/* strcpy: copy t to s; array subscript version */
void strcpy(char *s, char *t)
{
    int i;

    i = 0;

    while ((s[i] = t[i]) != '\0')
        i++;
}
```

For contrast, here is a version of `strcpy` with pointers:

```
/* strcpy: copy t to s; pointer version 1 */
void strcpy(char *s, char *t)
{
    while ((*s = *t) != '\0') {
        s++;
        t++;
    }
}
```

Because arguments are passed by value, `strcpy` can use the parameters `s`
and `t` in any way it pleases. Here they are conveniently initialized 
pointers, which are marched along the arrays a character at a time, until
the '\0' that teminates `t` has been copied to `s`.


In practice, `strcpy` would not be written as we showed it above. Experienced
C programmers would prefer:

```
/* strcpy: copy t to s; pointer version 2 */
void strcpy(char *s, char *t)
{
    while ((*s++ = *t++) != '\0')
        ;
}
```

This moves the increment of `s` and `t` into the test part of the loop. The
value of `*t++` is the character that t pointed before `t` was incremented;
the postfix `++` doesn't change `t` until after this character has been 
fetched. In the same way, the character is stored into the old `s` position
before `s` is incremented. This character is also the value that is compared
against '\0' to control the loop. The net effect is that characters are 
copied from `t` to `s`, up to and including the terminating '\0'.


As the final abbreviation, observe  that a comparison against '\0' is 
redundant, since the question is merely whether the expression is zero. So
the function would likely be written as:

```
/* strcpy: copy t to s; pointer version 3 */
void strcpy(char *s, char *t)
{
    while (*s++ = *t++)
        ;
}
```

Although this may seem cryptic at first sight, the notational convenience is
considerable, and the idiom should be mastered, because you will see it
frequently in C programs.


The `strcpy` in the standard library (<string.h>) returns the target string
as its function value.


The second routine that we will examine is `strcmp(s, t)`, which compares
the characteer strings `s` and `t`, and returns negative, zero or positive
if `s` is lixicographically less than, equal to, or greater that `t`. The
value is obtained by subtracting the characters at the first position where
`s` and `t` disagree.


```
/* strcmp: return < 0 if s < t, 0 if s == t, > 0 if s > t */
int strcmp(char *s, char *t)
{
    int i;

    for (i = 0; s[i] == t[i]; i++)
        if (s[i] == '\0')
            return 0;

    return s[i] - t[i];
}
```

The pointer version of `strcmp`:


```
/* strcmp: return < 0 if s < t, 0 if s == t, > 0 if s > t */
int strcmp(char *s, char *t)
{
    for ( ; *s == *t; s++, t++)
        if (*s == '\0')
            return 0;

    return *s - *t;
}
```


Since `++` and `--` are either prefix or postfix operators, other combinations
of * and ++ and -- occur, although less frequently. For example, `*--p` 
decrements `p` before fetching the character that `p` points to. In fact, 
the pair of expression:

```
*p++ = val;     // push val onto stack
val = *--p;     // pop top of stack into val
```

are the standard idioms for pushing and popping a stack.


The header `<string.h>` contains declarations for the functions mentioned
in this section, plus a variety of other string-handling functions from
the standard library.


## 5.6 Pointer Arrays; Pointers to Pointers


Since pointers are variables themselves, they can be stored in arrays just
as other variables can. Let us illustrate by writing a program that will sort
a set of text lines into alphabetic order, a stripped-down version of the
UNIX program `sort`.


In Chapter 3, we presented a Shell sort function that would sort an array
of integers, and in Chapter 4 we improves on it with a quicksort. The same
algorithms will work, except that now we have to deal with lines of text, 
which are of different lengths, and which, unlike integers, can't be compared
or moved in a single operation. We need a data representation that will cope
efficiently and conveniently with variable-length text lines.


This is where the array of pointers enters. If the lines to be sorted are
stored end-to-end in one long character array, then each line can be accessed
by a pointer to its first character. The pointers themselves can be stored in
an array. Two lines can be compared by passing their pointers to `strcmp`.
When two out-of-order lines have to be exchanged, the pointers in the pointer
array are exchanged, not the text lines themsleves.


This eliminates the twin problems of complicated storage management and
high overhead that would go with moving the lines themselves.


The sorting process has three steps:

```
read all the lines of input
sort them
print them in order
```

As usual, it's best to divide the program into functions that match this
natural division, with the main routine controlling the other functions. Let
us defer the sorting step for a moment, and concentrate on the data structure
and the input and output.


The input routine has to collect and save the characters of each line, and
build an array of pointers to the lines. It will also have to count the
number of input lines, since that information is needed for sorting and 
printing. Since the input function can only cope with a finite number of
input lines, it can return some illegal line count like -1 if too much input
is presented.


The output routine only has to print the lines in order in which they appear
in the array of pointers.


**Program:**[ sort](code/sort.c)


The main new thing is the declaration for `lineptr`: `char *lineptr[MAXLINES]`
says that `lineptr` is an array of MAXLINES elements, each element of which
is a pointer to a char. That is, `lineptr[i]` is a character pointer, and
`*lineptr[i]` is the character it points to, the first character of the i-th
saved text line.


Since `lineptr` is itself the name of an array, it can be treated as a pointer
in the same manner as in our earlier examples, and `writelines` can be written
instead as:

```
/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}
```


Initially `*lineptr` points to the first line; each increment advances it to
the next line pointer while `nlines` is counted down.


With input and output under control, we can proceed to sorting. The quicksort
from Chapter 4 need minor changes: the declarations have to be modified, and
the comparison operation must be done by calling `strcmp`. The algorithm
remains the same, which gives us some confidence that it will still work.
Similarly, the swap routine need only trivial changes.


Since and individual element of `v` (alias `lineptr`) is a character pointer,
`temp` must be also, so one can be copied to the other.


## 5.7 Multi-dimensional Arrays


C provides rectangular multi-dimensional arrays, although in practice they are much less
used than arrays of pointers. In this section, we will show some of their properties.


Consider the problem of date conversion, from day of the month to day of the year and
vice versa. For example, March 1 is the 60th day of a non-leap year, and the 61st day
of a leap year. Let us define two functions to do the conversions: `day_of_year`
converts the month and day into the day of the year, and `month_day` converts the day
of the year into the month and day. Since this latter function computes two values,
the month and day arguments will be pointers `month_day(1988, 60, &m, &d)` sets m to 2
and d to 29 (February 29th).


These functions both need the same information, a table of the nubmer of days in each
month ("thirty days hath September ..."). Since the number of days per month differs
for leap years and non-leap years, it's easier to separate them into two rows of a 
two-dimensional array than to keep track of what happens to February during computation.
The array and the functions for performing the transformations are as follows:

```
static char daytab[2][13] = {
    {0 , 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0 , 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int i, leap;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    for (i = 1; i < month; i++)
        day += daytab[leap][i];

    return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    
    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];

    *pmonth = i;
    *pday = yearday;
}
```

Recall that the arithmetic value of a logical expression, such as the one for `leap`
is either zero (false) or one (true), so it can be used as a subscript of the array
`daytab`.


The array `daytab` has to be external to both `day_of_year` and `month_day`, so they can
both use it. We made it `char` to illustrate a legitimate use of `char` for storing 
small non-character integers.


`daytab` is the first two-dimensional array we have dealth with. In C, a two-dimensional
array is really a one-dimensional array, each of whose elements is an array. Hence 
subscripts are written as `daytab[i][j]     // [row][col]`. Other than this notational
distinction, a two-dimensional array can be treated in much the same way as in other
languagtes. Elements are stored by rows, so the rightmost subscript, or column, varies
fastest as elements are accessed in storage order.


An array is initialized in braces; each row of a two-dimensional array is initialized
by a corresponding sub-list. We started the array `daytab` with a column of zero so that
month numbers can run from the natural 1 to 12, instead of 0 to 11. Since space is not
at a premium here, this is clared than adjusting the indices.


If a two-dimensional array is to be passed to a function, the parameter declaration
in the function must include the number of columns; the number of rows is irrelevant
, since what is passed is, as before, a pointer to an array of rows, where each row is
an array of 13 ints. In this particular case, it is a pointer to  objects that are
arrays of 13 ints. Thus, if the array `daytab` is to be passed to a function f, the
declaration of f would be `f(int daytab[2][3]) {...}`, it could also be 
`f(int daytab[][3]) {...}` since the number of rows is irrelevant, or it could be
`f(int (*daytab)[3]) {...}` which says that the parameter is a pointer to an array of
3 integers. The parantheses are necessary since brackets [] have higher precedence than
*. Without parantheses, the declaration `int *daytab[3]` is an array of 3 pointers to
integers. More generally, only the first dimension (subscript) of an array is free; 
all the others have to be specified.


## 5.8 Initialization of Pointer Arrays


Consider the problem of writing a function `month_name(n)`, which returns a pointer
to a character string containing the name of the n-th month. This is an ideal 
application for an internal `static` array. `month_name` contains a private array
of character strings, and returns a pointer to the proper one when called. This section 
shows how that array of names is initialized. The syntax is similar to previous 
initializations:

```
/* month_name: return name of the n-th month */
char *month_name(int n)
{
    static char *name[] = {
        "Illegal month",
        "January", "February", "March",
        "April", "May", "June",
        "July", "August", "September",
        "October", "November", "December"
    };

    return (n < 1 || n > 12) ? name[0] : name[n];
}
```


The declaration of `name`, which is an array of chracter pointers, is the same as
`lineptr` in the sorting example. The initializer is a list of character strings; each
is assigned to the corresponding position in the array. The characters of the i-th
string are placed somewhere, and a pointer to htem is stored in `name[i]`. Since the
size of the array `name` is not specified, the compiler counts the initializers and 
fills in the correct number.


## 5.9 Pointers vs Multi-dimensional Arrays


Newcomers to C are sometimes confused about the difference between a two-dimensional 
array and an array of pointers, such as `name` in the example above. Given the 
definitions:

```
int a[10][20];
int *b[10];
```

then `a[3][4]` and `b[3][4]` are both syntactically legal references to a single int. 
But `a` is a true two-dimensional array: 200 `int`-sized locations have been set
asife, and the conventional rectangular subscript calculation `20 x row + col` is
used to find the element `a[row][col]`. For `b`, however, the defintion only allocates
10 pointers and does not initialize them; initialization must be done explicitly, either
statically or with code. Assuming that each element of `b` does point to a 
twenty-element array, then there will be 200 ints set aside, plus then cells for the 
pointers. The important advantage of the pointer array is that the rows of the array
may be of different lengths. That is, each element of `b` need not point to a 
twenty-element vector; some may point to two elements, some to fifty, and some to none
at all.


Although we have phrased this discussion in terms of integers, by far the most frequent
use of arrays of pointers is to store character strings of diverse lengths, as in the
function `month_name`. Compare the declaration and picture for an array of pointers:

```
char *name[] = {"illegal month", "Jan", "Feb", "Mar"};
```

with those for a two-dimensional array:

```
char aname[][15] = {"illegal month", "Jan", "Feb", "Mar"};
```


## 5.10 Command-line Arguments


In environments that support C, there is a way to pass command-line arguments or 
parameters to a program when it begins executing. When `main` is called, it is called
with two arguments. The first (conventionally called `argc`, for argument count) is 
the number of command-line arguments the program was invoked with; the second (`argv`,
for argument vector) is a pointer to an array of character string that contain the 
arguments, one per string. We customarily use multiple levels of pointers to manipulate
these character strings.


The simplest illustratino is the program `echo`, which  echoes its command-line 
arguments on a single line, separated by blanks. That is, the command 
`echo hello, world` prints the output `hello, world`.


By convention, `argv[0]` is the name by which the program was invoked, so `argc` is at
least 1. If `argc` is 1, there are no command-line arguments after the program name.
In the example above, `argc` is 3, and `argv[0]`, `argv[1]` and `argv[2]` are "echo", 
"hello," and "world" respectively. The first optional argument is `argv[1]` and the last
is `argv[arcg - 1]`; additionally, the standard requires that `argv[argc]` be a null
pointer.


The first version of `echo` treats `argv` as an array of character pointers:

```
#include <stdio.h>

/* echo command-line arguments; 1st version */
int main(int argc, char *argv[])
{
    int i;

    for (i = 1; i < argc; i++)
        printf("%s%s", argv[i], (i < argc - 1) ? " " : "");
    
    printf("\n");

    return 0;
}
```


Since `argv` is a pointer to an array of pointers, we can manipulate the pointer rather
than index the array. This next variation is based on incrementing `argv`, which is
a pointer to pointer to `char`, while `argc` is counted down:


```
#include <stdio.h>

/* echo command-line arguments; 2nd version */
int main(int argc, char *argv[])
{
    while (--argc > 0)
        printf("%s%s", *++argv, (argc > 1) ? " " : "");
    
    printf("\n");

    return 0;
}
```


Since `argv` is a pointer to the beginning of the array of argument strings, 
incrementing it by 1 (`++argv`) makes it point at the original `argv[1]` instead of
`argv[0]`. Each successive increment moves it along to the next argument; `*argv` is
then the pointer to that argument. At the same time, `argc` is decremented; when it 
becomes zero, there are no arguments left to print.


Alternatively, we could write the `printf` statement as `printf((argc > 1) ? "%s " : 
"%s", *++argv);`


This shows that the format argument of `printf` can be an expression too.


As a second example, let us make some enhancements to the pattern-finding program from
Section 4.1. If you recall, we wired the search pattern deep into the program, an 
obviously unsatisfactory arrangement. Following the lead of the UNIX program `grep`
let us change the program so the pattern to be matched is specified by the first 
argument on the commmand line.


```
#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int getline(char *line, int max);

/* find: print lines that match pattern from 1st arg */
int main(int argc, char *argv[])
{
    char line[MAXLINE];
    int found = 0;

    if (argc != 2)
        printf("Usage: find pattern\n");
    else
        while (getline(line, MAXLINE) > 0)
            if (strstr(line, argv[1]) != NULL) {
                printf("%s", line);
                found++;
            }
    return found;
}
```


The standard library function `strstr(s, t)` return a pointer to the first occurence
of the string t in the string s, or NULL if there is none. It is declared in 
`<string.h>`.


The model can now be elaborated to illustrate further pointer constructions. Suppose
we want to allow two optional arguments. One says "print all lines *except* those that
match the pattern;" the second says "preceed each printed line by its line number."


A common convention for C programs on UNIX systems is that an argument that begins 
with a minus sign introduces an optional flag or parameter. If we choose `-x` (for 
except) to signal the inversion, and `-n` ("number") to request line numbering, then
the command `find -x -n pattern` will print each line that doesn't match the pattern,
preceede by its line number.


Optional arguments should be permitted in any order, and the rest of the program should
be independent of the number of the arguments that were present. Futhermore, it is 
convenient for users if option arguments can be combined, as in `find -nx pattern`.


**Program:**[ optional arguments](code/optional_args.c)


`argc` is decremented and `argv` is incremented before each optional argument. At the
end of the loop, if there are no errors, `argc` tells how many arguments remain
unprocessed and `argv` points to the first of these. Thus `argc` should be 1 and 
`*argv` should point at the pattern. Notice that `*++argv` is a pointer to an argument
string, so `(*++argv)[0]` is its first character. (An alternate valid form would be
**++argv). Because [] binds tighter than * and ++, the parantheses are necessary;
without them the expression would be taken as `*++(argv[0])`. In fact, that is what
we used in the inner loop, where the task is to walk along a specific argument string.
In the inner loop, the expression `*++argv[0]` increments the pointer `argv[0]`!


It is rare that one uses pointer expressions more complicated than these; in such cases
, breaking them into two or three steps will be more intuitive.
