#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "compiler.h"

/* Use Empty Place Holder for testing purposes */
int process_source(char *filename, int core[]) {
  FILE *source;
  char *line = 0, *curr = 0;
  size_t bytes_read;
  ssize_t status;
  
  int x;

  struct Cons *base, *ctoken, *temptoken, *stack;

  /*
   * Open the source file.  Fail if we can't.
   */
  if( !( source = fopen(filename, "r")) ) {
    emessg("Could not open source file", 1);
  }

  /*
   * Create the base node that our program will be under.
   * This is of type "INTERNAL" and will have an ID of PROGN.
   */
  base = malloc(sizeof(struct Cons));
  base->car = 0;
  base->cdr = 0;
  base->type = LIST;
  base->ID = getID();
  base->location = 0;
  base->val.string = 0;
  base->resolved = T;

  base->car = malloc(sizeof( struct Cons));
  base->car->type = INTERNAL;
  base->car->ID = PROGN;
  base->car->location = 0;
  base->val.string = 0;
  base->car->car = 0;
  base->car->cdr = 0;
  base->car->resolved = T;

  stack = 0;
  
  /*
   * This is the first pass of the compiler.
   */
  ctoken = base;
  while(( status = getline(&line, &bytes_read, source)) != -1) {
    curr = line;

    while( 1 ) {
      if( !(temptoken = getNextNode(curr)) ) {
	break;			/* end of line */
      }
      curr = 0;

      if(temptoken->type == EOL) {
	ctoken = pop(&stack);
	continue;
      }

      if( ctoken->car ) {
	ctoken = append(ctoken,temptoken);
      } else {
	ctoken->car = temptoken;
      }
      
      if(temptoken->type == LIST) {
        stack=push(ctoken,stack);
	ctoken = temptoken;
      }
      
    }
      
  }

#ifdef DEBUG
  printList(base);
   printf("\n");
#endif

  /*
   * Before we actually compile the parsed tree
   * Zero out the core memory
   */
  for( x = 0; x < MEMSIZE; ++x ) {
    core[x] = 0;
  }

  compileTree(base,core);
  
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
  fprintf(dest,"\n");

  if( dest != stdout ) {
    fclose(dest);
  }
  return 0;
}
