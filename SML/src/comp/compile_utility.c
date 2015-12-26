/*
 * Utility functions for the compiler, they are used by other
 * functions to perform their tasks
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "compiler.h"
#include "compile_utility.h"
#include "compile_messages.h"

/* Returns 0 on failure */
char *getNextToken(char *string, struct Token *token) {
  if( (string = strtok( string, " \t" ) ) ) {
    str2token(string, token);
  }
  return string;
}
  

/*
 * This will allow us to use our instruction pointer more securely.
 * It ensures that it remains in bounds, it is the responsibility
 * of the program to check for -1 return value.
 */
int iptr(int delta) {
  static int instructionPointer = 0;
  int temp;
  
  /* Return value before modification */
  temp = instructionPointer;
  instructionPointer += delta;
    
  if( instructionPointer < 0 ) {
    emessg("Memory underun",1);
  }
  if( instructionPointer >= MEMSIZE ) {
    emessg("Memory overrun",1);
  }
  
  return temp;
}

/*
 * Call with the length of a string when you know it.
 */
int sptr(int delta) {
  static int stringPointer = MEMSIZE-1;

  stringPointer -= delta;

  if( stringPointer < 0 ) {
    emessg("Too many strings",1);
  }

  if( stringPointer >= MEMSIZE ) {
    emessg("How do you get less characters than you start with",1);
  }

  return stringPointer;
}

/*
 * Utility function to help with processing expressions
 */
int oplev(char n) {
  int x = 0;
  switch (n) {
  case '(':
    x = 0;
    break;

  case '=':
    x = 3;
    break;

  case '+':
  case '-':
    x = 6;
    break;

  case '*':
  case '/':
  case '%':
    x = 9;
    break;

  default:
    break;
  }
  return x;
}

int str2token(char *string, struct Token *token)
{
  int symbol = 0, x = 0;
  char *s;
  if( string[x] == '"' ) {
    /* This is a string constant. Save it as such. */
    s = currline(0,0,0);
    while( s[x] != 0 ) {
      symbol += s[x];
      x++;
    }
    symbol += strlen(s);
    token->symbol = symbol;
    token->type = 'S';
    token->location = stringtable(-1) + MEMSIZE;
    return 0;
  }

  while( string[x] != 0 ) {
    if( (string[x] >= 'A') && (string[x] <= 'Z') ) {
      string[x] = tolower(string[x]);
    }
    ++x;
  }

  token->type = 'K';		/* K-eyword */
  token->location = -1;
  if( (strcmp(string,"let") == 0)) {
    token->symbol = LET;
    return 0;
  }
  if( (strcmp(string,"rem") == 0) ) {
    token->symbol = REM;
    return 0;
  }
  if( (strcmp(string,"goto") == 0) ) {
    token->symbol = GOTO;
    return 0;
  }
  if( (strcmp(string,"sinput") == 0) ) {
    token->symbol = SINPUT;
    return 0;
  }
  if( (strcmp(string,"sprint") == 0) ) {
    token->symbol = SPRINT;
    return 0;
  }
  if ( (strcmp(string,"input") == 0) ) {
    token->symbol = INPUT;
    return 0;
  }
  if( (strcmp(string,"print") == 0) ) {
    token->symbol = PRINT;
    return 0;
  }
  if( (strcmp(string,"if") == 0) ) {
    token->symbol = IF;
    return 0;
  }
  if( (strcmp(string,"inc") == 0) ) {
    token->symbol = INC;
    return 0;
  }
  if( (strcmp(string,"dec") == 0) ) {
    token->symbol = DEC;
    return 0;
  }
  if( (strcmp(string,"end") == 0) ) {
    token->symbol = END;
    return 0;
  }
  if( (strcmp(string,"call") == 0) ) {
    token->symbol = CALLF;
    return 0;
  }
  if( (strcmp(string,"ret") == 0) ) {
    token->symbol = RETF;
    return 0;
  }
  if( (strcmp(string,"==") == 0) ) {
    token->symbol = EQL;
    return 0;
  }
  if( (strcmp(string,"!=") == 0) ) {
    token->symbol = DNE;
    return 0;
  }
  if( (strcmp(string,">=") == 0) ) {
    token->symbol = GTE;
    return 0;
  }
  if( (strcmp(string,">") == 0) ) {
    token->symbol = GT;
    return 0;
  }
  if( (strcmp(string,"<=") == 0) ) {
    token->symbol = LTE;
    return 0;
  }
  if( (strcmp(string,"<") == 0) ) {
    token->symbol = LT;
    return 0;
  }

  if( (string[0] == '-' && string[1] == 0) ||
      string[0] == '+' || string[0] == '*' ||
      string[0] == '/' || string[0] == '%' ||
      string[0] == '(' || string[0] == ')' ||
      string[0] == '=' ) {
    token->symbol = string[0];
    token->type = 'M';		/* M-ath operation */
    token->location = -1;
    return 0;
  }
  
  if( (string[0] >= '0' && string[0] <= '9') ||
      (string[0] == '-' || string[0] == '+') ) {
    symbol = strtol(string, 0, 10);
    token->symbol = symbol;
    token->type = 'C';		/* C-onst (or L-ine number) */
    token->location = -1;
    return 0;
  }

  if( (string[0] >= 'a' && string[0] <= 'z') ) {
    token->symbol = string[0];
    token->type = 'V';		/* V-ariable */
    token->location = -1;
    return 0;
  }
  
  return 1;
}

/*
 * returns location if symbol exists
 */
int insert_symbol(struct Token *token, struct Token symbolTable[MAXSYMS]) {
  int x;
  for( x = 0; x < MAXSYMS; ++x ) {
    if( symbolTable[x].type == 0 ) {
      /* New symbol to be added */
      symbolTable[x].symbol = token->symbol;
      symbolTable[x].type = token->type;
      symbolTable[x].location = token->location;
      break;
    }
    if( symbolTable[x].symbol == token->symbol ) {
      if( symbolTable[x].type == token->type ) {
	if( symbolTable[x].location < 0 ) {
	  symbolTable[x].location = token->location;
	}
	break;
      }
    }
  }
  if(x == MAXSYMS) {
    emessg("Enough is never enough",1);
  }
  return symbolTable[x].location;
}

/*
 * Test if we know where a token is. If so, return the memory location.
 * If not, make this location (in labels) one we need to check later
 */
int test_symbol(struct Token *token, struct Token syms[MAXSYMS],
		struct Token labels[MEMSIZE]) {
  int loc;

  loc = insert_symbol(token, syms);
  if( loc == -1 || token->type == 'S' ) {
    labels[iptr(0)].symbol = token->symbol;
    labels[iptr(0)].type = token->type;
    labels[iptr(0)].location = token->location;
    loc = 0;
  }
  return loc;
}

/*
 * Real simply utility function to return the required number
 * of bytes for a string.
 */
int stringmemreq(int length) {
  return (length+2)/2;
}

int stringtable(int location) {
  static int stringTable[MEMSIZE];
  static int offset = 1;
  
  int x = 0, y = 0, count = 0;
  char *s;

  if( location < 0 ) {
  
    if( !(s = currline(0,0,0)) ) {
      emessg("Line doesn't exist to add to stringtable",1);
    }
    while( s[x] != '\"' && s[x] != 0 ) {
      x++;
    }
    y = ++x;
    while( s[x] != '\"' && s[x] != 0 ) {
      x++;
      count++;
    }
  
    stringTable[ offset ] = count * OPFACT; /* start with length */
    for( x = 0; x < count; ++x ) {
      if( x%2 == 0 ) {
	stringTable[ offset + x/2 ] += s[ y + x ];
      } else {
	stringTable[ offset + (x+1)/2 ] = s[ y + x ] * OPFACT;
      }
    }

    x = offset;
    offset += count; /* Make room for it */
  
    return x;
  }

  /* return the value at location */
  if( location >= MEMSIZE ) {
    emessg("Value outside string table range",1);
  }
  
  return stringTable[location];
}
