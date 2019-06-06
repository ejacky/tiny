#
#Makefile for C - Minus
#Gnu C Version
#K.Louden 2 / 3 / 98

CC = gcc

CFLAGS = -g

OBJS = hw3.tab.o lex.yy.o main.o util.o analyze.o symtab.o code.o cgen.o

project4_30: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o project4_30

main.o: main.c globals.h util.h scan.h parse.h analyze.h code.h cgen.h
	$(CC) $(CFLAGS) -c main.c

analyze.o: analyze.c analyze.h globals.h symtab.h
	$(CC) $(CFLAGS) -c analyze.c
symtab.o: symtab.c symtab.h globals.h
	$(CC) $(CFLAGS) -c symtab.c
util.o: util.c util.h globals.h
	$(CC) $(CFLAGS) -c util.c
parse.o: parse.c parse.h scan.h globals.h util.h
	$(CC) $(CFLAGS) -c parse.c
code.o: code.c globals.h code.h
	$(CC) $(CFLAGS) -c code.c
cgen.o: cgen.c globals.h cgen.h code.h symtab.h 
	$(CC) $(CFLAGS) -c cgen.c

lex.yy.o: hw3.l scan.h util.h globals.h
	flex -o lex.yy.c hw3.l
	$(CC) $(CFLAGS) -c lex.yy.c

hw3.tab.o: hw3.y globals.h 
	bison -d hw3.y 
	$(CC) $(CFLAGS) -c hw3.tab.c

.PHONY: clean

clean:
	rm -f $(OBJS) lex.yy.c hw3.tab.c hw3.tab.h project4_30
