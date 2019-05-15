/****************************************************/
/* File: util.h                                     */
/* Utility functions for the TINY compiler          */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _UTIL_H_
#define _UTIL_H_

/* For Type Display*/
#define _DSP(_x_) _x_==VOID?"void":"int"

/* Procedure printToken prints a token 
 * and its lexeme to the listing file
 */
void printToken( TokenType, const char* );

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
TreeNode * newStmtNode(StmtKind);

/* Function newExpNode creates a new expression 
 * node for syntax tree construction
 */
TreeNode * newExpNode(ExpKind);


//TODO 
/* Function newParamNode creates a new declation
 * node for syntax tree construction
 */
TreeNode * newDeclNode(DeclKind);

/* Function newParamNode creates a new parameter
 * node for syntax tree construction
 */
TreeNode * newParamNode(ParamKind);

/* Function newTypeNode creates a new type
 * node for syntax tree construction
 */
TreeNode * newTypeNode(TypeKind);

/* Function copyString allocates and makes a new
 * copy of an existing string
 */
char * copyString( char * );

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 */
void printTree( TreeNode * );

#endif
