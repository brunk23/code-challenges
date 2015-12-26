#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "compiler.h"

struct Node *newNode(enum NTYPE ntype, struct Node *left, struct Node *right,
		     union SymbolValue sym, int location) {
  struct Node *curr;

  curr = malloc( sizeof( struct Node ) );
  
  if( !curr ) {
    emessg("Failed to create node.",1);
  }

  curr->type = ntype;
  curr->left = left;
  curr->right = right;

  if( ntype == STRING || ntype == BASE || ntype == LABEL ) {
    /*
     * The string should be allocated safely before newNode is called
     */
    curr->val.string = sym.string;
  }
  if( ntype == CONSTANT ) {
    curr->val.number = sym.number;
  }
  if( ntype == KEYWORD ) {
    curr->val.keyword = sym.keyword;
  }
  if( ntype == BASE ) {
    curr->resolved = 1;
  } else {
    curr->resolved = 0;
  }
  curr->location = location;

  return curr;
}

int printNode(struct Node *node) {
  printf("Memory Address: %x\n",node);
  printf("Left: %x\n",node->left);
  printf("Right: %x\n",node->right);
  printf("Type: %i\nValue: ",node->type);
  if( node->type == STRING ||
      node->type == BASE ||
      node->type == VARIABLE) {
    printf("%s\n",node->val.string);
  }
  if( node->type == CONSTANT ) {
    printf("%i\n",node->val.number);
  }
  if( node->type == KEYWORD ) {
    printf("%i\n",node->val.keyword);
  }
  printf("Location: %i\nResolved: ",node->location);
  if( node->resolved ) {
    printf("true\n");
  } else {
    printf("false\n");
  }
  return 0;
}
