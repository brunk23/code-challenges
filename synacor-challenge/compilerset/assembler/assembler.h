#ifndef SYNACOR_H
#define SYNACOR_H

#define BUFFSIZE 160
#define REGOFFSET 32768
#define FAIL -1
#define SUCCESS 0
#define USERWORD 32776
#define RESOLVED 32555
#define UNRESOLVED 39999
#define true 1
#define false 0

int linecount;
int symbolcount;
int tokencount;

/*
 * Synacor Machine Description
 */

typedef unsigned short int SWORD;
typedef struct TOKEN TOKEN;
typedef struct LINE LINE;
typedef struct SYMBOL SYMBOL;
/*
 * We are going to rewrite the code to be a much better assembler.
 * This is step 1.
 */
struct TOKEN {
  int line;
  int type;
  SWORD value;
  SWORD location;
  int length;
  char *word;
  const char *file_name;
  const char *source_line;
  TOKEN *next;
};

struct LINE {
  char *str;
  LINE *next;
};

struct SYMBOL {
  int count;
  SWORD resolved;
  SWORD value;
  char *str;
  SYMBOL *next;
};


/* 15 bit addressable, 16 bit values. Values limited from
 * 0-32768, 8 registers, an unbounded stack. These are globals
 * because I am both too lazy to pass them around, but it is
 * also a reasonable expectation that all parts of the chip can
 * access registers, memory, and the stack. pc is the program
 * counter
 */
SWORD memory[32768];
SWORD pc;
SYMBOL *syms;
TOKEN *tokens;
LINE *filelines;

enum REGISTERS {
  r0 = 32768, r1, r2, r3, r4, r5, r6, r7
};

enum INSTSET {
  halt = 0, set, push, pop, eq, gt, jmp, jt, jf, add, mult,
  mod, and, or, not, rmem, wmem, call, ret, out, in, nop,
  dread, dwrite, ORIGIN, DATA, INCLUDE
};

enum STATES {
  DIRECTIVE, LABEL, WORD, NUMBER, STRING
};

/*
 * Function prototypes
 */
int help_menu( const char * );
int init_machine();
TOKEN *process_input( const char * );
int process_output( const char * );
int process_data_line();
int pass1();
int pass2();
SWORD isregister(char *);
SWORD reserved(char *);
SWORD token_value(TOKEN *);
SYMBOL *find_symbol(char *);
TOKEN *token(char *, int);
TOKEN *origin_handler(TOKEN *, int *);
TOKEN *data_handler(TOKEN *, int *);
TOKEN *one_ops_handler(TOKEN *, int *);
TOKEN *two_ops_handler(TOKEN *, int *);
TOKEN *three_ops_handler(TOKEN *, int *);
TOKEN *include_handler(TOKEN *, int *);
void error_missing_word(TOKEN *);
void delete_token_tree();
void delete_line_tree();
void delete_sym_tree();
void add_symbol(char *, int, int);
void print_token(TOKEN *);

#endif
