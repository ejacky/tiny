%{

#include <stdio.h>
int lineno = 1;
%}
line .*\n
%%
{line} {printf("%5d %s",lineno++,yytext);}
%%

main()
{
  yylex(); return 0;
}

yywrap(){
  printf("EOF\n");
}
