%{

#include <stdio.h>

int lineno=0;
FILE * source;
FILE * listing;

#define 

%}


digit       [0-9]
number      {digit}+
letter      [a-zA-Z]
identifier  {letter}+
newline     \n
whitespace  [ \t]+


%%
"/*"             { 
int c;
for(;;){
while( (c = input()) != '*' && c !=EOF)
;
  if (c == '*'){
    while(  (c = input()) == '*')
      ;
    if (c == '/')
     break;  /* found end*/
  }
  if(c == EOF){
  error("EOF in comment");
  break;
  }
}
 }
"if"            {printf("%5d      if %s\n",lineno,yytext);}
"then"          {printf("%5d      then\n",lineno,yytext);}
"else"          {printf("%5d      else\n",lineno,yytext);}
"end"           {printf("%5d      end\n",lineno,yytext);}
"repeat"        {printf("%5d      repeat\n",lineno,yytext);}
"until"         {printf("%5d      until\n",lineno,yytext);}
"read"          {printf("%5d      read\n",lineno,yytext);}
"write"         {printf("%5d      write\n",lineno,yytext);}
"["             {printf("%5d      [\n",lineno,yytext);}
"]"             {printf("%5d      ]\n",lineno,yytext);}
":="            {printf("%5d      :=\n",lineno,yytext);}
"="             {printf("%5d      =\n",lineno,yytext);}
"<"             {printf("%5d      <\n",lineno,yytext);}
"+"             {printf("%5d      +\n",lineno,yytext);}
"-"             {printf("%5d      -\n",lineno,yytext);}
"*"             {printf("%5d      *\n",lineno,yytext);}
"("             {printf("%5d      (\n",lineno,yytext);}
")"             {printf("%5d      )\n",lineno,yytext);}
";"             {printf("%5d      ;\n",lineno,yytext);}
{number}        {printf("%5d      NUM %s\n",lineno,yytext); }
{identifier}    {printf("%5d      ID  %s\n",lineno,yytext);}
{newline}       {lineno++;}
{whitespace}    {/* skip whitespace */}
"{"             { char c;
                  do
                  { c = input();
                    if (c == EOF) break;
                    if (c == '\n') lineno++;
                  } while (c != '}');
                }
.               {printf("ERROR\n");}


%%


main(int argc, char*argv[])
{

 char pgm[20]; /* source code file name */
  if (argc != 2)
    { fprintf(stderr,"usage: %s <filename>\n",argv[0]);
      exit(1);
    }
  strcpy(pgm,argv[1]) ;
  if (strchr (pgm, '.') == NULL)
     strcat(pgm,".tny");
  source = fopen(pgm,"r");
  if (source==NULL)
  { fprintf(stderr,"File %s not found\n",pgm);
    exit(1);
  }
  listing = stdout; /* send listing to screen */
  fprintf(listing,"\nTINY COMPILATION: %s\n",pgm);
  fprintf(listing,"\n  line number    token     lexeme\n",pgm);
  fprintf(listing,"-------------------------------------\n",pgm);

  
  yyin = source;
//	yyout = listing;
	
  yylex();
 fclose(source); //책에는 없다.
 return 0;
}

yywrap(){
  printf("EOF\n");
}


