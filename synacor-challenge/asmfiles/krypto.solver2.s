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
	set	r0	4		; We enter find_solution with n=4
	call	find_solution
	halt


	;; find_solution() -- Does not need to preserve any registers
	;; Needs to do "ab ac ad ae bc bd be cd ce de" and all the variations
	;; Under that.
find_solution:
	eq	r7	r0	1
	jt	r7	find_solution_done
	set	r1	0
	set	r2	1
	call	copy_array
	add	r0	r0	32767
	call	find_solution
find_solution_done:
	ret

	;; copy_array()
	;;
	;; This will copy the array contents, except for the numbers
	;; currently being picked as the two active numbers. Those will
	;; be stored as the array[n-1][0] values
	;;
	;; Call method:
	;;   set r0 n  -- index of array
	;;   set r1 a  -- index of first number
	;;   set r2 b  -- index of second number
	;;   call copy_array
	;;
	;; Preserves all registers.  Doesn't save r1 and r2, but
	;; also doesn't change them
copy_array:
	push	r0
	push	r3
	push	r4
	push	r5
	push	r6
	push	r7
	jf	r0	copy_array_done		; we are done if this is zero
	add	r3	valsaddr	r0 	; Get addr of source values
	add	r5	r3	32767		; Get addr of dest values
	rmem	r3	r3			; r3 <- source values
	add	r3	r3	r0		; point to last value
	rmem	r5	r5			; r5 <- dest values
	add	r5	r5	r0		; point to last value
	add	r5	r5	32767		; which is one less than n
	add	r4	strsaddr	r0	; Get addr of source string
	add	r6	r4	32767		; Get addr of dest strings
	rmem	r4	r4			; r4 <- source strings
	add	r4	r4	r0		; point to last address
	rmem	r6	r6			; r6 <- dest strings
	add	r6	r6	r0		; pint to last string
	add	r6	r6	32767		; one less than n
copy_array_loop:
	eq	r7	r0	r1    		; skip copy
	jt	r7	copy_array_skip
	eq	r7	r0	r2    		; skip copy
	jt	r7	copy_array_skip
	rmem	r7	r3	      		; read source value
	wmem	r5	r7			; write to destination
	rmem	r7	r4			; read source string
	wmem	r6	r7			; write to destination
copy_array_skip:
	jf	r0	copy_array_done		; we copied the last value
	add	r0	r0	32767		; r0--
	add	r3	r3	32767		; r3--
	add	r4	r4	32767		; r4--
	add	r5	r5	32767		; r5--
	add	r6	r6	32767		; r6--
	jmp	copy_array_loop
copy_array_done:
	pop	r7
	pop	r6
	pop	r5
	pop	r4
	pop	r3
	pop	r0
	ret

	.include	"utils/readnum.s"
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

	;; We use these strings for printing the results.
openp:	data	"(\0"
closep:	data	")\0"
plus:	data	"+\0"
minus:	data	"-\0"
times:	data	"*\0"
divid:	data	"/\0"

	;; These will be used to pass the array addresses.
valsaddr:
	data	9009	9007	9004	9000	game_nums
strsaddr:
	data	9019	9017	9014	9010	wordstrs

	;; These will be the string locations. This begs two possible
	;; improvements to the assembler.  The ability to use equ statements
	;; like "first equ 10000" and compiled math like "first+3" to create
	;; 10003 automatically.
wordstrs:
	data	10000	10003	10006	10009	10012
strs:	data	10115	10123	10136	10154 ; first, second, third, final
