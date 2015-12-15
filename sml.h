#ifndef SML_H
#define SML_H

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


#endif
