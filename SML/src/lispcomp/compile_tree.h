#ifndef COMPILE_TREE_H
#define COMPILE_TREE_H

int compileTree(struct Cons *, int []);
struct Cons *inSymTree(struct Cons *, struct Cons *);
struct Cons *carType(struct Cons *, struct Cons **);
int comp_plus(struct Cons *, struct Cons *,int []);
int comp_list(struct Cons *, struct Cons *, int []);
int comp_progn(struct Cons *, struct Cons *, int []);

#endif
