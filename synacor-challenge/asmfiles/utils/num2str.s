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
