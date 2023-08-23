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
