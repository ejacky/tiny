/****************************************************/
/* File: symtab.c                                   */
/* Symbol table implementation for the TINY compiler*/
/* (allows only one symbol table)                   */
/* Symbol table is implemented as a chained         */
/* hash table                                       */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

/* SIZE is the size of the hash table */
#define SIZE 211

/* SHIFT is the power of two used as multiplier
   in hash function  */
#define SHIFT 4

// Token to string

char* TTS[] = {[ENDFILE] = "ENDFILE", [ERROR] = "ERROR",
               [COMMENT] = "COMMENT", [COMMENT_ERROR] = "COMMENT_ERROR",
               [ELSE] = "ELSE",       [IF] = "IF",
               [INT] = "INT",         [RETURN] = "RETURN",
               [VOID] = "VOID",       [WHILE] = "WHILE",
               [ID] = "ID",           [NUM] = "NUM",
               [PLUS] = "PLUS",       [MINUS] = "MINUS",
               [TIMES] = "TIMES",     [OVER] = "OVER",
               [LT] = "LT",           [LTEQ] = "LTEQ",
               [GT] = "GT",           [GTEQ] = "GTEQ",
               [EQ] = "EQ",           [NEQ] = "NEQ",
               [ASSIGN] = "ASSIGN",   [SEMI] = "SEMI",
               [COMMA] = "COMMA",     [LPAREN] = "LPAREN",
               [RPAREN] = "RPAREN",   [LBRACK] = "LBRACK",
               [RBRACK] = "RBRACK",   [LBRACE] = "LBRACE",
               [RBRACE] = "RBRACE"};

#define _YES_ARR(x) \
{\
fprintf( listing, "%-6s  ", "Yes" );\
fprintf( listing, "%-6d  ", x );\
}

#define _NO_ARR \
{\
fprintf( listing, "%-6s  ", "No" );\
fprintf( listing, "%-6s  ", "" );\
}

/* the hash function */
static int hash( char* key )
{
    int temp = 0;
    int i = 0;
#if DEBUG
//  printf("hash(%s)\n",key);
#endif
    while ( key[i] != '\0' )
    {
        temp = ( ( temp << SHIFT ) + key[i] ) % SIZE;
        ++i;
    }
    return temp;
}

/* the list of line numbers of the source
 * code in which a variable is referenced
 */
typedef struct LineListRec
{
    int lineno;
    struct LineListRec* next;
} * LineList;

/* The record in the bucket lists for
 * each variable, including name,
 * assigned memory location, and
 * the list of line numbers in which
 * it appears in the source code
 */
// TODO scope를 관리할수 있게 끔 수정.
typedef struct BucketListRec
{
    char* name;
    LineList lines;
    int memloc; /* memory location for variable */
    struct BucketListRec* next;
    // 타입 체크를 위한 노드 정보
    TreeNode* node;
} * BucketList;

/* the hash table */
// TODO 각각의 테이블들이 스코프별로 존재.
static BucketList hashTable[SIZE];

/* Procedure st_insert inserts line numbers and
 * memory locations into the symbol table
 * loc = memory location is inserted only the
 * first time, otherwise ignored
 */

// TODO 변화에 따라 수정.
void st_insert( char* name, int lineno, int loc, TreeNode* t )
{
    int h = hash( name );
    BucketList l = hashTable[h];

    while ( ( l != NULL ) && ( strcmp( name, l->name ) != 0 ) )
        l = l->next;
    if ( l == NULL ) /* variable not yet in table */
    {
        l = (BucketList)malloc( sizeof( struct BucketListRec ) );
        l->name = name;
        l->lines = (LineList)malloc( sizeof( struct LineListRec ) );
        l->lines->lineno = lineno;
        l->memloc = loc;
        l->lines->next = NULL;
        l->next = hashTable[h];

        l->node = t;

        hashTable[h] = l;
    }
    else /* found in table, so just add line number */
    {
        LineList t = l->lines;
        while ( t->next != NULL )
            t = t->next;
        t->next = (LineList)malloc( sizeof( struct LineListRec ) );
        t->next->lineno = lineno;
        t->next->next = NULL;
    }
    //
    /*
    switch(t->nodekind){
      case DeclK:
        printf("AA\n");
      l->node->type = t->attr.type;
        break;
      case ParamK:
        break;
      default:
        break;
    }
    */

} /* st_insert */

/* Function st_lookup returns the memory
 * location of a variable or -1 if not found
 */
int st_lookup( char* name )
{
    int h = hash( name );
    BucketList l = hashTable[h];
    while ( ( l != NULL ) && ( strcmp( name, l->name ) != 0 ) )
        l = l->next;
    if ( l == NULL )
        return -1;
    else
        return l->memloc;
}

/* Procedure printSymTab prints a formatted
 * listing of the symbol table contents
 * to the listing file
 */
void printSymTab( FILE* listing )
{
    int i;
    fprintf( listing, "Variable Name  Location  v/p/f  Array?  ArrSize  Type   Line Numbers\n" );
    fprintf( listing, "--------------------------------------------------------------------\n" );
    for ( i = 0; i < SIZE; ++i )
    {
        if ( hashTable[i] != NULL )
        {
            BucketList l = hashTable[i];
            while ( l != NULL )
            {
                LineList t = l->lines;
                fprintf( listing, "%-14s ", l->name );
                fprintf( listing, "%-8d  ", l->memloc );
                fprintf( listing, "%-6s  ", "v/p/f" );
                switch(l->node->nodekind){
                  case ExpK:
                    if(l->node->kind.exp == ArrIdK)
                      _YES_ARR(l->node->attr.arr.size)
                    else
                      _NO_ARR
                    break;
                  case DeclK:
                    if(l->node->kind.decl == ArrVarK)
                      _YES_ARR(l->node->attr.arr.size)
                    else
                      _NO_ARR
                    break;
                  case ParamK:
                    if(l->node->kind.param ==  ArrParamK)
                      _YES_ARR(l->node->attr.arr.size)
                    else
                      _NO_ARR
                    break;
                }
                fprintf( listing, "%-5s  ", TTS[l->node->type] );
                while ( t != NULL )
                {
                    fprintf( listing, "%4d ", t->lineno );
                    t = t->next;
                }
                fprintf( listing, "\n" );
                l = l->next;
            }
        }
    }
} /* printSymTab */
