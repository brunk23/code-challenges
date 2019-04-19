	.origin	0

	set	r1	dest
	set	r2	src
	call	prepend_str
	call	append_str
	call	pstr
	halt

	.include	"utils/append_str.s"
	.include	"utils/pstr.s"
	.include	"utils/strlen.s"
	.include	"utils/prepend_str.s"

	.origin	500
src:	data	"foo\0"

	.origin 600
dest:
	data	"bar\n\0"
