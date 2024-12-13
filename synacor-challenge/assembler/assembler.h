#ifndef SYNACOR_H
#define SYNACOR_H

enum CONSTANTS {
  FAIL = -1, SUCCESS = 0, BUFFSIZE = 160, REGOFFSET = 32768, USERWORD = 32776,
  RESOLVED, UNRESOLVED, BAD, GOOD, DIRECTIVE, LABEL, WORD, NUMBER, STRING,
  MATH, ORIGIN, DATA, INCLUDE, ASSIGN
};

enum REGISTERS {
  r0 = 32768, r1, r2, r3, r4, r5, r6, r7
};

enum INSTSET {
  halt = 0, set, push, pop, eq, gt, jmp, jt, jf, add, mult,
  mod, and, or, not, rmem, wmem, call, ret, out, in, nop,
  rndm, dread, dwrite
};

typedef unsigned short int SWORD;
typedef struct TOKEN TOKEN;
typedef struct LINE LINE;
typedef struct SYMBOL SYMBOL;

struct TOKEN {
  SWORD value;
  SWORD location;
  int line;
  int type;
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
  SWORD resolved;
  SWORD value;
  int count;
  char *str;
  SYMBOL *next;
};

/*
 * GLOBAL VARIABLES
 * 15 bit addressable, 16 bit values. Values limited from
 * 0-32768, 8 registers, an unbounded stack.
 * Variables to track malloc'd structures to check for leaks
 * And our global structure pointers
 */
SWORD memory[32768];
SWORD pc;
SYMBOL *syms;
TOKEN *tokens;
LINE *filelines;
/* These should be encapsulated in a struct with command line stuff */
int linecount;
int symbolcount;
int tokencount;
int instruction_count;
int data_words;
int arguments_count;

/*
 * Function prototypes
 */
int help_menu( const char * );
int init_machine();
int process_output( const char *, int );
void print_token( TOKEN * );

TOKEN *process_input( const char * );
TOKEN *get_empty_token();
TOKEN *token( char *, int );
int pass1();
int pass2();

/* Functions that check for valid tokens and syntax */
int verify_next_token( TOKEN * );
void error_missing_word( TOKEN * );
void error_end_of_line( TOKEN * );

int compile_token( TOKEN * );
SWORD isregister( char * );
SWORD reserved( char * );
SWORD token_value( TOKEN * );
SYMBOL *find_symbol( char * );
void add_symbol( char *, int, int );
TOKEN *origin_handler( TOKEN *, int * );
TOKEN *data_handler( TOKEN *, int * );
TOKEN *one_ops_handler( TOKEN *, int * );
TOKEN *two_ops_handler( TOKEN *, int * );
TOKEN *three_ops_handler( TOKEN *, int * );
TOKEN *include_handler( TOKEN *, int * );
TOKEN *assign_handler( TOKEN *, int * );

void delete_token_tree();
void delete_line_tree();
void delete_sym_tree();
void print_sym_tree(const char *);

#endif
