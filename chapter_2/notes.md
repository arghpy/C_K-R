# Chapter 2: Types, Operators, and Expressions


Variables and constants are the basic data objects manipulated in a program.
Declarations list the variables to be used, and state what type they have
and perhaps what their initial values are. Operators specify what is to be
done to them. Expressions combine variables and constants to produce new
values. The type of an object determines the set of values it can have and
what operations can be performed on it. These building blocks are the topic
of this chapter.


The ANSI standard has made many small changes and additions to basic
types and expressions. There are now **signed** and **unsigned** forms
of all integer types, and notations for unsigned constants and hexadecimal
character constants. Floating-point operations may be done in single
precision; there is also a **long double** type for extended precision.
String constants may be concatenated at compile time. Enumerations have
become part of the language, formalizing a feature of long standing. 
Objects may be declared **const**, which prevents them from being changed.
The rules for automatic coercions amoung arithmetic types have been augmented
to handle the richer set of types.


## 2.1 Variable Names


There are some restrictions on the names of variables and symbolic constants.
Names are made up of letters and digits; the first character must be a letter.
The underscore "_" counts as a letter; it is sometimes useful for improving
the readability of long variable names. Don't begin variable names with
underscore, however, since library rutines often use such names. Traditional 
C practice is to use lower case for variables names, and all upper case
for symbolic constants.


It's wise to choose variable names that are related to the purpose of the 
variable, and that are unlikely to get mixed up typographically. We tend to
use short names for local variables, especially loop indices, and longer 
names for external variables.


## 2.2 Data Types and Sizes


There are only a few basic data types in C:


`char`: a single byte, capables of holding one character in the local
character set.


`int`: an integer, typically reflecting the natural size of integers
on the host machine.


`float`: single-precision floating point.


`double`: double-precision floating point.


In addition, there are a number of qualifiers that can be applied to these
basic types. **short** and **long** apply to integers:

```
short int sh;
long int counter;
```


The word **int** can be omitted in such declarations, and typically is.


The intent is that **short** and **long** should provide different lengths
of integers where practical; `int` will normally be the natural size of a
particular machine. `short` is often 16 bits, `long` 32 bits, and `int` either
16 or 32 bits. Each compiler is free to choose appropiate sizes for its own
hardware, subject only to the restriction that `shorts` and `ints` are at 
least 16 bits, `longs` are at least 32 bits, and `short` is no longer than
`int`, which is no longer than `long`.


The qualifier **singned** and **unsingned** may be applied to `char` or any
integer. **unsigned** numbers are always positive or zero, and obey the laws
of arithmetic modulo 2^n, where n is the number of bits in the type. So, for
instance, if chars are 8 bits, unsigned char varibles have values between
0 and 255, while signed chars have values between -128 and 127 (in a two's
complement machine). Whether plain chars are signed or unsigned is 
machine-dependent, but printable characters are always positive.

