/*
 * Functions that perform io are here
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "compiler.h"
#include "compile_utility.h"
#include "compile_io.h"
#include "compile_messages.h"
#include "compile_parse.h"

/*
 * Write memory out to a core file.
 */
int output_core(char *filename, int core[MEMSIZE]) {
  FILE *dest = 0;
  int x = 0;
  
  if( filename ) {
    if( !( dest = fopen(filename, "w")) ) {
      currline(filename,strlen(filename)+1,-1);
      emessg("Could not open destination file:", 1);
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

  fclose(dest);
  return 0;
}

/*
 * Open and parse the source file
 */
int process_source(char *filename, int core[MEMSIZE]){
  FILE *source;
  char *line = 0, *curr = 0;
  int linenumber = 0;		/* for debugging */
  size_t bytes_read;
  ssize_t status;
  
  // allow up to 10 symbols per memory spot in the machine
  struct Token symbolTable[MAXSYMS];
  struct Token labels[MEMSIZE];
  int retcode = 0;
  int x, dest;

  if( !( source = fopen(filename, "r")) ) {
    currline(filename,strlen(filename)+1,-1);
    emessg("Could not open source file", 1);
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
    currline(curr, bytes_read, linenumber);
    
    if( (retcode = decode_line(curr, core, symbolTable, labels)) ) {
      emessg("Failed to decode line (nonspecific)",1);
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
  return retcode;
}

int decode_line(char *line, int core[MEMSIZE], 
		struct Token symbolTable[MAXSYMS],
		struct Token labels[MEMSIZE])
{
  struct Token inpt, *inptPtr = 0;
  char *curr = line;
  int dest;

  /* We use this for getting our new token */
  inpt.symbol = 0;
  inpt.type = 0;
  inpt.location = -1;
  inptPtr = &inpt;
  
  /*
   * First we process the line number
   */
  curr = getNextToken(curr, inptPtr);
  
  if( inpt.type != 'C' ) {
    emessg("All lines must start with a line number.",1);
  } else {
    inpt.type = 'L';
    insert_symbol(inptPtr, symbolTable);
  }

  /*
   * Process the rest of the line, one token at a time.
   */
  if ( (curr = getNextToken(0, inptPtr)) ) {
    if( inpt.type == 'K' ) {
      switch ( inpt.symbol ) {
      case REM:
	/*
	 * rem == comments
	 */
	break;
	
      case INPUT:
	/*
	 * input == read a value
	 */
	if( (curr = getNextToken(0, inptPtr)) ) {
	  if( inpt.type == 'V' ) {
	    dest = insert_symbol(inptPtr, symbolTable);
	    if( dest == -1 ) {
	      labels[iptr(0)].symbol = inpt.symbol;
	      labels[iptr(0)].type = inpt.type;
	      labels[iptr(0)].location = -1;
	      dest = 0;
	    }
	    core[iptr(1)] = (READ*OPFACT) + dest;
	  } else {
	    emessg("Missing/Invalid Destination",1);
	  }
	}
	break;
	
      case PRINT:
	/*
	 * print == display a value
	 */
	if( (curr = getNextToken(0, inptPtr))) {
	  if( inpt.type == 'V' ) {
	    dest = insert_symbol(inptPtr, symbolTable);
	    if( dest == -1 ) {
	      labels[iptr(0)].symbol = inpt.symbol;
	      labels[iptr(0)].type = inpt.type;
	      labels[iptr(0)].location = -1;
	      dest = 0;
	    }
	    core[iptr(1)] = (WRITE*OPFACT) + dest;
	  } else {
	    emessg("Missing/Invalid Destination",1);
	  }
	}
	break;

      case GOTO:
	/*
	 * goto == unconditional jump
	 */
	if( (curr = getNextToken(0,inptPtr)) ) {
	  if( inpt.type == 'C' ) {
	    inpt.type = 'L';	/* Make it a line */
	    dest = insert_symbol(inptPtr, symbolTable);
	    if( dest == -1 ) {
	      labels[iptr(0)].symbol = inpt.symbol;
	      labels[iptr(0)].type = inpt.type;
	      labels[iptr(0)].location = -1;
	      dest = 0;
	    }
	    core[iptr(1)] = (BRANCH*OPFACT) + dest;
	  } else {
	    emessg("Missing/Invalid Label",1);
	  }
	}
	break;

      case LET:
	/* 
	 * let == assignments
	 */
	curr = parseLet(symbolTable, labels, core);
	break;

      case IF:
	/*
	 * XXXX
	 * WORKING, I would like to support expressions on both sides
	 * This could be tricky
	 * XXXX
	 */
	if( (curr = getNextToken(0, inptPtr) ) ) {
	  // nothing yet.
	} else {
	  emessg("Left-Hand Side must be variable",1);
	  
	}
	break;

      case END:
	core[iptr(1)] = (HALT*OPFACT);
	break;

      default:
	break;
      }
    } else {
      emessg("Expected keyword",1);
    }
  }
  return 0;
}
