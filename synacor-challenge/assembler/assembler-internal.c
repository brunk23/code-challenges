#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "assembler.h"

/*
 * This will tokenize the source file.  It's a pre-processing step.
 * We don't null terminate strings.
 */
TOKEN *token(char *s, int start) {
  TOKEN *curr = NULL;
  int i = 0, j = 0, size = 0;
  char tmp[BUFFSIZE];

  curr = get_empty_token();
  if( curr == (TOKEN *)FAIL ) {
    fprintf(stderr,"Failed to get memory in token(): ");
    return curr;
  }

  size = strlen(s);
  i = start;
  while( isspace(s[i])) {
    i++;
    if( i == size ) {
      free(curr);
      tokencount--;
      return (TOKEN *)SUCCESS;
    }
  }
  for( ; i < size ; i++ ) {
    if( j == 0 ) {
      if( s[i] == '.' ) {
	curr->type = DIRECTIVE;
	continue;
      } else {
	if( isalpha( s[i] )) {
	  if( curr->type != DIRECTIVE ) {
	    curr->type = WORD;
	  }
	} else {
	  if( s[i] == '+' || s[i] == '-' ) {
	    curr->type = MATH;
	  } else {
	    curr->type = NUMBER;
	  }
	}
      }
    }
    if( s[i] == ':' ) {
      if( j == 0 ) {
	fprintf(stderr, "No label found: ");
	free(curr);
	tokencount--;
	return (TOKEN *)FAIL;
      }
      curr->type = LABEL;
      i++;
      break;
    }
    if( s[i] == '\"' ) {
      if( j == 0 ) {
	i++;
	curr->type = STRING;
	while( s[i] != '\"' && i < size ) {
	  if( s[i] != '\\' ) {
	    tmp[j] = s[i];
	    j++;
	    i++;
	  } else {
	    i++;
	    switch (s[i]) {
	    case '0':
	      tmp[j] = 0;
	      break;
	    case 'n':
	      tmp[j] = '\n';
	      break;
	    case 't':
	      tmp[j] = '\t';
	      break;
	    default:
	      tmp[j] = s[i];
	      break;
	    }
	    i++;
	    j++;
	  }
	}
	tmp[j] = '\0';
	j++;
	i++;
      }
      curr->value = j - 1;
    }
    if( isspace(s[i]) || s[i] == ';' ||
	( j > 0 && (s[i] == '+' || s[i] == '-')) ) {
      if( j == 0 ) {
	free(curr);
	tokencount--;
	return (TOKEN *)SUCCESS;
      }
      break;
    }
    tmp[j] = s[i];
    j++;
  }

  if( !(curr->word = malloc( sizeof(char) * j + 1)) ) {
    fprintf(stderr, "Could not save string: ");
    free(curr);
    tokencount--;
    return (TOKEN *)FAIL;
  }
  strncpy(curr->word,tmp,j);
  curr->word[j] = '\0';
  curr->length = i;
  if( curr->type != STRING ) {
    curr->value = strtol(curr->word, 0, 10);
  }

  /*
   * Correctly handle EOF after last char on last line.
   */
  if( curr->length == start ) {
    free(curr->word);
    free(curr);
    curr = NULL;
  }
  return curr;
}

TOKEN *get_empty_token() {
  TOKEN *curr = NULL;
  
  if( !(curr = malloc( sizeof(TOKEN) ))) {
    return (TOKEN *)FAIL;
  }

  tokencount++;
  curr->line = 0;
  curr->type = WORD;
  curr->value = 0;
  curr->location = 0;
  curr->length = 0;
  curr->word = NULL;
  curr->next = NULL;

  return curr;
}  

void print_token(TOKEN *t) {
  printf("Line: %i\n",t->line);
  printf("Type: %i\n",t->type);
  printf("Value: %i\n",t->value);
  printf("Location: %i\n",t->location);
  printf("Length: %i\n",t->length);
  printf("Word: \"%s\"\n",t->word);
  printf("File: \"%s\"\n",t->file_name);
  printf("Source: \"%s\"\n",t->source_line);
}

/*
 * We handle the compiling of tokens to memory values here.
 * We increase pc no matter what, because
 * that will let us declare labels as arguments in commands. If
 * the label is not in a command, we will decrease the pc and
 * overwrite that value with the next command.
 */
int compile_token(TOKEN *curr) {
  SYMBOL *tmp = NULL;

  if( curr->type == LABEL ) {
    if( (tmp = find_symbol(curr->word )) ) {

      if( tmp->resolved == RESOLVED ) {
	fprintf(stderr,"WARNING: Redefined symbol \"%s\" on line %i\n",
		curr->word, curr->line);
	fprintf(stderr,"%s: %s",curr->file_name, curr->source_line);
      }

      tmp->value = pc;
      tmp->resolved = RESOLVED;
      tmp->count = 0;
    } else {
      add_symbol(curr->word, RESOLVED, pc);
    }
    curr->location = pc;
  } else {
    if( curr->type != MATH ) {
      curr->location = pc;
      memory[pc] = token_value(curr);
    } else {
      pc--;
    }
  }
  pc++;

  return curr->type;
}

/*
 * This is a very basic pass1. It traverses the token list one
 * token at a time, parsing each as it goes. The list might grow,
 * if there is an include file, but this will continue through
 * each item.
 */
int pass1() {
  TOKEN *curr = tokens;
  int compile_status = GOOD;
  SWORD inst;

  pc = 0;

  while( curr ) {

    if( curr->type == LABEL ) {

      /* We don't want this label to take up space, so decrement pc */
      compile_token(curr);
      pc--;
      curr = curr->next;

    } else {

      /* Try and see if this is a reserved word */
      inst = reserved(curr->word);
      if( inst == USERWORD ) {

	/* Not a reserved word is probably an error, but we'll warn and ignore */
	fprintf(stderr,"WARNING: Unexpected word \"%s\" where command should be. [Line %i]\n",
		curr->word,curr->line);
        fprintf(stderr,"%s: %s",curr->file_name,curr->source_line);
	fprintf(stderr,"Ignoring unexpected word.\n");
	curr = curr->next;

      } else {

	/*  Process instructions and directives  */
	curr->value = inst;
	if( (inst == ORIGIN) || (inst == INCLUDE) ||
	    (inst == DATA) || (inst == ASSIGN) ) {
	  switch (inst) {

	  case ORIGIN:
	    curr->location = pc;
	    curr = origin_handler(curr, &compile_status);
	    break;

	  case INCLUDE:
	    curr->location = pc;
	    curr = include_handler(curr, &compile_status);
	    break;

	  case DATA:
	    curr = data_handler(curr, &compile_status);
	    break;

	  case ASSIGN:
	    curr = assign_handler(curr, &compile_status);
	    break;

	  default:   /* This should be unreachable */
	    fprintf(stderr,"WARNING: Unrecognized instruction \"%s\" [Line %i]\n",
		    curr->word,curr->line);
	    fprintf(stderr,"%s: %s",curr->file_name,curr->source_line);
	    curr = curr->next;
	  }

	} else {
	  memory[pc] = inst;
	  curr->location = pc;
	  pc++;
	  instruction_count++;
	  switch (inst) {

	  case eq:
	  case gt:
	  case add:
	  case mult:
	  case mod:
	  case and:
	  case or:
	    arguments_count += 3;
	    curr = three_ops_handler(curr, &compile_status);
	    break;

	  case set:
	  case jt:
	  case jf:
	  case not:
	  case rmem:
	  case wmem:
	    arguments_count += 2;
	    curr = two_ops_handler(curr, &compile_status);
	    break;

	  case in:
	  case out:
	  case push:
	  case pop:
	  case rndm:
	  case jmp:
	  case call:
	    arguments_count++;
	    curr = one_ops_handler(curr, &compile_status);
	    break;

	  case nop:
	  case halt:
	  case ret:
	    curr = curr->next;
	    break;

	  default:
	    fprintf(stderr,"WARNING: Unrecognized instruction \"%s\" [Line %i]\n",
		    curr->word,curr->line);
	    fprintf(stderr,"%s: %s",curr->file_name,curr->source_line);
	    curr = curr->next;
	    break;
	  }
	}
      }
    }
  }
  return compile_status;
}

/*
 * Everything should be in memory, except for the values of labels that
 * were still unresolved when we hit them in pass1.  All the labels should
 * be resolved at this point.  We now go back in and put the correct value
 * for the missing labels.
 *
 * If a label is still unresolved, that is a fatal error.
 */
int pass2() {
  TOKEN *c = tokens;
  SYMBOL *s;
  int compile_status = GOOD;

  while( c ) {
    if( c->value == UNRESOLVED ) {

      if( !(s = find_symbol(c->word)) || s->resolved == UNRESOLVED ) {
	fprintf(stderr,"ERROR: Unresolved symbol \"%s\" [Line %i]\n",
		c->word, c->line);
        fprintf(stderr,"%s: %s",c->file_name,c->source_line);
	compile_status = BAD;
	return compile_status;
      }

      c->value = s->value;
      if( c->next && c->next->type == MATH ) {
	c->value += c->next->value;
      }
      s->count++;
      memory[c->location] = c->value;
    }

    c = c->next;
  }

  /* We will check for unused lables, but this is a warning and not an error */
  s = syms;
  while( s ) {
    if( s->count == 0 ) {
	fprintf(stderr,"WARNING: Label \"%s\" was never used\n", s->str);
    }
    s = s->next;
  }

  return compile_status;
}

/*
 * We ran out of tokens unexpectedly. This is almost certainly
 * a fatal error.
 */
void error_missing_word(TOKEN *curr) {
  fprintf(stderr,"ERROR: Unexpected end of tokens. [Line %i]\n",
	  curr->line);
  fprintf(stderr,"%s: %s",curr->file_name,curr->source_line);
}

/*
 * We expected a token from the same line, but the next token
 * isn't from this line of the source file.
 */
void error_end_of_line(TOKEN *curr) {
  fprintf(stderr,"ERROR: Unexpected end of line. [Line %i]\n",
	  curr->line);
  fprintf(stderr,"%s: %s",curr->file_name,curr->source_line);
}

int verify_next_token(TOKEN *curr) {
  int line = curr->line;

  if( !curr->next ) {
    error_missing_word(curr);
    return BAD;
  }

  if( !(line == curr->next->line) ) {
    error_end_of_line(curr);
    return BAD;
  }

  return GOOD;
}

/*
 * This will compile one token into memory. It will warn if the
 * instruction expects a register and didn't get one.
 */
TOKEN *one_ops_handler(TOKEN *curr, int *compile_status) {
  char *inst = curr->word;
  int val = curr->value;

  /* First Argument */
  if( verify_next_token(curr) == BAD ) {
    *compile_status = BAD;
    return curr->next;
  }
  curr = curr->next;
  compile_token(curr);

  if( (val == pop || val == rndm) &&
      (curr->value < r0 || curr->value > r7 )) {
    fprintf(stderr,"WARNING: 1st argument to %s should be a register.\n",inst);
    fprintf(stderr,"%s: %s",curr->file_name,curr->source_line);
  }

  return curr->next;
}

/*
 * This will compile two tokens into memory. It will warn if the first one
 * is expected to be a register and didn't get one.
 */
TOKEN *two_ops_handler(TOKEN *curr, int *compile_status) {
  char *inst = curr->word;
  int val = curr->value;

  /* First Argument */
  if( verify_next_token(curr) == BAD ) {
    *compile_status = BAD;
    return curr->next;
  }
  curr = curr->next;
  compile_token(curr);

  switch( val ) {
  case set:
  case not:
  case rmem:
    if( curr->value < r0 || curr->value > r7 ) {
      fprintf(stderr,"WARNING: 1st argument to %s should be a register.\n",inst);
      fprintf(stderr,"%s: %s",curr->file_name,curr->source_line);
    }
    break;
  default:
      break;
  }

  /* Second Argument */
  if( verify_next_token(curr) == BAD ) {
    *compile_status = BAD;
    return curr->next;
  }
  curr = curr->next;
  compile_token(curr);

  return curr->next;
}

TOKEN *three_ops_handler(TOKEN *curr, int *compile_status) {
  char *inst = curr->word;

  /* First Argument */
  if( verify_next_token(curr) == BAD ) {
    *compile_status = BAD;
    return curr->next;
  }
  curr = curr->next;
  compile_token(curr);

  if( curr->value < r0 || curr->value > r7 ) {
    fprintf(stderr,"WARNING: 1st argument to %s should be a register.\n",inst);
    fprintf(stderr,"%s: %s",curr->file_name,curr->source_line);
  }

  /* Second Argument */
  if( verify_next_token(curr) == BAD ) {
    *compile_status = BAD;
    return curr->next;
  }
  curr = curr->next;
  compile_token(curr);

  /* Third Argument */
  if( verify_next_token(curr) == BAD ) {
    *compile_status = BAD;
    return curr->next;
  }
  curr = curr->next;
  compile_token(curr);

  return curr->next;
}

/*
 * This will return the value of a given token (a number that represents its
 * memory address, numeric contents, resgister number).
 */
SWORD token_value(TOKEN *curr) {
  SYMBOL *csym;

  if(curr->type == NUMBER) {
    while ( curr->value < 0 ) {
      curr->value += 32768;
    }
    curr->value %= 32768;
    return curr->value;
  }

  curr->value = isregister(curr->word);
  if(curr->value > 0) {
    return curr->value;
  }

  csym = find_symbol(curr->word);
  if( !csym ) {
    add_symbol(curr->word, UNRESOLVED, UNRESOLVED);
    curr->value = UNRESOLVED;
  } else {
    /* Will return the value or UNRESOLVED depending on contents */
    curr->value = csym->value;
    if( curr->value != UNRESOLVED &&
	curr->next && curr->next->type == MATH ) {
      curr->value += curr->next->value;
    }
  }

  return curr->value;
}

/*
 * This stuffs all the information on the line into memory.
 */
TOKEN *data_handler(TOKEN *curr, int *compile_status) {
  int line = curr->line, i = 0;

  /* We need at least one valid token on the line */
  if( verify_next_token(curr) == BAD ) {
    *compile_status = BAD;
    return curr->next;
  }
  curr = curr->next;

  if( curr->type == STRING ) {
    curr->location = pc;
    data_words += curr->value;
    while( i < curr->value ) {
      memory[pc] = curr->word[i];
      pc++;
      i++;
    }
    curr = curr->next;
  } else {
    while( curr && (curr->line == line) ) {
      compile_token(curr);
      curr = curr->next;
      data_words++;
    }
  }

  return curr;
}

/*
 * This adds a symbol to the table
 */
TOKEN *assign_handler(TOKEN *curr, int *compile_status) {
  char *symstr = NULL;

  if( verify_next_token(curr) == BAD ) {
    *compile_status = BAD;
    return curr->next;
  }
  curr = curr->next;

  if( curr->type != WORD ) {
    fprintf(stderr, "WARNING: .assign lval should be a word. [Line %i]\n",
	    curr->line);
    return curr->next;
  }
  symstr = curr->word;

  if( verify_next_token(curr) == BAD ) {
    *compile_status = BAD;
    return curr->next;
  }
  curr = curr->next;

  if( curr->type != NUMBER ) {
    fprintf(stderr, "WARNING: .assign rval should be a number. [Line %i]\n",
	    curr->line);
    return curr->next;
  }

  add_symbol(symstr, RESOLVED, curr->value);

  return curr->next;
}

/*
 * This changes where pc is pointing during pass1
 */
TOKEN *origin_handler(TOKEN *curr, int *compile_status) {

  if( verify_next_token(curr) == BAD ) {
    *compile_status = BAD;
    return curr->next;
  }
  curr = curr->next;

  if(curr->type != NUMBER) {
    fprintf(stderr,"ERROR: .origin must be a number. [Line %i]\n",
	    curr->line);
    fprintf(stderr,"%s: %s",curr->file_name,curr->source_line);
    *compile_status = BAD;
    return curr->next;
  }

  pc = curr->value;

  return curr->next;
}

/*
 * This will read a new file into the token tree at the location
 * we are at. It should handle includes in includes seamlessly.
 */
TOKEN *include_handler(TOKEN *curr, int *compile_status) {
  TOKEN *after_file = NULL, *file_token = NULL, *head_token = NULL;

  if( verify_next_token(curr) == BAD ) {
    *compile_status = BAD;
    return curr->next;
  }

  /* We need to save the token after the filename to connect this
   * token chain to the main one */
  file_token = curr->next;
  after_file = file_token->next;

  if( file_token->type != STRING ) {
    fprintf(stderr,"ERROR: .include must be a filename. [Line %i]\n",
	    curr->line);
    fprintf(stderr,"%s: %s",curr->file_name,curr->source_line);
    *compile_status = BAD;
  } else {
    if( !(head_token = process_input( file_token->word ))) {
      fprintf(stderr,"WARNING: .include \"%s\" did not produce any tokens. Line [%i]\n",
	      file_token->word, file_token->line);
      return after_file;
    }
  }

  /* If we got tokens we need to find the last one. */
  if( head_token ) {
    /* We must link here for the memory freeing to work correctly */
    file_token->next = head_token;
    file_token = head_token;

    while(file_token->next) {
      file_token = file_token->next;
    }
    file_token->next = after_file;

  } else {
    return after_file;
  }

  return head_token;
}

/*
 * This function will return the register value, or it will return 0.
 */
SWORD isregister(char *str) {
  const char *words[] = { "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", 0 };
  const SWORD values[] = { r0, r1, r2, r3, r4, r5, r6, r7 };
  int i = 0;

  while( words[i] != 0 ) {
    if( !(strcmp(str,words[i])) ) {
      return values[i];
    }
    i++;
  }

  return 0;
}

/*
 * These global constants are really only used by reserved()
 * but this keeps them off the stack
 */
const char *words[] = { "halt", "set", "push", "pop", "eq", "gt", "jmp",
			"jt", "jf", "add", "mult", "mod", "and", "or",
			"not", "rmem", "wmem", "call", "ret", "out", "in",
			"nop", "rndm", "dread", "dwrite", "origin",
			"include", "data", "assign", 0 };
const SWORD values[] = { halt, set, push, pop, eq, gt, jmp,
			 jt, jf, add, mult, mod, and, or,
			 not, rmem, wmem, call, ret, out, in,
			 nop, rndm, dread, dwrite, ORIGIN,
			 INCLUDE, DATA, ASSIGN, USERWORD };

/*
 * This will return the value of the reserved words.
 */
SWORD reserved(char *str) {
  int i = 0;

  while( words[i] != 0 ) {
    if( !(strcmp(str,words[i])) ) {
      return values[i];
    }
    i++;
  }

  return USERWORD;
}

void add_symbol(char *s, int r, int val) {
  SYMBOL *tmp = NULL, *nsym = syms;

  if( !(tmp = malloc( sizeof(SYMBOL) )) ) {
    fprintf(stderr,"Unable to create symbol for %s.\n",s);
  }
  symbolcount++;

  tmp->str = s;
  tmp->resolved = r;
  tmp->value = val;
  tmp->count = 0;
  tmp->next = NULL;

  if( nsym ) {
    while( nsym->next ) {
      nsym = nsym->next;
    }
    nsym->next = tmp;
  } else {
    syms = tmp;
  }
}

/*
 * We use this to find symbols.
 */
SYMBOL *find_symbol(char *str) {
  SYMBOL *s = syms;

  while( s ) {
    if( !(strcmp(s->str, str)) ) {
      if( s->resolved == RESOLVED ) {
	s->count++;
      }
      return s;
    }
    s = s->next;
  }

  return (SYMBOL *)NULL;
}
