#include <stdio.h>

#include "synacor.h"
#include "synacor_random.h"

int random_fill_buffer() {
  FILE *source;
  int words_read = 0;

  if( !( source = fopen("/dev/urandom", "r"))) {
    fprintf(stderr, "Could not load random device! Using rndm is undefined.\n");
    return -1;
  }

  words_read = fread( synacor_rndm.random_buffer,
		      sizeof(SWORD),
		      RANDOM_BUFFER_SIZE,
		      source);

  if( source ) {
    fclose( source );
  }
  return words_read;
}

int init_random() {
  int size = 0;
  size = random_fill_buffer();
  synacor_rndm.random_numbers_left = size;
  return size;
}

SWORD next_random() {
  if( synacor_rndm.random_numbers_left == 0 ) {
    synacor_rndm.random_numbers_left = random_fill_buffer();
  }
  if( synacor_rndm.random_numbers_left > 0 ) {
    synacor_rndm.random_numbers_left--;
    return synacor_rndm.random_buffer[synacor_rndm.random_numbers_left];
  }
  return 0;
}
