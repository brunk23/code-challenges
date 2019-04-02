; prints null terminated string starting at r1
pstr:
	push	r0
	push	r1
	push	r7

p001:	rmem	r0	r1		; read the digit to print
	eq	r7	r0	0	; if it's 0, we're done
	jt	r7	p002		; jump to the end
	out	r0			; if not, print it to output
	add	r1	r1	1	; point to the next digit
	jmp	p001			; loop back to start

p002:	pop	r7
	pop	r1
	pop	r0
	ret
