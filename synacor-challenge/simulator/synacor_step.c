#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "synacor.h"

/*
 * Pretty print register names.
 */
const char *regname(SWORD r) {
  const char *rname[] = { "r0", "r1", "r2", "r3",
			  "r4", "r5", "r6", "r7" };
  SWORD x;

  x = REGOFFSET - r;

  if( x < 8 ) {
    return rname[x];
  }
  return 0;
}

/*
 * Will print a detailed view of a given address
 */
int print_instruction(SWORD addr) {
  if( memory[addr] > 21 ) {
    fprintf(stderr,"%05i:\tdata  %05i\n",addr,memory[addr]);
  } else {
    switch (memory[addr]) {
    case halt:
      fprintf(stderr,"%05i:\thalt\n",addr);
      break;

    case set:
      fprintf(stderr,"%05i:\tset ",addr);
      fprintf(stderr,"%s",regname(memory[addr+1]));
      fprintf(stderr,", %i\n",memory[addr+2]);
      break;

    case push:
      fprintf(stderr,"%05i:\tpush ",addr);
      if( memory[addr+1] >= r0 && memory[addr+1] <= r7 ) {
	fprintf(stderr,"%s\n",regname(memory[addr+1]));
      } else {
	fprintf(stderr,"%i\n",memory[addr+1]);
      }
      break;

    case pop:
      fprintf(stderr,"%05i:\tpop ",addr);
      if( memory[addr+1] >= r0 && memory[addr+1] <= r7 ) {
	fprintf(stderr,"%s\n",regname(memory[addr+1]));
      } else {
	fprintf(stderr,"%i\n",memory[addr+1]);
      }
      break;

    case eq:
      break;

    case gt:
      break;

    case jmp:
      break;

    case jt:
      break;

    case jf:
      break;

    case add:
      break;

    case mult:
      break;

    case mod:
      break;

    case and:
      break;

    case or:
      break;

    case not:
      break;

    case rmem:
      break;

    case wmem:
      break;

    case call:
      break;

    case ret:
      fprintf(stderr,"%05i:\tret\n",addr);
      break;

    case out:
      break;

    case in:
      break;

    case nop:
      fprintf(stderr,"%05i:\tnop\n",addr);
      break;

    default:
      break;
    }
  }
  return 0;
}
