#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "synacor_a.h"

/*
 * Process .directive lines, consumes all the
 * data from the line
 */
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
    return 0;
  }

  if( command ) {
    free(command);
  }
  return 0;
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

  strind += used;
  
  free(command);

  return z;
}

int process_data_line() {
  int len, y;

  while( (len = findtoken(inbuffer))) {
    if( inbuffer[strind] == '#' ) {
      break;
    }
    if( inbuffer[strind] >= '0' && inbuffer[strind] <= '9' ) {
      y = read_number(len);
      memory[pc++] = y;
      continue;
    }
    y = pc;
    variable_name(len);
    if( y == pc ) {
      ++pc;
    }
  }
  return 0;
}


/*
 * This will fill 'words' with the content on the line
 * leaves index after the last byte of the last word info.
 */
int fill( int words ) {
  int len, x, y;

  for( x = 0; x < words; ++x ) {
    len = findtoken(inbuffer);
    if(inbuffer[strind] >= '0' && inbuffer[strind] <= '9') {
      y = read_number(len);
      memory[pc++] = y;
      continue;
    }
    if( len == 2 && inbuffer[strind] == 'r' &&
	inbuffer[strind+1] >= '0' &&
	inbuffer[strind+1] <= '7' ) {
      switch (inbuffer[strind+1]) {
      case '0':
	memory[pc++] = r0;
	break;

      case '1':
	memory[pc++] = r1;
	break;
	
      case '2':
	memory[pc++] = r2;
	break;
	
      case '3':
	memory[pc++] = r3;
	break;
	
      case '4':
	memory[pc++] = r4;
	break;
	
      case '5':
	memory[pc++] = r5;
	break;
	
      case '6':
	memory[pc++] = r6;
	break;
	
      case '7':
	memory[pc++] = r7;
	break;
	
      default:
	break;
      }
      strind += len;
      /* End the register process */
      continue;
    }
    y = pc;
    variable_name(len);
    if( y == pc ) {
      ++pc;
    }
  }
  return 0;
}

