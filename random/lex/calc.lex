%{
#include <stdlib.h>
#include <math.h>
#include "calc.h"
#include "y.tab.h"
  extern double vbltable[26];
%}

%%

([0-9]+|([0-9]*\.[0-9]+)([eE][-+]?[0-9]+)?) {
  yylval.dval = atof(yytext);
  return NUMBER;
}

[ \t] ;    /* ignore whitespace */

[A-Za-z][A-Za-z0-9]* {  /* return symbol pointer */
  struct symtab *sp = symlook(yytext);
  yylval.symp = sp;
  if( sp->funcptr ) {
    /* it is a function */
    return FUNC;
  } else {
    return NAME;
  }
}

"$"   { return 0; /* end of input */ }

\n    |
.     return yytext[0];

%%
