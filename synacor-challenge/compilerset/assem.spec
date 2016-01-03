Assembly files will have the following format:
----------------------------------------------
# comments are everything after a #

.origin 00000           # will give an address where the next code goes

:label                  # all labels and variable names start with :

    jmp :label          # example (label needs to be resolved if unknown)

    add r1, 234, r0     # numbers are written directly into memory

:date
    data 0 0 4533 234 99  # everything after a data statement is written directly
    

    # registers start with r
