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
