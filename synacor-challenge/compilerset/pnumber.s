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
