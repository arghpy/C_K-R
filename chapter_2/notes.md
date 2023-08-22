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


**Program:**[ Strlen version](code/my_strlen.c)


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


## 2.6 Relational and Logical Operators


The relational operators are:

```
>       >=      <       <=
```


They all have hte same precedence. Just below them in precedence are the
equality operators:


```
==      !=
```


Relational operators have lower precedence than arithmetic operators, so an
expression like **i < lim - 1** is taken as **i < (lim - 1)**, as would be
expected.


More interesting are the logical operators **&&** and **||**. Expressions
connected by them are evaluated left to right, and evaluation stops as soon as
the truth or falsehood of the result is known.


By definition, the numeric value of a relational or logical expression is 1
if the relation is true, and 0 if the relation is false.


The unary negation operator **!** converts a non-zero operand into 0, and a
zero operand into 1:

```
if (!valid)
```
rather than
```
if (valid == 0)
```


## 2.7 Type Conversions


When an operator has operands of different types, they are converted to a 
common type according to a small number of rules. In general, the only 
automatic conversions aree those that convert a "narrower" operand into a 
"wider" one without losing information, such as converting an integer to 
floating point in an expression like **f + i**. Expressions that don't make
sense, like using a **float** as a subscript, are disallowed. Expressions 
that might lose information, like assigning a longer integer type to a 
shorther, or a floating-point type to an integer, may draw a warning, but 
they are not illegal.


A **char** is just a small integer, so chars may be freely used in arithmetic
expressions. One is exemplified by this naive implementation of the function
**atoi**, which converts a string of digits into its numeric equivalent:


**Program:**[ Atoi](code/my_atoi.c)


As discussed, the expression **s[i] - '0'** gives the numeric value of the 
character stored in s[i].


Another example of **char** to **int** conversion is the function **lower**,
which maps a single character to lower case for the ASCII character set. If
the character is not an upper case letter, **lower** return it unchaged:


**Program:**[ Lower](code/lower.c)


This works for ASCII because corresponding upper case and lower case letters
are a fixed distance apart as numeric values and each alphabet is contigous -
there is nothing but letters between A and Z.


The standard header **<ctype.h>** defines a family of functions that provide
tests and conversions that are independent of character set. For example, the
function **tolower(c)** returns the lower case value of c if c is upper case
, so **tolower** is a portable replacement for the function **lower** shown
above. Similarly, the test:

```
c >= '0' && c <= '9'
```

can be replaced by **isdigit(c)**. We will use the **<ctype.h>** function from
now.


There is one subtle point about the conversion of characters to integers. The
language does not specify whether variables of type *char* are signed or 
unsigned quantities. When a *char* is converted to an *int*, can it ever 
produce a negative integer? The answer varies from machine to machine, 
reflecting differences in architecture. For portability, specify **signed**
or **unsigned** if non-character data is to be stored in *char* variables.


*Note*: in the tests, **true** just means **non-zero**.


Implicit arithmetic conversions work much as expected. In general, if an 
operator like + or * that takes two operands (binary operator) has operands
of different types, the "lower" type is **promoted** to the "higher" type 
before the operation proceeds. The result is of the higher type.


Since an argument of a fucntion call is an expression, type conversions also
take place when arguments are passed to functions. Explicit type conversions
can be forced ("coerced") in any expression, with a unary operator called a 
**cast**. In the construction:


```
(type-name) expression
```

the expression is converted to the named type by the conversion rules. The 
precise meaning of a cast is as if the *expression* were assigned to a 
variable of the specified type, which is then used in place of the whole
construction. For example, the library routine **sqrt** expects a double
argument, and will produce nonsense if inadvertently handed something else.
So if *n* is an integer, we can use:

```
sqrt((double) n)
```

to convert the value of *n* to *double* before passing it to sqrt. Note that
the cast produces the *value* of *n* in the proper type; *n* itself is not
altered.


If arguments are declared by a function prototype, as they normally should
be, the declaration causes automatic coercion of any arguments when the
function is called. Thus, given a function prototype for *sqrt*:

```
double sqrt(double);
```

the call:

```
root2 = sqrt(2);
```

coerces the integer 2 into the *double* value 2.0 without any need for a cast.


The standard library includes a portable implementation of a pseudo-random
number generator and a function for initializing the seed; the former 
illustrates a cast:


**Program:**[ rand and srand](code/rand_srand.c)


## 2.8 Increment and Decrement Operators


C provides two unusual operators for incrementing and decrementing variables.
The increment operator ++ ads 1 to its operand, while the decrement operator
-- subtracts 1. The unusual aspect is that ++ and __ may be used either as 
prefix operators (before the variable, as in ++n), or postfix (after the 
variable, as in n++). But the expression *++n* increments *n* **before**
its value is used, while n++ increments *n* **after** its value has been used.
This means that in a context where the value is being used, not just the
effect, ++n and n++ are different. If *n* is 5, then:

```
x = n++;
```
sets x to 5, but
```
x = ++n;
```
sets x to 6. In both cases, n becomes 6. The increment and decrement operators
can only be applied to varibles; an expression like (i + j)++ is illegal.


In a context where no value is wanted, just the incrementing effect, prefix
and postfix are the same. But there are situations where one or the other
is specifically called for. For instance, consider the function 
**squeeze(s,c)**, which removes all occurrences of the character c from string
s:


**Program:**[ squeeze](code/squeeze.c)


Each time a non-c occurs, it is copied into the current j position, and only
then is j incremented to be ready for the next character. This is exactly 
equivalent to:


```
if (s[i] != c) {
    s[j] = s[i];
    j++;
}
```


Another example of a similar construction comes from the *getline* function
that we wrote, where we can replace:

```
if (c == '\n') {
    s[i] = c;
    ++i;
}
```

by the more compact:

```
if (c == '\n')
    s[i++] = c;
```

As a third example, consider the standard function **strcat(s,t)**, which
concatenates the string t to the end of the string s. *strcat* assumes 
that there is enough space in s to hold the combination. As we have written it
*strcat* returns no value; the standard library version returns a pointer to
the resulting string:


**Program:**[ strcat](code/strcat.c)


As each character is copied from t to s, the postfix ++ is applied to both
i and j to make sure that they are in position for the next pass through
the loop.


## 2.9 Bitwise Operators


C provides six operators for bit manipulation; these may only be applied
to integral operands, that is *char*, *short*, *int* and *long*, whether
signed or unsigned.

```
&       bitwise AND
|       bitwise inclusive OR
^       bitwise exclusive OR
<<      left shift
>>      right shift
~       one's complement (unary)
```


The bitwise AND operator & is often used to mask off some set of bits; for
example, **n = n & 0177;** sets to zero all but the low-order 7 bits of n.


The bitwise OR operator | is used to turn bits on **x = x | SET_ON;** sets
to one in x the bits that are set to one in SET_ON.


The bitwise exclusive OR operator ^ sets a one in each bit position where its
operands have different bits, and zero where they are the same.


The shift operators << and >> perform left and right shifts of their left
operand by the number of bit positions given by the right operand, which must
be postive. Thus **x << 2** shifts the value of x left by two positions,
filling vacated bits with zero; this is equivalent to multiplication by 4.
Right shifting an unsigned quantity always fills vacated bits with zero.
Right shifting a signed quantity will fill with sign bits ("arithmetic shift")
on some machines and with 0-bits ("logical shift") on others.


The unary operator ~ yields the one's complement of an integer; that is, it
converts each 1-bit into a 0-bit and vice versa. For example **x = x & ~ 077**
sets the last six bits of x to zero. Note that x & ~077 is independent of word
length, and is thus preferable to, for example, **x & 0177700** which assumes
that x is a 16-bit quantity. The portable form involves no extra cost, since
~077 is a constant expression that can be evaluated at compile time.


As an illustration of some of the bit operators, consider the function 
**getbits(x, p, n)** that returns the (right adjusted) n-bit field of x that
begins at positon p. We assume that bit position 0 is at the right end and
that n and p are sensible positive values. For example, *getbits(x, 4, 3)*
returns the three bits in bit position 4, 3 and 2, right adjusted.


**Program:**[ getbits(x, p, n)](code/getbits.c)


The expression **x >> (p + 1 - n)** moves the desired field to the right end
of the word. **~0** is all 1-bits; shifting it left n bit positions with 
**~0 << n** places zeros in the rightmost n bits; complementing that with ~
makes a mask with ones in the rightmost n bits.


## 2.10 Assignment Operators and Expressions


Expressions such as `i = i + 2` in which the variable on the left hand side
is repeated immediately on the right, can be written in compressed form
`i += 2`. The operator += is called an asignment operator.


As an example, the function *bitcount* counts the number of 1-bits in its
integer argument.


**Program:**[ bitcount](code/bitcount.c)


Declaring the argument x to be unsigned ensures that when it is right-shifted
vacated bits will be filled with zeros, not sign bits, regardless of the 
machine the program is run on.


Quite apart from concisness, assignment operators have the advantage that
they correspond better to the way people think.


We have already seen that the assignment statement has a value and can occur
in expressions; the most common example is:

```
while ((c - getchar()) != EOF)
    ...
```


In all such expressions, the type of an assignment expression is the type
of its left operand, and the value is the value after the assignment.


## 2.11 Conditional Expressions


The statements:

```
if (a > b)
    z = a;
else
    z = b;
```

compute in z the maximum of a and b. The conditional expression, written with
the ternary operator **?:**, provides an alternate way to write this and 
similar constructions. Thus, the if/else statement can be written as:

```
z = (a > b) ? a : b;    // z = max(a, b)
```

If a and b are of different types, than the result is determined by the 
conversion rules. For example, if a si float and b is int, the result will be
a float.


## 2.12 Precedence and Order of Evaluation


Operators on the same line have the same precedence; rows are in order of 
decreasing precedence, so, for example, *, /, and % all have the same
precedence, which is higher than that of binary + and -. The "operator" ()
refers to function call. The operators -> and . are used to access members
of structures; they will be covered in Chapter 6. Chapter 5 discusses * 
(indirection through a pointer) and & (address of an object), and Chapter 3
discusses comma operator.


Note that the precedence of the bitwise operators &, ^, and | falls below
== and !=. This implies that bit-testing expressions like 
`if ((x & MASK) == 0) ...` must be fully parenthesized to give proper results.


C, like most languages, does not specify the order in which the operands of
an operator are evaluated.
