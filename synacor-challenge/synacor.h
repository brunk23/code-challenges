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
unsigned short int memory[32768];
unsigned short int reg[8];
unsigned short int *stack = 0;
int pc = 0;

#define REGOFFSET 32768

enum REGISTERS {
  r0 = 32768, r1, r2, r3, r4, r5, r6, r7
};

enum INSTSET {
  halt = 0, set, push, pop, eq, gt, jmp, jt, jf, add, mult,
  mod, and, or, not, rmem, wmem, call, ret, out, in, noop
};

struct STACKOBJ {
  struct STACKOBJ *next;
  unsigned short int value;
};

/*
 * See the arch-spec sheet for detailed instructions on
 * opcodes
 */

/* There are 22 opcodes and we just call them
 * from here. */
typedef int (*iPtr)();
iPtr inst_tble[22];
