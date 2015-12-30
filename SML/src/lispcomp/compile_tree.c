#include <stdio.h>
#include <string.h>

#include "compiler.h"
#include "compile_messages.h"
#include "compile_tree.h"
#include "compile_utility.h"
#include "compile_symbol.h"

int compileTree(struct Cons *base, int code[MEMSIZE]) {
  struct Cons *symTree, *ctoken;

  symTree = 0;
  
  /* The first pass collects all the symbols and populates
   * the symbol tree, it generates code for everything but
   * defun options, we call comp_progn because everything is
   * constained in a (progn ) list */
  comp_list(base,symTree,code);
  code[iptr(1)] = (HALT*OPFACT) + NIL;

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
      if( s->type != CONSTANT && a->type != CONSTANT ) {
	if( strcmp(a->val.string,s->val.string) == 0 ) {
	  return s;
	}
      }
    }
    b = b->cdr;
    s = b->car;
  }
  return 0;
}

/*
 * Returns a pointer to the value in the symTree
 * Returns 0 if the object is not in the symTree
 */
struct Cons *carType(struct Cons *a, struct Cons **s) {
  struct Cons *curr, *sym;
  curr = a->car;
  if( !a ) {
    emessg("The head of this list was empty?",1);
  }
  sym = inSymTree(curr,*s);
  if( a->type == CONSTANT && !sym ) {
    /* Constants always added to the symbol tree */
    *s = push(sym, *s);
    sym = inSymTree(curr,*s);
  }
  if( curr->type == SYMBOL ) {
    sym = process_symbol(curr,*s);
  } else {
    sym = curr;
  }
  return sym;
}

int comp_list(struct Cons *c, struct Cons *symtree,
	      int code[MEMSIZE]) {
  struct Cons *object, *curr;

  curr = c;
  while( curr ) {
    object = carType(curr, &symtree);
    
    if( object->type == INTERNAL ) {
      switch (object->ID) {
      case PROGN:
	comp_progn(curr->cdr, symtree, code);
	break;
	
      case SUM:
	comp_plus(curr->cdr, symtree, code);
	break;

      default:
	printf("Unimplemented\n");
	break;
      }
    }
    curr = curr->cdr;
  }
  return 0;
}
    
      
/*
 * Handles (progn
 * This expects a series of lists. It doesn't produce
 * any code by itself.
 */
int comp_progn(struct Cons *curr, struct Cons *symtree,
	       int code[MEMSIZE]) {
  int argument = 0;
  struct Cons *object;
 
  if(curr->car->type == CONSTANT) {
    printList(curr);
    emessg("Constant by itself in progn",1);
  }

  while(curr) {
    if(curr->car->type == LIST ) {
      comp_list(curr->car,symtree,code);
    }
    curr = curr->cdr;
  }
  
  return 0;
}

/*
 * Handles (+
 */
int comp_plus(struct Cons *curr, struct Cons *symtree,
	     int code[MEMSIZE]) {

#ifdef DEBUG
  printf("In comp_plus\n");
#endif

  return 0;
}
