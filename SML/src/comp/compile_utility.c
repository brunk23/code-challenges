/*
 * Utility functions for the compiler, they are used by other
 * functions to perform their tasks
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

int str2token(const char *string, struct Token *token)
{
  int symbol = 0;
  if( (strcmp(string,"let") == 0) ||
      (strcmp(string,"rem") == 0) ||
      (strcmp(string,"goto") == 0) ||
      (strcmp(string,"input") == 0) ||
      (strcmp(string,"print") == 0) ||
      (strcmp(string,"if") == 0) ||
      (strcmp(string,"inc") == 0) ||
      (strcmp(string,"dec") == 0) ||
      (strcmp(string,"end") == 0) ||
      (strcmp(string,"==") == 0) ||
      (strcmp(string,"!=") == 0) ||
      (strcmp(string,">=") == 0) ||
      (strcmp(string,">") == 0) ||
      (strcmp(string,"<=") == 0) ||
      (strcmp(string,"<") == 0) ) {
    switch ( string[0] ) {
    case 'l':
      symbol = LET;
      break;

    case 'r':
      symbol = REM;
      break;

    case 'g':
      symbol = GOTO;
      break;

    case 'i':
      if( string[1] == 'n' ) {
	symbol = INPUT;
	if( string[2] == 'c' ) {
	  symbol = INCM;
	}
      } else {
	symbol = IF;
      }
      break;
      
    case 'p':
      symbol = PRINT;
      break;

    case 'e':
      symbol = END;
      break;

    case 'd':
      symbol = DECM;
      break;

    case '!':
      symbol = DNE;
      break;

    case '=':
      symbol = EQL;
      break;

    case '<':
      if( string[1] == '=' ) {
	symbol = LTE;
      } else {
	symbol = LT;
      }
      break;

    case '>':
      if( string[1] == '=' ) {
	symbol = GTE;
      } else {
	symbol = GT;
      }
      break;
	 
    default:
      break;
    }
    token->symbol = symbol;
    token->type = 'K';		/* K-eyword */
    token->location = -1;
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
  
  if( (string[0] >= '0' && string[0] <= '9') || string[0] == '-') {
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
  if( loc == -1 ) {
    labels[iptr(0)].symbol = token->symbol;
    labels[iptr(0)].type = token->type;
    labels[iptr(0)].location = -1;
    loc = 0;
  }
  return loc;
}
