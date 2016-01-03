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
    if( !(command=malloc(used+1))) {
      fprintf(stderr,"Can't get memory!\n");
      return len;
    }
    for( x = 0; x < used; ++x) {
      command[x] = inbuffer[strind + x];
    }
    command[used] = 0;
    z = strtol(command,0,10);
    free(command);
    command = 0;
    fprintf(stderr,"Setting origin to %i\n",z);
    pc = z;
    return used;
  }

  if( command ) {
    free(command);
  }
  return used;
}
