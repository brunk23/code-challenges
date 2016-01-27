%{
  #include <stdio.h>
  double vbltable[26];
%}

%union {
  double dval;
  int vblno;
}

%token <vblno> NAME
%token <dval> NUMBER
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%type <dval> expression

%%

statementList: statement '\n'
     | statementList statement '\n'
     ;

statement: NAME '=' expression { vbltable[$1] = $3; }
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
     | NAME { $$ = vbltable[$1]; }
     ;

%%
int main(void) {
  return yyparse();
}

