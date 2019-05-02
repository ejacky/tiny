%{

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

//switch print
#define _S_P(_x_) printf("%5d           %-8s       %s\n ",lineno,_x_,yytext);break;

#define MAXTOKENLEN 10

typedef enum 
    /* book-keeping tokens */
   {ENDFILE,ERROR,
    /* reserved words */
    IF,THEN,ELSE,WHILE,FOR,SWITCH,CASE,RETURN,
    SHORT,INT,LONG,FLOAT,DOUBLE,CHAR,
    /* multicharacter tokens */
    ID,NUM,
    /* special symbols */
    ASSIGN,EQ,LT,RT,LET,RET,PLUS,MINUS,TIMES,OVER,
    LPAREN,RPAREN, LCB,RCB,LSQ,RSQ,
    COMMA,DOT,SEMI

   } TokenType;


int lineno = 0;
FILE * source;
FILE * listing;


char tokenString[MAXTOKENLEN+1];
TokenType getToken();


//""          {return ;}
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
	{if(c =='\n')lineno++;}
	//;

  if(c =='\n')lineno++;
  if (c == '*'){
    while(  (c = input()) == '*')
	{if(c=='\n')lineno++;}    
	 // ;
    if(c =='\n')lineno++;
    if (c == '/')
     break;  /* found end*/
  }
  if(c == EOF){
printf("%5d           %-8s       %s\n ",lineno,"ERROR","Comment Error");break;
  break;
  }
}
 }

"if"            {return IF;}
"then"          {return THEN;}
"else"          {return ELSE;}
"while"          {return WHILE;}
"for"          {return FOR;}
"switch"          {return SWITCH;}
"return"          {return RETURN;}

"short"          {return SHORT;}
"int"          {return INT;}
"long"          {return LONG;}
"float"          {return FLOAT;}
"double"          {return DOUBLE ;}
"char"          {return CHAR;}
"=="            {return ASSIGN;}
"="             {return EQ;}
"<="             {return LET;}
">="             {return RET;}
"<"             {return LT;}
">"             {return RT;}
"+"             {return PLUS;}
"-"             {return MINUS;}
"*"             {return TIMES;}
"/"             {return OVER;}

";"             {return SEMI;}
"."             {return DOT;}
","             {return COMMA;}

"("             {return LPAREN;}
")"             {return RPAREN;}
"["             {return LSQ;}
"]"             {return RSQ;}
"{"             {return LCB;}
"}"             {return RCB;}
{number}        {return NUM;}
{identifier}    {return ID;}
{newline}       {lineno++;}
{whitespace}    {/* skip whitespace */}

"<<EOF>>"       {return ENDFILE;}

.               {return ERROR;}


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
//  fprintf(listing,"\nTINY COMPILATION: %s\n",pgm);
  fprintf(listing,"\n  line number    token         lexeme\n",pgm);
  fprintf(listing,"-------------------------------------\n ",pgm);

  
//  yyin = source;
//	yyout = listing;
  while (getToken()!=ENDFILE);
  //yylex();
 fclose(source);
 return 0;
}

yywrap(){
//  printf("EOF\n");
//printf("%5d           %-8s       %s\n ",lineno,"EOF","");
}


TokenType getToken(void)
{
  static int firstTime = TRUE;
  TokenType currentToken;
  if (firstTime)
  { firstTime = FALSE;
    lineno++;
    yyin = source;
    yyout = listing;
  }
  currentToken = yylex();
  strncpy(tokenString,yytext,MAXTOKENLEN);
  //if (TraceScan) {
  //  fprintf(listing,"\t%d: ",lineno);
  //  printToken(currentToken,tokenString);
 // }
//  printf("currentToken %d\n",currentToken);
  switch(currentToken){
    /* reserved words */
     case IF: _S_P("IF")
     case ELSE: _S_P("ELSE")
     case WHILE: _S_P("WHILE")
     case FOR: _S_P("FOR")
     case SWITCH: _S_P("SWITCH")
     case RETURN: _S_P("RETURN")

     case SHORT: _S_P("SHORT")
     case INT: _S_P("INT")
     case LONG: _S_P("LONG")
     case FLOAT: _S_P("FLOAT")
     case DOUBLE: _S_P("DOUBLE")
     case CHAR: _S_P("CHAR")

    /* multicharacter tokens */
     case NUM: _S_P("NUM")
     case ID: _S_P("ID")

    /* special symbols */
     case LPAREN : _S_P("(")
     case RPAREN : _S_P(")")
     case LSQ: _S_P("[")
     case RSQ: _S_P("]")
     case LCB: _S_P("{")
     case RCB: _S_P("}")

     case LT : _S_P("<")
     case RT : _S_P(">=")
     case LET : _S_P("<=")
     case RET : _S_P(">=")

     case SEMI : _S_P(";")
     case TIMES : _S_P("*")
     case PLUS: _S_P("+")
     case MINUS: _S_P("-")
     case OVER: _S_P("/")
     case EQ: _S_P("=")
     case ASSIGN: _S_P("==")
     case COMMA: _S_P(",")
     case DOT: _S_P(".")
    // case : _S_P("")

    case ENDFILE : _S_P("EOF")
     
  }
  return currentToken;
}
