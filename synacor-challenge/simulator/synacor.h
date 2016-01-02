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
SWORD reg[8];
SWORD pc;
SWORD debugmode;

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

int read_in_file(const char *);
int init_machine();
int enter_debug_mode();
int printstack();
int save_state();
int load_state();
SWORD set_add( SWORD, SWORD );
SWORD get_add( SWORD );
const char *regname( SWORD );
SWORD print_instruction( SWORD );
int print_addr(SWORD, const char *);

/*
 * See the arch-spec sheet for detailed instructions on
 * opcodes
 */
int op_halt();
int op_set();
int op_push();
int op_pop();
int op_eq();
int op_gt();
int op_jmp();
int op_jt();
int op_jf();
int op_add();
int op_mult();
int op_mod();
int op_and();
int op_or();
int op_not();
int op_rmem();
int op_wmem();
int op_call();
int op_ret();
int op_out();
int op_in();
int op_nop();

/* There are 22 opcodes and we just call them
 * from here. */
typedef int (*iPtr)();
iPtr inst_tble[22];

#endif
