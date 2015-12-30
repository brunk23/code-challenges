#include <stdio.h>

#include "compiler.h"

int comp_if(struct Cons *head, struct Cons **symtree,
	    int code[MEMSIZE]) {
  struct Cons *arg, *curr;

  curr = head->cdr;
  
  if( length(curr) != head->car->args ) {
    fprintf(stderr,"(IF ");
    printList(curr);
    emessg("Incorrect number of arguments to IF",1);
  }

  arg = curr->car;  

  if( arg->type == LIST ) {
    comp_list(arg, symtree,code);
  } else {
    arg->location = iptr(0);
    arg->resolved = NIL;
    code[iptr(1)] = (LOAD*OPFACT) + NIL;
  }
  head->car->location = iptr(0);
  code[iptr(1)] = (BRANCHZERO*OPFACT) + NIL;

  arg = nth(curr,2);
  if( arg->type == LIST ) {
    comp_list(arg, symtree,code);
  } else {
    arg->location = iptr(0);
    arg->resolved = NIL;
    code[iptr(1)] = (LOAD*OPFACT) + NIL;
  }
  code[iptr(1)] = (BRANCH*OPFACT) + NIL;
  code[head->car->location] += iptr(0);
  head->car->location = iptr(0) - 1;

  arg = nth(curr,3);
  if( arg->type == LIST ) {
    comp_list(arg, symtree,code);
  } else {
    arg->location = iptr(0);
    arg->resolved = NIL;
    code[iptr(1)] = (LOAD*OPFACT) + NIL;
  }
  code[head->car->location] += iptr(0);
  
  return 0;
}
