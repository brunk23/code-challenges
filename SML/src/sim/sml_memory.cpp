/*
 * Memory related operations
 */

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

#include "sml.h"
#include "sml_memory.h"

// load operation
int opcode_load(machineState *sml)
{
  sml->counter++;		// increment the instruction counter	
  sml->accumulator = sml->memory[sml->operand];
  return 0;
}

// store operation
int opcode_store(machineState *sml)
{
  sml->counter++;		// increment the instruction counter	
  sml->memory[sml->operand] = sml->accumulator;
  return 0;
}

// simple operation
int opcode_read(machineState *sml)
{
  int input = MAXVAL+1;
  sml->counter++;		// increment the instruction counter	
  while ( out_of_bounds(input, MINVAL, MAXVAL) ) {
    cout << "? ";
    cin >> input;;
    if (out_of_bounds(input, MINVAL, MAXVAL)) {
      cout << "That is not a valid number.\n"
	   << MINVAL << " to " << MAXVAL << endl;
    }
  }
  sml->memory[sml->operand] = input;
  // memory_dump(sml);
  return 0;
}

int opcode_write(machineState *sml)
{
  sml->counter++;		// incremement the instruction counter
  cout << sml->memory[sml->operand] << "  ";
  return 0;
}
