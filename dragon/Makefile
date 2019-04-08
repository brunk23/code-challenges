OPTS = -g -Wall
OBJS = lexer.o parser.o emitter.o symbol.o
OBJS += init.o error.o main.o

dragon: $(OBJS)
	gcc -o dragon $(OPTS) $(OBJS)

lexer.o: lexer.c global.h
	gcc -c $(OPTS) lexer.c

parser.o: parser.c global.h
	gcc -c $(OPTS) parser.c

emitter.o: emitter.c global.h
	gcc -c $(OPTS) emitter.c

symbol.o: symbol.c global.h
	gcc -c $(OPTS) symbol.c

init.o: init.c global.h
	gcc -c $(OPTS) init.c

error.o: error.c global.h
	gcc -c $(OPTS) error.c

main.o: parser.c global.h
	gcc -c $(OPTS) main.c

clean:
	rm $(OBJS)
