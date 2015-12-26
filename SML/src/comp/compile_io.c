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

  /* Read through the core memory, a number at a time, and print
   * it out, with 5 digit integers padded, only output as many
   * values as are used. */
  for( x = 0; x < iptr(0); ++x ) {
    fprintf(dest,"%06i ", core[x]);
    if( (x + 1) % 10 == 0 ) {
      fprintf(dest,"\n");
    }
  }

  if( dest != stdout ) {
    fclose(dest);
  }
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
  
  /* allow up to 10 symbols per memory spot in the machine */
  struct Node *basePtr = 0;
  struct Node *currPtr = 0;

  int retcode = 0;
  int x, dest, strtmp, strindex;

  if( !( source = fopen(filename, "r")) ) {
    currline(filename,strlen(filename)+1,-1);
    emessg("Could not open source file", 1);
  }
  
  /*
   * An unresolved label will have a non-zero type
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

  /*
   * This is the first pass of the compiler.
   */
  while(( status = getline(&line, &bytes_read, source)) != -1) {
    linenumber++;
    curr = strtok(line, "\n");
    currline(curr, bytes_read, linenumber);

    currPtr = newNode(BASE,basePtr,0,currline,linenumber);
    
    if( (retcode = decode_line(curr, core, symbolTable, labels)) ) {
      emessg("Failed to decode line (nonspecific)",1);
    }
  }
  
  /*
   * Assign all data spots to locations right after the end of
   * our code and fill in the missing information. We only assign
   * memory spots for labels we use. This avoids assigning temp
   * spots we didn't actually use.  This is the second pass of the
   * compiler
   */
  for( x = 0; x < MEMSIZE; ++x ) {
    
    /* If the type isn't 0, we need to find the symbol */
    if( labels[x].type != 0 ) {

      /* Walk through the symbol tree looking for symbol */
      for( dest = 0; dest < MAXSYMS; ++dest) {

	/* Check if the symbol and type are equal */
	if( symbolTable[dest].symbol == labels[x].symbol &&
	    (symbolTable[dest].type == labels[x].type) ) {
	  /* If this is our symbol, but the location is not defined
	   * we need to assign it to an area after memory (if it is
	   * a variable or constant). If it is a line number, we
	   * jump to a non-existant location, a fatal error.*/
	  if( symbolTable[dest].location < 0 ) {
	    if( symbolTable[dest].type == 'V' ) {
	      /* All variables are uninitialized by default and should 
	       * be zero */
	      symbolTable[dest].location = iptr(1);
	    }
	    if( symbolTable[dest].type == 'C' ) {
	      /* A constant is the value of its symbol and needs to be
	       * saved in core */
	      core[iptr(0)] = symbolTable[dest].symbol;
	      symbolTable[dest].location = iptr(1);
	    }
	    if( symbolTable[dest].type == 'L' ) {
	      /* The line number printed with this error is wrong */
	      emessg("Jump to Never-Never Land",1);
	    }
	    /* Sometimes let will have marked this memory location
	     * unresolved, it isn't, so clear the flag (just in case */
	    labels[symbolTable[dest].location].type = 0;
	  }
	  if(symbolTable[dest].type == 'S' ) {
	    /* String input. Check to see if we start with something
	     * here. If so, copy it into the current location. If it
	     * is 'S', iptr( stringmemreq(core[iptr(0)]/OPFACT) )
	     * else, iptr( stringmemreq(INPMAX) );
	     */
	    strtmp = symbolTable[dest].location;
	    if( strtmp > MEMSIZE ) {
	      strtmp -= MEMSIZE;
	      symbolTable[dest].location = iptr(0);
	      strindex = stringmemreq(stringtable(strtmp)/OPFACT);
	      while( strindex ) {
		core[ iptr(0)+strindex-1 ] = stringtable( strtmp+strindex-1 );
		strindex--;
	      }
	      iptr( stringmemreq( core[ iptr(0) ] / OPFACT ) );
	    } else {
	      if( strtmp < 0 ) {
		symbolTable[dest].location = iptr(0);
		iptr( stringmemreq( INPMAX ) );
	      }
	    }
	  }

	  /* Now that we know the location of this symbol, add it to
	   * the core location, so the machine code is correct */
	  core[x] += symbolTable[dest].location;
	  break;
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
  if( !curr ) {
    /* Ignore blank lines */
    return 0;
  }
  
  if( inpt.type != 'C' ) {
    emessg("All lines must start with a line number.",1);
  } else {
    inpt.type = 'L';
    inpt.location = iptr(0);	/* Make sure we set the location */
    test_symbol(inptPtr, symbolTable, labels);
  }

  /* Just in case a previous let messed with this location. */
  labels[iptr(0)].symbol = 0;
  labels[iptr(0)].type = 0;
  labels[iptr(0)].location = -1;
  
  /*
   * Process the rest of the line, one token at a time.
   */
  if ( (curr = getNextToken(0, inptPtr)) ) {
    if( inpt.type == 'K' ) {
      switch ( inpt.symbol ) {
      case REM:
	/*
	 * rem == comments
	 * don't process the rest of this line
	 */
	break;
	
      case INPUT:
	/*
	 * input == read a value
	 */
	if( (curr = getNextToken(0, inptPtr)) ) {
	  if( inpt.type == 'V' ) {
	    dest = test_symbol(inptPtr, symbolTable, labels);
	    core[iptr(1)] = (READ*OPFACT) + dest;
	  } else {
	    emessg("Missing/Invalid Destination",1);
	  }
	}
	break;

      case SINPUT:
	/*
	 * input == read a value
	 */
	if( (curr = getNextToken(0, inptPtr)) ) {
	  if( inpt.type == 'V' ||
	      inpt.type == 'S' ) {
	    inpt.type = 'S';
	    dest = test_symbol(inptPtr, symbolTable, labels);
	    core[iptr(1)] = (SREAD*OPFACT) + dest;
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
	  if( inpt.type == 'V' || inpt.type == 'C' ) {
	    dest = test_symbol(inptPtr, symbolTable, labels);
	    core[iptr(1)] = (WRITE*OPFACT) + dest;
	  } else {
	    emessg("Missing/Invalid Destination",1);
	  }
	}
	break;

      case SPRINT:
	/*
	 * print == display a value
	 */
	if( (curr = getNextToken(0, inptPtr))) {
	  if( inpt.type == 'S' ||
	      inpt.type == 'V' ) {
	    if( inpt.type == 'V' ) {
	      inpt.type = 'S';
	    }
	    dest = test_symbol(inptPtr, symbolTable, labels);
	    core[iptr(1)] = (SWRITE*OPFACT) + dest;
	  } else {
	    emessg("Missing/Invalid Destination",1);
	  }
	}
	break;

      case INCM:
	/*
	 * Inc == increment a variable.
	 * I allow constants to be incremented and decremented
	 * although this is highly discouraged and will likely
	 * lead to really obscure errors. It basically creates
	 * a variable with the same name as the number. If you
	 * choose to do this, you can't use the same number in
	 * the program (as a const). This changes it globally.
	 */
	if( (curr = getNextToken(0, inptPtr)) ) {
	  if( inpt.type == 'V' || inpt.type == 'C' ) {
	    if( inpt.type == 'C' ) {
	      wmessg("Why should constants remain the same",1);
	      wmessg("This changes ALL references to this number",0);
	    }
	    dest = test_symbol(inptPtr, symbolTable, labels);
	    core[iptr(1)] = (INC*OPFACT) + dest;
	  } else {
	    emessg("Missing/Invalid Destination",1);
	  }
	}
	break;

      case DECM:
	/*
	 * dec == decrement a variable
	 * The same warnings about changing a constant apply
	 * here as they do above.
	 */
	if( (curr = getNextToken(0, inptPtr)) ) {
	  if( inpt.type == 'V' || inpt.type == 'C' ) {
	    if( inpt.type == 'C' ) {
	      wmessg("Why should constants remain the same",1);
	      wmessg("This changes ALL references to this number",0);
	    }
	    dest = test_symbol(inptPtr, symbolTable, labels);
	    core[iptr(1)] = (DEC*OPFACT) + dest;
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
	    inpt.type = 'L';
	    dest = test_symbol(inptPtr, symbolTable, labels);
	    core[iptr(1)] = (BRANCH*OPFACT) + dest;
	  } else {
	    emessg("Missing/Invalid Label",1);
	  }
	}
	break;

      case CALLF:
	/*
	 * call == function call
	 */
	if( (curr = getNextToken(0,inptPtr)) ) {
	  if( inpt.type == 'C' ) {
	    inpt.type = 'L';
	    dest = test_symbol(inptPtr, symbolTable, labels);
	    core[iptr(1)] = (CALL*OPFACT) + dest;
	  } else {
	    emessg("Missing/Invalid Label",1);
	  }
	}
	break;

      case RETF:
	/*
	 * ret == return from function call
	 */
	core[iptr(1)] = (RET*OPFACT);
	break;

      case LET:
	/* 
	 * let == assignments
	 */
	curr = parseLet(symbolTable, labels, core);
	break;

      case IF:
	/*
	 * if == simply conditional testing
	 */
	curr = parseIf(symbolTable, labels, core);
	break;

      case END:
	/*
	 * end == halt the program
	 */
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
