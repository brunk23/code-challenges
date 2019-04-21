	.origin 0
	set	r0	20
loop:
	rndm	r1
	mod	r1	r1	6
	call	pnumber
	out	10
	add	r0	r0	32767
	jt	r0	loop
	halt

	.include "utils/pnumber.s"
	.include "utils/bindivide.s"
