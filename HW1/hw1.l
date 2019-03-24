%{

#include <stdio.h>

/*** globals.h ****/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

/* MAXRESERVED = the number of reserved words */
#define MAXRESERVED 8

typedef enum 
    /* book-keeping tokens */
   {ENDFILE,ERROR,
    /* reserved words */
    IF,THEN,ELSE,END,REPEAT,UNTIL,READ,WRITE,
    /* multicharacter tokens */
    ID,NUM,
    /* special symbols */
    ASSIGN,EQ,LT,PLUS,MINUS,TIMES,OVER,LPAREN,RPAREN,SEMI
   } TokenType;

FILE* source; /* source code text file */
FILE* listing; /* listing output text file */
FILE* code; /* code text file for TM simulator */

int lineno; /* source line number for listing */

/**************************************************/
/***********   Syntax tree for parsing ************/
/**************************************************/

typedef enum {StmtK,ExpK} NodeKind;
typedef enum {IfK,RepeatK,AssignK,ReadK,WriteK} StmtKind;
typedef enum {OpK,ConstK,IdK} ExpKind;

/* ExpType is used for type checking */
typedef enum {Void,Integer,Boolean} ExpType;

#define MAXCHILDREN 3

typedef struct treeNode
   { struct treeNode * child[MAXCHILDREN];
     struct treeNode * sibling;
     int lineno;
     NodeKind nodekind;
     union { StmtKind stmt; ExpKind exp;} kind;
     union { TokenType op;
             int val;
             char * name; } attr;
     ExpType type; /* for type checking of exps */
   } TreeNode;

/**************************************************/
/***********   Flags for tracing       ************/
/**************************************************/

/* EchoSource = TRUE causes the source program to
 * be echoed to the listing file with line numbers
 * during parsing
 */
int EchoSource;

/* TraceScan = TRUE causes token information to be
 * printed to the listing file as each token is
 * recognized by the scanner
 */
int TraceScan;

/* TraceParse = TRUE causes the syntax tree to be
 * printed to the listing file in linearized form
 * (using indents for children)
 */
int TraceParse;

/* TraceAnalyze = TRUE causes symbol table inserts
 * and lookups to be reported to the listing file
 */
int TraceAnalyze;

/* TraceCode = TRUE causes comments to be written
 * to the TM code file as code is generated
 */
int TraceCode;

/* Error = TRUE prevents further passes if an error occurs */
int Error; 



/**************************************************/
/***********   Flags for tracing       ************/
/**************************************************/

/* TraceScan = TRUE causes token information to be
 * printed to the listing file as each token is
 * recognized by the scanner
 */
int TraceScan;

/**** util.h ****/

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

/* Function copyString allocates and makes a new
 * copy of an existing string
 */
char * copyString( char * );

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 */
void printTree( TreeNode * );



/**** util.c ***/

/* Procedure printToken prints a token 
* and its lexeme to the listing file
*/
void printToken( TokenType token, const char* tokenString )
{ switch (token)
 { case IF:
   case THEN:
   case ELSE:
   case END:
   case REPEAT:
   case UNTIL:
   case READ:
   case WRITE:
     fprintf(listing,
        "reserved word: %s\n",tokenString);
     break;
   case ASSIGN: fprintf(listing,":=\n"); break;
   case LT: fprintf(listing,"<\n"); break;
   case EQ: fprintf(listing,"=\n"); break;
   case LPAREN: fprintf(listing,"(\n"); break;
   case RPAREN: fprintf(listing,")\n"); break;
   case SEMI: fprintf(listing,";\n"); break;
   case PLUS: fprintf(listing,"+\n"); break;
   case MINUS: fprintf(listing,"-\n"); break;
   case TIMES: fprintf(listing,"*\n"); break;
   case OVER: fprintf(listing,"/\n"); break;
   case ENDFILE: fprintf(listing,"EOF\n"); break;
   case NUM:
     fprintf(listing,
         "NUM, val= %s\n",tokenString);
     break;
   case ID:
     fprintf(listing,
         "ID, name= %s\n",tokenString);
     break;
   case ERROR:
     fprintf(listing,
         "ERROR: %s\n",tokenString);
     break;
   default: /* should never happen */
     fprintf(listing,"Unknown token: %d\n",token);
 }
}

/* Function newStmtNode creates a new statement
* node for syntax tree construction
*/
TreeNode * newStmtNode(StmtKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
 int i;
 if (t==NULL)
   fprintf(listing,"Out of memory error at line %d\n",lineno);
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
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
 int i;
 if (t==NULL)
   fprintf(listing,"Out of memory error at line %d\n",lineno);
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

/* Function copyString allocates and makes a new
* copy of an existing string
*/
char * copyString(char * s)
{ int n;
 char * t;
 if (s==NULL) return NULL;
 n = strlen(s)+1;
 t = malloc(n);
 if (t==NULL)
   fprintf(listing,"Out of memory error at line %d\n",lineno);
 else strcpy(t,s);
 return t;
}

/* Variable indentno is used by printTree to
* store current number of spaces to indent
*/
static indentno = 0;

/* macros to increase/decrease indentation */
#define INDENT indentno+=2
#define UNINDENT indentno-=2

/* printSpaces indents by printing spaces */
static void printSpaces(void)
{ int i;
 for (i=0;i<indentno;i++)
   fprintf(listing," ");
}

/* procedure printTree prints a syntax tree to the 
* listing file using indentation to indicate subtrees
*/
void printTree( TreeNode * tree )
{ int i;
 INDENT;
 while (tree != NULL) {
   printSpaces();
   if (tree->nodekind==StmtK)
   { switch (tree->kind.stmt) {
       case IfK:
         fprintf(listing,"If\n");
         break;
       case RepeatK:
         fprintf(listing,"Repeat\n");
         break;
       case AssignK:
         fprintf(listing,"Assign to: %s\n",tree->attr.name);
         break;
       case ReadK:
         fprintf(listing,"Read: %s\n",tree->attr.name);
         break;
       case WriteK:
         fprintf(listing,"Write\n");
         break;
       default:
         fprintf(listing,"Unknown ExpNode kind\n");
         break;
     }
   }
   else if (tree->nodekind==ExpK)
   { switch (tree->kind.exp) {
       case OpK:
         fprintf(listing,"Op: ");
         printToken(tree->attr.op,"\0");
         break;
       case ConstK:
         fprintf(listing,"Const: %d\n",tree->attr.val);
         break;
       case IdK:
         fprintf(listing,"Id: %s\n",tree->attr.name);
         break;
       default:
         fprintf(listing,"Unknown ExpNode kind\n");
         break;
     }
   }
   else fprintf(listing,"Unknown node kind\n");
   for (i=0;i<MAXCHILDREN;i++)
        printTree(tree->child[i]);
   tree = tree->sibling;
 }
 UNINDENT;
}

/**** scan.h ****/
#define MAXTOKENLEN 40

char tokenString[MAXTOKENLEN+1];
TokenType getToken(void);

/**** scan.c ****/
/* states in scanner DFA */
typedef enum
   { START,INASSIGN,INCOMMENT,INNUM,INID,DONE }
   StateType;

/* lexeme of identifier or reserved word */
char tokenString[MAXTOKENLEN+1];

/* BUFLEN = length of the input buffer for
   source code lines */
#define BUFLEN 256

static char lineBuf[BUFLEN]; /* holds the current line */
static int linepos = 0; /* current position in LineBuf */
static int bufsize = 0; /* current size of buffer string */
static int EOF_flag = FALSE; /* corrects ungetNextChar behavior on EOF */

/* getNextChar fetches the next non-blank character
   from lineBuf, reading in a new line if lineBuf is
   exhausted */
static int getNextChar(void)
{ if (!(linepos < bufsize))
  { lineno++;
    if (fgets(lineBuf,BUFLEN-1,source))
    { if (EchoSource) fprintf(listing,"%4d: %s",lineno,lineBuf);
      bufsize = strlen(lineBuf);
      linepos = 0;
      return lineBuf[linepos++];
    }
    else
    { EOF_flag = TRUE;
      return EOF;
    }
  }
  else return lineBuf[linepos++];
}

/* ungetNextChar backtracks one character
   in lineBuf */
static void ungetNextChar(void)
{ if (!EOF_flag) linepos-- ;}

/* lookup table of reserved words */
static struct
    { char* str;
      TokenType tok;
    } reservedWords[MAXRESERVED]
   = {{"if",IF},{"then",THEN},{"else",ELSE},{"end",END},
      {"repeat",REPEAT},{"until",UNTIL},{"read",READ},
      {"write",WRITE}};

/* lookup an identifier to see if it is a reserved word */
/* uses linear search */
static TokenType reservedLookup (char * s)
{ int i;
  for (i=0;i<MAXRESERVED;i++)
    if (!strcmp(s,reservedWords[i].str))
      return reservedWords[i].tok;
  return ID;
}

/****************************************/
/* the primary function of the scanner  */
/****************************************/
/* function getToken returns the 
 * next token in source file
 */
TokenType getToken(void)
{  /* index for storing into tokenString */
   int tokenStringIndex = 0;
   /* holds current token to be returned */
   TokenType currentToken;
   /* current state - always begins at START */
   StateType state = START;
   /* flag to indicate save to tokenString */
   int save;
   while (state != DONE)
   { int c = getNextChar();
     save = TRUE;
     switch (state)
     { case START:
         if (isdigit(c))
           state = INNUM;
         else if (isalpha(c))
           state = INID;
         else if (c == ':')
           state = INASSIGN;
         else if ((c == ' ') || (c == '\t') || (c == '\n'))
           save = FALSE;
         else if (c == '{')
         { save = FALSE;
           state = INCOMMENT;
         }
         else
         { state = DONE;
           switch (c)
           { case EOF:
               save = FALSE;
               currentToken = ENDFILE;
               break;
             case '=':
               currentToken = EQ;
               break;
             case '<':
               currentToken = LT;
               break;
             case '+':
               currentToken = PLUS;
               break;
             case '-':
               currentToken = MINUS;
               break;
             case '*':
               currentToken = TIMES;
               break;
             case '/':
               currentToken = OVER;
               break;
             case '(':
               currentToken = LPAREN;
               break;
             case ')':
               currentToken = RPAREN;
               break;
             case ';':
               currentToken = SEMI;
               break;
             default:
               currentToken = ERROR;
               break;
           }
         }
         break;
       case INCOMMENT:
         save = FALSE;
         if (c == EOF)
         { state = DONE;
           currentToken = ENDFILE;
         }
         else if (c == '}') state = START;
         break;
       case INASSIGN:
         state = DONE;
         if (c == '=')
           currentToken = ASSIGN;
         else
         { /* backup in the input */
           ungetNextChar();
           save = FALSE;
           currentToken = ERROR;
         }
         break;
       case INNUM:
         if (!isdigit(c))
         { /* backup in the input */
           ungetNextChar();
           save = FALSE;
           state = DONE;
           currentToken = NUM;
         }
         break;
       case INID:
         if (!isalpha(c))
         { /* backup in the input */
           ungetNextChar();
           save = FALSE;
           state = DONE;
           currentToken = ID;
         }
         break;
       case DONE:
       default: /* should never happen */
         fprintf(listing,"Scanner Bug: state= %d\n",state);
         state = DONE;
         currentToken = ERROR;
         break;
     }
     if ((save) && (tokenStringIndex <= MAXTOKENLEN))
       tokenString[tokenStringIndex++] = (char) c;
     if (state == DONE)
     { tokenString[tokenStringIndex] = '\0';
       if (currentToken == ID)
         currentToken = reservedLookup(tokenString);
     }
   }
   if (TraceScan) {
     fprintf(listing,"\t%d: ",lineno);
     printToken(currentToken,tokenString);
   }
   return currentToken;
} /* end getToken */

%}

digit       [0-9]
number      {digit}+
letter      [a-zA-Z]
identifier  {letter}+
newline     \n
whitespace  [ \t]+


%%
"if"            {printf("if\n");return IF;}
"then"          {return THEN;}
"else"          {return ELSE;}
"end"           {return END;}
"repeat"        {return REPEAT;}
"until"         {return UNTIL;}
"read"          {return READ;}
"write"         {return WRITE;}
":="            {return ASSIGN;}
"="             {return EQ;}
"<"             {return LT;}
"+"             {return PLUS;}
"-"             {return MINUS;}
"*"             {return TIMES;}
"/"             {return OVER;}
"("             {return LPAREN;}
")"             {return RPAREN;}
";"             {return SEMI;}
{number}        {printf("num\n"); return NUM;}
{identifier}    {return ID;}
{newline}       {lineno++;}
{whitespace}    {/* skip whitespace */}
"{"             { char c;
                  do
                  { c = input();
                    if (c == EOF) break;
                    if (c == '\n') lineno++;
                  } while (c != '}');
                }
.               {return ERROR;}


%%

main(int argc, char*argv[])
{

 char pgm[20]; /* source code file name */
  if (argc != 2)
    { fprintf(stderr,"usage: %s <filename>\n",argv[0]);
      exit(1);
    }
  strcpy(pgm,argv[1]) ;
  if (strchr (pgm, '.') == NULL)
     strcat(pgm,".tny");
  source = fopen(pgm,"r");
  if (source==NULL)
  { fprintf(stderr,"File %s not found\n",pgm);
    exit(1);
  }
  listing = stdout; /* send listing to screen */
  fprintf(listing,"\nTINY COMPILATION: %s\n",pgm);
  fprintf(listing,"\n  line number    token     lexeme\n",pgm);
  fprintf(listing,"-------------------------------------\n",pgm);

  
  yyin = source;
	yyout = listing;
	
  yylex();
 fclose(source); //책에는 없다.
 return 0;
}

yywrap(){
  printf("EOF\n");
}



