#LEX = lex
#YACC = yacc -d

CC = gcc

calc: calc.y calc.lex
	$(YACC) calc.y && $(LEX) calc.lex && $(CC) -o calc y.tab.c lex.yy.c -ll -ly -lm
