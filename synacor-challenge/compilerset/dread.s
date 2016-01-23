# This is a test file to see if we can load the original
# challenge file as a second device from this file. It does
# work exactly as expected

.origin 0
	jmp start
.origin 32762
:start
	dread 0 0 2 0 32767

