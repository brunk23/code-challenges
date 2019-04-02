SRCDIR = simulator
CFILES = $(SRCDIR)/synacor.c $(SRCDIR)/synacor_debug.c $(SRCDIR)/synacor_stack.c
CFILES += $(SRCDIR)/synacor_iset.c $(SRCDIR)/synacor_step.c
HFILES = $(SRCDIR)/synacor.h $(SRCDIR)/synacor_stack.h
DISASS = $(SRCDIR)/synacor_disassem.c
DEST = bin

bin/synacor: $(CFILES) $(HFILES)
	gcc -Wall -g -o $(DEST)/synacor $(CFILES)

bin/disass: $(SRCDIR)/$(DISASS) $(SRCDIR)/$(HFILES)
	gcc -Wall -g -o $(DEST)/disass $(DISASS)
