#ifndef COMPILE_DEBUG_H
#define COMPILE_DEBUG_H

#include "compiler.h"

int printToken(struct Token *);
char *printType(enum TYPE);
char *printInternalID(int);

#endif
