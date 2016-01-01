#include <stdio.h>

#include "synacor.h"

/*
 * Synacor Emulator
 */

int read_in_file(const char *);

int main(int argc, char *argv[]) {

  if( argc != 2 ) {
    fprintf(stderr,"Usage: %s {challenge.bin}\n",argv[0]);
    return 1;
  }
  
  if( !read_in_file(argv[1])) {
    fprintf(stderr,"Could not read file: %s\n",argv[1]);
    return 1;
  }

  return 0;
}

int read_in_file(const char *filename) {
  FILE *source;
  int words_read = 0;

  if( !( source = fopen(filename, "r"))) {
    fprintf(stderr,"Could not open file for reading.\n");
    return 0;
  }

  words_read = fread(memory,
		     sizeof(unsigned short int),
		     REGOFFSET,
		     source);
  fprintf(stderr,"Initializing Machine...\n");
  fprintf(stderr,"Read %i words into memory\n",words_read);

  if( source ) {
    fclose(source);
  }
  return words_read;
}
