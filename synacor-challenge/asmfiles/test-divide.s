	set	r1	32767
	set	r2	2
	call	divide
	call	pnumber
	halt

	.include	"bindivide.s"
	.include	"pnumber.s"
