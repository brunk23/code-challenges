Assembly files will have the following format:
----------------------------------------------
# comments are everything after a #

.origin 00000           # will give an address where the next code goes

:label                  # all labels and variable names start with :

    jmp :label          # example (label needs to be resolved if unknown)

    add r1, 234, r0     # numbers are written directly into memory

:data                   # <- is label :data not a data statement
    data 0 0 4533 234 99  # everything after a data statement is written directly
    

    # registers start with r
-- OPCODES and number of args --
add a b c
and a b c
call a
eq a b c
gt a b c
halt
in a
jf a b
jmp a
jt a b
-- LEFT OFF HERE --
mod a b c
mult a b c
nop
not a b
or a b c
out a
pop a
push a
ret
rmem a b
set a b
wmem a b
