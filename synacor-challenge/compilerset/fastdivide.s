	# This is a faster divide function, but it could probably still
	# be improved to increase the performance even more.
divide:
	push	r3
	push	r4
	push	r5
	push	r6
	push	r7

	set	r6	0
	gt	r7	r2	3
	jt	r7	fdiv.thousands
	mult	r3	r2	10000
	mult	r5	r3	32767
	set	r4	0
fdiv.a:
	gt	r7	r3	r1
	jt	r7	fdiv.b
	add	r4	r4	1
	add	r1	r1	r5
	jmp	fdiv.a
fdiv.b:
	mult	r4	r4	10000
	add	r6	r6	r4

fdiv.thousands:
	gt	r7	r2	32
	jt	r7	fdiv.hundreds
	mult	r3	r2	1000
	mult	r5	r3	32767
	set	r4	0
fdiv.c:
	gt	r7	r3	r1
	jt	r7	fdiv.d
	add	r4	r4	1
	add	r1	r1	r5
	jmp	fdiv.c
fdiv.d:
	mult	r4	r4	1000
	add	r6	r6	r4

fdiv.hundreds:
	gt	r7	r2	327
	jt	r7	fdiv.tens
	mult	r3	r2	100
	mult	r5	r3	32767
	set	r4	0
fdiv.e:
	gt	r7	r3	r1
	jt	r7	fdiv.f
	add	r4	r4	1
	add	r1	r1	r5
	jmp	fdiv.e
fdiv.f:
	mult	r4	r4	100
	add	r6	r6	r4

fdiv.tens:
	gt	r7	r2	3276
	jt	r7	fdiv.ones
	mult	r3	r2	10
	mult	r5	r3	32767
	set	r4	0
fdiv.g:
	gt	r7	r3	r1
	jt	r7	fdiv.h
	add	r4	r4	1
	add	r1	r1	r5
	jmp	fdiv.g
fdiv.h:
	mult	r4	r4	10
	add	r6	r6	r4

fdiv.ones:
	set	r3	r2
	mult	r5	r3	32767
	set	r4	0
fdiv.i:
	gt	r7	r3	r1
	jt	r7	fdiv.j
	add	r4	r4	1
	add	r1	r1	r5
	jmp	fdiv.i
fdiv.j:
	add	r6	r6	r4
	set	r2	r1
	set	r1	r6

	pop	r7
	pop	r6
	pop	r5
	pop	r4
	pop	r3
	ret
