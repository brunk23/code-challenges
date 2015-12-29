#include <stdio.h>
#include "compiler.h"
#include "compile_debug.h"

int printToken(struct Token *curr) {

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
    "EQL", "GT", "GTE", "LT", "LTE", "DEFUN", "PROGN", "SUM", "EOL"
  };

  if( id >= 0 && id < 17 ) {
    return values[id];
  }
  return values[0];
}
