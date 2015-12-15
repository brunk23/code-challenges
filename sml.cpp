#include <iostream>
#include <iomanip>
#include <string>

#include "sml.h"

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::setw;
using std::string;

int opcode_invalid(machineState *);
int opcode_add(machineState *);
int opcode_inc(machineState *);
int opcode_dec(machineState *);
int opcode_subtract(machineState *sml);
int opcode_multiply(machineState *sml);
int opcode_divide(machineState *sml);
int opcode_mod(machineState *sml);
int opcode_load(machineState *sml);
int opcode_store(machineState *sml);
int opcode_read(machineState *sml);
int opcode_write(machineState *sml);
int opcode_branch(machineState *sml);
int opcode_branch_neg(machineState *sml);
int opcode_branch_zero(machineState *sml);
int opcode_nop(machineState *sml);
int opcode_halt(machineState *sml);
int init_machine(machineState *, opPtr[]);
int memory_dump(machineState *sml);
void error_message(string message);
bool out_of_bounds(int,int,int);

int main()
{
	int returnCode = 0;
	int input = 0;
	machineState smlReal;
	machineState *sml = &smlReal;

	/*
	 * We are going to use a jump table for the commands.
	 */
	opPtr instruction_table[MAXOP];

	// If there's an error making the machine, quit.
	if ( (returnCode = init_machine(sml, instruction_table)) ) {
		cout << "ERROR: Failed to create SML Machine." << endl;
		return 1;
	}

	while ( input != -99999 ) { 
		cout << smlReal.counter << ": ";
		cin >> input;
		if ( !out_of_bounds(input,MINVAL,MAXVAL) ) {
			smlReal.memory[smlReal.counter++] = input;
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
		smlReal.operationCode = smlReal.instructionRegister / 100;
		smlReal.operand = smlReal.instructionRegister % 100;
		returnCode=instruction_table[smlReal.operationCode](sml);
	}
	memory_dump(sml);
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

	sml->accumulator = 0;
	sml->counter = 0;
	sml->instructionRegister = 0;
	sml->operationCode = 0;
	sml->operand = 0;
	sml->running = false;
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

// Handle trying to run an unsupported operation
int opcode_invalid(machineState *sml)
{
	error_message("INVALID OPERATION CODE: MACHINE HALTED");
	sml->running = false;
	return -1;
}

int memory_dump(machineState *sml)
{
	cout << "\n\nREGISTERS:" << endl
		<< setw(20) << "Accumulator" << setw(6)
		<< sml->accumulator << endl
		<< setw(20) << "counter" << setw(6)
		<< sml->counter << endl
		<< setw(20) << "instructionRegister" << setw(6)
		<< sml->instructionRegister << endl
		<< setw(20) << "operationCode" << setw(6)
		<< sml->operationCode << endl
		<< setw(20) << "operand" << setw(6)
		<< sml->operand << endl << endl;

	cout << "MEMORY:" << endl;
	cout << setw(8);
	for(int i = 0; i < 10; ++ i) {
		cout << i << setw(6);
	}
	cout << endl;
	for(int i = 0; i < 10; ++i) {
		cout << setw(2) << i*10;
		for(int j = 0; j < 10; ++j) {
			cout << setw(6) << sml->memory[i*10+j];
		}
		cout << endl;
	}
	cout << endl;

	sml->counter++;
	return 0;
}

// add operation
int opcode_add(machineState *sml)
{
	sml->counter++;		// increment the instruction counter	
	sml->accumulator += sml->memory[sml->operand];
	if( out_of_bounds(sml->accumulator, MINVAL, MAXVAL) ) {
		sml->running = false;
		error_message("RESULT OUT OF BOUNDS: MACHINE HALTED");
		return 1;
	}
	return 0;
}

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

// subtract operation
int opcode_subtract(machineState *sml)
{
	sml->counter++;		// increment the instruction counter	
	sml->accumulator -= sml->memory[sml->operand];
	if( out_of_bounds(sml->accumulator, MINVAL, MAXVAL) ) {
		sml->running = false;
		error_message("RESULT OUT OF BOUNDS: MACHINE HALTED");
		return 1;
	}
	return 0;
}

bool out_of_bounds(int n,int min, int max) {
	return ( (n > max) || (n < min) );
}

// simple operation
int opcode_read(machineState *sml)
{
	int input = -99999;
	sml->counter++;		// increment the instruction counter	
	while ( out_of_bounds(input, MINVAL, MAXVAL) ) {
		cout << "? ";
		cin >> input;
		if (out_of_bounds(input, MINVAL, MAXVAL)) {
			cout << "That is not a valid number.\n"
				<< "-9999 to 9999";
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

// simple operation
int opcode_multiply(machineState *sml)
{
	sml->counter++;		// increment the instruction counter	
	sml->accumulator *= sml->memory[sml->operand];
	if( out_of_bounds(sml->accumulator, MINVAL, MAXVAL) ) {
		sml->running = false;
		error_message("RESULT OUT OF BOUNDS: MACHINE HALTED");
		return 1;
	}
	return 0;
}

// division operation
int opcode_divide(machineState *sml)
{
	if ( sml->memory[sml->operand] == 0 ) {
		error_message("DIVIDE BY ZERO: MACHINE HALTED");
		sml->running = false;
		return -1;
	}
	sml->counter++;		// increment the instruction counter	
	sml->accumulator /= sml->memory[sml->operand];
	return 0;
}

// provide the modulus operation
int opcode_mod(machineState *sml)
{
	if ( sml->memory[sml->operand] == 0 ) {
		error_message("DIVIDE BY ZERO: MACHINE HALTED");
		sml->running = false;
		return -1;
	}
	sml->counter++;		// increment the instruction counter	
	sml->accumulator %= sml->memory[sml->operand];
	return 0;
}

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

int opcode_inc(machineState *sml)
{
	sml->counter++;
	sml->memory[sml->operand]++;
	if( out_of_bounds(sml->memory[sml->operand], MINVAL, MAXVAL) ) {
		sml->running = false;
		error_message("RESULT OUT OF BOUNDS: MACHINE HALTED");
		return 1;
	}
	return 0;
}

int opcode_dec(machineState *sml)
{
	sml->counter++;
	sml->memory[sml->operand]--;
	if( out_of_bounds(sml->memory[sml->operand], MINVAL, MAXVAL) ) {
		sml->running = false;
		error_message("RESULT OUT OF BOUNDS: MACHINE HALTED");
		return 1;
	}
	return 0;
}
