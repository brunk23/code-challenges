	;; This will use binary to divide
	;; Invoke: call divide
	;; Inputs:  r1 <- dividend, r2 <- divisor
	;; Outputs:  r1 <- quotient, r2 <- remainder
divide:

	;; We start off by finding early return conditions. We can return
	;; right away if we are dividing a 0, or by 1. This saves a marginal
	;; amount of time
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
	push	r5
	push	r4
	push	r3

	;; We store possible factors on the stack
	push	0			; push 0 on the stack for when we are done
	set	r4	r2		; We first push r2 on the stack
	set	r5	1		; This is the power of 2
divide.findfactor:
	set	r3	r4		; save the old factor to see when we go over
	push	r5			; push the power of 2 we multiplied by
	push	r4			; push the next factor on the stack
	add	r4	r4	r4	; double the factor
	add	r5	r5	r5	; double the power of 2
	gt	r7	r4	r1 	; is r4 > dividend
	gt	r3	r3	r4	; is the old number > the new number?
	or	r3	r3	r7	; Either one is a done situation
	jf	r3	divide.findfactor

	set	r3	0		; keep quotient in r6
divide.loop:
	pop	r4		   	; pop the factor we are testing
	jf	r4	divide.end	; We quit when we read a zero from the stack
	pop	r5			; pop the power of 2 for this factor
	gt	r7	r4	r1	; Is the factor greater than the remainder?
	jt	r7	divide.loop	; if so, don't do anything and loop
	mod	r1	r1	r4	; remove this factor from the dividend
	add	r3	r3	r5	; Add the current power of 2 to our quotient
	jmp	divide.loop		; Return to the loop

divide.end:
	set	r2	r1	; save remainder in r2
	set	r1	r3	; save quotient in r1
	;; restore other registers
	pop	r3
	pop	r4
	pop	r5
	pop	r7
	ret
