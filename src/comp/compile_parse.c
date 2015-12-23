#include <stdio.h>
#include "compiler.h"
#include "compile_parse.h"
#include "compile_utility.h"

int TEMP = 55555;

char *parseLet(struct Token symbolTable[MAXSYMS],
	       struct Token labels[MEMSIZE], int core[MEMSIZE]) {
  struct Token inpt, *inptPtr = 0;
  char oper[SSIZE], *string;
  struct Token vals[SSIZE];
  int obase = 0;
  int vbase = 0;
  int acc = 0;
  
  inpt.symbol = 0;
  inpt.type = 0;
  inpt.location = -1;
  inptPtr = &inpt;
  
  if( (string = getNextToken(0, inptPtr)) ) {
    if( inpt.type == 'V' ) {
      vals[vbase].symbol = inpt.symbol;
      vals[vbase].type = inpt.type;
      vals[vbase].location = inpt.location;
      vbase++;
    } else {
      fprintf(stderr,"ERROR: Missing/Invalid Destination:\n");
      return 0;
    }
  }
  while( (string = getNextToken(0, inptPtr)) ) {
    if( inpt.type == 'V' || inpt.type == 'C' ) {
      vals[vbase].symbol = inpt.symbol;
      vals[vbase].type = inpt.type;
      vals[vbase].location = inpt.location;
      vbase++;
    }
    /* These always get pushed */
    if( inpt.symbol == '=' || inpt.symbol == '(' ) {
      oper[obase] = inpt.symbol;
      obase++;
    }
    if( inpt.symbol == ')' ) {
      while( oper[--obase] != '(' ) {
	vbase--;
	gencode(oper[obase],vals,vbase,symbolTable,
		core,labels,&acc);
      }
    } 
    if( inpt.symbol == '+' || inpt.symbol == '-' ) {
      while ( oplev( oper[obase - 1] )  >= 1 ) {
	vbase--;
	gencode(oper[--obase],vals,vbase,symbolTable,
		core,labels,&acc);
      }
      oper[obase] = inpt.symbol;
      obase++;
    }
    
    if( inpt.symbol == '*' || inpt.symbol == '/' || inpt.symbol == '%') {
      while( oplev( oper[ obase -1 ] ) >= 2 ) {
	vbase--;
	gencode(oper[--obase],vals,vbase,symbolTable,
		core,labels,&acc);
      }
      oper[obase] = inpt.symbol;
      obase++;
    }
  }
  while( obase > 0 ) {
    vbase--;
    gencode(oper[--obase],vals,vbase,symbolTable,
	    core,labels,&acc);
  }
  
  return string;
}

/*
 * This is a mess with too many arguments, but it is needed to keep
 * the above function from getting even crazier
 */
int gencode(char oper, struct Token vals[], int vbase,
	    struct Token syms[MAXSYMS], int code[MEMSIZE],
	    struct Token labels[MEMSIZE], int *acc)
{
  int left, right, temp;
  char rtype, ltype;
  struct Token *rPtr, *lPtr, tempToken;
  if( oper != '=' ) {
    rPtr = &vals[vbase];
    lPtr = &vals[vbase-1];
  } else {
    lPtr = &vals[vbase];
    rPtr = &vals[vbase-1];
  }
  rtype = rPtr->type;
  ltype = lPtr->type;
  
  /* If both are constants, we will do the math here */
  if( rtype != 'C' || ltype != 'C' ) {
    right = insert_symbol(rPtr, syms);
    left = insert_symbol(lPtr, syms);
    
    if(left == -1) {
      labels[iptr(0)].symbol = lPtr->symbol;
      labels[iptr(0)].type = ltype;
      left = 0;
    }
    if( iptr(0) > 0 && (code[iptr(0) - 1] / OPFACT) == STORE ) {
      /* The last command was a store, was it storing
       * the value we are trying to load now? If so, we can
       * write the command there instead */
      if( labels[ iptr(0) - 1 ].symbol == lPtr->symbol &&
	  labels[ iptr(0) - 1 ].type == ltype ) {
	if( (*acc) > 0 ) {
	  iptr(-1);
	}
      }	else {
	code[iptr(1)] = (LOAD*OPFACT) + left;
	(*acc)++;
      }
    } else {
	code[iptr(1)] = (LOAD*OPFACT) + left;
	(*acc)++;
    }

    if(right == -1) {
      labels[iptr(0)].symbol = rPtr->symbol;
      labels[iptr(0)].type = rtype;
      right = 0;
    }

    TEMP++;
    tempToken.symbol = TEMP;
    tempToken.type = 'V';
    tempToken.location = -1;
    temp = insert_symbol(&tempToken, syms);
    
    switch( oper ) {
    case '+': /* load left, add right store temp */
      code[iptr(1)] = (ADD*OPFACT) + right;
      break;

    case '-': /* load left, subtract right store temp */
      code[iptr(1)] = (SUBTRACT*OPFACT) + right;
      break;
      
    case '*': /* load left, multiply right store temp */
      code[iptr(1)] = (MULTIPLY*OPFACT) + right;
      break;
      
    case '/': /* load left, divide right store temp */
      code[iptr(1)] = (DIVIDE*OPFACT) + right;
      break;
      
    case '%': /* load left, mod right store temp */
      code[iptr(1)] = (MOD*OPFACT) + right;;
      break;
      
    case '=': /* load right store left */
      temp = right;
      break;
      
    default:
      break;
    }

    if( temp == -1) {
      labels[iptr(0)].symbol = TEMP;
      labels[iptr(0)].type = 'V';
      temp = 0;
    }
    /* Save the result */
    code[iptr(1)] = (STORE*OPFACT) + temp;

    vals[vbase-1].symbol = TEMP;
    vals[vbase-1].type = 'V';
  } else {
    switch (oper) {
    case '+':
      vals[vbase-1].symbol += vals[vbase].symbol;
      break;
    case '-':
      vals[vbase-1].symbol -= vals[vbase].symbol;
      break;
    case '*':
      vals[vbase-1].symbol *= vals[vbase].symbol;
      break;
    case '/':
      vals[vbase-1].symbol /= vals[vbase].symbol;
      break;
    case '%':
      vals[vbase-1].symbol %= vals[vbase].symbol;
      break;
    default:
      break;
    }
  }
  return 0;
}
