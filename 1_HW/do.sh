#! /bin/sh
flex hw1.l
gcc lex.yy.c
./a.out test.c
