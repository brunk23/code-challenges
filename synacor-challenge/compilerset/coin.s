.origin 00000
	setr1disp
	callpstr
	out10
inp:	callreadnum
	jfr1tryagain
	gtr0r1499
	jtr0tryagain
	setr0r1

	# This is our adding loop
addvalues:
	setr1vals# point r1 to vals
	rmemr2r1# get the first number
addvalues1:
	addr1r11# increase r1
	rmemr3r1# get the val
	addr2r2r3# add next value
	eqr7lastvr1# if r1 != 6
	jfr7addvalues1# loop again

	eqr7r0r2# if r0 == r2
	jtr7hitvalue
	gtr7r2r0# if r2 > r0
	jtr7overvalue

	rmemr3vals
	rmemr2coins
	addr3r3r2
	wmemvalsr3
	jmpaddvalues

hitvalue:
	addr6r61
	eqr7r610000
	jtr7upcount
hitvalue2:
	setr4strgs
	setr5coins
	setr3vals
jfcount:	hitvalue0
	rmemr1count
	callpnumber
	gtr7r69
	jfr7three0s
	gtr7r699
	jfr7two0s
	gtr7r6999
	jfr7one0
	jmphitvalue0
three0s:
	out48
two0s:	out48
one0:	out48
hitvalue0:
	setr1r6
	callpnumber
	out9
hitvalue1:
	 rmemr1r4
	callpstr
	rmemr1r3
	rmemr2r5
	calldivide
	callpnumber
	out9
	addr3r31
	addr4r41
	addr5r51
	eqr7r3coins
	jfr7hitvalue1
	out10
overvalue:
	setr5vals
	setr3coins
overvalue1:
	rmemr2r5
	addr5r51
	addr3r31
	eqr7r5coins# we are out of coins
	jtr7endprogram
	eqr70r2# if r2 == 0
	jtr7overvalue1# go to next value
	rmemr2r5# r2 = m[1]
	rmemr3r3# r3 = m[r3]
	addr2r3r2# r2 = r3 + r2
	wmemr5r2# m[r1] = r2
	addr5r532767# r1 = r1 - 1
	wmemr50
	jmpaddvalues
endprogram:
	halt

tryagain:
	setr1emsg
	callpstr
	jmpinp

upcount:
	rmemr1count
	addr1r11
	wmemcountr1
	setr60
	jmphitvalue2

	.include"readnum.s"
	.include"divide.s"
	.include"pstr.s"
	.include"pnumber.s"

vals:	data0 0  0  0  0
lastv:	data    0
coins:	data1 5 10 25 50 100
disp:	data"How much cents? "
emsg:	data"Pick a different number: "
strgs:	datapenny nickel dime quarter half-dollar dollar
penny:	data"Pennies: "
nickel:	data"Nickels: "
dime:	data"Dimes: "
quarter:	data"Quarters: "
half-dollar:	data"Halfs: "
dollar:	data"Dollars: "