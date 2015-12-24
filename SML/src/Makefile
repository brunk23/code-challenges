# This will make both the programs

COMPC = comp/*.c
COMPH = comp/*.h shared/*.h
SIMC = sim/*.cpp
SIMH = sim/*.h shared/*.h

all: sml_sim sml_comp

sml_comp: $(COMPC) $(COMPH)
	gcc -g -Wall -o sml_comp $(COMPC)

sml_sim: $(SIMC) $(SIMH)
	c++ -g -Wall -o sml_sim $(SIMC)

clean:
	rm *.o
