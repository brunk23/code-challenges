%{
  #include <stdio.h>
  #include <string.h>
  #include "calc.h"
%}

%union {
  double dval;
  struct symtab *symp;
}

%token <symp> NAME
%token <dval> NUMBER
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%type <dval> expression

%%

statementList: statement '\n'
     | statementList statement '\n'
     ;

statement: NAME '=' expression { $1->value = $3; }
     | expression      { printf("= %g\n", $1); }
     ;

expression:  expression '+' expression { $$ = $1 + $3; }
     | expression '-' expression { $$ = $1 - $3; }
     | expression '*' expression { $$ = $1 * $3; }
     | expression '/' expression
     {
       if( $3 == 0.0 )
         yyerror("divide by zero");
       else
         $$ = $1 / $3;
     }
     | '-' expression %prec UMINUS { $$ = -$2; }
     | '(' expression ')' { $$ = $2; }
     | NUMBER { $$ = $1; }
     | NAME { $$ = $1->value; }
     ;

%%

struct symtab *symlook(char *s) {
  char *p;
  struct symtab *sp;

  for( sp = symtab; sp < &symtab[NSYMS]; sp++ ) {
    /* is it already here? */
    if( sp->name && !strcmp(sp->name, s)) {
      return sp;
    }

    /* is it free */
    if( !sp->name ) {
      sp->name = strdup(s);
      return sp;
    }
    /* otherwise continue to next */
  }

  yyerror("too many symbols");
  exit(1);   /* cannot continue */
}

int main(void) {
  return yyparse();
}

