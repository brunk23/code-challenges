#ifndef SYNACOR_H
#define SYNACOR_H

/*
 * Synacor Machine Description
 */

enum CONSTANTS {
  REGISTERS = 8, MAXDEV = 10, BUFFSIZE = 160, MAXMEM = 32767, REGOFFSET
};

/* 15 bit addressable, 16 bit values. Values limited from
 * 0-32768, 8 registers, an unbounded stack. These are globals
 * because I am both too lazy to pass them around, but it is
 * also a reasonable expectation that all parts of the chip can
 * access registers, memory, and the stack. pc is the program
 * counter
 *
 * Up to 10 attached files at a time
 */
typedef unsigned short int SWORD;
SWORD memory[REGOFFSET];
SWORD reg[REGISTERS];
SWORD pc;
SWORD stepmode;
FILE *devices[MAXDEV];

enum REGISTERS {
  r0 = REGOFFSET, r1, r2, r3, r4, r5, r6, r7,
  INVALID, SET, JUMP, BREAK, CLEAR, PRINT, SAVE, STEP, PC,
  LOAD,STACK, QUIT
};

enum INSTSET {
  halt = 0, set, push, pop, eq, gt, jmp, jt, jf, add, mult,
  mod, and, or, not, rmem, wmem, call, ret, out, in, nop,
  dread, dwrite
};

char inbuffer[BUFFSIZE];
char debugbuffer[BUFFSIZE];
int inbuffindex;
int breakpoint;

int read_in_file(FILE *, SWORD, long, size_t);
int write_out_file(FILE *, SWORD, long, size_t);
int init_machine();
int enter_debug_mode();
int print_stack();
int save_state();
int load_state();
SWORD get_add( SWORD );
SWORD set_add( SWORD, SWORD );
const char *regname( SWORD );
SWORD print_instruction( SWORD );
int print_addr(SWORD, const char *);
SWORD isdebugcommand(char *);
SWORD next_word(char *, int *);
int scan_inbuff();
void process_debug_str(char *);
void debug_print(char *, int *);
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
int op_dread();
int op_dwrite();
void print_mem_range(SWORD, SWORD);
void debug_set(char *, int *);
void debug_jump(char *, int *);
void debug_break(char *, int *);
void catch_int(int);

/* There are 22 opcodes and we just call them
 * from here. +2 extensions */
typedef int (*iPtr)();
iPtr inst_tble[dwrite + 1];

#endif
