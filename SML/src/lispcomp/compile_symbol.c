#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "compiler.h"

/*
 * This will process functions and built-ins
 */
struct Cons *process_symbol(struct Cons *curr, struct Cons *sym) {
  char *n;
  struct Cons *temp = curr;
  
  n = curr->val.string;
  
  if(strcmp(n,"defun") == 0) {
    temp->type = INTERNAL;
    temp->ID = DEFUN;
    temp->args = -1;
  }
  if(strcmp(n,"setf") == 0) {
    temp->type = INTERNAL;
    temp->ID = SETF;
    temp->args = 2;
  }
  if(strcmp(n,"print") == 0) {
    temp->type = INTERNAL;
    temp->ID = PRINT;
    temp->args = 1;
  }
  if(strcmp(n,"read") == 0) {
    temp->type = INTERNAL;
    temp->ID = INPUT;
    temp->args = 1;
  }
  if(strcmp(n,"+") == 0) {
    temp->type = INTERNAL;
    temp->ID = SUM;
    temp->args = -1;
  }
  if(strcmp(n,"-") == 0) {
    temp->type = INTERNAL;
    temp->ID = DIFFERENCE;
    temp->args = -1;
  }
  if(strcmp(n,"*") == 0) {
    temp->type = INTERNAL;
    temp->ID = PRODUCT;
    temp->args = -1;
  }
  if(strcmp(n,"/") == 0) {
    temp->type = INTERNAL;
    temp->ID = QUOTIENT;
    temp->args = -1;
  }
  if(strcmp(n,"%") == 0) {
    temp->type = INTERNAL;
    temp->ID = REMAINDER;
    temp->args = -1;
  }
  if(strcmp(n,"if") == 0) {
    temp->type = INTERNAL;
    temp->ID = IF;
    temp->args = 3;
  }
  if(strcmp(n,"<") == 0) {
    temp->type = INTERNAL;
    temp->ID = LT;
    temp->args = 2;
  }
  if(strcmp(n,"progn") == 0) {
    temp->type = INTERNAL;
    temp->ID = PROGN;
    temp->args = -1;
  }
  return temp;
}

int resolve_symbols(struct Cons *tree, struct Cons *syms,
		    int code[MEMSIZE]) {
  struct Cons *curr, *s;
  curr = tree;
  while( curr ) {
    if( curr->car->type == LIST ) {
      resolve_symbols(curr->car, syms, code);
    }
    if( curr->car->resolved == NIL ) {
      s = inSymTree(curr->car, syms);
      if( s ) {
	code[curr->car->location] += s->location;
      } else {
	emessg("Symbol not found",1);
      }
    }
    curr = curr->cdr;
  }
  return 0;
}
int assign_symbols(struct Cons *tree, int code[MEMSIZE]) {
  struct Cons *curr;
  curr = tree;

  while( curr ) {
    if( curr->car->type == CONSTANT ) {
      curr->car->location = iptr(0);
      curr->car->resolved = T;
      code[iptr(1)] = curr->car->val.value;
    }
    if( curr->car->type == VARIABLE ) {
      curr->car->location = iptr(1);
      curr->car->resolved = T;
    }
    if( curr->car->type == STRING ) {
      curr->car->location = iptr(0);
      if( strlen(curr->car->val.string) > 0 ) {
	/* copy the string into memory here */
      }
      iptr(INPMAX/2+1);
    }
    curr = curr->cdr;
  }
  return 0;
}

/*
 * Will go down the tree looking for a symbol.
 */
struct Cons *inSymTree(struct Cons *a, struct Cons *sym) {
  struct Cons *s, *b;
  b = sym;
  while( b ) {
    s = b->car;
    if( s->type == CONSTANT && a->type == CONSTANT ) {
      if( a->val.value == s->val.value ) {
	return s;
      }
    } else {
      if( (s->val.string && a->val.string) &&
	  (s->type != CONSTANT) &&
	  (a->type != CONSTANT)) {
	if( strcmp(a->val.string,s->val.string) == 0 ) {
	  return s;
	}
      }
    }
    b = b->cdr;
  }
  return 0;
}

/*
 * Returns a pointer to the value in the symTree
 * Returns 0 if the object is not in the symTree
 */
struct Cons *cType(struct Cons *a, struct Cons **s) {
  struct Cons *curr, *sym;
  curr = a;
  if( !a ) {
    emessg("The head of this list was empty?",1);
  }
  sym = inSymTree(curr,*s);
  if( a->type == CONSTANT && !sym ) {
    /* Constants always added to the symbol tree */
    (*s) = push(copy(a), *s);
    sym = inSymTree(curr,*s);
  }
  if( curr->type == SYMBOL ) {
    sym = process_symbol(curr,*s);
  } else {
    sym = curr;
  }
  return sym;
}
