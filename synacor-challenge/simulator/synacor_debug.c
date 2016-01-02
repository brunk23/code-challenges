#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "synacor.h"

/*
 * The debug commands
 */

int enter_debug_mode() {
  char *test = 0;
  int x = 0, index = 0;
  
  printf("ENTER DEBUG MODE: %s%i: ",inbuffer, pc);
  while( (test = fgets(inbuffer, BUFFSIZE, stdin)) ) {
    if( !(test = strtok(inbuffer," \n"))) {
      continue;
    }

    if( strcmp(test,"savestate") == 0) {
      save_state();
      continue;
    }

    if( strcmp(test,"loadstate") == 0) {
      load_state();
      continue;
    }

    if( strcmp(test,"debugmode") == 0) {
      if( debugmode ) {
	debugmode = 0;
      } else {
	debugmode = 1;
      }
    }
    
    /* START PRINT */
    if( strcmp(test,"print") == 0) {
      if( (test = strtok(0," \n") )) {
	  
	if( strcmp(test,"reg") == 0) {
	  for( x = 0; x < 8; ++x ) {
	    printf("r%i: %i\n", x, reg[x]);
	  }
	}

	if( strcmp(test,"pc") == 0) {
	  printf("r%i: %i\n", x, pc);
	}

	if( strcmp(test,"stack") == 0) {
	  printstack();
	}
	
	continue;
      } else {
	continue;
      }
    } /* END PRINT */

    /* START SET */
    if (strcmp(test,"set") == 0) {
      if( (test = strtok(0," \n"))) {
	if( test[0] == 'r' ) {
	  index = test[1] - '0';
	  if( (test = strtok(0," \n"))) {
	    x = strtol(test,0,10);
	    reg[index] = x;
	  }
	}
	continue;
      } else {
        continue;
      }
    
    } /* END SET */
    
    if( inbuffer[0] == '#' ) {
      printf("LEAVE DEBUG MODE (%i)\n",debugmode);
      break;
    } else {
      printf("%i: ",pc);
    }
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
    fprintf(stderr,"STACK CONTENTS: %i words\n",words_read);
    stack->value = y;
    --x;
  }
  if( source ) {
    fclose(source);
  }
  return words_read;
}
