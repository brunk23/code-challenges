#ifndef COMPILE_FUNCTION_H
#define COMPILE_FUNCTION_H

struct Cons *process_symbol(struct Cons *, struct Cons *curr);
int resolve_symbols(struct Cons *, struct Cons *,int []);
struct Cons *inSymTree(struct Cons *, struct Cons *);
struct Cons *cType(struct Cons *, struct Cons **);
int assign_symbols(struct Cons *, int []);

#endif
