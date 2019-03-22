#미리 지정된 매크로 'CC' : .c 파일의 컴파일러 
CC=gcc
#OBJ 매크로 지정
OBJS = main.o util.c lex.yy.c parse.c scan.c cgen.c analyze.c systab.c


#매크로 호출은 $(매크로명)
#
#$@ 현재 타겟
#$^ 현재 타겟의 종속항목
one : $(OBJS)
	$(CC) -o $@ $^ 
#각 OBJS 에 대해 .o 파일을 만드는  명령은 없지만
#make 에 그정도의 기능은 내장되어있다


clean : 
	rm *.o
