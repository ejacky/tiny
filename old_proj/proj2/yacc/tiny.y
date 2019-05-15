/****************************************************/
/* File: tiny.y                                     */
/* The TINY Yacc/Bison specification file           */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/
%{
#define YYPARSER /* distinguishes Yacc output from other code files */

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

#define YYSTYPE TreeNode *
//static char * savedName; /* for use in assignments */
//static int savedLineNo;  /* ditto */
static TreeNode * savedTree; /* stores syntax tree for later return */

static int yyerror(char*);
static int yylex(void);

%}

/* reserved words */
%token ELSE IF INT RETURN VOID WHILE
/* multicharacter tokens */
%token ID NUM
/* special symbols */
%token PLUS MINUS TIMES OVER
%token LESSTHEN LESSEQUAL GREATTHEN GREATEQUAL EQUAL NOTEQUAL
%token ASSIGN SEMICOLON COMMA
%token LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE // paren:(), bracket:[], brace:{}
/* book-keeping tokens */
%token ERROR COMMENT COMMENT_ERROR

%nonassoc RPAREN
%nonassoc ELSE

%start program

/* Grammar for TINY */

%%

program:    decl_list               { savedTree = $1; }
            ;

decl_list:  decl_list decl          { $$ = addSiblingOrNot($1,$2); }
            | decl                  { $$ = $1; }
            ;

decl:       var_decl                { $$ = $1; }
            | func_decl             { $$ = $1; }
            ;

var_decl:   type_spec id_node SEMICOLON {
                $$ = newDeclNode(VarK);
                $$->child[0] = $2; // name
                $$->child[1] = $1; // type_spec
            }
            | type_spec id_node LBRACKET num_node RBRACKET SEMICOLON {
                $$ = newDeclNode(VarArrK);
                $$->child[0] = $2; // name
                $$->child[1] = $4; // arr_length
                $$->child[2] = $1; // type_spec
            }
            ;

type_spec:  INT { 
                $$ = newTypeNode(TypeSpecK);
                $$->attr.typeSpec = INT;
            }
            | VOID {
                $$ = newTypeNode(TypeSpecK);
                $$->attr.typeSpec = VOID;
            }
            ;

func_decl:  type_spec id_node LPAREN params RPAREN comp_stmt {
                $$ = newDeclNode(FuncK);
                $$->child[0] = $2; // name
                $$->child[1] = $1; // type_spec
                $$->child[2] = $4; // parameter list
                $$->child[3] = $6; // compound list
            }
            ;

params:     param_list              {
                $$ = newStmtNode(ParamK);
                $$->child[0] = $1;
            }
            | VOID                  { $$ = newStmtNode(ParamK); }
            ;

param_list: param_list COMMA param  { $$ = addSiblingOrNot($1,$3); }
            | param                 { $$ = $1; }
            ;

param:      type_spec id_node {
                $$ = newDeclNode(VarK);
                $$->child[0] = $2; // name
                $$->child[1] = $1; // type_spec
            }
            | type_spec id_node LBRACKET RBRACKET { 
                $$ = newDeclNode(VarArrK);
                $$->child[0] = $2; // name
                $$->child[1] = NULL; // arr_length, NULL for param
                $$->child[2] = $1; // type_spec
            }
            ;

comp_stmt:  LBRACE local_decls stmt_list RBRACE {
                $$ = newStmtNode(CompK);
                $$->child[0] = $2;
                $$->child[1] = $3;
            }
            ;

local_decls: local_decls var_decl   { $$ = addSiblingOrNot($1,$2); }
            | empty                 { $$ = NULL; }
            ;

stmt_list:  stmt_list stmt          { $$ = addSiblingOrNot($1,$2); }
            | empty                 { $$ = NULL; }
            ;

stmt:       expr_stmt               { $$ = $1; }
            | comp_stmt             { $$ = $1; }
            | select_stmt           { $$ = $1; }
            | iter_stmt             { $$ = $1; }
            | return_stmt           { $$ = $1; }
            ;

expr_stmt:  expr SEMICOLON          { $$ = $1; }
            | SEMICOLON             { $$ = NULL; }
            ;

select_stmt: IF LPAREN expr RPAREN stmt {
                $$ = newStmtNode(SelectK);
                $$->child[0] = $3;
                $$->child[1] = $5;
            }
            | IF LPAREN expr RPAREN stmt ELSE stmt {
                $$ = newStmtNode(SelectK);
                $$->child[0] = $3;
                $$->child[1] = $5;
                $$->child[2] = $7;
            }
            ;

iter_stmt:  WHILE LPAREN expr RPAREN stmt {
                $$ = newStmtNode(IterK);
                $$->child[0] = $3;
                $$->child[1] = $5;
            }
            ;

return_stmt: RETURN SEMICOLON       { $$ = newStmtNode(RetK); }
            | RETURN expr SEMICOLON {
                $$ = newStmtNode(RetK);
                $$->child[0] = $2;
            }
            ;

expr:       var ASSIGN expr {
                $$ = newExpNode(AssignK);
                $$->child[0] = $1;
                $$->child[1] = $3;
            }
            | simple_expr           { $$ = $1; }
            ;

var:        id_node                 { $$ = $1; }
            | id_node LBRACKET expr RBRACKET {
                $$ = newExpNode(IdArrK);
                $$->child[0] = $1;
                $$->child[1] = $3;
            }
            ;

simple_expr: add_expr relop add_expr {
                $$ = $2;
                $$->child[0] = $1;
                $$->child[1] = $3;
            }
            | add_expr              { $$ = $1; }
            ;

relop:      LESSTHEN        {
                $$ = newExpNode(OpK);
                $$->attr.op = LESSTHEN;
            }
            | LESSEQUAL     {
                $$ = newExpNode(OpK);
                $$->attr.op = LESSEQUAL;
            }
            | GREATTHEN     {
                $$ = newExpNode(OpK);
                $$->attr.op = GREATTHEN;
            }
            | GREATEQUAL    {
                $$ = newExpNode(OpK);
                $$->attr.op = GREATEQUAL;
            }
            | EQUAL         {
                $$ = newExpNode(OpK);
                $$->attr.op = EQUAL;
            }
            | NOTEQUAL      {
                $$ = newExpNode(OpK);
                $$->attr.op = NOTEQUAL;
            }
            ;

add_expr:   add_expr addop term {
                $$ = $2;
                $$->child[0] = $1;
                $$->child[1] = $3;
            }
            | term                  { $$ = $1; }
            ;

addop:      PLUS    { 
               $$ = newExpNode(OpK);
               $$->attr.op = PLUS;
            }
            | MINUS {
                $$ = newExpNode(OpK);
                $$->attr.op = MINUS;
            }
            ;

term:       term mulop factor {
                $$ = $2;
                $$->child[0] = $1;
                $$->child[1] = $3;
            }
            | factor { $$ = $1; }
            ;

mulop:      TIMES   {
               $$ = newExpNode(OpK);
               $$->attr.op = TIMES;
            }
            | OVER  {
               $$ = newExpNode(OpK);
               $$->attr.op = OVER;
            }
            ;

factor:     LPAREN expr RPAREN      { $$ = $2; }
            | var                   { $$ = $1; }
            | call                  { $$ = $1; }
            | num_node              { $$ = $1; }
            ;

call:       id_node LPAREN args RPAREN {
                $$ = newExpNode(CallK);
                $$->child[0] = $1;
                $$->child[1] = $3;
            }
            ;

args:       arg_list                { 
                $$ = newStmtNode(ArgK);
                $$->child[0] = $1;
            }
            | empty                 { $$ = NULL; }
            ;

arg_list:   arg_list COMMA expr     { $$ = addSiblingOrNot($1,$3); }
            | expr                  { $$ = $1; }
            ;

id_node:    ID {
                $$ = newExpNode(IdK);
                $$->attr.name = copyString(tokenString);
            }
            ;

num_node:   NUM {
                $$ = newExpNode(ConstK);
                $$->attr.val = atoi(tokenString);
            }
            ;

empty:      /* empty matching */{ $$ = NULL; }
            ;

%%

int yyerror(char * message)
{
    fprintf(listing,"Syntax error at line %d: %s\n",lineno,message);
    fprintf(listing,"Current token: ");
    printToken(yychar,tokenString);
    Error = TRUE;
    return 0;
}

/* yylex calls getToken to make Yacc/Bison output
 * compatible with ealier versions of the TINY scanner
 */
static int yylex(void)
{
    static int token;
    do { token = getToken(); } while (token == COMMENT);
    return token;
}

TreeNode* parse(void)
{
    yyparse();
    return savedTree;
}
