	;; This will solve a given krypto puzzle, if it has a solution
	;; It will print out all the solutions and the steps you need to
	;; take in order.
	;; You enter the 5 numbers first and then the goal number last

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
	call	find_solution
	halt


	;; find_solution() -- Does not need to preserve any registers
	;; r6 = &c[i] r5 = c[i], r4 = &a[i] r3 = a[i], r2 = tmp
	;; This is Heap's algorithm.
find_solution:
	set	r0	game_nums 	; r0 = a
	set	r1	c		; r1 = c
	set	r7	0		; r7 = i <- 0
	set	r0	buffer
	set	r1	25424
	call	num2str
	set	r2	r0
	set	r1	str
	call	append_str
	call	pstr
	ret

	;; This will decrement the print buffer.
zero_pbuffer:
	push	r0
	push	r1
	set	r0	70		; we have a 70 character
	set	r1	buffer		; print buffer
zero_pbuffer1:
	wmem	r1	0		; write nulls
	add	r1	r1	1	; increment address
	add	r0	r0	32767	; decrement counter
	jt	r0	zero_pbuffer1	; loop if not 0
	pop	r1
	pop	r0
	ret

	.include	"utils/readnum.s"
	.include	"utils/pnumber.s"
	.include	"utils/bindivide.s"
	.include	"utils/pstr.s"
	.include	"utils/prepend_str.s"
	.include	"utils/strlen.s"
	.include	"utils/num2str.s"
	.include	"utils/append_str.s"

prompt:
	data	"Enter the 5 numbers followed by the goal number: \0"
value_ops:
;;	data	val_add	val_mul	val_sub	val_div 
game_nums:
	data	0	0	0	0	0
goal:	data	0
c:	data	0	0	0	0	0

	;; Since we feed backwards for the string, we need
	;; this buffer area.
buffer:	data	0	0	0	0	0	0	0
	data	0	0	0	0	0	0	0
	data	0	0	0	0	0	0	0
	data	0	0	0	0	0	0	0
	data	0	0	0	0	0	0	0
	data	0	0	0	0	0	0	0
str:	data	" This is a test\0"
