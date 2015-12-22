#ifndef COMPILER_H
#define COMPILER_H

#define LINESIZE 80
#define MEMSIZE 100
#define MAXSYMS 1000
#define MAXOP 100
#define OPFACT 100
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

struct tableEntry {
  int symbol;
  char type;			// 'C', 'L', 'V'
  int location;			// 00 to 99
};

int help_menu(char *);
int process_source(const char *, int[]);
int insert_symbol(int, char, struct tableEntry[], int);
int emessg(int, char *);
int output_core(char *, int[]);
int decode_line(char *,int[],int *,struct tableEntry [],struct tableEntry[]);

#endif
