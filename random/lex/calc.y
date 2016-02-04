%{
  #include <stdio.h>
  #include <math.h>
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
%left '*' '/' '%'
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
     | expression '%' expression
     {
       if( $3 == 0.0 )
	 yyerror("modulus of zero");
       else
	 $$ = (int)$1 % (int)$3;
     }
     | '-' expression %prec UMINUS { $$ = -$2; }
     | '(' expression ')' { $$ = $2; }
     | NUMBER { $$ = $1; }
     | NAME { $$ = $1->value; }
     | NAME '(' expression ')' {
         if( $1->funcptr ) {
	   $$ = ($1->funcptr)($3);
         } else {
	   printf("%s not a function\n",$1->name);
	   $$ = 0.0;
         }
       }
     ;

%%

int addfunc(char *name, double (*func)() ) {
  struct symtab *sp = symlook(name);
  sp->funcptr = func;
  return 0;
}

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
  extern double sqrt(double), exp(double), log(double),
    sin(double), cos(double), tan(double);

  addfunc("sqrt", sqrt);
  addfunc("exp", exp);
  addfunc("log", log);
  addfunc("sin", sin);
  addfunc("cos", cos);
  addfunc("tan", tan);
  yyparse();

  return 0;
}

