
CFILES = synacor.c synacor_debug.c
HFILES = synacor.h
DISASS = synacor_disassem.c

synacor: $(CFILES) $(HFILES)
	gcc -Wall -g -o synacor $(CFILES)

disass: $(DISASS) $(HFILES)
	gcc -Wall -g -o disass $(DISASS)
