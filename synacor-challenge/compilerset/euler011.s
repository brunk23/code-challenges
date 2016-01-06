# Attempt to solve project Euler #11 in 
# Synacor assembly

# Due to limitations, the product will be kept in 4 words.
# (00 00 00 49) * 99 = (00 00 00 4851) = (00 00 48 51)
# (00 00 48 51) * 97 = (00 00 4656 4947) = (00 00 4705 47)
# = (00 47 05 47) etc

.origin 0

# r0 will be row (0 - 19)
# r1 will be col (0 - 19)
# r2 will be rowoffset
# r3 will be coloffset

	set r0 0
	set r1 0
	set r2 0
	set r3 0
:loopr
	

:loopc
	call down
	call downl
	call downr
	call right


	add r1 r1 1
	gt r7 20 r1
	jt r7 loopc
	set r1 0		# Reset col to 0
	add r0 r0 1		# Increment row
	gt r7 20 r0		# Loop while under 20
	jt ry loopr

:down
	gt r7 r0 16
	jt r7 done		# if we are at row 17+, return
	mult r4 r0 20   	# r4 = row * 20
	add r4 r4 r1		# r4 = row * 20 + col
	rmem r5 r4		# read value of r4 into r5
	set r6 curr		# r6 = address of curr product
	wmem r6 0
	add r6 r6 1
	wmem r6 0
	add r6 r6 1
	wmem r6 0
	add r6 r6 1
	wmem r6 r5		# Reset the curr number to 00 00 00 row*20+col
	add r4 r4 20		# Add 20 to go down a row
	call getprod    	# multiply curr by this number
	add r4 r4 20		# Add 20 to go down a row
	call getprod		# multiply curr by this number
	add r4 r4 20		# Add 20 to go down a row
	call getprod		# multiply curr by this number
	call checklarg		# check if it is larger
:done
	ret

:downl
	gt r7 r0 16
	jt r7 done
	gt r7 r0 2
	jf r7 done		# only rectangle 0,3 - 16,19
	mult r4 r0 20		# r4 = row * 20
	add r4 r4 1		# r4 = r4 + col
	rmem r5 r4
	set r6 curr	        # r6 = address of curr product
	wmem r6	0
	add r6 r6 1
	wmem r6	0
	add r6 r6 1
	wmem r6	0
	add r6 r6 1
	wmem r6	r5	        # Reset	the curr number	to 00 00 00 row*20+col
	######
	
:downr


:right


:ascii0 data 48			# the ASCII for 0
:curr   data 00 00 00 00	# product will be kept in 4 words
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
