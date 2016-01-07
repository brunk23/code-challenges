#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "synacor.h"

/*
 * Synacor Emulator
 */

int main(int argc, char *argv[]) {
  struct STACKOBJ *obottom;
  char *test;
  int retval = 0;
  int source = 0;
  
  init_machine();

  for( retval = 1; retval < argc; ++retval ) {
    if( strcmp(argv[retval],"-s") == 0 ) {
      stepmode = 1;
    } else {
      source = retval;
    }
  }

  if( argc < 2 || source == 0 ) {
    fprintf(stderr,"Usage: %s {challenge.bin}\n",argv[0]);
    return 1;
  }

  if( !read_in_file(argv[source])) {
    fprintf(stderr,"Could not read file: %s\n",argv[source]);
    return 1;
  }

  while( 1 ) {
    if( memory[pc] > 21 ) {
      fprintf(stderr,"Error: Invalid operation %i",pc);
      break;
    }

    /* I want to bring the string operation in here */

    if( pc == breakpoint ) {
      stepmode = 1;
    }
    
    if((memory[pc] == in && inbuffindex >= strlen(inbuffer)) ||
       (stepmode)) {
      if(stepmode) {
	print_instruction( pc );
      }
      test = fgets(inbuffer, BUFFSIZE, stdin);
      if( !test || feof(stdin) || ferror(stdin) ) {
	fprintf(stderr,"Input error!");
	return 1;
      }
      inbuffindex = 0;
      if( inbuffer[inbuffindex] == '#' ) {
	enter_debug_mode();
      }
    }

    /* Only halt returns 1 */
    if( ( retval=inst_tble[ get_add(pc) ]() ) ) {
      break;
    }
  }

  /* Unwind the stack and free it */
  while(stack) {
    obottom = stack;
    stack = stack->next;
    free(obottom);
  }
  
  return 0;
}

int init_machine() {
  int x;
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
  inst_tble[21] = op_nop;
  stack = 0;
  pc = 0;
  stepmode = 0;
  breakpoint = REGOFFSET;
  
  /* Reset Input Buffer */
  for( x = 0; x < BUFFSIZE; ++x ) {
    inbuffer[x] = 0;
  }
  inbuffindex = 0;

  /* Reset Memory */
  for( x = 0; x < REGOFFSET; ++x ) {
    memory[x] = 0;
  }

  /* Reset Registers */
  for( x = 0; x < 8; ++x ) {
    reg[x] = 0;
  } 
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

/*
 * Helper function for memory access to return
 * register values when those are requested.
 */
unsigned short int get_add(unsigned short int a) {
  unsigned short int b;
  b = memory[a];
  if( b < REGOFFSET ) {
    return b;
  } else {
    b -= REGOFFSET;
  }
  if( b <= r7 ) {
    return reg[b];
  }
  fprintf(stderr,"Invalid access request: %i at %i\n",
	  b+REGOFFSET, pc);
  return 0;
}

/*
 * Helper function for memory setting. It also sets
 * registers correctly.
 */
unsigned short int set_add(unsigned short int a,
			   unsigned short int b) {
  unsigned short int c;
  c = memory[a];

  if( c >= REGOFFSET ) {
    c -= REGOFFSET;
    if( c >= 8 ) {
      fprintf(stderr,"Invalid access request: %i at %i\n",
	      a+REGOFFSET, pc);
      return 0;
    }
    return reg[c] = b;
  }
  return memory[c] = b;
}
