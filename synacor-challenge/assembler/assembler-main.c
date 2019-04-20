#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "assembler.h"

/*
 * I want to change this to take the base name of the file and produce
 * {file}.bin [the binary], {file}.sym [the symbol table], {file}.lst [listing]
 */
int main(int argc, char *argv[]) {
  int compile_status = 0, source = 0, dest = 0, verbose = 0;
  char *src_file = NULL, *dest_file = NULL, *sym_file = NULL;

  /* COMMAND LINE ARGUMENTS */
  for( compile_status = 1; compile_status < argc; compile_status++) {
    if( strcmp(argv[compile_status],"-v" ) == 0 ) {
      verbose = 1;
      continue;
    }
    if( strcmp(argv[compile_status],"-o" ) == 0 ) {
      dest = compile_status + 1;
      compile_status++;
    } else {
      if( !source ) {
        source = compile_status;
      } else {
        source = 0;
        break;
      }
    }
  }

  /* Make sure the command line arguments are correct */
  if( !source || dest >= argc ) {
    help_menu(argv[0]);
    return 1;
  }

  if( dest == 0 ) {
    if( !(dest_file = malloc( strlen(argv[source]) + 5))) {
      fprintf(stderr, "Fatal Error creating filename.\n");
      return 1;
    }
    strncpy(dest_file, argv[source], strlen(argv[source])+1);
    strncat(dest_file, ".bin", 4);
  } else {
    if( !(dest_file = malloc( strlen(argv[dest]) + 1))) {
      fprintf(stderr, "Fatal Error creating filename.\n");
      return 1;
    }
    strncpy(dest_file, argv[dest], strlen(argv[dest]));
  }

  if( !(src_file = malloc( strlen(argv[source]) + 5))) {
    fprintf(stderr, "Fatal Error creating filename.\n");
    return 1;
  }
  strncpy(src_file, argv[source], strlen(argv[source])+1);
  strncat(src_file, ".s", 2);

  if( !(sym_file = malloc( strlen(argv[source]) + 5))) {
    fprintf(stderr, "Fatal Error creating filename.\n");
    return 1;
  }
  strncpy(sym_file, argv[source], strlen(argv[source])+1);
  strncat(sym_file, ".sym", 4);

  instruction_count = 0;
  data_words = 0;
  arguments_count = 0;
  tokencount = 0;
  linecount = 0;
  symbolcount = 0;

  init_machine();

  if( !(tokens = process_input( src_file ))) {
    return 1;
  }

  compile_status = pass1(tokens, filelines);
  if( compile_status == GOOD ) {
    compile_status = pass2(tokens, filelines);
  }

  print_sym_tree( sym_file );

  if( verbose ) {
    fprintf(stderr, "\tProgram Statistics\n\n");
    fprintf(stderr, "Lines of source code: %i\n", linecount);
    fprintf(stderr, "Tokens Generated: %i\n", tokencount);
    fprintf(stderr, "Symbols Found: %i\n\n", symbolcount);
    fprintf(stderr, "Instructions compiled: %i with %i arguments\n",
	    instruction_count, arguments_count);
    fprintf(stderr, "Data words: %i\n\n", data_words);
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
  if( compile_status == GOOD ) {
    process_output(dest_file, verbose);
  }

  free( dest_file );
  free( sym_file );
  free( src_file );
  return compile_status;
}

int process_output(const char *filename, int verbose) {
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
    fprintf(stderr, "Wrote %i words\nExpected to write %i words\n", y, x);
  }

  if( verbose ) {
    fprintf(stderr, "Wrote %i words to %s\n", y, filename);
  }

  fclose(fp);
  return 0;
}

TOKEN *process_input(const char *filename) {
  FILE *fp;
  LINE *curr_line = filelines, *line_tmp = NULL;
  TOKEN *head_token = NULL, *curr_token = NULL, *tmp_token = NULL;
  int lineno = 0, strind = 0, len = 0;
  char inbuffer[BUFFSIZE];

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

/*
 * This will eventually become a command line option and
 * be changed to allow dumping to a file.
 */
void print_sym_tree(const char *filename) {
  SYMBOL *curr = syms;
  FILE *fp = NULL;

  if( !(fp = fopen(filename,"w"))) {
    fprintf(stderr,"Couldn't open file: %s\n",filename);
    return;      /* This should probably be exit(1) */
  }

  while(curr) {
    fprintf(fp, "%s: %i\n", curr->str, curr->value);
    curr = curr->next;
  }

  fclose(fp);
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
