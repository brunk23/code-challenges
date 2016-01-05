#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "synacor_a.h"

int main(int argc, char *argv[]) {
  int retcode = 0, source = 0, dest = 0;
  
  /* COMMAND LINE ARGUMENTS */
  for( retcode = 1; retcode < argc; retcode++) {
    if( strcmp(argv[retcode],"-o" ) == 0 ) {
      dest = retcode + 1;
      retcode++;
    } else {
      if( !source ) {
        source = retcode;
      } else {
        source = 0;
        break;
      }
    }
  }

  /* Make sure the command line arguments are correct */
  if( !source || dest >= argc || (dest == 0 && argc > 2) ) {
    help_menu(argv[0]);
    return 1;
  }

  init_machine();

  if( process_input(argv[source]) ) {
    return 1;
  }
  
  return 0;
}

int process_input(const char *filename) {
  FILE *fp;
  char *str;
  int tokenlen;
  
  if( !(fp = fopen(filename,"r"))) {
    fprintf(stderr,"Couldn't open file: %s\n",filename);
    return 1;
  }

  while( (str = fgets(inbuffer,BUFFSIZE,fp) ) ) {
    strind = 0;
    while ( (tokenlen = findtoken(inbuffer)) ) {
      if( inbuffer[strind] == '#' ) {
	/* Start a comment */
	break;
      }
      if( inbuffer[strind] == '.' ) {
	strind += internal_command(tokenlen);
      } else {
	if( inbuffer[strind] == ':' ) {
	  strind += variable_name(tokenlen);
	} else {
	  if( inbuffer[strind] >= 'a' &&
	      inbuffer[strind] <= 'z' ) {
	    strind += opcode(tokenlen);
	  } else {
	    fprintf(stderr,"Unexpected junk in input at %i\n",strind);
	    fprintf(stderr,"%s",inbuffer);
	    strind += tokenlen;
	  }
	}
      }
    }
  }
  return 0;
}

/*
 * Meh, I am unsure how I want to implement this
 * if I want the stack objects to keep track of their
 * locations, or if I want to track locations elsewhere
 * probably the second... have another stack with variable
 * names and the location they should be assigned to when
 * located in memory
 */
int variable_name(int len) {
  int x = 0, ndecl = 0;
  struct symstack *sptr = 0;
  char *vname;
  if(inbuffer[strind] == ':') {
    strind++;
    len--;
    ndecl = 1;
  }
  if(!(vname=malloc(len+1))) {
    fprintf(stderr,"Can't allocate memory\n");
    return len;
  }
  for(x = 0; x < len; ++x ) {
    vname[x] = inbuffer[strind+x];
  }
  vname[len] = 0;
  strind += len;

  /* Check to see if it's in the tree */
  sptr = stack;
  while(sptr) {
    if( strcmp(sptr->name, vname) == 0 ) {
      /* in the tree */
      break;
    }
  }

  if( !sptr ) {
    /* not in the tree */
    sptr = malloc(sizeof(struct symstack));
    sptr->next = stack;
    stack = sptr;
    sptr->name = vname;
    sptr->location = 0;
    sptr->known = 0;
  }

  if( ndecl == 1 && stack->known == 1 ) {
    fprintf(stderr,"Double declaration of label\n");
    return len;
  }

  if( ndecl == 1 ) {
    stack->location = pc;
    stack->known = 1;
  }

  /* INC */
  
  return 0;
}

/*
 * index = start of token, returns token length
 */
int findtoken(const char *buff) {
  int n=0;
  int found = 1;

  while( found ) {
    switch( inbuffer[strind] ) {
    case ' ':
    case '\t':
    case ',':
      strind++;
      break;

    case 0:
    case '\n':
      return 0;
      break;

    default:
      found = 0;
      break;
    }
  }
  
  found = 1;
  while ( found ) {
    ++n;
    switch (inbuffer[strind+n]) {
    case ' ':
    case '\t':
    case ',':
    case '#':
    case '\n':
    case 0:
      found = 0;
      break;

    default:
      break;
    }
  }
  return n;
}
  

int init_machine() {
  int x;

  /* Zero memory for use */
  for( x = 0; x < REGOFFSET; ++x) {
    memory[x] = 0;
  }

  stack = 0;
  pc = 0;
  
  return 0;
}

int help_menu(const char *progname) {
  fprintf(stderr,"Usage: %s {source} [-o destination]\n",progname);
  return 0;
}
