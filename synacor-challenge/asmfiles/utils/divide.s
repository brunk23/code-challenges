divide:	push	r3
	push	r4
	push	r7

	mod	r3	r1	r2	; remainder of r1 mod r2
	mult	r4	r3	32767	; r4 = -r3
	add	r4	r1	r4	; subtract the remainder
	mult	r2	r2	32767	; r2 = -r2
	set	r1	0		; r1 = 0
div001:	eq	r7	r4	0	; check if we have anything left to divide
	jt	r7	div002		; if not, we're done
	add	r1	r1	1	; otherwise increase the quotient
	add	r4	r4	r2	; subtract the divisor
	jmp	div001			; and loop back to the test

div002:	set	r2	r3		; put remainder in r2 before leaving
	pop	r7
	pop	r4
	pop	r3
	ret
