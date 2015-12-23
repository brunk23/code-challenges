#include <stdio.h>
#include "compiler.h"
#include "compile_parse.h"
#include "compile_utility.h"
#include "compile_messages.h"

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
      emessg("Missing/Invalid Destination",1);
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
    right = test_symbol(rPtr, syms, labels);
    left = test_symbol(lPtr, syms, labels);
    
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

    right = test_symbol(rPtr, syms, labels);

    TEMP++;
    tempToken.symbol = TEMP;
    tempToken.type = 'V';
    tempToken.location = -1;
    
    /* We can't use test_symbol, because we split the check and
     * the attempt to add it to the unknown values */
    temp = insert_symbol( &tempToken, syms);
    
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

    /* We can't use test_symbol, because we split the check and
     * the attempt to add it to the unknown values */
    if( temp == -1) {
      labels[iptr(0)].symbol = TEMP;
      labels[iptr(0)].type = 'V';
      labels[iptr(0)].location = -1;
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

char *parseIf(struct Token symbolTable[MAXSYMS],
	       struct Token labels[MEMSIZE], int core[MEMSIZE]) {
  struct Token left, oper, right, gt, dest;
  int leftloc, rightloc, destloc;
  char *string;  

  /*
   * For the moment, all conitionals must be in the following
   * format:
   * TOKEN EQOP TOKEN goto ADDRESS
   */
  string = getNextToken( 0, &left);
  string = getNextToken( 0, &oper);
  string = getNextToken( 0, &right);
  string = getNextToken( 0, &gt);
  string = getNextToken( 0, &dest);

  if( !string || gt.symbol != GOTO || dest.type != 'C' ) {
    emessg("Conditional Parse Error",1);
  }
  dest.type = 'L';		/* Make dest a line number */
  
  switch (oper.symbol) {

  case EQL:
  case DNE:
  case GT:
  case GTE:
    /* EQL: load right, subtract left, branch zero dest
     * DNE: load right, subtract left, branch zero ip + 2, branch dest
     * GT: load right, subtract left, branch negative dest
     * GTE: load right, subtract left, branch neg dest, branch zero dest
     */

    /* load right */
    rightloc = test_symbol(&right, symbolTable, labels);
    core[iptr(1)] = (LOAD*OPFACT) + rightloc;

    /* subtract left */
    leftloc = test_symbol(&left, symbolTable, labels);
    core[iptr(1)] = (SUBTRACT*OPFACT) + leftloc;

    if( oper.symbol == EQL ) {
      /* if zero, we branch because they were equal */
      destloc = test_symbol(&dest, symbolTable, labels);
      core[iptr(1)] = (BRANCHZERO*OPFACT) + destloc;
    } else {
      
      if( oper.symbol == DNE ) {
	/* here we skip one instruction, if they were equal */
	core[iptr(1)] = (BRANCHZERO*OPFACT) + iptr(0) + 2;
	/* if we get here, they weren't equal, so unconditional branch */
	destloc = test_symbol(&dest, symbolTable, labels);
	core[iptr(1)] = (BRANCH*OPFACT) + destloc;
      } else {
	
	if( oper.symbol == GT || oper.symbol == GTE ) {
	  /* if the result was negative, left was greater than right */
	  destloc = test_symbol(&dest, symbolTable, labels);
	  core[iptr(1)] = (BRANCHNEG*OPFACT) + destloc;
	  
	  if( oper.symbol == GTE ) {
	    /* if it wasn't GT, we check if they were equal */
	    destloc = test_symbol(&dest, symbolTable, labels);
	    core[iptr(1)] = (BRANCHZERO*OPFACT) + destloc;
	  }
	}
      }
    }
    break;

  case LT:
  case LTE:
    /* load left value */
    leftloc = test_symbol(&left, symbolTable, labels);
    core[iptr(1)] = (LOAD*OPFACT) + leftloc;

    /* subtract right value */
    rightloc = test_symbol(&right, symbolTable, labels);
    core[iptr(1)] = (SUBTRACT*OPFACT) + rightloc;

    /* branch negative (left was less than right) */
    destloc = test_symbol(&dest, symbolTable, labels);
    core[iptr(1)] = (BRANCHNEG*OPFACT) + destloc;

    /* if LTE, we also branch if zero */
    if( oper.symbol == LTE ) {
      destloc = test_symbol(&dest, symbolTable, labels);
      core[iptr(1)] = (BRANCHZERO*OPFACT) + destloc;
    }
    break;
    
  default:
    break;
  }
  return string;
}
