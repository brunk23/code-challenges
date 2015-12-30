#ifndef COMPILE_TREE_H
#define COMPILE_TREE_H

int assign_symbols(struct Cons *, int []);
int compileTree(struct Cons *, int []);
int resolve_symbols(struct Cons *, struct Cons *,int []);
struct Cons *inSymTree(struct Cons *, struct Cons *);
struct Cons *cType(struct Cons *, struct Cons **);
int comp_plus(struct Cons *, struct Cons **,int []);
int comp_list(struct Cons *, struct Cons **, int []);
int comp_progn(struct Cons *, struct Cons **, int []);
int comp_print(struct Cons *, struct Cons **, int []);

#endif
