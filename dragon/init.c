#include "global.h"

struct entry keywords[] = {
  {"div",DIV},
  {"mod",MOD},
  {0, 0}
};

/* loads keywords into symtable */
void init() {
  struct entry *p;
  lastchar = -1;		/* last used position in lexemes */
  lastentry = 0;		/* we set these here */
  for( p = keywords; p->token; ++p ) {
    insert(p->lexptr, p->token);
  }
}
