/****************************************************/
/* File: cgen.c                                     */
/* The code generator implementation                */
/* for the TINY compiler                            */
/* (generates code for the TM machine)              */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "symtab.h"
#include "code.h"
#include "cgen.h"



static int  isGlobalVarsDone=FALSE;

/* tmpOffset is the memory offset for temps
   It is decremented each time a temp is
   stored, and incremeted when loaded again
*/
static int tmpOffset = 0;

/* prototype for internal recursive code generator */
static void cGen (TreeNode * tree);


/* Procedure genStmt generates code at a statement node */
static void genDecl( TreeNode * tree){
  TreeNode * p1, * p2, * p3;
  int savedLoc1,savedLoc2,currentLoc;
  int loc;
#if DEBUG
  printf("genDecl\n");
#endif
  switch(tree->kind.decl){
    case FuncK:
#if DEBUG
      printf("Decl FuncK %s\n",tree->attr.name);
#endif
      /* global vars 선언에서 바로 main 으로*/
      if(!isGlobalVarsDone){
        isGlobalVarsDone=TRUE;
        emitString(".text\n");
        emitLabel("main");
        emitCode("j __main");
      }
      /* main 함수 부분 라벨 예외*/
      if(!strcmp(tree->attr.name,"main")){
        emitLabel("__main");

      }else{
        emitLabel(tree->attr.name);
      }

      /* body of func */
      //p1 = tree->child[2];
      //cGen(p1);

         emitComment("FuncK");

      break;
    case VarK:
#if DEBUG
      printf("Decl VarK %s\n",tree->attr.name);
#endif
      if(!isGlobalVarsDone){
        // 생각해보니 할 것이 없다.
      }
      // local variables
      else{
        emitCode("addi $sp,$sp,-4");
      }

      break;
    case ArrVarK:
      break;
  }
}
/*genDecl*/

/* Procedure genStmt generates code at a statement node */
static void genStmt( TreeNode * tree)
{ 
  TreeNode * p1, * p2, * p3;
  int savedLoc1,savedLoc2,currentLoc;
  int loc;

#if DEBUG
  printf("genStmt\n");
#endif
  switch (tree->kind.stmt) {
      case IfK :
#if DEBUG
  printf("IfK lineno %d\n",tree->lineno);
#endif
         if (TraceCode) emitComment("-> if") ;
         p1 = tree->child[0] ;
         p2 = tree->child[1] ;
         p3 = tree->child[2] ;
         /* generate code for test expression */
         cGen(p1);
         savedLoc1 = emitSkip(1) ;
       
         printf("savedLoc1 : %d\n",savedLoc1);

         emitComment("if: jump to else belongs here");
         /* recurse on then part */
         cGen(p2);
         savedLoc2 = emitSkip(1) ;

         printf("savedLoc2 : %d\n",savedLoc2);

         emitComment("if: jump to end belongs here");
         currentLoc = emitSkip(0) ;
         emitBackup(savedLoc1) ;
         emitRM_Abs("JEQ",ac,currentLoc,"if: jmp to else");
         emitRestore() ;
         /* recurse on else part */
         if(p3 != NULL){
           cGen(p3);
           currentLoc = emitSkip(0) ;
           emitBackup(savedLoc2) ;
           emitRM_Abs("LDA",pc,currentLoc,"jmp to end") ;
           emitRestore() ;
         }
         if (TraceCode)  emitComment("<- if") ;
//      case RepeatK:
//         if (TraceCode) emitComment("-> repeat") ;
//         p1 = tree->child[0] ;
//         p2 = tree->child[1] ;
//         savedLoc1 = emitSkip(0);
//         emitComment("repeat: jump after body comes back here");
//         /* generate code for body */
//         cGen(p1);
//         /* generate code for test */
//         cGen(p2);
//         emitRM_Abs("JEQ",ac,savedLoc1,"repeat: jmp back to body");
//         if (TraceCode)  emitComment("<- repeat") ;
//         break; /* repeat */
//
      case CompK:
         emitComment("CompK");
         //p1 = tree->child[0] ;
         //p2 = tree->child[1] ;
        // emitComment("Compound Statment : var_decl");
         //cGen(p1);
        // emitComment("Compound Statment : stmt_list");
        // cGen(p2);

          break;
      case IterK:
          break;
      case RetK:
          emitComment("RetK");
          break;
      case ElseK:
          break;


      case 111:   
         if (TraceCode) emitComment("-> assign") ;
         /* generate code for rhs */

         // void argument
         //if(!strcmp(tree->attr.name,"(null)")) break;
#if DEBUG
         printf("CompK %s\n",tree->attr.name);
#endif
         cGen(tree->child[0]);
         /* now store value */
         loc = st_lookup(tree->attr.name);
         emitRM("ST",ac,loc,gp,"assign: store value");
         if (TraceCode)  emitComment("<- assign") ;
         break; /* assign_k */

//      case ReadK:
//         emitRO("IN",ac,0,0,"read integer value");
//         loc = st_lookup(tree->attr.name);
//         emitRM("ST",ac,loc,gp,"read: store value");
//         break;
//      case WriteK:
//         /* generate code for expression to write */
//         cGen(tree->child[0]);
//         /* now output it */
//         emitRO("OUT",ac,0,0,"write ac");
//         break;
      default:
         break;
    }
} /* genStmt */

/* Procedure genExp generates code at an expression node */
static void genParam( TreeNode * tree){
#if DEBUG
  printf("genParam\n");
#endif

}/* genParam*/


/* Procedure genExp generates code at an expression node */
static void genExp( TreeNode * tree)
{
#if DEBUG
  printf("genExp\n");
#endif
  int loc;
  TreeNode * p1, * p2;
  switch (tree->kind.exp) {

    case ConstK :
#if DEBUG
      printf("genExp ConstK\n");
#endif
      if (TraceCode) emitComment("-> Const") ;
      /* gen code to load integer constant using LDC */
      emitRM("LDC",ac,tree->attr.val,0,"load const");
      if (TraceCode)  emitComment("<- Const") ;
      break; /* ConstK */
    
    case IdK :
      if (TraceCode) emitComment("-> Id") ;
      loc = st_lookup(tree->attr.name);
      emitRM("LD",ac,loc,gp,"load id value");
      if (TraceCode)  emitComment("<- Id") ;
      break; /* IdK */

    case OpK :
         if (TraceCode) emitComment("-> Op") ;
         p1 = tree->child[0];
         p2 = tree->child[1];
         /* gen code for ac = left arg */
         cGen(p1);
         /* gen code to push left operand */
         emitRM("ST",ac,tmpOffset--,mp,"op: push left");
         /* gen code for ac = right operand */
         cGen(p2);
         /* now load left operand */
         emitRM("LD",ac1,++tmpOffset,mp,"op: load left");
         switch (tree->attr.op) {
            case PLUS :
               emitRO("ADD",ac,ac1,ac,"op +");
               break;
            case MINUS :
               emitRO("SUB",ac,ac1,ac,"op -");
               break;
            case TIMES :
               emitRO("MUL",ac,ac1,ac,"op *");
               break;
            case OVER :
               emitRO("DIV",ac,ac1,ac,"op /");
               break;
            case LT :
               emitRO("SUB",ac,ac1,ac,"op <") ;
               emitRM("JLT",ac,2,pc,"br if true") ;
               emitRM("LDC",ac,0,ac,"false case") ;
               emitRM("LDA",pc,1,pc,"unconditional jmp") ;
               emitRM("LDC",ac,1,ac,"true case") ;
               break;
            case EQ :
               emitRO("SUB",ac,ac1,ac,"op ==") ;
               emitRM("JEQ",ac,2,pc,"br if true");
               emitRM("LDC",ac,0,ac,"false case") ;
               emitRM("LDA",pc,1,pc,"unconditional jmp") ;
               emitRM("LDC",ac,1,ac,"true case") ;
               break;
            default:
               emitComment("BUG: Unknown operator");
               break;
         } /* case op */
         if (TraceCode)  emitComment("<- Op") ;
         break; /* OpK */
    case CallK:
      

         emitComment("CallK");
      break;   

    default:
      break;
  }
} /* genExp */



/* Procedure cGen recursively generates code by
 * tree traversal
 */
static void cGen( TreeNode * tree)
{ 

  int i=0;
  if (tree != NULL)
  {
#if DEBUG
  printf("cGen lineno %d\n",tree->lineno);
#endif
    switch (tree->nodekind) {
      case StmtK:
        genStmt(tree);
        break;
      case ExpK:
        genExp(tree);
        break;
      case ParamK:
        genParam(tree);
        break;
      case DeclK:
        genDecl(tree);
        break;
      default:
        break;
    }
    for( i=0; i<MAXCHILDREN;i++){
      cGen(tree->child[i]);
      if(tree->child[i]==NULL)
        continue;

      switch(tree->nodekind){
          case DeclK:
            switch(tree->kind.decl){
              case FuncK:
                  // Function 끝에 return
                  if(tree->child[i]->nodekind == StmtK){
                    emitComment("return ");
                    emitCode("jr $ra");
                  }
                break;
            }
          break;
          case StmtK:
              switch(tree->kind.stmt){
                case CompK:
                  // Compound 끝에 stack관리
                  emitComment("stack manage");
                  break;
              }
          break;
      }
    }
    cGen(tree->sibling);
  }
#if DEBUG
  if(tree!=NULL)
  printf("cGen lineno %d finished\n",tree->lineno);
#endif
}

/**********************************************/
/* the primary function of the code generator */
/**********************************************/
/* Procedure codeGen generates code to a code
 * file by traversal of the syntax tree. The
 * second parameter (codefile) is the file name
 * of the code file, and is used to print the
 * file name as a comment in the code file
 */
void codeGen(TreeNode * syntaxTree, char * codefile)
{  char * s = malloc(strlen(codefile)+7);
   strcpy(s,"File: ");
   strcat(s,codefile);
   emitComment("C-");
   emitString(".data\n");
   emitComment("Area for global Variables");
   /* generate standard prelude */
 //  emitRM("LD",mp,0,ac,"load maxaddress from location 0");
//   emitRM("ST",ac,0,ac,"clear location 0");
//   emitComment("End of standard prelude.");
   /* generate code for TINY program */
   cGen(syntaxTree);
#if DEBUG
   printf("cGen(SyntaxTree) Finished\n");
#endif
   /* finish */
   emitComment("End of execution.");
   emitCode("li $v0, 10");
   emitCode("syscall");
//   emitRO("HALT",0,0,0,"");
#if DEBUG
   printf("CODEGEN\n");
#endif
}
