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
  if( (string = strtok( string, " " ) ) ) {
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
  case '=':
    x = 0;
    break;

  case '+':
  case '-':
    x = 1;
    break;

  case '*':
  case '/':
  case '%':
    x = 2;
    break;

  default:
    break;
  }
  return x;
}

int str2token(const char *string, struct Token *token)
{
  int symbol = 0;
  if( (string[0] == '-' && string[1] == 0) ||
      string[0] == '+' || string[0] == '*' ||
      string[0] == '/' || string[0] == '%' ||
      string[0] == '(' || string[0] == ')' ||
      string[0] == '=' ) {
    token->symbol = string[0];
    token->type = 'M';		/* math operation */
    token->location = -1;
    return 0;
  }
  if( (strcmp(string,"let") == 0) ||
      (strcmp(string,"rem") == 0) ||
      (strcmp(string,"goto") == 0) ||
      (strcmp(string,"input") == 0) ||
      (strcmp(string,"print") == 0) ||
      (strcmp(string,"if") == 0) ||
      (strcmp(string,"end") == 0) ) {
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

    default:
      break;
    }
    token->symbol = symbol;
    token->type = 'K';		/* K-eyword */
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
  int x, retcode;
  for( x = 0; x < MAXSYMS; ++x ) {
    if( symbolTable[x].type == 0 ) {
      /* New symbol to be added */
      symbolTable[x].symbol = token->symbol;
      symbolTable[x].type = token->type;
      if( token->type == 'L' ) {
	symbolTable[x].location = iptr(0);
      } else {
	symbolTable[x].location = -1;
      }
      retcode = -1;
      break;
    }
    if( symbolTable[x].symbol == token->symbol ) {
      if( symbolTable[x].type == token->type ) {
	retcode = symbolTable[x].location;
	break;
      }
    }
  }
  return retcode;
}
