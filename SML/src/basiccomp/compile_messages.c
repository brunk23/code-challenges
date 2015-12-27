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
int wmessg(char *messg, struct Node *base) {
  fprintf(stderr,"WARNING: %s:\n",messg);
  if( base ) {
    while( base->type != BASE ) {
      base = base->up;
    }
    fprintf(stderr,"ON LINE #%i: ",base->location);
    fprintf(stderr,"%s", base->val.string);
    fprintf(stderr,"\n\n");
  }
  return 0;
}


/*
 * Print error message and fail.
 */
int emessg(char *messg, struct Node *base) { 
  fprintf(stderr,"ERROR: %s:\n",messg);

  if ( base ) {
    while( base->type != BASE ) {
      base = base->up;
    }
    fprintf(stderr,"ON LINE #%i: ",base->location);
    fprintf(stderr,"%s", base->val.string);
    fprintf(stderr,"\n\n");
  }
  exit(1);
}
