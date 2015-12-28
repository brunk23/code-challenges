#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "compiler.h"
#include "compile_io.h"
#include "compile_utility.h"
#include "compile_messages.h"
#include "compile_function.h"
#include "compile_debug.h"

/* Use Empty Place Holder for testing purposes */
int process_source(char *filename, int core[]) {
  FILE *source;
  char *line = 0, *curr = 0;
  int linenumber = 0;           /* for debugging */
  size_t bytes_read;
  ssize_t status;
  char seperator;
  
  int retcode = 0;
  int x, y, constant, dest, strtmp, strindex;

  struct Token *base,*ctoken, *temptoken;
  struct Symbol *symbolPtr = 0, *newSymbol = 0;

  /*
   * Open the source file.  Fail if we can't.
   */
  if( !( source = fopen(filename, "r")) ) {
    currline(filename,strlen(filename)+1,-1);
    emessg("Could not open source file", 1);
  }

  /*
   * Create the base node that our program will be under.
   * This is of type "INTERNAL" and will have an ID of PROGN.
   */
  base = malloc(sizeof(struct Token));
  base->symTree = 0;
  base->arg = 0;
  base->parent = 0;
  base->type = INTERNAL;
  base->ID = PROGN;
  base->location = 0;

  /*
   * This is the first pass of the compiler.
   */
  ctoken = base;
  while(( status = getline(&line, &bytes_read, source)) != -1) {
    linenumber++;
    curr = line;
    
    for( x = 0; x < strlen(line); ++x ) {

      /* HANDLE ENTERING FUNCTIONS AND CHANGING SCOPE */
      if(curr[x] == '(') {
	y = x+1;
        ++x;
	while( curr[x] != ' ' && curr[x] != 0 &&
	       curr[x] != ')' && curr[x] != '(' &&
	       curr[x] != '\t' && curr[x] != '\n' ) {
	  ++x;
	}
	seperator = curr[x];
	curr[x] = 0;
	process_functions(&curr[y],ctoken);
	ctoken = ctoken->arg;
	curr[x] = seperator;
      }

      if(curr[x] == ')') {
	/* move context up to parent */
	ctoken = ctoken->parent;
	x++;
      }
      /* END CHANGING SCOPE AND FUNCTION HANDLING */

      /* START PROCESSING VARIABLE NAME */
      if( (curr[x] >= 'a' && curr[x]<='z') ) {
	y = x;
	while( (curr[x] >= 'a' && curr[x]<='z') ||
	       (curr[x] >= '0' && curr[x]<='9') ||
	       (curr[x] == '-') ) {
	  ++x;
	}
	seperator = curr[x];
	curr[x] = 0;
	symbolPtr = ctoken->symTree;
	while( symbolPtr ) {
	  if( symbolPtr->type == VARIABLE) {
	    if( strcmp(&curr[y],symbolPtr->val.string) == 0 ) {
	      break;
	    }
	  }
	  symbolPtr = symbolPtr->next;
	}
	if(ctoken->type == INTERNAL &&
	   (ctoken->ID == DEFUN || ctoken->ID == SETF)) {
	  if( !symbolPtr ) {
	    symbolPtr = malloc(sizeof(struct Symbol));
	    if(!symbolPtr) {
	      emessg("Failed to allocate symbol",ctoken);
	    }
	    /* XXX This should set the parent XXX */
	    symbolPtr->next = ctoken->symTree;
	    ctoken->symTree=symbolPtr;
	    symbolPtr->type = VARIABLE;
	    symbolPtr->ID = getID();
	    symbolPtr->val.string = malloc(strlen(&curr[y]) + 1);
	    if(! symbolPtr->val.string) {
	      emessg("Failed to allocate string",ctoken);
	    }
	    strncpy(symbolPtr->val.string, &curr[y],strlen(&curr[y]) +1);
	  }
	}
	if(symbolPtr == 0) {
	  /* Check parent scopes here */
	  emessg("Variable not found in current Scope!",1);
	} else {
	  ctoken->arg = malloc(sizeof(struct Token));
	  if(!ctoken->arg) {
	    emessg("Failed to create Token",1);
	  }
	  ctoken->arg->parent = ctoken->parent;
	  ctoken->arg->symTree = ctoken->symTree;
	  ctoken = ctoken->arg;
	  ctoken->arg = 0;
	  ctoken->type = VARIABLE;
	  ctoken->ID = symbolPtr->ID;
	  ctoken->location = -1;
	}
      }
      /* END PROCESSING VARIABLE NAME */
      
      /* START PROCESSING CONSTANT */
      if( (curr[x] >= '0' && curr[x]<='9') ||
	  (curr[x] == '-' || curr[x]=='+') ) {
	/* This is the start of a constant, constants are
	 * automatically saved and saved at global scope */
	temptoken = ctoken;
	while(temptoken->parent != 0) {
	  temptoken = ctoken->parent;
	}
	symbolPtr = temptoken->symTree
	while( symbolPtr ) {
	  if( symbolPtr->type == CONSTANT &&
	      symbolPtr->val.value == constant ) {
	    /* already in table */
	    break;
	  }
	}
	if( !symbolPtr ) {
	  /* Not in the table, add it */
	}
      }
      /* END PROCESSING CONSTANT */
      
    }
  }

  ctoken = base;
  while (ctoken) {
    printToken(ctoken);
    printf("\n\n");
    ctoken = ctoken->arg;
  }



  /*
   * Before we actually compile the parsed tree
   * Zero out the core memory
   */
  for( x = 0; x < MEMSIZE; ++x ) {
    core[x] = 0;
  }

  return 0;
}

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
