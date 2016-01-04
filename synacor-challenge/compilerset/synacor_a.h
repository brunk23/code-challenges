#ifndef SYNACOR_H
#define SYNACOR_H

/*
 * Synacor Machine Description
 */

/* 15 bit addressable, 16 bit values. Values limited from
 * 0-32768, 8 registers, an unbounded stack. These are globals
 * because I am both too lazy to pass them around, but it is
 * also a reasonable expectation that all parts of the chip can
 * access registers, memory, and the stack. pc is the program
 * counter
 */
typedef unsigned short int SWORD;
SWORD memory[32768];
SWORD pc;

#define BUFFSIZE 160
#define REGOFFSET 32768

enum REGISTERS {
  r0 = 32768, r1, r2, r3, r4, r5, r6, r7
};

enum INSTSET {
  halt = 0, set, push, pop, eq, gt, jmp, jt, jf, add, mult,
  mod, and, or, not, rmem, wmem, call, ret, out, in, nop
};

struct STACKOBJ {
  struct STACKOBJ *next;
  SWORD value;
};

struct STACKOBJ *stack;
char inbuffer[BUFFSIZE];
int strind;

/*
 * Function prototypes
 */
int help_menu( const char * );
int init_machine();
int process_input( const char * );
int findtoken( const char * );
int internal_command( int );
int variable_name( int );
int opcode( int );
int inv_op();
int fill( int );
int read_number( int );

#endif
