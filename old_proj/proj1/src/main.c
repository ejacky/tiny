/****************************************************/
/* File: main.c                                     */
/* Main program for TINY compiler                   */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/*                                                  */
/* modified by Dohyun Kim in 03/27/19               */
/*                                                  */
/****************************************************/

#include "globals.h"

/* set NO_PARSE to TRUE to get a scanner-only compiler */
#define NO_PARSE TRUE
/* set NO_ANALYZE to TRUE to get a parser-only compiler */
#define NO_ANALYZE FALSE

/* set NO_CODE to TRUE to get a compiler that does not
 * generate code
 */
#define NO_CODE TRUE

#include "util.h"
#if NO_PARSE
#include "scan.h"

#else
#include "parse.h"

#if !NO_ANALYZE
#include "analyze.h"

#if !NO_CODE
#include "cgen.h"

#endif // !NO_CODE
#endif // !NO_ANALYZE
#endif // NO_PARSE

/* allocate global variables */
int lineno = 0;
FILE * source;
FILE * listing;
FILE * code;

/* allocate and set tracing flags */
int EchoSource = FALSE;
int TraceScan = TRUE;
int TraceParse = FALSE;
int TraceAnalyze = FALSE;
int TraceCode = FALSE;

int Error = FALSE;

int main( int argc, char * argv[] )
{
    TreeNode * syntaxTree;
    char pgm[120]; /* source code file name */

    // Shell error check part
    if (argc != 2)
    {
        fprintf(stderr,"usage: %s <filename>\n",argv[0]);
        exit(1);
    }

    strcpy(pgm,argv[1]) ;
    if (strchr (pgm, '.') == NULL)
    {
        strcat(pgm,".tny");
    }

    source = fopen(pgm,"r");
    if (source==NULL)
    {
        fprintf(stderr,"File %s not found\n",pgm);
        exit(1);
    }

    listing = stdout; /* send listing to screen */
    //fprintf(listing,"\nTINY COMPILATION: %s\n",pgm);

#if NO_PARSE
    if (TraceScan) {
        fprintf(listing,"\n\tline number\t\ttoken\t\t\tlexeme\n");
        fprintf(listing,"====================================\n");
        while (getToken()!=ENDFILE);
    }

#else
    syntaxTree = parse();
    if (TraceParse) {
        fprintf(listing,"\nSyntax tree:\n");
        printTree(syntaxTree);
    }
#if !NO_ANALYZE
    if (! Error)
    { if (TraceAnalyze) fprintf(listing,"\nBuilding Symbol Table...\n");
        buildSymtab(syntaxTree);
        if (TraceAnalyze) fprintf(listing,"\nChecking Types...\n");
        typeCheck(syntaxTree);
        if (TraceAnalyze) fprintf(listing,"\nType Checking Finished\n");
    }
#if !NO_CODE
    if (! Error)
    {
        char * codefile;
        int fnlen = strcspn(pgm,".");
        codefile = (char *) calloc(fnlen+4, sizeof(char));
        strncpy(codefile,pgm,fnlen);
        strcat(codefile,".tm");
        code = fopen(codefile,"w");
        if (code == NULL)
        {
            printf("Unable to open %s\n",codefile);
            exit(1);
        }
        codeGen(syntaxTree,codefile);
        fclose(code);
    }
#endif // NO_CODE
#endif // NO_ANALYZE
#endif // NO_PARSE
    fclose(source);
    return 0;
}

