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

  tokencount = 0;
  linecount = 0;
  symbolcount = 0;

  init_machine();

  if( !(tokens = process_input(argv[source]) )) {
    return 1;
  }

  retcode = pass1(tokens, filelines);
  if( retcode == FALSE ) {
    retcode = pass2(tokens, filelines);
  }

  /*
   * Free all the structures created by process_input
   */
  delete_sym_tree();
  delete_line_tree();
  delete_token_tree();

  /* Used for finding memory leaks.
  printf("tokens: %i\nlines: %i\nsymbols: %i\n",
	 tokencount,linecount,symbolcount);
  */
  if( !retcode ) {
    if( dest ) {
      process_output(argv[dest]);
    } else {
      process_output("syn-asm.bin");
    }
  }

  return retcode;
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

TOKEN *process_input(const char *filename) {
  FILE *fp;
  int lineno = 0, strind = 0, len = 0;
  char inbuffer[BUFFSIZE];
  LINE *curr_line = filelines, *line_tmp = NULL;
  TOKEN *head_token = NULL, *curr_token = NULL, *tmp_token = NULL;

  if( !(fp = fopen(filename,"r"))) {
    fprintf(stderr,"Couldn't open file: %s\n",filename);
    return NULL;
  }

  if( !(line_tmp = malloc( sizeof(LINE) ))) {
    fprintf(stderr, "Failed to get memory for line buffer\n");
    return NULL;
  }
  linecount++;
  line_tmp->next = NULL;
  line_tmp->str = NULL;

  if( !(curr_line) ) {
    filelines = line_tmp;
  } else {
    while( curr_line->next ) {
      curr_line = curr_line->next;
    }
    curr_line->next = line_tmp;
  }
  curr_line = line_tmp;

  while( fgets(inbuffer,BUFFSIZE,fp) ) {
    strind = 0;
    lineno += 1;
    len = strlen(inbuffer);
    if( !(curr_line->str = malloc(sizeof(char)* len + 1)) ) {
      fprintf(stderr, "Failed to get memory for line buffer\n");
      return NULL;
    }
    strncpy(curr_line->str, inbuffer, strlen(inbuffer));
    while ( strind <= len ) {
      if( !(tmp_token = token(inbuffer, strind)) ) {
	/* We didn't get a token and are done with this line */
	break;
      }
      if( tmp_token == (TOKEN *)FAIL ) {
	/* Error on this line */
	fprintf(stderr, "Line #%i: %s", lineno, curr_line->str);
	break;
      }
      if( head_token == (TOKEN *)NULL ) {
	head_token = tmp_token;
	curr_token = head_token;
      } else {
	curr_token->next = tmp_token;
	curr_token = curr_token->next;
      }
      curr_token->line = lineno;
      curr_token->file_name = filename;
      curr_token->source_line = curr_line->str;
      strind = curr_token->length;
    }
    if( !(curr_line->next = malloc( sizeof(LINE) ))) {
      fprintf(stderr, "Failed to get memory for line buffer\n");
      return NULL;
    }
    linecount++;
    curr_line = curr_line->next;
    curr_line->next = (LINE *)NULL;
    curr_line->str = NULL;
  }

  fclose(fp);
  return head_token;
}

void delete_sym_tree() {
  SYMBOL *curr, *next;
  curr = syms;
  while(curr) {
    next = curr->next;
    free(curr);
    symbolcount--;
    curr = next;
  }
  syms = (SYMBOL *)NULL;
}
/*
 * Will delete the tree of the file lines
 */
void delete_line_tree() {
  LINE *curr, *next;
  curr = filelines;
  while( curr ) {
    next = curr->next;
    if( curr->str ) {
      free( curr->str );
    }
    free( curr );
    linecount--;
    curr = next;
  }
  filelines = NULL;
}

/*
 * Will delete all the tokens
 */
void delete_token_tree() {
  TOKEN *curr, *next;
  curr = tokens;
  while( curr ) {
    if( curr->word ) {
      free(curr->word);
    }
    next = curr->next;
    free(curr);
    tokencount--;
    curr = next;
  }
  tokens = NULL;
}
  

int init_machine() {
  int x;

  /* Zero memory for use */
  for( x = 0; x < REGOFFSET; ++x) {
    memory[x] = 0;
  }

  syms = (SYMBOL *)NULL;
  tokens = (TOKEN *)NULL;
  filelines = (LINE *)NULL;
  pc = 0;

  return 0;
}

int help_menu(const char *progname) {
  fprintf(stderr,"Usage: %s {source} [-o destination]\n",progname);
  return 0;
}
