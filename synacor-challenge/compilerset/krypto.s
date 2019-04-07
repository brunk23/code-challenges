	;; The Krypto deck consists of 56 cards: three of each of the numbers
	;; 1-6, four each of the numbers 7-10, two each of 11-17, one each of
	;; 18-25. Six cards are dealt: a common objective card at the top and
	;; five other cards below. Each player must use all five of the cards'
	;; numbers exactly once, using any combination of arithmetic operations
	;; (addition, subtraction, multiplication, and division), to form the
	;; objective card's number. The first player to come up with a correct
	;; formula is the winner.

	;; Krypto International Rules specify the use of whole numbers only,
	;; using addition, subtraction, division, multiplication and/or any
	;; combination thereof ... fractions, negative numbers or square
	;; rooting are not permitted. Each of the five cards must be used once
	;; and only once. 

	;; TODO: write a separate "solver" program for these games in synacor
	set	r1	start_message
	call	pstr
again:
	rmem	r0	games_left_num
	set	r1	games_left
	call	pstr
	set	r1	r0
	call	pnumber
	out	10
	call	main
	add	r0	r0	32767
	wmem	games_left_num	r0
	jt	r0	again
end_game:
	set	r1	quit_message
	call	pstr
	rmem	r1	win_count
	call	pnumber
	set	r1	quit_message2
	call	pstr
	rmem	r0	games_left_num
	mult	r0	r0	32767
	add	r0	r0	10
	set	r1	r0
	call	pnumber
	out	10
	halt

	;; Only preserves r0, it is the only register that the
	;; calling function needs preserved.
	;; Destroys r1, r2, r3, r7 {Possibly r4, r5, r6}
main:
	push	r0
	set	r0	4		; Number of moves
	call	pick_six		; get our six numbers
input:
	call	parse_input
	rmem	r1	first_let 	; offset of first word
	rmem	r2	second_let	; offset of second word
	eq	r7	r1	r2	; if they are the same,
	jt	r7	input		; we loop back
	set	r3	game_numbers	; point to the start of the game_numbers
	add	r3	r3	r1	; add the offset
	rmem	r1	r3		; read the value
	eq	r7	r1	9973 	; Is this a valid word?
	jt	r7	input		; if Not we quit and loop
	set	r3	game_numbers	; point to the start of the game_numbers
	add	r3	r3	r2	; add the offset
	rmem	r2	r3		; read the value
	eq	r7	r2	9973	; is this a valid word?
	jt	r7	input		; if not we quit and loop
	rmem	r3	command		; get the address for the command
	call	r3			; call it
	jt	r0	input		; Loop if we have operations left to go
	call	win_lose		; check if we won
	pop	r0
	ret

	;; Called from main. This does not need to preserve any registers
	;; Destroys r0, r1, r2
win_lose:
	set	r0	5		; We grab the goal number first
	set	r1	game_numbers	; we index off this address
	add	r1	r1	r0	; Get the memory address
	rmem	r2	r1		; r2 = the goal
next_value:
	add	r0	r0	32767 	; decrement i
	set	r1	game_numbers	; point to the values we played with
	add	r1	r0	r1	; add the index
	rmem	r1	r1		; read the value into r1
	eq	r1	r1	r2	; if r2 == r1
	jt	r1	won		; we won
	jt	r0	next_value	; if not, check the next value
	set	r1	lose_text	; we didn't have any values that matched
	call	pstr			; print the lose string
	ret

	;; This is a helper for win_lose and prints a string saying we won.
won:
	set	r1	win_text 	; print the win string
	call	pstr
	rmem	r1	win_count
	add	r1	r1	1
	wmem	win_count	r1
	ret

	;; This will do the multiplication step
	;; None of these functions preserve any registers
	;; Destroy r1, r2, r3, r7
	;; Decrements r0 in the main function (step counter)
cmd_mult:
	mult	r7	r1	r2   	; the actual multiplication
	rmem	r1	first_let 	; get the first letter index
	set	r3	game_numbers	; the address we index off of
	add	r1	r1	r3 	; index to first location
	wmem	r1	r7		; write the new value to the first location
	rmem	r2	second_let	; get the second letter index
	add	r2	r2	r3	; calculate the new location
	wmem	r2	9973		; mark the second location as invalid
	add	r0	r0	32767	; decrement the counter
	ret

	;; See cmd_mult for comments
cmd_add:
	add	r7	r1	r2
	rmem	r1	first_let
	set	r3	game_numbers
	add	r1	r1	r3
	wmem	r1	r7
	rmem	r2	second_let
	add	r2	r2	r3
	wmem	r2	9973
	add	r0	r0	32767
	ret

	;; See cmd_sub for comments
cmd_sub:
	gt	r7	r2	r1 	; ensure that we don't get a negative
	jt	r7	not_neg		; as negative's aren't allowed.
	mult	r2	r2	32767	; Negate the second number
	add	r7	r1	r2	; the rest is similar to the other cmd_s
	rmem	r1	first_let
	set	r3	game_numbers
	add	r1	r1	r3
	wmem	r1	r7
	rmem	r2	second_let
	add	r2	r2	r3
	wmem	r2	9973
	add	r0	r0	32767
	ret
not_neg:
	push	r1
	set	r1	negative_message
	call	pstr
	pop	r1
	ret

cmd_div:
	jf	r2	no_div		; We don't divide by 0, ignore move
	call	divide
	jt	r2	no_div		; If we have a remainder, move denied
	rmem	r7	first_let
	set	r3	game_numbers
	add	r7	r7	r3
	wmem	r7	r1
	rmem	r2	second_let
	add	r2	r2	r3
	wmem	r2	9973
	add	r0	r0	32767
	ret
no_div:
	push	r1
	set	r1	divide_error
	call	pstr
	pop	r1
	ret

	;; Must preserve r0, but does not use r0.
	;; Destroys r1, r7
	;; * = 42, + = 43, - = 45, / = 47, NL = 10
	;; a/A = 97/65, b/B = 98/66, c/C = 99/67, d/D = 100/68, e/E = 101/69
parse_input:
	call	print_game
parse_input_f_let:
	call	get_char		; Get the next char
	call	get_letter
	gt	r7	r1	4	; Over 'e'
	jt	r7	parse_input_f_let
	wmem	first_let	r1
parse_get_command2:
	call	get_char
	eq	r7	r1	10 	; restart if we get a newline
	jt	r7	parse_input
	eq	r7	r1	42 	; This is mult
	jf	r7	parse_not_mult
	wmem	command	cmd_mult
	jmp	parse_input_second_let
parse_not_mult:
	eq	r7	r1	43 	; This is add
	jf	r7	parse_not_add
	wmem	command	cmd_add
	jmp	parse_input_second_let
parse_not_add:
	eq	r7	r1	45 	; This is sub
	jf	r7	parse_not_sub
	wmem	command	cmd_sub
	jmp	parse_input_second_let
parse_not_sub:
	eq	r7	r1	47 	; This is div
	jf	r7	parse_get_command2
	wmem	command	cmd_div
parse_input_second_let:
	call	get_char			; Get the next char
	eq	r7	r1	10		; Found newline, restart
	jt	r7	parse_input
	call	get_letter
	gt	r7	r1	4   		; Was it over e?
	jt	r7	parse_input_second_let
	wmem	second_let	r1
	ret

	;; This will return 0-4 when valid letter and something
	;; over 4 when it was invalid. It destroys r7, but the
	;; function that calls it will overwrite r7 anyway
get_letter:
	gt	r7	r1	101		; Over 'e'
	jt	r7	get_letter_done
	gt	r7	r1	96 		; under 'a'
	jt	r7	parse_input_cap_let
	gt	r7	r1	69 		; Over 'E'
	jt	r7	get_letter_done
	gt	r7	r1	64 		; under 'A'
	jt	r7	parse_input_low_let
	set	r1	100			; An invalid value
get_letter_done:
	ret

	;; Helper for get_letter
parse_input_cap_let:
	add	r1	r1	32671 	; subtract 'a'
	jmp	get_letter_done

	;; Helper for get_letter
parse_input_low_let:
	add	r1	r1	32703 	; subtract 'A'
	jmp	get_letter_done

	;; This will get a character from the input and quit the
	;; game if it is a q. It leaves the stack full, but we
	;; will not need the stack any more
get_char:
	pop	r1
	wmem	reta	r1
	in	r1
	eq	r7	r1	81 	; capital Q
	jt	r7	quit
	eq	r7	r1	113 	; lowercase q
	jt	r7	quit
	eq	r7	r1	72 	; capital H
	jt	r7	help_message
	eq	r7	r1	104 	; lowercase h
	jt	r7	help_message
end_get_char:
	push	reta:			; Self-modifying, change where we return to
	ret
	;; Helper for get_char
quit:
	wmem	reta	end_game
	jmp	end_get_char

help_message:
	push	r1
	set	r1	start_message
	call	pstr
	pop	r1
	jmp	end_get_char

	;; Print the 5 numbers and the goal. This will be the start of the game
	;; Must preserve r0, but does not use r0
	;; Destroys r1, r2, r3, r4
print_game:
	set	r2	6		; Just control the loop
	set	r1	strings		; The start of the strings
	set	r3	game_numbers	; Our six numbers
print_game_loop:
	rmem	r4	r3		; Print the associated number
	eq	r4	r4	9973	; Not a valid number
	jt	r4	print_game_next	; We don't print numbers we used
	push	r1			; Save this address for the next loop
	rmem	r1	r3		; Read the number to print
	call	pnumber
	pop	r1			; Restore the string pointer
	call	pstr			; Print the current string
print_game_next:
	add	r1	r1	5	; Next string is 5 bytes forward
	add	r3	r3	1	; Increase data pointer
	add	r2	r2	32767	; Decrease counter
	jt	r2	print_game_loop	; Loop while we have data to print
	out	10
	ret

	;; Pick 6 random numbers and put them in the buffer
	;; Put the numbers back before we return.
	;; Must preserve r0, does not use it.
	;; Destroys r1, r2, r3, r4, r5
pick_six:
	set	r1	6	     	; We need six numbers
	set	r3	game_numbers	; We save the six numbers here
	add	r3	r3	r1	; This is our index into it
pick_6_loop:
	rndm	r2
	mod	r2	r2	56	; Index into numbers[]
	add	r2	r2	numbers ; Add address of number
	rmem	r4	r2		; r2 = numbers[i]
	jf	r4	pick_6_loop	; If the number is already used, pick again
	wmem	r2	0	      	; 0 the address so we don't pick it twice
	add	r1	r1	32767 	; r1--
	add	r3	r3	32767	; save value
	wmem	r3	r4		; game_numbers[r1] <- r2
	jt	r1	pick_6_loop	; Get 6 numbers

	;; We now put the numbers we picked back. As we will need to use
	;; them for the next game, if we play one.
	set	r1	6
	set	r3	game_numbers
	set	r2	numbers
put_away:
	add	r1	r1	32767 	; count of our picked numbers
	rmem	r4	r3		; pointer into our picked numbers
put_away2:
	rmem	r5	r2		; Check the current location
	add	r2	r2	1	; Go forward one spot
	jt	r5	put_away2	; If we read a value, continue to move
	add	r2	r2	32767	; We didn't read a value, go back one spot
	wmem	r2	r4		; Write our first number back
	add	r3	r3	1	; Point to next number to put away
	jt	r1	put_away
	ret

	.include "pnumber.s"
	.include "bindivide.s"
	.include "pstr.s"

	;; There are 56 numbers
numbers:
	data	1	2	3	4	5	6
	data	1	2	3	4	5	6
	data	1	2	3	4	5	6
	data	7	8	9	10
	data	7	8	9	10
	data	7	8	9	10
	data	7	8	9	10
	data	11	12	13	14	15	16	17
	data	11	12	13	14	15	16	17
	data	18	19	20	21	22	23	24	25
game_numbers:
	data	0	0	0	0	0	0
first_let:
	data	0
second_let:
	data	0
command:
	data	0
win_count:
	data	0
games_left_num:
	data	10
strings:
	data	"[a]	\0"
	data	"[b]	\0"
	data	"[c]	\0"
	data	"[d]	\0"
	data	"[e]	\0"
	data	"[Goal]\0"
win_text:
	data	"You did it!\n\n\0"
lose_text:
	data	"You lost this time.\n\n\0"
negative_message:
	data	"Negative numbers are not allowed.\n\0"
divide_error:
	data	"You divided by zero, or the quotient was not a whole number.\n\0"
games_left:
	data	"Games left to play: \0"
quit_message:
	data	"You won \0"
quit_message2:
	data	" games out of \0"
start_message:
	data	"\nThis is the game of krypto. You will be given 5 numbers\n"
	data	"and a goal number. You must use the four basic math operations\n"
	data	"to create the goal number. You must use all 5 numbers. You can\n"
	data	"only use each number 1 time.\n\nNo fractions or decimals allowed."
	data	"\n\nCommands are entered: \"c/a\" which will divide the number\n"
	data	"in location c by the number in location a and store the result\n"
	data	"in location c. e.g.  c <- c/a\n\nType h to show this message "
	data	"again. Type q to quit.\n\n\0"
