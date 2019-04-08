	;; This will solve a given krypto puzzle, if it has a solution
	.origin 0
	;; main() -- The following code implements main()
	set	r1	prompt		; the prompt for the user
	call	pstr			; print it
	set	r7	6		; count of numbers to read
	set	r6	game_nums	; where to store the numbers
get_nums:
	call	readnum			; read a number
	wmem	r6	r1		; store it in the current location
	add	r6	r6	1	; point to next location
	add	r7	r7	32767	; decrement counter
	jt	r7	get_nums	; loop while r7 > 0
	call	try_all			; Try before we permute anything
	call	find_solution
	halt

	;; find_solution() -- Does not need to preserve any registers
	;; r6 = &c[i] r5 = c[i], r4 = &a[i] r3 = a[i], r2 = tmp
find_solution:
	set	r0	game_nums 	; r0 = a
	set	r1	c		; r1 = c
	set	r7	0		; r7 = i <- 0
permutation:				; while( i < 5 )
	add	r6	r1	r7
	rmem	r5	r6		; r5 = c[i]
	gt	r2	r7	r5	; i > c[i]
	jf	r2	perm_not_greater
	mod	r2	r7	2  	; r2 <- i%2
	jt	r2	perm_not_even
	add	r4	r0	r7 	; point to value at a[i]
	rmem	r2	r4		; r2 = a[i]
	rmem	r3	r0		; r3 = a[0]
	wmem	r0	r2		; a[0] = a[i]
	wmem	r4	r3		; a[i] = a[]
	jmp	try_perm
perm_not_even:	
	add	r6	r1	r7 	; r6 = &c[i]
	rmem	r6	r6		; r6 = c[i]
	add	r6	r6	r0	; r6 = &a[ c[i] ]
	add	r5	r0	r7	; r5 = &a[i]
	rmem	r4	r6		; r4 = a[ c[i] ]
	rmem	r3	r5		; r3 = a[ i ]
	wmem	r6	r3		; a[ c[i] ] = a[ i ]
	wmem	r5	r4		; a[ i ] = a[ c[i] ]
try_perm:
	call	try_all			; test this permutation for wins
	add	r5	r1	r7	; increment c[i]
	rmem	r4	r5
	add	r4	r4	1
	wmem	r5	r4		; and save it back
	set	r7	0
	jmp	while_bottom
perm_not_greater:
	add	r6	r1	r7 	; We didn't permute
	wmem	r6	0		; c[i] = 0
	add	r7	r7	1	; i++
while_bottom:
	gt	r2	5	r7 	; the while test condition is here
	jt	r2	permutation
	ret

	;; Not implemented yet -- Currently just prints the current permutation
	;; Must preserve r0, r1, and r7
try_all:
	push	r0
	push	r1
	push	r7
	set	r5	5
	set	r4	game_nums
try_loop:
	rmem	r1	r4
	call	pnumber
	out	9
	add	r4	r4	1
	add	r5	r5	32767
	jt	r5	try_loop
	out	10
	pop	r7
	pop	r1
	pop	r0
	ret


	.include	"utils/readnum.s"
	.include	"utils/pnumber.s"
	.include	"utils/bindivide.s"
	.include	"utils/pstr.s"

prompt:
	data	"Enter the 5 numbers followed by the goal number: \0"
game_nums:
	data	0	0	0	0	0
goal:	data	0
c:	data	0	0	0	0	0
ops:	data	0	0	0	0
