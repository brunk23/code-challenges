#include "sml.h"
#include "sml_stack.h"

// Push acc to the top of the stack
// The lower half of the instruction represents a
// possible operation
// stack = stack [operation] acc
// I am not sure this is bulletproof, yet
int opcode_push(machineState *sml)
{
  int temp;
  // Increment the counter

  if( sml->operand != NOP ) {
    sml->memory[sml->stackPointer] = sml->accumulator;
    temp = sml->accumulator;
    sml->operationCode = sml->operand;
    sml->operand = sml->stackPointer;
    
    if( ++sml->stackPointer < MEMSIZE ) {
      sml->accumulator = sml->memory[sml->stackPointer];
    } else {
      sml->stackPointer--;
      sml->accumulator = 0;
    }
    
    sml->inst_tble[sml->operationCode](sml);
    sml->memory[sml->stackPointer] = sml->accumulator;
    sml->stackPointer--;
    sml->accumulator = temp;
  } else {

    sml->counter++;
    sml->memory[sml->stackPointer] = sml->accumulator;
    sml->stackPointer--;
  }
  return 0;
}

// POP operation this is funky
// the lower half of the instruction represents a
// possible operation
// acc = stack [operation] acc
// Example = 071032 would be acc = stack / acc 
int opcode_pop(machineState *sml)
{
  int temp;
  // Don't Increment the counter
  sml->stackPointer++;
  if(sml->stackPointer == MEMSIZE) {
    error_message("STACK UNDERRUN");
    sml->running = false;
    return 1;
  }
  temp = sml->accumulator;
  sml->accumulator = sml->memory[sml->stackPointer];
  sml->memory[sml->stackPointer] = temp;
  sml->operationCode = sml->operand;
  sml->operand = sml->stackPointer;
  return sml->inst_tble[sml->operationCode](sml);
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
