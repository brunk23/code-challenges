#ifndef COMPILER_H
#define COMPILER_H

#include "../shared/sml_shared.h"

#define MAXSYMS MEMSIZE * 10
#define SSIZE 25

/*
 * Types and meanings:
 * L - Label
 * K - Keyword
 * M - Math operator
 *
 * C - Constant
 * V - Variable
 *
 * S - Fixed length string
 * W - Writable string
 */

struct Token {
  int symbol;
  char type;			/* 'C', 'L', 'V', 'K', 'E' */
  int location;			/* 00 to MEMSIZE-1 */
};

enum KEYWORDS {
  LET = 1, REM, GOTO, INPUT, IF, PRINT, INCM, DECM, END, DNE,
  EQL, GT, GTE, LT, LTE, SINPUT, SPRINT, CALLF, RETF
};

#endif
