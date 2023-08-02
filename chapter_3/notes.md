# Chapter 3: Control Flow


The control-flow statements of a language specify the order in which 
computations are performed. We have already met the most common control-flow
constructions in earlier examples; here we will complete the set, and be more
precise about the ones discussed before.



## 3.1 Statements and Blocks


An expression such as `x = 0` or `i++` or `printf(...)` becomes a statement
when it is followed by a semicolon, as in:

```
x = 0;
i++;
printf(...);
```


In C, the semicolon is a statement terminator, rather than a sperator.


Braces { and } are used to group declarations and statements together into a
**compunds statement**, or **block**, so that they are syntactically 
equivalent to a single statement. The braces that surround the statements of
a function are one obvious example; braces around multiple statements after
and if, else, while, or for are another. There is no semicolon after the 
right brace that ends a block.


## 3.2 If-Else


The if-else statement is used to express decisions. Formally, the syntax is:

```
if (expression)
    statement1
else
    statement2
```

where else part is optional. The expression is evaluated; if it is true (that
is, if expression has a non-zero value), statement1 is executed. If it is 
false (expression is zero) and if there is an else part, statement2 is 
executed instead.


Since an if simply tests the numeric value of an expression, certain coding
shortcuts are possible. The most obvious is writing:

```
if (expression)
```
instead of 
```
if (expression != 0)
```


The identation shows unequivocally what you want, but the compiler doesn't
get the message, and associates the else with the inner if. This kind of
bug can be hard to find; it's a good idea to use braces when there are 
nested ifs.


## 3.3 Else-If


The construction:

```
if (expression)
    statement1
else if (expression)
    statement2
else
    statement3
```


occurs often. This sequence of if statements is the most general way of 
writing a multi-way decision. The expression are evaluated in order; if any
expression is true, the statement associated with it is executed, and this
terminates the whole chain.


To illustrate a three-way decision, here is a binary search function that 
decides if a particular value x occurs in the sorted array v. The elements of
v must be in increasing order. The function returns the position (a number
between 0 an n-1) if x occurs in v, and -1 if not.


Binary search first compares the input of value x to the middle element of
the array v. If x is less than the middle value, searching focuses on the
lower half of the table, otherwise on the upper hald. In either case, the
next step is to compare x to the middle element of the selected half. This 
process of dividing the range in two continues until the value is found
or the range is empty.


**Program**[binary search](code/binary_search.c)


The fundamental decision is whether x is less than, greater than, or equal
to the middle element v[mid] at each step; this is a natural for else-if.


## 3.4 Switch


The switch statement is a multi-way decision that tests whether an expression
matches one of a number of **constant** integer values, and branches 
accordingly:

```
switch (expression) {
    case const-expr: statements
    case const-expr: statements
    default: statements
}
```


Each case is labeled by one or more integer-valued constants or constant
expresisons. If a case matches the expression value, execution starts at that
case. All case expressions must be different. The case labeled *default*
is optional; if it isn't there and if none of the cases match, no action at
all takes place. Cases and the default clause can occur in any order.


Here is an example:


**Program**[switch example](code/switch_ex.c)


The **break** statement causes an immediate exit from the *switch*. Because
cases server just as labels, after the code for one case is done, execution 
falls through to the next unless you take explicit action to escape. Break
and **return** are the most common ways to leave a *switch*. A break
statement can also be used to force an immediate exit form while, for and do
loops, as will be discussed later in the chapter.


Falling through cases is a mixed blessing. On the positive side, it allows
several cases to be attached to a single action, as with the digits in this
example. But it also implies that normally each case must end with a break to
prevent falling through to the next. Falling through from one case to another
is not robust, being prone to disintegration when the prorgam is modified.
With hte exception of multiple labels for a single computation, fall-throughs
should be used sparingly, and commented.


As a matter of good form, put a break after the last case (the default here)
even though it's logically unnecessary. Some day when another case gets
added at the end, this bit of defensive programming will save you.


## 3.5 Loops - While and For


We have already encountered the *while* and *for* loops. In:
```
while (expression)
    statement
```
the expression is evaluated. If it is non-zero, statement is executed and
expression is re-evaluated. This cycle continues until expression becomes
zero, at which point execution resumes after statement.


The *for* statement :
```
for (expr1; expr2; expr3)
    statement
```
is equivalent to:
```
expr1;
while (expr2) {
    statement
    expr3;
}
```
except for the behaviour of continue.


Gramatically, the three components of a for loop are expressions. Most 
commonly, expr1 and expr3 are assignments or function calls and expr2 is a
relational expression. Any of the three parts can vbe omitted, although
the semicolons must remain. If expr1 or expr3 is omitted, it is simply
dropped from the expansion. If the test, expr2, is not present, it is
taken as permanently true, so:

```
for (;;) {
    ...
}
```
is an "infinite" loop, presumably to be broken by other means, such as a 
break or return.


The advantages of keeping loop control centralized are even more obvious
when there are several nested loops. The following function is a Shell sort
for sorting an array of integers. The basic idea of sorting algorithm, which
was invented in 1959 by D. I. Shell, is that in early stages, far-apart 
elements are compared, rather than adjacent ones as in simpler interchange
sorts. This tends to eliminate large amounts of disorder quickly, so later
stages have less work to do. The interval between compared elements is
gradually decreased to one, at which point the sort effectively becomes
an adjacent interchange method.


**Program**[Shell sort](code/shell_sort.c)


There are three nested loops. The outermost controls the gap between compared
elements, shrinking it from n/2 by a factor of two each pass untill it 
becomes zero. The middle loop steps along the elements. The innermost
loop compares each pair of elements that is separated by *gap* and reverses
any that are out of order. Since *gap* is eventually reduced to one, all 
elements are eventually ordered correctly. Notice how the generality of the
for makes the outer loop fit the same form as the others, even though it is 
not an arithmetic progression.


One finaly C operator is the comma ",", which most often finds use in the
for statement. A pair of expressions separated by a comma is evaluated 
left to right, and the type and value of the result are the type and value
of th right operand. Thus in a for statement, it is possible to place 
multiple expressions in the various parts, for example to process two indices
in parallel. This is illustrated in the function *reverse(s)*, which reverses
the string s in place.


**Program**[Reverse string](code/reverse_string.c)


The commas that separate function arguments, variables in declarations, etc.,
are not comma operators, and do not guarantee left to right evaluation.


Comma operators should be used sparingly. the most suitable uses are for 
constructs strongly related to each other, as in the for loop in reverse, and
in macros where a multistep computation has to be a single expression. A comma
expression might also be appropriate for the exchange of elements in reverse,
where the exchange can be thought of as a single operation:

```
for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    c = s[i], s[i] = s[j], s[j] = c;
```


## 3.6 Loops - Do-While


The while and for loops test the termination condition at the top. By contrast
the third loop in C, the *do-while*, tests at the bottom *after* making each
pass through the loop body; the body is always executed at least once.


The syntax is:
```
do
    statement
while (expression)
```


The statement is executed, then expression is evaluated. If it is true,
statement is evaluated again and so on. When the expression becomes false, 
the loop terminates.


Experience shows that do-while is much less used than while and for. 
Nontheless, from time to time it is valuable, as in the following function
*itoa*, which converts a number to a character string (the reverse of *atoi*).
The job is slightly more complicated than might be thought at first, because
the easy methods of generating the digits generate them in the wrong order.
We have chosen to generate the string backwards, then reverse it.


**Program**[itoa](code/itoa.c)


The *do-while* is necessary, or at least convenient, since at least one
character must be installed in the array s, even if n is zero. We also used
braces around the single statement that makes up the body of the do-while,
even though they are unnecessary, so the hasty reader will not mistake the 
while part for the beginning of a while loop.


## 3.7 Break and Continue


It is sometimes convenient to be able to exit from a loop other than by
testing at the top or bottom. The break statement provides an early exit from
for, while, and do, just as from switch. A break causes the innermost
enclosing loop or switch to be exited immediately.


The following function, trim, removes traling blanks, tabs, and newlines from
the end of a string, using a break to exit from a loop when the rightmost
non-blank, non-tab, non-newline is found.


**Program**[trim](code/trim.c)


strlen return the length of the string. The for loop starts at the end and 
scans backwards looking for the first character that is not a blank or tab
or newline. The loop is broken when one is found, or when n becomes negative
(that is, when the entire string has been scanned). You should verify that
this is correct behavior even when the string is empty or contains only white
space characters.


The continue statement is related to break, but less often used; it causes
the next iteration of the enclosing for, while, or do loop to begin. In the
while and do, this means that the test part is executed immediately; in the
for, control passes to the increment step. The continue statement applies
only to loops, not to switch. A continue inside a switch inside a loop causes
the next loop iteration.


As an example, this fragment processes only the non-negative elements in the
array a; negative values are skipped:

```
for (i = 0; i < n; i++) {
    if (a[i] < 0)
        continue;
    ...
}
```


The continue statement is often used when the part of the loop that follows is
complicated, so that reversing a test and indenting another level would nest
the program too deeply.
