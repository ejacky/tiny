/****************************************************/
/* File: symtab.h                                   */
/* Symbol table interface for the TINY compiler     */
/* (allows only one symbol table)                   */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _SYMTAB_H_
#define _SYMTAB_H_

#include "globals.h"
#include "hw3.tab.h"

/* SIZE is the size of the hash table */
#define SIZE 211

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

typedef struct ScopeTreeRec
{
    BucketList node[SIZE];
    struct ScopeTreeRec* parent;
    struct ScopeTreeRec* child;
    struct ScopeTreeRec* sibling;
    int level;
    /* 순회 도움 플래그*/
    int visited;
    /* Stack 관리를 위한 변수*/
    int location;
} * ScopeTree;

/* the hash table */
// TODO 각각의 테이블들이 스코프별로 존재.
extern ScopeTree globals;
extern ScopeTree top;
/* Procedure st_insert inserts line numbers and
 * memory locations into the symbol table
 * loc = memory location is inserted only the
 * first time, otherwise ignored
 */
void st_insert( char* name, int lineno, int loc, TreeNode* t );
void st_insert_local( char* name, int lineno, int loc, TreeNode* t );

/* Function st_lookup returns the memory
 * location of a variable or -1 if not found
 */
int st_lookup( char* name );
int st_lookup_local( char* name );
int st_lookup_lineno( char* name );
int st_lookup_type( char* name );
BucketList st_lookup_buck( char* name );

/* Procedure printSymTab prints a formatted
 * listing of the symbol table contents
 * to the listing file
 */
void printSymTab( FILE* listing );

#endif
