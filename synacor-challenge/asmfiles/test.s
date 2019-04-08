	.origin 0

	set r0 0
	set r1 96
	set r2 10
:main
	add r1 r1 1
	gt r7 r1 122
	jt r7 done
	out r1
	jmp main
:done
	out r2
	out r2
	halt
