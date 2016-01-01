#include <stdio.h>
#include <stdlib.h>

#include "synacor.h"

/*
 * Synacor Emulator
 */

int main(int argc, char *argv[]) {
  struct STACKOBJ *obottom;
  int retval = 0;
  
  if( argc != 2 ) {
    fprintf(stderr,"Usage: %s {challenge.bin}\n",argv[0]);
    return 1;
  }

  init_machine();
  
  if( !read_in_file(argv[1])) {
    fprintf(stderr,"Could not read file: %s\n",argv[1]);
    return 1;
  }

  while( 1 ) {
    if( memory[pc] > 21 ) {
      fprintf(stderr,"Error: Invalid operation");
      break;
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
  inst_tble[21] = op_noop;
  stack = 0;
  pc = 0;

  for( x = 0; x < BUFFSIZE; ++x ) {
    inbuffer[x] = 0;
  }
  
  for( x = 0; x < REGOFFSET; ++x ) {
    memory[x] = 0;
  }

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

/* Just return 1 to end the program */
int op_halt() {
  return 1;
}

/* set a b :: set register a to value of b */
int op_set() {
  set_add( pc + 1, get_add( pc + 2 ) );
  pc += 3;
  return 0;
}

int op_push() {
  struct STACKOBJ *nbottom;
  if( !(nbottom = malloc(sizeof(struct STACKOBJ)))) {
    fprintf(stderr,"Could not allocate room on stack\n");
    return 1;
  }
  nbottom->next = stack;
  stack = nbottom;
  stack->value = get_add(pc + 1);
  pc += 2;
  return 0;
}

int op_pop() {
  struct STACKOBJ *obottom;
  if(stack) {
    set_add(pc+1, stack->value);
    obottom = stack;
    stack = stack->next;
    free(obottom);
  } else {
    fprintf(stderr,"Pop from empty stack.\n");
    return 1;
  }
  pc += 2;
  return 0;
}

int op_eq() {
  if( get_add(pc + 2) == get_add(pc + 3) ) {
    set_add(pc + 1, 1);
  } else {
    set_add(pc + 1, 0);
  }
  pc += 4;
  return 0;
}

int op_gt() {
  if( get_add(pc + 2) > get_add(pc + 3) ) {
    set_add(pc + 1, 1);
  } else {
    set_add(pc + 1, 0);
  }
  pc += 4;
  return 0;
}

/* jmp a :: jump to a */
int op_jmp() {
  pc = get_add(pc + 1);
  return 0;
}

/* jt a b :: if a is non-zero, jump to b */
int op_jt() {
  if( get_add(pc + 1) != 0 ) {
    pc = get_add(pc + 2);
  } else {
    pc += 3;
  }
  return 0;
}

/* jf a b :: if a is zero, jump to b */
int op_jf() {
  if( get_add(pc + 1) == 0 ) {
    pc = get_add(pc + 2);
  } else {
    pc += 3;
  }
  return 0;
}

int op_add() {
  unsigned short int sum;
  sum = get_add(pc + 2);
  sum += get_add(pc + 3);
  sum %= REGOFFSET;
  set_add(pc + 1, sum);
  pc += 4;
  return 0;
}

int op_mult() {
  unsigned int temp;
  temp = get_add(pc + 2);
  temp *= get_add(pc + 3);
  temp %= REGOFFSET;
  set_add(pc + 1, temp);
  pc += 4;
  return 0;
}

int op_mod() {
  unsigned short int temp;
  temp = get_add(pc + 2);
  temp %= get_add(pc + 3);
  set_add(pc + 1, temp);
  pc += 4;
  return 0;
}

int op_and() {
  unsigned short int temp;
  temp = get_add(pc + 2);
  temp &= get_add(pc + 3);
  set_add(pc + 1, temp);
  pc += 4;
  return 0;
}

int op_or() {
  unsigned short int temp;
  temp = get_add(pc + 2);
  temp |= get_add(pc + 3);
  set_add(pc + 1, temp);
  pc += 4;
  return 0;
}

int op_not() {
  unsigned short int temp;
  temp = get_add(pc + 2);
  temp = ~temp;
  temp %= REGOFFSET;
  set_add(pc + 1, temp);
  pc += 3;
  return 0;
}

int op_rmem() {
  unsigned short int source;
  source = get_add(pc+2);
  set_add(pc+1, memory[source]);
  pc += 3;
  return 0;
}

int op_wmem() {
  unsigned short int dest;
  dest = get_add(pc+1);
  memory[dest] = get_add(pc+2);
  pc += 3;
  return 0;
}

int op_call() {
  struct STACKOBJ *nbottom;
  if( !(nbottom = malloc(sizeof(struct STACKOBJ)))) {
    fprintf(stderr,"Could not allocate room on stack\n");
    return 1;
  }
  nbottom->next = stack;
  stack = nbottom;
  stack->value = pc + 2;
  pc = get_add(pc+1);
  return 0;
}

int op_ret() {
  struct STACKOBJ *obottom;
  if(stack) {
    pc = stack->value;
    obottom = stack;
    stack = stack->next;
    free(obottom);
  } else {
    fprintf(stderr,"Pop from empty stack.\n");
    return 1;
  }
  return 0;
}

/* out <a> :: print ascii value of a to screen */
int op_out() {
  printf("%c", get_add(pc+1));
  pc += 2;
  return 0;
}

int op_in() {
  static int index = 0;
  char *test;
  char inp = 0;
  
  for( ; index < BUFFSIZE; ++index ) {
    if( inbuffer[index] != 0 ) {
      inp = inbuffer[index];
      inbuffer[index] = 0;
      break;
    }
  }
  if( index == BUFFSIZE ) {
    /* We need more input */
    test = fgets(inbuffer, BUFFSIZE, stdin);
    if( !test || feof(stdin) || ferror(stdin) ) {
      fprintf(stderr,"Input error!");
      return 1;
    }
    for(index = 0 ; index < BUFFSIZE; ++index ) {
      if( inbuffer[index] != 0 ) {
	inp = inbuffer[index];
	inbuffer[index] = 0;
	break;
      }
    }
    if( inp == 0 ) {
      fprintf(stderr,"No valid input found!\n");
      return 1;
    }
  }

  set_add(pc+1, inp);
  pc += 2;
  
  return 0;
}

/* Just increment the program counter and return */
int op_noop() {
  ++pc;
  return 0;
}
