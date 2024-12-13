	;; This will solve a given krypto puzzle, if it has a solution
	;; It will print out all the solutions and the steps you need to
	;; take in order.
	;; You enter the 5 numbers first and then the goal number last

	.origin 0

	;; main() -- The following code implements main()
	set	r1	prompt		; the prompt for the user
	call	pstr			; print it
	set	r7	6		; count of numbers to read
	set	r0	wordstrs	; where to save the strings
	rmem	r0	r0		; get the index
	set	r6	game_nums	; where to store the numbers
get_nums:
	call	readnum			; read a number
	jf	r1	get_nums	; zero is not allowed as a number
	wmem	r6	r1		; store it in the current location
	add	r6	r6	1	; point to next location
	call	num2str			; saves r1 as a string to r0
	add	r0	r0	3	; increment to next location
	add	r7	r7	32767	; decrement counter
	jt	r7	get_nums	; loop while r7 > 0
	set	r0	4		; We enter find_solution with n=4
	call	find_solution		; This does all the work
	halt


	;; find_solution() -- Does not need to preserve any registers
	;; Expects:
	;;   r0 is the counter coming in, which we use to control the
	;;      recursion and the index into the various arrays
find_solution:
	;; Check if this is the last value
	jt	r0	find_solution_main	; If we have 1 number, we
	rmem	r1	2009			; avoid the double read
	rmem	r2	goal			; get the goal value
	eq	r1	r1	r2		; are we equal
	jf	r1	find_solution_done	; if not, quit

	;; This was the right answer, we check the old strings to make
	;; sure we haven't printed it already. If we haven't, we save
	;; it to the list of strings seen and print it.
	set	r1	2074			; final string to print
	add	r0	r1	23		; solutions stored after 2074
find_solution_check:
	rmem	r2	r0			; read the value at r0
	jf	r2	find_solution_new	; this was a brand new string
	call	strcmp				; compare strings r0 and r1
	jt	r7	find_solution_done	; this is a duplicate quit
	add	r0	r0	23		; check next string
	jmp	find_solution_check
find_solution_new:
	call	pstr			; print the answer string
	out	10			; print a newline
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
	call	copy_array		; copy the arrays
	call	try_sum
	call	try_diff
	call	try_div
	call	try_mult
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
try_sum:
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
	ret


try_diff:
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
	ret


try_mult:
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
	ret


try_div:
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
	;; Only preserves r0, must not change r1 and r2.
	;; Doesn't save r1 and r2, but also doesn't change them
copy_array:
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
	ret


	;; Invoke: call strcmp
	;; Inputs: r0 <- string1  r1 <- string2
	;; Outputs: r7 = 1, if equal, 0 if not
strcmp:
	push	r0
	push	r1
	push	r2
	push	r3

strcmp_loop:
	rmem	r2	r0		; read a char
	rmem	r3	r1		; read a char
	eq	r7	r2	r3	; compare the two values
	jf	r7	strcmp_done	; quit if unequal
	jf	r2	strcmp_done	; quit if r2 is 0 
	jf	r3	strcmp_done	; quit if r3 is 0
	add	r0	r0	1	; next char
	add	r1	r1	1	; next char
	jmp	strcmp_loop

strcmp_done:
	pop	r3
	pop	r2
	pop	r1
	pop	r0
	ret


	;; This will read the next number from input
	;; Invoke: call readnum
	;; Inputs: none
	;; Outputs: r1 will contain the value of the number entered on stdin
	;;	or 0, if no number was read.
readnum:
	push	r2
	push	r7
	set	r1	0		; start with r1 = 0
rnum01:	in	r2			; get the next ascii char
	add	r2	r2	32720	; subtract '0'
	gt	r7	r2	9	; was the value a digit?
	jt	r7	rnum02		; if not, quit
	mult	r1	r1	10	; move the old digit over
	add	r1	r1	r2	; add this value
	jmp	rnum01
rnum02:	pop	r7
	pop	r2
	ret


	;; This will use binary to divide
	;; Invoke: call divide
	;; Inputs:  r1 <- dividend, r2 <- divisor
	;; Outputs:  r1 <- quotient, r2 <- remainder
divide:
	;; We start off by finding early return conditions. We can return
	;; right away if we are dividing a 0, or by 1. This saves a marginal
	;; amount of time
	jt	r1	divide_notzero
	set	r2	0
	ret
divide_notzero:
	push	r7
	gt	r7	r2	1	; If we divide by 1 or 0, just return right away
	jt	r7	divide_start	; Dividing by more than 1, jump forward
	set	r2	0		; No remainder, don't change the dividend
	pop	r7			; restore the register
	ret				; return to main function

divide_start:
	push	r5
	push	r4
	push	r3

	;; We store possible factors on the stack
	push	0			; push 0 on the stack for when we are done
	set	r4	r2		; We first push r2 on the stack
	set	r5	1		; This is the power of 2
divide_findfactor:
	set	r3	r4		; save the old factor to see when we go over
	push	r5			; push the power of 2 we multiplied by
	push	r4			; push the next factor on the stack
	add	r4	r4	r4	; double the factor
	add	r5	r5	r5	; double the power of 2
	gt	r7	r4	r1	; is r4 > dividend
	gt	r3	r3	r4	; is the old number > the new number?
	or	r3	r3	r7	; Either one is a done situation
	jf	r3	divide_findfactor

	set	r3	0		; keep quotient in r6
divide_loop:
	pop	r4			; pop the factor we are testing
	jf	r4	divide_end	; We quit when we read a zero from the stack
	pop	r5			; pop the power of 2 for this factor
	gt	r7	r4	r1	; Is the factor greater than the remainder?
	jt	r7	divide_loop	; if so, don't do anything and loop
	mod	r1	r1	r4	; remove this factor from the dividend
	add	r3	r3	r5	; Add the current power of 2 to our quotient
	jmp	divide_loop		; Return to the loop

divide_end:
	set	r2	r1	; save remainder in r2
	set	r1	r3	; save quotient in r1
	;; restore other registers
	pop	r3
	pop	r4
	pop	r5
	pop	r7
	ret


	;; prints null terminated string starting at r1
	;; Invoke: call pstr
	;; Inputs: r1 <- address of first character of null terminated string
	;; Outputs: values printed as characters to stdout, no register changes
pstr:
	push	r0
	push	r1
p001:	rmem	r0	r1		; read the digit to print
	jf	r0	p002		; jump to the end if zero
	out	r0			; if not, print it to output
	add	r1	r1	1	; point to the next digit
	jmp	p001			; loop back to start
p002:
	pop	r1
	pop	r0
	ret


	;; This will turn the number in r1 into a str at r0
	;; Invoke: call pnumber
	;; Inputs: r1 <- number to print
	;; Outputs: r0 <- address of string
num2str:
	; Preserve all the changed registers for code reuse
	push	r0
	push	r1
	push	r2
	push	r5

	set	r5	0		; pushed digits
num2str_a:
	set	r2	10		; We're dividing by 10
	call	divide			; r1 <- quotient, r2 <- remainder
	push	r2			; save remainder
	add	r5	r5	1	; increase pushed digits
	jt	r1	num2str_a	; if we still have digits, loop
num2str_b:
	pop	r1			; pop the value to print
	add	r1	r1	48	; add ascii 0
	wmem	r0	r1		; save it to the string
	add	r0	r0	1	; next character
	add	r5	r5	32767	; count of digits pushed -1
	jt	r5	num2str_b	; print the next digit if not 0
	wmem	r0	0		; null terminate it

	;; Restore all the registers before returning
	pop	r5
	pop	r2
	pop	r1
	pop	r0
	ret


	;; Returns new address of string
	;; Invoke: call append_str
	;; Inputs: r1 <- dest, r2 <- src
	;; Outputs: N/A
append_str:
	push	r1
	push	r2
	push	r3
	rmem	r3	r1
	jf	r3	append_str_loop
end_str:
	add	r1	r1	1	; point to next char
	rmem	r3	r1
	jt	r3	end_str
append_str_loop:
	rmem	r3	r2
	wmem	r1	r3
	add	r2	r2	1	; r2++
	add	r1	r1	1	; r1++
	jt	r3	append_str_loop
	pop	r3
	pop	r2
	pop	r1
	ret

prompt:
	data	"Enter the 5 numbers followed by the goal number: \0"
closep:	data	")\0"
plus:	data	"+\0"
minus:	data	"-\0"
times:	data	"*\0"
divid:	data	"/\0"
valsaddr:
	data	2009	2007	2004	2000	game_nums
strsaddr:
	data	2019	2017	2014	2010	wordstrs
wordstrs:
	data	2020  	2023	2026	2029	2032
strs:	data	2074	2056	2043	2035
game_nums:
	data	0	0	0	0	0
goal:	data	0
