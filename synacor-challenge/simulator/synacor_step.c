#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "synacor.h"

/*
 * Pretty print register names.
 */
const char *regname(SWORD r) {
  const char *rname[8] = { "r0", "r1", "r2", "r3",
			   "r4", "r5", "r6", "r7" };
  SWORD x;

  x = r - REGOFFSET;

  if( x < 8 ) {
    return rname[x];
  }
  return 0;
}

int print_addr(SWORD r,const char *sep) {
  if( memory[r] >= r0 && memory[r] <= r7 ) {
    fprintf(stderr,"%s%s",regname(memory[r]),sep);
  } else {
    fprintf(stderr,"%i%s",memory[r],sep);
  }
  return 0;
}

/*
 * Will print a detailed view of a given address
 */
SWORD print_instruction(SWORD addr) {
  SWORD delta = 0;
  if( memory[addr] > 21 ) {
    fprintf(stderr,"%05i:\tdata\t%05i\n",addr,memory[addr]);
    delta = 1;
  } else {
    switch (memory[addr]) {
    case halt:
      fprintf(stderr,"%05i:\thalt\n",addr);
      delta = 1;
      break;

    case set:
      fprintf(stderr,"%05i:\tset\t",addr);
      print_addr(addr+1,",\t");
      print_addr(addr+2,"\n");
      delta = 3;
      break;

    case push:
      fprintf(stderr,"%05i:\tpush\t",addr);
      print_addr(addr+1,"\n");
      delta = 2;
      break;

    case pop:
      fprintf(stderr,"%05i:\tpop\t[",addr);
      print_addr(addr+1,"]\n");
      delta = 2;
      break;

    case eq:
      fprintf(stderr,"%05i:\teq\t",addr);
      print_addr(addr+1,",\t");
      print_addr(addr+2,",\t");
      print_addr(addr+3,"\n");
      delta = 4;
      break;

    case gt:
      fprintf(stderr,"%05i:\tgt\t",addr);
      print_addr(addr+1,",\t");
      print_addr(addr+2,",\t");
      print_addr(addr+3,"\n");
      delta = 4;
      break;

    case jmp:
      fprintf(stderr,"%05i:\tjmp\t",addr);
      print_addr(addr+1,"\n");
      delta = 2;
      break;

    case jt:
      fprintf(stderr,"%05i:\tjt\t",addr);
      print_addr(addr+1,",\t");
      print_addr(addr+2,"\n");
      delta = 3;
      break;

    case jf:
      fprintf(stderr,"%05i:\tjf\t",addr);
      print_addr(addr+1,",\t");
      print_addr(addr+2,"\n");
      delta = 3;
      break;

    case add:
      fprintf(stderr,"%05i:\tadd\t",addr);
      print_addr(addr+1,",\t");
      print_addr(addr+2,",\t");
      print_addr(addr+3,"\n");
      delta = 4;
      break;

    case mult:
      fprintf(stderr,"%05i:\tmult\t",addr);
      print_addr(addr+1,",\t");
      print_addr(addr+2,",\t");
      print_addr(addr+3,"\n");
      delta = 4;
      break;

    case mod:
      fprintf(stderr,"%05i:\tmod\t",addr);
      print_addr(addr+1,",\t");
      print_addr(addr+2,",\t");
      print_addr(addr+3,"\n");
      delta = 4;
      break;

    case and:
      fprintf(stderr,"%05i:\tand\t",addr);
      print_addr(addr+1,",\t");
      print_addr(addr+2,",\t");
      print_addr(addr+3,"\n");
      delta = 4;
      break;

    case or:
      fprintf(stderr,"%05i:\tor\t",addr);
      print_addr(addr+1,",\t");
      print_addr(addr+2,",\t");
      print_addr(addr+3,"\n");
      delta = 4;
      break;

    case not:
      fprintf(stderr,"%05i:\tnot\t",addr);
      print_addr(addr+1,",\t");
      print_addr(addr+2,"\n");
      delta = 3;
      break;

    case rmem:
      fprintf(stderr,"%05i:\trmem\t",addr);
      print_addr(addr+1,",\t[");
      print_addr(get_add(addr+2),"]\n");
      delta = 3;
      break;

    case wmem:
      fprintf(stderr,"%05i:\twmem\t[",addr);
      print_addr(get_add(addr+1),"],\t");
      print_addr(addr+2,"\n");
      delta = 3;
      break;

    case call:
      fprintf(stderr,"%05i:\tcall\t",addr);
      print_addr(addr+1,"\n");
      delta = 2;
      break;

    case ret:
      fprintf(stderr,"%05i:\tret\n",addr);
      delta = 1;
      break;

    case out:
      fprintf(stderr,"%05i:\tout\t",addr);
      fprintf(stderr,"%c\n",memory[addr+1]);
      delta = 2;
      break;

    case in:
      fprintf(stderr,"%05i:\tin\t",addr);
      print_addr(addr+1,"\n");
      delta = 2;
      break;

    case nop:
      fprintf(stderr,"%05i:\tnop\n",addr);
      delta = 1;
      break;

    default:
      break;
    }
  }
  return delta;
}
