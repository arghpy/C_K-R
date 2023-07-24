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
