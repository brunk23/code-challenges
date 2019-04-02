#include <stdio.h>
#include <stdlib.h>

#include "synacor.h"
#include "synacor_stack.h"

/*
 * Implement the actual instruction set
 */

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
  pc += 2;

  return push_word( get_add(pc - 1) );
}

int op_pop() {
  SWORD value = pop_word();

  if( value == REGOFFSET ) {
    return 1;
  }

  set_add(pc + 1, value);
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
  SWORD source;
  source = get_add(pc+2);
  set_add(pc+1, memory[source]);
  pc += 3;
  return 0;
}

int op_wmem() {
  SWORD dest;
  dest = get_add(pc+1);
  memory[dest] = get_add(pc+2);
  pc += 3;
  return 0;
}

int op_call() {
  if( push_word( pc + 2 ) ) {
    return 1;
  }
  pc = get_add(pc + 1);
  return 0;
}

int op_ret() {
  SWORD addr = pop_word();

  if( addr == REGOFFSET ) {
    return 1;
  }

  pc = addr;
  return 0;
}

/* out <a> :: print ascii value of a to screen */
int op_out() {
  printf("%c", get_add(pc+1));
  pc += 2;
  return 0;
}

int op_in() {
  set_add(pc+1, inbuffer[inbuffindex++]);
  pc += 2;
  return 0;
}

/* Just increment the program counter and return */
int op_nop() {
  ++pc;
  return 0;
}

/*
 * The following two instructions (dread/dwrite) are
 * extensions to the standard synacor instruction set
 * that allow us to read/write from "devices", that is
 * files that are connected. Each device has 1 gigaword
 * of addressable space (2^30 words) addressed through
 * segments.
 *
 * dread address dev segment address words
 * dread 0 0 0 0 0
 * would be the default normal command. It reads into
 * memory location 0 from device 0 (first file on the
 * command line) segment 0, address 0 (start of the file)
 * for a full segment (0 = 32768 words).
 *
 */
int op_dread() {

  long start = 0;
  SWORD len = 0;
  start = get_add( pc + 3 );
  start = start << 15;
  start += get_add( pc + 4 );
  len = get_add( pc + 5 );
  if( !len ) {
    len = REGOFFSET;
  }

  read_in_file(devices[ get_add( pc + 2 ) ],
	       get_add( pc + 1 ),
	       start,
	       len );
  pc += 6;
  return 0;
}

/*
 * Need to create a write_out_file that complements
 * read_in_file
 */
int op_dwrite() {

  long start = 0;
  SWORD len = 0;
  start = get_add( pc + 2 );
  start = start << 15;
  start += get_add( pc + 3 );
  len = get_add( pc + 5 );
  if( !len ) {
    len = REGOFFSET;
  }

  write_out_file(devices[ get_add( pc + 1 ) ],
		 get_add( pc + 4 ),
		 start,
		 len);

  pc += 6;
  return 0;
}
