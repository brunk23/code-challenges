#ifndef SML_H
#define SML_H

#include <string>

using std::string;

#define MEMSIZE 100
#define MAXOP 100
#define MAXVAL 9999
#define MINVAL -9999

/*
 * Not all these opcodes were part of the original spec.
 *   Extended Opcodes Include: INC, DEC, MOD, DUMP, NOP
 */
enum OPCODES {
	READ = 10, WRITE,
	LOAD = 20, STORE,
	ADD = 30, SUBTRACT, DIVIDE, MULTIPLY, MOD,
	BRANCH = 40, BRANCHNEG, BRANCHZERO, HALT,
	INC = 60, DEC,
	NOP = 98, DUMP
};

struct machineState {
	int accumulator;
	int counter;
	int instructionRegister;
	int operationCode;
	int operand;
	int memory[MEMSIZE];
	bool running;
};

typedef int (*opPtr)(machineState *);

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

#endif
