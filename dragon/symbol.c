#include "global.h"
#include <string.h>

/* returns position of entry for s */
int lookup( char *s ) {
  int p;
  for( p = lastentry; p > 0; --p) {
    if( strcmp(symtable[p].lexptr, s) == 0) {
      return p;
    }
  }
  return 0;
}

/* returns position of entry for s */
int insert( char *s, int tok) {
  int len;
  len = strlen(s);		/* strlen computers length of s */
  if( lastentry + 1 > SYMMAX ) {
    error("symbol table full");
  }
  if( lastentry + len + 1 >= STRMAX ) {
    error("lexemes array full");
  }
  lastentry++;
  symtable[lastentry].token = tok;
  symtable[lastentry].lexptr = &lexemes[lastchar + 1];
  lastchar = lastchar + len + 1;
  strlcpy(symtable[lastentry].lexptr, s, len+1);
  return lastentry;
}
