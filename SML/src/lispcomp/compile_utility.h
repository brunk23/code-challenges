#ifndef COMPILE_UTILITY_H
#define COMPILE_UTILITY_H

int printList(struct Cons *);
struct Cons *pop(struct Cons **);
struct Cons *push(struct Cons *, struct Cons *);
struct Cons *car(struct Cons *);
struct Cons *cdr(struct Cons *);
struct Cons *append(struct Cons *, struct Cons *);
int length(struct Cons *);
struct Cons *getNextNode(char *);
int getID();
int iptr();

#endif
