/*
 * Functions that exist to give messages to the user of the
 * compiler.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compiler.h"
#include "compile_messages.h"

int help_menu(char *progname) {
  fprintf(stderr,"Usage: %s {sourcefile} [destination]\n",progname);
  return 0;
}

/*
 * Just print warnings, don't fail.
 */
int wmessg(char *messg) {
  int linenumber = 0;
  char *cline = 0;

  linenumber = lineno(0);
  cline = currline(0, 0, 0); 
  fprintf(stderr,"WARNING: %s:\n",messg);
  if(linenumber) {
    fprintf(stderr,"ON LINE #%i: ",linenumber);
    if(cline) {
      fprintf(stderr,"%s", cline);
    }
    fprintf(stderr,"\n");
  }
  return 0;
}


/*
 * Print error message and fail.
 */
int emessg(char *messg, int returncode) {
  int linenumber = 0;
  char *cline = 0;

  linenumber = lineno(0);
  cline = currline(0, 0, 0); 

  fprintf(stderr,"ERROR: %s:\n",messg);
  if(linenumber) {
    fprintf(stderr,"ON LINE #%i: ",linenumber);
    if(cline) {
      fprintf(stderr,"%s", cline);
    }
    fprintf(stderr,"\n");
  }
  currline("", 0, 0);		/* Free currline */
  exit(returncode);
}

/*
 * Store and print the current line
 */
char *currline(const char *n, size_t bytes_read, int line) {
  static char *unedited = 0;
  static size_t size = 0;
  static int linenumber = 0;

  /* Use 0 as first argument to just return the current value */
  if( n == 0 ) {
    return unedited;
  }
  
  char *temp = 0;
  lineno(line);
  
  /* If we call with 0 as the second argument, free the string */
  if( bytes_read == 0 ) {
    if( unedited ) {
      free(unedited);
      unedited = 0;
      size = 0;
      linenumber = 0;
      return unedited;
    }
  }

  /*
   * If unedited is NULL, realloc() behaves like malloc() and
   * allocates a new object.
   */
  if( size < bytes_read ) {
    temp = realloc( unedited, bytes_read );
    if( !temp ) {
      /* failed to allocate enough memory */
      free( unedited );
      unedited = 0;
      size = 0;
      emessg("Failed to allocate enough memory in currline()\n",2);
    }
    size = bytes_read;
    unedited = temp;
  }
  strncpy(unedited, n, size);	/* Copy the new string in */

  return unedited;
}

/*
 * Simple way to save and view the line number
 */
int lineno(int x) {
  static int linenumber = 0;
  if( x ) {
    linenumber = x;
  }

  return linenumber;
}
