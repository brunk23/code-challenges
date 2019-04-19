	;; Returns new address of string
	;; Invoke: call append_str
	;; Inputs: r1 <- dest, r2 <- src
	;; Outputs: N/A
append_str:
	push	r1
	push	r2
	push	r3
	rmem	r3	r1
	jf	r3	append_str_loop
end_str:
	add	r1	r1	1	; point to next char
	rmem	r3	r1
	jt	r3	end_str
append_str_loop:
	rmem	r3	r2
	wmem	r1	r3
	add	r2	r2	1	; r2++
	add	r1	r1	1	; r1++
	jt	r3	append_str_loop
	pop	r3
	pop	r2
	pop	r1
	ret
