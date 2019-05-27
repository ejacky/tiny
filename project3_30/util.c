/****************************************************/
/* File: util.c                                     */
/* Utility function implementation                  */
/* for the TINY compiler                            */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "util.h"

/* Procedure printToken prints a token
 * and its lexeme to the listing file
 */
void printToken( TokenType token, const char* tokenString )
{
    switch ( token )
    {
        case ELSE:
        case IF:
        case INT:
        case RETURN:
        case VOID:
        case WHILE:
            fprintf( listing, "reserved word: %s\n", tokenString );
            break;
        case PLUS:
            fprintf( listing, "+\n" );
            break;
        case MINUS:
            fprintf( listing, "-\n" );
            break;
        case TIMES:
            fprintf( listing, "*\n" );
            break;
        case OVER:
            fprintf( listing, "/\n" );
            break;
        case LT:
            fprintf( listing, "<\n" );
            break;
        case LTEQ:
            fprintf( listing, "<=\n" );
            break;
        case GT:
            fprintf( listing, ">\n" );
            break;
        case GTEQ:
            fprintf( listing, ">=\n" );
            break;
        case EQ:
            fprintf( listing, "==\n" );
            break;
        case NEQ:
            fprintf( listing, "!=\n" );
            break;
        case ASSIGN:
            fprintf( listing, "=\n" );
            break;
        case SEMI:
            fprintf( listing, ";\n" );
            break;
        case COMMA:
            fprintf( listing, ",\n" );
            break;
        case LPAREN:
            fprintf( listing, "(\n" );
            break;
        case RPAREN:
            fprintf( listing, ")\n" );
            break;
        case LBRACK:
            fprintf( listing, "[\n" );
            break;
        case RBRACK:
            fprintf( listing, "]\n" );
            break;
        case LBRACE:
            fprintf( listing, "{\n" );
            break;
        case RBRACE:
            fprintf( listing, "}\n" );
            break;
        case ENDFILE:
            fprintf( listing, "EOF\n" );
            break;
        case NUM:
            fprintf( listing, "NUM, val= %s\n", tokenString );
            break;
        case ID:
            fprintf( listing, "ID, name= %s\n", tokenString );
            break;
        case ERROR:
            fprintf( listing, "ERROR: %s\n", tokenString );
            break;
        default: /* should never happen */
            fprintf( listing, "Unknown token: %d\n", token );
    }
}

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
TreeNode* newStmtNode( StmtKind kind )
{
    TreeNode* t = (TreeNode*)malloc( sizeof( TreeNode ) );
    int i;
    if ( t == NULL )
        fprintf( listing, "Out of memory error at line %d\n", lineno );
    else
    {
        for ( i = 0; i < MAXCHILDREN; i++ )
            t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = StmtK;
        t->kind.stmt = kind;
        t->lineno = lineno;
    }
    return t;
}

/* Function newExpNode creates a new expression
 * node for syntax tree construction
 */
TreeNode* newExpNode( ExpKind kind )
{
    TreeNode* t = (TreeNode*)malloc( sizeof( TreeNode ) );
    int i;
    if ( t == NULL )
        fprintf( listing, "Out of memory error at line %d\n", lineno );
    else
    {
        for ( i = 0; i < MAXCHILDREN; i++ )
            t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = ExpK;
        t->kind.exp = kind;
        t->lineno = lineno;
        if ( kind == ConstK )
            t->type = INT;
        else
            t->type = VOID;
    }
    return t;
}

// TODO
/* Function newParamNode creates a new declation
 * node for syntax tree construction
 */
TreeNode* newDeclNode( DeclKind kind )
{
    TreeNode* t = (TreeNode*)malloc( sizeof( TreeNode ) );
    int i;
    if ( t == NULL )
        fprintf( listing, "Out of memory error at line %d\n", lineno );
    else
    {
        for ( i = 0; i < MAXCHILDREN; i++ )
            t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = DeclK;
        t->kind.decl = kind;
        t->lineno = lineno;
    }
    return t;
}

/* Function newParamNode creates a new parameter
 * node for syntax tree construction
 */
TreeNode* newParamNode( ParamKind kind )
{
    TreeNode* t = (TreeNode*)malloc( sizeof( TreeNode ) );
    int i;
    if ( t == NULL )
        fprintf( listing, "Out of memory error at line %d\n", lineno );
    else
    {
        for ( i = 0; i < MAXCHILDREN; i++ )
            t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = ParamK;
        t->kind.param = kind;
        t->lineno = lineno;
    }
    return t;
}

/* Function newTypeNode creates a new type
 * node for syntax tree construction
 */
TreeNode* newTypeNode( TypeKind kind )
{
    TreeNode* t = (TreeNode*)malloc( sizeof( TreeNode ) );
    int i;
    if ( t == NULL )
        fprintf( listing, "Out of memory error at line %d\n", lineno );
    else
    {
        for ( i = 0; i < MAXCHILDREN; i++ )
            t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = TypeK;
        t->kind.type = kind;
        t->lineno = lineno;
    }
    return t;
}

/* Function copyString allocates and makes a new
 * copy of an existing string
 */
char* copyString( char* s )
{
    int n;
    char* t;
    if ( s == NULL )
        return NULL;
    n = strlen( s ) + 1;
    t = malloc( n );
    if ( t == NULL )
        fprintf( listing, "Out of memory error at line %d\n", lineno );
    else
        strcpy( t, s );
    return t;
}

/* Variable indentno is used by printTree to
 * store current number of spaces to indent
 */
static int indentno = 0;

/* macros to increase/decrease indentation */
#define INDENT indentno += 2
#define UNINDENT indentno -= 2

/* printSpaces indents by printing spaces */
static void printSpaces( void )
{
    int i;
    for ( i = 0; i < indentno; i++ )
        fprintf( listing, " " );
}

// TODO
/* procedure printTree prints a syntax tree to the
 * listing file using indentation to indicate subtrees
 */
void printTree( TreeNode* tree )
{
    int i;
    INDENT;
    while ( tree != NULL )
    {
        printSpaces();
        if ( tree->nodekind == StmtK )
        {
            switch ( tree->kind.stmt )
            {
                case CompK:
                    fprintf( listing, "Compound\n" );
                    break;
                case IfK:
                    fprintf( listing, "If\n" );
                    break;
                case IterK:
                    fprintf( listing, "While\n" );
                    break;
                case RetK:
                    fprintf( listing, "Return\n" );
                    break;
                default:
                    fprintf( listing, "Unknown ExpNode kind\n" );
                    break;
            }
        }
        else if ( tree->nodekind == ExpK )
        {
            switch ( tree->kind.exp )
            {
                case AssignK:
                    fprintf( listing, "Op : " );
                    printToken( tree->attr.op, "\0" );
                    break;
                case OpK:
                    fprintf( listing, "Op : " );
                    printToken( tree->attr.op, "\0" );
                    break;
                case ConstK:
                    fprintf( listing, "Const: %d\n", tree->attr.val );
                    break;
                case IdK:
                    fprintf( listing, "ID : %s\n", tree->attr.name );
                    break;
                case ArrIdK:
                    fprintf( listing, "Array Subscript\n" );
                    INDENT;
                    printSpaces();
                    fprintf( listing, "ID : %s\n", tree->attr.name );
                    UNINDENT;
                    break;
                case CallK:
                    fprintf( listing, "Call : %s\n", tree->attr.name );
                    break;
                default:
                    fprintf( listing, "Unknown ExpNode kind\n" );
                    break;
            }
        }
        else if ( tree->nodekind == DeclK )
        {
            switch ( tree->kind.decl )
            {
                case FuncK:
                    fprintf( listing, "Function Declaration\n" );
                    INDENT;
                    printSpaces();
                    fprintf( listing, "Type : %s\n", _DSP( tree->type ) );
                    printSpaces();
                    fprintf( listing, "ID : %s\n", tree->attr.name );
                    UNINDENT;

                    break;
                case VarK:
                    fprintf( listing, "Variable Declaration\n" );
                    INDENT;
                    printSpaces();
                    fprintf( listing, "Type : %s\n", _DSP( tree->type ) );
                    printSpaces();
                    fprintf( listing, "ID : %s\n", tree->attr.name );
                    UNINDENT;

                    break;
                case ArrVarK:
                    fprintf( listing, "Array Declaration\n" );
                    INDENT;
                    printSpaces();
                    fprintf( listing, "Type : %s\n", _DSP( tree->type ) );
                    printSpaces();
                    /*fprintf(listing, "Type : %s\n",  tree->attr.type);*/
                    fprintf( listing, "ID : %s\n", tree->attr.arr.name );
                    printSpaces();
                    fprintf( listing, "const : %d\n", tree->attr.arr.size );
                    /*tree->attr.arr.size);*/
                    UNINDENT;
                    break;
                default:
                    fprintf( listing, "Unknown DeclNode kind\n" );
                    break;
            }
        }
        else if ( tree->nodekind == ParamK )
        {
            fprintf( listing, "Parameter\n" );
            INDENT;
            printSpaces();
            switch ( tree->kind.param )
            {
                case ArrParamK:
                    fprintf( listing, "Type : %s\n", _DSP( tree->type ) );
                    printSpaces();
                    fprintf( listing, "ID : %s\n", tree->attr.arr.name );
                    printSpaces();
                    fprintf( listing, "const : %d\n", tree->attr.arr.size );
                    break;
                case NonArrParamK:

                    fprintf( listing, "Type : %s\n", _DSP( tree->type ) );
                    if ( tree->type != VOID )
                    {
                        printSpaces();
                        fprintf( listing, "ID : %s\n", tree->attr.name );
                    }
                    break;
                default:
                    fprintf( listing, "Unknown ParamNode kind\n" );
                    break;
            }
            UNINDENT;
        }
        else if ( tree->nodekind == TypeK )
        {
            switch ( tree->kind.type )
            {
                case TypeNameK:
                    fprintf( listing, "Type: " );
                    switch ( tree->attr.type )
                    {
                        case INT:
                            fprintf( listing, "int\n" );
                            break;
                        case VOID:
                            fprintf( listing, "void\n" );
                            break;
                            /*
                          case ARR:
                            fprintf(listing,"int\n");
                            */
                            /*   fprintf(listing," %d\n",tree->attr.arr.size);*/
                    }
                    break;
                default:
                    fprintf( listing, "Unknown TypeNode kind\n" );
                    break;
            }
        }
        else
            fprintf( listing, "Unknown node kind\n" );
        for ( i = 0; i < MAXCHILDREN; i++ )
        {
            printTree( tree->child[i] );
        }
        tree = tree->sibling;
    }
    UNINDENT;
}
