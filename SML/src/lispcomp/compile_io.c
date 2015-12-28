#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "compiler.h"
#include "compile_io.h"
#include "compile_utility.h"
#include "compile_messages.h"
#include "compile_function.h"

/* Use Empty Place Holder for testing purposes */
int process_source(char *filename, int core[]) {
  FILE *source;
  char *line = 0, *curr = 0;
  int linenumber = 0;           /* for debugging */
  size_t bytes_read;
  ssize_t status;
  
  int retcode = 0;
  int x, y, dest, strtmp, strindex;

  struct Token *base;

  /*
   * Open the source file.  Fail if we can't.
   */
  if( !( source = fopen(filename, "r")) ) {
    currline(filename,strlen(filename)+1,-1);
    emessg("Could not open source file", 1);
  }

  /*
   * Create the base node that our program will be under.
   * This is of type "PROGN" and will have an ID of 1.
   */
  base = malloc(sizeof(struct Token));
  base->symTree = 0;
  base->next = 0;
  base->arg = 0;
  base->type = PROGN;
  base->ID = getID();
  base->location = 0;

  /*
   * This is the first pass of the compiler.
   */
  while(( status = getline(&line, &bytes_read, source)) != -1) {
    linenumber++;
    curr = strtok(line, "\n");
    
    for( x = 0; x < strlen(line); ++x ) {
      if(curr[x] == '(') {
	y = x+1;
	while( curr[x] != ' ' && curr[x] != 0 ) {
	  ++x;
	}
	curr[x] = 0;
	process_functions(&curr[y],base);
	curr[x] = '|';
      }

    }
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
