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

struct Node *str2node(char *str, struct Node *up)
{
  struct Node *node = 0;
  int x = 0, y=0;
  char *s, *string;
  enum NTYPE ntype;
  enum KEYWORDS keyword;
  union SymbolValue n;

  string = strtok(str,"\t ");
  if( !string || string[0] =='#' ) {
    /* There was nothing left or we started a comment */
    return node;
  }
  
  if( string[x] == '"' ) {
    /* This is a string constant. This should only be
     * called from a base node XXX we should check this! XXX */
    s = up->val.string;
    while( s[x] != 0 && s[x] != '"' ) {
      x++;
    }
    x++;
    while( s[x+y] != 0 && s[x+y] != '"' ) {
      y++;
    }
    if( !(n.string = malloc( y + 1)) ) {
      emessg("Couldn't allocate memory for string.",1);
    }
    strncpy(n.string, s[x], y);
    n.string[y] = 0;
    
    node = newNode(STRING, up, 0, 0, n, 0);

    return node;
  }

  while( string[x] != 0 ) {
    if( (string[x] >= 'A') && (string[x] <= 'Z') ) {
      string[x] = tolower(string[x]);
    }
    ++x;
  }

  for(x = 0; x < 1; x++) {
    n.keyword = NONE;
    if( (strcmp(string,"let") == 0)) {
      n.keyword = LET;
      break;
    }
    if( (strcmp(string,"rem") == 0) ) {
      n.keyword = REM;
      break;
    }
    if( (strcmp(string,"goto") == 0) ) {
      n.keyword = GOTO;
      break;
    }
    if( (strcmp(string,"sinput") == 0) ) {
      n.keyword = SINPUT;
      break;
    }
    if( (strcmp(string,"sprint") == 0) ) {
      n.keyword = SPRINT;
      break;
    }
    if ( (strcmp(string,"input") == 0) ) {
      n.keyword = INPUT;
      break;
    }
    if( (strcmp(string,"print") == 0) ) {
      n.keyword = PRINT;
      break;
    }
    if( (strcmp(string,"if") == 0) ) {
      n.keyword = IF;
      break;
    }
    if( (strcmp(string,"inc") == 0) ) {
      n.keyword = INC;
      break;
    }
    if( (strcmp(string,"dec") == 0) ) {
      n.keyword = DEC;
      break;
    }
    if( (strcmp(string,"end") == 0) ) {
      n.keyword = END;
      break;
    }
    if( (strcmp(string,"call") == 0) ) {
      n.keyword = CALLF;
      break;
    }
    if( (strcmp(string,"ret") == 0) ) {
      n.keyword = RETF;
      break;
    }
    
    if( (strcmp(string,"==") == 0) ) {
      n.keyword = EQL;
      break;
    }
    if( (strcmp(string,"!=") == 0) ) {
      n.keyword = DNE;
      break;
    }
    if( (strcmp(string,">=") == 0) ) {
      n.keyword = GTE;
      break;
    }
    if( (strcmp(string,">") == 0) ) {
      n.keyword = GT;
      break;
    }
    if( (strcmp(string,"<=") == 0) ) {
      n.keyword = LTE;
      break;
    }
    if( (strcmp(string,"<") == 0) ) {
      n.keyword = LT;
      break;
    }
  }
  if( n.keyword != NONE ) {
    node = newNode(KEYWORD, up, 0, 0, n, 0);
    return node;
  }

  if( (string[0] == '-' && string[1] == 0) ||
      string[0] == '+' || string[0] == '*' ||
      string[0] == '/' || string[0] == '%' ||
      string[0] == '(' || string[0] == ')' ||
      string[0] == '=' ) {
    n.operator = string[0];
    node = newNode(OPERATOR, up, 0, 0, n, 0);
    return node;
  }
  
  if( (string[0] >= '0' && string[0] <= '9') ||
      (string[0] == '-' || string[0] == '+') ) {
    n.number = strtol(string, 0, 10);
    node = newNode(CONSTANT, up, 0, 0, n, 0);
    return node;
  }

  ntype = VARIABLE;
  if( string[ strlen(string)-1 ] == ':' ) {
    /* this is a label not a variable */
    string[ strlen(string)-1 ] = 0;
    ntype = LABEL;
  }
  if( !(n.string = malloc( strlen(string) + 1)) ) {
    emessg("Couldn't allocate string.",1);
  }
  strncpy(n.string, string, strlen(string));
  n.string[strlen(string)] = 0;
  node = newNode(ntype, up, 0, 0, n, 0);
  return node;
}

/*
 * Real simple utility function to return the required number
 * of bytes for a string.
 */
int stringmemreq(int length) {
  return (length+2)/2;
}

int stringtable(int location) {
  static int stringTable[MEMSIZE];
  static int offset = 1;
  
  int x = 0, y = 0, count = 0;
  char *s, curr;

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
      if( s[x] == '\\' ) {
	count--;
      }
      count++;
    }
  
    stringTable[ offset ] = count * OPFACT; /* start with length */
    for( x = 0; x < count; ++x ) {
      curr = s[ y + x ];
      if( curr == '\\' ) {
	y++;
	switch (s[ y + x ]) {
	case 'r':
	  curr = '\r';
	  break;

	case 'n':
	  curr = '\n';
	  break;

	case '\\':
	  curr = '\\';
	  break;

	case 't':
	  curr = '\t';
	  break;

	default:
	  curr = s[ y + x];
	  break;
	}
      }
      if( x%2 == 0 ) {
	stringTable[ offset + (x)/2 ] += curr;
      } else {
	stringTable[ offset + (x+1)/2 ] = curr * OPFACT;
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
