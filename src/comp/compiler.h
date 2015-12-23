#ifndef COMPILER_H
#define COMPILER_H

#include "../shared/sml_shared.h"

#define MAXSYMS 1000
#define SSIZE 25

struct Token {
  int symbol;
  char type;			// 'C', 'L', 'V'
  int location;			// 00 to 99
};

enum KEYWORDS {
  LET = 1, REM, GOTO, INPUT, IF, PRINT, END
};

#endif
