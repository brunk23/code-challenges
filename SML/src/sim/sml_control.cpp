/*
 * Control related opcodes
 */

#include "sml.h"
#include "sml_control.h"

// branch operation
int opcode_branch(machineState *sml)
{
  // Just change the counter, we're going to a different spot.
  sml->counter = sml->operand;
  return 0;
}

int opcode_branch_neg(machineState *sml)
{
  if( sml->accumulator < 0 ) {	
    sml->counter = sml->operand;
  } else {
    sml->counter++;
  }
  return 0;
}

int opcode_branch_zero(machineState *sml)
{
  if( sml->accumulator == 0 ) {	
    sml->counter = sml->operand;
  } else {
    sml->counter++;
  }
  return 0;
}

int opcode_nop(machineState *sml)
{
  sml->counter++;
  return 0;
}

int opcode_halt(machineState *sml)
{
  sml->running = false;
  return sml->memory[sml->operand];
}

// Handle trying to run an unsupported operation
int opcode_invalid(machineState *sml)
{
  error_message("INVALID OPERATION CODE: MACHINE HALTED");
  sml->running = false;
  return -1;
}
