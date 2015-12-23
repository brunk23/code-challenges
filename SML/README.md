SML

This is the SML (Simpltron Machine Language) simulator and compiler that
I have created.  It is based on the model suggested by Deital and Deital
in their book.  I have made some extensions to the language and might make
more.

The simulator is written in C++. It is pretty basic. You can load a file,
created by hand or with the compiler, by typing its name after the simulator
command. There are some problems, like improperly handling bad input and
not respecting or warning about out of value items. But, it functions as
expected according to the book.

The compiler is written in C, not C++.  Why?  No real reason, aside from the
fact that I wanted to make sure I still remembered enough of the way C does
things to complete the project in that language.  The compiler currently supports
the following commands:

rem -- a comment
input -- read a value from the user
print -- print a value
let -- variable = expression
if -- variable/constant condition variable/constant

expressions can consist of: +, -, \*, /, % and ( )s
conditions accepted are: ==, !=, <, <=, >, >=

All variables are a single letter, everything is case-sensitive (lower-case only).
