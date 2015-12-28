#include <stdio.h>
#include "compiler.h"
#include "compile_debug.h"

int printToken(struct Token *curr) {
  printf("token Addr: %p\n",curr);
  printf("symTree Addr: %p\n",curr->symTree);	/* Pointer to the bottom */
  printf("parent Addr: %p\n",curr->parent);
  printf("currarg Addr: %p\n",curr->currarg);      	/* Points to the next argument */
  printf("nextarg Addr: %p\n",curr->nextarg);      	/* Points to the next argument */
  printf("type: %s\n", printType(curr->type));	/* what is this */
  printf("ID: %i\n", curr->ID);
  if( curr->type == INTERNAL ) {
    printf("ID VAL: %s\n",printInternalID(curr->ID));
  }
  printf("location: %i\n",curr->location);
  return 0;
}

char *printType(enum TYPE type) {
  switch (type) {
  case CONSTANT:
    return "Constant";
    break;

  case FUNCTION:
    return "Function";
    break;

  case INTERNAL:
    return "Internal Function";
    break;

  case VARIABLE:
    return "Variable";
    break;

  case STRING:
    return "String";
    break;

  default:
    break;
  }
  return "Unknown type!";
}

char *printInternalID(int id) {
  char *values[] = {
    "", "SETF", "INPUT", "IF", "PRINT", "INCM", "DECM", "DNE",
    "EQL", "GT", "GTE", "LT", "LTE", "DEFUN", "PROGN", "SUM"
  };

  if( id >= 0 && id < 16 ) {
    return values[id];
  }
  return values[0];
}
