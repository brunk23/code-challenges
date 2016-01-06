	.origin 0

	set r0 0
	set r1 97
	set r2 32
:main
	add r1 r1 1
	gt r7 r1 122
	jt r7 done
	out r1
	jmp main
:done
	out r2
	halt
