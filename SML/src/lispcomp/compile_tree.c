#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "compiler.h"
#include "compile_messages.h"
#include "compile_tree.h"
#include "compile_utility.h"
#include "compile_symbol.h"

int compileTree(struct Cons *base, int code[MEMSIZE]) {
  struct Cons *symTree;

  symTree = 0;
  
  /* The first pass collects all the symbols and populates
   * the symbol tree, it generates code for everything but
   * defun options, we call comp_progn because everything is
   * constained in a (progn ) list */
  comp_list(base,&symTree,code);
  code[iptr(1)] = (HALT*OPFACT) + NIL;

  assign_symbols(symTree,code);
  resolve_symbols(base,symTree,code);
  
  return 0;
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
      code[curr->car->location] += s->location;
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
	  !(s->type == CONSTANT || a->type == CONSTANT)) {
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

int comp_list(struct Cons *c, struct Cons **symtree,
	      int code[MEMSIZE]) {
  struct Cons *object, *curr;

  curr = c;
  while( curr ) {
    object = cType(curr->car, symtree);
    
    if( object->type == INTERNAL ) {
      switch (object->ID) {
      case PROGN:
	comp_progn(curr->cdr, symtree, code);
	break;
	
      case SUM:
	comp_plus(curr->cdr, symtree, code);
	break;

      case PRINT:
	comp_print(curr->cdr, symtree, code);
	break;

      case DIFFERENCE:
	comp_subtract(curr->cdr, symtree, code);
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
int comp_progn(struct Cons *curr, struct Cons **symtree,
	       int code[MEMSIZE]) {
 
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
int comp_plus(struct Cons *curr, struct Cons **symtree,
	     int code[MEMSIZE]) {
  int x;
  struct Cons *arg;

  /* Get the first value into accumulator. If it is a
   * symbol or value, we load it. If it is a list, we
   * execute it, because it will leave its result in the
   * accumulator */
  arg = nth(curr,1);
  arg = cType(arg,symtree);
  if(arg->type == LIST) {
    comp_list(arg,symtree,code);
  } else {
    arg->location = iptr(0);
    arg->resolved = NIL;
    code[iptr(1)] = (LOAD*OPFACT) + NIL;
  }
  
  for( x = 2; x <= length(curr); ++x ) {
    arg = nth(curr,x);
    arg = cType(arg,symtree);
    if(arg->type == LIST) {
      code[iptr(1)] = (PUSH*OPFACT) + NIL;
      comp_list(arg,symtree,code);
      code[iptr(1)] = (POP*OPFACT) + ADD;
    } else {
      arg->location = iptr(0);
      arg->resolved = NIL;
      code[iptr(1)] = (ADD*OPFACT) + NIL;
    }
  }
  
  return 0;
}

int comp_print(struct Cons *curr, struct Cons **symtree,
	     int code[MEMSIZE]) {
  struct Cons *arg, *temp;
  int x, y;
  
  if( length(curr) > 1 ) {
    emessg("Too many arguments to print",1);
  }

  arg = curr->car;

  if(arg->type == LIST) {
    comp_list(arg,symtree,code);
    /* we need to make a location to save the value in */
    if( !(temp = malloc( sizeof( struct Cons)))) {
      emessg("Failed to create temp.",1);
    }
    temp->car = 0;
    temp->cdr = 0;
    temp->type = VARIABLE;
    temp->location = -1;
    x = getID();
    temp->ID = x;
    temp->resolved = NIL;
    if( !(temp->val.string = malloc( 10 ))) {
      emessg("Failed to make room for string.",1);
    }
    y = 0;
    while( x > 0 ) {
      temp->val.string[y] = (x % 8) + '0';
      x = x / 8;
      y++;
    }
    temp->val.string[y] = 0;
    printf("%s\n",temp->val.string);
    (*symtree) = push(temp, *symtree);
    arg->resolved = NIL;
    arg->val.string = temp->val.string;
    arg->location = iptr(0);
    code[iptr(1)] = (STORE*OPFACT) + NIL;
    arg->car->resolved = NIL;
    arg->car->val.string = temp->val.string;
    arg->car->location = iptr(0);
    code[iptr(1)] = (WRITE*OPFACT) + NIL;
  }
  
  if(arg->type == STRING) {
    arg->location = iptr(0);
    arg->resolved = NIL;
    code[iptr(1)] = (SWRITE*OPFACT) + NIL;
  } else {
    if(arg->type == CONSTANT) {
      arg->location = iptr(0);
      arg->resolved = NIL;
      code[iptr(1)] = (WRITE*OPFACT) + NIL;
    }
  }
  return 0;
}

/*
 * Handles (+
 */
int comp_subtract(struct Cons *curr, struct Cons **symtree,
	     int code[MEMSIZE]) {
  int x;
  struct Cons *arg;

  /* Get the first value into accumulator. If it is a
   * symbol or value, we load it. If it is a list, we
   * execute it, because it will leave its result in the
   * accumulator */
  arg = nth(curr,1);
  arg = cType(arg,symtree);
  if(arg->type == LIST) {
    comp_list(arg,symtree,code);
  } else {
    arg->location = iptr(0);
    arg->resolved = NIL;
    code[iptr(1)] = (LOAD*OPFACT) + NIL;
  }
  
  for( x = 2; x <= length(curr); ++x ) {
    arg = nth(curr,x);
    arg = cType(arg,symtree);
    if(arg->type == LIST) {
      code[iptr(1)] = (PUSH*OPFACT) + NIL;
      comp_list(arg,symtree,code);
      code[iptr(1)] = (POP*OPFACT) + SUBTRACT;
    } else {
      arg->location = iptr(0);
      arg->resolved = NIL;
      code[iptr(1)] = (SUBTRACT*OPFACT) + NIL;
    }
  }
  
  return 0;
}
