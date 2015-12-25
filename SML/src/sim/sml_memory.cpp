/*
 * Memory related operations
 */

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;

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
  string line;
  char *pfull, *parse, *before;
  int input = MAXVAL+1;
  sml->counter++;		// increment the instruction counter	
  cout << "? ";
  while( getline(cin, line) ) {
    pfull = new char[line.size()];
    parse = before = pfull;
    strncpy(pfull, line.c_str(), line.size());
    input = strtol(parse, &parse, 10);
    if( parse == before || parse == 0 ||
	out_of_bounds(input,MINVAL,MAXVAL) ) {
      cout << "That is not a valid number.\n"
	   << MINVAL << " to " << MAXVAL << endl;
      cout << "? ";
      delete pfull;
      continue;
    } else {
      sml->memory[sml->operand] = input;
      delete pfull;
      break;
    }
  }
  return 0;
}

int opcode_write(machineState *sml)
{
  sml->counter++;		// incremement the instruction counter
  cout << sml->memory[sml->operand] << "  ";
  return 0;
}
