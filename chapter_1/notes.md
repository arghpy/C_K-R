# Chapter 1: A Tutorial Introduction


The purpose of this tutorial is to show-case the language in order to get
the user started. It does not represent in any way or form a standard in
which the programs are expected to be written. Only the basis are presented
such as: variables and constants, arithmetic, control flow, functions, and
the rudiments of input and output.


Some of C's key features won't be convered in this chapter. That includes and
is not limited to: pointers, structures, most of C's rich set of operators,
several control-flow statements and standard library.


## 1.1 Getting Started


As always, the first program would be a 'Hello World!'.

**Program**: [Hello World!](code/hello_world.c)


Every C program must end in ".c". To compile it, use the command
`cc hello_world.c`. This will produce a compiled file named **a.out**.

Another rule is that every C program must have a **main** function. This
is the place where the program start executing.

The first line of the program (**#include <stdio.h>**) tells the compiler
to include information from this library. In this case, the standar 
input/output library.

In our example, we called the function `printf` from standard library
and by passing the argument "Hello, World!\\n" we managed to print it to 
standard output.

The character '\\n' represents a single character. An **escape sequence** like
'\\n' provides a general and extensible mechanism for representing
hard-to-type or invisible characters. Among the otehrs that C provides
are '\\t' for tab, '\\b' for backspace, '\\"' for the double quote, and '\\\'
for the backslash itself.


## 1.2 Variables and Arithmetic Expressions

The next program uses the formula `C = (5/9)(F -  32)` to print
the following table of Fahrenheit temperatures and their centigrade
or Celsius equivalents:


**Program**: [Fahrenheit-Celsius](code/celsius-fahrenheit.c)

The sizes of C data types are machine independent as they depend directly
on the CPU.

**NOTE**: if a control flow structure contains a single statement, it can
also be written as:

```
while (i < j)
    i = 2 * j;
```

The recommandation is to write one statement per line, and use blanks around
operators for grouping.

The program has several problems:

1. The temperature is not very accurate because by divind two integers, the
output is truncated
2. The alignment is not correct, as the numbers are all over the place

Here is the second version of the program:


**Program**: [Fahrenheit-Celsius: version 2](code/celsius-fahrenheit2.c)

We were unable to use 5/9 in the previous version because integer division
would truncate it to zero. A decimal point in a constant indicates that
it is floating point, however, so 5.0/9.0 is ont truncated because it is
the ratio of two floating-point values.

Even though conversion are made automatically if one of the numbers is a 
float number, it is easier to read when applying a decimal point.

The printf conversion specification **%3.0f** says that a floating-point
number is to be printed at least three characters wide, with no decimal
point and no fraction digits. **%6.1f** describes another number that
is to be printed at least six characters wide, with 1 digit after
the decimal point.

Width and precision may be omitted from a specification: **%6f** says that 
the number is to be at least six characters wide; **%.2f** specifies two 
characters after the decimal point, but the width is not constrained; and
**%f** merely says to print the number as a floating point.

Notes:

- %d        : print as decimal integer
- %6d       : print as decimal integer, at least 6 characters wide
- %f        : print as floating point
- %6f       : print as floating point, at least 6 characters wide
- %.2f      : print as floating point, 2 characters after decimal point 
- %6.2f     : print as floating point, at least 6 wide and 2 after decimal point

Among others, `printf` also recognizes %o for octal, %x for hexadecimal,
%c for character, %s for character string, and %% for % itself.


## 1.3 The For Statement

There are plenty of different ways of writting a program. For example,
the temperature program. This is almost a one liner:


**Program**: [Fahrenheit-Celsius: Version 3 - For loop](code/celsius-fahrenheit3.c)


## 1.5 Symbolic Constants


It's bad practice to bury "magic numbers" like 300 and 20 in a program;
they convey little information to someone who might have to read the 
program later, and they are hard to change in a systematic way. One way
to deal with magic numbers is to five them meaningful names. A `**#define**`
line defines a symbolic name or **symbolic constant** to be a particular
string of characters:

```
#define     name    replacement text 
```

Thereafter, any occurrence of name (not in quotes and not part of another
name) will be replaced by the corresponding **replacement text**. The **name**
has the same form as a variable name: a sequence of letters and digits that
begins with a letter. The **replacement text** can be any sequence of
characters; it is not limited to numbers.


**Program**: [Fahrenheit-Celsius: Version 4 - SYMBOLIC CONSTANTS](code/celsius-fahrenheit_define.c)


The quantites LOWER, UPPER and STEP are symbolic constants, not variables, so they do not appear in declarations. Symbolic constant names are conventionally
written in upper case so they can be readily distinguished from lower case
variable name. Notice that there is no semicolon at the end of a **#define**
line.


## 1.5 Character Input and Output


The Standard Library provides several functions for reading or 
writing one characyer at a time, of which **getchar** and **putchar**
are the simplest. Each time it is called, **getchar** reads the 
*next input characyer* from a text stream and returns that as its value.
That is, after `c = getchar()` the variable  `c` contains the next
character of input. The characters normally come from the keyboard.

The function `putchar` prints the character each time it is called
`putchar(c)` priunts the contents of the integer variable `c` as a 
character, usually on the screen. Calls to `putchar` and `printf` may
be interleaved; the output will appear in the order in which the calls
are made.


### 1.5.1 File Copying


Given `getchar` and `putchar`, you can write a surprising amount of useful
code without knowing anything more about input and output. The simplest
example is a program that copies its input to its output one character at 
a time:


**Program**: [Input to Output](code/input_output.c)


The problem is distinguishing the end of the input from valid data.
The solution is that `getchar` returns a distinctive value when there
is no more input, a value that cannot be confused with any real character.
This value is called "EOF" for "end of file". We must decalre `c` to be 
a type big enough to gold EOF in addition to any possible `char`. Therefore
we must use `int`.

EOF is an integer defined in `<stdio.h>`, but the specific numeric value
doesn't matter as long as it is not the same as any `char` value. By using
the symbolic constant, we are assured that nothing in the program depends
on the specific numeric value.

In C, any assignment, such as `c = getchar()` is an expression and has
a value, which is the value of the left hand side adter the assignment. This
means that an assignment can appear as part of a larger expression. If the
assignment of a character to `c` is put inside the test part of a `while`
loop, the copy program can be written this way:


**Program**: [Input to Output - version 2](code/input_output2.c)

This version centralizes the input - there is now only one reference to
`getchar` - and shrinks the program. The resulting program is more compact,
and, once the idiom is mastered, easier to read.


### 1.5.2 Character Counting


The next program counts characters; it is similar to the copy program.


**Program**: [Character counter](code/character_counter.c)


The caracter counting program accumulates its count in a `long` variable
instead of an `int`. `long` integers are at least 32 bits. Although on some
machines, `int` and `long` are the same size, on others an  `int` is 16 bits,
with a maximum value of 32767, and it would take relatively little input to 
overflow an `int` counter.

It may be possible to cope with even bigger numbers by using a `double`
(double precision `float`). We will also use a `for` statement instead
of a `while`, to illustrate anothe way to write the loop.


**Program**: [Character counter - version2](code/character_counter2.c)


`printf` uses %f for both float and double; %.0f suppresses printing of 
the decimal point and the fraction part, which is zero.


The body of this `for` loop is empty, because all of the work is done
in the test and increment parts. But the grammatical rules of C require 
that a `for` statement have a body. The isolated semicolon, called a 
`null statement`, is there to satisfy that requirement. We put it on a
separate line to make it visible.

Before we leave the character count program, obeserve that if the input
contains no charcters, the while or for test fails on the very first call 
to `getchar`, an the program produces zero, the right answer. This is 
important. One of the nice things about while and for is that they test
at the top of the loop, before proceeding with the body. If there is nothing
to do, nothing is done, even if that means never going thourgh the loop body.
Programs should act intelligently when given zero-length input. The while and
for statements help ensure that programs do reasonable things with 
boundary conditions.


### 1.5.3 Line Counting


The next program counts input lines. As we mentioned above, the standard
library ensures that an input text stream appears as a sequence of lines, each
terminated by a newline. Hence, counting lines is just counting newlines:


**Program**: [Line counter](code/line_counter.c)


A character written between single quotes represents an integer value
equal to the numerical value of the character in the machines's character
set. This is called a `character constant`, although it is just another way
to write a small integer. So, for example, 'A' is a character constant; in
the ASCII character set its value is 65, the internal representation of
the character **A**.


The escape sequences used in string constants are also legal in character
constants, so '\\n' stand for the value of the newline character, which is 
10 in ASCII. You should note carefully that '\\n' is a single character, and
in expressions is just an integer; on the other hand, "\\n" is a string 
constant that happens to contain only one character.


### 1.5.4 Word Counting


The fourth in our series of useful programs counts lines, words, and
characters, with the loose definition that a word is any sequence of 
characters that does not contain a blank, tab or newline. This is a 
bare-bones version of the UNIX program **`wc`**.


**Program**: [wc program](code/wc.c)


## 1.6 Arrays


Let us write a program to count the number of occurences of each digit, of
white space chracters (blank, tab newline), and of all other characters. This
is artificial, but it permits us to illustrate several aspects of C in one
program.

There are twelve categories of input, so it is convenient to use an array to
hold the number of occurrences of each digit, rather than ten individual
variables. Here is one version of the program:


**Program**: [counting](code/counting.c)


## 1.7 Functions


A function provides a convenient way to encapsulate some computation,
which can then be used without worrying about its implementation. With
properly designed functions, it is possible to ignore *how* a job is done;
knowing *what* is done is sufficient. C makes the use of functions easy,
convenient and efficient; you will often see a short function defined and
called only once, just because it clarifies some piece of code.


So far we have used only functions like `printf`, `getchar`, and `putchar`
that have been provided for us; now it's time to write a few of our own. 
Sincce C has no exponentiation operator like `**` of Fortran, let us 
illustrate the mechanics of functino definition by writing a function 
`power(m,n)` to raise an integer `m` to a positive integer power `n`. That
is, the value of `power(2,5)` is 32. This function is not a practical
exponentiation routine, since it handles only positive powers of small 
integers, but it's good enough for illustration.


Here is the function `power` and a main program to exercise it, so you can 
see the whole structure at once.


**Program**: [power](code/pow.c)


The names used by `power` for its parameters are local to `power`, and are
not visible to any other function: other routines can use the same names
without conflict. This is also true of the variables `i` and `p`: the i in
power is unrelated to the i in main.


We will generally use **parameter** for a variable named in the parenthesized
list in a function definition, and **argument** for the value used in a call
of the function. The terms **formal argument** and **actual argument** are
sometimes used for the same distinction.


Any expression may follow **return**:

```
return expression;
```


A functin need no return a value; a `return` statement with no expression
causes control, but no useful value, to be returned to the caller, as does
"falling off the end" of a function by reaching the terminating right brace.
And the calling function can ignore a value returned by a function.


You may have noticed that there is a `return` statement at the end of `main`.
Since `main` is a function like any other, it may return a value to its
caller, which is in effect the environment in which the program was executed.
Typically, a return value of zero implies normal terminatin; non-zero values
signal unusual or erroneous termination conditions. In the interests of 
simplicity, we have omitted `return` statements from our `main` functions up
to this point, but we will include them hereafter, as a reminder that 
programs should return status to their environment.


The declaration:

```
int power(int m, int n);
```

just before `main` says that `power` is a function that expects two **int**
arguments and returns a **int**. This declaration, which is called a 
`function prototype`, has to agree with the definition and uses of `power`.
It is an error if the definition of a function or any uses of it do not 
agree with its prototype.


Parameter names need not agree. Indeed, parameter names are optional in a
function prototype, so for the prototype we could have written:

```
int power(int , int );
```

Well-chosen names are good documentation, however, so we will often use them.


## 1.8 Arguments - Call by Value


In C, all function arguments are passed "by value". This means that the 
called function is given the values of its arguments in temporary variables
rather than the originals. This leads to some different properties than are 
seen with "call by reference" languages.


The main distinction is that in C the called function cannot directly alter
a variable in the calling function; it can only alter its private, temporary
copy.


Call by value is an asset, however, not a liability. It usually leads to more
compact programs with fewer extraneous vairables, because parameters can be
treated as conveniently initialized local vairables in the called routine.


When necessary, it is possible to arrange for a function to modify a variable
in a calling routine. The caller must provide the **address** of the 
variable to be set (technically a **pointer** to the variable), and the 
called function must declare the parameter to be a pointer and access the
variable indirectly through it.


The story is different for arrays. When the name of an array is used as an
argument, the value passed to the function is the location or address of the
beginning of the array - there is no copying of array elements. By 
subscripting the value, the function can access and alter any element of 
the array.


## 1.9 Character Arrays


The most common type of array in C is the array of characters. To illustrate
the use of character arrays and functions to manipulate them, let's write a
program that reads a set of text lines and prints the longest. The outline is 
simple enough:

```
while (there's another line)
    if (it's longer than the previous longest)
        save it
        save its length
print longest line
```


This outline makes it clear that the program divides naturally into pieces.
One piece gets a new line, another tests it, another saves it, and the rest
controls the process.


Since things divide so nicely, it would be well to write them that way too.
Accordingly, let us first write a separate function **getline** to fetch the
next line of input. We will try to make the function useful in other 
contexts. At the minimum, `getline` has to return a signal about possible 
end of file; a more useful design would be to return the length of the line, 
or zero if end of file is encountered. Zero is an acceptable end-of-file 
return because it is never a valid line length. Every text line has at least
one character; even a line containing only a newline has length 1.


When we find a line that is longer than the previous longest line, it must
be saved somewhere. This suggests a second function, **copy**, to copy the 
new line to a safe place.


Finally, we need a main program to control **getline** and **copy**. Here is
the result:


**Program**: [Biggest line](code/biggest_line.c)


## 1.10 External Variables and Scope


Each local variable in a function comes into existence only when the function is called,
and disappears when the function is exited. This is why such variables are usually
known as **automatic** variables, following terminology in other languages. We will
use the term automatic henceforth to refer to these local variables.


Because automatic variables come and go with function invocation, they do not retain
their values from one call to the next, and must be explicitly set upon each entry. If
they are not set, they will contain garbage.


As an alternative to automatic variables, it is possible to define variables that
are **external** to all functions, that is, variables that can be accessed by
name by any function.


Becasue external variables are globally accessible, they can be used instead of argument
lists to communicate date between functions. Furthermore, because external variables
remain in existence permanently, rather than appearing and disappearing as functions
asre called and exited, they retain their values even after the functions that set
them have returned.


An external variable must be **defined**, exactly once, outside of any function; this
sets aside storage for it. The variable must also be **declared** in each function 
that wants to access it; this states the type of the variable. The declaration may be
an explicit **extern** statement or may be implicit from context. To make the 
discussion concrete, let us rewrite the longest-line program with `line`, `longest`, 
and `max` as external variables. This requires changing the calls, declarations, and
bodies of all three functions.


**Program**: [Biggest line - external variables](code/biggest_line_external.c)


The external variables in `main`, `getline`, and `copy` are defined by the first lines of
the example above, which state their type and cause storage to be allocated for them. 
Syntactically, external definitions are just like definitions of local variables, but since
they occur outside of functions, the variables are external. Before a function can use
an external variable, the name of the variable must be made known to the function. One way 
to do this is to write an **extern** declaration in the function; the declaration is the same
as before except for the added keyword **extern**.


In certain curcumstances, the **extern** declaration can be omitted. If the definition
of an external variable occurs in the source file before its use in particular function, then
there is no need for an **extern** declaration in the function. The **extern** declaration in
`main`, `getline`, and `copy` are thus redundant. In fact, common practice is to place 
definitions of all external variables at the beginning of the source file, and then omit all 
**extern** declarations.


If the program is in several source files, and a variable is defined in *file1*, and used in
*file2* and *file3*, then **extern** declarations are needed in *file2* and *file3* to 
connect the occurences of the variable. The usual practice is to collect **extern** 
declarations of variables and functions in a separate file, historically called a **header**, 
that is included by **#include** at the front of each source file. The suffix `.h` is 
conventional for header names. The functions of the standard library, for example, are declared
in headers like **<stdio.h>**.


Since the specialized versions of `getline` and `copy` have no arguments, logic would suggest
that their prototypes at the beginning of the file should be `getline()` and `copy()`. But
for compatibility with older C programs the standard takes an empty list as an old-style
declaration, and turns off all argument list checking; the word **void** must be used ofr an
explicitly empty list.


You should note that we are using the words *definition* and *declaration* carefully when we
refer to external variables in this section. "Definition" refers to the place where the
variable is created or assigned storage; "declaration" refers to places where the nature of the 
variable is stated but no storage is allocated.


By the way, there is a tendency to make everything in sight an **extern** variable because
it appears to simplify communications - argument lists are short and variables are always 
there when you want them. But external variables are always there vene when you don't want them.
Relying too heavily on external variables is fraught with peril since it leads to programs
whose data connections are not all obvious - variables can be changed in unexpected and even 
inadvertent ways, and the program is hard to modify. The second version of the longest-line
program is inferior to the first, partly for these reasons, and partly because it destroys
the generality of two useful functions by wiring into them the names of the variables they 
manipulate.
