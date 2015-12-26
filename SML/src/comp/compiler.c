#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "compiler.h"
#include "compile_utility.h"
#include "compile_io.h"
#include "compile_messages.h"
#include "compile_parse.h"
#include "compile_node.h"

int main(int argc, char *argv[]) {
  int code[MEMSIZE];
  int retcode = 0;
  
  /* COMMAND LINE ARGUMENTS */
  if(argc < 2 ) {
    help_menu(argv[0]);
    return 1;
  }

  /* PROCESS THE FILE AND GENERATE THE OUTPUT */
  if( (retcode = process_source(argv[1], core)) ) {
    /* Something went wrong processing the source code, abort */
    emessg("Compilation failed",retcode);
  }

  if( argc > 2 ) {
    if( (retcode = output_core(argv[2], core)) ) {
      emessg("Saving core failed",retcode);
    }
  } else {
    if( (retcode = output_core(0, core)) ) {
      emessg("Saving core failed",retcode);
    }
  }
  
  return retcode;
}
