# Attempt to solve project Euler #11 in 
# Synacor assembly

# Due to limitations, the product will be kept in 4 words.
# (00 00 00 49) * 99 = (00 00 00 4851) = (00 00 48 51)
# (00 00 48 51) * 97 = (00 00 4656 4947) = (00 00 4705 47)
# = (00 47 05 47) etc

.origin 0

# r0 will be current location 0 - > 399

	# ENTER THE MAIN PROGRAM
	call main
	set r3 max
	call print
	halt

	##
	# print() prints the 4 digit number, starting at
	# r3, to the output, followed by a newline.
	##
:print
	push r0
	push r2
	push r3
	push r4
	push r5
	add r3 r3 3		# r1 is the place we work on
	call pnum
	add r3 r3 32767
	call pnum
	add r3 r3 32767
	call pnum
	add r3 r3 32767
	call pnum
	out 10
	pop r5
	pop r4
	pop r3
	pop r2
	pop r0
	ret

	# pnum() is a helper function that prints a
	# number pair
:pnum
	rmem r2 r3		# r2 is the number
	mod r5 r2 10		# r5 is ones place
	set r4 0
	:ploop
	add r4 r4 1
	mult r0 r4 10
	gt r0 r0 r2
	jt r0 pdone
	jmp ploop
	:pdone
	add r4 r4 32767		# subtract one
	add r4 r4 48		# add '0'
	add r5 r5 48		# add '0'
	out r4
	out r5
	ret

	##
	# Main loop, will check every number, not efficient
	##
:main
	set r0 grid
	add r1 r0 339    #		# MAXDOWN
	set r6 0
:main_loop
	gt r7 r0 r1
	jt r7 main_right	# skip all down routines if past grid+339

	call down
	call compare

	mod r7 r6 20
	gt r7 r7 2
	jf r7 main_downr
	call downl
	call compare

:main_downr
	mod r7 r6 20
	gt r7 r7 16
	jt r7 main_noright
	call downr
	call compare
:main_right
	mod r7 r6 20
	gt r7 r7 16
	jt r7 main_noright
	call right
	call compare

:main_noright
	add r0 r0 1
	add r6 r6 1
	eq r7 r0 gstop		# should be gstop not r1
	jf r7 main_loop
	ret

:down
	# Zero out the 3 higher digit pairs
	set r5 prod
	add r5 r5 1
	wmem r5 0
	add r5 r5 1
	wmem r5 0
	add r5 r5 1
	wmem r5 0
	set r5 prod
	set r2 r0		# r2 = curr number
	rmem r3 r2
	wmem r5 r3		# save first number in prod

	add r2 r2 20		# next row down
	rmem r3 r2
	call mult

	add r2 r2 20
	rmem r3 r2
	call mult

	add r2 r2 20
	rmem r3 r2
	call mult
	ret

:downl
	# Zero out the 3 higher digit pairs
	set r5 prod
	add r5 r5 1
	wmem r5 0
	add r5 r5 1
	wmem r5 0
	add r5 r5 1
	wmem r5 0
	set r5 prod
	set r2 r0               # r2 = curr number
	rmem r3 r2
	wmem r5 r3              # save first number in prod

	add r2 r2 19            # next row down and left
	rmem r3 r2
	call mult

	add r2 r2 19
	rmem r3 r2
	call mult

	add r2 r2 19
	rmem r3 r2
	call mult
	ret
	
:downr
        # Zero out the 3 higher digit pairs
	set r5 prod
	add r5 r5 1
	wmem r5 0
	add r5 r5 1
	wmem r5 0
	add r5 r5 1
	wmem r5 0
	set r5 prod
	set r2 r0               # r2 = curr number
	rmem r3 r2
	wmem r5 r3              # save first number in prod

	add r2 r2 21            # next row down
	rmem r3 r2
	call mult

	add r2 r2 21
	rmem r3 r2
	call mult

	add r2 r2 21
	rmem r3 r2
	call mult
	ret

:right
        # Zero out the 3 higher digit pairs
	set r5 prod
	add r5 r5 1
	wmem r5 0
	add r5 r5 1
	wmem r5 0
	add r5 r5 1
	wmem r5 0
	set r5 prod
	set r2 r0		# r2 = curr number
	rmem r3 r2
	wmem r5 r3		# save first number in prod

	add r2 r2 1		# next row down
	rmem r3 r2
	call mult

	add r2 r2 1
	rmem r3 r2
	call mult

	add r2 r2 1
	rmem r3 r2
	call mult
	ret

	
	##
	# multiplies curr by the number in r3
	# r3 will be the head of the 4 numbers we
	# are multiplying. The remaining 3 will be
	# in curr
	##
:mult
	push r0
	push r1
	push r2
	push r5

	# The first pair of digits
	set r0 prod
	rmem r1 r0		# load bottom digits into r1
	mult r1 r1 r3
	mod r2 r1 100
	wmem r0 r2
	call hundreds
	add r4 r4 32767		# subtract 1

	# The second pair of digits
	add r0 r0 1		# move to the next digits
	rmem r1 r0		# load next digit pair
	mult r1 r1 r3		# multiply the digit pair by current factor
	add r1 r1 r4		# add the carry
	mod r2 r1 100		# get the bottom 2 digits
	wmem r0 r2		# save them to this spot
	call hundreds		# split the hundreds off for the carry
	add r4 r4 32767		# subtract 1, because hundreds is always 1 high

	# The third pair of digits
	add r0 r0 1
	rmem r1 r0
	mult r1 r1 r3
	add r1 r1 r4
	mod r2 r1 100
	wmem r0 r2
	call hundreds
	add r4 r4 32767

	# The top pair will always be the carry alone
	add r0 r0 1
	wmem r0 r4		# top numbers

	pop r5
	pop r2
	pop r1
	pop r0
	ret

:hundreds
	set r4 1
:hstart
	mult r5 r4 100		# we're going to loop until we find a
	gt r5 r5 r1		# number that times 100 will be larger
	jt r5 hunddone		# than the current partial product
	add r4 r4 1		# this is probably a bottleneck.
	jmp hstart
:hunddone
	ret


	##
	# compare() will see if the current product is larger than the
	# old max
	# called from main_loop, only needs to preserve r0 and r1
	##
:compare
	push r0
	push r1
	set r0 prod		# set the numbers up to point to the
	set r1 max		# highest pair of digits
	add r0 r0 3		# will go down from here
	add r1 r1 3
:compare_start
	rmem r2 r0
	rmem r3 r1
	gt r7 r3 r2
	jt r7 compare_done	# The new product is smaller
	gt r7 r2 r3
	jt r7 compare_copy	# The new product is larger!
	add r0 r0 32767		# They were equal, go to the next digits
	add r1 r1 32767
	gt r7 prod r0
	jt r7 compare_done	# We've run out of digits to check
	jmp compare_start	# loop to check the new digits
:compare_copy
	wmem r1 r2		# We only need to copy the digits we're at and down
	add r0 r0 32767		# Shift both indexes down
	add r1 r1 32767
	gt r7 prod r0		# check to see if we're done
	jt r7 compare_done	# jump to done if we are
	rmem r2 r0		# read the next didit pair in
	jmp compare_copy	# loop to copy next pair
:compare_done
	pop r1
	pop r0
	ret
	
	
:prod   data 00 00 00 00  	# product will be kept in 4 words
:max	data 00 00 00 00
:grid
	data 08 02 22 97 38 15 00 40 00 75 04 05 07 78 52 12 50 77 91 08
	data 49 49 99 40 17 81 18 57 60 87 17 40 98 43 69 48 04 56 62 00
	data 81 49 31 73 55 79 14 29 93 71 40 67 53 88 30 03 49 13 36 65
	data 52 70 95 23 04 60 11 42 69 24 68 56 01 32 56 71 37 02 36 91
	data 22 31 16 71 51 67 63 89 41 92 36 54 22 40 40 28 66 33 13 80
	data 24 47 32 60 99 03 45 02 44 75 33 53 78 36 84 20 35 17 12 50
	data 32 98 81 28 64 23 67 10 26 38 40 67 59 54 70 66 18 38 64 70
	data 67 26 20 68 02 62 12 20 95 63 94 39 63 08 40 91 66 49 94 21
	data 24 55 58 05 66 73 99 26 97 17 78 78 96 83 14 88 34 89 63 72
	data 21 36 23 09 75 00 76 44 20 45 35 14 00 61 33 97 34 31 33 95
	data 78 17 53 28 22 75 31 67 15 94 03 80 04 62 16 14 09 53 56 92
	data 16 39 05 42 96 35 31 47 55 58 88 24 00 17 54 24 36 29 85 57
	data 86 56 00 48 35 71 89 07 05 44 44 37 44 60 21 58 51 54 17 58
	data 19 80 81 68 05 94 47 69 28 73 92 13 86 52 17 77 04 89 55 40
	data 04 52 08 83 97 35 99 16 07 97 57 32 16 26 26 79 33 27 98 66
	data 88 36 68 87 57 62 20 72 03 46 33 67 46 55 12 32 63 93 53 69
	data 04 42 16 73 38 25 39 11 24 94 72 18 08 46 29 32 40 62 76 36
	data 20 69 36 41 72 30 23 88 34 62 99 69 82 67 59 85 74 04 36 16
	data 20 73 35 29 78 31 90 01 74 31 49 71 48 86 81 16 23 57 05 54
	data 01 70 54 71 83 51 54 69 16 92 33 48 61 43 52 01 89 19 67 48
:gstop
