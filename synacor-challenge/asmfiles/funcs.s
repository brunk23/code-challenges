# Useful functions for programs.

# This will read the next number from input
readnum:
	push	r2
	push	r7
	set	r1	0		# start with r1 = 0
rnum01:	in	r2			# get the next ascii char
	add	r2	r2	32720	# subtract '0'
	gt	r7	r2	9	# was the value a digit?
	jt	r7	rnum02		# if not, quit
	mult	r1	r1	10	# move the old digit over
	add	r1	r1	r2	# add this value
	jmp	rnum01
rnum02:	pop	r7
	pop	r2
	ret


divide:	push	r3
	push	r4
	push	r7

	mod	r3	r1	r2	# remainder of r1 mod r2
	mult	r4	r3	32767	# r4 = -r3
	add	r4	r1	r4	# subtract the remainder
	mult	r2	r2	32767	# r2 = -r2
	set	r1	0		# r1 = 0
div001:	eq	r7	r4	0	# check if we have anything left to divide
	jt	r7	div002		# if not, we're done
	add	r1	r1	1	# otherwise increase the quotient
	add	r4	r4	r2	# subtract the divisor
	jmp	div001			# and loop back to the test

div002:	set	r2	r3		# put remainder in r2 before leaving
	pop	r7
	pop	r4
	pop	r3
	ret

# prints null terminated string starting at r1
pstr:
	push	r0
	push	r1
	push	r7

p001:	rmem	r0	r1		# read the digit to print
	eq	r7	r0	0	# if it's 0, we're done
	jt	r7	p002		# jump to the end
	out	r0			# if not, print it to output
	add	r1	r1	1	# point to the next digit
	jmp	p001			# loop back to start

p002:	pop	r7
	pop	r1
	pop	r0
	ret

# This will print the number in r1
pnumber:
	# Preserve all the changed registers for code reuse
	push	r1
	push	r2
	push	r5
	push	r7

	set	r5	0		# pushed digits
pn01:	set	r2	10		# We're dividing by 10
	call	divide			# r1 <- quotient, r2 <- remainder
	push	r2			# save remainder
	add	r5	r5	1	# increase pushed digits
	eq	r7	r1	0	# if r1 == 0
	jt	r7	pn03		# we have found all the digits
	jmp	pn01			# otherwise loop for the next one
pn03:	pop	r1			# pop the value to print
	add	r1	r1	48	# add ascii 0
	out	r1			# output the digit
	add	r5	r5	32767	# count of digits pushed -1
	eq	r7	r5	0	# if this is 0, we're done
	jf	r7	pn03		# otherwise print the next digit.

	# Restore all the registers before returning
	pop	r7
	pop	r5
	pop	r2
	pop	r1
	ret
