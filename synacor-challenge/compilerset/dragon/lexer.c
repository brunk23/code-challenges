#include "global.h"

char lexbuf[BSIZE];
int lineno = 1;
int tokenval = NONE;

/* Lexical analyzer */
int lexan() {
  int t, p, b;
  while(1) {

    t = getchar();

    if( t == ' ' || t == '\t' )
      ;				/* strip whitespace */
    else if( t == '\n' )
      lineno += 1;
    else if( isdigit(t) ) {
      /* t is a digit */
      ungetc(t, stdin);
      scanf("%d", &tokenval);
      return NUM;
    }
    else if( isalpha(t) ) {
      /* t is a character */
      b = 0;
      while( isalpha(t) ) {
	  lexbuf[b] = t;
	  t = getchar();
	  b += 1;
	  if ( b >= BSIZE ) {
	    error("compiler error");
	  }
      }
      lexbuf[b] = EOS;
      if( t != EOF )
	ungetc(t, stdin);
      p = lookup(lexbuf);
      if( p == 0 ) {
	p = insert(lexbuf, ID);
      }
      tokenval = p;
      return symtable[p].token;
    }
    else if( t == EOF )
      return DONE;
    else {
      tokenval = NONE;
      return t;
    }
  }
}
	
      
