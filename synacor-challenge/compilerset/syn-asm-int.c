#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "synacor_a.h"

int internal_command(int len) {
  char *command;
  int used;
  int x, z;
  
  if( !(command=malloc(len+1))) {
    fprintf(stderr,"Can't get memory!\n");
    return len;
  }
  for( x = 0; x < len; ++x) {
    command[x] = inbuffer[strind + x];
  }
  command[len] = 0;
  strind += len;
  
  if( strcmp(".origin",command) == 0 ) {
    free(command);
    command = 0;
    used = findtoken(inbuffer);

    z = read_number(used);

    fprintf(stderr,"Setting origin to %i\n",z);
    pc = z;
    return used;
  }

  if( command ) {
    free(command);
  }
  return used;
}

/*
 * Will take a token and return the value of it.
 */
int read_number(int used) {
  int x, z;
  char *command;

  if( !(command=malloc(used+1))) {
    fprintf(stderr,"Can't get memory!\n");
  }
  
  for( x = 0; x < used; ++x) {
    command[x] = inbuffer[strind + x];
  }
  command[used] = 0;

  z = strtol(command,0,10);

  free(command);

  return z;
}
