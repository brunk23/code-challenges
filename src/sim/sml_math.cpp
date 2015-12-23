/*
 * The math related opcodes for SML
 */

#include "sml.h"
#include "sml_math.h"

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
