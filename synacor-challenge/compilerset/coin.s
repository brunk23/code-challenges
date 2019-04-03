;; This will count and print all the ways to make a certain amount of cents
;; with coins. It starts penny first.  The method will work if you don't use
;; the coins in order, but it is less efficient.
;;
;; Some effort was put into making this the most efficient program possible.
;; But, there is likely more improvements that could be done.
	.origin	00000
	set	r1	disp
	call	pstr
	out	10
inp:	call	readnum
	jf	r1	tryagain
	gt	r0	r1	499 ; We don't have $5 bills, so limit to under $5
	jt	r0	tryagain
	set	r0	r1

	;; This is our adding loop. We start by adding all the values and
	;; then we continue to add only the first coin until we hit the value
	;; we are looking for or we are over it.
addvalues:
	set	r1	coins		; point r1 to vals[6] i
	add	r1	r1	32767	; i--
	rmem	r2	r1		; r2 = vals[i]
addvalues1:
	add	r1	r1	32767	; i--
	rmem	r3	r1		; r3 = vals[i]
	add	r2	r2	r3	; r2 += r3
	eq	r7	vals	r1	; if i != 0
	jf	r7	addvalues1	; loop again
	set	r3	0		; We should have none of the first coin
	rmem	r4	coins		; Get the value of the first coin
	set	r5	0		; No first coins
addvalues2:
	eq	r7	r0	r2	; if r0 == r2
	jt	r7	hitvalue	;   we count a hit
	gt	r7	r2	r0	; if r2 > r0
	jt	r7	overvalue	;   we went over
	add	r2	r2	r4	; Increase the current sum
	add	r5	r5	1	; Increase the current count
	jmp	addvalues2	; We save time by avoiding recalculating whole sum

	;; When we find a match, we need to increase the counter and then
	;; print a line showing how the match was made.
hitvalue:
	wmem	counts	r5
	add	r6	r6	1	; r6 is out counter for hits, increase it
	eq	r7	r6	10000	; if we hit 10k, we need a second word
	jt	r7	upcount		; so we jump there to handle that
hitvalue2:
	set	r4	strgs		; r4 = strgs[0] j
	set	r3	counts		; r3 = counts[0]  i
	jf	count:	hitvalue0	; count=# of 10k groups, skip forward if 0
	rmem	r1	count
	call	pnumber		  	; print the number of 10k groups we have
	gt	r7	r6	9 	; 9 or lower needs 000 padding
	jf	r7	three0s
	gt	r7	r6	99 	; 10-99 needs 00 padding
	jf	r7	two0s
	gt	r7	r6	999 	; 100-999 neext 0 padding
	jf	r7	one0
	jmp	hitvalue0		; don't pad any digits
three0s:
	out	48			; Print 1-3 0s based on where we jump in
two0s:	out	48			; to this block from above
one0:	out	48
hitvalue0:
	set	r1	r6		; put counter in r1 for printing
	call	pnumber			; print the number
	out	9			; print a tab
hitvalue1:
	rmem	r1	r4		; r1 = strgs[j]
	call	pstr			; print strgs[j]
	rmem	r1	r3		; r1 = counts[i]
	call	pnumber			; print r1
	out	9			; print a tab
	add	r3	r3	1	; i++
	add	r4	r4	1	; j++
	eq	r7	r3	vals	; if &counts[i] != &vals[0]
	jf	r7	hitvalue1	;   print the next pair of string/number
	out	10			; print a newline

	;; We intentionally fallthrough from the above code into this
	;; block. This block will add one of the next highest coin and
	;; zero out all the blocks below it.
overvalue:
	wmem	counts	r5
	set	r5	vals		; r5 = vals[0]
	set	r4	counts		; r4 = counts[0]
	set	r3	coins		; r3 = coins[0]
overvalue1:
	rmem	r2	r4	  	; r2 = counts[i]
	add	r5	r5	1 	; i++
	add	r4	r4	1	; k++
	add	r3	r3	1 	; j++
	eq	r7	r5	coins	; &vals[i] == &coins[0] we are out of coins
	jt	r7	endprogram
	eq	r7	0	r2	; if counts[i] == 0
	jt	r7	overvalue1	; go to next value
	rmem	r2	r5		; r2 = vals[i]
	rmem	r3	r3		; r3 = coins[j]
	add	r2	r3	r2	; r2 += r3
	wmem	r5	r2		; vals[i] = r2
	rmem	r3	r4
	add	r3	r3	1     	; counts[k]++
	wmem	r4	r3
	add	r4	r4	32767	; k--
	add	r5	r5	32767	; i--
	wmem	r5	0		; vals[i] = 0
	wmem	r4	0		; counts[k] = 0
	jmp	addvalues

	;; We are done with the program.
endprogram:
	halt

	;; This is a helper for the input. It makes sure we get a valid
	;; number for the program.
tryagain:
	set	r1	emsg
	call	pstr
	jmp	inp

	;; This is a helper that lets us have more than 32767 combinations
	;; and print them correctly.
upcount:
	rmem	r1	count
	add	r1	r1	1
	wmem	count	r1
	set	r6	0
	jmp	hitvalue2

	.include	"readnum.s"
	.include	"bindivide.s"
	.include	"pstr.s"
	.include	"pnumber.s"

counts:	data	0	0	0	0	0	0
vals:	data	0	0	0	0	0	0
coins:	data	1	5	10	25	50	100
disp:	data	"How much cents? "
emsg:	data	"Pick a different number: "
strgs:	data	penny nickel dime quarter half-dollar dollar
penny:	data	"Pennies: "
nickel:	data	"Nickels: "
dime:	data	"Dimes: "
quarter:	data	"Quarters: "
half-dollar:	data	"Halfs: "
dollar:	data	"Dollars: "
