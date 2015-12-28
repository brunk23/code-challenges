#ifndef SML_H
#define SML_H

#include <string>
#include "../shared/sml_shared.h"

#define EINPUT -9999999

using std::string;

struct machineState;		/* Forward declare */

typedef int (*opPtr)(machineState *);

struct machineState {
  int accumulator;
  int stackPointer;
  int counter;
  int instructionRegister;
  int operationCode;
  int operand;
  int memory[MEMSIZE];
  opPtr inst_tble[MAXOP];
  bool indirect;
  bool running;
};

// These functions are in the main program file
int init_machine(machineState *);
int memory_dump(machineState *sml);
void error_message(string message);
bool out_of_bounds(int,int,int);

#endif
