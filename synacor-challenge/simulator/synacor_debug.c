#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "synacor.h"

/*
 * The debug commands
 */

int enter_debug_mode() {
  int x = 0, y = 0, i=0, index = 0;
  struct STACKOBJ *sptr;
  
  inbuffindex++;
  switch ( inbuffer[inbuffindex] ) {
    /* Return at the end of the string */
  case 0:
    return 0;
    break;

    /* Ignore whitespace and # */
  case ' ':
  case '\t':
  case '\n':
  case '#':
    inbuffindex++;
    break;

    /* This has to be load state */
  case 'l':
    while( inbuffer[inbuffindex] >= 'a' &&
	   inbuffer[inbuffindex] <= 'z') {
      inbuffindex++;
    }
    load_state();
    break;

  case 'j':
    while( (inbuffer[inbuffindex] >= 'a' &&
	    inbuffer[inbuffindex] <= 'z') ||
	   (inbuffer[inbuffindex] >= '0' &&
	    inbuffer[inbuffindex] <= '9') ) {
      inbuffindex++;
    }
    y = strtol(&inbuffer[inbuffindex],0,10);
    pc = y;
    break;

  case 'b':
    while( (inbuffer[inbuffindex] >= 'a' &&
	    inbuffer[inbuffindex] <= 'z') ||
	   (inbuffer[inbuffindex] >= '0' &&
	    inbuffer[inbuffindex] <= '9') ) {
      inbuffindex++;
    }
    y = strtol(&inbuffer[inbuffindex],0,10);
    breakpoint = y;
    break;
    
  case 'c':
    while( (inbuffer[inbuffindex] >= 'a' &&
	    inbuffer[inbuffindex] <= 'z') ||
	   (inbuffer[inbuffindex] >= '0' &&
	    inbuffer[inbuffindex] <= '9') ) {
      inbuffindex++;
    }
    y = strtol(&inbuffer[inbuffindex],0,10);
    if( !(sptr = malloc(sizeof(struct STACKOBJ)))) {
      fprintf(stderr,"Error saving pc\n");
    }
    sptr->next = stack;
    sptr->value = pc;
    stack = sptr;
    pc = y;
    break;

    /* This has to be print */
  case 'p':
    while( inbuffer[inbuffindex] >= 'a' &&
	   inbuffer[inbuffindex] <= 'z') {
      inbuffindex++;
    }
    while( inbuffer[inbuffindex] == ' ' ) {
      inbuffindex++;
    }
    if( inbuffer[inbuffindex] == 'p' ) {
      /* print pc */
      printf("PC: %i\n", pc);
      break;
    }
    if( inbuffer[inbuffindex] == 'r' ) {
      for( x = 0; x < 8; ++x ) {
	printf("r%i: %i\n", x, reg[x]);
      }
      break;
    }
    if( inbuffer[inbuffindex] == 's' ) {
      printstack();
      break;
    }
    x = strtol(&inbuffer[inbuffindex],0,10);
    while( (inbuffer[inbuffindex] >= 'a' &&
	    inbuffer[inbuffindex] <= 'z') ||
	   (inbuffer[inbuffindex] >= '0' &&
	    inbuffer[inbuffindex] <= '9') ) {
      inbuffindex++;
    }
    y = strtol(&inbuffer[inbuffindex],0,10);
    if( !y ) {
      y = x;
    }
    if( (x < 0 || x > 32767) || (y < 0 || y > 32767 )) {
      fprintf(stderr,"Invalid memory location\n");
    }
    fprintf(stderr,"MEMORY: %i to %i\n",x,y);
    for( i = x; i <= y; ++i ) {
      fprintf(stderr,"%05i\t",memory[i]);
    }
    fprintf(stderr,"\n");
    break;

  case 's':
    if( inbuffer[inbuffindex+1] == 'a' ) {
      save_state();
      break;
    }
    if( inbuffer[inbuffindex+1] == 't' ) {
      if( stepmode ) {
	stepmode = 0;
      } else {
	stepmode = 1;
      }
      break;
    }
    if( inbuffer[inbuffindex+1] == 'e' ) {
      while(inbuffer[inbuffindex] >= 'a' &&
	    inbuffer[inbuffindex] <= 'z') {
	inbuffindex++;
      }
      while(inbuffer[inbuffindex] == ' ') {
	inbuffindex++;
      }
      if(inbuffer[inbuffindex] == 'r') {
	inbuffindex++;
	index = inbuffer[inbuffindex] - '0';
	inbuffindex++;
	x = strtol(&inbuffer[inbuffindex],0,10);
	reg[index] = x;
      }
      if( inbuffer[inbuffindex] >= '0' && inbuffer[inbuffindex] <= '9' ) {
	x = strtol(&inbuffer[inbuffindex],0,10);
	while( (inbuffer[inbuffindex] >= '0' &&
		inbuffer[inbuffindex] <= '9') ) {
	  inbuffindex++;
	}
	y = strtol(&inbuffer[inbuffindex],0,10);
	fprintf(stderr,"Setting [%05i] to %05i\n",x,y);
	memory[x] = y;
      }
      break;
    }
  }
  while( inbuffer[inbuffindex] != 0 ) {
    inbuffindex++;
  }
  return 0;
}

int printstack() {
  struct STACKOBJ *sptr = 0;

  sptr = stack;

  while(sptr) {
    printf("%i\n",sptr->value);
    sptr = sptr->next;
  }
  return 0;
}

int save_state() {
  FILE *source;
  int words_written = 0, x = 0, y = 0;
  struct STACKOBJ *sptr;
  unsigned short int *temp;
  
  if( !( source = fopen("synacor.dump", "w"))) {
    fprintf(stderr,"Could not open file for writing.\n");
    return 0;
  }

  words_written= fwrite(memory,
			sizeof(unsigned short int),
			REGOFFSET,
			source);
  fprintf(stderr,"CORE MEM: %i words\n",words_written);
  words_written= fwrite(reg,
			sizeof(unsigned short int),
			8,
			source);
  fprintf(stderr,"REGISTERS: %i words\n",words_written);
  words_written= fwrite(&pc,
			sizeof(unsigned short int),
			1,
			source);
  fprintf(stderr,"PROGRAM COUNTER: %i words\n",words_written);

  sptr = stack;
  while( sptr ) {
    ++x;
    sptr = sptr->next;
  }

  words_written= fwrite(&x,
			sizeof(unsigned short int),
			1,
			source);
  fprintf(stderr,"STACK SIZE: %i words\n",words_written);
  if( x ) {
    if( !(temp = malloc( x*sizeof(unsigned short int)) ) ) {
      fprintf(stderr,"Couldn't save stack.\n");
    }
    sptr = stack;
    for( y = 1; y <= x; ++y ) {
      temp[x-y] = sptr->value;
      sptr = sptr->next;
    }
    words_written= fwrite(temp,
			  sizeof(unsigned short int),
			  x,
			  source);
    fprintf(stderr,"STACK CONTENTS: %i words\n",words_written);
  }
  if( source ) {
    fclose(source);
  }
  return words_written;
}

int load_state() {
  FILE *source;
  int words_read = 0, x = 0, y = 0;
  struct STACKOBJ *sptr;

  /* Free the stack, if there is one */
  while(stack) {
    sptr = stack->next;
    free(stack);
    stack = sptr;
  }

  stack = 0;
  
  if( !( source = fopen("synacor.dump", "r"))) {
    fprintf(stderr,"Could not open file for reading.\n");
    return 0;
  }

  words_read = fread(memory,
		     sizeof(unsigned short int),
		     REGOFFSET,
		     source);
  fprintf(stderr,"CORE MEM: %i words\n",words_read);
  words_read = fread(reg,
		     sizeof(unsigned short int),
		     8,
		     source);
  fprintf(stderr,"REGISTERS: %i words\n",words_read);
  words_read = fread(&pc,
		     sizeof(unsigned short int),
		     1,
		     source);
  fprintf(stderr,"PROGRAM COUNTER: %i words\n",words_read);

  words_read = fread(&x,
		     sizeof(unsigned short int),
		     1,
		     source);
  fprintf(stderr,"STACK SIZE: %i words\n",words_read);
  while( x ) {
    if( !(sptr = malloc( sizeof(struct STACKOBJ) ) ) ) {
      fprintf(stderr,"Couldn't get memory for stack.\n");
      break;
    }
    sptr->next = stack;
    stack = sptr;
    
    words_read= fread(&y,
		      sizeof(unsigned short int),
		      1,
		      source);
    stack->value = y;
    --x;
  }
  x = 0;
  sptr = stack;
  while( sptr ) {
    ++x;
    sptr = sptr->next;
  }
  fprintf(stderr,"STACK CONTENTS: %i words\n",words_read);
  if( source ) {
    fclose(source);
  }
  return words_read;
}
