#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "compiler.h"
#include "compile_utility.h"
#include "compile_io.h"
#include "compile_messages.h"
#include "compile_parse.h"

int main(int argc, char *argv[]) {
  int core[MEMSIZE];		// The memory in the SML machine
  int retcode = 0;
  
  /* COMMAND LINE ARGUMENTS */
  if(argc < 2 ) {
    help_menu(argv[0]);
    return 1;
  }

  /* PROCESS THE FILE AND GENERATE THE OUTPUT */
  if( (retcode = process_source(argv[1], core)) ) {
    /* Something went wrong processing the source code, abort */
    fprintf(stderr,"ERROR: Compilation failed.\n");
    return retcode;
  }

  if( argc > 2 ) {
    if( (retcode = output_core(argv[2], core)) ) {
      fprintf(stderr,"ERROR: Saving core failed.\n");
      return retcode;
    }
  } else {
    if( (retcode = output_core(0, core)) ) {
      fprintf(stderr,"ERROR: Saving core failed.\n");
      return retcode;
    }
  }
  
  return retcode;
}
