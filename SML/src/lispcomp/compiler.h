#ifndef COMPILER_H
#define COMPILER_H

#include "../shared/sml_shared.h"

enum KEYWORDS {
  SETF = 1, INPUT, IF, PRINT, INCM, DECM, DNE,
  EQL, GT, GTE, LT, LTE, DEFUN, PROGN, SUM
};

enum TYPE {
  CONSTANT, FUNCTION, INTERNAL, VARIABLE, STRING
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

struct Token {
  struct Symbol *symTree;	/* Pointer to the bottom */
  struct Token *parent;         /* Points to the function that contains this */
  struct Token *nextarg;       	/* Points to the next argument */
  struct Token *currarg;
  enum TYPE type;		/* what is this */
  int ID;
  int location;		       
};

#endif
