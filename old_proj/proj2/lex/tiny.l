/****************************************************/
/* File: tiny.l                                     */
/* Lex specification for TINY                       */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

%{
#include "globals.h"
#include "util.h"
#include "scan.h"

/* lexeme of identifier or reserved word */
char tokenString[MAXTOKENLEN+1];
%}

digit       [0-9]
number      {digit}+
letter      [a-zA-Z]
identifier  {letter}+
newline     (\n|\r|\n\r)
whitespace  [ \t]+

%x C_COMMENT
%option noyywrap
%option nounput
%option noinput
%%

"/*"                    {BEGIN(C_COMMENT);}
<C_COMMENT>{newline}    {lineno++;}
<C_COMMENT>.            {/*ignore comment*/}
<C_COMMENT>"*/"         {BEGIN(INITIAL); return COMMENT;}
<C_COMMENT><<EOF>>      {BEGIN(INITIAL); return COMMENT_ERROR;}

<<EOF>>                 {return ENDFILE;}
"else"                  {return ELSE;}
"if"                    {return IF;}
"int"                   {return INT;}
"return"                {return RETURN;}
"void"                  {return VOID;}
"while"                 {return WHILE;}
"+"                     {return PLUS;}
"-"                     {return MINUS;}
"*"                     {return TIMES;}
"/"                     {return OVER;}
"<"                     {return LESSTHEN;}
"<="                    {return LESSEQUAL;}
">"                     {return GREATTHEN;}
">="                    {return GREATEQUAL;}
"=="                    {return EQUAL;}
"!="                    {return NOTEQUAL;}
"="                     {return ASSIGN;}
";"                     {return SEMICOLON;}
","                     {return COMMA;}
"("                     {return LPAREN;}
")"                     {return RPAREN;}
"["                     {return LBRACKET;}
"]"                     {return RBRACKET;}
"{"                     {return LBRACE;}
"}"                     {return RBRACE;}
{number}                {return NUM;}
{identifier}            {return ID;}
{newline}               {lineno++;}
{whitespace}            {/* skip whitespace */}

.                       {return ERROR;}

%%

TokenType getToken(void)
{
    static int firstTime = TRUE;
    TokenType currentToken;
    if (firstTime)
    {
        firstTime = FALSE;
        lineno++;
        yyin = source;
        yyout = listing;
    }
    currentToken = yylex();
    strncpy(tokenString,yytext,MAXTOKENLEN);
    if (TraceScan)
    {
        // fprintf(listing,"\t%d: ",lineno);
        printToken(currentToken,tokenString);
    }
    return currentToken;
}

