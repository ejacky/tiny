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

ScopeTree globals;
ScopeTree top;

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

#define _YES_ARR( x )                        \
    {                                        \
        fprintf( listing, "%-6s  ", "Yes" ); \
        fprintf( listing, "%-6d  ", x );     \
    }

#define _NO_ARR                             \
    {                                       \
        fprintf( listing, "%-6s  ", "No" ); \
        fprintf( listing, "%-6s  ", "" );   \
    }

/* the hash function */
static int hash( char* key )
{
    int temp = 0;
    int i = 0;
#if DEBUG
//    printf( "hash(%s)\n", key );
#endif
    while ( key[i] != '\0' )
    {
        temp = ( ( temp << SHIFT ) + key[i] ) % SIZE;
        ++i;
    }
    return temp;
}

/* Procedure st_insert inserts line numbers and
 * memory locations into the symbol table
 * loc = memory location is inserted only the
 * first time, otherwise ignored
 */

// TODO 변화에 따라 수정.
void st_insert( char* name, int lineno, int loc, TreeNode* t )
{
    int h = hash( name );
    ScopeTree s = top;
    BucketList l = top->node[h];

    while ( s != NULL )  // search symbol name in scope tree
    {
        while ( ( l != NULL ) && ( strcmp( name, l->name ) != 0 ) )
            l = l->next;
        if ( l == NULL )
        {
            s = s->parent;
            if ( s != NULL )
                l = s->node[h];
        }
        else
            break;
    }

    if ( s == NULL )  // variable not yet in table, insert symbol in top
    {
        l = (BucketList)malloc( sizeof( struct BucketListRec ) );
        l->name = name;
        l->lines = (LineList)malloc( sizeof( struct LineListRec ) );
        l->lines->lineno = lineno;
        l->memloc = loc;
        l->lines->next = NULL;
        l->next = top->node[h];
        l->node = t;
        top->node[h] = l;
    }
    else  // found in table, so just add line number
    {
        LineList t = l->lines;
        while ( t->next != NULL )
            t = t->next;
        t->next = (LineList)malloc( sizeof( struct LineListRec ) );
        t->next->lineno = lineno;
        t->next->next = NULL;
    }
} /* st_insert */

void st_insert_local( char* name, int lineno, int loc, TreeNode* t )
{
    int h = hash( name );
    ScopeTree s = top;
    BucketList l = top->node[h];

    while ( ( l != NULL ) && ( strcmp( name, l->name ) != 0 ) )
        l = l->next;

    if ( l == NULL )  // variable not yet in table, insert symbol in top
    {
        l = (BucketList)malloc( sizeof( struct BucketListRec ) );
        l->name = name;
        l->lines = (LineList)malloc( sizeof( struct LineListRec ) );
        l->lines->lineno = lineno;
        l->memloc = loc;
        l->lines->next = NULL;
        l->next = top->node[h];

        l->node = t;

        top->node[h] = l;
    }
    else  // found in table, so just add line number
    {
        LineList t = l->lines;
        while ( t->next != NULL )
            t = t->next;
        t->next = (LineList)malloc( sizeof( struct LineListRec ) );
        t->next->lineno = lineno;
        t->next->next = NULL;
    }
} /* st_insert */

/* Function st_lookup returns the memory
 * location of a variable or -1 if not found
 */
int st_lookup( char* name )
{
    int h = hash( name );
    int i;
    BucketList l = NULL;
    ScopeTree s = NULL;
    s = top;
    l = top->node[h];
    while ( s != NULL )
    {
        while ( ( l != NULL ) && ( strcmp( name, l->name ) != 0 ) )
            l = l->next;
        if ( l == NULL )
        {
            s = s->parent;
            if ( s != NULL )
                l = s->node[h];
        }
        else
            break;
    }
    if ( s == NULL )
        return -1;
    else
        return l->memloc;
}

int st_lookup_local( char* name )
{
    int h = hash( name );
    BucketList l = NULL;
    l = top->node[h];
    if ( l == NULL )
        return -1;
    else
        return l->memloc;
}
/* Procedure printSymTab prints a formatted
 * listing of the symbol table contents
 * to the listing file
 */

void printSymTabNode( FILE* listing, ScopeTree s )
{
    int i;

    fprintf( listing,
             "\nVariable Name  Loc level  v/p/f  Array?  ArrSize  Type   Line "
             "Numbers\n" );
    fprintf(
        listing,
        "-------------------------------------------------------------------"
        "---\n" );

    for ( i = 0; i < SIZE; ++i )
    {
        if ( s->node[i] != NULL )
        {
            BucketList l = s->node[i];
            while ( l != NULL )
            {
                LineList t = l->lines;
                fprintf( listing, "%-14s ", l->name );
                fprintf( listing, "%-4d  ", l->memloc );
                fprintf( listing, "%-4d  ", s->level );

                // V/P/F print
                switch ( l->node->nodekind )
                {
                    case DeclK:
                        switch ( l->node->kind.exp )
                        {
                            case ArrVarK:
                            case VarK:
                                fprintf( listing, "%-6s  ", "Var" );
                                break;
                            case FuncK:
                                fprintf( listing, "%-6s  ", "Func" );
                                break;
                            default:
                                fprintf( listing, "%-6s  ", "error" );
                                break;
                        }
                        break;
                    case ParamK:
                        fprintf( listing, "%-6s  ", "Param" );
                        break;
                    default:
                        fprintf( listing, "%-6s  ", "error" );
                        break;
                }

                // Array? print
                switch ( l->node->nodekind )
                {
                    case ExpK:
                        if ( l->node->kind.exp == ArrIdK )
                            _YES_ARR( l->node->attr.arr.size )
                        else
                            _NO_ARR
                        break;
                    case DeclK:
                        if ( l->node->kind.decl == ArrVarK )
                            _YES_ARR( l->node->attr.arr.size )
                        else
                            _NO_ARR
                        break;
                    case ParamK:
                        if ( l->node->kind.param == ArrParamK )
                            _YES_ARR( l->node->attr.arr.size )
                        else
                            _NO_ARR
                        break;
                    default:
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
    if ( s->child != NULL )
    {
        printSymTabNode( listing, s->child );
    }
    if ( s->sibling != NULL )
    {
        printSymTabNode( listing, s->sibling );
    }
} /* printSymTab */

void printSymTab( FILE* listing )
{
    // for all scope: print symtab
    printSymTabNode( listing, globals );
}
