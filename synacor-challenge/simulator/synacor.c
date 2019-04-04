#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>

#include "synacor.h"
#include "synacor_stack.h"

/*
 * Synacor Emulator
 */

int main(int argc, char *argv[]) {
  struct STACKOBJ *obottom;
  char *test;
  int retval = 0;
  int source = 0;
  int bufflen = 0;

  signal(SIGINT, catch_int);

  fprintf(stderr,"Initializing Machine...\n");
  init_machine();

  for( retval = 1; retval < argc; ++retval ) {
    if( strcmp(argv[retval],"-s") == 0 ) {
      stepmode = 1;
    } else {
      if( source == MAXDEV ) {
	fprintf(stderr,"Too many devices!\n");
	return 0;
      }
      if( !( devices[source] = fopen(argv[retval], "r+"))) {
	fprintf(stderr,"Could not open file for reading/writing.\n");
	return 0;
      }
      ++source;
    }
  }

  if( argc < 2 || devices[0] == 0 ) {
    fprintf(stderr,"Usage: %s {challenge.bin}\n",argv[0]);
    return 1;
  }

  read_in_file( devices[0], 0, 0, REGOFFSET );

  while( 1 ) {

    /* Make sure pc loops down correctly */
    pc &= MAXMEM;

    if( memory[pc] > 23 ) {
      fprintf(stderr,"Error: Invalid operation %i",pc);
      break;
    }

    /* I want to bring the string operation in here */

    if( pc == breakpoint ) {
      stepmode = 1;
    }

    /*
     * This is where we need to change the code.
     */
    if((memory[pc] == in && inbuffindex >= bufflen)) {
      test = fgets(inbuffer, BUFFSIZE, stdin);
      if( !test || feof(stdin) || ferror(stdin) ) {
	fprintf(stderr,"Input error!");
	return 1;
      }
      inbuffindex = 0;
      if( !(bufflen = scan_inbuff()) ) {
	continue;
      }
    }
    if(stepmode) {
      print_instruction( pc );
      fprintf(stderr,"  SYNDB> ");
      test = fgets(debugbuffer, BUFFSIZE, stdin);
      if( !test || feof(stdin) || ferror(stdin) ) {
	fprintf(stderr,"Input error!");
	return 1;
      }
      process_debug_str(debugbuffer);
    }

    /* Only halt or errors return 1 */
    if( ( retval=inst_tble[ get_add(pc) ]() ) ) {
      break;
    }
  }

  /* Unwind the stack and free it */
  while(stack) {
    obottom = stack;
    stack = stack->next;
    free(obottom);
  }

  /*
   * Close open files
   */
  for(retval = 0; retval < MAXDEV; ++retval) {
    if( devices[retval] ) {
      fclose( devices[retval] );
    }
  }
  
  return 0;
}

void catch_int(int none) {
  stepmode = 1;
}

/*
 * This will clear the inbuff of debug strings
 */
int scan_inbuff() {
  int count = 0, i = 0;
  while( isspace(inbuffer[i])) {
    i++;
  }
  while ( inbuffer[i] != 0 ) {
    if( inbuffer[i] == '#' ) {
      inbuffer[i] = 0;
      process_debug_str(&inbuffer[i+1]);
    } else {
      i++;
      count++;
    }
  }
  return count;
}

int init_machine() {
  int x;
  inst_tble[halt] = op_halt;
  inst_tble[set] = op_set;
  inst_tble[push] = op_push;
  inst_tble[pop] = op_pop;
  inst_tble[eq] = op_eq;
  inst_tble[gt] = op_gt;
  inst_tble[jmp] = op_jmp;
  inst_tble[jt] = op_jt;
  inst_tble[jf] = op_jf;
  inst_tble[add] = op_add;
  inst_tble[mult] = op_mult;
  inst_tble[mod] = op_mod;
  inst_tble[and] = op_and;
  inst_tble[or] = op_or;
  inst_tble[not] = op_not;
  inst_tble[rmem] = op_rmem;
  inst_tble[wmem] = op_wmem;
  inst_tble[call] = op_call;
  inst_tble[ret] = op_ret;
  inst_tble[out] = op_out;
  inst_tble[in] = op_in;
  inst_tble[nop] = op_nop;
  inst_tble[dread] = op_dread;
  inst_tble[dwrite] = op_dwrite;
  stack = NULL;

  pc = 0;

  stepmode = 0;

  breakpoint = REGOFFSET;
  
  /* Reset Input Buffer */
  for( x = 0; x < BUFFSIZE; ++x ) {
    inbuffer[x] = 0;
    debugbuffer[x] = 0;
  }
  inbuffindex = 0;

  /* Reset Memory */
  for( x = 0; x < REGOFFSET; ++x ) {
    memory[x] = 0;
  }

  /* Reset Registers */
  for( x = 0; x < REGISTERS; ++x ) {
    reg[x] = 0;
  } 

  for( x = 0; x < MAXDEV; ++x ) {
    devices[x] = 0;
  }

  return 0;
}

int read_in_file(FILE *source,
		 SWORD dest,
		 long start,
		 size_t words) {
  int words_read = 0;
  int diff = 0;

  if( fseek(source, start*sizeof(SWORD), SEEK_SET) ){
    fprintf(stderr,"Unable to access location on device\n");
    return 0;
  }

  if( dest + words > REGOFFSET ) {
    /* we need to wrap memory */
    diff = (words + dest - REGOFFSET);
    words_read = fread(&memory[dest],
		       sizeof(SWORD),
		       words - diff,
		       source);
    words_read += fread(memory,
			sizeof(SWORD),
			diff,
			source);
  } else {
    words_read = fread(&memory[dest],
		       sizeof(SWORD),
		       words,
		       source);
  }

  /*  We don't need to worry about the order as
   * little endian is read in correctly.
   * for( x = 0; x < 8; ++x ) {
   * y = memory[x] << 8;
   * y += memory[x] / 0x100;
   * }
   */

  return words_read;
}

/*
 * This should work
 * Untested
 */
int write_out_file(FILE *dest,
		 SWORD source,
		 long start,
		 size_t words) {
  int words_wrote = 0;
  int diff = 0;

  if( fseek(dest, start*sizeof(SWORD), SEEK_SET) ){
    fprintf(stderr,"Unable to access location on device\n");
    return 0;
  }

  /*
   * This doesn't work at all right now (the overflow)
   * Perhaps I shouldn't worry about going about 2^30 words
   * and instead should focus on the wrapping around memory,
   * which is the original intent.
   *
   * Technically, we can read/write above the addressable
   * limit with these functions
   */
  if( source+words > REGOFFSET ) {
    /* we need to wrap memory */
    diff = (words + source - REGOFFSET);
    words_wrote = fwrite(&memory[source],
		       sizeof(SWORD),
		       words - diff,
		       dest);
    words_wrote += fwrite(memory,
			  sizeof(SWORD),
			diff,
			dest);
  } else {
    words_wrote = fwrite(&memory[source],
		       sizeof(SWORD),
		       words,
		       dest);
  }

  /*  We don't need to worry about the order as
   * little endian is read in correctly.
   * for( x = 0; x < 8; ++x ) {
   * y = memory[x] << 8;
   * y += memory[x] / 0x100;
   * }
   */

  return words_wrote;
}

/*
 * Helper function for memory access to return
 * register values when those are requested.
 */
SWORD get_add(SWORD a) {
  SWORD b;

  /* a should be within memory, but if pc was near the top of
   * memory and we pass ( pc + 5 ) or similar, we could read
   * outside the array, protect against that by wrapping down */
  a &= MAXMEM;
  b = memory[a];

  if( b < REGOFFSET ) {
    return b;
  } else {
    b -= REGOFFSET;
  }
  if( b <= r7 ) {
    return reg[b];
  }
  fprintf(stderr,"Invalid access request: %i at %i\n",
	  b + REGOFFSET, pc);
  return 0;
}

/*
 * Helper function for memory setting. It also sets
 * registers correctly.
 */
SWORD set_add(SWORD a, SWORD b) {
  SWORD c;

  /* ensure both are inside memory */
  a &= MAXMEM;
  b &= MAXMEM;
  c = memory[a];

  if( c >= REGOFFSET ) {
    c -= REGOFFSET;
    if( c >= 8 ) {
      fprintf(stderr,"Invalid access request: %i at %i\n",
	      a + REGOFFSET, pc);
      return 0;
    }
    return reg[c] = b;
  }
  return memory[c] = b;
}
