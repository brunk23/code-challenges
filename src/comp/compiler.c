#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "compiler.h"

int TEMP = 55555;

int main(int argc, char *argv[]) {
  FILE *dest = 0;
  int core[MEMSIZE];		// The memory in the SML machine
  int retcode = 0;
  
  /* COMMAND LINE ARGUMENTS */
  if(argc < 2 ) {
    help_menu(argv[0]);
    return 1;
  }

  /* PROCESS THE FILE AND GENERATE THE OUTPUT */
  if( retcode = process_source(argv[1], core) ) {
    /* Something went wrong processing the source code, abort */
    fprintf(stderr,"ERROR: Compilation failed.\n");
    return retcode;
  }

  if( argc > 2 ) {
    if( retcode = output_core(argv[2], core)) {
      fprintf(stderr,"ERROR: Saving core failed.\n");
      return retcode;
    }
  } else {
    if( retcode = output_core(0, core)) {
      fprintf(stderr,"ERROR: Saving core failed.\n");
      return retcode;
    }
  }
  
  return retcode;
}


int output_core(char *filename, int core[MEMSIZE]) {
  FILE *dest = 0;
  int x = 0;
  
  if( filename ) {
    if( !( dest = fopen(filename, "w")) ) {
      fprintf(stderr,"ERROR: could not open destination file: %s\n", filename);
      return 1;
    }
  } else {
    dest = stdout;
  }

  for( x = 0; x < MEMSIZE; ++x ) {
    fprintf(dest,"%4i ", core[x]);
    if( (x + 1) % 10 == 0 ) {
      fprintf(dest,"\n");
    }
  }

  return 0;
}

int process_source(const char *filename, int core[MEMSIZE]){
  FILE *source;
  char *line = 0, *unedited = 0, *curr = 0;
  size_t unedited_size = 0;
  int linenumber = 0;		/* for debugging */
  size_t bytes_read;
  ssize_t status;
  
  // allow up to 10 symbols per memory spot in the machine
  struct tableEntry symbolTable[MAXSYMS];
  struct tableEntry labels[MEMSIZE];
  int retcode = 0;
  int x, symbol, dest;

  if( !( source = fopen(filename, "r")) ) {
    fprintf(stderr,"ERROR: could not open source file: %s\n", filename);
    return 1;
  }
  
  /*
   * An unresolved label is saved over the -1
   * core memory is 0'd out
   */
  for(x = 0; x < MEMSIZE; ++x) {
    labels[x].type = 0;
    core[x] = 0;
  }
  for(x = 0; x < MAXSYMS; ++x) {
    symbolTable[x].symbol = 0;
    symbolTable[x].type = 0;
    symbolTable[x].location = -1;
  }

  while(( status = getline(&line, &bytes_read, source)) != -1) {
    linenumber++;
    curr = strtok(line, "\n");
    if( unedited ) {
      if( unedited_size < bytes_read ) {
	free(unedited);
	unedited = malloc(bytes_read);
	unedited_size = bytes_read;
      }
    } else {
      unedited = malloc(bytes_read);
      unedited_size = bytes_read;
    }
    strncpy(unedited, curr, unedited_size);
    
    if( retcode = decode_line(curr, core, symbolTable, labels) ) {
      emessg(linenumber,unedited);
      break;
    }
    if( iptr(0) == -1 ) {
      fprintf(stderr,"ERROR: Out of memory.\n");
      emessg(linenumber,unedited);
    }
  }

  /*
   * Assign all data spots to locations right after the end of
   * our code and fill in the missing information. We only assign
   * memory spots for labels we use. This avoids assigning temp
   * spots we didn't actually use.
   */
  for( x = 0; x < MEMSIZE; ++x ) {
    if( labels[x].type != 0 ) {
      for( dest = 0; dest < MAXSYMS; ++dest) {
	if( symbolTable[dest].symbol == labels[x].symbol &&
	    symbolTable[dest].type == labels[x].type ) {
	  if( symbolTable[dest].location == -1 ) {
	    if( symbolTable[dest].type == 'V' ) {
	      symbolTable[dest].location = iptr(1);
	    }
	    if( symbolTable[dest].type == 'C' ) {
	      core[iptr(0)] = symbolTable[dest].symbol;
	      symbolTable[dest].location = iptr(1);
	    }
	  }
	  core[x] += symbolTable[dest].location;
	}
      }
    }
  }
  
  fclose(source);
  if(line) {
    free(line);
  }
  if(unedited) {
    free(unedited);
  }
  return retcode;
}

int decode_line(char *line, int core[MEMSIZE], 
		struct tableEntry symbolTable[MAXSYMS],
		struct tableEntry labels[MEMSIZE])
{
  char *curr = line;
  ssize_t status;
  int symbol, dest;

  char oper[SSIZE];
  struct tableEntry vals[SSIZE];
  int obase = 0;
  int vbase = 0;
  int acc = 0;
  
  /*
   * First we process the line number
   */
  curr = strtok(curr, " ");
  if( !(curr[0]>='0' && (curr[0]<='9')) ) {
    fprintf(stderr,"\nERROR: All lines must start with a line number.\n");
    return 1;
  } else {
    symbol = strtol(curr, 0, 10);
    insert_symbol(symbol, 'L', symbolTable, iptr(0));      
  }

  
  /*
   * Process the rest of the line, one token at a time.
   */
  if ( curr = strtok(0, " ") ) {

    /*
     * rem == comments
     */
    if( strcmp(curr, "rem") == 0 ) {
      return 0;
    }

    /*
     * input == read a value
     */
    if( strcmp(curr, "input") == 0 ) {
      if( (curr = strtok(0, " ")) && curr[0]>='a' && curr[0]<='z') {
	symbol = curr[0];
	dest = insert_symbol(symbol, 'V', symbolTable, iptr(0));
	if( dest == -1 ) {
	  labels[iptr(0)].symbol = symbol;
	  labels[iptr(0)].type = 'V';
	  dest = 0;
	}
	core[iptr(1)] = (READ*OPFACT) + dest;
      } else {
	fprintf(stderr,"ERROR: Missing/Invalid Destination:\n");
	return 1;
      }
      return 0;
    }

    /*
     * print == display a value
     */
    if( strcmp(curr, "print") == 0 ) {
      if( (curr = strtok(0, " ")) && curr[0]>='a' && curr[0]<='z') {
	symbol = curr[0];
	dest = insert_symbol(symbol, 'V', symbolTable, iptr(0));
	if( dest == -1 ) {
	  labels[iptr(0)].symbol = symbol;
	  labels[iptr(0)].type = 'V';
	  dest = 0;
	}
	core[iptr(1)] = (WRITE*OPFACT) + dest;
      } else {
	fprintf(stderr,"ERROR: Missing/Invalid Destination:\n");
	return 1;
      }
      return 0;
    }

    /*
     * goto == unconditional jump
     */
    if( strcmp(curr, "goto") == 0 ) {
      if( (curr = strtok(0, " ")) ) {
	if( (curr[0]>='0') && (curr[0]<='9') ) {
	  symbol = strtol(curr, 0, 10);
	  dest = insert_symbol(symbol, 'L', symbolTable, iptr(0));
	  if( dest == -1 ) {
	    labels[iptr(0)].symbol = symbol;
	    labels[iptr(0)].type = 'L';
	    dest = 0;
	  }
	  core[iptr(1)] = (BRANCH*OPFACT) + dest;
	} else {
	  fprintf(stderr,"ERROR: Missing/Invalid Label:\n");
	  return 1;
	}
      }
      return 0;
    }

    /* 
     * let == assignments
     */
    if( strcmp(curr, "let") == 0 ) {
      obase = 0;
      vbase = 0;
      acc = 0;
      if( (curr = strtok(0, " ")) && curr[0]>='a' && curr[0]<='z') {
	vals[vbase].symbol = curr[0];
	vals[vbase].type = 'V';
	vbase++;
      } else {
	fprintf(stderr,"ERROR: Missing/Invalid Destination:\n");
	return 1;
      }
      
      while( (curr = strtok(0, " ")) ) {
	if( curr[0] >= 'a' && curr[0] <= 'z' ) {
	  vals[vbase].symbol = curr[0];
	  vals[vbase].type = 'V';
	  vbase++;
	}
	if( curr[0] >= '0' && curr[0] <= '9' ) {
	  vals[vbase].symbol = strtol(curr, 0, 10);
	  vals[vbase].type = 'C';
	  vbase++;
	}
	/* These always get pushed */
	if( curr[0] == '=' || curr[0] == '(' ) {
	  oper[obase] = curr[0];
	  obase++;
	}
	if( curr[0] == ')' ) {
	  while( oper[--obase] != '(' ) {
	    vbase--;
	    gencode(oper[obase],vals,vbase,symbolTable,
			   core,labels,&acc);
	  }
	} 
	if( curr[0] == '+' || curr[0] == '-' ) {
	  while ( oplev( oper[obase - 1] )  >= 1 ) {
	    vbase--;
	    gencode(oper[--obase],vals,vbase,symbolTable,
			   core,labels,&acc);
	  }
	  oper[obase] = curr[0];
	  obase++;
	}
	
	if( curr[0] == '*' || curr[0] == '/' || curr[0] == '%') {
	  while( oplev( oper[ obase -1 ] ) >= 2 ) {
	    vbase--;
	    gencode(oper[--obase],vals,vbase,symbolTable,
			   core,labels,&acc);
	  }
	  oper[obase] = curr[0];
	  obase++;
	}
      }
      while( obase > 0 ) {
	vbase--;
	gencode(oper[--obase],vals,vbase,symbolTable,
		       core,labels,&acc);
      }
      
      return 0;
    }

    /*
     * XXXX
     * WORKING, I would like to support expressions on both sides
     * This could be tricky
     * XXXX
     */
    if( strcmp(curr, "if") == 0 ) {
      if( (curr = strtok(0, " ")) && curr[0]>='a' && curr[0]<='z') {
	vals[vbase].symbol = curr[0];
	vals[vbase].type = 'V';
	vbase++;
      } else {
	fprintf(stderr,"ERROR: Left-Hand Side must be variable:\n");
	return 1;
      }
    }
    
    if( strcmp(curr, "end") == 0 ) {
      core[iptr(1)] = (HALT*OPFACT);
      return 0;
    }
  }

  return 0;
}

/*
 * This is a mess with too many arguments, but it is needed to keep
 * the above function from getting even crazier
 */
int gencode(char oper, struct tableEntry vals[], int vbase,
	    struct tableEntry syms[MAXSYMS], int code[MEMSIZE],
	    struct tableEntry labels[MEMSIZE], int *acc)
{
  int left, right, temp;
  char rtype, ltype;
  struct tableEntry *rPtr, *lPtr;
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
    right = insert_symbol(rPtr->symbol, rtype, syms, iptr(0));
    left = insert_symbol(lPtr->symbol, ltype, syms, iptr(0));
    
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
    temp = insert_symbol(TEMP, 'V', syms, iptr(0));
    
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
  
int emessg(int linenumber, char *unedited) {
  fprintf(stderr,"ON LINE #%i: \"%s\"\n",linenumber, unedited);
  return 0;
}
/*
 * returns location if symbol exists
 */
int insert_symbol(int symbol, char type,
		  struct tableEntry symbolTable[MAXSYMS], int not) {
  int x, retcode;
  for( x = 0; x < MAXSYMS; ++x ) {
    if( symbolTable[x].type == 0 ) {
      /* New symbol to be added */
      symbolTable[x].symbol = symbol;
      symbolTable[x].type = type;
      if( type == 'L' ) {
	symbolTable[x].location = iptr(0);
      } else {
	symbolTable[x].location = -1;
      }
      retcode = -1;
      break;
    }
    if( symbolTable[x].symbol == symbol ) {
      if( symbolTable[x].type == type ) {
	retcode = symbolTable[x].location;
	break;
      } else {
	/* This is probably a line number and constant that are
	   conflicting here, warn anyway
	   fprintf(stderr,"WARNING: Duplicate symbols\n"); */
      }
    }
  }
  return retcode;
}

int help_menu(char *progname) {
  fprintf(stderr,"Usage: %s {sourcefile} [destination]\n",progname);
  return 0;
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
