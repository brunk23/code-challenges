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
 * Write memory out to a core file. This shouldn't have
 * to change with the new code.
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
  
  /* basePtr will always point to the first base node */
  struct Node *basePtr = 0;
  struct Node *currNodePtr = 0;
  union SymbolValue val;

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
    core[x] = 0;
  }

  currNodePtr = basePtr;
  /*
   * This is the first pass of the compiler.
   */
  while(( status = getline(&line, &bytes_read, source)) != -1) {
    linenumber++;
    curr = strtok(line, "\n");

    /* Save the original line and where it was found  in the file
     * in the base node, for error printing */
    if( !(val.string = malloc( strlen(curr) + 1) ) ) {
      emessg("Could not allocate memory for string.",1);
    }
    strncpy(val.string, curr, strlen(curr) + 1);

    currNodePtr = newNode(BASE,currNodePtr,0,val,linenumber);

    /* Make sure the previous base node points to this one */
    currNodePtr->left->right = currNodePtr;

    currNodePtr->up = decode_line(curr, currNodePtr, 0)
    
    }
  }

  return 0;
}


int decode_line(char *line, struct Node *up, struct Node *left)
{
  struct Node *temp = 0, *right = 0, *oper;
  char *curr = line;
  
  /*
   * This line was blank or just a comment
   */
  temp = str2node(curr, up);
  if( !temp ) {
    return 0;
  }
  
  /*
   * This was a label.
   */
  if( temp.type == LABEL ) {
    if( up->type != BASE ) {
      ewarn("Nested labels are foo.",1);
    }
    temp->up = up;
    temp->left = 0;
    temp->associate = 2;
    temp->right = decode_line(0, temp, left);
  }
  
  if( temp.type == KEYWORD ) {
    /* This was a keyword, might be input print etc */
    oper = temp;
    if( !left) {
      left = str2node(0, up);
    } else {
      
  } else {
    oper = str2node(0, base);
    right = str2node(0, base);
  }
  /* XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
   * XX  This function needs to be completed to
   * XX  parse the line correctly
   * XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
   */
  /*
   * Process the rest of the line, one token at a time.
   */

  }

}
