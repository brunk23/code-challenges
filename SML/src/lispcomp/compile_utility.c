#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "compiler.h"

struct Cons *push(struct Cons *new, struct Cons *old) {
  struct Cons *head;
  if(new) {
    head = malloc( sizeof(struct Cons) );
    if( head ) {
      head->car = new;
      head->cdr = old;
      head->type = LIST;
      head->string = 0;
      head->resolved = T;
      head->ID=getID();
    } else {
      emessg("Push failed",1);
    }
    return head;
  }
  return old;
}

/* Here we need to pass the address of the stack pointer
 * because we need to return what we pop, while keeping
 * the stack pointer pointing to the current value */
struct Cons *pop(struct Cons **stack) {
  struct Cons *car;
  struct Cons *old;
  old = *stack;
  if( old ) {
    car = old->car;
    *stack = old->cdr;
    free(old);
    return car;
  }
  return 0;
}

struct Cons *copy(struct Cons *old) {
  struct Cons *cpy;

  if( !(cpy = malloc( sizeof( struct Cons ) ) ) ) {
    emessg("Couldn't get copy",1);
  }
  cpy->car = 0;
  cpy->cdr = 0;
  cpy->string = 0;
  cpy->type = old->type;
  if(old->type == CONSTANT) {
    cpy->value = old->value;
  } else {
    if( !(cpy->string = malloc( strlen( old->string ) + 1))) {
      emessg("Could not make new string",1);
    }
    strncpy(cpy->string,old->string,strlen(old->string)+1);
  }
  cpy->ID=old->ID;
  cpy->args=old->args;
  cpy->location= -1;
  cpy->resolved = NIL;

  return cpy;
}     

struct Cons *car(struct Cons *list) {
  if(list) {
    if(list->type == LIST) {
      return list->car;
    }
  }
  return 0;
}

struct Cons *cdr(struct Cons *list) {
  if(list) {
    if(list->type == LIST) {
      return list->cdr;
    }
  }
  return 0;
}

/* This will save an item at the end of the current list */
struct Cons *append(struct Cons *list, struct Cons *add) {
  struct Cons *spot;
  spot = list;
  if(spot) {
    if(spot->type == LIST) {
      while( spot->cdr ) {
	spot = spot->cdr;
      }
      spot->cdr = malloc( sizeof( struct Cons ) );
      if( !spot->cdr ) {
	emessg("Failed to allocate for append",1);
      }
      spot = spot->cdr;
      spot->car = add;		/* put the new item in car */
      spot->cdr = 0;		/* this is the new end of the list */
      spot->type = LIST;
      spot->string = 0;
      spot->location = 0;
      spot->ID = getID();
      spot->resolved = T;
    }
  }
  return list;
}

/* Return the length of a list */
int length(struct Cons *list) {
  struct Cons *spot;
  int x = 1;
  spot = list;
  if( spot ) {
    while( spot->cdr ) {
      ++x;
      spot = spot->cdr;
    }
    return x;
  }
  return 0;
}

struct Cons *nth(struct Cons *list, int n) {
  struct Cons *spot;
  int x = 1;
  spot = list;
  if( spot ) {
    while( x < n ) {
      ++x;
      spot = spot->cdr;
      if( !spot ) {
	emessg("nth does not exist",1);
      }
    }
  }
  return spot->car;
}

/*
 * This is currently not working with '(' and ')' correctly
 */
struct Cons *getNextNode(char *string) {
  static char *s;
  static int x;
  static char prev;

  struct Cons *created;
  
  int y;
  
  if(string) {
    if(s) {
      free(s);
    }
    s = malloc(strlen(string) + 1);
    strncpy(s,string,strlen(string)+1);
    x = 0;
    prev = s[0];
  }

  s[x] = prev;
  
  /* Ignore everything after a comment */
  if( prev == ';' || s[x] == ';' ) {
    return 0;
  }
  
  created = malloc( sizeof( struct Cons ) );
  if( !created ) {
    emessg("Failure to create node",1);
  }

  created->car = 0;
  created->cdr = 0;
  created->location = 0;
  created->string = 0;
  created->resolved = T;
  created->ID=getID();

  if( prev == ')' ) {
    /* we need to return a token to represent it */
    created->type = EOL;
    prev = s[++x];
    return created;
  }

  if( prev == '(' ) {
    created->type = LIST;
    prev = s[++x];
    return created;
  }
  
  while( s[x] != 0 ) {
    if( s[x] == ' ' || s[x] == '\t' ||
	s[x] == '\n' || s[x] == '\r' ||
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
  
  if( prev  == '(' ) {
    /* this starts a list */
    created->type = LIST;
    prev = s[++x];
    return created;
  }

  if( x == y && prev  == ')' ) {
    /* this ends a list */
    created->type = EOL;
    prev = s[++x];
    return created;
  }

  /* The string was empty */
  if( x == y ) {
    free(created);
    return 0;
  }
  
  if( !(s[y] >='0' && s[y] <= '9') ||
      ((s[y] == '+' || s[y] =='-') &&
       !((s[y+1] >= '0') && (s[y+1] <= '9')))) {
    created->type = SYMBOL;
    created->string = malloc( strlen(&s[y]) + 1 );
    if( created->string ) {
      strncpy(created->string, &s[y], strlen(&s[y]) +1 );
    } else {
      emessg("String not created",1);
    }
    return created;
  }
  
  if( (s[y] >= '0' && s[y] <= '9') ||
      (s[y] == '-') || (s[y] == '+') ) {
    created->type = CONSTANT;
    created->value = strtol(&s[y],0,10);
    return created;
  }
  return created;
}
  

/* Will return a uniq ID number each time it's called */
int getID() {
  static int ID = EOL;
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
