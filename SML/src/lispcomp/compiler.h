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
  
struct Cons {
  struct Cons *car;
  struct Cons *cdr;
  char *string;
  int value;
  enum TYPE type;		/* what is this */
  int ID;
  int args;
  int location;
  int resolved;
};

#include "compile_conditionals.h"
#include "compile_debug.h"
#include "compile_io.h"
#include "compile_math.h"
#include "compile_messages.h"
#include "compile_symbol.h"
#include "compile_tree.h"
#include "compile_utility.h"

#endif
