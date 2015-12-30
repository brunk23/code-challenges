#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "compiler.h"
#include "compile_messages.h"
#include "compile_tree.h"
#include "compile_utility.h"
#include "compile_symbol.h"
#include "compile_math.h"

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
