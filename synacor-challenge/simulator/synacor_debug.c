#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "synacor.h"
#include "synacor_stack.h"

/*
 * The debug commands
 */

void process_debug_str(char *s) {
  int i = 0;
  SWORD command_word = INVALID;

  command_word = next_word(s, &i);

  switch( command_word ) {
  case PRINT:
    debug_print( s, &i );
    break;
  case LOAD:
    load_state();
    break;
  case SAVE:
    save_state();
    break;
  case JUMP:
    debug_jump( s, &i );
    break;
  case SET:
    debug_set( s, &i );
    break;
  case BREAK:
    debug_break(s, &i );
    break;
  case QUIT:
    exit(1);
    break;
  case STEP:
    if( stepmode == 0 ) {
      stepmode = 1;
    } else {
      stepmode = 0;
    }
    break;
  default:
    fprintf(stderr,"Invalid debug command %s\n",s);
    break;
  }
}

void debug_break(char *s, int *i) {
  SWORD arg1 = INVALID;
  arg1 = next_word(s, i);
  if( arg1 < r0 ) {
    breakpoint = arg1;
  }
}

void debug_jump(char *s, int *i) {
  SWORD arg1 = INVALID;
  arg1 = next_word(s, i);
  if( arg1 < r0 ) {
    pc = arg1;
  }
}

void debug_set(char *s, int *i) {
  SWORD arg1 = INVALID, arg2 = INVALID;
  arg1 = next_word(s, i);
  arg2 = next_word(s, i);

  if( arg1 >= INVALID || arg2 >= INVALID ) {
    fprintf(stderr,"Unable to set bad address\n");
    return;
  }
  fprintf(stderr,"Set address [%i] <- %i\n",arg1, arg2);
  if( arg1 >= r0 ) {
    arg1 -= r0;
    reg[arg1] = arg2;
  } else {
    memory[arg1] = arg2;
  }
}

void debug_print(char *s, int *i) {
  SWORD arg1 = INVALID, arg2 = INVALID;
  int x = 0;

  arg1 = next_word(s, i);
  switch( arg1 ) {
  case r0:
  case r1:
  case r2:
  case r3:
  case r4:
  case r5:
  case r6:
  case r7:
    if( arg1 >= r0 && arg1 <= r7 ) {
      for( x = 0; x < 8; ++x ) {
	fprintf(stderr,"r%i: %i\n", x, reg[x]);
      }
    }
    break;
  case PC:
    printf("PC: %i\n", pc);
    break;
  case STACK:
    printstack();
    break;
  default:
    arg2 = next_word(s, i);
    if( arg2 == INVALID ) {
      arg2 = arg1;
    }
    print_mem_range(arg1, arg2);
    break;
  }
}

void print_mem_range(SWORD x, SWORD y) {
  int i = 0;
  fprintf(stderr,"MEMORY: %i to %i\n",x,y);
  for( i = x; i <= y; ++i ) {
    fprintf(stderr,"%05i\t",memory[i]);
  }
  fprintf(stderr,"\n");
}

SWORD next_word(char *s, int *i) {
  SWORD value = INVALID;
  int start = 0, end = 0;
  char oldchar = 0;

  while( isspace(s[*i]) ) {
    (*i)++;
  }
  start = *i;
  while( isalnum(s[*i]) ) {
    (*i)++;
  }
  end = *i;
  oldchar = s[end];
  s[end] = 0;

  value = isdebugcommand( &s[start] );
  if( value == INVALID ) {
    value = strtol( &s[start], 0, 10 );
  }
  s[end] = oldchar;
  return value;
}

SWORD isdebugcommand( char *s ) {
  if( !(strcmp( s, "set" )) ) {
    return SET;
  }
  if( !(strcmp( s, "jump" )) || !(strcmp( s, "j")) ) {
    return JUMP;
  }
  if( !(strcmp( s, "break" )) || !(strcmp( s, "b")) ) {
    return BREAK;
  }
  if( !(strcmp( s, "clear" )) || !(strcmp( s, "c")) ) {
    return CLEAR;
  }
  if( !(strcmp( s, "print" )) || !(strcmp( s, "p")) ) {
    return PRINT;
  }
  if( !(strcmp( s, "save" )) || !(strcmp( s, "sa")) ) {
    return SAVE;
  }
  if( !(strcmp( s, "load" )) || !(strcmp( s, "l")) ) {
    return LOAD;
  }
  if( !(strcmp( s, "step" )) || !(strcmp( s, "st")) ) {
    return STEP;
  }
  if( !(strcmp( s, "quit")) || !(strcmp( s, "q")) ) {
    return QUIT;
  }
  if( !(strcmp( s, "stack")) || !(strcmp( s, "s")) ) {
    return STACK;
  }
  if( !(strcmp( s, "r0" )) ) {
    return r0;
  }
  if( !(strcmp( s, "r1" )) ) {
    return r1;
  }
  if( !(strcmp( s, "r2" )) ) {
    return r2;
  }
  if( !(strcmp( s, "r3" )) ) {
    return r3;
  }
  if( !(strcmp( s, "r4" )) ) {
    return r4;
  }
  if( !(strcmp( s, "r5" )) ) {
    return r5;
  }
  if( !(strcmp( s, "r6" )) ) {
    return r6;
  }
  if( !(strcmp( s, "r7" )) ) {
    return r7;
  }
  if( !(strcmp( s, "pc" )) ) {
    return PC;
  }
  return INVALID;
}


/*** Remove the ability to call
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
*/

int printstack() {
  struct STACKOBJ *sptr = 0;
  int i = 0;

  sptr = stack;

  while(sptr) {
    for( i = sptr->stack_size; i > 0; i-- ) {
      printf("%i\n", sptr->values[ i - 1 ] );
    }
    sptr = sptr->next;
  }
  return 0;
}

int save_state() {
  FILE *source;
  int words_written = 0, x = 0, y = 0;
  struct STACKOBJ *sptr;
  SWORD *temp;
  
  if( !( source = fopen("synacor.dump", "w"))) {
    fprintf(stderr,"Could not open file for writing.\n");
    return 0;
  }

  words_written= fwrite(memory,
			sizeof(SWORD),
			REGOFFSET,
			source);
  fprintf(stderr,"CORE MEM: %i words\n",words_written);
  words_written= fwrite(reg,
			sizeof(SWORD),
			8,
			source);
  fprintf(stderr,"REGISTERS: %i words\n",words_written);
  words_written= fwrite(&pc,
			sizeof(SWORD),
			1,
			source);
  fprintf(stderr,"PROGRAM COUNTER: %i words\n",words_written);

  sptr = stack;
  while( sptr ) {
    ++x;
    sptr = sptr->next;
  }

  words_written= fwrite(&x,
			sizeof(SWORD),
			1,
			source);
  fprintf(stderr,"STACK SIZE: %i words\n",words_written);
  if( x ) {
    if( !(temp = malloc( x*STACKMAX*sizeof(SWORD)) ) ) {
      fprintf(stderr,"Couldn't save stack.\n");
    }
    sptr = stack;
    for( y = 1; y <= x; ++y ) {
      temp[x-y] = sptr->values[y];  // XXX BROKEN
      sptr = sptr->next;
    }
    words_written= fwrite(temp,
			  sizeof(SWORD),
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

  stack = NULL;
  
  if( !( source = fopen("synacor.dump", "r"))) {
    fprintf(stderr,"Could not open file for reading.\n");
    return 0;
  }

  words_read = fread(memory,
		     sizeof(SWORD),
		     REGOFFSET,
		     source);
  fprintf(stderr,"CORE MEM: %i words\n",words_read);
  words_read = fread(reg,
		     sizeof(SWORD),
		     8,
		     source);
  fprintf(stderr,"REGISTERS: %i words\n",words_read);
  words_read = fread(&pc,
		     sizeof(SWORD),
		     1,
		     source);
  fprintf(stderr,"PROGRAM COUNTER: %i words\n",words_read);

  words_read = fread(&x,
		     sizeof(SWORD),
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
		      sizeof(SWORD),
		      1,
		      source);
    stack->values[0] = y;  // BROKEN
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
