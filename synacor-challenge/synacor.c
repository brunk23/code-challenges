#include <stdio.h>

#include "synacor.h"

/*
 * Synacor Emulator
 */

int main(int argc, char *argv[]) {
  int retval = 55;
  
  if( argc != 2 ) {
    fprintf(stderr,"Usage: %s {challenge.bin}\n",argv[0]);
    return 1;
  }
  
  if( !read_in_file(argv[1])) {
    fprintf(stderr,"Could not read file: %s\n",argv[1]);
    return 1;
  }

  init_machine();

  while( 1 ) {
    if( memory[pc] > 21 ) {
      fprintf(stderr,"Error: Invalid operation");
      break;
    }

    /* Only halt returns 1 */
    if( ( retval=inst_tble[ memory[pc] ]() ) ) {
      break;
    }
  }

  return 0;
}

int init_machine() {
  inst_tble[0] = op_halt;
  inst_tble[1] = op_set;
  inst_tble[2] = op_push;
  inst_tble[3] = op_pop;
  inst_tble[4] = op_eq;
  inst_tble[5] = op_gt;
  inst_tble[6] = op_jmp;
  inst_tble[7] = op_jt;
  inst_tble[8] = op_jf;
  inst_tble[9] = op_add;
  inst_tble[10] = op_mult;
  inst_tble[11] = op_mod;
  inst_tble[12] = op_and;
  inst_tble[13] = op_or;
  inst_tble[14] = op_not;
  inst_tble[15] = op_rmem;
  inst_tble[16] = op_wmem;
  inst_tble[17] = op_call;
  inst_tble[18] = op_ret;
  inst_tble[19] = op_out;
  inst_tble[20] = op_in;
  inst_tble[21] = op_noop;
  stack = 0;
  pc = 0;

  return 0;
}

int read_in_file(const char *filename) {
  FILE *source;
  int words_read = 0;

  if( !( source = fopen(filename, "r"))) {
    fprintf(stderr,"Could not open file for reading.\n");
    return 0;
  }

  words_read = fread(memory,
		     sizeof(unsigned short int),
		     REGOFFSET,
		     source);
  fprintf(stderr,"Initializing Machine...\n");
  fprintf(stderr,"Read %i words into memory\n",words_read);

  /*  We don't need to worry about the order as
   * little endian is read in correctly.
   * for( x = 0; x < 8; ++x ) {
   * y = memory[x] << 8;
   * y += memory[x] / 0x100;
   * }
   */
  
  if( source ) {
    fclose(source);
  }
  return words_read;
}

/* Just return 1 to end the program */
int op_halt() {
  return 1;
}

int op_set() {
  printf("set unimplemented\n");
  return 0;
}

int op_push() {
  printf("push unimplemented\n");
  return 0;
}

int op_pop() {
  printf("pop unimplemented\n");
  return 0;
}

int op_eq() {
  printf("eq unimplemented\n");
  return 0;
}

int op_gt() {
  printf("gt unimplemented\n");
  return 0;
}

int op_jmp() {
  printf("jmp unimplemented\n");
  return 0;
}

int op_jt() {
  printf("jt unimplemented\n");
  return 0;
}

int op_jf() {
  printf("jf unimplemented\n");
  return 0;
}

int op_add() {
  printf("add unimplemented\n");
  return 0;
}

int op_mult() {
  printf("mult unimplemented\n");
  return 0;
}

int op_mod() {
  printf("mod unimplemented\n");
  return 0;
}

int op_and() {
  printf("and unimplemented\n");
  return 0;
}

int op_or() {
  printf("or unimplemented\n");
  return 0;
}

int op_not() {
  printf("not unimplemented\n");
  return 0;
}

int op_rmem() {
  printf("rmem unimplemented\n");
  return 0;
}

int op_wmem() {
  printf("wmem unimplemented\n");
  return 0;
}

int op_call() {
  printf("call unimplemented\n");
  return 0;
}

int op_ret() {
  printf("ret unimplemented\n");
  return 0;
}

/* out <a> :: print ascii value of a to screen */
int op_out() {
  printf("%c", memory[pc+1]);
  pc += 2;
  return 0;
}

int op_in() {
  printf("in unimplemented\n");
  return 0;
}

/* Just increment the program counter and return */
int op_noop() {
  ++pc;
  return 0;
}
