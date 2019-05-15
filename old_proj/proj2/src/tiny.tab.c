/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 7 "yacc/tiny.y" /* yacc.c:339  */

#define YYPARSER /* distinguishes Yacc output from other code files */

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

#define YYSTYPE TreeNode *
//static char * savedName; /* for use in assignments */
//static int savedLineNo;  /* ditto */
static TreeNode * savedTree; /* stores syntax tree for later return */

static int yyerror(char*);
static int yylex(void);


#line 84 "src/tiny.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "tiny.tab.h".  */
#ifndef YY_YY_INC_TINY_TAB_H_INCLUDED
# define YY_YY_INC_TINY_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ELSE = 258,
    IF = 259,
    INT = 260,
    RETURN = 261,
    VOID = 262,
    WHILE = 263,
    ID = 264,
    NUM = 265,
    PLUS = 266,
    MINUS = 267,
    TIMES = 268,
    OVER = 269,
    LESSTHEN = 270,
    LESSEQUAL = 271,
    GREATTHEN = 272,
    GREATEQUAL = 273,
    EQUAL = 274,
    NOTEQUAL = 275,
    ASSIGN = 276,
    SEMICOLON = 277,
    COMMA = 278,
    LPAREN = 279,
    RPAREN = 280,
    LBRACKET = 281,
    RBRACKET = 282,
    LBRACE = 283,
    RBRACE = 284,
    ERROR = 285,
    COMMENT = 286,
    COMMENT_ERROR = 287
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_INC_TINY_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 168 "src/tiny.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   100

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  107

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   287

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    46,    46,    49,    50,    53,    54,    57,    62,    70,
      74,    80,    89,    93,    96,    97,   100,   105,   113,   120,
     121,   124,   125,   128,   129,   130,   131,   132,   135,   136,
     139,   144,   152,   159,   160,   166,   171,   174,   175,   182,
     187,   190,   194,   198,   202,   206,   210,   216,   221,   224,
     228,   234,   239,   242,   246,   252,   253,   254,   255,   258,
     265,   269,   272,   273,   276,   282,   288
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ELSE", "IF", "INT", "RETURN", "VOID",
  "WHILE", "ID", "NUM", "PLUS", "MINUS", "TIMES", "OVER", "LESSTHEN",
  "LESSEQUAL", "GREATTHEN", "GREATEQUAL", "EQUAL", "NOTEQUAL", "ASSIGN",
  "SEMICOLON", "COMMA", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET",
  "LBRACE", "RBRACE", "ERROR", "COMMENT", "COMMENT_ERROR", "$accept",
  "program", "decl_list", "decl", "var_decl", "type_spec", "func_decl",
  "params", "param_list", "param", "comp_stmt", "local_decls", "stmt_list",
  "stmt", "expr_stmt", "select_stmt", "iter_stmt", "return_stmt", "expr",
  "var", "simple_expr", "relop", "add_expr", "addop", "term", "mulop",
  "factor", "call", "args", "arg_list", "id_node", "num_node", "empty", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287
};
# endif

#define YYPACT_NINF -85

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-85)))

#define YYTABLE_NINF -14

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      10,   -85,   -85,     5,    10,   -85,   -85,     7,   -85,   -85,
     -85,   -85,    48,   -85,    32,    15,    19,     7,    46,    28,
     -85,   -85,    31,    47,    50,    10,    55,    52,   -85,   -85,
     -85,   -85,   -85,    10,   -85,   -85,     7,     0,   -85,   -15,
      56,    33,    57,   -85,     9,   -85,   -85,   -85,   -85,   -85,
     -85,   -85,    60,    63,   -85,    49,    62,   -85,   -85,    21,
     -85,     9,   -85,    61,     9,    64,   -85,     9,   -85,   -85,
     -85,   -85,   -85,   -85,   -85,   -85,     9,     9,   -85,   -85,
       9,     9,     9,    65,   -85,    66,   -85,   -85,   -85,    51,
      62,   -85,   -85,    67,    70,   -85,    58,    26,    26,   -85,
       9,   -85,    83,   -85,   -85,    26,   -85
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     9,    10,     0,     2,     4,     5,     0,     6,     1,
       3,    64,     0,     7,     0,     0,    10,     0,     0,    12,
      15,    65,     0,    16,     0,     0,     0,     0,    66,    11,
      14,     8,    17,    66,    20,    19,     0,     0,    22,     0,
       0,     0,     0,    29,     0,    18,    24,    21,    23,    25,
      26,    27,     0,    56,    36,    40,    48,    52,    57,    37,
      58,     0,    33,     0,     0,     0,    28,     0,    49,    50,
      41,    42,    43,    44,    45,    46,     0,     0,    53,    54,
       0,    66,     0,     0,    34,     0,    55,    35,    56,    39,
      47,    51,    63,     0,    60,    61,     0,     0,     0,    59,
       0,    38,    30,    32,    62,     0,    31
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -85,   -85,   -85,    84,    54,    13,   -85,   -85,   -85,    69,
      71,   -85,   -85,   -84,   -85,   -85,   -85,   -85,   -41,   -24,
     -85,   -85,    20,   -85,    22,   -85,    17,   -85,   -85,   -85,
      -5,    85,   -32
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,     7,     8,    18,    19,    20,
      46,    33,    37,    47,    48,    49,    50,    51,    52,    53,
      54,    76,    55,    77,    56,    80,    57,    58,    93,    94,
      59,    60,    34
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      63,    38,    12,    65,    40,     9,    41,    13,    42,    11,
      21,    15,    23,   102,   103,     1,    11,     2,    11,    21,
      83,   106,    43,    85,    44,    21,    87,    17,    28,    45,
      40,    39,    41,    44,    42,    11,    21,     1,    17,    16,
      92,    96,    11,    21,   -13,    81,    36,    82,    43,    95,
      44,    25,    88,    88,    28,    62,    88,    44,    26,   104,
      68,    69,    68,    69,    70,    71,    72,    73,    74,    75,
      13,    24,    14,    27,    15,    78,    79,    31,    28,    32,
      61,    64,    66,    84,    67,   101,   105,    35,    10,    86,
      97,    98,    99,   100,    30,    29,    89,    91,     0,    90,
      22
};

static const yytype_int8 yycheck[] =
{
      41,    33,     7,    44,     4,     0,     6,    22,     8,     9,
      10,    26,    17,    97,    98,     5,     9,     7,     9,    10,
      61,   105,    22,    64,    24,    10,    67,    14,    28,    29,
       4,    36,     6,    24,     8,     9,    10,     5,    25,     7,
      81,    82,     9,    10,    25,    24,    33,    26,    22,    81,
      24,    23,    76,    77,    28,    22,    80,    24,    27,   100,
      11,    12,    11,    12,    15,    16,    17,    18,    19,    20,
      22,    25,    24,    26,    26,    13,    14,    22,    28,    27,
      24,    24,    22,    22,    21,    27,     3,    33,     4,    25,
      25,    25,    25,    23,    25,    24,    76,    80,    -1,    77,
      15
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     7,    34,    35,    36,    37,    38,    39,     0,
      36,     9,    63,    22,    24,    26,     7,    38,    40,    41,
      42,    10,    64,    63,    25,    23,    27,    26,    28,    43,
      42,    22,    27,    44,    65,    37,    38,    45,    65,    63,
       4,     6,     8,    22,    24,    29,    43,    46,    47,    48,
      49,    50,    51,    52,    53,    55,    57,    59,    60,    63,
      64,    24,    22,    51,    24,    51,    22,    21,    11,    12,
      15,    16,    17,    18,    19,    20,    54,    56,    13,    14,
      58,    24,    26,    51,    22,    51,    25,    51,    52,    55,
      57,    59,    51,    61,    62,    65,    51,    25,    25,    25,
      23,    27,    46,    46,    51,     3,    46
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    33,    34,    35,    35,    36,    36,    37,    37,    38,
      38,    39,    40,    40,    41,    41,    42,    42,    43,    44,
      44,    45,    45,    46,    46,    46,    46,    46,    47,    47,
      48,    48,    49,    50,    50,    51,    51,    52,    52,    53,
      53,    54,    54,    54,    54,    54,    54,    55,    55,    56,
      56,    57,    57,    58,    58,    59,    59,    59,    59,    60,
      61,    61,    62,    62,    63,    64,    65
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     6,     1,
       1,     6,     1,     1,     3,     1,     2,     4,     4,     2,
       1,     2,     1,     1,     1,     1,     1,     1,     2,     1,
       5,     7,     5,     2,     3,     3,     1,     1,     4,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     3,     1,     1,     1,     3,     1,     1,     1,     4,
       1,     1,     3,     1,     1,     1,     0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 46 "yacc/tiny.y" /* yacc.c:1646  */
    { savedTree = (yyvsp[0]); }
#line 1321 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 49 "yacc/tiny.y" /* yacc.c:1646  */
    { (yyval) = addSiblingOrNot((yyvsp[-1]),(yyvsp[0])); }
#line 1327 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 50 "yacc/tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1333 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 53 "yacc/tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1339 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 54 "yacc/tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1345 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 57 "yacc/tiny.y" /* yacc.c:1646  */
    {
                (yyval) = newDeclNode(VarK);
                (yyval)->child[0] = (yyvsp[-1]); // name
                (yyval)->child[1] = (yyvsp[-2]); // type_spec
            }
#line 1355 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 62 "yacc/tiny.y" /* yacc.c:1646  */
    {
                (yyval) = newDeclNode(VarArrK);
                (yyval)->child[0] = (yyvsp[-4]); // name
                (yyval)->child[1] = (yyvsp[-2]); // arr_length
                (yyval)->child[2] = (yyvsp[-5]); // type_spec
            }
#line 1366 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 70 "yacc/tiny.y" /* yacc.c:1646  */
    { 
                (yyval) = newTypeNode(TypeSpecK);
                (yyval)->attr.typeSpec = INT;
            }
#line 1375 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 74 "yacc/tiny.y" /* yacc.c:1646  */
    {
                (yyval) = newTypeNode(TypeSpecK);
                (yyval)->attr.typeSpec = VOID;
            }
#line 1384 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 80 "yacc/tiny.y" /* yacc.c:1646  */
    {
                (yyval) = newDeclNode(FuncK);
                (yyval)->child[0] = (yyvsp[-4]); // name
                (yyval)->child[1] = (yyvsp[-5]); // type_spec
                (yyval)->child[2] = (yyvsp[-2]); // parameter list
                (yyval)->child[3] = (yyvsp[0]); // compound list
            }
#line 1396 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 89 "yacc/tiny.y" /* yacc.c:1646  */
    {
                (yyval) = newStmtNode(ParamK);
                (yyval)->child[0] = (yyvsp[0]);
            }
#line 1405 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 93 "yacc/tiny.y" /* yacc.c:1646  */
    { (yyval) = newStmtNode(ParamK); }
#line 1411 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 96 "yacc/tiny.y" /* yacc.c:1646  */
    { (yyval) = addSiblingOrNot((yyvsp[-2]),(yyvsp[0])); }
#line 1417 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 97 "yacc/tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1423 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 100 "yacc/tiny.y" /* yacc.c:1646  */
    {
                (yyval) = newDeclNode(VarK);
                (yyval)->child[0] = (yyvsp[0]); // name
                (yyval)->child[1] = (yyvsp[-1]); // type_spec
            }
#line 1433 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 105 "yacc/tiny.y" /* yacc.c:1646  */
    { 
                (yyval) = newDeclNode(VarArrK);
                (yyval)->child[0] = (yyvsp[-2]); // name
                (yyval)->child[1] = NULL; // arr_length, NULL for param
                (yyval)->child[2] = (yyvsp[-3]); // type_spec
            }
#line 1444 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 113 "yacc/tiny.y" /* yacc.c:1646  */
    {
                (yyval) = newStmtNode(CompK);
                (yyval)->child[0] = (yyvsp[-2]);
                (yyval)->child[1] = (yyvsp[-1]);
            }
#line 1454 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 120 "yacc/tiny.y" /* yacc.c:1646  */
    { (yyval) = addSiblingOrNot((yyvsp[-1]),(yyvsp[0])); }
#line 1460 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 121 "yacc/tiny.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 1466 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 124 "yacc/tiny.y" /* yacc.c:1646  */
    { (yyval) = addSiblingOrNot((yyvsp[-1]),(yyvsp[0])); }
#line 1472 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 125 "yacc/tiny.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 1478 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 128 "yacc/tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1484 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 129 "yacc/tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1490 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 130 "yacc/tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1496 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 131 "yacc/tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1502 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 132 "yacc/tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1508 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 135 "yacc/tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 1514 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 136 "yacc/tiny.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 1520 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 139 "yacc/tiny.y" /* yacc.c:1646  */
    {
                (yyval) = newStmtNode(SelectK);
                (yyval)->child[0] = (yyvsp[-2]);
                (yyval)->child[1] = (yyvsp[0]);
            }
#line 1530 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 144 "yacc/tiny.y" /* yacc.c:1646  */
    {
                (yyval) = newStmtNode(SelectK);
                (yyval)->child[0] = (yyvsp[-4]);
                (yyval)->child[1] = (yyvsp[-2]);
                (yyval)->child[2] = (yyvsp[0]);
            }
#line 1541 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 152 "yacc/tiny.y" /* yacc.c:1646  */
    {
                (yyval) = newStmtNode(IterK);
                (yyval)->child[0] = (yyvsp[-2]);
                (yyval)->child[1] = (yyvsp[0]);
            }
#line 1551 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 159 "yacc/tiny.y" /* yacc.c:1646  */
    { (yyval) = newStmtNode(RetK); }
#line 1557 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 160 "yacc/tiny.y" /* yacc.c:1646  */
    {
                (yyval) = newStmtNode(RetK);
                (yyval)->child[0] = (yyvsp[-1]);
            }
#line 1566 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 166 "yacc/tiny.y" /* yacc.c:1646  */
    {
                (yyval) = newExpNode(AssignK);
                (yyval)->child[0] = (yyvsp[-2]);
                (yyval)->child[1] = (yyvsp[0]);
            }
#line 1576 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 171 "yacc/tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1582 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 174 "yacc/tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1588 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 175 "yacc/tiny.y" /* yacc.c:1646  */
    {
                (yyval) = newExpNode(IdArrK);
                (yyval)->child[0] = (yyvsp[-3]);
                (yyval)->child[1] = (yyvsp[-1]);
            }
#line 1598 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 182 "yacc/tiny.y" /* yacc.c:1646  */
    {
                (yyval) = (yyvsp[-1]);
                (yyval)->child[0] = (yyvsp[-2]);
                (yyval)->child[1] = (yyvsp[0]);
            }
#line 1608 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 187 "yacc/tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1614 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 190 "yacc/tiny.y" /* yacc.c:1646  */
    {
                (yyval) = newExpNode(OpK);
                (yyval)->attr.op = LESSTHEN;
            }
#line 1623 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 194 "yacc/tiny.y" /* yacc.c:1646  */
    {
                (yyval) = newExpNode(OpK);
                (yyval)->attr.op = LESSEQUAL;
            }
#line 1632 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 198 "yacc/tiny.y" /* yacc.c:1646  */
    {
                (yyval) = newExpNode(OpK);
                (yyval)->attr.op = GREATTHEN;
            }
#line 1641 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 202 "yacc/tiny.y" /* yacc.c:1646  */
    {
                (yyval) = newExpNode(OpK);
                (yyval)->attr.op = GREATEQUAL;
            }
#line 1650 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 206 "yacc/tiny.y" /* yacc.c:1646  */
    {
                (yyval) = newExpNode(OpK);
                (yyval)->attr.op = EQUAL;
            }
#line 1659 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 210 "yacc/tiny.y" /* yacc.c:1646  */
    {
                (yyval) = newExpNode(OpK);
                (yyval)->attr.op = NOTEQUAL;
            }
#line 1668 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 216 "yacc/tiny.y" /* yacc.c:1646  */
    {
                (yyval) = (yyvsp[-1]);
                (yyval)->child[0] = (yyvsp[-2]);
                (yyval)->child[1] = (yyvsp[0]);
            }
#line 1678 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 221 "yacc/tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1684 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 224 "yacc/tiny.y" /* yacc.c:1646  */
    { 
               (yyval) = newExpNode(OpK);
               (yyval)->attr.op = PLUS;
            }
#line 1693 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 228 "yacc/tiny.y" /* yacc.c:1646  */
    {
                (yyval) = newExpNode(OpK);
                (yyval)->attr.op = MINUS;
            }
#line 1702 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 234 "yacc/tiny.y" /* yacc.c:1646  */
    {
                (yyval) = (yyvsp[-1]);
                (yyval)->child[0] = (yyvsp[-2]);
                (yyval)->child[1] = (yyvsp[0]);
            }
#line 1712 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 239 "yacc/tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1718 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 242 "yacc/tiny.y" /* yacc.c:1646  */
    {
               (yyval) = newExpNode(OpK);
               (yyval)->attr.op = TIMES;
            }
#line 1727 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 246 "yacc/tiny.y" /* yacc.c:1646  */
    {
               (yyval) = newExpNode(OpK);
               (yyval)->attr.op = OVER;
            }
#line 1736 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 252 "yacc/tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 1742 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 253 "yacc/tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1748 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 254 "yacc/tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1754 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 255 "yacc/tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1760 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 258 "yacc/tiny.y" /* yacc.c:1646  */
    {
                (yyval) = newExpNode(CallK);
                (yyval)->child[0] = (yyvsp[-3]);
                (yyval)->child[1] = (yyvsp[-1]);
            }
#line 1770 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 265 "yacc/tiny.y" /* yacc.c:1646  */
    { 
                (yyval) = newStmtNode(ArgK);
                (yyval)->child[0] = (yyvsp[0]);
            }
#line 1779 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 269 "yacc/tiny.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 1785 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 272 "yacc/tiny.y" /* yacc.c:1646  */
    { (yyval) = addSiblingOrNot((yyvsp[-2]),(yyvsp[0])); }
#line 1791 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 273 "yacc/tiny.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1797 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 276 "yacc/tiny.y" /* yacc.c:1646  */
    {
                (yyval) = newExpNode(IdK);
                (yyval)->attr.name = copyString(tokenString);
            }
#line 1806 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 282 "yacc/tiny.y" /* yacc.c:1646  */
    {
                (yyval) = newExpNode(ConstK);
                (yyval)->attr.val = atoi(tokenString);
            }
#line 1815 "src/tiny.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 288 "yacc/tiny.y" /* yacc.c:1646  */
    { (yyval) = NULL; }
#line 1821 "src/tiny.tab.c" /* yacc.c:1646  */
    break;


#line 1825 "src/tiny.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 291 "yacc/tiny.y" /* yacc.c:1906  */


int yyerror(char * message)
{
    fprintf(listing,"Syntax error at line %d: %s\n",lineno,message);
    fprintf(listing,"Current token: ");
    printToken(yychar,tokenString);
    Error = TRUE;
    return 0;
}

/* yylex calls getToken to make Yacc/Bison output
 * compatible with ealier versions of the TINY scanner
 */
static int yylex(void)
{
    static int token;
    do { token = getToken(); } while (token == COMMENT);
    return token;
}

TreeNode* parse(void)
{
    yyparse();
    return savedTree;
}
