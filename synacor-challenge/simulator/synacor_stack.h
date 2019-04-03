#ifndef SYNACOR_STACK_H
#define SYNACOR_STACK_H

enum STACK_CONSTANTS {
  STACKMAX = 512, STACK_ERROR = 32768
};

struct STACKOBJ {
  struct STACKOBJ *next;
  SWORD values[STACKMAX];
  int stack_size;
};

struct STACKOBJ *stack;

int push_word(SWORD);
SWORD pop_word();

#endif
