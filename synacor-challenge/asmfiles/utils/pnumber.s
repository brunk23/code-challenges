	;; This will print the number in r1
	;; Invoke: call pnumber
	;; Inputs: r1 <- number to print
	;; Outputs: ASCII of number printed to stdout, no registers changed
pnumber:
	; Preserve all the changed registers for code reuse
	push	r1
	push	r2
	push	r5

	set	r5	0		; pushed digits
pn01:	set	r2	10		; We're dividing by 10
	call	divide			; r1 <- quotient, r2 <- remainder
	push	r2			; save remainder
	add	r5	r5	1	; increase pushed digits
	jt	r1	pn01		; if we still have digits, loop
pn03:	pop	r1			; pop the value to print
	add	r1	r1	48	; add ascii 0
	out	r1			; output the digit
	add	r5	r5	32767	; count of digits pushed -1
	jt	r5	pn03		; print the next digit if not 0

	; Restore all the registers before returning
	pop	r5
	pop	r2
	pop	r1
	ret
