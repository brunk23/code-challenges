#include <stdio.h>
#include <string.h>

#include "compiler.h"

int main(int argc, char *argv[]) {
  FILE *source = 0;
  FILE *dest = 0;
  // allow up to 10 symbols per memory spot in the machine
  struct tableEntry symbolTable[MEMSIZE*10];
  int labels[MEMSIZE];
  int core[MEMSIZE];		// The memory in the SML machine
  int instPtr = 0;
  int x;
  
  /*
   * An unresolved label is saved here
   */
  for(x = 0; x < MEMSIZE; ++x) {
    labels[x] = -1;
    core[x] = 0;
  }

  if(argc < 2 ) {
    help_menu(argv[0]);
    return 1;
  }
  if( !( source = fopen(argv[1], "r")) ) {
    fprintf(stderr,"ERROR: could not open source file: %s\n", argv[1]);
    return 1;
  }
  if(argc > 2) {
    if( !( dest = fopen(argv[2], "w")) ) {
      fprintf(stderr,"ERROR: could not open destination file: %s\n", argv[2]);
      return 1;
    }
  } else {
    dest = stdout;
  }
  
  fprintf(dest, "There were %i arguments\n", argc);
  
  return 0;
}

int help_menu(char *progname) {
  fprintf(stderr,"Usage: %s {sourcefile} [destination]\n",progname);
  return 0;
}
