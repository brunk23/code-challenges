#include "compiler.h"
#include "compile_math.h"
#include "compile_utility.h"
#include "compile_symbol.h"
#include "compile_tree.h"

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
