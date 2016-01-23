## Synacor v2

I extended the Synacor machine to allow device access. These devices
are the file name(s) listed on the command line when you run the
simiulator.  For example: "synacor challenge.bin" would have a one device
(number 0) that connects to the challenge.bin file.  The default operation
of the synacor machine, on boot, will be to load the first addressable
segment of memory from device 0 into the machine memory (up to 32768 words
or the end of the device contents, if it is less than that), and start
executing from address 0.  So, the default operation will continue to work
as the old machine used to.

New Opcodes:

* dread a b c d e

a is the destination memory location 0-32767 (or a register that contains
the destination memory location)

b is the device number (0 - n) which corresponds to the files listed as
arguments when opening the simulator

c is the segment (0 - 32767), basically the upper 15 bits of the starting
location in the device

d is the address (0 - 32767), in the segment

e is the number of words to read into memory (0 = read a full segment)

NOTE: is c is 32767 and d + e > 32767, the read will wrap down to segment 0
address 0 to fulfill the ordered number of words.  If an EOF is encountered,
the remainder of the words requested will be 0s.  (Maybe they should be undefined
or remain what was in memory before, I am undecided on this).

The values of c and d are combined to form a 30 bit address into the device.  
In this way, up to 1 Gig of words can be addressed from any given device.

* dwrite a b c d e

a is the destination device (0 - n) which corresponds to the files listed as
arguments when opening the simulator

b is the destination segment (0 - 32767)

c is the destination address (0 - 32767)

d is the source memory location or a register pointing to it

e is the length of words to write.

NOTE: if segment is 32767 and c + e > 32767, the write will wrap down to segment 0
address 0 and overwrite the start of the device memory.
