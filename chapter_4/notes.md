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



