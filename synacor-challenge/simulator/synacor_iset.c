#include <stdio.h>
#include <stdlib.h>

#include "synacor.h"

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
  set_add(pc+1, inbuffer[inbuffindex++]);
  pc += 2;
  return 0;
}

/* Just increment the program counter and return */
int op_nop() {
  ++pc;
  return 0;
}