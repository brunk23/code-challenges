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
  LOAD,STACK, QUIT, CALL
};

enum INSTSET {
  halt = 0, set, push, pop, eq, gt, jmp, jt, jf, add, mult,
  mod, and, or, not, rmem, wmem, call, ret, out, in, nop,
  rndm, dread, dwrite
};

char inbuffer[BUFFSIZE];
char debugbuffer[BUFFSIZE];
int inbuffindex;
int breakpoint;

/*
 * In synacor.c
 */
int read_in_file(FILE *, SWORD, long, size_t);
int write_out_file(FILE *, SWORD, long, size_t);
int init_machine();
int scan_inbuff();
void catch_int(int);

/*
 * In synacor_step.c
 */
const char *regname( SWORD );
SWORD print_instruction( SWORD );
int print_addr(SWORD, const char *);


/*
 * In synacor_debug.c
 */
SWORD isdebugcommand(char *);
SWORD next_word(char *, int *);
void process_debug_str(char *);
void debug_print(char *, int *);
void debug_call(char *s, int *i);
void debug_set(char *s, int *i);
void debug_jump(char *s, int *i);
void debug_break(char *s, int *i);
void print_mem_range(SWORD, SWORD);
int print_stack();
int save_state();
int load_state();

/*
 * See the arch-spec sheet for detailed instructions on
 * opcodes
 * In synacor_iset.c
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
int op_rndm();
int op_dread();
int op_dwrite();

/* There are 22 opcodes and we just call them
 * from here. +2 extensions */
typedef int (*iPtr)();
iPtr inst_tble[dwrite + 1];


/*
 * Helper function for memory access to return
 * register values when those are requested.
 */
static inline SWORD get_add(SWORD source) {
  SWORD location_value;

  /* source should be within memory, but if pc was near the top of
   * memory and we pass ( pc + 5 ) or similar, we could read
   * outside the array, protect against that by wrapping down */
  source &= MAXMEM;
  location_value = memory[ source ];

  if( location_value < REGOFFSET ) {
    return location_value;
  } else {
    location_value -= REGOFFSET;
  }
  if( location_value < REGISTERS ) {
    return reg[ location_value ];
  }
  fprintf(stderr,"Invalid access request: %i at %i\n",
	  location_value + REGOFFSET, pc);
  return 0;
}

/*
 * Helper function for memory setting. It also sets
 * registers correctly.
 */
static inline SWORD set_add(SWORD destination, SWORD source) {
  SWORD real_destination;

  /* ensure both are inside memory */
  destination &= MAXMEM;
  source &= MAXMEM;
  real_destination = memory[destination];

  if( real_destination >= REGOFFSET ) {
    real_destination -= REGOFFSET;
    if( real_destination >= REGISTERS ) {
      fprintf(stderr,"Invalid access request: %i at %i\n",
	      destination + REGOFFSET, pc);
      return 0;
    }
    return reg[ real_destination ] = source;
  }
  return memory[ real_destination ] = source;
}

#endif
