#
# makefile for TINY
# Borland C Version
# K. Louden 2/3/98
#
# modified by Dohyun Kim /02/37/19
# target : Linux, flex 2.6.0
#

CC = gcc
COPT += -I./inc
CFLAGS = -Wall -g $(COPT)
LEX = flex
IDENT = 20141390

OBJS = obj/main.o obj/util.o obj/lex.yy.o
LEXGEN = src/lex.yy.c
RESULT = $(OBJS) $(LEXGEN) $(IDENT)

$(IDENT): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(IDENT)

obj/main.o: src/main.c inc/globals.h inc/util.h inc/scan.h
	$(CC) $(CFLAGS) -c src/main.c -o obj/main.o

obj/util.o: src/util.c inc/util.h inc/globals.h
	$(CC) $(CFLAGS) -c src/util.c -o obj/util.o

obj/lex.yy.o: src/lex.yy.c inc/util.h inc/globals.h inc/scan.h
	$(CC) $(CFLAGS) -c src/lex.yy.c -o obj/lex.yy.o

src/lex.yy.c: lex/tiny.l
	$(LEX) -o src/lex.yy.c lex/tiny.l

.PHONY: clean

clean:
	rm -f $(RESULT)

all: $(IDENT)
