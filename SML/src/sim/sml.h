#ifndef SML_H
#define SML_H

#include <string>
#include "../shared/sml_shared.h"

#define EINPUT -9999999

using std::string;

struct machineState {
  int accumulator;
  int counter;
  int instructionRegister;
  int operationCode;
  int operand;
  int memory[MEMSIZE];
  bool indirect;
  bool running;
};

typedef int (*opPtr)(machineState *);

// These functions are in the main program file
int init_machine(machineState *, opPtr[]);
int memory_dump(machineState *sml);
void error_message(string message);
bool out_of_bounds(int,int,int);

#endif
