#include <stdio.h>

#include "synacor_a.h"

int main(int argc, char *argv[]) {
  int retcode = 0, source = 0, dest = 0;
  
  /* COMMAND LINE ARGUMENTS */
  for( retcode = 1; retcode < argc; retcode++) {
    if( strcmp(argv[retcode],"-o" ) == 0 ) {
      dest = retcode + 1;
      retcode++;
    } else {
      if( !source ) {
        source = retcode;
      } else {
        source = 0;
        break;
      }
    }
  }

  /* Make sure the command line arguments are correct */
  if( !source || dest >= argc || (dest == 0 && argc > 2) ) {
    help_menu(argv[0]);
    return 1;
  }

  init_machine();
  
  return 0;
}

int init_machine() {
  int x;

  /* Zero memory for use */
  for( x = 0; x < REGOFFSET; ++x) {
    memory[x] = 0;
  }

  return 0;
}

int help_menu(const char *progname) {
  fprintf(stderr,"Usage: %s {source} [-o destination]\n",progname);
  return 0;
}
