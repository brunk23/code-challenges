# This will make both the programs

COMPCMAIN = comp/compiler.c
COMPCTEST = comp/node_tester.c
COMPC = comp/compile_io.c comp/compile_parse.c comp/compile_messages.c
COMPC += comp/compile_utility.c comp/compile_node.c
COMPH = comp/*.h shared/*.h
SIMC = sim/*.cpp
SIMH = sim/*.h shared/*.h

all: sml_sim sml_comp

test: $(COMPC) $(COMPCTEST) $(COMPH)
	gcc -g -Wall -o test $(COMPC) $(COMPCTEST)

sml_comp: $(COMPC) $(COMPH) $(COMPCMAIN)
	gcc -g -Wall -o sml_comp $(COMPC) $(COMPCMAIN)

sml_sim: $(SIMC) $(SIMH)
	c++ -g -Wall -o sml_sim $(SIMC)

clean:
	rm *.o
