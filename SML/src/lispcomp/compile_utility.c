#include <stdlib.h>

#include "compiler.h"
#include "compile_utility.h"
#include "compile_messages.h"

/*
 * This is currently not working with '(' and ')' correctly
 */
struct Token *getNextToken(char *string) {
  static char *s;
  static int x;
  static char prev;

  struct Token *created;
  
  int y;
  
  if(string) {
    s = string;
    x = 0;
    prev = 0;
  }

  /* Ignore everything after a comment */
  if( prev == ';' || s[x] == ';' ) {
    return 0;
  }
  
  created = malloc(sizeof(struct Token));
  if( !created ) {
    emessg("Failure to create token",1);
  }

  created->car = 0;
  created->cdr = 0;
  created->location = 0;

  if( x > 0 ) {
    s[x++] = prev;
  }
  if( prev == ')' ) {
    /* we need to return a token to represent it */
    created->type = EOL;
    created->val.string = &s[x];
    prev = s[x];
    return created;
  }

  /* Do NOT discard a leading ( */
  if( prev == '(' ) {
    --x;
  }
  
  while( s[x] != 0 ) {
    if( s[x] == ' ' || s[x] == ')' ||
	s[x] == '\t' || s[x] == '\n' || s[x] == '\r' ||
	s[x] == 0 || s[x] == ';' ) {
      ++x;
    } else {
      break;
    }
  }

  y = x;
  while( s[x] != 0 ) {
    if( s[x] == ' ' || s[x] == ')' || s[x] == '(' ||
	s[x] == '\t' || s[x] == '\n' || s[x] == '\r' ||
	s[x] == 0 || s[x] == ';' ) {
      prev = s[x];
      s[x] = 0;
      break;
    }
    ++x;
  }

  /* The string was empty */
  if( x == y ) {
    free(created);
    return 0;
  }

  created->val.string = &s[y];
  
  if( s[y] == '(' ) {
    /* this starts a function */
    created->type = FUNCTION;
    return created;
  }

  if( s[y] >= 'a' && s[y] <= 'z' ) {
    created->type = VARIABLE;
    return created;
  }

  if( (s[y] >= '0' && s[y] <= '9') ||
      (s[y] == '-') || (s[y] == '+') ) {
    created->type = CONSTANT;
    return created;
  }
  return created;
}
  

/* Will return a uniq ID number each time it's called */
int getID() {
  static int ID = 0;
  ID++;
  return ID;
}

int iptr(int delta) {
  static int instructionPointer = 0;
  int temp;
  
  /* Return value before modification */
  temp = instructionPointer;
  instructionPointer += delta;
    
  if( instructionPointer < 0 ) {
    emessg("Memory underun",1);
  }
  if( instructionPointer >= MEMSIZE ) {
    emessg("Memory overrun",1);
  }
  
  return temp;
}
