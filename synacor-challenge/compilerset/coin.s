.origin 00000
	set	r0	62		# initial amount of coins
	set	r1	disp
	call	pstr
	out	10

# This is our adding loop
addvalues:
	set	r1	vals		# point r1 to vals
	rmem	r2	r1		# get the first number
addvalues1:
	add	r1	r1	1	# increase r1
	rmem	r3	r1		# get the val
	add	r2	r2	r3	# add next value
	eq	r7	lastv	r1	# if r1 != 6
	jf	r7	addvalues1	# loop again

	eq	r7	r0	r2	# if r0 == r2
	jt	r7	hitvalue
	gt	r7	r2	r0	# if r2 > r0
	jt	r7	overvalue

	rmem	r3	vals
	rmem	r2	coins
	add	r3	r3	r2
	wmem	vals	r3
	jmp	addvalues
	
hitvalue:
	add	r6	r6	1
	set	r4	strgs
	set	r3	vals
	set	r1	r6
	call	pnumber
	out	9
hitvalue1:
 	rmem	r1	r4
	call	pstr
	rmem	r1	r3
	call	pnumber
	out	9
	add	r3	r3	1
	add	r4	r4	1
	eq	r7	r3	coins
	jf	r7	hitvalue1
	out	10
overvalue:
	set	r5	vals
	set	r3	coins
overvalue1:
	rmem	r2	r5
	add	r5	r5	1
	add	r3	r3	1
	eq	r7	r5	coins	# we are out of coins
	jt	r7	endprogram
	eq	r7	0	r2	# if r2 == 0
	jt	r7	overvalue1	# go to next value
	rmem	r2	r5		# r2 = m[1]
	rmem	r3	r3		# r3 = m[r3]
	add	r2	r3	r2	# r2 = r3 + r2
	wmem	r5	r2		# m[r1] = r2
	add	r5	r5	32767	# r1 = r1 - 1
	wmem	r5	0
	jmp	addvalues
endprogram:
	halt

pstr:
	push	r0
	push	r1
	push	r7
p001:
	rmem	r0	r1
	eq	r7	r0	0
	jt	r7	p002
	out	r0
	add	r1	r1	1
	jmp	p001
p002:
	pop	r7
	pop	r1
	pop	r0
	ret

# This will print the number in r1
pnumber:
	# Preserve all the changed registers for code reuse
	push	r1
	push	r2
	push	r3
	push	r5
	push	r7

	set	r5	0		# pushed digits
pn01:
	mod	r2	r1	10	# take remainder of r6 mod 10
	push	r2			# save it
	add	r5	r5	1
	mult	r2	r2	32767	# multiply by neg 1
	add	r1	r1	r2	# subtract it
	eq	r7	r1	0
	jt	r7	pn03
	set	r3	0		# set r3 = 0

pn02:
	add	r3	r3	1	
	mult	r2	r3	10	# multiply it by 10
	eq	r7	r2	r1	# 
	jf	r7	pn02
	set	r1	r3
	jmp	pn01
pn03:
	pop	r1
	add	r1	r1	48	# push ascii for last digit
	out	r1
	add	r5	r5	32767	# count digit pushed -1
	eq	r7	r5	0
	jf	r7	pn03

	# Restore all the registers before returning
	pop	r7
	pop	r5
	pop	r3
	pop	r2
	pop	r1
	ret


vals:
	data	0 0  0  0  0
lastv:
	data    0
coins:
	data	1 5 10 25 50 100
disp:	data	"				How Many Ways To Make Change!"
strgs:	data	penny nickel dime quarter half-dollar dollar
penny:	data	"Pennies: "
nickel:	data	"Nickels: "
dime:	data	"Dimes: "
quarter:data	"Quarters: "
half-dollar:	data	"Halfs: "
dollar:	data	"Dollars: "
