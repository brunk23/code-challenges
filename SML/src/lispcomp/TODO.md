lisp style code that will compile to SML instructions

(defun y (a b)
   (input c)
   (+ a (\* b c)))
(print (y 3 5))

Will create 3 variables, with scope local to y
Will create one funtion y that takes 3 arguments

push 3
push 5
call y
store tmp
print tmp
halt
y: pop b
   pop a
   input c
   push a
   load b
   mult c
   pop-add (a = stack + a)
   ret 
   a: --
   b: --
   c: --
tmp:

Simulator will support pop-add, pop-sub, etc. These variations which use the
pop into A instruction with the lower half of the instruction set to the
instruction code required.  pop-sub is the same as acc = stack - acc

All functions leave their results on the accumulator.

(+ 5 (- 8 4) 7)

will load 5 and push it, it will load 8, subtract 4, then pushadd that to the stack. Then pop the stack and add 7
