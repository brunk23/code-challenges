#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "compiler.h"

/*
 * This will process functions and built-ins
 */
int process_functions(char *n, struct Cons *curr) {

  struct Cons *temp = curr;
  
  if(strcmp(n,"defun") == 0) {
    temp->type = INTERNAL;
    temp->ID = DEFUN;
  }
  if(strcmp(n,"setf") == 0) {
    temp->type = INTERNAL;
    temp->ID = SETF;
  }
  if(strcmp(n,"print") == 0) {
    temp->type = INTERNAL;
    temp->ID = PRINT;
  }
  if(strcmp(n,"input") == 0) {
    temp->type = INTERNAL;
    temp->ID = INPUT;
  }
  if(strcmp(n,"+") == 0) {
    temp->type = INTERNAL;
    temp->ID = SUM;
  }
  if(strcmp(n,"if") == 0) {
    temp->type = INTERNAL;
    temp->ID = IF;
  }
  if(strcmp(n,"<") == 0) {
    temp->type = INTERNAL;
    temp->ID = LT;
  }
  if(strcmp(n,"progn") == 0) {
    temp->type = INTERNAL;
    temp->ID = PROGN;
  }
  return temp->ID;
}
