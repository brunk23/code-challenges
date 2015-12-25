#include "sml.h"
#include "sml_stack.h"

// Push a to the top of the stack
int opcode_push(machineState *sml)
{
  // Increment the counter
  sml->counter++;
  sml->memory[sml->stackPointer] = sml->accumulator;
  sml->stackPointer--;
  return 0;
}

// branch operation
int opcode_pop(machineState *sml)
{
  // Increment the counter
  sml->counter++;
  sml->stackPointer++;
  sml->accumulator = sml->memory[sml->stackPointer];
  return 0;
}

// branch operation
int opcode_call(machineState *sml)
{
  sml->counter++;		// we return to the next instruction
  sml->memory[sml->stackPointer] = sml->counter;
  sml->stackPointer--;
  sml->counter = sml->operand;
  return 0;
}

// branch operation
int opcode_ret(machineState *sml)
{
  sml->stackPointer++;
  sml->counter = sml->memory[sml->stackPointer];
  return 0;
}
