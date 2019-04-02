; This will read the next number from input
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
