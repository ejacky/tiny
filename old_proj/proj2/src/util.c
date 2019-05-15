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

char* TokenTypetoString [] = 
{
    [ENDFILE] = "ENDFILE",
    [ERROR] = "ERROR",
    [COMMENT] = "COMMENT",
    [COMMENT_ERROR] = "COMMENT_ERROR",
    [ELSE] = "ELSE",
    [IF] = "IF",
    [INT] = "INT",
    [RETURN] = "RETURN",
    [VOID] = "VOID",
    [WHILE] = "WHILE",
    [ID] = "ID",
    [NUM] = "NUM",
    [PLUS] = "PLUS",
    [MINUS] = "MINUS",
    [TIMES] = "TIMES",
    [OVER] = "OVER",
    [LESSTHEN] = "LESSTHEN",
    [LESSEQUAL] = "LESSEQUAL",
    [GREATTHEN] = "GREATTHEN",
    [GREATEQUAL] = "GREATEQUAL",
    [EQUAL] = "EQUAL",
    [NOTEQUAL] = "NOTEQUAL",
    [ASSIGN] = "ASSIGN",
    [SEMICOLON] = "SEMICOLON",
    [COMMA] = "COMMA",
    [LPAREN] = "LPAREN",
    [RPAREN] = "RPAREN",
    [LBRACKET] = "LBRACKET",
    [RBRACKET] = "RBRACKET",
    [LBRACE] = "LBRACE",
    [RBRACE] = "RBRACE"
};

void printToken( TokenType token, const char* tokenString )
{
    if (token == COMMENT) return; //ignore comment

    fprintf( listing, "\t%d\t\t", lineno );
    switch (token)
    {
        case ENDFILE:
            fprintf( listing, "EOF\n" );
            break;
        case COMMENT_ERROR:
            fprintf( listing, "%-20s\t%-20s\n", "ERROR", "Comment Error" );
            break;
        default:
            fprintf( listing, "%-20s\t%-20s\n", TokenTypetoString[token], tokenString );
    }
}

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
TreeNode * newStmtNode(StmtKind kind)
{
    TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
    int i;
    if (t==NULL) fprintf(listing,"Out of memory error at line %d\n",lineno);
    else {
        for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
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
TreeNode * newExpNode(ExpKind kind)
{
    TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
    int i;
    if (t==NULL) fprintf(listing,"Out of memory error at line %d\n",lineno);
    else {
        for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = ExpK;
        t->kind.exp = kind;
        t->lineno = lineno;
        t->type = Void;
    }
    return t;
}

/* Function newDeclNode creates a new statement
 * node for syntax tree construction
 */
TreeNode * newDeclNode(DeclKind kind)
{
    TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
    int i;
    if (t==NULL) fprintf(listing,"Out of memory error at line %d\n",lineno);
    else {
        for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = DeclK;
        t->kind.exp = kind;
        t->lineno = lineno;
    }
    return t;
}

/* Function newTypeNode creates a new statement
 * node for syntax tree construction
 */
TreeNode * newTypeNode(TypeKind kind)
{
    TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
    int i;
    if (t==NULL) fprintf(listing,"Out of memory error at line %d\n",lineno);
    else {
        for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = TypeK;
        t->kind.exp = kind;
        t->lineno = lineno;
    }
    return t;
}

char * copyString(char* s)
{
    int n;
    char* t;
    if (s==NULL) return NULL;

    n = strlen(s)+1;
    t = malloc(n);

    if (t==NULL) fprintf(listing,"Out of memory error at line %d\n",lineno);
    else strcpy(t,s);

    return t;
}

/* Variable indentno is used by printTree to
 * store current number of spaces to indent
 */
static int indentno = 0;

/* macros to increase/decrease indentation */
#define INDENT indentno+=2
#define UNINDENT indentno-=2

/* printSpaces indents by printing spaces */
static void printSpaces(void)
{
    int i;
    for (i=0;i<indentno;i++) fprintf(listing," ");
}

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 */
void printTree( TreeNode * tree )
{
    int i;
    INDENT;
    while ( tree != NULL ) {
        printSpaces();
        switch ( tree->nodekind ) // StmtK,ExpK, DeclK, TypeK
        {
        case StmtK:
            switch ( tree->kind.stmt )
            {
            case CompK: // only in comp_stmt
                fprintf(listing, "Compound Statement : lineno[%4d]\n",tree->lineno);
                break;

            case ParamK: // only in params
                fprintf(listing, "Parameter List : lineno[%4d]\n",tree->lineno);
                break;

            case ArgK: // only in args
                fprintf(listing, "Argument List : lineno[%4d]\n",tree->lineno);
                break;

            case SelectK:
                if( tree->child[2] == NULL )
                    fprintf(listing, "If Statement : lineno[%4d]\n",tree->lineno);
                else
                    fprintf(listing, "If&Else Statement : lineno[%4d]\n",tree->lineno);
                break;

            case IterK:
                fprintf(listing, "While Statement : lineno[%4d]\n",tree->lineno);
                break;

            case RetK:
                fprintf(listing, "Return Statement : lineno[%4d]\n",tree->lineno);
                break;

            default:
                fprintf(listing, "UnKnown Statement Node lineno[%4d]\n",tree->lineno);
                break;
            }
            break;
        case ExpK:
            switch (tree->kind.exp)
            {
            case AssignK:
                fprintf(listing, "Assign Op : = lineno[%4d]\n",tree->lineno);
                break;

            case OpK:
                fprintf(listing, "Op : %s lineno[%4d]\n",TokenTypetoString[tree->attr.op],tree->lineno);
                break;

            case ConstK:
                fprintf(listing, "Constant : %d lineno[%4d]\n",tree->attr.val,tree->lineno);
                break;

            case IdK:
                fprintf(listing, "ID : %s lineno[%4d]\n",tree->attr.name,tree->lineno);
                break;

            case IdArrK:
                fprintf(listing, "Arr ID : lineno[%4d]\n",tree->lineno);
                break;

            case CallK:
                fprintf(listing, "Function Call : lineno[%4d]\n",tree->lineno);
                break;

            default:
                fprintf(listing, "UnKnown Expression Node lineno[%4d]\n",tree->lineno);
                break;
            }
            break;
        case DeclK:
            switch (tree->kind.decl) 
            {
            case FuncK:
                fprintf(listing, "Function Declaration : lineno[%4d]\n",tree->lineno);
                break;

            case VarK:
                fprintf(listing, "Variable Declaration : lineno[%4d]\n",tree->lineno);
                break;

            case VarArrK:
                fprintf(listing, "Array Variable Declaration: lineno[%4d]\n",tree->lineno);
                break;

            default:
                fprintf(listing, "UnKnown Declaration Node lineno[%4d]\n",tree->lineno);
                break;

            }
            break;
        case TypeK:
            switch (tree->kind.type) 
            {
            case TypeSpecK:
                fprintf(listing, "Type : %s lineno[%4d]\n",TokenTypetoString[tree->attr.typeSpec],tree->lineno);
                break;
                
            default:
                fprintf(listing, "UnKnown Type Node lineno[%4d]\n",tree->lineno);
                break;
                    
            }
            break;
        default:
            fprintf(listing,"Unknown Node Type lineno[%4d]\n",tree->lineno);
            break;
        }
        if ( tree->child[0] != NULL || tree->child[1] != NULL || tree->child[2] != NULL || tree->child[3] != NULL )
        {
            printSpaces(); fprintf(listing,"{\n");
            for (i=0;i<MAXCHILDREN;i++)
                printTree(tree->child[i]);
            printSpaces(); fprintf(listing,"}\n");
        }
        tree = tree->sibling;
    }
    UNINDENT;
}

TreeNode* addSiblingOrNot( TreeNode * list, TreeNode * element )
{
    TreeNode* t = list;
    if ( t != NULL )
    {
        while ( t->sibling ) { t = t->sibling; }
        t->sibling = element;
        return list;
    }
    else
    {
        return element;
    }
}
