	;; This will use binary to divide
divide:
	push	r7
	gt	r7	r2	1 	; If we divide by 1 or 0, just return right away
	jt	r7	divide.start	; Dividing by more than 1, jump forward
	set	r2	0		; No remainder, don't change the dividend
	pop	r7			; restore the register
	ret				; return to main function
divide.start:
	push	r3
	push	r4
	push	r5
	push	r6
	set	r3	DIVIDEFACTORS	; r3 = &DIVIDEFACTORS
	add	r3	r3	2	; Start with 2
divide.findfactor:
	rmem	r5	r3		; Get the factor
	mult	r4	r2	r5	; r4 = divisor * factor
	gt	r7	r5	r4	; Did we go down when we multiplied?
	jt	r7	divide.main	; if we did, then we have a factor
	add	r3	r3	1	; otherwise, check the next one
	jmp	divide.findfactor	; loop back up
divide.main:
	push	0			; keep quotient on the stack
divide.loop:
	add	r3	r3	32767 	; r3--
	rmem	r5	r3
	jf	r5	divide.end	; We read a zero
	mult	r4	r2	r5 	; r4 = divisor * factor
	mod	r6	r1	r4	; r6 = r1 mod r4
	eq	r7	r6	r1	; Is the remainder the same as the start?
	jt	r7	divide.loop	; if so, don't add anything and loop
	pop	r7			; Get the current quotient
	add	r7	r7	r5	; Add the current factor to it
	push	r7			; Save it back on the stack
	set	r1	r6		; r1 <- r6
	jmp	divide.loop		; Return to the loop

divide.end:
	set	r2	r1	; save remainder in r2
	pop	r1		; save quotient in r1
	pop	r6		; restore other registers
	pop	r5
	pop	r4
	pop	r3
	pop	r7
	ret


DIVIDEFACTORS:
	data	0,	1,	2,	4,	8,	16,	32,	64,
	data	128,	256,	512,	1024	2048,	4096,	8192,	16384
	