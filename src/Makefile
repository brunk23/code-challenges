# This will make both the programs

sml_sim: sml.o sml_control.o sml_math.o sml_memory.o
	c++ -Wall -o sml_sim sml.o sml_control.o sml_math.o sml_memory.o

sml.o: shared/sml_shared.h sim/sml.h sim/sml.cpp
	c++ -Wall -c sim/sml.cpp

sml_math.o: shared/sml_shared.h sim/sml_math.h sim/sml_math.cpp
	c++ -Wall -c sim/sml_math.cpp

sml_memory.o: shared/sml_shared.h sim/sml_memory.h sim/sml_memory.cpp
	c++ -Wall -c sim/sml_memory.cpp

sml_control.o: shared/sml_shared.h sim/sml_control.h sim/sml_control.cpp
	c++ -Wall -c sim/sml_control.cpp

clean:
	rm *.o
