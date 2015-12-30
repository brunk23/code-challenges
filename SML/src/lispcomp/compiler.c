#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "compiler.h"

int main(int argc, char *argv[]) {
  int core[MEMSIZE];		/* The memory in the SML machine */
  int retcode = 0;
  int source = 0, dest = 0;
  
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

  printf("Source: %s\nDestination: %s\n",argv[source],argv[dest]);
  
  /* PROCESS THE FILE AND GENERATE THE OUTPUT */
  if( (retcode = process_source(argv[source], core)) ) {
    /* Something went wrong processing the source code, abort */
    emessg("Compilation failed",retcode);
  }

  if( dest ) {
    if( (retcode = output_core(argv[dest], core)) ) {
      emessg("Saving core failed",retcode);
    }
  } else {
    if( (retcode = output_core(0, core)) ) {
      emessg("Saving core failed",retcode);
    }
  }
  
  return retcode;
}
