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
  fprintf(stderr,"Usage: %s {sourcefile} -o [destination]\n",progname);
  return 0;
}

/*
 * Just print warnings, don't fail.
 */
int wmessg(char *messg, int continued) {
  fprintf(stderr,"\nWARNING: %s:\n",messg);
  return 0;
}


/*
 * Print error message and fail.
 */
int emessg(char *messg, int returncode) {
  fprintf(stderr,"\nERROR: %s:\n",messg);
  exit(returncode);
}
