#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <ctype.h>

#define BSIZE 128		/* buffer size */
#define NONE -1
#define EOS '\0'

#define NUM 256
#define DIV 257
#define MOD 258
#define ID 259
#define DONE 260

int tokenval;			/* value of token attribute */
int lineno;			/* line number */

struct entry {			/* form of symbol table entry */
  char *lexptr;
  int token;
};

/* lexer.c */
int lexan();

/* parser.c */
void parse();
void expr();
void term();
void factor();
void match(int);

/* emitter.c */
void emit(int, int);

/* symbol.c */
#define STRMAX 999		/* size of lexemes array */
#define SYMMAX 100		/* size of symtable */

char lexemes[STRMAX];
int lastchar;		/* last used position in lexemes */
struct entry symtable[SYMMAX];
int lastentry;		/* last used position in symtable */

int lookup(char *);
int insert(char *,int);

/* init.c */
void init();

/* error.c */
void error(char *);

/* main.c */
int main();
#endif
