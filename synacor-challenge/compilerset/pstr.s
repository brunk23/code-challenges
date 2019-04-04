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
