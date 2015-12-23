/*
 * Functions that perform io are here
 */

#include <stdio.h>
#include "../shared/sml_shared.h"
#include "compile_io.h"

/*
 * Write memory out to a core file.
 */
int output_core(char *filename, int core[MEMSIZE]) {
  FILE *dest = 0;
  int x = 0;
  
  if( filename ) {
    if( !( dest = fopen(filename, "w")) ) {
      fprintf(stderr,"ERROR: could not open destination file: %s\n", filename);
      return 1;
    }
  } else {
    dest = stdout;
  }

  for( x = 0; x < MEMSIZE; ++x ) {
    fprintf(dest,"%4i ", core[x]);
    if( (x + 1) % 10 == 0 ) {
      fprintf(dest,"\n");
    }
  }

  return 0;
}
