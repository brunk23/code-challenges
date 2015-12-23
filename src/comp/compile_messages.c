/*
 * Functions that exist to give messages to the user of the
 * compiler.
 */

#include <stdio.h>
#include "compiler.h"
#include "compile_messages.h"

int help_menu(char *progname) {
  fprintf(stderr,"Usage: %s {sourcefile} [destination]\n",progname);
  return 0;
}

/*
 * Print error message and fail.
 */
int emessg(int linenumber, char *unedited) {
  if(linenumber) {
    fprintf(stderr,"ON LINE #%i: \"%s\"\n",linenumber, unedited);
  }
  return 1;
}
