#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compiler.h"
#include "compile_node.h"

int main() {
  struct Node *test = 0, *basePtr = 0, *next = 0;
  union SymbolValue val;
  char currline[] = "This is the current line";
  int linenumber = 10;
  val.string = malloc( sizeof(currline) + 1);
  val.string = strncpy(val.string, currline, sizeof(currline) + 1);

  test = newNode(BASE,basePtr,(struct Node *)0,val,linenumber);

  basePtr = test;

  val.number = 56;
  test = newNode(CONSTANT,basePtr,(struct Node *)0,val,0);

  basePtr->right = test;

  val.keyword = GOTO;

  test = newNode(KEYWORD, test,0, val, 0);

  test->left->right = test;	/* Make the previous node point to this one */

  next = basePtr;

  while(next) {
    printNode(next);
    printf("\n");
    next = next->right;
  }
  
  free(test);

  return 0;
}
