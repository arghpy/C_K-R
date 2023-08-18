# Chapter 4: Functions and Program Structure


Fucntions break large computing tasks into smaller ones, and enable people
to build on what others have done instead of starting over from scratch.
Appropriate functions hide details of operation from parts of the program
that don't need to know about them, thus clarifying the whole, and easing the
pain of making changes.


C has been designed to make fucntions efficient and easy to use; C programs
generally consist of many small functions rather than a few big ones. A 
program may reside in one or more source files. Source files may be compiled
separately and loaded together, along with previously compiled functions 
from libraries. We will not go into that process here, however, since the 
details vary from system to system.


Function declaration and definition is the area where the ANSI standard has
made the most visible changes to C. As we saw first in Chapter 1, it is now
possible to declare the types of arguments when a function is declared. The
syntax of fucntion definition also changes, so that declarations and 
definitions match. this makes it possible for a compiler to detect many
more errors that it could before. Furthermore, when arguments are properly
declared, appropriate type corecions are performed automatically.


The standard clarifies the rules on the scope of names; in particular, it 
requires that there be only one definition of each external object.
Initialization is more general: automatic arrays and structures may now be
initialized.


The C preprocessor has also been enhances. New preprocessor facilities include
a more complete set of conditional compilation directives, a way to create
quoted strings from macro arguments, and better control over the macro 
expansion process.


## 4.1 Basics of Functions


To begin, let us design and write a program to print each line of its input
that contains a particular "pattern" or string of characters. (This is a 
special case of the UNIX program *grep*). 


Although it's certainly possible to put the code for all of this in *main*
a better way is to use the structure to advantage by making each part a 
separate function. Three small pieces are easier to deal with than one big
one, because irrelevant details can be buried in the functions, and the 
chance of unwanted interactions is minimized. And the pieces may even be
useful in other programs.


"While there's another line" is *getline*, a function that we wrote in Chapter
1, and "print it" is *printf*, which someone has already provided for us. This
means we need only write a routine to decide whether the line contains an 
occurence of the pattern.


We can solve that probelem by writing a function *strindex(s, t)* that 
returns the position or index in the string s where the string t begins, or -1
if s doesn't contain t. Because C arrays begin at position zero, indexed will
be zero or positive, and so an negative value like -1 is convenient for 
signaling failure. When we later need more sophisticated pattern matching, we
only have to replace strindex; the rest of the code can remain the same. (The
standard library provides a function *strstr* that is similar to strindex, 
except that it return a pointer of an index.)


Given this much design, filling in the details of the program is 
straightforward. Here is the whole thing, so you can see how the pieces fit
together. For now, the pattern to be searched for is a literal string, which
is not the most general of mechanisms. We will return shortly to a discussion
of how to initialize character arrays, and in Chapter 5, will show how to
make the pattern a parameter that is set when the program is run. There is 
also a slightly different version of *getline*; you might find it instructive
to compare it to the one in Chapter 1.


**Program: **[strindex aka grep](code/strindex.c)


Each function definition has the form:

```
return-tpe function-name(argument declarations)
{
    declarations and statements;
}
```

Various parts may be absent; a minimal function is:

```
dummy() {}
```

which does nothing and return nothing. A do-nothing function like this is 
sometimes useful as a place holder during program development. If the return
rype is omitted, **int** isi assumed.


A program is just a set of definitions of variables and functions.
Communication between the functions is by arguments and values returned by the
functions, and through external variables. The functions can occur in any 
order in the source file, and the source program can be split into multiple
files, so long as not function is split.


The return statement is the mechanism for returning a value from the called
function to its caller. Any expression can follow return:

```
return expression;
```


The expression will be converted to the return type of the function if 
necessary. Parantheses are often used around the expression, but they are 
optional.


The calling function is free to ignore the returned value. Furthermore, there
need be no expression after return; in that case, no value is returned to the
caller. Control also returns to the caller with no value when execution "falls
off the end" of the function by reaching the closing right brace. It is not
illegal, but probably a sing of trouble if a function returns a value from
onde place and no value from another. In any case, if a function fails to
return a value, its "value" is certain to be garbage.


The pattern-searching program return a status from *main*, the number of
matches found. This value is available for use by the environment that called
the program.


The mechanics of how to compile and load a C program that resides on 
multiple source files vary from one system to the next. On the UNIX system, 
for example, the *cc* command does the job. Suppose that the three functions
are stored in three files called *main.c*, *getline.c* and *strindex.c*. Then
the command:

```
cc main.c getline.c strindex.c
```

compiles the three files, placing the resulting object code in files main.o, 
getline.o and strindex.o, then loads them all into an executable file called
a.out. If there is an error, say in main.c, that file can be recompiled by
itself and the result loaded with the previous object files, with the
command:

```
cc main.c getline.o strindex.o
```


The *cc* command uses the ".c" versus ".o" naming convention to distinguish
source files from object files.


## 4.2 Functions Returning Non-integers


So far our examples of functions have returned either no value (void)
or an `int`. What if a function must return some other type? Many numerical
functions return `double`; other specialized functions return other types.
To ilustrate how to deal with this, let us write and use the function
**atof(s)**, which converts the string *s* to its double-precision floating
point equivalent. It handles an optional sign and decimal point, and the
presence of absence of either integer part or fractional part. Our version
is not a high-quality input conversion routine; that would take more space
than we care to use. The standard library includes an **atof**; the header
**stdlib.h** declares it.


First, atof itself must declare the type of value it returns, since it is
not int. The type name precedes the function name:


**Program:**[atof](code/atof.c)


Second, and just as important, the calling routine must know that **atof**
return a non-int value. One way to ensure this is to declare **atof**
explicitly in the calling routine. The declaration is shown in this primitive
calculator (barely adequate for check-book balancing), which reads one 
number per line, optionally preceeded by a sing, and adds them up, printing
the running sumb after each input:


**Program:**[atof calling routine](code/atof_calling.c)


The declaration:
```
double sum, atof(char []);
```
says that sum is a double variable, and that atof is a function that takes
one char[] argument and return a double.


The function **atof** must be declared and defined consistently. If atof
itself and the call to it in main have inconsistent types in the same source
file, the error will be detected by the compiler. But if (as if more likely)
atof were compiled separetely, the mismatch would not be detected, atof 
would return a double that main would treat as an int, and meaningless 
answers would result.


In the light of what we have said about how declarations must match
definitions, this might seem surprising. The reason a mismatch can happen
is that if there is no function prototype, a function is implicitly declared
by its first appearance in an expression, such as
```
sum += atof(line)
```


If a name that has not been previously declared occurs in an expression
and is followed by a left parenthesis, it is declared by context to be
a function name, the function is assumed to return an int, and nothing
is asumed about its arguments. Furthermore, if a function decalration
does not include arguments, as in **double atof();** that too is taken
to mean that nothing is to be assumed about the arguments of atof; all
parameter checking is turned off. This special meaning of the empty
argument list is intended to permit older C programs to compile with
new compilers. But it's a bad idea to use it with new programs. If the 
function takes arguemtns, decalre them; if it takes no arguments, use 
**void**.


Given atof, properly declared, we could write atoi (convert a strinf to
an int) in terms of it:


```
// atoi: convert string s to integer using atof
int atoi(char s[])
{
    double atof(char s[]);

    return (int) atof(s);
}
```


## 4.3 External Variables


A C program consists of a set of external objects, which are either variables
or functions. The adjective "external" is used in contrast to "internal", 
which describes the arguments and variables defined inside functions. External
variables are defined outside of any function, and are thus potentially 
available to many functions. Fucntions themselves are always external, 
because C does not allow functions to be defined inside other functions.
By default, external variables and functions have the property that all 
references to them by the same name, even from functions compiled separately
are references to the same thing. (The standard calls this property external
linkage.)


Because external variables are globally accessible, they provide an
alternative to function arguments and return values for communicating data
between functions. Any function may access an external variable by referring
to it by name, if the name has been declared somehow.


If a large number of variables must be shared among functions, external 
variables are more convenient and efficient than long argument lists. As
pointed out in Chapter 1, however, this reasoning should be applied with
some caution, for it can have a bad effect on program structure, and lead
to programs with too many data connections between functions.


External variables are also useful because of their greater scope and 
lifetime. Automatic variables are internal to a function; they come into
existence when the function is entered, and disappear when it is left. 
External variables, on the other hand, are permanent, so they retain values
from one function invocation to the next. Thus if two functions must share
some data, yet neither calls the other, it is often most convenient if the
shared data is kept in external variables rather than passed in and out
via arguments.


Let us examine this issue further with a larger example. The problem is to
write a calculator program that provides the operators +, -, *, and /.
Because it is easier to implement, the calculator will use reverse Polish
notation instead of infix. (Reverse Polish is used by some pocket 
calculators, and in languages like Forth and Postscript).


In reverse Polish notation, each operator follows its operands; and infix 
expression like `(1 - 2) * (4 + 5)` is entered as `1 2 - 4 5 + *`. Parantheses
are not needed; the notation is unambigous as long as we know how many
operands each operator expects.


The implementation is simple. Each operand is pushed onto a stack; when an
operator arrives, the proper number of operands (two for binary operators)
is popped, the operator is applied ot them, and the result is pushed back
onto the stack. In the example above, for instance, 1 and 2 are pushed, then
replaced by their difference, -1. Next, 4 and 5 are pushed and then replaced 
by their sum, 9. The product of -1 and 9, which is -9, replaces them on the
stack. The value on the top of the stack is popped and printed when the end
of the input line is encountered.


The structure of the program is thus a loop that performs the proper operation
on each operator and operand as it appears:


```
while (next operator or operand is not end-of-file indicator)
    if (number)
        push it
    else if (operator)
        pop operands
        do operation
        push result
    else if (newline)
        pop and print top of stack
    else
        error
```


The oparations of pushing and popping a stack are trivial, but by the time
error detection and recovery are added, they are long enough that it is
better to put each in a separate function than to repeat the code throughout
the whole program. And there should be a separate function for fetching the
next input operator or operand.


The main design decision that has not yet been discussed is where the stack
is, that is, which routines access it directly. One possibility is to keep
it in `main`, and pass the stack and the current stack position to the 
routines that push and pop it. But `main` doesn't need to know about the
variables that control the stack; it only does push and pop operations. So
we have decided to store the stack and its associated information in external
variables accessible to the `push` and `pop` functions but not to `main`.


Translating this outline into code is easy enough. If for now we think of the
program as existing in one source file, it will look like this:

```
#includes
#defines

function declarations for main

main() {...}

external variables for push and pop

void push(double f) {...}
double pop(void) {...}

int getopt(char s[]) {...}

routines called by getopt
```


Later we will discuss how this might be split into two or more source files.


The function **main** is a loop containing a big **switch** on the type
of operator or operand.


**Program: **[reverse polish calculator](code/polish_calculator.c)


Because **+** and ***** are commutative operators, the order in which the 
popped operands are combined is irrelevant, but for **-** and **/** the
left and right operands must be distinguished. In **push(pop() - pop());**
the order in which the two calls of pop are evaluated is not defined. To
guarantee the right order, it is necesarry to pop the first value into
a temproary variable as we did in **main**.


A variable is external if it is defined outside of any function. Thus the
stack and stack index that must be shared by **push** and **pop** are 
defined outside of these functions. But **main** itslef does not refer to
the stack or stack position - the representation can be hidden.


Let us now turn to the implementation of **getop**, the function that
fetches the next operator or operand. The task is easy. Skip blanks and tabs.
If the next character is not a digit or a decimal point, return it. Otherwise
collect a string of digits (which might include a decimal point), and return 
NUMBER, the signal that a number has been collected.


What are **getch** and **ungetch** ? It is often the case that a program
cannot determine that it has read enough input until it has read too much.
One instance is collecting the characters that make up a number: until the 
first non-digit seen, the number is not complete. But then the program has 
read one character too far, a character that it is not prepared for.


The problem would be solved if it were possibler to "un-read" the unwanted
character. Then, every time the program reads one character too many, it could
push it back on the input, so the rest of the code could behave as if it had
never been read. Fortunately, it's easy to simulate un-getting a character
, by writing a pair of cooperating functions. **getch** delivers the next 
input character to be considered; **ungetch** remembers the characters put
back on the input, so that subsequent calls to getch will return them before
reading new input.


How they work together is simple. **ungetch** puts the pushed back characters
into a shared buffer - a character array. **getch** reads from the buffer if
there is anything there, and calls **getchar** if the buffer is empty. There
must also be an index variable that records the position of the current 
character in the buffer.


Since the buffer and the index are shared by **getch** and **ungetch** and
must retain their values between calls, they must be external to both
routines.


The standard library includes a function **ungetc** that provide one 
character of pushback. We have used an array for the pushback, rather than
a single character, to illustrate a more general approach.


## Scope Rules


The functions and external variables that make up a C program need not all
be compiled at the same time; the source text of the program may be kept
in several files, and previously compiled routines may be loaded from
libraries. Among the questions of interest are:

- How are declarations written so that variables are properly declared 
during compilation?
- How are declarations arranged so that all the pieces will be properly
conected when the program is loaded?
- How are declarations organized so there is only one copy?
- How are external variables initialized?


Let us discuss these topics by reorganizing the calculator program into
several files. As  practical matter, the calculator is too small to be
worth splitting, but it is a fine illustration of the issues that arrise
in larger programs.


The *scope* of a name is the part of the program within which the name
can be used. For an automatic variable declared at the beginning of a
function, the scope is the function in which the name is declared. Local
variables of the same name in different funcitons are unrelated. The same
is true of the parameters of the function, which are in effect local 
variables.


The scope of an external variable or a function lasts from the point at which
it is declared to the end of the file being compiled. For example, if *main*
, *sp*, *val*, *push*, and *pop* are defined in one file, in the order
shown above, that is, 

```
main() {...}

int sp = 0;
double val[MAXVAL];

void push(double f) {...}

double pop(void) {...}
```

then the variables *sp* and *val* may be used in *push* and *pop* simply by
naming them; no further declarations are needed. But these names are not
visible in *main*, nor are *push* and *pop* themselves.


On the other hand, if an external variable is to be referred to before it is
defined, or if it is defined in a different source file from the one where
it is being used, hten an **extern** declaration is mandatory.


It is important to distinguish between the *declaration* of an external 
variable and its *definition*. A declaration announces the properties of 
a variable (primarly its type); a definition also causes storage to be 
set aside. If the lines:

```
int sp;
double val[MAXVAL];
```

appear outside of any function, they **define** the external variables *sp*
and *val*, cause storage to be set aside, and also serve as the declaration
for the rest of that source file. On the other hand, the lines:

```
extern int sp;
extern double val[];
```

**declare** for the rest of the source file that *sp* is an *int* and that
*val* is a *double* array (whose size is determined elsewhere), but they do
not create the variables or reserve storage for them. 


There must be only one *definition* of an external variable among all the
files that make up the source program; other files may contain **extern**
declarations to access it. (There may also be **extern** delcarations in
the file containing the definition). Array sized must be specified with the
definition, but are optional with an **extern** declaration.


Initialization of an external variable goes only with the definiton.


Although it is not likely organization for this program, the functions *push*
and *pop* could be defined in one file, and the variables *val* and *sp*
defined and initialized in another. Then these definitions and declarations
would be necessary to tie them together:


```
In file1:
    extern int sp;
    extern double val[];

    void push(double f) {...}
    double pop(void) {...}

In file2:
    int sp = 0;
    double val[MAXVAL];
```


Because the **extern** declarations in *file1* lie ahead of and outside the
function definitons, they apply to all functions; one set of declarations
suffices for all of *file1*. This same organization would also be needed
if the definitions of *sp* and *val* followed their use in one file.


## 4.5 Header Files


Let us now consider dividing the calculator program into several source
files, as it might be if each of the componenets were substantailly
bigger. The **main** function would go in one file, which we will call
**main.c**; **push**, **pop**, and their variables go into a second file,
*stack.c*; **getop** goes into a third, *getop.c*. Finally, **getch** and
**ungetch** go into a fourth file, *getch.c*; we separate them from the
others because they would come from a separetely-compiled library in a 
realistic program.


There is one more thing to worry about - the definitions and declarations
shared among the files. As much as possible, we want to centralize this,
so that there is only one copy to get right and keep right as the program
evolves. Accordingly, we will place this common material in a **header file**
named *calc.h*, which will we included as necessary. (The **#include** line
is described in Section 4.11) The resulting program then looks like this:


```
calc.h:
    #define NUMBER '0'
    void push(double);
    double pop(void);
    int getop(char []);
    int getch(void);
    void ungetch(int);
```


```
getop.c:
    #include <stdio.h>
    #include <ctype.h>
    #include "calc.h"
    getop() {
        ...
    }
```


```
stack.c:
    #include <stdio.h>
    #include "calc.h"
    #define MAXVAL 100
    int sp = 0;
    double val[MAXVAL];
    void push(double) {
        ...
    }
    double pop(void) {
        ...
    }
```


```
getch.c:
    #include <stdio.h>
    #define BUFSIZE 100
    char buf[BUFSZE];
    int bufp = 0;
    int getch(void) {
        ...
    }
    void ungetch(int) {
        ...
    }
```


```
main.c:
    #include <stdio.h>
    #include <stdlib.h>
    #include "calc.h"
    #define MAXOP 100
    main() {
        ...
    }
```


There is a tradeoff between the sedire that each file have access only to 
the information it needs for tis job and the practical reality that it is 
harder to mainatin more header files. Up to some moderate program size, it is
probably best to have one header file that contains everything that is to be
shared between any two parts of the program; that is the decision we made
here . For a much larger program, more organization and more headers would
be needed.


## 4.6 Static Variables


The variables *sp* and *val* in **stack.c**, and *buf* and *bufp* in 
**getch.c**, are for the private use of the functions in their respective
source files, and are not meant to be accessed by anything else. The 
**static** declaration, applied to an external variable or function, limits
the scope of that object to the rest of the source file being compiled.
External **static** thus provides a way to hide names like *buf* and *bufp*
in the *getch-ungetch* combination, which must be external so they can be 
shared, yet which should not be visible to users of *getch* and *ungetch*.


Static storage is specified by prefixing the normal declaration with the 
word **static**. If the two routines and the two variables are compiled in one
file, as in:

```
static char buf[BUFSIZE];
static int bufp = 0;

int getch(void) {...}
void ungetch(int c) {...}
```

then no other routine will be able to access *buf* and *bufp*, and those names
will not conflict with the same names in other files of the same program. In
the same way, the varuables that *push* and *pop* use for stack manipulation
can be hidden, by declaring *sp* and *val* to be *static*.


The external *static* declaration is most often used ofr variables, but it
can be applied to functions as well. Normally, function names are global,
visible to any part of the entire program. If a function is declared *static*
however, its name is invisible outside of the file in which it is declared.


The *static* declaration can also be applied to internal variables. Internal
*static* variables are local to a particular function just as automatic 
variables are, but unlike automatics, they remain in existence rather than
coming and going each time the function is activated. This means that 
internal *static* variables provide private, permanent storage within a 
single function.


## 4.7 Register Variables


A **register** declaration advises the compiler that the variable in question
will be heavily used. The idea is that **register** variables are to be placed
in machine registers, which may result in smaller and faster programs. But
compiler are free to ignore the advice.


The **register** declaration looks like:

```
register int x;
register char c;
```

and so on. The **register** declaration can only be appllied to automatic
variables and to the formal parameters of a function. In this latter case,
it looks like:

```
f(register unsigned m, register long n)
{
    register int i;
}
```

In practice, there are restrictions on register variables, reflecting the
realitites of underlying hardware. Only a few variables in each function
may be kept in registers, and only certain types are allowed. Excess register
declarations are harmless, however, since the word *register* is ignored for
excess or disallowed declarations. The specific restrictions on number and
types of register variables vary from machine to machine.


## 4.8 Block Structure


C is not a block-structured language in the sense of Python or similar
languages, because functions may not be defined within other functions. On
the other hand, variables can be defined in a block-structured fashion within
a function. Declarations of variables (including initializations) may
follow the left brace that introduces any compound statement, not just
the one that begins a function. Variables declared in this way hide any
identically named variables in outer blocks, and remain in existence until
the matching right brace. For example, in:

```
if (n > 0) {
    int i;

    for (i = 0; i < n; i++)
        ...
}
```

the scope of the variable **i** is the "true" branch of the *if*; this *i*
is unrelated to any *i* otside the block. An automatic variable declared and
initialized in a block is initialized each time the block is entered. A 
**static** variable is initialized only the first time the block is entered.


Automatic variables, including formal parameters, also hide external variables
and functions of the same name. Given the declarations:

```
int x;
int y;

f(double x)
{
    double y;
    ...
}
```

then within the function f, occurrences of x refer to the parameter, which is
a double; outside of f, they refer to the external int. The same is true of
the variable y.


As a matter of style, it's best to avoid variable names that conceal names in
an outer scope; the potential for confusion and error is too great.
