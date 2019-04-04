#ifndef SYNACOR_STACK_H
#define SYNACOR_STACK_H

/*
 * We are going to create a stack as large as addressable memory.
 * If someone needs more stack than that for an application, they
 * are really pushing things and could compile the simulator with
 * larger limits or a stack that will grow.
 */
enum STACK_CONSTANTS {
  STACKMAX = 32768, STACK_ERROR = 32768
};

/*
 * Global stack object
 */
struct STACKOBJ {
  SWORD values[STACKMAX];
  int stack_size;
} synacor_stack;

/*
 * We inline the stack functions for speed purposes. They are simple
 * enough to be inline.
 */
static inline int push_word(SWORD value) {
  if( synacor_stack.stack_size < STACKMAX ) {
    synacor_stack.values[synacor_stack.stack_size] = value;
    synacor_stack.stack_size++;
    return 0;
  }
  fprintf(stderr, "Fatal error: Out of stack! %i words should be enough for anyone!\n", STACKMAX);
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

/*
 * Resetting the stack just requires that we reset the counter
 */
static inline void init_stack() {
  synacor_stack.stack_size = 0;
}

/*
 * Return the size of the stack
 */
static inline int stack_size() {
  return synacor_stack.stack_size;
}

/*
 * Return the address of the stack buffer for dump purposes
 */
static inline const SWORD *stack_buffer() {
  return synacor_stack.values;
}

#endif
