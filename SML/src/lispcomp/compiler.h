#ifndef COMPILER_H
#define COMPILER_H

#include "../shared/sml_shared.h"

enum KEYWORDS {
  SETF = 1, INPUT, IF, PRINT, INCM, DECM, DNE,
  EQL, GT, GTE, LT, LTE, DEFUN, PROGN, SUM, EOL
};

enum TYPE {
  LIST, SYMBOL, CONSTANT, FUNCTION, INTERNAL, VARIABLE, STRING
};

union SymVal {
  char *string;
  int value;
};

/*
 * Each Token has a pointer to the last known symbol for the
 * current context. They can find a symbol by going up the tree
 *
 * A symbol leaves context when you go up and *right is not 0
 */
struct Symbol {
  struct Symbol *next;
  union SymVal val;
  enum TYPE type;
  int ID;
  int location;
};
  
struct Cons {
  struct Cons *car;
  struct Cons *cdr;
  union SymVal val;
  enum TYPE type;		/* what is this */
  int ID;
  int args;
  int location;		       
};

#endif
