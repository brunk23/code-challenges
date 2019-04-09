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
	set	r7	4
try_i:				; do {
	add	r7	r7	32767
	set	r6	4
try_j:				; do {
	add	r6	r6	32767
	set	r5	4
try_k:				; do {
	add	r5	r5	32767
	set	r4	4
try_m:				; do {
	add	r4	r4	32767
	call	get_value		; r3 = value
	set	r1	goal		; r1 = &goal
	rmem	r1	r1		; r1 = &goal
	eq	r1	r1	r3	; are they equal?
	jf	r1	no_print_match
	call	print_match
	out	10
no_print_match:
	jt	r4	try_m		; } while(r4)
	jt	r5	try_k		; } while(r5)
	jt	r6	try_j		; } while(r6)
	jt	r7	try_i		; } while(r7)
	pop	r7
	pop	r1
	pop	r0
	ret

	;; Must preserve r4, r5, r6, r7
	;; Can we avoid touching them?
	;; 1 = +, 2 = *, 3 = -, 4 = /
	;; WARNING {Black Magic} ret here returns to other functions!
get_value:
	set	r0	game_nums
	add	r3	value_ops	r4	; Fourth operation
	rmem	r3	r3			; Read the function address
	push	r3				; Push it
	add	r3	value_ops	r5	; Third operation
	rmem	r3	r3			; Read the function address
	push	r3				; Push it
	add	r3	value_ops	r6	; Second operation
	rmem	r3	r3			; Read the function address
	push	r3				; Push it
	add	r3	value_ops	r7	; First operation
	rmem	r3	r3			; Read the fucntion address
	push	r3				; Push it
	rmem	r3	r0			; r3 <- first value
	add	r0	r0	1	 	; point to next number
get_value_error:
	ret					; Return calls 1st operation function

val_add:
	eq	r1	r3	32767	  	; Error
	jt	r1	get_value_error		; Return right away
	rmem	r2	r0			; Read next number
	add	r3	r3	r2		; Add it to r3 (value)
	add	r0	r0	1		; point to next number
	ret

val_sub:
	eq	r1	r3	32767		; Error
	jt	r1	get_value_error		; Return right away
	rmem	r2	r0			; Read the next number
	add	r0	r0	1 		; Point to next number
	gt	r1	r2	r3
	jt	r1	val_sub_2
	mult	r2	r2	32767 		; subtract r2
	add	r3	r3	r2
	ret
val_sub_2:
	mult	r3	r3	32767 		; subtract r3
	add	r3	r3	r2
	ret

val_mul:
	eq	r1	r3	32767		; Error
	jt	r1	get_value_error		; Return right away
	gt	r1	r3	1280		; Check for potential overflow
	jf	r1	val_mul2		; Don't allow it
	set	r3	32767
	jmp	get_value_error
val_mul2:
	rmem	r2	r0			; Read next number
	mult	r3	r3	r2		; r3 <- r3 * r2
	add	r0	r0	1		; point to next number1
	ret

val_div:
	eq	r1	r3	32767
	jt	r1	get_value_error
	rmem	r2	r0
	add	r0	r0	1
	mod	r1	r3	r2 		; r1 <- r3 mod r2
	jt	r1	val_div2
	set	r1	r3			; We divide r3 by r2
	call	divide
	set	r3	r1
	ret
val_div2:
	mod	r1	r2	r3
	jt	r1	val_div3
	set	r1	r2
	set	r2	r3
	call	divide
	set	r3	r1
	ret
val_div3:
	set	r3	32767
	ret

	;; Must preserve r7, r6, r5, r4
	;; More black magic
print_match:
	set	r0	game_nums
	add	r3	print_ops	r4	; Fourth operation
	rmem	r3	r3			; Read the function address
	push	r3				; Push it
	add	r3	print_ops	r5	; Third operation
	rmem	r3	r3			; Read the function address
	push	r3				; Push it
	add	r3	print_ops	r6	; Second operation
	rmem	r3	r3			; Read the function address
	push	r3				; Push it
	add	r3	print_ops	r7	; First operation
	rmem	r3	r3			; Read the fucntion address
	push	r3				; Push it
	rmem	r3	r0			; r3 <- first value
	add	r0	r0	1	 	; point to next number
	ret					; Return calls 1st operation function

pri_add:
	out	40		   		; '('
	set	r1	r3
	call	pnumber
	out	43		   		; '+'
	rmem	r2	r0			; Read next number
	add	r3	r3	r2		; Add it to r3 (value)
	add	r0	r0	1		; point to next number
	set	r1	r2
	call	pnumber
	out	41				; ')'
	ret

pri_sub:
	out	40
	rmem	r2	r0			; Read the next number
	add	r0	r0	1 		; Point to next number
	gt	r1	r2	r3
	jt	r1	pri_sub_2
	set	r1	r3
	call	pnumber
	out	45
	set	r1	r2
	call	pnumber
	out	41
	mult	r2	r2	32767 		; subtract r2
	add	r3	r3	r2
	ret
pri_sub_2:
	set	r1	r2
	call	pnumber
	out	45		      ; '-'
	set	r1	r3
	call	pnumber
	out	41
	mult	r3	r3	32767 		; subtract r3
	add	r3	r3	r2
	ret

pri_mul:
	out	40
	set	r1	r3
	call	pnumber
	out	42
	rmem	r2	r0			; Read next number
	set	r1	r2
	call	pnumber
	out	41
	mult	r3	r3	r2		; r3 <- r3 * r2
	add	r0	r0	1		; point to next number1
	ret

pri_div:
	out	40
	rmem	r2	r0
	add	r0	r0	1
	mod	r1	r3	r2 		; r1 <- r3 mod r2
	jt	r1	pri_div2
	set	r1	r3
	call	pnumber
	out	47
	set	r1	r2
	call	pnumber
	set	r1	r3			; We divide r3 by r2
	call	divide
	set	r3	r1
	out	41
	ret
pri_div2:
	set	r1	r2
	call	pnumber
	out	47
	set	r1	r3
	call	pnumber
	set	r1	r2
	set	r2	r3
	call	divide
	set	r3	r1
	out	41
	ret

	.include	"utils/readnum.s"
	.include	"utils/pnumber.s"
	.include	"utils/bindivide.s"
	.include	"utils/pstr.s"

prompt:
	data	"Enter the 5 numbers followed by the goal number: \0"
value_ops:
	data	val_add	val_sub	val_mul	val_div
print_ops:
	data	pri_add	pri_sub	pri_mul	pri_div
game_nums:
	data	0	0	0	0	0
goal:	data	0
c:	data	0	0	0	0	0
