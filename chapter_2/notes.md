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


<<<<<<< HEAD

The standars headers **<limits.h>** and **<float.h>** contain symbolic
constants for all of these sizes, along with other properties of the machine
and compiler.
=======
## 2.3 Constants


An *integer constant* like **1234** is an `int`. A `long` constant is written
with a terminal **l** (ell) or **L**, as in **1234L**; an integer too big
to fit into an `int` will also be taken as a `long`. Unsigned constants
are written with a terminal **u** or **U**, and the suffix **ul** or **UL**
indicates `unsigned long`.


*Floating-point* constants contain a decimal point (123.4) or an 
exponent (1e-2)
or both; their type is double, unless suffixed. The suffixes **f** or **F**
indicate a `float` constant; **l** or **L** indicate a `long double`.


The value of an integer can be specified in octal or hexadecimal instead of
decimal. A leading 0 (zero) on an integer constant means octal; a leading 
**0x** or **0X** means hexadecimal. For example, decimal 31 can be written
as 037 in octal and 0x1f or 0X1F in hex. Octal and hexadecimal constants
may also be followed by an L to make them long and U to make them unsigned;
0XFUL is an unsigned long constant with value 15 decimal.


A *character constant* is an integer, written as one character within single 
quotes, such as 'x'. The value of a character constant is the numeric value
of the character in the machine's character set. For example, in the ASCII
character set the character constant '0' has the value 48, which is unrelated
to the numeric value 0.


Certain characters can be represented in character and string constants by
escape sequences like **\\n** (newline). In addition, an arbitrary byte-sized
bit pattern can be specified by **\\000** where `000` is one to three octal
digits (0..7) or by **\\xhh** where hh is one or more hexadecimal digits
(0..9, a..f, A..F). So we might write:


```
#define VTAB '\013' /* ASCII vertical tab */
#define BELL '\007' /* ASCII bell character */
```


or in hexadecimal:


```
#define VTAB '\xb' /* ASCII vertical tab */
#define BELL '\x7' /* ASCII bell character */
```


A `constant expression` is an expression that involves only constants.
Such expressions may be evaluated during compilation rather than run-time
, and accordingly may be used in any place that a constant can occur, as in:


```
#define MAX 1000
char line[MAX];
```


A `string constant`, or `string literal`, is a sequence of zero or more
characters surrounded by double quotes, as in "I am a string" or the empty
string "".


String constants can be concatenated at compile time:

```
"hello," " world"
```


is equivalent to "hello, world". This is useful for splitting long strings
across several source lines.


Technically, a string constant is an array of characters. The internal
representation of a string has a null character '\0' at the end, so the
physical storage required is one more than the number of characters written
between the quotes. This representation means that there is no limit
to how long a string can be, but programs must scan a string completely to
determine its length. The standard library function **strlen(s)** returns 
the length of its character string argument s, excluding the terminal '\0'.


Here is our version:


**Program**[Strlen version](code/my_strlen.c)


**strlen** and other string functions are declared in the standard header
**<string.h>**.


Be careful to distinguish between a character constant and a string that 
contains a single character: 'x' is not the same as "x". The former is an 
integer, used to produce the numeric value of letter x in the machine's 
character set, while the latter is an array of characters that contains 
the character x and '\0'.


There is one other kind of constant, the *enumeration constant*. An 
enumeration is a list of constant integer values, as in:


```
enum boolean { NO, YES };
```


The first name in an enum has value 0, the next 1, and so on, unless explicit
values are specified. If not all values are specified, unspecified values
continue the progression from the last specified value, as in the second
of these examples:


```
enum escapes { BELL = '\a', BACKSPACE = '\b', 
                NEWLINE = '\n' };

enum months {JAN = 1, FEB, MAR };
// FEB is 2, MAR is 3
```


Names in different enumerations must be distinct. Values need not be distinct
in the same enumeration.


Enumerations provide a conveninet way to associate constant values with names,
an alternative to **#define** with the advantage that the values can be
generated for your. Although variables of *enum* types may be declared,
compilers need not check that what you store in such a variable is a valid
value for the enumeration. Nevertheless, enumeration variables offer
the chance of checking and so are often better than *#defines*. In addition,
a debugger may be able to print values of enumeration variables in their
symbolic form.


## 2.4 Declarations


All variables must be declared before use, although certain declarations can
be made implicitly by context. A declaration specifies a type, and contains a
list of one or more variables of that type, as in:

```
int lower, upper, step;
char c, line[1000];
```


If the variable in question is not automatic, the initialization is done once
only, conceptually before the program starts executing, and the initializer
must be a constant expression. An explicitly initialized automatic variable
is initialized each time the function or block it is in is entered; the
initializer may be any expression. External and static variables are 
initialized to zero by default. Automatic variables for which there is no
explicit initializer have undefined (i.e. garbage) values.


The qualifier **const** can be applied to the declaration of any variable
to specify that its value will not be changed. For an array, the **const**
qualifier says that the elements will not be altered.


```
const double e = 2.41;
cont char msg[] = "warning: ";
```


The **const** declaration can also be used with array arguments, to indicate
that the function does not change the array:


```
int strlen(const char[]);
```


The result is implementation-defined if an attempt is made to change a 
**const**.


## 2.5 Arithmetic operators


The binary arithmetic operators are "+, -, *, /" and the modulus operator "%".
Integer division truncates any fractional part.


The "%" operator cannot be applied to *float* or *double*.


Arithmetic operators associate left to right.



