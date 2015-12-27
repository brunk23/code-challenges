#ifndef COMPILE_NODE_H
#define COMPILE_NODE_H

#include "compiler.h"

struct Node *newNode(enum NTYPE ntype, struct Node * up,
		     struct Node *left, struct Node *right,
		     union SymbolValue sym, int location);
int printNode(struct Node *node);

#endif
