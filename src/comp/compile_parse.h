#ifndef COMPILE_PARSE_H
#define COMPILE_PARSE_H

char *parseLet(struct Token symbolTable[MAXSYMS],
	       struct Token labels[MEMSIZE], int core[MEMSIZE]);
int gencode(char oper, struct Token vals[], int vbase,
	      struct Token syms[MAXSYMS], int code[MEMSIZE],
	    struct Token labels[MEMSIZE], int *);

#endif
