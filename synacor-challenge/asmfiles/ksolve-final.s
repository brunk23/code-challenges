	;; This will solve a given krypto puzzle, if it has a solution
	;; It will print out all the solutions and the steps you need to
	;; take in order.
	;; You enter the 5 numbers first and then the goal number last

	.origin 0

	;; Locations of our value arrays
	.assign	finalv	1209	; should be val +9
	.assign val	1200	; 4 words

	;; Locations of all our strings
	.assign	stri	1220	; should be val +20
	.assign	finals	1274	; should be val +74
	.assign progtop	1320	; should be val +120 (46 more than finals)

	;; main() -- The following code implements main()
	set	r1	prompt		; the prompt for the user
	call	pstr			; print it
	set	r7	6		; count of numbers to read
	set	r0	wordstrs	; where to save the strings
	rmem	r0	r0		; get the index
	set	r6	game_nums	; where to store the numbers
get_nums:
	call	readnum			; read a number
	jf	r1	bad_num		; zero is not allowed as a number
	gt	r5	r1	99	; two digit numbers only
	jt	r5	bad_num		; so get a new number
	wmem	r6	r1		; store it in the current location
	add	r6	r6	1	; point to next location
	call	num2str			; saves r1 as a string to r0
	add	r0	r0	3	; increment to next location
	add	r7	r7	32767	; decrement counter
	jt	r7	get_nums	; loop while r7 > 0
	set	r0	4		; We enter find_solution with n=4
	call	find_solution		; This does all the work
	halt
bad_num:
	set	r1	emesg		; the number was out of range
	call	pstr			; print error message and try again
	jmp	get_nums


	;; find_solution() -- Does not need to preserve any registers
	;; Expects:
	;;   r0 is the counter coming in, which we use to control the
	;;      recursion and the index into the various arrays
find_solution:
	;; Check if this is the last value
	jt	r0	find_solution_main	; If we have 1 number, we
	rmem	r1	finalv			; avoid the double read
	rmem	r2	goal			; get the goal value
	eq	r1	r1	r2		; are we equal
	jf	r1	find_solution_done	; if not, quit

	;; This was the right answer, we check the old strings to make
	;; sure we haven't printed it already. If we haven't, we save
	;; it to the list of strings seen and print it.
	set	r1	finals			; final string to print
	set	r0	32744			; solutions stored at top of memory
find_solution_check:
	rmem	r2	r0			; read the value at r0
	jf	r2	find_solution_new	; this was a brand new string
	set	r4	r0			; r4 and r5 need to point to
	set	r5	r1			; the strings to compare

	;; This will compare each string
strcmp_loop:
	rmem	r6	r4		; read a char
	rmem	r3	r5		; read a char
	eq	r7	r6	r3	; compare the two values
	jf	r7	strcmp_done	; quit if unequal
	jf	r6	strcmp_done	; quit if r6 is 0 (r3 is also 0)
	add	r4	r4	1	; next char
	add	r5	r5	1	; next char
	jmp	strcmp_loop
strcmp_done:

	jt	r7	find_solution_done	; this is a duplicate quit
	add	r0	r0	32745		; check next string 23 below this
	gt	r2	progtop	r0		; stay above the program
	jt	r2	find_solution_new	; or overflow and don't save string
	jmp	find_solution_check
find_solution_new:
	call	pstr			; print the answer string
	out	10			; print a newline
	jf	r2	find_solution_norm
	push	r1			; We overflowed and stopped checking
	set	r1	overflow	; for duplicates, print warning.
	call	pstr
	pop	r1
find_solution_norm:
	set	r2	r1		; save it in the buffer
	set	r1	r0		; so we don't print it twice
	call	append_str		; this works like strcpy here
	jmp	find_solution_done	; then print it and return

	;; The main body of find_solution starts here. This works through
	;; every possible combination and calls the try_ functions.
find_solution_main:
	set	r1	r0		; outer loop is r0-1 to 0
out_body:
	add	r1	r1	32767	; decrement outer loop counter
	set	r2	r0		; set inner loop counter to r0
in_body:
	;; copy_array()
	;;
	;; This will copy the array contents, except for the numbers
	;; currently being picked as the two active numbers. Those will
	;; be stored as the array[n-1][0] values
	;;
	;; Expects:
	;;   set r0 n  -- index of array
	;;   set r1 a  -- index of first number
	;;   set r2 b  -- index of second number
	;;
	;; Only preserves r0, must not change r1 and r2.
	;; Doesn't save r1 and r2, but also doesn't change them
	;; copy_array:
	push	r0
	jf	r0	copy_array_done		; we are done if this is zero
	add	r3	valsaddr	r0	; Get addr of source values
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
	eq	r7	r0	r1		; skip copy
	jt	r7	copy_array_skip
	eq	r7	r0	r2		; skip copy
	jt	r7	copy_array_skip
	rmem	r7	r3			; read source value
	wmem	r5	r7			; write to destination
	rmem	r7	r4			; read source string
	wmem	r6	r7			; write to destination
	add	r5	r5	32767		; r5--
	add	r6	r6	32767		; r6--
copy_array_skip:
	jf	r0	copy_array_done		; we copied the last value
	add	r0	r0	32767		; r0--
	add	r3	r3	32767		; r3--
	add	r4	r4	32767		; r4--
	jmp	copy_array_loop
copy_array_done:
	pop	r0

	;; We need to find a sum, and create the string
	;; Expects:
	;;   r0 points to current array
	;;      (r0-1) points to the destination array
	;;   r1 and r2 are the indexes into our current arrays(string and val)
	;; Provides:
	;;   vals[r0-1][0] <- result
	;;   strs[r0-1][0] <- new string to get result
	;; Notes:
	;;   must decrement r0 before calling find_solution at the end
	;;   try_diff, try_mult, and try_div function the same way
	;;   must preserve r0, r1, and r2 for when we return to find_solution
	;; try_sum:
	push	r0
	push	r1
	push	r2
	call	setup_vals		; r6, r7 <- values, r5 <- dest
	add	r7	r7	r6	; add them both together
	wmem	r5	r7		; store it at the start of the array
	set	r3	plus		; The addition string
	call	generate_string		; generate the string
	add	r0	r0	32767	; decrement before calling find_solution
	call	find_solution
	pop	r2
	pop	r1
	pop	r0

	;; try_diff:
	push	r0
	push	r1
	push	r2
	call	setup_vals		; r6, r7 <- values, r5 <- dest
	mult	r6	r6	32767	; make r6 negative
	add	r7	r7	r6	; subtract them
	wmem	r5	r7		; store it at the start of the array
	set	r3	minus		; The subtraction string
	call	generate_string		; generate the string
	add	r0	r0	32767	; decrement before calling find_solution
	call	find_solution
	pop	r2
	pop	r1
	pop	r0

	;; try_mult:
	push	r0
	push	r1
	push	r2
	call	setup_vals		; r6, r7 <- values, r5 <- dest
	mult	r7	r7	r6	; multiply them both together
	wmem	r5	r7		; store it at the start of the array
	set	r3	times		; The multiplication string
	call	generate_string		; generate the string
	add	r0	r0	32767	; decrement before calling find_solution
	call	find_solution
	pop	r2
	pop	r1
	pop	r0

	;; try_div:
	push	r0
	push	r1
	push	r2
	call	setup_vals		; r6, r7 <- values, r5 <- dest
	jf	r6	try_div_fail	; don't divide by zero, quit this attempt
	mod	r3	r7	r6	; a remainder is not allowed
	jt	r3	try_div_fail	; quit this attempt
	push	r1			; divide uses r1 and r2
	push	r2			; and we don't want to lose them
	set	r1	r7		; this will set them up right
	set	r2	r6		; for the divide
	call	divide			; actually do the division
	wmem	r5	r1		; store it at the start of the array
	pop	r2			; restore r2
	pop	r1			; and r1
	set	r3	divid		; the division string
	call	generate_string		; generate the string
	add	r0	r0	32767	; decrement before calling find_solution
	call	find_solution
try_div_fail:
	pop	r2
	pop	r1
	pop	r0

	;; Back to the main body loop for find_solution
	add	r2	r2	32767	; decrement inner loop counter
	eq	r4	r2	r1	; compare r2 to r1, as that is the end cond
	jf	r4	in_body		; inner loop is r0 to r1
	jt	r1	out_body	; while not 0, loop back again

find_solution_done:
	ret


	;; This sets up the values for each try_ function
	;; Expects:
	;;   r0 is the depth we are at
	;;   r1 and r2 are the indexes we need from that array
	;; Returns:
	;;   r7 is the larger number
	;;   r6 is the smaller number
	;;   r1 is the larger number's index
	;;   r2 is the smaller number's index
	;;   r5 is the destination for the answer
setup_vals:
	set	r7	valsaddr	; address of vals[][]
	add	r7	r7	r0	; index to current array
	add	r5	r7	32767	; r5 = destination address
	rmem	r7	r7		; read address of current array
	rmem	r5	r5		; read address of destination array
	add	r6	r7	r2	; r6 is the second number
	add	r7	r7	r1	; r7 is first number
	rmem	r7	r7		; read first number
	rmem	r6	r6		; read second number
	gt	r4	r6	r7	; we need to switch r1 and r2
	jf	r4	setup_vals_done
	set	r4	r1		; reverse the index for strings
	set	r1	r2		; because we want to print correctly
	set	r2	r4		; no matter what
	set	r4	r6		; make the larger value first
	set	r6	r7		; for all math operations
	set	r7	r4		; it is easier
setup_vals_done:
	ret


	;; This will generate each new string in the try_ blocks
	;; Expects:
	;;   r3 points to the operation string
	;;   r1 and r2 point to the numbers' indexes in order
	;; This does not preserve r1 and r2. They are saved in the try_
	;; functions and they are not used in those functions after this call
generate_string:
	set	r4	r1		; move r1 to r4
	set	r5	r2		; move r2 to r5
	add	r7	strsaddr	r0	; index it to the current
	add	r7	r7	32767	; Point to correct spot
	add	r1	strs	r0	; r5 = destination address
	add	r1	r1	32767	; get the address for the destinations str
	rmem	r1	r1		; the destination string array
	rmem	r7	r7		; read the current string array
	wmem	r7	r1		; put the address of new string in r1[0]
	add	r7	strsaddr	r0
	rmem	r7	r7		; get the address of the source array
	add	r6	r7	r4	; first string r7[r4]
	rmem	r6	r6
	add	r7	r7	r5	; second string r7[r5]
	rmem	r7	r7
	wmem	r1	40		; start with '('
	add	r1	r1	1	; increment
	wmem	r1	0		; null terminate
	set	r2	r6		; append the first string
	call	append_str
	set	r2	r3		; the operation
	call	append_str
	set	r2	r7		; append the second string
	call	append_str
	set	r2	closep		; end with ")\0"
	call	append_str
	ret

	.include	"utils/readnum.s"
	.include	"utils/bindivide.s"
	.include	"utils/pstr.s"
	.include	"utils/num2str.s"
	.include	"utils/append_str.s"

prompt:
	data	"Enter the 5 numbers followed by the goal number: \0"
emesg:	data	"Numbers must be between 1 and 99 inclusive.\n\0"
overflow:
	data	"Overflow!\n\0"

	;; We use these strings for printing the results.
closep:	data	")\0"
plus:	data	"+\0"
minus:	data	"-\0"
times:	data	"*\0"
divid:	data	"/\0"

	;; These will be used to pass the array addresses.
valsaddr:
	data	finalv	val+7	val+4	val	game_nums
strsaddr:
	data	val+19	val+17	val+14	val+10	wordstrs

	;; These will be the string locations.
wordstrs:
	data	stri	stri+3	stri+6	stri+9	stri+12
strs:	data	finals	stri+36	stri+23	stri+15	; first, second, third, final
game_nums:
	data	0	0	0	0	0
goal:	data	0
