
calc: calc.y calc.lex
	yacc -d calc.y && lex calc.lex && gcc -o calc y.tab.c lex.yy.c -ll -ly -lm
