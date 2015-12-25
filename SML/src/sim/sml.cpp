#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

#include "sml.h"
#include "sml_math.h"
#include "sml_control.h"
#include "sml_memory.h"
#include "sml_stack.h"

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::setw;
using std::string;
using std::ifstream;
using std::setfill;

int main(int argc, char *argv[])
{
  int returnCode = 0;
  int input = 0;
  machineState smlReal;
  machineState *sml = &smlReal;
  bool debug = false;
  int x = 1;
  /*
   * We are going to use a jump table for the commands.
   */
  opPtr instruction_table[MAXOP];

  // If there's an error making the machine, quit.
  if ( (returnCode = init_machine(sml, instruction_table)) ) {
    cout << "ERROR: Failed to create SML Machine." << endl;
    return 1;
  }
  if( argc > 1 ) {
    if( strcmp(argv[1],"-d") == 0 || strcmp(argv[1],"-debug") == 0) {
      debug = true;
      x++;
    }
    ifstream filename;
    filename.open(argv[x], std::ios::in);
    cout << "Opening file: " << argv[x] << endl;
    if( !filename.is_open() ) {
      cout << "Unable to open file" << endl;
      return 1;
    }
    cout << "Opened file: " << argv[x] << endl;
    while( true ) {
      filename >> input;
      if( filename.eof() ) {
	break;
      }
      if( !out_of_bounds(input,MINVAL,MAXVAL) ) {
	smlReal.memory[smlReal.counter++] = input;
      } else {
	cout << "Error in file" << endl;
	return 1;
      }
    }
    if( debug ) {
      memory_dump(sml);
    }
  } else {
    while ( input != EINPUT ) {
      debug = true;
      cout << smlReal.counter << ": ";
      cin >> input;
      if ( !out_of_bounds(input,MINVAL,MAXVAL) ) {
	smlReal.memory[smlReal.counter++] = input;
      }
    }
  }
  smlReal.counter = 0;
  smlReal.running = true;
  while ( smlReal.running ) {
    if(smlReal.counter == MEMSIZE) {
      error_message("COUNTER OVERRAN MEMORY");
      returnCode = 1;
      break;
    }
    smlReal.instructionRegister = smlReal.memory[smlReal.counter];
    smlReal.operationCode = smlReal.instructionRegister / OPFACT;
    smlReal.operand = smlReal.instructionRegister % OPFACT;
    if( smlReal.operationCode >= MAXOP ) {
      smlReal.indirect = true;
      smlReal.operationCode %= MAXOP;
      x = sml->memory[sml->operand] / OPFACT;
      x += sml->memory[sml->operand] % OPFACT;
      if( out_of_bounds( x, 0, MEMSIZE-1) ) {
	sml->running = false;
	error_message("INDIRECT ADDRESS INVALID");
	continue;
      }
      sml->operand = x;
    } else {
      smlReal.indirect = false;
    }
    returnCode=instruction_table[smlReal.operationCode](sml);
  }
  if( debug ) {
    // we only dump the memory if we input the file by hand
    // or we request it
    memory_dump(sml);
  } else {
    cout << endl << endl;
  }
  return returnCode;
}

int init_machine(machineState *sml, opPtr inst_tble[])
{
  // Unsupported OPCODES crash the machine.
  for(int i = 0; i < MAXOP; ++i) {
    inst_tble[i] = opcode_invalid;
  }

  // These are the currently supported instructions
	
  // Arithmatic
  inst_tble[ADD]=opcode_add;
  inst_tble[SUBTRACT]=opcode_subtract;
  inst_tble[MULTIPLY]=opcode_multiply;
  inst_tble[DIVIDE]=opcode_divide;
  inst_tble[MOD]=opcode_mod;

  // memory access
  inst_tble[LOAD]=opcode_load;
  inst_tble[STORE]=opcode_store;

  // i/o
  inst_tble[READ]=opcode_read;
  inst_tble[WRITE]=opcode_write;

  // flow control
  inst_tble[BRANCH]=opcode_branch;
  inst_tble[BRANCHNEG]=opcode_branch_neg;
  inst_tble[BRANCHZERO]=opcode_branch_zero;
  inst_tble[HALT]=opcode_halt;

  // Extended opcodes
  inst_tble[INC]=opcode_inc;
  inst_tble[DEC]=opcode_dec;
  inst_tble[DUMP]=memory_dump;
  inst_tble[NOP]=opcode_nop;

  // Stack opcodes
  inst_tble[PUSH]=opcode_push;
  inst_tble[POP]=opcode_pop;
  inst_tble[CALL]=opcode_call;
  inst_tble[RET]=opcode_ret;
  
  sml->accumulator = 0;
  sml->counter = 0;
  sml->stackPointer = MEMSIZE - 1;
  sml->instructionRegister = 0;
  sml->operationCode = 0;
  sml->operand = 0;
  sml->running = false;
  sml->indirect = false;
  for(int i = 0; i < MEMSIZE; ++i) {
    sml->memory[i] = 0;
  }
  return 0;
}

void error_message(string message)
{
  unsigned int y = message.size();
  cout << "\n\n\t";
  for(unsigned int i = 0; i < y + 4; ++i) {
    cout << "*";
  }
  cout << "\n\t* " << message << " *" << "\n\t";
  for(unsigned int i = 0; i < y + 4; ++i) {
    cout << "*";
  }
  cout << "\n\n\n";
}

int memory_dump(machineState *sml)
{
  cout << "\n\nREGISTERS:" << endl
       << setfill(' ') << setw(20) << "Accumulator" << setw(8)
       << setfill(' ') << sml->accumulator << endl
       << setfill(' ') << setw(20) << "instructionPointer" << setw(8)
       << setfill(' ') << sml->counter << endl
       << setfill(' ') << setw(20) << "stackPointer" << setw(8)
       << setfill(' ') << sml->stackPointer << endl    
       << setfill(' ') << setw(20) << "instructionRegister" << setw(8)
       << setfill(' ') << sml->instructionRegister << endl
       << setfill(' ') << setw(20) << "operationCode" << setw(8)
       << setfill(' ') << sml->operationCode << endl
       << setfill(' ') << setw(20) << "operand" << setw(8)
       << setfill(' ') << sml->operand << endl
       << setfill(' ') << setw(20) << "indirect" << setw(8)
       << setfill(' ') << (sml->indirect ? "true" : "false")
       << endl << endl;
  
  cout << "MEMORY:" << endl;
  cout << setw(10);
  for(int i = 0; i < 10; ++ i) {
    cout << i << setw(7) << "  ";
  }
  cout << endl;
  for(int i = 0; i < MEMSIZE/10 ; ++i) {
    bool used = false;
    for(int j = 0; j < 10; ++j) {
      if( sml->memory[i*10+j] != 0 ) {
	used = true;
	break;
      }
    }
    if( used ) {
      cout << setw(3) << i*10 << " ";
      for(int j = 0; j < 10; ++j) {
	cout << setw(7) << sml->memory[i*10+j] << " ";
      }
      cout << endl;
    }
  }
  cout << endl;

  sml->counter++;
  return 0;
}

bool out_of_bounds(int n,int min, int max) {
  return ( (n > max) || (n < min) );
}
