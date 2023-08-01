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
