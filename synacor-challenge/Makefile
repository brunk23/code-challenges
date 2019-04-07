SRCDIR = simulator
DSRCDIR = disassem
ASMDIR = assembler
CFILES = $(SRCDIR)/synacor.c $(SRCDIR)/synacor_debug.c
CFILES += $(SRCDIR)/synacor_iset.c $(SRCDIR)/synacor_step.c
CFILES += $(SRCDIR)/synacor_random.c
HFILES = $(SRCDIR)/synacor.h $(SRCDIR)/synacor_stack.h
DISASS = $(DSRCDIR)/synacor_disassem.c
DHFILES = $(SRCDIR)/synacor.h
ASSEMBLERC = $(ASMDIR)/assembler-internal.c $(ASMDIR)/assembler-main.c
ASSEMBLERH = $(ASMDIR)/assembler.h
DEST = bin

all: bin/synacor bin/disass bin/synacor-asm

bin/synacor: $(CFILES) $(HFILES)
	gcc -Wall -O2 -o $(DEST)/synacor $(CFILES)
#	gcc -Wall -g -o $(DEST)/synacor $(CFILES)

bin/disass: $(DISASS) $(DHFILES)
	gcc -Wall -g -o $(DEST)/disass $(DISASS)

bin/synacor-asm: $(ASSEMBLERC) $(ASSEMBLERH)
	gcc -Wall -g -o $(DEST)/synacor-asm $(ASSEMBLERC)
