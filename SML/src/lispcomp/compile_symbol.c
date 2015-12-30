#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "compiler.h"
#include "compile_symbol.h"
#include "compile_messages.h"

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

struct Cons *copy(struct Cons *old) {
  struct Cons *cpy;

  if( !(cpy = malloc( sizeof( struct Cons ) ) ) ) {
    emessg("Couldn't get copy",1);
  }
  cpy->car = 0;
  cpy->cdr = 0;
  cpy->type = old->type;
  if(old->type == CONSTANT) {
    cpy->val.value = old->val.value;
  } else {
    cpy->val.string = old->val.string;
  }
  cpy->ID=old->ID;
  cpy->args=old->args;
  cpy->location= -1;
  cpy->resolved = NIL;

  return cpy;
}
