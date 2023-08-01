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



