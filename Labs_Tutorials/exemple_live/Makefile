count: count.o lexer.o
	gcc count.o lexer.o -o count -lfl

count.o: count.c count.h
	gcc -c count.c -o count.o

lexer.o: lexer.c
	gcc -c lexer.c -o lexer.o

lexer.c: lexer.l
	flex -o lexer.c lexer.l
