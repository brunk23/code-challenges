#ifndef COMPILE_TREE_H
#define COMPILE_TREE_H

int compileTree(struct Cons *, int []);
int comp_list(struct Cons *, struct Cons **, int []);
int comp_progn(struct Cons *, struct Cons **, int []);
int comp_print(struct Cons *, struct Cons **, int []);
int comp_setf(struct Cons *, struct Cons **, int []);

#endif
