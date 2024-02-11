This is the README.DOS file included in the loucomp.zip file.
The other files in the distribution are the source code files 
in standard C for the TINY compiler and Tiny Machine simulator
as described in the text:

	Compiler Construction - Principles and Practice, by Kenneth C. Louden,
	PWS Publishing Co., 1997.

They are (with very minor variations) all the files as listed in Appendices
B and C of the text.

At the top level are:

     The file you are now reading (README.DOS):

     The sixteen files as listed on page 23 of the text (which are
     used to make the TINY compiler)

     The tm.c source code file for the TM machine interpreter

     The TINY program of Figure 1.4, page 23 (called sample.tny)

     Two DOS executables tiny.exe and tm.exe for your convenience.

     A Makefile for the TINY compiler and TM simulator for Borland's
     MAKE utility (with minor edits this should work for other MAKEs).

There are also two subdirectories: lex and yacc (assuming you have
unzipped with the -d option).

The lex subdirectory contains the single file tiny.l
as described in the text on pages 90-91, which can be used to build
a lex/flex version of the scanner.

The yacc subdirectory contains the two files tiny.y and globals.h 
as described on pages 243-245 of the text, which can be used 
to build a Yacc/Bison version of the parser. Note that, due to
the considerable variation among Yacc/Bison versions, these files
will probably need some minor editing in order to get them to
work correctly.

All source code has been tested with the Borland 3.0 and 4.0 compilers,
as well as with the Gnu C compiler and the Sun Ansi C compiler (version 2.0).
Any Ansi C compiler should be usable to compile this code, but there is
no guarantee that your favorite compiler will work. Nevertheless, if you
have a problem, I would appreciate hearing about it, and I will respond if I
can find a solution.

