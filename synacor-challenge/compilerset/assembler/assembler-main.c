#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "assembler.h"

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

  if( dest ) {
    process_output(argv[dest]);
  } else {
    process_output("syn-asm.bin");
  }

  return 0;
}

int process_output(const char *filename) {
  FILE *fp;
  int x, y;

  for( x = REGOFFSET-1; x > 0; --x) {
    if( memory[x] ) {
      break;
    }
  }
  ++x;

  if( !(fp = fopen(filename,"w"))) {
    fprintf(stderr,"Couldn't open file: %s\n",filename);
    return 1;
  }

  y = fwrite(memory, sizeof(SWORD), x, fp);

  if( y != x ) {
    fprintf(stderr,"Wrote %i words\nExpected to write %i words\n",y,x);
  }

  fclose(fp);
  return 0;
}

int process_input(const char *filename) {
  FILE *fp;
  int lineno = 0, strind = 0, len = 0;
  char inbuffer[BUFFSIZE];
  LINE *start = NULL, *curr = NULL;
  TOKEN *tokens = NULL, *curr_token = NULL, *tmp = NULL;

  if( !(fp = fopen(filename,"r"))) {
    fprintf(stderr,"Couldn't open file: %s\n",filename);
    return 1;
  }

  if( !(start = malloc( sizeof(LINE) ))) {
    fprintf(stderr, "Failed to get memory for line buffer\n");
    return 1;
  }
  start->number = 0;
  start->next = NULL;
  start->str = NULL;
  curr = start;

  while( fgets(inbuffer,BUFFSIZE,fp) ) {
    strind = 0;
    lineno += 1;
    len = strlen(inbuffer);
    if( !(curr->str = malloc(sizeof(char)* len + 1)) ) {
      fprintf(stderr, "Failed to get memory for line buffer\n");
      return 1;
    }
    strncpy(curr->str, inbuffer, strlen(inbuffer));
    curr->number = lineno;
    while ( strind <= len ) {
      if( !(tmp = token(inbuffer, strind)) ) {
	/* We didn't get a token and are done with this line */
	break;
      }
      if( tmp == (TOKEN *)FAIL ) {
	/* Error on this line */
	fprintf(stderr, "Line #%i: %s", lineno, curr->str);
	break;
      }
      if( tokens == (TOKEN *)NULL ) {
	tokens = tmp;
	curr_token = tokens;
      } else {
	curr_token->next = tmp;
	curr_token = curr_token->next;
      }
      curr_token->line = lineno;
      strind = curr_token->length;
    }
    if( !(curr->next = malloc( sizeof(LINE) ))) {
      fprintf(stderr, "Failed to get memory for line buffer\n");
      return 1;
    }
    curr = curr->next;
    curr->next = (LINE *)NULL;
    curr->str = NULL;
  }

  fclose(fp);

  pass1(tokens, start);
  pass2(tokens, start);

  delete_sym_tree();
  syms = NULL;
  delete_line_tree(start);
  start = NULL;
  curr = NULL;
  delete_token_tree(tokens);
  tokens = NULL;
  curr_token = NULL;
  return 0;
}

void delete_sym_tree() {
  SYMBOL *curr, *next;
  curr = syms;
  while(curr) {
    next = curr->next;
    free(curr);
    curr = next;
  }
  syms = (SYMBOL *)NULL;
}
/*
 * Will delete the tree of the file lines
 */
void delete_line_tree(LINE *s) {
  LINE *curr, *next;
  curr = s;
  while( curr ) {
    next = curr->next;
    if( curr->str ) {
      free( curr->str );
    }
    free( curr );
    curr = next;
  }
}

/*
 * Will delete all the tokens
 */
void delete_token_tree(TOKEN *t) {
  TOKEN *curr, *next;
  curr = t;
  while( curr ) {
    if( curr->word ) {
      free(curr->word);
    }
    next = curr->next;
    free(curr);
    curr = next;
  }
}
  

int init_machine() {
  int x;

  /* Zero memory for use */
  for( x = 0; x < REGOFFSET; ++x) {
    memory[x] = 0;
  }

  syms = (SYMBOL *)NULL;
  pc = 0;

  return 0;
}

int help_menu(const char *progname) {
  fprintf(stderr,"Usage: %s {source} [-o destination]\n",progname);
  return 0;
}
