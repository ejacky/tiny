%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
	typedef enum 
	/* book-keeping tokens */
	{ENDFILE,ERROR,
	/* reserved words */
	ELSE, IF, INT, RETURN, VOID, WHILE,
    /* multicharacter tokens */
    ID,NUM,
    /* special symbols */
	PLUS, MINUS, TIMES, OVER, LT, LEQ, GT, GEQ, EQ, NEQ, 
	ASSIGN, SEMI, COMMA, LPAREN, RPAREN, LBRACE, RBRACE, LBRACKET, RBRACKET,
	LCOMMENT, RCOMMENT} TokenType;
	
	TokenType getToken(void);
	void printToken(TokenType tokenType, char * tokenString);
	int lineno = 1;
	FILE * source;
	FILE * listing;
%}

digit       [0-9]
number      {digit}+
letter      [a-zA-Z]
identifier  {letter}+
newline     \n
whitespace  [ \t]+

%%

"else"			{return ELSE;}
"if"			{return IF;}
"int"			{return INT;}
"return"		{return RETURN;}
"void"			{return VOID;}
"while"			{return WHILE;}
"+"				{return PLUS;}
"-"				{return MINUS;}
"*"				{return TIMES;}
"/"				{return OVER;}
"<"				{return LT;}
"<="			{return LEQ;}
">"				{return GT;}
">="			{return GEQ;}
"=="			{return EQ;}
"!="			{return NEQ;}
"="				{return ASSIGN;}
";"				{return SEMI;}
","				{return COMMA;}
"("				{return LPAREN;}
")"				{return RPAREN;}
"["				{return LBRACKET;}
"]"				{return RBRACKET;}
"{"				{return LBRACE;}
"}"				{return RBRACE;}
"/*"			{ char c[3] = {0,0,0};
				  c[0] = input();
				  if(c[0] == EOF) return ERROR;
				  else if(c[0] == '\n') lineno++;
				  c[1] = input();
				  while(strcmp(c, "*/"))
				  {
					  if(c[1] == EOF) return ERROR;
					  else if(c[1] == '\n') lineno++;
					  c[0] = c[1];
					  c[1] = input();
				  }
				}
"*/"			{return ERROR;}
{number}		{return NUM;}
{identifier}	{return ID;}
{newline}		{lineno++;}
{whitespace}	{/*do nothing*/}
%%

int main(int argc, char * argv[])
{

	char pgm[12]; /* source code file name */
	if (argc != 2)
    {	fprintf(stderr,"usage: %s <filename>\n",argv[0]);
    	exit(1);
    }
	strcpy(pgm,argv[1]) ;
	if (strchr (pgm, '.') == NULL)
		strcat(pgm,".tny");
	source = fopen(pgm,"r");
	if (source==NULL)
	{ 	fprintf(stderr,"File %s not found\n",pgm);
		exit(1);
	}
	listing = stdout; /* send listing to screen */
	yyin = source;
	yyout = listing;
	fprintf(listing, "line number\ttoken\t\tlexeme\n");
	fprintf(listing, "-----------------------------------------------------------\n");
	
	while ( getToken() != ENDFILE);

	fclose(source);
	return 0;
}

TokenType getToken(void)
{
	char token[10];
	TokenType currentToken;
	currentToken = yylex();
	switch(currentToken){
		case ELSE:
			strcpy(token, "ELSE");
			break;
		case IF:
			strcpy(token, "IF");
			break;
		case INT:
			strcpy(token, "INT");
			break;
		case RETURN:
			strcpy(token, "RETURN");
			break;
		case VOID:
			strcpy(token, "VOID");
			break;
		case WHILE:
			strcpy(token, "WHILE");
			break;
		case PLUS:
			strcpy(token, "+");
			break;
		case MINUS:
			strcpy(token, "-");
			break;
		case TIMES:
			strcpy(token, "*");
			break;
		case OVER:
			strcpy(token, "/");
			break;
		case LT:
			strcpy(token, "<");
			break;
		case LEQ:
			strcpy(token, "<=");
			break;
		case GT:
			strcpy(token, ">");
			break;
		case GEQ:
			strcpy(token, ">=");
			break;
		case EQ:
			strcpy(token, "==");
			break;
		case NEQ:
			strcpy(token, "!=");
			break;
		case ASSIGN:
			strcpy(token, "=");
			break;
		case SEMI:
			strcpy(token, ";");
			break;
		case COMMA:
			strcpy(token, ",");
			break;
		case LPAREN:
			strcpy(token, "(");
			break;
		case RPAREN:
			strcpy(token, ")");
			break;
		case LBRACKET:
			strcpy(token, "[");
			break;
		case RBRACKET:
			strcpy(token, "]");
			break;
		case LBRACE:
			strcpy(token, "{");
			break;
		case RBRACE:
			strcpy(token, "}");
			break;
		case NUM:
			strcpy(token, "NUM");
			break;
		case ID:
			strcpy(token, "ID");
			break;
		case ENDFILE:
			strcpy(token, "EOF");
			break;
		case ERROR:
			fprintf(listing, "%d\t\tERROR\t\tComment Error\n", lineno);
			return currentToken;
	}
	fprintf(listing, "%d\t\t%s\t\t%s\n",lineno, token, yytext);
	
	return currentToken;
}
