	;; Returns new address of string
	;; Invoke: call prepend_str
	;; Inputs: r1 <- dest, r2 <- src
	;; Outputs: N/A
prepend_str:
	push	r0
	push	r2
	push	r3
	push	r1			; we need this after strlen
	set	r1	r2		; point to src string
	call	strlen			; r0 <- length of src
	pop	r1			; get address of dest
	add	r2	r2	r0	; point to last char in src string
prepend_str_loop:
	jf	r0	prepend_str_end ; we're done
	add	r2	r2	32767	; r2--
	add	r1	r1	32767	; r1--
	rmem	r3	r2		; read char
	wmem	r1	r3		; save in front
	add	r0	r0	32767	; decrement counter
	jmp	prepend_str_loop
prepend_str_end:
	pop	r3
	pop	r2
	pop	r0
	ret
