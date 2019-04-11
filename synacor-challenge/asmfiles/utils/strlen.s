	;; Returns length of 0 terminated string pointed to by r1.
	;; Invoke: call strlen
	;; Inputs: r1 <- &string
	;; Outputs: r0 <- strlen(string)
strlen:
	push	r1
	push	r2
	set	r0	32767		; r0 = -1
strlen_loop:
	rmem	r2	r1		; read first char
	add	r1	r1	1	; next character
	add	r0	r0	1	; increase length
	jt	r2	strlen_loop	; loop if not done
	pop	r2
	pop	r1
	ret
