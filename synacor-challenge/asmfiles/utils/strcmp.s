	;; Invoke: call strcmp
	;; Inputs: r0 <- string1  r1 <- string2
	;; Outputs: r7 = 1, if equal, 0 if not
strcmp:
	push	r0
	push	r1
	push	r2
	push	r3

strcmp_loop:
	rmem	r2	r0		; read a char
	rmem	r3	r1		; read a char
	eq	r7	r2	r3	; compare the two values
	jf	r7	strcmp_done	; quit if unequal
	jf	r2	strcmp_done	; quit if r2 is 0 
	jf	r3	strcmp_done	; quit if r3 is 0
	add	r0	r0	1	; next char
	add	r1	r1	1	; next char
	jmp	strcmp_loop

strcmp_done:
	pop	r3
	pop	r2
	pop	r1
	pop	r0
	ret
