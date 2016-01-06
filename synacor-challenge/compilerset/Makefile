
ADIR = assembler
AFILES = $(ADIR)/assembler-main.c $(ADIR)/assembler-internal.c
AFILES += $(ADIR)/assembler-opcodes.c
AHFILES = $(ADIR)/assembler.h

syn-asm: $(AFILES) $(AHFILES)
	gcc -Wall -g -o synacor-asm $(AFILES)
