/****************************************************/
/* File: analyze.c                                  */
/* Semantic analyzer implementation                 */
/* for the TINY compiler                            */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "symtab.h"
#include "analyze.h"

ScopeTree globals;
ScopeTree top;

/* counter for variable memory locations */
static int location = 0;
static int location_global = 0;
static int location_param = 0;

static int flag_param = 0;

/* Token To String */

char* T2S[] = {[ENDFILE] = "ENDFILE", [ERROR] = "ERROR",
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

/* TODO */
void scope_down()
{
    int i;
    ScopeTree s = NULL;

    // child가 없다.
    if ( top->child == NULL )
    {
        top->child = top->child;
        top->child = (ScopeTree)malloc( sizeof( struct ScopeTreeRec ) );
        for ( i = 0; i < SIZE; i++ )
            top->child->node[i] = NULL;
        top->child->parent = top;
        top->child->child = NULL;
        top->child->sibling = NULL;
        top->child->level = top->level + 1;
        top = top->child;
    }
    // 기존의 child 가 있으므로 siblin에서 찾는다.
    else
    {
        s = top->child;
        while ( s->sibling != NULL )
        {
            s = s->sibling;
        }
        s->sibling = (ScopeTree)malloc( sizeof( struct ScopeTreeRec ) );
        for ( i = 0; i < SIZE; i++ )
            s->sibling->node[i] = NULL;
        s->sibling->parent = top;
        s->sibling->child = NULL;
        s->sibling->sibling = NULL;
        s->sibling->level = top->level + 1;
        s = s->sibling;
        top = s;
    }
}

void scope_up()
{
    top = top->parent;
}

// build
void check_comp_out( TreeNode* t )
{
    if ( t->nodekind == StmtK && t->kind.stmt == CompK )
    {
        scope_up();
    }
    else if ( t->nodekind == DeclK && t->kind.decl == FuncK )
    {
        location = 0;
    }
}

// type check
void check_comp_in( TreeNode* t )
{
    if ( t->nodekind == StmtK && t->kind.stmt == CompK )
    {
        scope_down();
    }
}

/* Procedure traverse is a generic recursive
 * syntax tree traversal routine:
 * it applies preProc in preorder and postProc
 * in postorder to tree pointed to by t
 */
static void traverse( TreeNode* t,
                      void ( *preProc )( TreeNode* ),
                      void ( *postProc )( TreeNode* ) )
{
    if ( t != NULL )
    {
        preProc( t );
        {
            int i;
            for ( i = 0; i < MAXCHILDREN; i++ )
                traverse( t->child[i], preProc, postProc );
        }
        postProc( t );
        traverse( t->sibling, preProc, postProc );
    }
}

/* Undeclaraed Variable,function */
void error_undecl( TreeNode* t, int num_line )
{
    switch ( t->kind.exp )
    {
        case IdK:
            printf( "ERROR in line %d : variable '%s' not exists.\n", num_line,
                    t->attr.name );
            break;
        case ArrIdK:
            printf( "ERROR in line %d : array '%s' not exists.\n", num_line,
                    t->attr.arr.name );
            break;
        case CallK:
            printf( "ERROR in line %d : function '%s' not exists.\n", num_line,
                    t->attr.name );
            break;
    }
    printf( "exit.\n" );
    exit( -1 );
}

/* nullProc is a do-nothing procedure to
 * generate preorder-only or postorder-only
 * traversals from traverse
 */
static void nullProc( TreeNode* t )
{
    if ( t == NULL )
        return;
    else
        return;
}

/* Procedure insertNode inserts
 * identifiers stored in t into
 * the symbol table
 */
// TODO tiny -> C-
//여기서 해시테이블의 요소에 노드 정보를 같이 받아야함.
static void insertNode( TreeNode* t )
{
    switch ( t->nodekind )
    {
        case StmtK:
            switch ( t->kind.stmt )
            {
                case CompK:
#if DEBUG
                    printf( "Stmt CompK : scope down \n" );
#endif
                    if ( !flag_param )
                    {
                        scope_down();
                    }
                    flag_param = 0;
                    break;
                case IfK:
#if DEBUG
                    printf( "Stmt IfK \n" );
#endif
                    break;
                case IterK:
#if DEBUG
                    printf( "Stmt IterK \n" );
#endif
                    break;
                case RetK:
#if DEBUG
                    printf( "Stmt RetK \n" );
#endif
                    break;
                case ElseK:
#if DEBUG
                    printf( "Stmt ElseK \n" );
#endif
                    break;
            }
            break;
        case ExpK:
            switch ( t->kind.exp )
            {
                case IdK:
#if DEBUG
                    printf( "%s : ExpK id \n", t->attr.name );
#endif
                    if ( st_lookup( t->attr.name ) == -1 )
                        error_undecl( t, t->lineno );
                    else
                        st_insert( t->attr.name, t->lineno, 0, t );
                    break;
                // Array는 별도의 id kind를 지님.
                case ArrIdK:
#if DEBUG
                    printf( "%s : ExpK ArrIdK \n", t->attr.arr.name );
#endif
                    if ( st_lookup( t->attr.arr.name ) == -1 )
                        error_undecl( t, t->lineno );
                    else
                        st_insert( t->attr.arr.name, t->lineno, 0, t );
                    break;
                case CallK:
#if DEBUG
                    printf( "%s : ExpK CallK \n", t->attr.name );
#endif
                    if ( st_lookup( t->attr.name ) == -1 )
                        error_undecl( t, t->lineno );
                    else
                        st_insert( t->attr.name, t->lineno, 0, t );
                    break;
                case AssignK:
#if DEBUG
                    printf( "%d : ExpK AssignK \n", t->attr.type );
#endif
                    break;
                default:
                    break;
            }
            break;
        case DeclK:
            switch ( t->kind.decl )
            {
                case VarK:
#if DEBUG
                    printf( "%s : DeclK NonArrVar \n", t->attr.name );
#endif

                    // if ( st_lookup( t->attr.arr.name ) == -1 )
                    if ( st_lookup_local( t->attr.arr.name ) == -1 )
                    {
                        if ( top == globals )
                        {
                            st_insert_local( t->attr.arr.name, t->lineno,
                                             location_global, t );
                            location_global -= 4;
                        }
                        else
                        {
                            st_insert_local( t->attr.arr.name, t->lineno,
                                             location, t );
                            location -= 4;
                        }
                    }
                    else
                        printf( "ERROR duplicate\n" );
                    // st_insert( t->attr.arr.name, t->lineno, 0, t );

                    break;
                case ArrVarK:

#if DEBUG
                    printf( "%s : DeclK ArrVar \n", t->attr.name );
#endif
                    if ( st_lookup( t->attr.arr.name ) == -1 )
                    {
                        if ( top == globals )
                        {
                            st_insert_local( t->attr.arr.name, t->lineno,
                                             location_global, t );
                            location_global -= 4;
                        }
                        else
                        {
                            st_insert_local( t->attr.arr.name, t->lineno,
                                             location, t );
                            location -= 4;
                        }
                    }
                    else
                        printf( "ERROR duplicate\n" );
                    // st_insert( t->attr.arr.name, t->lineno, 0, t );

                    break;
                case FuncK:
#if DEBUG
                    printf( "%s : DeclK Func \n", t->attr.name );
#endif
                    if ( st_lookup( t->attr.arr.name ) == -1 )
                    {
                        st_insert( t->attr.arr.name, t->lineno, location_global,
                                   t );
                        location_global -= 4;
                    }
                    else
                        st_insert( t->attr.arr.name, t->lineno, 0, t );

                    break;
                default:
                    break;
            }
            break;
        case ParamK:
            switch ( t->kind.param )
            {
                case NonArrParamK:
                    if ( !flag_param )
                    {
                        flag_param = 1;
                        scope_down();
                    }
#if DEBUG
                    printf( "%s : ParamK NonArr \n", t->attr.name );
#endif
                    // null 은 거름
                    if ( t->type == VOID )
                        break;

                    if ( st_lookup( t->attr.arr.name ) == -1 )
                    {
                        location_param += 4;
                        st_insert( t->attr.arr.name, t->lineno, location_param,
                                   t );
                    }
                    else
                        st_insert( t->attr.arr.name, t->lineno, 0, t );
                    break;
                case ArrParamK:
                    if ( !flag_param )
                    {
                        flag_param = 1;
                        scope_down();
                    }
#if DEBUG
                    printf( "%s : ParamK NonArr \n", t->attr.arr.name );
#endif
                    if ( st_lookup( t->attr.arr.name ) == -1 )
                    {
                        location_param += 4;
                        st_insert( t->attr.arr.name, t->lineno, location_param,
                                   t );
                    }
                    else
                        st_insert( t->attr.arr.name, t->lineno, 0, t );
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

/* Function buildSymtab constructs the symbol
 * table by preorder traversal of the syntax tree
 */
void buildSymtab( TreeNode* syntaxTree )
{
    int i;
    // 첫 시행
    if ( globals == NULL )
    {
        globals = (ScopeTree)malloc( sizeof( struct ScopeTreeRec ) );
        top = globals;
        for ( i = 0; i < SIZE; i++ )
            globals->node[i] = NULL;
        globals->parent = NULL;
        globals->child = NULL;
        globals->sibling = NULL;
        printf( "Build globals..\n" );
    }

    traverse( syntaxTree, insertNode, check_comp_out );
    if ( TraceAnalyze )
    {
        fprintf( listing, "\nSymbol table:\n\n" );
        printSymTab( listing );
    }
}

static void typeError( TreeNode* t, char* message )
{
    fprintf( listing, "Type error at line %d: %s\n", t->lineno, message );
    Error = TRUE;
}

/* Procedure checkNode performs
 * type checking at a single tree node
 */
static void checkNode( TreeNode* t )
{
    switch ( t->nodekind )
    {
        case StmtK:
            switch ( t->kind.stmt )
            {
                case CompK:
                    scope_up();
                    if ( t->child[0] == NULL && t->child[1] == NULL )
                        typeError( t,
                                   "Compound Statement must have an Element?" );
#if DEBUG
                    else
                        fprintf( listing, "Test Compound at %d\n", t->lineno );
#endif
                    break;
                case IfK:
                case IterK:
                case RetK:
                case ElseK:
                default:
                    break;  // for Fallback, Never entered in normal code
            }
            break;
        case ExpK:
            switch ( t->kind.exp )
            {
                case AssignK:
// if( t->child[0]->type != Intea ||
// t->child[1]->type != Int)
#if DEBUG
                    fprintf( listing, "Test %d, type : %s\n", t->lineno,
                             T2S[t->child[0]->type] );
#endif
                case OpK:
                case ConstK:
                    break;
                case IdK:
                    break;
                case ArrIdK:
                    break;
                case CallK:
#if DEBUG
                    printf( "%s : ExpK CallK \n", t->attr.name );
#endif

                default:
                    break;  // for Fallback, Never entered in normal code
            }
            break;
        case DeclK:
            switch ( t->kind.decl )
            {
                case FuncK:
                    break;
                case VarK:
                    if ( t->type == VOID )
                        printf(
                            "ERROR in line %d : can't declare 'void' tpye "
                            "variable\n",
                            t->lineno );
                    break;
                case ArrVarK:
                    if ( t->type == VOID )
                        printf(
                            "ERROR in line %d : can't declare 'void' tpye "
                            "array\n",
                            t->lineno );
                    break;
                default:
                    break;  // for Fallback, Never entered in normal code
            }
            break;
        case ParamK:
            switch ( t->kind.param )
            {
                case ArrParamK:
                case NonArrParamK:
                default:
                    break;  // for Fallback, Never entered in normal code
            }
            break;
        case TypeK:
            switch ( t->kind.type )
            {
                case TypeNameK:
                default:
                    break;  // for Fallback, Never entered in normal code
            }
            break;
        default:  // for Fallback, Never entered in normal code
            break;
    }
}

/* Procedure typeCheck performs type checking
 * by a postorder syntax tree traversal
 */
void typeCheck( TreeNode* syntaxTree )
{
    top = globals;
    traverse( syntaxTree, check_comp_in, checkNode );
}
