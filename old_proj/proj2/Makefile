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
YACC = bison
IDENT = 20141390

OBJS = obj/main.o obj/util.o obj/lex.yy.o obj/tiny.tab.o
LEXGEN = src/lex.yy.c

YACCSRC = src/tiny.tab.c
YACCINC = inc/tiny.tab.h
YACCLOG = log/bison.log
YACCOPT = --output=$(YACCSRC) --defines=$(YACCINC) -v --report-file=$(YACCLOG)
YACCGEN = $(YACCSRC) $(YACCINC) $(YACCLOG)
RESULT = $(OBJS) $(LEXGEN) $(IDENT) $(YACCGEN)


$(IDENT): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(IDENT)

obj/main.o: src/main.c inc/globals.h inc/util.h inc/scan.h inc/tiny.tab.h
	$(CC) $(CFLAGS) -c src/main.c -o obj/main.o

obj/util.o: src/util.c inc/util.h inc/globals.h
	$(CC) $(CFLAGS) -c src/util.c -o obj/util.o

obj/lex.yy.o: src/lex.yy.c inc/util.h inc/globals.h inc/scan.h
	$(CC) $(CFLAGS) -c src/lex.yy.c -o obj/lex.yy.o

src/lex.yy.c: lex/tiny.l
	$(LEX) -o src/lex.yy.c lex/tiny.l

obj/tiny.o: src/tiny.c inc/tiny.h
	$(CC) $(CFLAGS) -c src/tiny.c -o obj/tiny.o

src/tiny.tab.c inc/tiny.tab.h: yacc/tiny.y
	$(YACC) $(YACCOPT) yacc/tiny.y

obj/tiny.tab.o: src/tiny.tab.c inc/tiny.tab.h inc/globals.h inc/scan.h inc/parse.h inc/util.h
	$(CC) $(CFLAGS) -c src/tiny.tab.c -o obj/tiny.tab.o

.PHONY: clean

clean:
	rm -f $(RESULT)

all: $(IDENT)
