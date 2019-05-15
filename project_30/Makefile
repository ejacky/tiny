#
# Makefile for C-Minus
# Gnu C Version
# K. Louden 2/3/98

CC = gcc

CFLAGS = 

OBJS = hw2.tab.o lex.yy.o main.o util.o 

20130523: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o 20130523

main.o: main.c globals.h util.h scan.h parse.h
	$(CC) $(CFLAGS) -c main.c

util.o: util.c util.h globals.h
	$(CC) $(CFLAGS) -c util.c

parse.o: parse.c parse.h scan.h globals.h util.h
	$(CC) $(CFLAGS) -c parse.c

lex.yy.o: hw2.l scan.h util.h globals.h
	flex -o lex.yy.c hw2.l
	$(CC) $(CFLAGS) -c lex.yy.c

hw2.tab.o: hw2.y globals.h
	bison -d hw2.y 
	$(CC) $(CFLAGS) -c hw2.tab.c

clean:
	-rm hw2.tab.c
	-rm hw2.tab.h
	-rm lex.yy.c
	-rm $(OBJS)

all: 20130523 clean
