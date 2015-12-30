#ifndef COMPILER_H
#define COMPILER_H

#define NODEBUG

#include "../shared/sml_shared.h"

enum KEYWORDS {
  NIL, T, SETF, INPUT, IF, PRINT, INCM, DECM, DNE,
  EQL, GT, GTE, LT, LTE, DEFUN, PROGN,
  SUM, DIFFERENCE, PRODUCT, QUOTIENT, REMAINDER, EOL
};

enum TYPE {
  LIST, SYMBOL, CONSTANT, FUNCTION, INTERNAL, VARIABLE, STRING
};

union SymVal {
  char *string;
  int value;
};
  
struct Cons {
  struct Cons *car;
  struct Cons *cdr;
  union SymVal val;
  enum TYPE type;		/* what is this */
  int ID;
  int args;
  int location;
  int resolved;
};

#endif
