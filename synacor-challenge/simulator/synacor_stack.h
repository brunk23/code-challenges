#ifndef SYNACOR_STACK_H
#define SYNACOR_STACK_H

enum STACK_CONSTANTS {
  STACKMAX = 32768, STACK_ERROR = 32768
};

struct STACKOBJ {
  SWORD values[STACKMAX];
  int stack_size;
} synacor_stack;

static inline int push_word(SWORD value) {
  if( synacor_stack.stack_size < STACKMAX ) {
    synacor_stack.values[synacor_stack.stack_size] = value;
    synacor_stack.stack_size++;
    return 0;
  }
  fprintf(stderr, "Fatal error: Out of stack!\n");
  return 1;
}

static inline SWORD pop_word() {
  if( synacor_stack.stack_size > 0 ) {
    synacor_stack.stack_size--;
    return synacor_stack.values[synacor_stack.stack_size];
  }
  fprintf(stderr, "Pop from empty stack!\n");
  return STACK_ERROR;
}

static inline void init_stack() {
  synacor_stack.stack_size = 0;
}

#endif
