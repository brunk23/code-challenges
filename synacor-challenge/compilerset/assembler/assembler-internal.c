#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "assembler.h"

/*
 * This will tokenize the source file.  It's a pre-processing step.
 */
TOKEN *token(char *s, int start) {
  TOKEN *curr = NULL;
  char tmp[BUFFSIZE];
  int i = 0, j = 0, size = 0;

  if( !(curr = malloc( sizeof(TOKEN) ))) {
    fprintf(stderr,"Failed to get memory in token(): ");
    return (TOKEN *)FAIL;
  }
  curr->line = 0;
  curr->type = 0;
  curr->value = 0;
  curr->location = 0;
  curr->length = 0;
  curr->word = NULL;
  curr->next = NULL;

  size = strlen(s);
  i = start;
  while( isspace(s[i])) {
    i++;
    if( i == size ) {
      free(curr);
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
	  curr->type = WORD;
	} else {
	  curr->type = NUMBER;
	}
      }
    }
    if( s[i] == ':' ) {
      if( j == 0 ) {
	fprintf(stderr, "No label found: ");
	free(curr);
	return (TOKEN *)FAIL;
      }
      curr->type = LABEL;
      i++;
      break;
    }
    if( s[i] == '\"' ) {
      if( j == 0 ) {
	curr->type = STRING;
	tmp[j] = s[i];
	j++;
	i++;
	while( s[i] != '\"' && i < size ) {
	  if( s[i] != '\\' ) {
	    tmp[j] = s[i];
	    j++;
	    i++;
	  } else {
	    i++;
	    tmp[j] = s[i];
	    i++;
	    j++;
	  }
	}
	tmp[j] = '\"';
	j++;
	tmp[j] = 0;
	i++;
      }
    }
    if( isspace(s[i]) || s[i] == '#' ) {
      if( j == 0 ) {
	free(curr);
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
    return (TOKEN *)FAIL;
  }
  strncpy(curr->word,tmp,j);
  curr->word[j] = '\0';
  curr->value = strtol(curr->word, 0, 10);
  curr->length = i;
  return curr;
}

void print_token(TOKEN *t) {
  printf("Line: %i\n",t->line);
  printf("Type: %i\n",t->type);
  printf("Value: %i\n",t->value);
  printf("Location: %i\n",t->location);
  printf("Length: %i\n",t->length);
  printf("Word: \"%s\"\n\n",t->word);
}

int pass1(TOKEN *tokens, LINE *source) {
  TOKEN *curr = tokens;
  SWORD inst;
  SYMBOL *tmp;
  int error = false;
  pc = 0;

  while( curr ) {
    if( curr->type == LABEL ) {
      if( (tmp = find_symbol(curr->word )) ) {
	  tmp->value = pc;
	  tmp->resolved = RESOLVED;
	  tmp->count = 0;
      } else {
	add_symbol(curr->word, RESOLVED, pc);
      }
      curr = curr->next;
    } else {
      /* Try and see if this is a reserved word */
      inst = reserved(curr->word);
      if( inst == USERWORD ) {
	/* Not a reserved word */
	fprintf(stderr,"WARNING: Unexpected word \"%s\" where command should be. [Line %i]\n",
		curr->word,curr->line);
        fprintf(stderr,"%s",source_line(source,curr->line));
	fprintf(stderr,"Ignoring unexpected word.\n");
	curr = curr->next;
      } else {
	/*  Process instructions and directives  */
	curr->value = inst;
	switch (inst) {
	case ORIGIN:
	  curr->location = pc;
	  curr = origin_handler(curr, source, &error);
	  break;
	case eq:
	case gt:
	case add:
	case mult:
	case mod:
	case and:
	case or:
	  curr = three_ops_handler(curr, source, &error);
	  break;
	case set:
	case jt:
	case jf:
	case not:
	case rmem:
	case wmem:
	  curr = two_ops_handler(curr, source, &error);
	  break;
	case in:
	case out:
	case push:
	case pop:
	case jmp:
	case call:
	  curr = one_ops_handler(curr, source, &error);
	  break;
	case nop:
	case halt:
	case ret:
	  memory[pc] = inst;
	  curr->location = pc;
	  pc++;
	  curr = curr->next;
	  break;
	case DATA:
	  curr = data_handler(curr,source, &error);
	  break;
	default:
	  fprintf(stderr,"WARNING: Unrecognized instruction \"%s\" [Line %i]\n",
		  curr->word,curr->line);
	  fprintf(stderr,"%s",source_line(source,curr->line));
	  curr = curr->next;
	  break;
	}
      }
    }
  }
  return error;
}

int pass2(TOKEN *c, LINE *source) {
  int error = false;
  SYMBOL *s;

  while( c ) {
    if( c->value == UNRESOLVED ) {
      if( !(s = find_symbol(c->word)) || s->resolved == UNRESOLVED ) {
	fprintf(stderr,"ERROR: Unresolved symbol \"%s\" [Line %i]\n",
		c->word, c->line);
	fprintf(stderr,"%s",source_line(source,c->line));
	error = true;
	return error;
      }
      c->value = s->value;
      s->count++;
      memory[c->location] = s->value;
    }
    c = c->next;
  }

  s = syms;
  while( s ) {
    if( s->count == 0 ) {
	fprintf(stderr,"WARNING: Label \"%s\" was never used\n", s->str);
    }
    s = s->next;
  }
  return error;
}

void error_missing_word(TOKEN *curr, LINE *source) {
  fprintf(stderr,"ERROR: Unexpected end of tokens. [Line %i]\n",
	  curr->line);
  fprintf(stderr,"%s",source_line(source,curr->line));
}

TOKEN *one_ops_handler(TOKEN *curr, LINE *source, int *error) {
  char *inst = curr->word;
  int val = curr->value;
  curr->location = pc;
  memory[pc] = curr->value;
  pc++;
  if( !curr->next ) {
    error_missing_word(curr,source);
    *error = true;
    return curr->next;
  }
  curr = curr->next;
  curr->value = token_value(curr);
  if( val == pop && (curr->value < r0 || curr->value > r7 )) {
    fprintf(stderr,"WARNING: 1st argument to %s should be a register.\n",inst);
    fprintf(stderr,"%s",source_line(source,curr->line));
  }
  curr->location = pc;
  memory[pc] = curr->value;
  pc++;
  return curr->next;
}

TOKEN *two_ops_handler(TOKEN *curr, LINE *source, int *error) {
  char *inst = curr->word;
  int val = curr->value;
  curr->location = pc;
  memory[pc] = curr->value;
  pc++;
  if( !curr->next ) {
    error_missing_word(curr,source);
    *error = true;
    return curr->next;
  }
  curr = curr->next;
  curr->value = token_value(curr);
  switch( val ) {
  case set:
  case not:
  case rmem:
    if( curr->value < r0 || curr->value > r7 ) {
      fprintf(stderr,"WARNING: 1st argument to %s should be a register.\n",inst);
      fprintf(stderr,"%s",source_line(source,curr->line));
    }
    break;
  default:
      break;
  }
  curr->location = pc;
  memory[pc] = curr->value;
  pc++;
  if( !curr->next ) {
    error_missing_word(curr,source);
    *error = true;
    return curr->next;
  }
  curr = curr->next;
  curr->location = pc;
  memory[pc] = token_value(curr);
  pc++;
  return curr->next;
}

TOKEN *three_ops_handler(TOKEN *curr, LINE *source, int *error) {
  char *inst = curr->word;
  curr->location = pc;
  memory[pc] = curr->value;
  pc++;
  if( !curr->next ) {
    error_missing_word(curr,source);
    *error = true;
    return curr->next;
  }
  curr = curr->next;
  curr->value = token_value(curr);
  if( curr->value < r0 || curr->value > r7 ) {
    fprintf(stderr,"WARNING: 1st argument to %s should be a register.\n",inst);
    fprintf(stderr,"%s",source_line(source,curr->line));
  }
  curr->location = pc;
  memory[pc] = curr->value;
  pc++;
  if( !curr->next ) {
    error_missing_word(curr,source);
    *error = true;
    return curr->next;
  }
  curr = curr->next;
  curr->location = pc;
  memory[pc] = token_value(curr);
  pc++;
  if( !curr->next ) {
    error_missing_word(curr,source);
    *error = true;
    return curr->next;
  }
  curr = curr->next;
  curr->location = pc;
  memory[pc] = token_value(curr);
  pc++;
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
    if( csym->resolved == RESOLVED ) {
      curr->value = csym->value;
    } else {
      curr->value = UNRESOLVED;
    }
  }
  return curr->value;
}

/*
 * This needs to be modified to also take strings.
 */
TOKEN *data_handler(TOKEN *curr, LINE *source, int *error) {
  int line = curr->line, i = 1;
  if( !curr->next ) {
    *error = true;
    return curr->next;
  }
  curr->location = pc;
  curr = curr->next;
  if( curr->type == STRING ) {
    curr->location = pc;
    while( curr->word[i] != '"' && curr->word[i] != '\0' ) {
      memory[pc] = curr->word[i];
      pc++;
      i++;
    }
    memory[pc] = 0;
    pc++;
    curr = curr->next;
  } else {
    while( curr && (curr->line == line) ) {
      curr->location = pc;
      memory[pc] = curr->value;
      pc++;
      curr = curr->next;
    }
  }
  return curr;
}

TOKEN *origin_handler(TOKEN *curr, LINE *source, int *error) {
  if( !curr->next ) {
    error_missing_word(curr, source);
    *error = true;
    return (TOKEN *)NULL;
  }
  curr = curr->next;
  if(curr->type != NUMBER) {
    fprintf(stderr,"ERROR: .origin must be a number. [Line %i]\n",
	    curr->line);
    fprintf(stderr,"%s",source_line(source,curr->line));
    *error = true;
    return curr->next;
  }
  pc = curr->value;
  return curr->next;
}

/*
 * This function will return the register value, or it will return 0.
 */
SWORD isregister(char *str) {
  if( !(strcmp(str,"r0")) ) {
    return r0;
  }
  if( !(strcmp(str,"r1")) ) {
    return r1;
  }
  if( !(strcmp(str,"r2")) ) {
    return r2;
  }
  if( !(strcmp(str,"r3")) ) {
    return r3;
  }
  if( !(strcmp(str,"r4")) ) {
    return r4;
  }
  if( !(strcmp(str,"r5")) ) {
    return r5;
  }
  if( !(strcmp(str,"r6")) ) {
    return r6;
  }
  if( !(strcmp(str,"r7")) ) {
    return r7;
  }
  return 0;
}

/*
 * This will return the value of the reserved words.
 */
SWORD reserved(char *str) {
  if( !(strcmp(str,"halt")) ) {
    return halt;
  }
  if( !(strcmp(str,"set")) ) {
    return set;
  }
  if( !(strcmp(str,"push")) ) {
    return push;
  }
  if( !(strcmp(str,"pop")) ) {
    return pop;
  }
  if( !(strcmp(str,"eq")) ) {
    return eq;
  }
  if( !(strcmp(str,"gt")) ) {
    return gt;
  }
  if( !(strcmp(str,"jmp")) ) {
    return jmp;
  }
  if( !(strcmp(str,"jt")) ) {
    return jt;
  }
  if( !(strcmp(str,"jf")) ) {
    return jf;
  }
  if( !(strcmp(str,"add")) ) {
    return add;
  }
  if( !(strcmp(str,"mult")) ) {
    return mult;
  }
  if( !(strcmp(str,"mod")) ) {
    return mod;
  }
  if( !(strcmp(str,"and")) ) {
    return and;
  }
  if( !(strcmp(str,"or")) ) {
    return or;
  }
  if( !(strcmp(str,"not")) ) {
    return not;
  }
  if( !(strcmp(str,"rmem")) ) {
    return rmem;
  }
  if( !(strcmp(str,"wmem")) ) {
    return wmem;
  }
  if( !(strcmp(str,"call")) ) {
    return call;
  }
  if( !(strcmp(str,"ret")) ) {
    return ret;
  }
  if( !(strcmp(str,"out")) ) {
    return out;
  }
  if( !(strcmp(str,"in")) ) {
    return in;
  }
  if( !(strcmp(str,"nop")) ) {
    return nop;
  }
  if( !(strcmp(str,"dread")) ) {
    return dread;
  }
  if( !(strcmp(str,"dwrite")) ) {
    return dwrite;
  }
  if( !(strcmp(str,"origin")) ) {
    return ORIGIN;
  }
  if( !(strcmp(str,"data")) ) {
    return DATA;
  }
  return USERWORD;
}

char *source_line(LINE *lp, int i) {
  while( lp ) {
    if( i == lp->number ) {
      return lp->str;
    }
    lp = lp->next;
  }
  return (char *)NULL;
}

void add_symbol(char *s, int r, int val) {
  SYMBOL *tmp = NULL, *nsym = syms;
  if( !(tmp = malloc( sizeof(SYMBOL) )) ) {
    fprintf(stderr,"Unable to create symbol for %s.\n",s);
  }
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
