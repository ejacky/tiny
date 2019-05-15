/****************************************************/
/* File: globals.h                                  */
/* Global types and vars for TINY compiler          */
/* must come before other include files             */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef YYPARSER
#include "tiny.tab.h"
#define ENDFILE 0
#endif //YYPARSER

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

/* MAXRESERVED = the number of reserved words */
#define MAXRESERVED 8

// typedef enum {
//     /* book-keeping tokens */
//     ENDFILE,ERROR,COMMENT,COMMENT_ERROR,
//     /* reserved words */
//     ELSE, IF, INT, RETURN, VOID, WHILE,
//     /* multicharacter tokens */
//     ID,NUM,
//     /* special symbols */
//     PLUS, MINUS, TIMES, OVER,
//     LESSTHEN, LESSEQUAL, GREATTHEN, GREATEQUAL, EQUAL, NOTEQUAL,
//     ASSIGN, SEMICOLON, COMMA,
//     LPAREN, RPAREN, LBRACKET, RBRACKET, LBRACE, RBRACE
// } TokenType;

typedef int TokenType;

extern FILE* source; /* source code text file */
extern FILE* listing; /* listing output text file */
extern FILE* code; /* code text file for TM simulator */

extern int lineno; /* source line number for listing */

/**************************************************/
/***********   Syntax tree for parsing ************/
/**************************************************/

typedef enum {StmtK, ExpK, DeclK, TypeK} NodeKind;
typedef enum {CompK, ParamK, ArgK, SelectK, IterK, RetK} StmtKind;
typedef enum {AssignK, OpK, ConstK, IdK, IdArrK, CallK} ExpKind;
typedef enum {FuncK, VarK, VarArrK} DeclKind;
typedef enum {TypeSpecK} TypeKind;

/* ExpType is used for type checking */
typedef enum {Void,Integer} ExpType;

#define MAXCHILDREN 4

typedef struct treeNode
{
    struct treeNode* child[MAXCHILDREN];
    struct treeNode* sibling;
    int lineno;
    NodeKind nodekind;
    union {
        StmtKind stmt;
        ExpKind exp;
        DeclKind decl;
        TypeKind type;
    } kind;
    union {
        TokenType op;
        TokenType typeSpec;
        int val;
        char* name;
    } attr;
    ExpType type; /* for type checking of exps */
} TreeNode;

/**************************************************/
/***********   Flags for tracing       ************/
/**************************************************/

/* EchoSource = TRUE causes the source program to
 * be echoed to the listing file with line numbers
 * during parsing
 */
extern int EchoSource;

/* TraceScan = TRUE causes token information to be
 * printed to the listing file as each token is
 * recognized by the scanner
 */
extern int TraceScan;

/* TraceParse = TRUE causes the syntax tree to be
 * printed to the listing file in linearized form
 * (using indents for children)
 */
extern int TraceParse;

/* TraceAnalyze = TRUE causes symbol table inserts
 * and lookups to be reported to the listing file
 */
extern int TraceAnalyze;

/* TraceCode = TRUE causes comments to be written
 * to the TM code file as code is generated
 */
extern int TraceCode;

/* Error = TRUE prevents further passes if an error occurs */
extern int Error; 
#endif
