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

int comp_cond(struct Cons *head, struct Cons **symtree,
	      int code[MEMSIZE], int oper) {
  struct Cons *arg1, *arg2, *curr;

  curr = head->cdr;
  
  if( length(curr) != head->car->args ) {
    fprintf(stderr,"(%s ",head->car->string);
    printList(curr);
    emessg("Incorrect number of arguments to COND",1);
  }

  /* Determine the order of the operations */
  switch (oper) {
  case EQL:
  case DNE:
  case GT:
  case GTE:
    arg1 = nth(curr, 2);
    arg2 = nth(curr, 1);
    break;

  case LT:
  case LTE:
    arg1 = nth(curr, 1);
    arg2 = nth(curr, 2);
    break;

  default:
    break;
  }
  
  if(arg1->type == LIST) {
    comp_list(arg1,symtree,code);
  } else {
    arg1->location = iptr(0);
    arg1->resolved = NIL;
    code[iptr(1)] = (LOAD*OPFACT) + NIL;
  }
  if(arg2->type == LIST) {
    code[iptr(1)] = (PUSH*OPFACT) + NIL;
    comp_list(arg2,symtree,code);
    code[iptr(1)] = (POP*OPFACT) + SUBTRACT;
  } else {
    arg2->location = iptr(0);
    arg2->resolved = NIL;
    code[iptr(1)] = (SUBTRACT*OPFACT) + NIL;
  }

  switch (oper) {
    /* if it's 0, make non-zero, else make zero */
  case EQL:
    code[iptr(0)] = (BRANCHZERO*OPFACT) + iptr(0) + 2;
    iptr(1);
    code[iptr(1)] = (LOAD*OPFACT) + NIL;
    code[iptr(1)] = (SUBTRACT*OPFACT) + NIL;
    break;

    /* If they are equal accumulator is already 0 */
  case DNE:
    break;

  case GT:
  case LT:
    code[iptr(0)] = (BRANCHNEG*OPFACT) + iptr(0) + 3;
    iptr(1);
    code[iptr(1)] = (LOAD*OPFACT) + NIL;
    code[iptr(1)] = (SUBTRACT*OPFACT) + NIL;
    break;

  case GTE:
  case LTE:
    code[iptr(0)] = (BRANCHNEG*OPFACT) + iptr(0) + 4;
    iptr(1);
    code[iptr(0)] = (BRANCHZERO*OPFACT) + iptr(0) + 2;
    iptr(1);
    code[iptr(1)] = (LOAD*OPFACT) + NIL;
    code[iptr(1)] = (SUBTRACT*OPFACT) + NIL;
    break;
    
  default:
    break;
  }

  return 0;
}
