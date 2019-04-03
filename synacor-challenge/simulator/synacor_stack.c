#include <stdio.h>
#include <malloc.h>

#include "synacor.h"
#include "synacor_stack.h"

int push_word(SWORD value) {
  struct STACKOBJ *nbottom = NULL;
  if( stack == NULL || stack->stack_size == STACKMAX ) {
    if( !(nbottom = malloc(sizeof( struct STACKOBJ ))) ) {
      fprintf(stderr, "Could not allocate room on stack.\n");
      return 1;
    }
    nbottom->stack_size = 0;
    nbottom->next = stack;
    stack = nbottom;
  }
  stack->values[stack->stack_size] = value;
  stack->stack_size++;
  return 0;
}

SWORD pop_word() {
  struct STACKOBJ *obottom = NULL;
  SWORD value = STACK_ERROR;
  if( stack ) {
    stack->stack_size--;
    value = stack->values[stack->stack_size];
    if( stack->stack_size == 0 ) {
      obottom = stack;
      stack = stack->next;
      free( obottom );
    }
  } else {
    fprintf(stderr, "Pop from empty stack.\n");
    return value;
  }
  return value;
}
