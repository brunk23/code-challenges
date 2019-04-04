	;; This will use binary to divide
	;; Inputs:  r1 <- dividend, r2 <- divisor
	;; Outputs:  r1 <- quotient, r2 <- remainder
divide:

	;; We start off by finding early return conditions. We can return
	;; right away if we are dividing a 0, or by 1.
	jt	r1	divide.notzero
	set	r2	0
	ret
divide.notzero:
	push	r7
	gt	r7	r2	1 	; If we divide by 1 or 0, just return right away
	jt	r7	divide.start	; Dividing by more than 1, jump forward
	set	r2	0		; No remainder, don't change the dividend
	pop	r7			; restore the register
	ret				; return to main function

divide.start:
	push	r6
	push	r5
	push	r4
	push	r3

	;; We store possible factors on the stack
	push	0			; push 0 on the stack for when we are done
	set	r4	r2		; We first push r2 on the stack
	set	r5	1
divide.findfactor:
	set	r3	r4		; save the old factor to see when we go over
	push	r5			; push the power of 2 we multiplied by
	push	r4			; push the next factor on the stack
	mult	r4	r4	2	; double the factor
	mult	r5	r5	2	; double the power of 2
	gt	r7	r4	r1 	; is r4 > dividend
	gt	r3	r3	r4	; is the old number > the new number?
	or	r3	r3	r7	; Either one is a done situation
	jf	r3	divide.findfactor

	set	r6	0		; keep quotient in r6
divide.loop:
	pop	r4		   	; pop the test divisor
	jf	r4	divide.end	; We read a zero
	pop	r5			; pop the power of 2 we add
	mod	r3	r1	r4	; r3 = r1 mod r4
	eq	r7	r3	r1	; Is the remainder the same as the start?
	jt	r7	divide.loop	; if so, don't add anything and loop
	add	r6	r6	r5	; Add the current factor to it
	set	r1	r3		; r1 <- r3
	jmp	divide.loop		; Return to the loop

divide.end:
	set	r2	r1	; save remainder in r2
	set	r1	r6	; save quotient in r1
	;; restore other registers
	pop	r3
	pop	r4
	pop	r5
	pop	r6
	pop	r7
	ret
