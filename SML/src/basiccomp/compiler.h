#ifndef COMPILER_H
#define COMPILER_H

#include "../shared/sml_shared.h"

#define MAXSYMS MEMSIZE * 10
#define SSIZE 25

enum NTYPE {
  CONSTANT, LABEL, VARIABLE, CONDITIONAL, OPERATOR,
  KEYWORD, STRING, BASE
};

enum KEYWORDS {
  NONE, LET, REM, GOTO, INPUT, IF, PRINT, INCM, DECM, END, DNE,
  EQL, GT, GTE, LT, LTE, SINPUT, SPRINT, CALLF, RETF
};

union SymbolValue {
  char *string;
  int number;
  char operator;
  enum KEYWORDS keyword;
};

struct Node {
  struct Node *up;		/* For base nodes, this points to the tree */
  struct Node *left;		/* For base nodes this is the prev */
  struct Node *right;		/* for base nodes this is the next */

  enum NTYPE type;			/* The symbol type */

  union SymbolValue val;	/* holds the actual symbol here */

  /* if this is a base node, this is the line number */
  int location;		        /* where in core memory does this node start */
  int resolved;		/* Is this location known */
  int associate;	/* up=0, left = 1, right = 2 */
};


#endif
