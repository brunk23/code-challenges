# This will make both the programs

DISASSC = disass/*.cpp
DISASSH = shared/*.h
LISPC = lispcomp/*.c
LISPH = lispcomp/*.h shared/*.h
BASICC = basiccomp/*.c
BASICH = basiccomp/*.h shared/*.h
SIMC = sim/*.cpp
SIMH = sim/*.h shared/*.h

all: sml_sim sml_basic sml_lisp sml_disass

sml_basic: $(BASICC) $(BASICH)
	gcc -g -Wall -o sml_basic $(BASICC)

sml_lisp: $(LISPC) $(LISPH)
	gcc -g -Wall -o sml_lisp $(LISPC)

sml_sim: $(SIMC) $(SIMH)
	c++ -g -Wall -o sml_sim $(SIMC)

sml_disass: $(DISASSC) $(DISASSH)
	c++ -g -Wall -o sml_disass $(DISASSC)

clean:
	rm *.o

clean-all:
	rm *.o *.core *~
