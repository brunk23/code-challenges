#ifndef COMPILER_H
#define COMPILER_H

#include "../shared/sml_shared.h"

#define MAXSYMS 1000
#define SSIZE 25

struct tableEntry {
  int symbol;
  char type;			// 'C', 'L', 'V'
  int location;			// 00 to 99
};

int help_menu(char *);
int process_source(const char *, int[]);
int insert_symbol(int, char, struct tableEntry[], int);
int emessg(int, char *);
int output_core(char *, int[]);
int decode_line(char *,int[],struct tableEntry [],struct tableEntry[]);
int gencode(char oper, struct tableEntry vals[], int vbase,
	      struct tableEntry syms[MAXSYMS], int code[MEMSIZE],
	    struct tableEntry labels[MEMSIZE], int *);
int oplev(char);

#endif
