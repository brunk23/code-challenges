#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "synacor.h"
#include "synacor_stack.h"

/*
 * The debug commands
 */

const char *debug_commands[] = {
  "set", "jump", "j", "break", "b", "clear", "c", "print", "p",
  "save", "sa", "load", "l", "step", "st", "quit", "q", "stack",
  "s", "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "pc",
  "call", 0
};

const SWORD debug_command_values[] = {
  SET, JUMP, JUMP, BREAK, BREAK, CLEAR, CLEAR, PRINT, PRINT,
  SAVE, SAVE, LOAD, LOAD, STEP, STEP, QUIT, QUIT, STACK,
  STACK, r0, r1, r2, r3, r4, r5, r6, r7, PC,
  CALL
};

SWORD isdebugcommand( char *s ) {
  int i = 0;

  while( debug_commands[i] ) {
    if( !(strcmp( s, debug_commands[i])) ) {
      return debug_command_values[i];
    }
    i++;
  }
  return INVALID;
}

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
  case STACK:
    print_stack();
    break;
  case BREAK:
    debug_break( s, &i );
    break;
  case CALL:
    debug_call( s, &i );
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
    print_stack();
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

void debug_call(char *s, int *i) {
  push_word( pc );
  pc = next_word(s, i);
}

/*
 * Will print a range of memory in columns of 10 words each
 */
void print_mem_range(SWORD x, SWORD y) {
  int i = 0, j = 1;
  if( x > y ) {
    i = y;
    y = x;
    x = i;
    i = 0;
  }
  fprintf(stderr,"MEMORY: %i to %i\n",x,y);
  for( i = x; i <= y; ++i, ++j ) {
    fprintf(stderr,"%05i\t",memory[i]);
    if( !( j % 10 ) ) {
      fprintf(stderr,"\n");
    }
  }
  fprintf(stderr,"\n");
}

/*
 * This should probably be reworked. It's messy and ugly.
 */
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

int print_stack() {
  const SWORD *stack = stack_buffer();
  int i = 0;

  while(i < stack_size()) {
    printf("%i: %i\n", i, stack[i] );
    i++;
  }
  return 0;
}

int save_state() {
  FILE *source;
  int words_written = 0, x = 0;
  
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

  x = stack_size();
  words_written= fwrite(&x,
			sizeof(SWORD),
			1,
			source);
  fprintf(stderr,"STACK SIZE: %i words\n",words_written);
  words_written= fwrite(stack_buffer(),
			sizeof(SWORD),
			x,
			source);
  fprintf(stderr,"STACK CONTENTS: %i words\n",words_written);

  if( source ) {
    fclose(source);
  }
  return words_written;
}

int load_state() {
  FILE *source;
  int words_read = 0, x = 0, y = 0;

  /* Free the stack, if there is one */
  init_stack();

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
    
    words_read = fread(&y,
		       sizeof(SWORD),
		       1,
		       source);
    push_word( y );
    --x;
  }

  fprintf(stderr,"STACK CONTENTS: %i words\n",words_read);
  if( source ) {
    fclose(source);
  }
  return words_read;
}
