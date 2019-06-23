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
static int location = -4;
static int location_global = 0;
static int location_param = 0;

/* parameter 스코프 조정*/
static int flag_param = 0;
/* main 예외처리를 위한 플래그*/
static int flag_main = 0;

static int flag_check = 0;
static int cnt_scope = 0;

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
    if ( !flag_check )
    {
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
            top->visited = 0;
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
            top->visited = 0;
        }
    }
    /* TypeCheck 일경우. */
    else
    {
        top = top->child;
        while ( top->visited )
        {
            top = top->sibling;
        }
        top->visited = 1;
    } 
    top->location = location;
}

void scope_up()
{
    location = top->location;
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
        location = -4;
    }
}

// type check
void check_in( TreeNode* t )
{
    // compound check
    if ( t->nodekind == StmtK && t->kind.stmt == CompK )
    {
        scope_down();
    }
    // find main func
    if ( t->nodekind == DeclK && t->kind.decl == FuncK )
    {
        if ( t->attr.name[0] == 'm' && t->attr.name[1] == 'a' &&
             t->attr.name[2] == 'i' && t->attr.name[3] == 'n' &&
             t->attr.name[4] == '\0' )
            flag_main = 1;
    }
    else
        flag_main = 0;
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

// return type mismatch
void error_return_mismatch( TreeNode* t )
{
    printf( "ERROR in line %d : function type mismatch.\n", t->lineno );
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

static void checkVOIDreturn( TreeNode* t )
{
    if ( t->nodekind == StmtK && t->kind.stmt == RetK )
        if ( t->child[0] != NULL )
            error_return_mismatch( t );
    // return int in void func()
}

static void checkINTreturn( TreeNode* t )
{
    if ( t->nodekind == StmtK && t->kind.stmt == RetK )
        if ( t->child[0] == NULL )
            error_return_mismatch( t );
    // return void in int func()
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
                    if ( !flag_param )
                    {
                        scope_down();
                    }
                    flag_param = 0;
                    break;
                case IfK:
                    break;
                case IterK:
                    break;
                case RetK:
                    break;
                case ElseK:
                    break;
            }
            break;
        case ExpK:
            switch ( t->kind.exp )
            {
                case IdK:
                    if ( st_lookup( t->attr.name ) == -1 )
                        error_undecl( t, t->lineno );
                    else
                        st_insert( t->attr.name, t->lineno, 0, t );
                    break;
                // Array는 별도의 id kind를 지님.
                case ArrIdK:
                    if ( st_lookup( t->attr.arr.name ) == -1 )
                        error_undecl( t, t->lineno );
                    else
                        st_insert( t->attr.arr.name, t->lineno, 0, t );
                    break;
                case CallK:
                    if ( st_lookup( t->attr.name ) == -1 )
                    {
                        if ( strcmp( t->attr.name, "input" ) == 0 ||
                             strcmp( t->attr.name, "output" ) == 0 )
                        {
                            printf( "input or output called\n" );
                        }
                        else
                            error_undecl( t, t->lineno );
                    }
                    else
                        st_insert( t->attr.name, t->lineno, 0, t );
                    break;
                case AssignK:
                    break;
                default:
                    break;
            }
            break;
        case DeclK:
            switch ( t->kind.decl )
            {
                case VarK:

                    // if ( st_lookup( t->attr.arr.name ) == -1 )
                    if ( st_lookup_local( t->attr.name ) == -1 )
                    {
                        if ( top == globals )
                        {
                            location_global += 4;
                            t->location = location_global;
                            st_insert_local( t->attr.name, t->lineno,
                                             location_global, t );
                        }
                        else
                        {
                            location -= 4;
                            t->location = location;
                            st_insert_local( t->attr.name, t->lineno, location,
                                             t );
                        }
                    }
                    else
                        printf(
                            "ERROR in line %d : declaration of duplicated name "
                            "'%s'. First declared in %d\n",
                            t->lineno, t->attr.name,
                            st_lookup_lineno( t->attr.name ) );

                    break;
                case ArrVarK:

                    if ( st_lookup( t->attr.arr.name ) == -1 )
                    {
                        if ( top == globals )
                        {
                            location_global += 4 * t->attr.arr.size;
                            t->location = location_global;
                            st_insert_local( t->attr.arr.name, t->lineno,
                                             location_global, t );
                        }
                        else
                        {
                            location -= 4*t->attr.arr.size;
                            t->location = location;
                            st_insert_local( t->attr.arr.name, t->lineno,
                                             location, t );
                        }
                    }
                    else
                        printf(
                            "ERROR in line %d : declaration of duplicated name "
                            "'%s'. First declared in %d\n",
                            t->lineno, t->attr.name,
                            st_lookup_lineno( t->attr.arr.name ) );
                    // st_insert( t->attr.arr.name, t->lineno, 0, t );

                    break;
                case FuncK:
                    if ( st_lookup( t->attr.arr.name ) == -1 )
                    {
                        location_global += 4;
                        t->location = location_global;
                        st_insert( t->attr.arr.name, t->lineno, location_global,
                                   t );
                    }
                    else
                        printf(
                            "ERROR in line %d : declaration of duplicated name "
                            "'%s'. First declared in %d\n",
                            t->lineno, t->attr.name,
                            st_lookup_lineno( t->attr.name ) );

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
                    // null 은 거름
                    if ( t->type == VOID )
                        break;

                    if ( st_lookup( t->attr.arr.name ) == -1 )
                    {
                        location_param += 4;
                        t->location = location_param;

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
                    if ( st_lookup( t->attr.arr.name ) == -1 )
                    {
                        location_param += 4;
                        t->location = location_param;
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
    BucketList l_1, l_2;
    TreeNode *t_1, *t_2,*t_3;
    switch ( t->nodekind )
    {
        case StmtK:
            switch ( t->kind.stmt )
            {
                case CompK:
                    scope_up();
                    break;
                case IfK:
                    if ( t->child[0]->nodekind == ExpK &&
                         t->child[0]->kind.exp == CallK &&
                         t->child[0]->type == VOID )
                        // assign function return void
                    {
                        fprintf( listing,
                                 "ERROR in line %d : If condition must "
                                 "be INT\n",
                                 t->lineno );
                    }
                    break;
                case IterK:
                    if ( t->child[1]->nodekind == ExpK &&
                         t->child[1]->kind.exp == CallK &&
                         t->child[1]->type == VOID )
                        // assign function return void
                    {
                        fprintf( listing,
                                 "ERROR in line %d : Iteration condition must "
                                 "be INT\n",
                                 t->lineno );
                    }
                    break;
                case RetK:
                    break;
                case ElseK:
                    break;
                default:
                    break;  // for Fallback, Never entered in normal code
            }
            break;
        case ExpK:
            switch ( t->kind.exp )
            {
                case AssignK:
                    if ( t->child[1]->nodekind == ExpK &&
                         t->child[1]->kind.exp == CallK &&
                         t->child[1]->type == VOID )
                        // assign function return void
                    {
                        fprintf( listing,
                                 "ERROR in line %d : assigning void value to "
                                 "variable\n",
                                 t->lineno );
                    }

                    /* () = Non Arr check */
                    if ( t->child[1]->nodekind == ExpK &&
                         t->child[1]->kind.exp == ArrIdK )
                    {
                        l_2 = st_lookup_buck( t->child[1]->attr.name );

                        if ( ( l_2->node->nodekind == ParamK &&
                               l_2->node->kind.param != ArrParamK ) ||
                             ( l_2->node->nodekind == DeclK &&
                               l_2->node->kind.exp != ArrVarK ) )
                        {
                            printf(
                                "ERROR in line %d : Can't use non-array as "
                                "array\n",
                                t->lineno );
                        }
                    }
                    /* Non arr = () */
                    if ( t->child[0]->nodekind == ExpK &&
                         t->child[0]->kind.exp == ArrIdK &&
                         t->child[1]->nodekind == ExpK &&
                         ( t->child[1]->kind.exp == IdK ||
                           t->child[1]->kind.exp == ArrIdK ))
                    {
                        l_2 = st_lookup_buck( t->child[0]->attr.name );

                        if ( ( l_2->node->nodekind == ParamK &&
                                    l_2->node->kind.param != ArrParamK ) ||
                                ( l_2->node->nodekind == DeclK &&
                                  l_2->node->kind.exp != ArrVarK ) )
                        {
                            printf(
                                    "ERROR in line %d : Can't use non-array as "
                                    "array\n",
                                    t->lineno );
                        }
                    }
/* Non Array[] = ()*/
                    if ( t->child[0]->nodekind == ExpK &&
                              t->child[0]->kind.exp == IdK ){
                         l_2 = st_lookup_buck( t->child[0]->attr.name );

                        if ( ( l_2->node->nodekind == ParamK &&
                               l_2->node->kind.param == ArrParamK ) ||
                             ( l_2->node->nodekind == DeclK &&
                               l_2->node->kind.exp == ArrVarK ) )
                        {
                            printf(
                                "ERROR in line %d : Can't use array as "
                                "non-array\n",
                                t->lineno );
                        } 
                    
                    }
                    /*() = Non Arr[]*/
                  if ( t->child[1]->nodekind == ExpK &&
                              t->child[1]->kind.exp == IdK ){
                         l_2 = st_lookup_buck( t->child[1]->attr.name );

                        if ( ( l_2->node->nodekind == ParamK &&
                               l_2->node->kind.param == ArrParamK ) ||
                             ( l_2->node->nodekind == DeclK &&
                               l_2->node->kind.exp == ArrVarK ) )
                        {
                            printf(
                                "ERROR in line %d : Can't use array as "
                                "non-array\n",
                                t->lineno );
                        } 
                    
                    }

/*
 * 변수에 값을 assign 하는 경우 type에 대한 check
 * 를 해야하는데 어차피 다른 타입 체크에서 걸러짐.
 * ? 뭘 하라는 걸까?
if(t->child[1]->kind.exp == IdK)
fprintf(listing,"%s = %s\n",
    t->child[0]->attr.name,t->child[1]->attr.name);
if(t->child[1]->kind.exp == ConstK)
fprintf(listing,"%s = %d\n",
    t->child[0]->attr.name,t->child[1]->attr.val);
    */

                    break;
                case OpK:
                    // Get Declared type of function
                    
                    if ( 
                         t->child[0]->nodekind == ExpK &&
                         t->child[0]->kind.exp == CallK )
                        // assign function return void
                    {
                        t_1 = st_lookup_buck(t->child[0]->attr.name)->node;
                        if( t_1->type == VOID )
                            fprintf( listing,
                                    "ERROR in line %d : void cannot operated\n",
                                    t->lineno );
                    }
                    if ( t->child[1]->nodekind == ExpK &&
                         t->child[1]->kind.exp == CallK)
                        // assign function return void
                    {
                        t_1 = st_lookup_buck(t->child[1]->attr.name)->node;
                        if ( t_1->type == VOID )
                            fprintf( listing,
                                    "ERROR in line %d : void cannot operated\n",
                                    t->lineno );
                    }
                    
                    break;
                case ConstK:
                    t->type = INT;
                    break;
                case IdK:
                    // fprintf(listing,
                    //"ERROR in line %d : index is not integer.\n",t->lineno
                    // );
                    break;
                case ArrIdK:
                    /* 변수가 array인 경우 array index가 int가 아닌 경우 */
                    if ( t->child[0]->nodekind == ExpK &&
                         ( t->child[0]->kind.exp == IdK ||
                           t->child[0]->kind.exp == ArrIdK ) )
                    {
                     // printf("%s\n",t->child[0]->attr.name);
                        if ( st_lookup_buck( t->child[0]->attr.name )->node->type
                            != INT )
                            fprintf(
                                listing,
                                "ERROR in line %d : index is not integer.\n",
                                t->lineno );
                    }
                    else
                    {
                        //OK
                    }

                    break;
                case CallK:
                    /* parameters - arguments check */
                    l_1 = st_lookup_buck( t->attr.name );
                    if ( l_1->node->nodekind != DeclK ||
                         l_1->node->kind.decl != FuncK )  // call value
                        printf( "ERROR in line %d : cannot call value\n",
                                t->lineno );
                    t_1 = t->child[0];          // call parameter
                    t_2 = l_1->node->child[1];  // decl parameter
                    t->type = l_1->node->type;
                    if ( t_1 == NULL && t_2 != NULL && t_2->type != VOID )
                    {
                        // func(void) > func(a,...)
                        printf(
                                "ERROR in line %d : the number of arguments is "
                                "incorrect.\n",
                                t->lineno );
                    }
                    else if ( t_1 != NULL && t_2 != NULL )
                    // func(a,...) > func(b,...)
                    {
                        while ( t_1 != NULL || t_2 != NULL )
                        {
                            if ( t_1 == NULL || t_2 == NULL )
                            {
                                printf(
                                        "ERROR in line %d : the number of arguments is "
                                        "incorrect.\n",
                                        t->lineno );
                                break;
                            }
                            if(!(t_1->nodekind==ExpK && t_1->kind.exp==ConstK) )
                            {l_1 = st_lookup_buck(t_1->attr.name);
                            t_3 = l_1->node;
                            /*t_3 arg decl, t_2 paarm decl */
                            if (  (t_2->kind.param == ArrParamK 
                                && t_3->kind.decl ==IdK)||
                                ( t_2->kind.param == NonArrParamK &&
                                  t_3->kind.decl == ArrVarK
                                 )
                                )
                                printf(
                                        "ERROR in line %d : the type of argument is "
                                        "incorrect.\n",
                                        t->lineno );
                            // const arg
                            }else{
                               if(t_2->kind.param == ArrParamK) 
                                printf(
                                        "ERROR in line %d : the type of argument is "
                                        "incorrect.\n",
                                        t->lineno );
                            }
                            t_1 = t_1->sibling;
                            t_2 = t_2->sibling;
                        }
                    }

                    break;

                default:
                    break;  // for Fallback, Never entered in normal code
            }
            break;
        case DeclK:
            switch ( t->kind.decl )
            {
                case FuncK:
                    if ( strcmp( t->attr.name, "main" ) == 0 )
                    {
                        if ( t->sibling != NULL )
                        {
                            fprintf( listing,
                                     "ERROR in line %d : main function must at "
                                     "last place\n",
                                     t->lineno );
                        }
                        if ( t->type != VOID )
                        {
                            fprintf( listing,
                                     "ERROR in line %d : main function must "
                                     "return VOID\n",
                                     t->lineno );
                        }
                        if ( t->child[1]->type != VOID )
                        {
                            fprintf( listing,
                                     "ERROR in line %d : main function must "
                                     "have no parameter\n",
                                     t->lineno );
                        }
                        if ( t->child[1]->type == VOID )
                        {
                            traverse(
                                t, nullProc,
                                checkVOIDreturn );  // check return type in void
                        }
                        if ( t->child[1]->type == VOID )
                        {
                            traverse(
                                t, nullProc,
                                checkINTreturn );  // check reutrn type in int
                        }
                    }
                    break;
                case VarK:

                    if ( t->type == VOID )
                        fprintf( listing,
                                 "ERROR in line %d : can't declare 'void' tpye "
                                 "variable\n",
                                 t->lineno );

                    break;
                case ArrVarK:
                    if ( t->type == VOID )
                        fprintf( listing,
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
                /*
                 * main(void) 를 예외처리 해줘야함.
                 * 이 때 "(null)"로 들어올거임.
                 * */
                case ArrParamK:
                    if ( t->type == VOID && !flag_main )
                        fprintf( listing,
                                 "ERROR in line %d : can't declare 'void' type "
                                 "parameter\n",
                                 t->lineno );

                    break;
                case NonArrParamK:
                    if ( t->type == VOID && flag_main )
                        fprintf( listing,
                                 "ERROR in line %d : can't declare 'void' type "
                                 "parameter\n",
                                 t->lineno );
                    break;
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
    flag_check = 1;
    //    top = globals;
    traverse( syntaxTree, check_in, checkNode );
}
