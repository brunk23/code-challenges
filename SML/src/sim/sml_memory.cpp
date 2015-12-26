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
  while( getline(cin, line) ) {
    pfull = new char[line.size()];
    parse = before = pfull;
    strncpy(pfull, line.c_str(), line.size());
    input = strtol(parse, &parse, 10);
    if( parse == before || parse == 0 ||
	out_of_bounds(input,MINVAL,MAXVAL) ) {
      cout << "That is not a valid number.\n"
	   << MINVAL << " to " << MAXVAL << endl;
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

int opcode_sread(machineState *sml)
{
  unsigned int length, x, strsize;
  string line;
  int *buff;
  sml->counter++;
  getline(cin, line);
  strsize = line.size();
  if( strsize > INPMAX ) {
    strsize = INPMAX;
  }
  buff = new int[ (strsize+2)/2 ];
  for( x = 0; x < (strsize+2)/2; ++x) {
    buff[x] = 0;
  }
  for( length = 1; length <= strsize; ++length ) {
    if( (length%2) == 0 ) {
      buff[length/2] = line[length-1]*OPFACT; // store in top half
    } else {
      buff[length/2] += line[length-1];
    }
  }
  buff[0] += (length-1)*OPFACT;
  for( x = 0; x < (strsize+2)/2; ++x) {
    sml->memory[sml->operand + x] = buff[x];
  }
  delete buff;
  return 0;
}
  
int opcode_write(machineState *sml)
{
  sml->counter++;		// incremement the instruction counter
  cout << sml->memory[sml->operand] << "  ";
  return 0;
}

int opcode_swrite(machineState *sml)
{
  int x, length;
  sml->counter++;
  x = 0;
  length = sml->memory[sml->operand] / OPFACT;
  while( length ) {
    if( x%2 == 0) {
      cout << static_cast< char >(sml->memory[sml->operand + x/2] % OPFACT);
    } else {
      cout << static_cast< char >(sml->memory[sml->operand + (x+1)/2] / OPFACT);
    }
    length--;
    x++;
  }
  return 0;
}
