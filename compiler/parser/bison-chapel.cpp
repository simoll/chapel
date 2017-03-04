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
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 1

/* Pull parsers.  */
#define YYPULL 0




/* Copy the first part of user declarations.  */

#line 67 "bison-chapel.cpp" /* yacc.c:339  */

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
   by #include "bison-chapel.h".  */
#ifndef YY_YY_INCLUDE_BISON_CHAPEL_H_INCLUDED
# define YY_YY_INCLUDE_BISON_CHAPEL_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 32 "chapel.ypp" /* yacc.c:355  */

  #include <string>
  extern int         captureTokens;
  extern std::string captureString;
#line 45 "chapel.ypp" /* yacc.c:355  */

  #ifndef _BISON_CHAPEL_DEFINES_0_
  #define _BISON_CHAPEL_DEFINES_0_

  #define YYLEX_NEWLINE                  -1
  #define YYLEX_SINGLE_LINE_COMMENT      -2
  #define YYLEX_BLOCK_COMMENT            -3

  typedef void* yyscan_t;

  int processNewline(yyscan_t scanner);
  void stringBufferInit();

  #endif
#line 65 "chapel.ypp" /* yacc.c:355  */

  #ifndef _BISON_CHAPEL_DEFINES_1_
  #define _BISON_CHAPEL_DEFINES_1_

  #include "symbol.h"

  #include <cstdio>
  #include <utility>
  #include <vector>

  class ArgSymbol;
  class BlockStmt;
  class CallExpr;
  class DefExpr;
  class EnumType;
  class Expr;
  class FnSymbol;
  class Type;

  enum   ProcIter {
    ProcIter_PROC,
    ProcIter_ITER
  };

  struct IntentExpr {
    Expr*     iVar;
    IntentTag tfIntent; // undefined for a reduce intent
    Expr*     riExp;    // non-NULL for a reduce intent
  };

  struct OnlyRename {
    enum{SINGLE, DOUBLE} tag;

    union {
      Expr*  elem;
      std::pair<Expr*, Expr*>* renamed;
    };
  };

  // The lexer only uses pch.
  // The remaining types are for parser productions
  union  YYSTYPE {
    const char*       pch;

    Vec<const char*>* vpch;
    RetTag            retTag;
    bool              b;
    IntentTag         pt;
    Expr*             pexpr;
    DefExpr*          pdefexpr;
    CallExpr*         pcallexpr;
    BlockStmt*        pblockstmt;
    Type*             ptype;
    EnumType*         penumtype;
    FnSymbol*         pfnsymbol;
    Flag              flag;
    ProcIter          procIter;
    FlagSet*          flagSet;
    IntentExpr        pIntentExpr;
    ForallIntents*    pForallIntents;
    std::vector<OnlyRename*>* ponlylist;
  };

  #endif
#line 135 "chapel.ypp" /* yacc.c:355  */

  #ifndef _BISON_CHAPEL_DEFINES_2_
  #define _BISON_CHAPEL_DEFINES_2_

  struct YYLTYPE {
    int         first_line;
    int         first_column;
    int         last_line;
    int         last_column;
    const char* comment;
  };

  #define YYLTYPE_IS_DECLARED 1
  #define YYLTYPE_IS_TRIVIAL  1

  #endif
#line 157 "chapel.ypp" /* yacc.c:355  */

  #ifndef _BISON_CHAPEL_DEFINES_3_
  #define _BISON_CHAPEL_DEFINES_3_

  class ParserContext {
  public:
    ParserContext()
    {
      scanner       = 0;
      latestComment = 0;
      generatedStmt = 0;
    }

    ParserContext(yyscan_t scannerIn)
    {
      scanner       = scannerIn;
      latestComment = 0;
      generatedStmt = 0;
    }

    yyscan_t    scanner;
    const char* latestComment;
    BaseAST*    generatedStmt;
  };

  #endif

#line 227 "bison-chapel.cpp" /* yacc.c:355  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TIDENT = 258,
    INTLITERAL = 259,
    REALLITERAL = 260,
    IMAGLITERAL = 261,
    STRINGLITERAL = 262,
    CSTRINGLITERAL = 263,
    EXTERNCODE = 264,
    TALIGN = 265,
    TAS = 266,
    TATOMIC = 267,
    TBEGIN = 268,
    TBREAK = 269,
    TBY = 270,
    TCATCH = 271,
    TCLASS = 272,
    TCOBEGIN = 273,
    TCOFORALL = 274,
    TCONFIG = 275,
    TCONST = 276,
    TCONTINUE = 277,
    TDELETE = 278,
    TDMAPPED = 279,
    TDO = 280,
    TDOMAIN = 281,
    TELSE = 282,
    TENUM = 283,
    TEXCEPT = 284,
    TEXPORT = 285,
    TEXTERN = 286,
    TFOR = 287,
    TFORALL = 288,
    TIF = 289,
    TIN = 290,
    TINDEX = 291,
    TINLINE = 292,
    TINOUT = 293,
    TITER = 294,
    TLABEL = 295,
    TLAMBDA = 296,
    TLET = 297,
    TLOCAL = 298,
    TMINUSMINUS = 299,
    TMODULE = 300,
    TNEW = 301,
    TNIL = 302,
    TNOINIT = 303,
    TON = 304,
    TONLY = 305,
    TOTHERWISE = 306,
    TOUT = 307,
    TPARAM = 308,
    TPLUSPLUS = 309,
    TPRAGMA = 310,
    TPRIMITIVE = 311,
    TPRIVATE = 312,
    TPROC = 313,
    TPUBLIC = 314,
    TRECORD = 315,
    TREDUCE = 316,
    TREF = 317,
    TREQUIRE = 318,
    TRETURN = 319,
    TSCAN = 320,
    TSELECT = 321,
    TSERIAL = 322,
    TSINGLE = 323,
    TSPARSE = 324,
    TSUBDOMAIN = 325,
    TSYNC = 326,
    TTHEN = 327,
    TTHROW = 328,
    TTHROWS = 329,
    TTRY = 330,
    TTRYBANG = 331,
    TTYPE = 332,
    TUNDERSCORE = 333,
    TUNION = 334,
    TUSE = 335,
    TVAR = 336,
    TWHEN = 337,
    TWHERE = 338,
    TWHILE = 339,
    TWITH = 340,
    TYIELD = 341,
    TZIP = 342,
    TALIAS = 343,
    TAND = 344,
    TASSIGN = 345,
    TASSIGNBAND = 346,
    TASSIGNBOR = 347,
    TASSIGNBXOR = 348,
    TASSIGNDIVIDE = 349,
    TASSIGNEXP = 350,
    TASSIGNLAND = 351,
    TASSIGNLOR = 352,
    TASSIGNMINUS = 353,
    TASSIGNMOD = 354,
    TASSIGNMULTIPLY = 355,
    TASSIGNPLUS = 356,
    TASSIGNSL = 357,
    TASSIGNSR = 358,
    TBAND = 359,
    TBNOT = 360,
    TBOR = 361,
    TBXOR = 362,
    TCOLON = 363,
    TCOMMA = 364,
    TDIVIDE = 365,
    TDOT = 366,
    TDOTDOT = 367,
    TDOTDOTDOT = 368,
    TEQUAL = 369,
    TEXP = 370,
    TGREATER = 371,
    TGREATEREQUAL = 372,
    THASH = 373,
    TLESS = 374,
    TLESSEQUAL = 375,
    TMINUS = 376,
    TMOD = 377,
    TNOT = 378,
    TNOTEQUAL = 379,
    TOR = 380,
    TPLUS = 381,
    TQUESTION = 382,
    TSEMI = 383,
    TSHIFTLEFT = 384,
    TSHIFTRIGHT = 385,
    TSTAR = 386,
    TSWAP = 387,
    TASSIGNREDUCE = 388,
    TIO = 389,
    TLCBR = 390,
    TRCBR = 391,
    TLP = 392,
    TRP = 393,
    TLSBR = 394,
    TRSBR = 395,
    TNOELSE = 396,
    TUPLUS = 397,
    TUMINUS = 398
  };
#endif

/* Value type.  */

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



#ifndef YYPUSH_MORE_DEFINED
# define YYPUSH_MORE_DEFINED
enum { YYPUSH_MORE = 4 };
#endif

typedef struct yypstate yypstate;

int yypush_parse (yypstate *ps, int pushed_char, YYSTYPE const *pushed_val, YYLTYPE *pushed_loc, ParserContext* context);

yypstate * yypstate_new (void);
void yypstate_delete (yypstate *ps);
/* "%code provides" blocks.  */
#line 188 "chapel.ypp" /* yacc.c:355  */

  extern int yydebug;

  void yyerror(YYLTYPE*       ignored,
               ParserContext* context,
               const char*    str);

#line 416 "bison-chapel.cpp" /* yacc.c:355  */

#endif /* !YY_YY_INCLUDE_BISON_CHAPEL_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 422 "bison-chapel.cpp" /* yacc.c:358  */
/* Unqualified %code blocks.  */
#line 38 "chapel.ypp" /* yacc.c:359  */

  #include <string>
  int         captureTokens;
  std::string captureString;
#line 196 "chapel.ypp" /* yacc.c:359  */

  #include "build.h"
  #include "CatchStmt.h"
  #include "DoWhileStmt.h"
  #include "driver.h"
  #include "flex-chapel.h"
  #include "ForLoop.h"
  #include "parser.h"
  #include "stmt.h"
  #include "stringutil.h"
  #include "TryStmt.h"
  #include "vec.h"
  #include "WhileDoStmt.h"

  #include <cstdio>
  #include <cstdlib>
  #include <cstring>
  #include <stdint.h>

  static int query_uid = 1;

  #define YYLLOC_DEFAULT(Current, Rhs, N)                                 \
    if (N) {                                                              \
      (Current).first_line   = (Rhs)[1].first_line;                       \
      (Current).first_column = (Rhs)[1].first_column;                     \
      (Current).last_line    = (Rhs)[N].last_line;                        \
      (Current).last_column  = (Rhs)[N].last_column;                      \
      (Current).comment      = NULL;                                      \
                                                                          \
      if ((Current).first_line)                                           \
        yystartlineno = (Current).first_line;                             \
                                                                          \
    } else  {                                                             \
      (Current) = yylloc;                                                 \
    }

  void yyerror(YYLTYPE*       ignored,
               ParserContext* context,
               const char*    str) {
    // TODO -- should this begin with error:
    if (!chplParseString) {
      const char* yyText = yyget_text(context->scanner);

      fprintf(stderr, "%s:%d: %s", yyfilename, chplLineno, str);

      if (strlen(yyText) > 0) {
        fprintf(stderr, ": near '%s'", yyText);
      }
    } else {
      fprintf(stderr, "%s: %s", yyfilename, str);

      if (chplParseStringMsg && (strlen(chplParseStringMsg) > 0)) {
        fprintf(stderr, " %s", chplParseStringMsg);
      }
    }

    fprintf(stderr, "\n");

    clean_exit(1);
  }

#line 491 "bison-chapel.cpp" /* yacc.c:359  */

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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   12823

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  144
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  119
/* YYNRULES -- Number of rules.  */
#define YYNRULES  472
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  891

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   398

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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   431,   431,   436,   437,   443,   444,   449,   450,   455,
     456,   457,   458,   459,   460,   461,   462,   463,   464,   465,
     466,   467,   468,   469,   470,   471,   472,   473,   474,   475,
     476,   477,   478,   479,   480,   481,   482,   486,   488,   493,
     494,   495,   510,   511,   516,   517,   522,   527,   532,   536,
     542,   547,   551,   556,   560,   561,   562,   566,   570,   571,
     572,   573,   574,   575,   576,   577,   578,   579,   580,   581,
     582,   583,   584,   585,   589,   590,   594,   598,   599,   603,
     604,   608,   609,   613,   614,   615,   616,   617,   618,   619,
     623,   624,   628,   643,   644,   645,   646,   647,   648,   649,
     650,   651,   652,   653,   654,   655,   656,   657,   658,   659,
     665,   671,   677,   683,   690,   700,   704,   705,   706,   707,
     711,   712,   713,   714,   715,   716,   720,   721,   725,   731,
     732,   733,   737,   740,   745,   746,   750,   752,   754,   761,
     766,   774,   779,   784,   792,   793,   798,   799,   801,   806,
     816,   825,   829,   837,   838,   843,   848,   842,   873,   879,
     886,   894,   905,   911,   904,   939,   943,   948,   952,   960,
     961,   965,   966,   967,   968,   969,   970,   971,   972,   973,
     974,   975,   976,   977,   978,   979,   980,   981,   982,   983,
     984,   985,   986,   987,   988,   989,   990,   994,   995,   996,
     997,   998,   999,  1000,  1001,  1002,  1003,  1004,  1005,  1009,
    1010,  1014,  1018,  1019,  1020,  1024,  1026,  1028,  1030,  1035,
    1036,  1040,  1041,  1042,  1043,  1044,  1045,  1046,  1047,  1048,
    1052,  1053,  1054,  1055,  1056,  1057,  1061,  1062,  1066,  1067,
    1068,  1069,  1070,  1071,  1075,  1076,  1079,  1080,  1084,  1085,
    1089,  1091,  1096,  1097,  1101,  1102,  1106,  1107,  1111,  1113,
    1115,  1120,  1133,  1150,  1151,  1153,  1158,  1166,  1174,  1182,
    1191,  1201,  1202,  1203,  1207,  1208,  1216,  1218,  1224,  1229,
    1231,  1233,  1238,  1240,  1242,  1249,  1250,  1251,  1255,  1256,
    1261,  1262,  1263,  1264,  1284,  1288,  1292,  1300,  1304,  1305,
    1306,  1310,  1312,  1318,  1320,  1322,  1327,  1328,  1329,  1330,
    1331,  1332,  1333,  1339,  1340,  1341,  1342,  1346,  1347,  1348,
    1352,  1353,  1357,  1358,  1362,  1363,  1367,  1368,  1369,  1370,
    1371,  1375,  1386,  1387,  1388,  1389,  1390,  1391,  1393,  1395,
    1397,  1399,  1401,  1403,  1408,  1410,  1412,  1414,  1416,  1418,
    1420,  1422,  1424,  1426,  1428,  1430,  1432,  1439,  1445,  1451,
    1457,  1466,  1471,  1479,  1480,  1481,  1482,  1483,  1484,  1485,
    1486,  1491,  1492,  1496,  1501,  1504,  1509,  1514,  1517,  1522,
    1526,  1527,  1531,  1532,  1537,  1542,  1550,  1551,  1552,  1553,
    1554,  1555,  1556,  1557,  1558,  1560,  1562,  1564,  1566,  1568,
    1573,  1574,  1575,  1576,  1587,  1588,  1592,  1593,  1594,  1598,
    1599,  1600,  1608,  1609,  1610,  1611,  1615,  1616,  1617,  1618,
    1619,  1620,  1621,  1622,  1623,  1624,  1628,  1636,  1637,  1641,
    1642,  1643,  1644,  1645,  1646,  1647,  1648,  1649,  1650,  1651,
    1652,  1653,  1654,  1655,  1656,  1657,  1658,  1659,  1660,  1661,
    1662,  1663,  1667,  1668,  1669,  1670,  1671,  1672,  1676,  1677,
    1678,  1679,  1683,  1684,  1685,  1686,  1691,  1692,  1693,  1694,
    1695,  1696,  1697
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TIDENT", "INTLITERAL", "REALLITERAL",
  "IMAGLITERAL", "STRINGLITERAL", "CSTRINGLITERAL", "EXTERNCODE", "TALIGN",
  "TAS", "TATOMIC", "TBEGIN", "TBREAK", "TBY", "TCATCH", "TCLASS",
  "TCOBEGIN", "TCOFORALL", "TCONFIG", "TCONST", "TCONTINUE", "TDELETE",
  "TDMAPPED", "TDO", "TDOMAIN", "TELSE", "TENUM", "TEXCEPT", "TEXPORT",
  "TEXTERN", "TFOR", "TFORALL", "TIF", "TIN", "TINDEX", "TINLINE",
  "TINOUT", "TITER", "TLABEL", "TLAMBDA", "TLET", "TLOCAL", "TMINUSMINUS",
  "TMODULE", "TNEW", "TNIL", "TNOINIT", "TON", "TONLY", "TOTHERWISE",
  "TOUT", "TPARAM", "TPLUSPLUS", "TPRAGMA", "TPRIMITIVE", "TPRIVATE",
  "TPROC", "TPUBLIC", "TRECORD", "TREDUCE", "TREF", "TREQUIRE", "TRETURN",
  "TSCAN", "TSELECT", "TSERIAL", "TSINGLE", "TSPARSE", "TSUBDOMAIN",
  "TSYNC", "TTHEN", "TTHROW", "TTHROWS", "TTRY", "TTRYBANG", "TTYPE",
  "TUNDERSCORE", "TUNION", "TUSE", "TVAR", "TWHEN", "TWHERE", "TWHILE",
  "TWITH", "TYIELD", "TZIP", "TALIAS", "TAND", "TASSIGN", "TASSIGNBAND",
  "TASSIGNBOR", "TASSIGNBXOR", "TASSIGNDIVIDE", "TASSIGNEXP",
  "TASSIGNLAND", "TASSIGNLOR", "TASSIGNMINUS", "TASSIGNMOD",
  "TASSIGNMULTIPLY", "TASSIGNPLUS", "TASSIGNSL", "TASSIGNSR", "TBAND",
  "TBNOT", "TBOR", "TBXOR", "TCOLON", "TCOMMA", "TDIVIDE", "TDOT",
  "TDOTDOT", "TDOTDOTDOT", "TEQUAL", "TEXP", "TGREATER", "TGREATEREQUAL",
  "THASH", "TLESS", "TLESSEQUAL", "TMINUS", "TMOD", "TNOT", "TNOTEQUAL",
  "TOR", "TPLUS", "TQUESTION", "TSEMI", "TSHIFTLEFT", "TSHIFTRIGHT",
  "TSTAR", "TSWAP", "TASSIGNREDUCE", "TIO", "TLCBR", "TRCBR", "TLP", "TRP",
  "TLSBR", "TRSBR", "TNOELSE", "TUPLUS", "TUMINUS", "$accept", "program",
  "toplevel_stmt_ls", "toplevel_stmt", "pragma_ls", "stmt",
  "module_decl_stmt", "access_control", "block_stmt", "stmt_ls", "only_ls",
  "opt_only_ls", "except_ls", "use_stmt", "require_stmt",
  "assignment_stmt", "opt_ident", "ident", "opt_ident_or_string",
  "do_stmt", "return_stmt", "class_level_stmt", "private_decl",
  "extern_block_stmt", "loop_stmt", "zippered_iterator", "if_stmt",
  "try_stmt", "catch_stmt_ls", "catch_stmt", "catch_expr", "throw_stmt",
  "select_stmt", "when_stmt_ls", "when_stmt", "class_decl_stmt",
  "class_tag", "opt_inherit", "class_level_stmt_ls", "enum_decl_stmt",
  "enum_ls", "enum_item", "lambda_decl_expr", "$@1", "$@2", "linkage_spec",
  "fn_decl_stmt", "$@3", "$@4", "fn_decl_stmt_inner",
  "fn_decl_receiver_expr", "fn_ident", "assignop_ident", "opt_formal_ls",
  "req_formal_ls", "formal_ls", "formal", "opt_intent_tag",
  "required_intent_tag", "opt_this_intent_tag", "proc_or_iter",
  "opt_ret_tag", "opt_throws_error", "opt_function_body_stmt",
  "function_body_stmt", "query_expr", "opt_query_expr", "var_arg_expr",
  "opt_where_part", "type_alias_decl_stmt", "type_alias_decl_stmt_inner",
  "opt_init_type", "var_decl_stmt", "opt_config", "var_decl_stmt_inner_ls",
  "var_decl_stmt_inner", "tuple_var_decl_component",
  "tuple_var_decl_stmt_inner_ls", "opt_init_expr", "opt_reindex_expr",
  "opt_type", "array_type", "opt_formal_array_elt_type",
  "formal_array_type", "opt_formal_type", "expr_ls", "tuple_component",
  "tuple_expr_ls", "opt_actual_ls", "actual_ls", "actual_expr",
  "ident_expr", "type_level_expr", "for_expr", "cond_expr", "nil_expr",
  "stmt_level_expr", "opt_task_intent_ls", "task_intent_clause",
  "task_intent_ls", "forall_intent_clause", "forall_intent_ls",
  "intent_expr", "io_expr", "new_expr", "let_expr", "expr", "lhs_expr",
  "fun_expr", "call_expr", "dot_expr", "parenthesized_expr",
  "literal_expr", "assoc_expr_ls", "binary_op_expr", "unary_op_expr",
  "reduce_expr", "scan_expr", "reduce_scan_op_expr", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398
};
# endif

#define YYPACT_NINF -799

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-799)))

#define YYTABLE_NINF -424

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -799,    85,  2649,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  3745,   -32,    97,  -799,   -32,  7350,    40,    97,  7350,
    3745,    32,    97,   286,   297,  6221,  7350,  7350,    82,  -799,
      97,  -799,    29,  3745,  7350,  7350,  -799,  7350,  7350,   154,
     162,   385,   630,  -799,  6443,  6553,  7350,  6690,  7350,   124,
     166,  3745,  7350,  7460,  7460,    97,  -799,  6443,  7350,  7350,
    -799,  -799,  7350,  -799,  -799,  8560,  7350,  7350,  -799,  7350,
    -799,  -799,  2923,  5889,  6443,  -799,  3608,  -799,  -799,   177,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,    97,  -799,   303,    53,  -799,
    -799,  -799,   267,   187,  -799,  -799,  -799,   211,   221,   182,
     229,   235, 12520,  1571,   273,   251,   259,  -799,  -799,  -799,
    -799,  -799,  -799,   331,  -799, 12520,   277,  3745,  -799,   293,
    -799,   302,  7350,  7350,  7350,  7350,  7350,  6443,  6443,   333,
    -799,  -799,  -799,  -799, 10049,   337,  -799,  -799,    97,   306,
   10244,   334,  6443,   310,  -799,  -799,  -799,  -799,    97,   139,
      97,   288,    47,  9074,  9012,  9198,  6443,  3745,   301,    17,
      75,    34,  -799,  -799,   374,   330,  9265,   374,  -799,  6443,
    -799,   283,  -799,  -799,    97,  -799,    -8, 12520,  -799, 10317,
    9925,  3745,  -799,  -799,  9265, 12520,   313,  6443,  -799, 12520,
   10361,  -799,  -799, 10395,  1644,  -799,  -799, 10439,   361,   335,
     102, 10122,  9265, 10512,   321,  2636,   374,   321,   374,  -799,
    -799,  3060,    -5,  -799,  7350,  -799,    72,    87, 12520,     4,
   10556,   -28,   464,  -799,    97,   369,  -799,  -799,  -799,     9,
      29,    29,    29,  -799,  7350,  7350,  7350,  7350,  6800,  6800,
    7350,  7350,  7350,  7350,  7350,  7350,    71,  8560,  7350,  7350,
    7350,  7350,  7350,  7350,  7350,  7350,  7350,  7350,  7350,  7350,
    7350,  7350,  7350,  7350,  7350,  7350,  7350,  7350,  7350,  7350,
    7350,  7350,  7350,  7350,  7350,  7350,  7350,  7350,  7350,  6443,
    6443,  6800,  6800,  5779,  -799,  -799,  3197,  -799, 10166, 10200,
   10637,    38,  6800,    47,   353,  -799,  -799,  7350,   398,  -799,
     349,   382,  -799, 12520,    97,   365,    97,   460,  6443,  -799,
    3882,  6800,  -799,  4019,  6800,   360,  -799,    47,  3745,   477,
     368,  -799,    56,  -799,  -799,    17,  -799,   399,   373,  -799,
    5227,   419,   423,  7350,    29,  -799,   377,  -799,  -799,  6443,
    -799,  -799,  -799,  -799,  -799,  6443,   378,  -799,   508,  -799,
     508,  -799,  5337,   420,  -799,  -799,  7570,  7350,  -799,  -799,
    -799,  -799,  6331,  -799,  8888,  6001,  -799,  6111,  -799,  6800,
    5447,  2786,   390,  7350,  5667,  -799,  -799,   396,  6443,   397,
     155,    29,   103,   174,   212,   218,  9987, 12630, 12630,   113,
    -799,   113,  -799,   113, 12692,  1275,   502,   781,   330,   321,
    -799,  -799,  -799,  2636,  2302,   113,  1955,  1955, 12630,  1955,
    1955,  1031,   321,  2302, 12659,  1031,   374,   374,   321, 10681,
   10715, 10759, 10832, 10876, 10910, 10954, 11027, 11071, 11105, 11149,
   11222, 11266, 11300, 11344, 11417,   402,   394,  -799,   113,  -799,
     113,   135,  -799,  -799,  -799,  -799,  -799,  -799,    97,   107,
    -799, 12582,   346,  7680,  6800,  7790,  6800,  7350,  6800,  2288,
     -32, 11479,  -799,  -799, 11541,  7350,  6443,  -799,  6443,   446,
      64,  -799,  -799,   369,  7350,   185,  7350, 12520,    50,  9327,
    7350, 12520,    57,  9136,  5779,  -799,   510, 11612,  3745,  -799,
     188,  -799,    35,  -799,   298,   403,    17,    49,  -799,  6443,
    -799,   445,  7350,  6910,  -799, 12520,  -799,  -799,  -799, 12520,
      54,   406,  -799,    97,  -799,  6443,  -799,   271,    97,   421,
     441,   424, 11674,   441,   427,  -799,  -799,  -799,  -799,  -799,
    -799,   -41,  8697,  -799,  -799, 12520,  3745, 12520,  -799, 11736,
    3334,   442,  -799,   495,  -799,  -799,  -799,  -799,  2118,   272,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,  5779,  -799,  6800,  6800,  7350,
     533, 11798,  7350,   534, 11860,   422,  1843,    47,    47,  -799,
   12520,  -799, 12520,  -799,  7350,    97,  -799,   425,  9265,  -799,
    9389,  4156,  -799,  4293,  -799,  9456,  4430,  -799,    47,  4567,
    -799,    47,   192,  -799,  3745,  7350,  -799,   290,  -799,    17,
     453,   503,  -799,  -799,  -799,    66,  -799,  -799,  5337,   423,
      51, 12520,  -799, 12520,  4704,  6443,  -799,  -799,  -799,   461,
     302,    55,  -799,  7350,  -799,  7350,  -799,  4841,   430,  4978,
     431,  -799,  7350,  -799,  3471,  1182,  -799,   298,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,    97,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -799,  -799,  -799,  7350,   468,   471,   438,   438,  -799,
    -799,  -799,   199,   227, 11922,  7900,  8010, 11989,  8120,  8230,
    8340,  8450,  -799,  -799, 12520,  -799,  -799,  -799,  3745,  7350,
   12520,  7350, 12520,  3745,  7350, 12520,  -799,  7350, 12520,  -799,
    5779,  -799,  -799, 12520,  -799,   448,  7020,    16,  -799,   500,
    -799,  6800,  2441,  3745,  -799,    -7,  7350,  -799,  5090, 12056,
   12520,  7350,  -799, 12520,  3745,  7350,  -799, 12520,  3745, 12520,
    -799,   619,   765,   765,  -799,   389,  -799,    24,  -799,  8950,
    2498,    56,  -799,  -799,  7350,  7350,  7350,  7350,  7350,  7350,
    7350,  7350,  1321, 11612,  9523,  9590, 11612,  9657,  9724,  -799,
     453,    32,  7350,  7350,  5557,  -799,  -799,   245,  6443,  -799,
    -799,  7350,    15,  8764,  -799,   521,   334,  -799, 12520,  7350,
    9791,  -799,  9858,  -799,  -799,   513,  -799,  -799,   438,   438,
     238, 12118, 12185, 12252, 12319, 12386, 12453,  -799,  3745,  3745,
    3745,  3745,    16,  7130,    58,  -799,  -799, 12520, 12520,  -799,
    -799,  -799,  8450, 12520,  3745,  3745,  -799,   500,  -799,  -799,
    -799,  7350,  7350,  7350,  7350,  7350,  7350, 11612, 11612, 11612,
   11612,  -799,  -799,  -799,  -799,  -799,   295,  6800,  8646,   798,
   11612, 11612,    74,  8826,  -799,  -799,  -799,  -799,  -799,  7240,
    -799
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       3,     0,     0,     1,    36,    76,   416,   417,   418,   419,
     420,     0,   371,    74,   141,   371,     0,   272,    74,     0,
       0,     0,     0,    74,    74,     0,     0,     0,     0,   159,
       0,   155,     0,     0,     0,     0,   362,     0,     0,     0,
       0,   271,   271,   142,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   143,     0,     0,     0,
     468,   470,     0,   471,   472,   399,     0,     0,   469,   466,
      83,   467,     0,     0,     0,     4,     0,     5,     9,     0,
      10,    11,    12,    14,   331,    21,    13,    84,    15,    17,
      16,    19,    20,    18,    89,     0,    87,   391,     0,    90,
      88,    91,     0,   400,   387,   388,   334,   332,     0,     0,
     392,   393,     0,   333,     0,   401,   402,   403,   386,   336,
     335,   389,   390,     0,    23,   342,     0,     0,   372,     0,
      75,     0,     0,     0,     0,     0,     0,     0,     0,   391,
     400,   332,   392,   393,   371,   333,   401,   402,     0,     0,
       0,     0,   322,     0,    78,    77,   160,    92,     0,   161,
       0,     0,     0,     0,     0,     0,   322,     0,     0,     0,
       0,     0,   274,    30,   454,   384,     0,   455,     7,   322,
     272,   273,    86,    85,   251,   314,     0,   313,    81,     0,
       0,     0,    80,    33,     0,   337,     0,   322,    34,   343,
       0,   126,   122,     0,   333,   126,   123,     0,   263,     0,
       0,   313,     0,     0,   457,   398,   453,   456,   452,    42,
      44,     0,     0,   317,     0,   319,     0,     0,   318,     0,
     313,     0,     0,     6,     0,   144,   237,   236,   162,     0,
       0,     0,     0,    22,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   397,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   322,
     322,     0,     0,     0,    24,    25,     0,    26,     0,     0,
       0,     0,     0,     0,     0,    27,    28,     0,   331,   329,
       0,   323,   324,   330,     0,     0,     0,     0,     0,   101,
       0,     0,   100,     0,     0,     0,   107,     0,     0,   117,
       0,    29,   212,   156,   279,     0,   280,   282,     0,   293,
       0,     0,   285,     0,     0,    31,     0,   161,   250,     0,
      57,    82,   134,    79,    32,   322,     0,   132,   124,   120,
     125,   121,     0,   261,   258,    54,     0,    50,    94,    35,
      43,    45,     0,   421,     0,     0,   412,     0,   414,     0,
       0,     0,     0,     0,     0,   425,     8,     0,     0,     0,
     230,     0,     0,     0,     0,     0,   370,   449,   448,   451,
     459,   458,   463,   462,   445,   442,   443,   444,   395,   432,
     411,   410,   409,   396,   436,   447,   441,   439,   450,   440,
     438,   430,   435,   437,   446,   429,   433,   434,   431,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   461,   460,   465,
     464,   224,   221,   222,   223,   227,   228,   229,     0,     0,
     374,     0,     0,     0,     0,     0,     0,     0,     0,   423,
     371,   371,    97,   259,     0,     0,     0,   339,     0,   153,
       0,   150,   260,   144,     0,     0,     0,   346,     0,     0,
       0,   352,     0,     0,     0,   108,   116,     0,     0,   338,
       0,   213,     0,   220,   238,     0,   283,     0,   297,     0,
     292,   387,     0,     0,   276,   385,   275,   408,   316,   315,
       0,     0,   340,   129,   127,     0,   265,   387,     0,   467,
      53,     0,    46,    51,     0,   422,   394,   413,   320,   415,
     321,     0,     0,   424,   113,   356,     0,   427,   426,     0,
       0,   145,   146,   234,   231,   232,   235,   163,     0,     0,
     267,   266,   268,   270,    58,    65,    66,    67,    62,    64,
      72,    73,    60,    63,    61,    59,    69,    68,    70,    71,
     406,   407,   225,   226,   379,     0,   373,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    93,
     328,   326,   327,   325,     0,   151,   149,     0,     0,   115,
       0,     0,    99,     0,    98,     0,     0,   105,     0,     0,
     103,     0,     0,   377,     0,     0,   119,   219,   211,     0,
     306,   239,   242,   241,   243,     0,   281,   284,     0,   285,
       0,   277,   286,   287,     0,     0,   133,   135,   341,   130,
       0,     0,   262,     0,    55,     0,    56,     0,     0,     0,
       0,   114,     0,    37,     0,   271,   233,   238,   194,   192,
     197,   204,   205,   206,   201,   203,   199,   202,   200,   198,
     208,   207,   173,   176,   174,   175,   186,   177,   190,   182,
     180,   193,   181,   179,   184,   189,   191,   178,   183,   187,
     188,   185,   195,   196,     0,   171,     0,   209,   209,   169,
     269,   375,   400,   400,     0,     0,     0,     0,     0,     0,
       0,     0,    96,    95,   154,   152,   146,   102,     0,     0,
     345,     0,   344,     0,     0,   351,   106,     0,   350,   104,
       0,   376,   118,   361,   214,     0,     0,   285,   240,   256,
     278,     0,     0,     0,   137,     0,     0,   128,     0,    48,
      47,     0,   111,   358,     0,     0,   109,   357,     0,   428,
      38,    74,   271,   271,   139,   271,   147,     0,   172,     0,
       0,   212,   165,   166,     0,     0,     0,     0,     0,     0,
       0,     0,   271,   349,     0,     0,   355,     0,     0,   378,
     306,   309,   310,   311,     0,   308,   312,   387,   252,   216,
     215,     0,     0,     0,   295,   387,   138,   136,   131,     0,
       0,   112,     0,   110,   148,   244,   170,   171,   209,   209,
       0,     0,     0,     0,     0,     0,     0,   140,     0,     0,
       0,     0,   285,   298,     0,   253,   255,   254,   257,   248,
     249,   157,     0,    49,     0,     0,   245,   256,   167,   168,
     210,     0,     0,     0,     0,     0,     0,   348,   347,   354,
     353,   218,   217,   300,   301,   303,   387,     0,   423,   387,
     360,   359,     0,     0,   302,   304,   246,   164,   247,   298,
     305
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -799,  -799,  -799,    -1,  -605,  1880,  -799,  -799,  1521,    39,
     225,  -799,  -799,  -799,  -799,   153,   375,  1871,   -10,   -98,
    -729,  -613,   -39,  -799,  -799,   299,  -799,  -799,   383,  -799,
    -799,  -799,  -799,  -799,  -799,  -799,   435,   114,  -130,  -799,
    -799,    -6,   750,  -799,  -799,  -799,  -799,  -799,  -799,  -799,
    -799,  -182,  -177,  -640,  -799,  -174,   -12,  -799,  -322,  -799,
    -799,   -51,  -799,  -799,  -261,   387,  -799,  -217,  -229,  -799,
    -139,  -799,  -799,  -799,  -211,   285,  -799,  -331,  -628,  -799,
    -490,  -355,  -674,  -798,  -165,    13,   115,  -799,   -63,  -799,
     158,   351,  -225,  -799,  -799,   873,  -799,    -9,  -799,  -799,
    -208,  -799,  -445,  -799,   954,   996,   -11,   492,  -799,  1146,
    1430,  -799,  -799,  -799,  -799,  -799,  -799,  -799,  -271
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,   220,    76,   496,    78,    79,    80,   221,
     530,   534,   531,    81,    82,    83,   155,    84,   159,   193,
      85,    86,    87,    88,    89,   595,    90,    91,   358,   524,
     650,    92,    93,   520,   647,    94,    95,   389,   665,    96,
     480,   481,   139,   168,   504,    98,    99,   390,   667,   557,
     706,   707,   708,   782,   333,   500,   501,   502,   458,   558,
     238,   635,   857,   887,   851,   185,   846,   809,   812,   100,
     209,   363,   101,   102,   171,   172,   337,   338,   514,   341,
     342,   510,   874,   806,   747,   222,   226,   227,   310,   311,
     312,   140,   104,   105,   106,   141,   108,   127,   128,   459,
     327,   622,   460,   109,   142,   143,   112,   145,   114,   146,
     147,   117,   118,   231,   119,   120,   121,   122,   123
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     125,    75,   182,   183,   505,   144,   131,   526,   150,   304,
     503,   750,     5,   156,   163,   164,   165,   639,   191,   315,
       5,   382,   462,   174,   175,   339,   176,   177,   392,   393,
     394,   395,     5,   187,   189,   190,   194,   195,     5,   379,
     199,   200,   203,   207,   325,   875,   211,   212,   213,   623,
     339,   214,   776,   126,   215,   216,   217,   186,   218,  -219,
     775,   187,   228,   230,   319,   322,   326,   339,   783,   343,
     210,   391,   191,   468,     5,   611,   339,   451,   345,    45,
     885,   384,   616,   850,  -290,     3,   751,   229,  -290,   325,
     751,   452,   236,   877,   453,   334,   354,   410,  -290,   657,
       5,   349,   349,   330,   372,   644,   513,  -290,   454,   455,
    -290,   237,   385,   380,   368,   511,   346,   148,   456,   810,
     350,   125,   298,   299,   300,   199,   187,   230,   296,   808,
    -290,   373,   638,   457,   356,   303,   645,   527,    45,  -290,
     711,   313,   325,   344,   381,   749,   169,   380,   411,  -290,
     296,   301,  -290,   850,   335,   313,    14,   638,  -290,  -290,
     380,   178,   824,  -288,   380,  -290,   169,   380,   313,   152,
     582,   347,   629,   605,   638,   637,   553,  -290,   469,   776,
     559,   375,   296,   340,  -290,   296,   313,   775,   858,   859,
     646,   752,   296,  -219,   196,   758,   377,   583,   878,    43,
     606,  -290,   886,  -290,   884,   472,   202,   206,   554,   296,
     376,   349,   344,   374,   872,   890,   585,   555,    56,   166,
     371,   254,   234,   462,   256,   378,   445,   446,   259,   495,
     365,   560,   556,   396,   397,   398,   399,   401,   403,   404,
     405,   406,   407,   408,   409,   586,   413,   414,   415,   416,
     417,   418,   419,   420,   421,   422,   423,   424,   425,   426,
     427,   428,   429,   430,   431,   432,   433,   434,   435,   436,
     437,   438,   439,   440,   441,   442,   443,   444,   313,   313,
     448,   450,   461,   344,   618,   621,     5,   825,   239,     5,
     154,   471,   521,   154,   349,   799,   474,   627,   745,   179,
       5,   740,   561,   197,   154,   503,   157,   187,  -380,   487,
     489,   451,   491,   493,   462,  -364,   244,   497,  -273,   631,
     240,   344,   -74,   609,   162,   452,   628,   344,   453,   241,
     741,   485,   515,   658,   660,  -307,  -381,  -380,   519,  -363,
     562,   -74,   454,   455,   313,   247,   563,   627,   242,   243,
    -273,   632,   456,   103,  -307,   532,   532,  -368,  -307,  -273,
     633,   519,   103,  -369,   228,  -381,   228,   457,   542,   519,
     545,   103,   547,   549,   158,   634,   860,   187,  -273,  -366,
    -264,   344,   248,  -307,   103,  -299,   249,  -365,   129,   652,
     612,   614,   291,   149,   617,   620,   292,   814,   247,  -264,
     710,   551,   103,   814,  -299,   180,    14,   588,  -299,    17,
     289,   292,   290,   511,   293,    23,   181,    22,   307,    23,
     771,   295,    29,   103,  -158,   318,    29,   103,  -158,   254,
     -41,  -367,   256,  -299,   305,   248,   259,   296,   332,   249,
    -405,   256,  -405,  -158,   232,   314,   772,  -158,   773,    43,
     355,   362,   487,   591,   491,   594,   497,   596,   545,   503,
     225,   597,   598,   364,   600,   602,    55,   313,    56,   462,
    -405,   386,  -405,   608,  -404,   610,  -404,   388,   103,   615,
    -291,   473,   254,   461,   255,   256,   475,   477,   476,   259,
     538,   478,   540,   482,   113,   484,   266,   494,   230,   722,
     723,   641,   643,   113,   498,   272,   499,   512,   506,  -291,
     727,   507,   113,   513,   230,   517,   522,    70,   103,  -291,
     736,   807,   640,   739,   523,   113,   247,   815,  -291,   528,
     546,   550,   552,   815,   581,  -291,   604,   624,   651,   309,
     580,   636,   103,   113,   648,   204,   204,   400,   402,   -52,
     653,   349,   654,   309,  -291,   656,  -294,   666,   715,   718,
     726,   746,   720,   248,   113,   748,   309,   249,   113,   756,
     764,   768,   103,  -291,   461,   781,   401,   448,   714,  -331,
    -291,   717,   780,   811,   309,  -294,   800,   856,   360,   664,
     447,   449,   533,   724,   316,  -294,   792,   607,   828,   725,
     730,   470,   732,   829,  -294,   735,   251,   830,   738,   253,
     254,  -294,   255,   256,   743,   744,   777,   259,   876,   113,
     488,   888,     5,   492,   266,   871,   154,   879,   882,   516,
    -294,   270,   271,   272,   187,   842,   603,     0,     0,     0,
    -273,     0,   759,     0,   760,     0,   763,   103,   767,  -294,
     180,   769,     0,   876,     0,     0,  -294,   817,   755,   113,
      23,   181,     0,   371,   876,     0,     0,    29,     0,  -158,
       0,   103,  -273,     0,   103,   -40,   309,   309,   541,   103,
       0,  -273,     0,   113,     0,     0,     0,     0,  -158,     0,
       0,     0,     0,   779,     0,     0,   158,     0,     0,     0,
    -273,     0,     0,     0,   730,   732,     0,   735,   738,   763,
     767,     0,     0,   113,     0,     0,     0,   793,   794,     0,
     795,     0,   796,   797,     0,     0,   798,     0,     0,   461,
       0,     0,   103,   182,   183,     0,   518,     0,     0,     0,
     813,   545,   309,     0,     0,   818,     0,   545,     0,     0,
     820,     0,    97,     0,   822,     0,     0,     0,     0,   518,
       0,    97,   225,   590,   225,   593,     0,   518,     0,     0,
      97,     0,     0,   793,   831,   832,   796,   833,   834,   835,
     836,     0,     0,    97,     0,   180,     0,     0,   113,     0,
       0,   195,   199,   230,     0,    23,   181,   847,     0,     0,
     848,    97,    29,     0,  -158,   247,     0,     0,   853,   584,
       0,     0,   113,     0,     0,   113,     0,   844,     0,     0,
     113,     0,    97,  -158,     0,     0,    97,   867,   868,   869,
     870,     0,     0,  -296,     0,     0,     0,     0,     0,     0,
       0,   767,   248,   880,   881,     0,   249,     0,     0,   103,
     867,   868,   869,   870,   880,   881,     0,     0,     0,     0,
       0,     0,  -296,   601,     0,   309,   883,   545,     0,     0,
       0,     0,  -296,   113,     0,   107,     0,    97,   767,     0,
       0,  -296,     0,     0,   107,   251,   400,   447,  -296,   254,
       0,   255,   256,   107,     0,     0,   259,   103,     0,     0,
       0,   103,     0,   266,     0,     0,   107,  -296,     0,   709,
     270,   271,   272,     0,     0,     0,     0,    97,     0,     0,
       0,     0,     0,     0,   107,     0,  -296,     0,     0,     0,
       0,     0,     0,  -296,     0,     0,     0,     0,   712,   713,
       0,    97,     0,     0,     0,   107,     0,     0,     0,   107,
       0,     0,     0,     0,     0,     0,   110,     0,     0,     0,
       0,     0,   103,     0,   103,   110,     0,   103,     0,     0,
     103,    97,     0,     0,   110,   103,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   110,     0,     0,
     113,     0,     0,     0,     0,   103,     0,     0,   111,     0,
     107,     0,     0,     0,     0,   110,     0,   111,   103,     0,
     103,     0,     0,     0,     0,   103,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   110,     0,     0,   111,
     110,     0,     0,     0,     0,     0,     0,     0,   113,     0,
     107,     0,   113,     0,     0,     0,    97,   111,     0,     0,
       0,     0,     0,     0,     0,   247,     0,     0,     0,     0,
       0,     0,     0,     0,   107,     0,     0,     0,   111,     0,
      97,     0,   111,    97,     0,     0,     0,     0,    97,   103,
       0,   110,     0,     0,   103,     0,     0,     0,     0,     0,
       0,     0,   248,     0,   107,     0,   249,     0,     0,     0,
       0,     0,     0,   113,   103,   113,     0,     0,   113,     0,
       0,   113,     0,     0,     0,   103,   113,     0,     0,   103,
       0,   110,     0,   111,     0,     0,     0,     0,     0,     0,
       0,    97,     0,   805,     0,   251,   113,   252,   253,   254,
       0,   255,   256,     0,     0,   110,   259,     0,   115,   113,
       0,   113,     0,   266,     0,     0,   113,   115,     0,     0,
     270,   271,   272,   111,     0,     0,   115,     0,     0,   107,
       0,     0,     0,     0,     0,   110,     0,     0,     0,   115,
       0,     0,     0,     0,     0,     0,     0,   111,     0,   103,
     103,   103,   103,   107,     0,   845,   107,   115,     0,    14,
       0,   107,    17,     0,     0,   103,   103,     0,     0,     0,
      22,     0,    23,   771,     0,     0,     0,   111,   115,    29,
     113,  -158,   115,     0,     0,   113,     0,     0,     0,     0,
     873,     0,     0,     0,     0,     0,     0,    39,     0,   772,
    -158,   773,    43,     0,     0,   113,     0,     0,    97,     0,
     110,     0,     0,     0,   107,     0,   113,     0,     0,    55,
     113,    56,     0,     0,     0,   873,     0,     0,     0,     0,
       0,     0,     0,   115,   110,     0,   873,   110,     0,     0,
       0,     0,   110,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   111,     0,     0,     0,    97,     0,     0,   247,
      97,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      70,     0,     0,   115,     0,     0,   111,     0,   774,   111,
       0,     0,     0,     0,   111,     0,     0,     0,     0,     0,
     113,   113,   113,   113,     0,   110,   248,   115,    14,     0,
     249,    17,     0,     0,     0,     0,   113,   113,     0,    22,
       0,    23,   771,     0,     0,     0,     0,     0,    29,     0,
    -158,    97,     0,    97,     0,     0,    97,   115,     0,    97,
       0,   107,     0,     0,    97,     0,    39,   111,   772,  -158,
     773,    43,     0,   254,     0,   255,   256,     0,     0,     0,
     259,     0,     0,     0,    97,     0,     0,   266,    55,     0,
      56,     0,     0,     0,   270,   271,   272,    97,     0,    97,
       0,     0,     0,     0,    97,     0,     0,     0,     0,   107,
       0,     0,     0,   107,     0,     0,     0,     0,     0,     0,
       0,     0,   116,     0,     0,     0,     0,     0,     0,     0,
       0,   116,   115,     0,     0,     0,     0,     0,     0,    70,
     116,     0,   110,     0,     0,     0,     0,   837,     0,     0,
       0,     0,     0,   116,     0,     0,   115,     0,     0,   115,
       0,     0,     0,     0,   115,     0,     0,     0,    97,     0,
       0,   116,     0,    97,   107,     0,   107,     0,     0,   107,
       0,     0,   107,     0,   111,     0,     0,   107,     0,     0,
     110,     0,   116,    97,   110,     0,   116,     0,     0,     0,
       0,     0,     0,     0,    97,     0,     0,   107,    97,     0,
       0,     0,     0,     0,     0,     0,     0,   115,     0,     0,
     107,     0,   107,     0,     0,     0,     0,   107,     0,     0,
       0,     0,   111,     0,     0,     0,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   116,     0,     0,
       0,     0,     0,     0,     0,   110,     0,   110,   192,     0,
     110,     0,     0,   110,   201,   205,     0,     0,   110,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    97,    97,
      97,    97,     0,     0,     0,     0,     0,   116,   110,     0,
       0,   107,     0,     0,    97,    97,   107,   111,     0,   111,
       0,   110,   111,   110,     0,   111,     0,     0,   110,     0,
     111,   116,     0,     0,     0,     0,   107,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   107,     0,     0,
     111,   107,     0,     0,   115,     0,     0,     0,     0,     0,
       0,   116,   297,   111,     0,   111,     0,     0,     0,     0,
     111,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,     0,     0,     0,     0,     0,
       0,     0,   110,   192,   192,   192,   329,   110,     0,     0,
       0,     0,   115,     0,     0,     0,   115,   192,     0,     0,
       0,     0,     0,   287,   288,  -382,     0,   110,  -404,     0,
    -404,   107,   107,   107,   107,   192,     0,     0,   110,     0,
       0,     0,   110,     0,   111,     0,   116,   107,   107,   111,
       0,     0,     0,   192,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,     0,   111,
     116,     0,     0,   116,     0,     0,     0,   115,   116,   115,
     111,     0,   115,     0,   111,   115,     0,     0,     0,     0,
     115,     0,     0,     0,     0,     0,   287,   288,     0,     0,
       0,  -404,     0,  -404,     0,     0,     0,     0,     0,     0,
     115,     0,   110,   110,   110,   110,     0,     0,     0,     0,
       0,     0,     0,   115,     0,   115,     0,     0,   110,   110,
     115,   116,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   192,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   111,   111,   111,   111,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   192,     0,
     111,   111,     0,   245,     0,     0,     0,     0,   246,     0,
       0,     0,     0,     0,     0,     0,     0,   247,     0,     0,
       0,     0,     0,     0,   115,     0,     0,     0,     0,   115,
       0,     0,    77,     0,   130,     0,     0,     0,     0,   130,
       0,   124,     0,   153,   130,   130,     0,     0,     0,   115,
     151,   167,     0,   170,   248,     0,     0,     0,   249,     0,
     115,     0,     0,   173,   115,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   208,     0,   116,     0,
       0,   198,   250,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   251,     0,   252,
     253,   254,    77,   255,   256,   257,   233,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   235,   267,   268,   269,
       0,     0,   270,   271,   272,     0,   116,     0,     0,   247,
     116,     0,     0,   721,   115,   115,   115,   115,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     115,   115,     0,     0,     0,     0,     0,   294,     0,   192,
     192,     0,     0,   192,   192,     0,   248,     0,     0,   208,
     249,     0,     0,   308,     0,     0,     0,     0,     0,   208,
       0,   317,     0,     0,     0,     0,     0,   308,     0,     0,
     336,   116,     0,   116,     0,     0,   116,   331,     0,   116,
     308,     0,   130,     0,   116,   348,     0,     0,     0,   251,
       0,   252,   253,   254,     0,   255,   256,   257,   308,     0,
     259,   353,     0,     0,   116,     0,   265,   266,     0,     0,
       0,   269,     0,     0,   270,   271,   272,   116,     0,   116,
       0,     0,     0,     0,   116,     0,     0,     0,     0,     0,
       0,    77,     0,     0,     0,   387,     0,     0,     0,     0,
     170,   170,   170,   170,     0,     0,     0,     0,   192,   192,
       0,     5,     0,     0,     0,     0,     0,   412,   668,   192,
       0,   329,     0,   669,     0,     0,   329,     0,     0,   192,
       0,     0,   192,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   116,     0,
     308,   308,     0,   116,     0,     0,     0,     0,     0,     0,
       0,   757,     0,     0,     0,     0,    77,     0,     0,     0,
       0,     0,     0,   116,     0,   479,     0,   483,     0,     0,
       0,     0,     0,     0,   116,     0,     0,     0,   116,     0,
     353,     0,     0,   353,     0,     0,   336,     0,   670,   671,
     672,   673,   674,   675,     0,   170,   676,   677,   678,   679,
     680,   681,   682,   683,   684,   685,   308,     0,   686,     0,
       0,     0,   687,   688,   689,   690,   691,   692,   693,   694,
     695,   696,   697,     0,   698,     0,     0,   699,   700,   701,
     702,     0,   703,     0,     0,   704,     0,     0,     0,     0,
       0,   544,   170,     0,     0,     0,     0,     0,   116,   116,
     116,   116,     0,     0,     0,     0,   192,     0,     0,     0,
       0,     0,     0,     0,   116,   116,     0,     0,     0,     0,
       0,     5,     6,     7,     8,     9,    10,     0,     0,     0,
     132,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    21,   329,   329,     0,   329,   329,
     133,   134,   135,     0,    28,     0,   247,     0,     0,    31,
      32,     0,    34,   849,    35,    36,     0,     0,     0,     0,
       0,   329,    38,   329,    40,     0,     0,     0,     0,   308,
       0,     0,     0,     0,     0,     0,    48,    49,    50,   136,
       0,     0,     0,   248,     0,     0,     0,   249,     0,     0,
       0,     0,     0,   630,     0,     0,     0,   336,   626,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    62,   649,     0,     0,     0,     0,   208,
       0,     0,     0,   849,     0,     0,   251,     0,   252,   253,
     254,    67,   255,   256,   257,     0,     0,   259,   260,   261,
       0,   263,   264,   265,   266,    73,   661,   138,   269,   705,
      77,   270,   271,   272,     0,     0,     0,     0,     0,     0,
       0,     0,   508,     0,     5,     6,     7,     8,     9,    10,
       0,  -423,     0,   132,     0,     0,  -423,     0,     0,     0,
       0,     0,     0,     0,     0,  -423,     0,    21,     0,     0,
       0,     0,     0,   133,   134,   135,   479,    28,     0,     0,
       0,     0,    31,    32,     0,    34,     0,    35,    36,     0,
       0,   353,     0,   353,     0,    38,   353,    40,     0,   353,
     336,     5,  -423,     0,   742,     0,  -423,     0,   668,    48,
      49,    50,   136,   669,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   754,     0,     0,     0,     0,  -289,
    -423,     0,     0,     0,     0,     0,     0,   762,     0,   766,
       0,     0,     0,     0,    77,  -423,    62,  -423,  -423,  -423,
       0,  -423,  -423,  -423,   778,  -423,  -423,  -423,  -423,  -423,
    -423,  -423,  -423,  -423,    67,  -423,  -423,  -423,     0,     0,
    -423,  -423,  -423,     0,     0,     0,   137,     0,    73,     0,
     525,     0,     0,     0,     0,     0,     0,     0,   670,   671,
     672,   673,   674,   675,     0,     0,   676,   677,   678,   679,
     680,   681,   682,   683,   684,   685,     0,     0,   686,     0,
       0,     0,   687,   688,   689,   690,   691,   692,   693,   694,
     695,   696,   697,     0,   698,     0,     0,   699,   700,   701,
     702,     0,   703,   816,     0,     0,     0,     0,     0,     0,
       0,     0,   130,     0,   821,     0,     0,     0,   823,    -2,
       4,   827,     5,     6,     7,     8,     9,    10,     0,     0,
     247,    11,    12,    13,     0,     0,    14,    15,    16,    17,
    -271,    18,    19,     0,    20,    21,     0,    22,     0,    23,
      24,    25,    26,    27,     0,    28,    29,     0,  -158,    30,
      31,    32,    33,    34,   -39,    35,    36,   248,    37,     0,
       0,   249,  -271,    38,    39,    40,    41,  -158,    42,    43,
       0,  -271,    44,    45,     0,    46,    47,    48,    49,    50,
      51,     0,    52,     0,    53,    54,    55,     0,    56,    57,
    -271,     0,     0,    58,     0,    59,     0,     0,    60,     0,
     251,     0,   252,   253,   254,     0,   255,   256,     0,     0,
       0,   259,     0,    61,    62,    63,    64,   265,   266,     0,
       0,    65,   269,     0,     0,   270,   271,   272,     0,     0,
      66,     0,    67,     0,    68,    69,     0,    70,     0,     0,
      71,     0,     0,     0,    72,     0,    73,     4,    74,     5,
       6,     7,     8,     9,    10,     0,  -423,     0,    11,    12,
      13,  -423,     0,    14,    15,    16,    17,  -271,    18,    19,
    -423,    20,    21,  -423,    22,     0,    23,    24,    25,    26,
      27,     0,    28,    29,     0,  -158,    30,    31,    32,    33,
      34,   -39,    35,    36,     0,    37,     0,     0,     0,  -271,
      38,     0,    40,    41,  -158,    42,    43,  -423,  -271,    44,
      45,  -423,    46,    47,    48,    49,    50,    51,     0,    52,
       0,    53,    54,    55,     0,    56,    57,  -271,     0,     0,
      58,     0,    59,     0,     0,  -423,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -423,    62,  -423,  -423,  -423,  -423,  -423,  -423,  -423,     0,
    -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,    67,
    -423,  -423,  -423,     0,    70,  -423,  -423,  -423,     0,     0,
       0,    72,  -423,    73,     4,    74,     5,     6,     7,     8,
       9,    10,     0,     0,     0,    11,    12,    13,     0,     0,
      14,    15,    16,    17,  -271,    18,    19,     0,    20,    21,
       0,    22,     0,    23,    24,    25,    26,    27,     0,    28,
      29,     0,  -158,    30,    31,    32,    33,    34,   -39,    35,
      36,     0,    37,     0,     0,     0,  -271,    38,    39,    40,
      41,  -158,    42,    43,     0,  -271,    44,    45,     0,    46,
      47,    48,    49,    50,    51,     0,    52,     0,    53,    54,
      55,     0,    56,    57,  -271,     0,     0,    58,     0,    59,
       0,     0,    60,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    61,    62,    63,
      64,     0,     0,     0,     0,    65,     0,     0,     0,     0,
       0,     0,     0,     0,    66,     0,    67,     0,    68,    69,
     184,    70,     0,     0,    71,     0,     0,     0,    72,   219,
      73,     4,    74,     5,     6,     7,     8,     9,    10,     0,
       0,     0,    11,    12,    13,     0,     0,    14,    15,    16,
      17,  -271,    18,    19,     0,    20,    21,     0,    22,     0,
      23,    24,    25,    26,    27,     0,    28,    29,     0,  -158,
      30,    31,    32,    33,    34,   -39,    35,    36,     0,    37,
       0,     0,     0,  -271,    38,    39,    40,    41,  -158,    42,
      43,     0,  -271,    44,    45,     0,    46,    47,    48,    49,
      50,    51,     0,    52,     0,    53,    54,    55,     0,    56,
      57,  -271,     0,     0,    58,     0,    59,     0,     0,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,    62,    63,    64,     0,     0,
       0,     0,    65,     0,     0,     0,     0,     0,     0,     0,
       0,    66,     0,    67,     0,    68,    69,     0,    70,     0,
       0,    71,     0,     0,     0,    72,   370,    73,     4,    74,
       5,     6,     7,     8,     9,    10,     0,     0,     0,    11,
      12,    13,     0,     0,    14,    15,    16,    17,  -271,    18,
      19,     0,    20,    21,     0,    22,     0,    23,    24,    25,
      26,    27,     0,    28,    29,     0,  -158,    30,    31,    32,
      33,    34,   -39,    35,    36,     0,    37,     0,     0,     0,
    -271,    38,    39,    40,    41,  -158,    42,    43,     0,  -271,
      44,    45,     0,    46,    47,    48,    49,    50,    51,     0,
      52,     0,    53,    54,    55,     0,    56,    57,  -271,     0,
       0,    58,     0,    59,     0,     0,    60,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    61,    62,    63,    64,     0,     0,     0,     0,    65,
       0,     0,     0,     0,     0,     0,     0,     0,    66,     0,
      67,     0,    68,    69,     0,    70,     0,     0,    71,     0,
       0,     0,    72,   219,    73,     4,    74,     5,     6,     7,
       8,     9,    10,     0,     0,     0,    11,    12,    13,     0,
       0,    14,    15,    16,    17,  -271,    18,    19,     0,    20,
      21,     0,    22,     0,    23,    24,    25,    26,    27,     0,
      28,    29,     0,  -158,    30,    31,    32,    33,    34,   -39,
      35,    36,     0,    37,     0,     0,     0,  -271,    38,    39,
      40,    41,  -158,    42,    43,     0,  -271,    44,    45,     0,
      46,    47,    48,    49,    50,    51,     0,    52,     0,    53,
      54,    55,     0,    56,    57,  -271,     0,     0,    58,     0,
      59,     0,     0,    60,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    61,    62,
      63,    64,     0,     0,     0,     0,    65,     0,     0,     0,
       0,     0,     0,     0,     0,    66,     0,    67,     0,    68,
      69,     0,    70,     0,     0,    71,     0,     0,     0,    72,
     663,    73,     4,    74,     5,     6,     7,     8,     9,    10,
       0,     0,     0,    11,    12,    13,     0,     0,    14,    15,
      16,    17,  -271,    18,    19,     0,    20,    21,     0,    22,
       0,    23,    24,    25,    26,    27,     0,    28,    29,     0,
    -158,    30,    31,    32,    33,    34,   -39,    35,    36,     0,
      37,     0,     0,     0,  -271,    38,    39,    40,    41,  -158,
      42,    43,     0,  -271,    44,    45,     0,    46,    47,    48,
      49,    50,    51,     0,    52,     0,    53,    54,    55,     0,
      56,    57,  -271,     0,     0,    58,     0,    59,     0,     0,
      60,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    61,    62,    63,    64,     0,
       0,     0,     0,    65,     0,     0,     0,     0,     0,     0,
       0,     0,    66,     0,    67,     0,    68,    69,     0,    70,
       0,     0,    71,     0,     0,     0,    72,   770,    73,     4,
      74,     5,     6,     7,     8,     9,    10,     0,     0,     0,
      11,    12,    13,     0,     0,    14,    15,    16,    17,  -271,
      18,    19,     0,    20,    21,     0,    22,     0,    23,    24,
      25,    26,    27,     0,    28,    29,     0,  -158,    30,    31,
      32,    33,    34,   -39,    35,    36,     0,    37,     0,     0,
       0,  -271,    38,   232,    40,    41,  -158,    42,    43,     0,
    -271,    44,    45,     0,    46,    47,    48,    49,    50,    51,
       0,    52,     0,    53,    54,    55,     0,    56,    57,  -271,
       0,     0,    58,     0,    59,     0,     0,    60,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    61,    62,    63,    64,     0,     0,     0,     0,
      65,     0,     0,     0,     0,     0,     0,     0,     0,    66,
       0,    67,     0,    68,    69,     0,    70,     0,     0,    71,
       0,     0,     0,    72,     0,    73,     4,    74,     5,     6,
       7,     8,     9,    10,     0,     0,     0,    11,    12,    13,
       0,     0,    14,    15,    16,    17,  -271,    18,    19,     0,
      20,    21,     0,    22,     0,    23,    24,    25,    26,    27,
       0,    28,    29,     0,  -158,    30,    31,    32,    33,    34,
     -39,    35,    36,     0,    37,     0,     0,     0,  -271,    38,
       0,    40,    41,  -158,    42,    43,     0,  -271,    44,    45,
       0,    46,    47,    48,    49,    50,    51,     0,    52,     0,
      53,    54,    55,     0,    56,    57,  -271,     0,     0,    58,
       0,    59,     0,     0,    60,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    61,
      62,    63,    64,     0,     0,     0,     0,    65,     0,     0,
       0,     0,     0,     0,     0,     0,    66,     0,    67,     0,
      68,    69,     0,    70,     0,     0,    71,     0,     0,     0,
      72,     0,    73,     4,    74,     5,     6,     7,     8,     9,
      10,     0,     0,     0,    11,    12,    13,     0,     0,    14,
      15,    16,    17,  -271,    18,    19,     0,    20,    21,     0,
      22,     0,    23,    24,    25,    26,   486,     0,    28,    29,
       0,  -158,    30,    31,    32,    33,    34,   -39,    35,    36,
       0,    37,     0,     0,     0,  -271,    38,     0,    40,    41,
    -158,    42,    43,     0,  -271,    44,    45,     0,    46,    47,
      48,    49,    50,    51,     0,    52,     0,    53,    54,    55,
       0,    56,    57,  -271,     0,     0,    58,     0,    59,     0,
       0,    60,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    61,    62,    63,    64,
       0,     0,     0,     0,    65,     0,     0,     0,     0,     0,
       0,     0,     0,    66,     0,    67,     0,    68,    69,     0,
      70,     0,     0,    71,     0,     0,     0,    72,     0,    73,
       4,    74,     5,     6,     7,     8,     9,    10,     0,     0,
       0,    11,    12,    13,     0,     0,    14,    15,    16,    17,
    -271,    18,    19,     0,    20,    21,     0,    22,     0,    23,
      24,    25,    26,   490,     0,    28,    29,     0,  -158,    30,
      31,    32,    33,    34,   -39,    35,    36,     0,    37,     0,
       0,     0,  -271,    38,     0,    40,    41,  -158,    42,    43,
       0,  -271,    44,    45,     0,    46,    47,    48,    49,    50,
      51,     0,    52,     0,    53,    54,    55,     0,    56,    57,
    -271,     0,     0,    58,     0,    59,     0,     0,    60,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    61,    62,    63,    64,     0,     0,     0,
       0,    65,     0,     0,     0,     0,     0,     0,     0,     0,
      66,     0,    67,     0,    68,    69,     0,    70,     0,     0,
      71,     0,     0,     0,    72,     0,    73,     4,    74,     5,
       6,     7,     8,     9,    10,     0,     0,     0,    11,    12,
      13,     0,     0,    14,    15,    16,    17,  -271,    18,    19,
       0,    20,    21,     0,    22,     0,    23,    24,    25,    26,
     729,     0,    28,    29,     0,  -158,    30,    31,    32,    33,
      34,   -39,    35,    36,     0,    37,     0,     0,     0,  -271,
      38,     0,    40,    41,  -158,    42,    43,     0,  -271,    44,
      45,     0,    46,    47,    48,    49,    50,    51,     0,    52,
       0,    53,    54,    55,     0,    56,    57,  -271,     0,     0,
      58,     0,    59,     0,     0,    60,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      61,    62,    63,    64,     0,     0,     0,     0,    65,     0,
       0,     0,     0,     0,     0,     0,     0,    66,     0,    67,
       0,    68,    69,     0,    70,     0,     0,    71,     0,     0,
       0,    72,     0,    73,     4,    74,     5,     6,     7,     8,
       9,    10,     0,     0,     0,    11,    12,    13,     0,     0,
      14,    15,    16,    17,  -271,    18,    19,     0,    20,    21,
       0,    22,     0,    23,    24,    25,    26,   731,     0,    28,
      29,     0,  -158,    30,    31,    32,    33,    34,   -39,    35,
      36,     0,    37,     0,     0,     0,  -271,    38,     0,    40,
      41,  -158,    42,    43,     0,  -271,    44,    45,     0,    46,
      47,    48,    49,    50,    51,     0,    52,     0,    53,    54,
      55,     0,    56,    57,  -271,     0,     0,    58,     0,    59,
       0,     0,    60,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    61,    62,    63,
      64,     0,     0,     0,     0,    65,     0,     0,     0,     0,
       0,     0,     0,     0,    66,     0,    67,     0,    68,    69,
       0,    70,     0,     0,    71,     0,     0,     0,    72,     0,
      73,     4,    74,     5,     6,     7,     8,     9,    10,     0,
       0,     0,    11,    12,    13,     0,     0,    14,    15,    16,
      17,  -271,    18,    19,     0,    20,    21,     0,    22,     0,
      23,    24,    25,    26,   734,     0,    28,    29,     0,  -158,
      30,    31,    32,    33,    34,   -39,    35,    36,     0,    37,
       0,     0,     0,  -271,    38,     0,    40,    41,  -158,    42,
      43,     0,  -271,    44,    45,     0,    46,    47,    48,    49,
      50,    51,     0,    52,     0,    53,    54,    55,     0,    56,
      57,  -271,     0,     0,    58,     0,    59,     0,     0,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,    62,    63,    64,     0,     0,
       0,     0,    65,     0,     0,     0,     0,     0,     0,     0,
       0,    66,     0,    67,     0,    68,    69,     0,    70,     0,
       0,    71,     0,     0,     0,    72,     0,    73,     4,    74,
       5,     6,     7,     8,     9,    10,     0,     0,     0,    11,
      12,    13,     0,     0,    14,    15,    16,    17,  -271,    18,
      19,     0,    20,    21,     0,    22,     0,    23,    24,    25,
      26,   737,     0,    28,    29,     0,  -158,    30,    31,    32,
      33,    34,   -39,    35,    36,     0,    37,     0,     0,     0,
    -271,    38,     0,    40,    41,  -158,    42,    43,     0,  -271,
      44,    45,     0,    46,    47,    48,    49,    50,    51,     0,
      52,     0,    53,    54,    55,     0,    56,    57,  -271,     0,
       0,    58,     0,    59,     0,     0,    60,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    61,    62,    63,    64,     0,     0,     0,     0,    65,
       0,     0,     0,     0,     0,     0,     0,     0,    66,     0,
      67,     0,    68,    69,     0,    70,     0,     0,    71,     0,
       0,     0,    72,     0,    73,     4,    74,     5,     6,     7,
       8,     9,    10,     0,     0,     0,    11,    12,    13,     0,
       0,    14,    15,    16,    17,  -271,    18,    19,     0,   753,
      21,     0,    22,     0,    23,    24,    25,    26,    27,     0,
      28,    29,     0,  -158,    30,    31,    32,    33,    34,   -39,
      35,    36,     0,    37,     0,     0,     0,  -271,    38,     0,
      40,    41,  -158,    42,    43,     0,  -271,    44,    45,     0,
      46,    47,    48,    49,    50,    51,     0,    52,     0,    53,
      54,    55,     0,    56,    57,  -271,     0,     0,    58,     0,
      59,     0,     0,    60,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    61,    62,
      63,    64,     0,     0,     0,     0,    65,     0,     0,     0,
       0,     0,     0,     0,     0,    66,     0,    67,     0,    68,
      69,     0,    70,     0,     0,    71,     0,     0,     0,    72,
       0,    73,     4,    74,     5,     6,     7,     8,     9,    10,
       0,     0,     0,    11,    12,    13,     0,     0,    14,    15,
      16,    17,  -271,    18,    19,     0,    20,    21,     0,    22,
       0,    23,    24,    25,    26,   761,     0,    28,    29,     0,
    -158,    30,    31,    32,    33,    34,   -39,    35,    36,     0,
      37,     0,     0,     0,  -271,    38,     0,    40,    41,  -158,
      42,    43,     0,  -271,    44,    45,     0,    46,    47,    48,
      49,    50,    51,     0,    52,     0,    53,    54,    55,     0,
      56,    57,  -271,     0,     0,    58,     0,    59,     0,     0,
      60,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    61,    62,    63,    64,     0,
       0,     0,     0,    65,     0,     0,     0,     0,     0,     0,
       0,     0,    66,     0,    67,     0,    68,    69,     0,    70,
       0,     0,    71,     0,     0,     0,    72,     0,    73,     4,
      74,     5,     6,     7,     8,     9,    10,     0,     0,     0,
      11,    12,    13,     0,     0,    14,    15,    16,    17,  -271,
      18,    19,     0,    20,    21,     0,    22,     0,    23,    24,
      25,    26,   765,     0,    28,    29,     0,  -158,    30,    31,
      32,    33,    34,   -39,    35,    36,     0,    37,     0,     0,
       0,  -271,    38,     0,    40,    41,  -158,    42,    43,     0,
    -271,    44,    45,     0,    46,    47,    48,    49,    50,    51,
       0,    52,     0,    53,    54,    55,     0,    56,    57,  -271,
       0,     0,    58,     0,    59,     0,     0,    60,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    61,    62,    63,    64,     0,     0,     0,     0,
      65,   508,     0,     5,     6,     7,     8,     9,    10,    66,
    -423,    67,   132,    68,    69,  -423,    70,     0,     0,    71,
       0,     0,     0,    72,  -423,    73,    21,    74,     0,     0,
       0,     0,   133,   134,   135,     0,    28,     0,     0,     0,
       0,    31,    32,     0,    34,     0,    35,    36,     0,     0,
       0,     0,     0,     0,    38,     0,    40,     0,     0,     0,
       0,  -423,     0,     0,     0,  -423,     0,     0,    48,    49,
      50,   136,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -423,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -423,    62,  -423,  -423,  -423,     0,
    -423,  -423,  -423,     0,  -423,  -423,  -423,  -423,  -423,  -423,
    -423,  -423,  -423,    67,  -423,  -423,  -423,     0,     0,  -423,
    -423,  -423,     0,     0,     0,   137,     0,    73,   508,   525,
       5,     6,     7,     8,     9,    10,     0,     0,     0,   132,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    21,     0,     0,     0,     0,     0,   133,
     134,   135,     0,    28,     0,     0,     0,     0,    31,    32,
       0,    34,     0,    35,    36,     0,     0,     0,     0,     0,
       0,    38,     0,    40,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    48,    49,    50,   136,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    60,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    61,    62,    63,    64,     0,     0,     0,   508,    65,
       5,     6,     7,     8,     9,    10,     0,     0,    66,   132,
      67,     0,    68,    69,     0,     0,     0,     0,    71,     0,
       0,     0,   137,    21,    73,     0,   509,     0,     0,   133,
     134,   135,     0,    28,     0,     0,     0,     0,    31,    32,
       0,    34,     0,    35,    36,     0,     0,     0,     0,     0,
       0,    38,     0,    40,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    48,    49,    50,   136,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    60,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    61,    62,    63,    64,     0,     0,     0,     0,    65,
       5,     6,     7,     8,     9,    10,     0,     0,    66,   132,
      67,     0,    68,    69,     0,     0,     0,     0,    71,     0,
       0,     0,   137,    21,    73,     0,   525,     0,     0,   133,
     134,   135,     0,    28,     0,     0,     0,     0,    31,    32,
       0,    34,     0,    35,    36,     0,     0,     0,     0,     0,
       0,    38,     0,    40,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    48,    49,    50,   136,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    60,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    61,    62,    63,    64,     0,     0,     0,     0,    65,
       5,     6,     7,     8,     9,    10,     0,     0,    66,   132,
      67,     0,    68,    69,   184,     0,     0,     0,    71,     0,
       0,     0,   137,    21,    73,     0,   138,   543,     0,   133,
     134,   135,     0,    28,     0,     0,     0,     0,    31,    32,
       0,    34,     0,    35,    36,     0,     0,     0,     0,     0,
       0,    38,     0,    40,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    48,    49,    50,   136,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    60,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    61,    62,    63,    64,     0,     0,     0,     0,    65,
       5,     6,     7,     8,     9,    10,     0,     0,    66,   132,
      67,     0,    68,    69,   184,     0,     0,     0,    71,     0,
       0,     0,   137,    21,    73,     0,   138,   843,     0,   133,
     134,   135,     0,    28,     0,     0,     0,     0,    31,    32,
       0,    34,     0,    35,    36,     0,     0,     0,     0,     0,
       0,    38,     0,    40,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    48,    49,    50,   136,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    60,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    61,    62,    63,    64,     0,     0,     0,     0,    65,
       0,     0,     5,     6,     7,     8,     9,    10,    66,     0,
      67,   132,    68,    69,     0,     0,     0,     0,    71,     0,
     451,     0,   137,     0,    73,    21,   138,   548,     0,     0,
       0,   133,   134,   135,   452,    28,     0,   453,     0,     0,
      31,    32,     0,    34,     0,    35,    36,     0,     0,     0,
       0,   454,   455,    38,     0,    40,     0,     0,     0,     0,
       0,   456,     0,     0,     0,     0,     0,    48,    49,    50,
     136,     0,     0,     0,     0,     0,   457,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    60,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    61,    62,    63,    64,     0,     0,     0,
       0,    65,     5,     6,     7,     8,     9,    10,     0,     0,
      66,   132,    67,     0,    68,    69,     0,     0,     0,     0,
      71,     0,     0,     0,   137,    21,    73,     0,   138,     0,
       0,   133,   134,   135,     0,    28,     0,     0,     0,     0,
      31,    32,     0,    34,     0,    35,    36,     0,     0,     0,
       0,     0,     0,    38,     0,    40,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    48,    49,    50,
     136,     0,     0,     0,     0,     0,     0,   223,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    60,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    61,    62,    63,    64,     0,     0,     0,
       0,    65,   224,     0,     5,     6,     7,     8,     9,    10,
      66,     0,    67,   132,    68,    69,   184,     0,     0,     0,
      71,     0,     0,     0,   137,     0,    73,    21,   138,     0,
       0,     0,     0,   133,   134,   135,     0,    28,     0,     0,
       0,     0,    31,    32,     0,    34,     0,    35,    36,     0,
       0,     0,     0,     0,     0,    38,     0,    40,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    48,
      49,    50,   136,     0,     0,     0,     0,     0,     0,   223,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      60,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    61,    62,    63,    64,     0,
       0,     0,     0,    65,     5,     6,     7,     8,     9,    10,
       0,     0,    66,   132,    67,     0,    68,    69,   184,     0,
       0,     0,    71,     0,     0,     0,   137,    21,    73,   537,
     138,     0,     0,   133,   134,   135,     0,    28,     0,     0,
       0,     0,    31,    32,     0,    34,     0,    35,    36,     0,
       0,     0,     0,     0,     0,    38,     0,    40,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    48,
      49,    50,   136,     0,     0,     0,     0,     0,     0,   223,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      60,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    61,    62,    63,    64,     0,
       0,     0,     0,    65,     5,     6,     7,     8,     9,    10,
       0,     0,    66,   132,    67,     0,    68,    69,   184,     0,
       0,     0,    71,     0,     0,     0,   137,    21,    73,   539,
     138,     0,     0,   133,   134,   135,     0,    28,     0,     0,
       0,     0,    31,    32,     0,    34,     0,    35,    36,     0,
       0,     0,     0,     0,   160,    38,     0,    40,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    48,
      49,    50,   136,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   161,     0,
      60,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    61,    62,    63,    64,     0,
       0,     0,     0,    65,     5,     6,     7,     8,     9,    10,
       0,     0,    66,   132,    67,     0,    68,    69,     0,     0,
       0,     0,    71,     0,     0,     0,   137,    21,    73,     0,
     138,     0,     0,   133,   134,   135,     0,    28,     0,     0,
       0,     0,    31,    32,     0,    34,     0,    35,    36,     0,
       0,     0,     0,     0,     0,    38,     0,    40,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    48,
      49,    50,   136,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      60,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    61,    62,    63,    64,     0,
       0,     0,     0,    65,     0,     0,     5,     6,     7,     8,
       9,    10,    66,     0,    67,   132,    68,    69,   184,     0,
       0,     0,    71,     0,     0,     0,   137,   535,    73,    21,
     138,     0,     0,     0,     0,   133,   134,   135,     0,    28,
       0,     0,     0,     0,    31,    32,     0,    34,     0,    35,
      36,     0,     0,     0,     0,     0,     0,    38,     0,    40,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    48,    49,    50,   136,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    60,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    61,    62,    63,
      64,     0,     0,     0,     0,    65,     5,     6,     7,     8,
       9,    10,     0,     0,    66,   132,    67,     0,    68,    69,
     184,     0,     0,     0,    71,     0,     0,     0,   137,    21,
      73,     0,   138,     0,     0,   133,   134,   135,     0,    28,
       0,     0,     0,     0,    31,    32,     0,    34,     0,    35,
      36,     0,     0,     0,     0,     0,     0,    38,     0,    40,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    48,    49,    50,   136,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    60,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    61,    62,    63,
      64,     0,     0,     0,     0,    65,     0,     0,     0,     0,
       0,     0,     0,     0,    66,     0,    67,     0,    68,    69,
       0,   188,     0,     0,    71,     0,     0,     0,   137,     0,
      73,     0,   138,     5,     6,     7,     8,     9,    10,     0,
       0,     0,   132,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   191,    21,     0,     0,     0,
       0,     0,   133,   134,   135,     0,    28,     0,     0,     0,
       0,    31,    32,     0,    34,     0,    35,    36,     0,     0,
       0,     0,     0,     0,    38,     0,    40,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    48,    49,
      50,   136,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,    62,    63,    64,     0,     0,
       0,     0,    65,     5,     6,     7,     8,     9,    10,     0,
       0,    66,   132,    67,     0,    68,    69,     0,     0,     0,
       0,    71,     0,     0,     0,    72,    21,    73,     0,   138,
       0,     0,   133,   134,   135,     0,    28,     0,     0,     0,
       0,    31,    32,     0,    34,     0,    35,    36,     0,     0,
       0,     0,     0,     0,    38,     0,    40,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    48,    49,
      50,   136,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   161,     0,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,    62,    63,    64,     0,     0,
       0,     0,    65,     5,     6,     7,     8,     9,    10,     0,
       0,    66,   132,    67,     0,    68,    69,     0,     0,     0,
       0,    71,     0,     0,     0,   137,    21,    73,     0,   138,
       0,     0,   133,   134,   135,     0,    28,     0,     0,     0,
       0,    31,    32,     0,    34,     0,    35,    36,   642,     0,
       0,     0,     0,     0,    38,     0,    40,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    48,    49,
      50,   136,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,    62,    63,    64,     0,     0,
       0,     0,    65,     5,     6,     7,     8,     9,    10,     0,
       0,    66,   132,    67,     0,    68,    69,     0,     0,     0,
       0,    71,     0,     0,     0,   137,   801,    73,     0,   138,
       0,     0,   133,   134,   135,     0,    28,     0,     0,     0,
       0,    31,    32,     0,    34,     0,    35,    36,     0,     0,
       0,     0,     0,     0,    38,     0,    40,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   802,    49,
      50,   803,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,    62,    63,    64,     0,     0,
       0,     0,    65,     5,     6,     7,     8,     9,    10,     0,
       0,    66,   132,    67,     0,    68,    69,   184,     0,     0,
       0,    71,     0,     0,     0,   137,    21,    73,     0,   804,
       0,     0,   133,   134,   135,     0,    28,     0,     0,     0,
       0,    31,    32,     0,    34,     0,    35,    36,     0,     0,
       0,     0,     0,     0,    38,     0,    40,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    48,    49,
      50,   136,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,    62,    63,    64,     0,     0,
       0,     0,    65,     5,     6,     7,     8,     9,    10,     0,
       0,    66,   132,    67,     0,    68,    69,   184,     0,     0,
       0,    71,     0,     0,     0,   137,    21,    73,     0,   804,
       0,     0,   133,   134,   791,     0,    28,     0,     0,     0,
       0,    31,    32,     0,    34,     0,    35,    36,     0,     0,
       0,     0,     0,     0,    38,     0,    40,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    48,    49,
      50,   136,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,    62,    63,    64,     0,     0,
       0,     0,    65,     5,     6,     7,     8,     9,    10,     0,
       0,    66,   132,    67,     0,    68,    69,   184,     0,     0,
       0,    71,     0,     0,     0,   137,    21,    73,     0,   138,
       0,     0,   133,   134,   135,     0,    28,     0,     0,     0,
       0,    31,    32,     0,    34,     0,    35,    36,     0,     0,
       0,     0,     0,     0,    38,     0,    40,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    48,    49,
      50,   136,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,    62,    63,    64,     0,     0,
       0,     0,    65,     5,     6,     7,     8,     9,    10,     0,
       0,    66,   132,    67,     0,    68,    69,     0,     0,     0,
       0,    71,     0,     0,     0,   137,    21,    73,     0,   138,
       0,     0,   133,   134,   135,     0,    28,     0,     0,     0,
       0,    31,    32,     0,    34,     0,    35,    36,     0,     0,
       0,     0,     0,     0,    38,     0,    40,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    48,    49,
      50,   136,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,    62,    63,    64,     0,     0,
       0,     0,    65,     5,     6,     7,     8,     9,    10,     0,
       0,    66,   132,    67,     0,    68,    69,     0,     0,     0,
       0,    71,     0,     0,     0,    72,    21,    73,     0,   138,
       0,     0,   133,   134,   135,     0,    28,     0,     0,     0,
       0,    31,    32,     0,    34,     0,    35,    36,     0,     0,
       0,     0,     0,     0,    38,     0,    40,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    48,    49,
      50,   136,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,    62,    63,    64,     0,     0,
       0,     0,    65,     5,     6,     7,     8,     9,    10,     0,
       0,    66,   132,    67,     0,    68,    69,     0,     0,     0,
       0,   529,     0,     0,     0,   137,    21,    73,     0,   138,
       0,     0,   133,   134,   589,     0,    28,     0,     0,     0,
       0,    31,    32,     0,    34,     0,    35,    36,     0,     0,
       0,     0,     0,     0,    38,     0,    40,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    48,    49,
      50,   136,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,    62,    63,    64,     0,     0,
       0,     0,    65,     5,     6,     7,     8,     9,    10,     0,
       0,    66,   132,    67,     0,    68,    69,     0,     0,     0,
       0,    71,     0,     0,     0,   137,    21,    73,     0,   138,
       0,     0,   133,   134,   592,     0,    28,     0,     0,     0,
       0,    31,    32,     0,    34,     0,    35,    36,     0,     0,
       0,     0,     0,     0,    38,     0,    40,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    48,    49,
      50,   136,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,    62,    63,    64,     0,     0,
       0,     0,    65,     5,     6,     7,     8,     9,    10,     0,
       0,    66,   132,    67,     0,    68,    69,     0,     0,     0,
       0,    71,     0,     0,     0,   137,    21,    73,     0,   138,
       0,     0,   133,   134,   785,     0,    28,     0,     0,     0,
       0,    31,    32,     0,    34,     0,    35,    36,     0,     0,
       0,     0,     0,     0,    38,     0,    40,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    48,    49,
      50,   136,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,    62,    63,    64,     0,     0,
       0,     0,    65,     5,     6,     7,     8,     9,    10,     0,
       0,    66,   132,    67,     0,    68,    69,     0,     0,     0,
       0,    71,     0,     0,     0,   137,    21,    73,     0,   138,
       0,     0,   133,   134,   786,     0,    28,     0,     0,     0,
       0,    31,    32,     0,    34,     0,    35,    36,     0,     0,
       0,     0,     0,     0,    38,     0,    40,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    48,    49,
      50,   136,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,    62,    63,    64,     0,     0,
       0,     0,    65,     5,     6,     7,     8,     9,    10,     0,
       0,    66,   132,    67,     0,    68,    69,     0,     0,     0,
       0,    71,     0,     0,     0,   137,    21,    73,     0,   138,
       0,     0,   133,   134,   788,     0,    28,     0,     0,     0,
       0,    31,    32,     0,    34,     0,    35,    36,     0,     0,
       0,     0,     0,     0,    38,     0,    40,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    48,    49,
      50,   136,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,    62,    63,    64,     0,     0,
       0,     0,    65,     5,     6,     7,     8,     9,    10,     0,
       0,    66,   132,    67,     0,    68,    69,     0,     0,     0,
       0,    71,     0,     0,     0,   137,    21,    73,     0,   138,
       0,     0,   133,   134,   789,     0,    28,     0,     0,     0,
       0,    31,    32,     0,    34,     0,    35,    36,     0,     0,
       0,     0,     0,     0,    38,     0,    40,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    48,    49,
      50,   136,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,    62,    63,    64,     0,     0,
       0,     0,    65,     5,     6,     7,     8,     9,    10,     0,
       0,    66,   132,    67,     0,    68,    69,     0,     0,     0,
       0,    71,     0,     0,     0,   137,    21,    73,     0,   138,
       0,     0,   133,   134,   790,     0,    28,     0,     0,     0,
       0,    31,    32,     0,    34,     0,    35,    36,     0,     0,
       0,     0,     0,     0,    38,     0,    40,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    48,    49,
      50,   136,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,    62,    63,    64,     0,     0,
       0,     0,    65,     5,     6,     7,     8,     9,    10,     0,
       0,    66,   132,    67,     0,    68,    69,     0,     0,     0,
       0,    71,     0,     0,     0,   137,    21,    73,     0,   138,
       0,     0,   133,   134,   791,     0,    28,     0,     0,     0,
       0,    31,    32,     0,    34,     0,    35,    36,     0,     0,
       0,     0,     0,     0,    38,     0,    40,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    48,    49,
      50,   136,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,    62,    63,    64,     0,     0,
       0,     0,    65,     5,     6,     7,     8,     9,    10,     0,
       0,    66,   132,    67,     0,    68,    69,     0,     0,     0,
       0,    71,     0,     0,     0,   137,    21,    73,     0,   138,
       0,     0,   133,   134,   135,     0,    28,     0,     0,     0,
       0,    31,    32,     0,    34,     0,    35,    36,     0,     0,
       0,     0,     0,     0,    38,     0,    40,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    48,    49,
      50,   136,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     5,
       6,     7,     8,     9,    10,     0,     0,     0,   132,     0,
       0,     0,     0,     0,    61,    62,    63,    64,     0,     0,
       0,     0,    21,     0,     0,     0,     0,     0,   133,   134,
     135,    66,    28,    67,     0,     0,    69,    31,    32,     0,
      34,    71,    35,    36,     0,   137,     0,    73,     0,   138,
      38,     0,    40,     0,     0,     0,     0,   245,     0,     0,
       0,     0,   246,     0,    48,    49,    50,   136,     0,     0,
       0,   247,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -298,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    62,     0,     0,     0,  -298,     0,     0,   248,  -298,
       0,     0,   249,     0,     0,     0,     0,     0,     0,    67,
       0,     0,     0,   184,   245,     0,     0,     0,     0,   246,
       0,   137,   325,    73,  -298,   804,   250,     0,   247,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   251,     0,   252,   253,   254,     0,   255,   256,   257,
       0,   258,   259,   260,   261,   262,   263,   264,   265,   266,
       0,   267,   268,   269,     0,   248,   270,   271,   272,   249,
       0,     0,     0,     0,     0,     0,   245,   659,     0,     0,
       0,   246,     0,     0,     0,     0,     0,     0,     0,     0,
     247,     0,     0,   250,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   251,     0,
     252,   253,   254,     0,   255,   256,   257,     0,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   248,   267,   268,
     269,   249,     0,   270,   271,   272,     0,     0,   245,     0,
       0,     0,     0,   246,   852,     0,     0,     0,     0,     0,
       0,     0,   247,     0,     0,   250,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     251,     0,   252,   253,   254,     0,   255,   256,   257,     0,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   248,
     267,   268,   269,   249,     0,   270,   271,   272,     0,     0,
     245,     0,     0,     0,     0,   246,   889,     0,     0,     0,
       0,     0,     0,     0,   247,     0,     0,   250,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   251,     0,   252,   253,   254,     0,   255,   256,
     257,     0,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   248,   267,   268,   269,   249,     0,   270,   271,   272,
       0,     0,   245,     0,     0,     0,   536,   246,     0,     0,
       0,     0,     0,     0,     0,     0,   247,   323,     0,   250,
       0,     0,     0,     0,     0,     0,     0,   324,     0,     0,
       0,     0,     0,     0,   251,     0,   252,   253,   254,     0,
     255,   256,   257,     0,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   248,   267,   268,   269,   249,     0,   270,
     271,   272,     0,     0,   245,     0,     0,     0,   826,   246,
       0,     0,     0,     0,     0,     0,     0,   325,   247,   320,
       0,   250,     0,     0,     0,     0,     0,     0,     0,   321,
       0,     0,     0,     0,     0,     0,   251,     0,   252,   253,
     254,     0,   255,   256,   257,     0,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   248,   267,   268,   269,   249,
       0,   270,   271,   272,     0,     0,   245,   296,     0,     0,
       0,   246,     0,     0,     0,     0,     0,     0,     0,     0,
     247,   619,     0,   250,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   251,     0,
     252,   253,   254,     0,   255,   256,   257,     0,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   248,   267,   268,
     269,   249,     0,   270,   271,   272,     0,     0,   245,   296,
       0,     0,     0,   246,     0,     0,     0,     0,     0,     0,
       0,   325,   247,     0,     0,   250,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     251,     0,   252,   253,   254,     0,   255,   256,   257,     0,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   248,
     267,   268,   269,   249,     0,   270,   271,   272,     0,     0,
     328,   296,     0,     0,     0,   245,     0,     0,     0,     0,
     246,     0,     0,     0,     0,     0,     0,   250,     0,   247,
     191,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   251,     0,   252,   253,   254,     0,   255,   256,
     257,     0,   258,   259,   260,   261,   262,   263,   264,   265,
     266,     0,   267,   268,   269,     0,   248,   270,   271,   272,
     249,     0,     0,   296,     0,     0,     0,   245,     0,     0,
       0,     0,   246,     0,     0,     0,     0,     0,     0,     0,
       0,   247,   613,     0,   250,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   251,
       0,   252,   253,   254,     0,   255,   256,   257,     0,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   248,   267,
     268,   269,   249,     0,   270,   271,   272,     0,     0,   245,
     296,     0,     0,     0,   246,     0,     0,     0,     0,     0,
       0,     0,     0,   247,     0,     0,   250,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   251,     0,   252,   253,   254,     0,   255,   256,   257,
       0,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     248,   267,   268,   269,   249,     0,   270,   271,   272,     0,
       0,   728,   296,     0,     0,     0,   245,     0,     0,     0,
       0,   246,     0,     0,     0,     0,     0,     0,   250,     0,
     247,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   251,     0,   252,   253,   254,     0,   255,
     256,   257,     0,   258,   259,   260,   261,   262,   263,   264,
     265,   266,     0,   267,   268,   269,     0,   248,   270,   271,
     272,   249,     0,     0,   296,     0,     0,     0,   733,     0,
       0,     0,     0,   245,     0,     0,     0,     0,   246,     0,
       0,     0,     0,     0,     0,   250,     0,   247,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     251,     0,   252,   253,   254,     0,   255,   256,   257,     0,
     258,   259,   260,   261,   262,   263,   264,   265,   266,     0,
     267,   268,   269,     0,   248,   270,   271,   272,   249,     0,
       0,   296,     0,     0,     0,   838,     0,     0,     0,     0,
     245,     0,     0,     0,     0,   246,     0,     0,     0,     0,
       0,     0,   250,     0,   247,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   251,     0,   252,
     253,   254,     0,   255,   256,   257,     0,   258,   259,   260,
     261,   262,   263,   264,   265,   266,     0,   267,   268,   269,
       0,   248,   270,   271,   272,   249,     0,     0,   296,     0,
       0,     0,   839,     0,     0,     0,     0,   245,     0,     0,
       0,     0,   246,     0,     0,     0,     0,     0,     0,   250,
       0,   247,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   251,     0,   252,   253,   254,     0,
     255,   256,   257,     0,   258,   259,   260,   261,   262,   263,
     264,   265,   266,     0,   267,   268,   269,     0,   248,   270,
     271,   272,   249,     0,     0,   296,     0,     0,     0,   840,
       0,     0,     0,     0,   245,     0,     0,     0,     0,   246,
       0,     0,     0,     0,     0,     0,   250,     0,   247,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   251,     0,   252,   253,   254,     0,   255,   256,   257,
       0,   258,   259,   260,   261,   262,   263,   264,   265,   266,
       0,   267,   268,   269,     0,   248,   270,   271,   272,   249,
       0,     0,   296,     0,     0,     0,   841,     0,     0,     0,
       0,   245,     0,     0,     0,     0,   246,     0,     0,     0,
       0,     0,     0,   250,     0,   247,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   251,     0,
     252,   253,   254,     0,   255,   256,   257,     0,   258,   259,
     260,   261,   262,   263,   264,   265,   266,     0,   267,   268,
     269,     0,   248,   270,   271,   272,   249,     0,     0,   296,
       0,     0,     0,   854,     0,     0,     0,     0,   245,     0,
       0,     0,     0,   246,     0,     0,     0,     0,     0,     0,
     250,     0,   247,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   251,     0,   252,   253,   254,
       0,   255,   256,   257,     0,   258,   259,   260,   261,   262,
     263,   264,   265,   266,     0,   267,   268,   269,     0,   248,
     270,   271,   272,   249,     0,     0,   296,     0,     0,     0,
     855,     0,     0,     0,     0,   245,     0,     0,     0,     0,
     246,     0,     0,     0,     0,     0,     0,   250,     0,   247,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   251,     0,   252,   253,   254,     0,   255,   256,
     257,     0,   258,   259,   260,   261,   262,   263,   264,   265,
     266,     0,   267,   268,   269,     0,   248,   270,   271,   272,
     249,     0,     0,   296,     0,     0,     0,   245,     0,     0,
       0,     0,   246,     0,     0,     0,     0,     0,     0,     0,
       0,   247,     0,     0,   250,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   251,
       0,   252,   253,   254,     0,   255,   256,   257,     0,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   248,   267,
     268,   269,   249,     0,   270,   271,   272,     0,     0,   245,
     352,     0,     0,     0,   246,     0,     0,     0,     0,     0,
       0,     0,     0,   247,     0,     0,   250,     0,     0,     0,
       0,     0,     0,     0,   302,     0,     0,     0,     0,     0,
       0,   251,     0,   252,   253,   254,     0,   255,   256,   257,
       0,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     248,   267,   268,   269,   249,     0,   270,   271,   272,     0,
       0,  -383,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   245,     0,   126,     0,     0,   246,   250,     0,
       0,     0,     0,     0,     0,     0,   247,     0,     0,     0,
       0,   366,     0,   251,     0,   252,   253,   254,     0,   255,
     256,   257,     0,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   367,   267,   268,   269,   245,     0,   270,   271,
     272,   246,     0,   248,     0,     0,     0,   249,     0,     0,
     247,   463,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   464,     0,     0,     0,     0,     0,     0,     0,     0,
     245,   250,     0,     0,     0,   246,     0,     0,     0,     0,
       0,     0,     0,     0,   247,   465,   251,   248,   252,   253,
     254,   249,   255,   256,   257,   466,   258,   259,   260,   261,
     262,   263,   264,   265,   266,     0,   267,   268,   269,     0,
       0,   270,   271,   272,   245,   250,     0,     0,     0,   246,
       0,   248,     0,     0,     0,   249,     0,     0,   247,     0,
     251,     0,   252,   253,   254,     0,   255,   256,   257,     0,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   250,
     267,   268,   269,     0,     0,   270,   271,   272,     0,     0,
       0,     0,     0,     0,   251,   248,   252,   253,   254,   249,
     255,   256,   257,     0,   258,   259,   260,   261,   262,   263,
     264,   265,   266,     0,   267,   268,   269,   245,     0,   270,
     271,   272,   246,   250,     0,     0,     0,     0,     0,     0,
       0,   247,     0,     0,     0,     0,     0,     0,   251,     0,
     252,   253,   254,     0,   255,   256,   257,     0,   258,   259,
     260,   261,   262,   263,   264,   265,   266,     0,   267,   268,
     269,   245,   306,   270,   271,   272,   246,     0,   248,     0,
       0,     0,   249,     0,     0,   247,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   245,   250,     0,     0,     0,
     246,     0,     0,     0,     0,     0,     0,     0,     0,   247,
       0,   251,   248,   252,   253,   254,   249,   255,   256,   257,
       0,   258,   259,   260,   261,   262,   263,   264,   265,   266,
       0,   267,   268,   269,     0,   351,   270,   271,   272,   245,
     250,     0,     0,     0,   246,     0,   248,     0,     0,     0,
     249,     0,     0,   247,     0,   251,     0,   252,   253,   254,
       0,   255,   256,   257,     0,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   250,   267,   268,   269,     0,   357,
     270,   271,   272,     0,     0,     0,     0,     0,     0,   251,
     248,   252,   253,   254,   249,   255,   256,   257,     0,   258,
     259,   260,   261,   262,   263,   264,   265,   266,     0,   267,
     268,   269,   245,   359,   270,   271,   272,   246,   250,     0,
       0,     0,     0,     0,     0,     0,   247,     0,     0,     0,
       0,     0,     0,   251,     0,   252,   253,   254,     0,   255,
     256,   257,     0,   258,   259,   260,   261,   262,   263,   264,
     265,   266,     0,   267,   268,   269,   245,   361,   270,   271,
     272,   246,     0,   248,     0,     0,     0,   249,     0,     0,
     247,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   250,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   251,   248,   252,   253,
     254,   249,   255,   256,   257,     0,   258,   259,   260,   261,
     262,   263,   264,   265,   266,     0,   267,   268,   269,     0,
     369,   270,   271,   272,   383,   250,     0,   245,     0,     0,
       0,     0,   246,     0,     0,     0,     0,     0,     0,     0,
     251,   247,   252,   253,   254,     0,   255,   256,   257,     0,
     258,   259,   260,   261,   262,   263,   264,   265,   266,     0,
     267,   268,   269,     0,     0,   270,   271,   272,     0,     0,
       0,   245,     0,     0,     0,     0,   246,     0,   248,     0,
       0,     0,   249,     0,     0,   247,     0,     0,     0,   467,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   245,   250,     0,     0,     0,
     246,     0,     0,     0,     0,     0,     0,     0,     0,   247,
       0,   251,   248,   252,   253,   254,   249,   255,   256,   257,
       0,   258,   259,   260,   261,   262,   263,   264,   265,   266,
       0,   267,   268,   269,     0,     0,   270,   271,   272,   245,
     250,     0,     0,     0,   246,     0,   248,     0,     0,     0,
     249,     0,     0,   247,     0,   251,     0,   252,   253,   254,
       0,   255,   256,   257,     0,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   250,   267,   268,   269,     0,   564,
     270,   271,   272,     0,     0,     0,     0,     0,     0,   251,
     248,   252,   253,   254,   249,   255,   256,   257,     0,   258,
     259,   260,   261,   262,   263,   264,   265,   266,     0,   267,
     268,   269,   245,   565,   270,   271,   272,   246,   250,     0,
       0,     0,     0,     0,     0,     0,   247,     0,     0,     0,
       0,     0,     0,   251,     0,   252,   253,   254,     0,   255,
     256,   257,     0,   258,   259,   260,   261,   262,   263,   264,
     265,   266,     0,   267,   268,   269,   245,   566,   270,   271,
     272,   246,     0,   248,     0,     0,     0,   249,     0,     0,
     247,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     245,   250,     0,     0,     0,   246,     0,     0,     0,     0,
       0,     0,     0,     0,   247,     0,   251,   248,   252,   253,
     254,   249,   255,   256,   257,     0,   258,   259,   260,   261,
     262,   263,   264,   265,   266,     0,   267,   268,   269,     0,
     567,   270,   271,   272,   245,   250,     0,     0,     0,   246,
       0,   248,     0,     0,     0,   249,     0,     0,   247,     0,
     251,     0,   252,   253,   254,     0,   255,   256,   257,     0,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   250,
     267,   268,   269,     0,   568,   270,   271,   272,     0,     0,
       0,     0,     0,     0,   251,   248,   252,   253,   254,   249,
     255,   256,   257,     0,   258,   259,   260,   261,   262,   263,
     264,   265,   266,     0,   267,   268,   269,   245,   569,   270,
     271,   272,   246,   250,     0,     0,     0,     0,     0,     0,
       0,   247,     0,     0,     0,     0,     0,     0,   251,     0,
     252,   253,   254,     0,   255,   256,   257,     0,   258,   259,
     260,   261,   262,   263,   264,   265,   266,     0,   267,   268,
     269,   245,   570,   270,   271,   272,   246,     0,   248,     0,
       0,     0,   249,     0,     0,   247,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   245,   250,     0,     0,     0,
     246,     0,     0,     0,     0,     0,     0,     0,     0,   247,
       0,   251,   248,   252,   253,   254,   249,   255,   256,   257,
       0,   258,   259,   260,   261,   262,   263,   264,   265,   266,
       0,   267,   268,   269,     0,   571,   270,   271,   272,   245,
     250,     0,     0,     0,   246,     0,   248,     0,     0,     0,
     249,     0,     0,   247,     0,   251,     0,   252,   253,   254,
       0,   255,   256,   257,     0,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   250,   267,   268,   269,     0,   572,
     270,   271,   272,     0,     0,     0,     0,     0,     0,   251,
     248,   252,   253,   254,   249,   255,   256,   257,     0,   258,
     259,   260,   261,   262,   263,   264,   265,   266,     0,   267,
     268,   269,   245,   573,   270,   271,   272,   246,   250,     0,
       0,     0,     0,     0,     0,     0,   247,     0,     0,     0,
       0,     0,     0,   251,     0,   252,   253,   254,     0,   255,
     256,   257,     0,   258,   259,   260,   261,   262,   263,   264,
     265,   266,     0,   267,   268,   269,   245,   574,   270,   271,
     272,   246,     0,   248,     0,     0,     0,   249,     0,     0,
     247,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     245,   250,     0,     0,     0,   246,     0,     0,     0,     0,
       0,     0,     0,     0,   247,     0,   251,   248,   252,   253,
     254,   249,   255,   256,   257,     0,   258,   259,   260,   261,
     262,   263,   264,   265,   266,     0,   267,   268,   269,     0,
     575,   270,   271,   272,   245,   250,     0,     0,     0,   246,
       0,   248,     0,     0,     0,   249,     0,     0,   247,     0,
     251,     0,   252,   253,   254,     0,   255,   256,   257,     0,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   250,
     267,   268,   269,     0,   576,   270,   271,   272,     0,     0,
       0,     0,     0,     0,   251,   248,   252,   253,   254,   249,
     255,   256,   257,     0,   258,   259,   260,   261,   262,   263,
     264,   265,   266,     0,   267,   268,   269,   245,   577,   270,
     271,   272,   246,   250,     0,     0,     0,     0,     0,     0,
       0,   247,     0,     0,     0,     0,     0,     0,   251,     0,
     252,   253,   254,     0,   255,   256,   257,     0,   258,   259,
     260,   261,   262,   263,   264,   265,   266,     0,   267,   268,
     269,     0,   578,   270,   271,   272,     0,     0,   248,     0,
       0,     0,   249,     0,     0,     0,     0,     0,     0,   245,
       0,     0,     0,     0,   246,     0,     0,     0,     0,     0,
       0,     0,     0,   247,     0,     0,   250,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   251,     0,   252,   253,   254,     0,   255,   256,   257,
       0,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     248,   267,   268,   269,   249,   579,   270,   271,   272,     0,
       0,   245,     0,     0,     0,     0,   246,     0,     0,     0,
       0,     0,     0,     0,   126,   247,     0,     0,   250,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   251,     0,   252,   253,   254,     0,   255,
     256,   257,     0,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   248,   267,   268,   269,   249,     0,   270,   271,
     272,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   245,     0,     0,     0,     0,   246,     0,     0,
     250,     0,     0,     0,     0,     0,   247,     0,     0,   625,
       0,     0,     0,     0,     0,   251,     0,   252,   253,   254,
       0,   255,   256,   257,     0,   258,   259,   260,   261,   262,
     263,   264,   265,   266,     0,   267,   268,   269,     0,   599,
     270,   271,   272,   248,     0,     0,     0,   249,     0,     0,
       0,     0,     0,     0,   245,   655,     0,     0,     0,   246,
       0,     0,     0,     0,     0,     0,     0,     0,   247,     0,
       0,   250,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   251,     0,   252,   253,
     254,     0,   255,   256,   257,     0,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   248,   267,   268,   269,   249,
       0,   270,   271,   272,     0,     0,   245,     0,     0,     0,
       0,   246,     0,     0,     0,     0,     0,     0,     0,     0,
     247,     0,     0,   250,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   251,     0,
     252,   253,   254,     0,   255,   256,   257,     0,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   248,   267,   268,
     269,   249,     0,   270,   271,   272,     0,     0,   245,     0,
       0,     0,     0,   246,     0,     0,     0,     0,     0,     0,
       0,     0,   247,   716,   662,   250,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     251,     0,   252,   253,   254,     0,   255,   256,   257,     0,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   248,
     267,   268,   269,   249,     0,   270,   271,   272,     0,     0,
     245,     0,     0,     0,     0,   246,     0,     0,     0,     0,
       0,     0,     0,     0,   247,   719,     0,   250,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   251,     0,   252,   253,   254,     0,   255,   256,
     257,     0,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   248,   267,   268,   269,   249,     0,   270,   271,   272,
       0,     0,   245,     0,     0,     0,     0,   246,     0,     0,
       0,     0,     0,     0,     0,     0,   247,     0,     0,   250,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   251,     0,   252,   253,   254,     0,
     255,   256,   257,     0,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   248,   267,   268,   269,   249,     0,   270,
     271,   272,     0,     0,   784,     0,     0,     0,     0,   245,
       0,     0,     0,     0,   246,     0,     0,     0,     0,     0,
       0,   250,     0,   247,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   251,     0,   252,   253,
     254,     0,   255,   256,   257,     0,   258,   259,   260,   261,
     262,   263,   264,   265,   266,     0,   267,   268,   269,     0,
     248,   270,   271,   272,   249,     0,     0,     0,     0,     0,
       0,   787,     0,     0,     0,     0,   245,   819,     0,     0,
       0,   246,     0,     0,     0,     0,     0,     0,   250,     0,
     247,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   251,     0,   252,   253,   254,     0,   255,
     256,   257,     0,   258,   259,   260,   261,   262,   263,   264,
     265,   266,     0,   267,   268,   269,     0,   248,   270,   271,
     272,   249,     0,     0,     0,     0,     0,     0,   245,     0,
       0,     0,     0,   246,     0,     0,     0,     0,     0,     0,
       0,     0,   247,     0,     0,   250,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     251,     0,   252,   253,   254,     0,   255,   256,   257,     0,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   248,
     267,   268,   269,   249,     0,   270,   271,   272,     0,     0,
     861,     0,     0,     0,     0,   245,     0,     0,     0,     0,
     246,     0,     0,     0,     0,     0,     0,   250,     0,   247,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   251,     0,   252,   253,   254,     0,   255,   256,
     257,     0,   258,   259,   260,   261,   262,   263,   264,   265,
     266,     0,   267,   268,   269,     0,   248,   270,   271,   272,
     249,     0,     0,     0,     0,     0,     0,   862,     0,     0,
       0,     0,   245,     0,     0,     0,     0,   246,     0,     0,
       0,     0,     0,     0,   250,     0,   247,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   251,
       0,   252,   253,   254,     0,   255,   256,   257,     0,   258,
     259,   260,   261,   262,   263,   264,   265,   266,     0,   267,
     268,   269,     0,   248,   270,   271,   272,   249,     0,     0,
       0,     0,     0,     0,   863,     0,     0,     0,     0,   245,
       0,     0,     0,     0,   246,     0,     0,     0,     0,     0,
       0,   250,     0,   247,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   251,     0,   252,   253,
     254,     0,   255,   256,   257,     0,   258,   259,   260,   261,
     262,   263,   264,   265,   266,     0,   267,   268,   269,     0,
     248,   270,   271,   272,   249,     0,     0,     0,     0,     0,
       0,   864,     0,     0,     0,     0,   245,     0,     0,     0,
       0,   246,     0,     0,     0,     0,     0,     0,   250,     0,
     247,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   251,     0,   252,   253,   254,     0,   255,
     256,   257,     0,   258,   259,   260,   261,   262,   263,   264,
     265,   266,     0,   267,   268,   269,     0,   248,   270,   271,
     272,   249,     0,     0,     0,     0,     0,     0,   865,     0,
       0,     0,     0,   245,     0,     0,     0,     0,   246,     0,
       0,     0,     0,     0,     0,   250,     0,   247,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     251,     0,   252,   253,   254,     0,   255,   256,   257,     0,
     258,   259,   260,   261,   262,   263,   264,   265,   266,     0,
     267,   268,   269,     0,   248,   270,   271,   272,   249,     0,
       0,     0,     0,     0,     0,   866,     0,     0,     0,     0,
     245,     0,     0,     0,     0,   246,     0,     0,     0,     0,
       0,     0,   250,     0,   247,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   251,     0,   252,
     253,   254,     0,   255,   256,   257,     0,   258,   259,   260,
     261,   262,   263,   264,   265,   266,     0,   267,   268,   269,
       0,   248,   270,   271,   272,   249,     0,     0,     0,     0,
       0,     0,   245,     0,     0,     0,     0,   246,     0,     0,
       0,     0,     0,     0,     0,     0,   247,     0,     0,   250,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   251,     0,   252,   253,   254,     0,
     255,   256,   257,     0,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   587,   267,   268,   269,   249,     0,   270,
     271,   272,     0,     0,   247,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   250,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   247,     0,     0,   251,     0,   252,   253,
     254,   248,   255,   256,   257,   249,   258,   259,   260,   261,
     262,   263,   264,   265,   266,     0,   267,   268,   269,     0,
       0,   270,   271,   272,     0,     0,   247,     0,     0,   250,
     248,     0,     0,     0,   249,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   251,     0,   252,   253,   254,     0,
     255,   256,   257,     0,   258,   259,   260,   261,   250,   263,
     264,   265,   266,   248,   267,   268,   269,   249,     0,   270,
     271,   272,     0,   251,     0,   252,   253,   254,     0,   255,
     256,   257,     0,   258,   259,   260,   261,     0,   263,   264,
     265,   266,     0,   267,     0,   269,     0,     0,   270,   271,
     272,     0,     0,     0,     0,     0,   251,     0,   252,   253,
     254,     0,   255,   256,   257,     0,   258,   259,   260,   261,
       0,   263,   264,   265,   266,     0,   267,     0,   269,     0,
       0,   270,   271,   272
};

static const yytype_int16 yycheck[] =
{
      11,     2,    41,    42,   335,    16,    15,   362,    19,   148,
     332,   639,     3,    23,    25,    26,    27,   507,    25,   158,
       3,   229,   293,    34,    35,     1,    37,    38,   239,   240,
     241,   242,     3,    44,    45,    46,    47,    48,     3,    35,
      51,    52,    53,    54,    85,   843,    57,    58,    59,   494,
       1,    62,   665,    85,    65,    66,    67,    44,    69,     3,
     665,    72,    73,    74,   162,   163,   164,     1,   708,    35,
      57,    62,    25,    35,     3,    25,     1,    21,   176,    64,
     878,   109,    25,   812,    35,     0,    35,    74,    64,    85,
      35,    35,    39,    35,    38,    78,   194,    26,    74,   140,
       3,   109,   109,   166,   109,    51,    90,    83,    52,    53,
      35,    58,   140,   109,   212,   340,   179,    77,    62,   747,
     128,   132,   133,   134,   135,   136,   137,   138,   135,   113,
      64,   136,   108,    77,   197,   144,    82,   362,    64,    90,
     585,   152,    85,   109,   140,   635,   137,   109,    77,    83,
     135,   138,   128,   882,   137,   166,    17,   108,   109,   135,
     109,     7,   775,    88,   109,    90,   137,   109,   179,   137,
      35,   181,   137,   109,   108,   506,    21,   128,   140,   792,
     391,   109,   135,   108,   109,   135,   197,   792,   828,   829,
     136,   140,   135,   137,    70,   140,   109,    62,   140,    60,
     136,   135,   128,   128,   878,   303,    53,    54,    53,   135,
     138,   109,   109,   224,   842,   889,   109,    62,    79,   137,
     221,   108,    45,   494,   111,   138,   289,   290,   115,   327,
     128,   128,    77,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   138,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   109,   492,   493,     3,   777,    21,     3,
       7,   302,   355,     7,   109,   740,   307,   109,   629,   137,
       3,   109,   128,   137,     7,   627,     9,   318,   109,   320,
     321,    21,   323,   324,   585,   128,   134,   328,    21,    21,
      53,   109,    39,   138,    25,    35,   138,   109,    38,    62,
     138,   318,   343,   541,   542,    90,   109,   138,   349,   128,
     128,    58,    52,    53,   355,    24,   128,   109,    81,   128,
      53,    53,    62,     2,   109,   366,   367,   128,   113,    62,
      62,   372,    11,   128,   375,   138,   377,    77,   379,   380,
     381,    20,   383,   384,    77,    77,   138,   388,    81,   128,
     109,   109,    61,   138,    33,    90,    65,   128,    13,   528,
     488,   489,    61,    18,   492,   493,    65,   752,    24,   128,
     128,   388,    51,   758,   109,    20,    17,    61,   113,    20,
     137,    65,   139,   638,   137,    30,    31,    28,    84,    30,
      31,   128,    37,    72,    39,   137,    37,    76,    39,   108,
      45,   128,   111,   138,   128,    61,   115,   135,   137,    65,
     137,   111,   139,    58,    55,   135,    57,    58,    59,    60,
     137,    90,   463,   464,   465,   466,   467,   468,   469,   781,
      73,   470,   471,   128,   475,   476,    77,   478,    79,   740,
     137,     7,   139,   484,   137,   486,   139,   108,   127,   490,
      35,   128,   108,   494,   110,   111,    88,   138,    90,   115,
     375,   109,   377,   128,     2,    35,   122,   137,   509,   597,
     598,   512,   513,    11,    27,   131,   138,    88,   109,    64,
     608,   138,    20,    90,   525,   138,   138,   128,   167,    74,
     618,   746,   509,   621,    16,    33,    24,   752,    83,   109,
     140,   135,   135,   758,   140,    90,    90,    27,   525,   152,
     138,   138,   191,    51,   138,    53,    54,   248,   249,   128,
     109,   109,   128,   166,   109,   128,    35,    62,    25,    25,
     135,   108,   140,    61,    72,    62,   179,    65,    76,   108,
     140,   140,   221,   128,   585,   137,   587,   588,   589,   111,
     135,   592,   111,    83,   197,    64,   138,    74,   205,   550,
     291,   292,   367,   604,   159,    74,   726,   483,   780,   605,
     611,   302,   613,   780,    83,   616,   104,   781,   619,   107,
     108,    90,   110,   111,   625,   627,   667,   115,   843,   127,
     321,   882,     3,   324,   122,   842,     7,   852,   857,   344,
     109,   129,   130,   131,   645,   800,   478,    -1,    -1,    -1,
      21,    -1,   653,    -1,   655,    -1,   657,   296,   659,   128,
      20,   662,    -1,   878,    -1,    -1,   135,   755,   645,   167,
      30,    31,    -1,   664,   889,    -1,    -1,    37,    -1,    39,
      -1,   320,    53,    -1,   323,    45,   289,   290,   379,   328,
      -1,    62,    -1,   191,    -1,    -1,    -1,    -1,    58,    -1,
      -1,    -1,    -1,   704,    -1,    -1,    77,    -1,    -1,    -1,
      81,    -1,    -1,    -1,   715,   716,    -1,   718,   719,   720,
     721,    -1,    -1,   221,    -1,    -1,    -1,   728,   729,    -1,
     731,    -1,   733,   734,    -1,    -1,   737,    -1,    -1,   740,
      -1,    -1,   381,   772,   773,    -1,   349,    -1,    -1,    -1,
     751,   752,   355,    -1,    -1,   756,    -1,   758,    -1,    -1,
     761,    -1,     2,    -1,   765,    -1,    -1,    -1,    -1,   372,
      -1,    11,   375,   464,   377,   466,    -1,   380,    -1,    -1,
      20,    -1,    -1,   784,   785,   786,   787,   788,   789,   790,
     791,    -1,    -1,    33,    -1,    20,    -1,    -1,   296,    -1,
      -1,   802,   803,   804,    -1,    30,    31,   808,    -1,    -1,
     811,    51,    37,    -1,    39,    24,    -1,    -1,   819,   458,
      -1,    -1,   320,    -1,    -1,   323,    -1,   804,    -1,    -1,
     328,    -1,    72,    58,    -1,    -1,    76,   838,   839,   840,
     841,    -1,    -1,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   852,    61,   854,   855,    -1,    65,    -1,    -1,   498,
     861,   862,   863,   864,   865,   866,    -1,    -1,    -1,    -1,
      -1,    -1,    64,   476,    -1,   478,   877,   878,    -1,    -1,
      -1,    -1,    74,   381,    -1,     2,    -1,   127,   889,    -1,
      -1,    83,    -1,    -1,    11,   104,   587,   588,    90,   108,
      -1,   110,   111,    20,    -1,    -1,   115,   546,    -1,    -1,
      -1,   550,    -1,   122,    -1,    -1,    33,   109,    -1,   558,
     129,   130,   131,    -1,    -1,    -1,    -1,   167,    -1,    -1,
      -1,    -1,    -1,    -1,    51,    -1,   128,    -1,    -1,    -1,
      -1,    -1,    -1,   135,    -1,    -1,    -1,    -1,   587,   588,
      -1,   191,    -1,    -1,    -1,    72,    -1,    -1,    -1,    76,
      -1,    -1,    -1,    -1,    -1,    -1,     2,    -1,    -1,    -1,
      -1,    -1,   611,    -1,   613,    11,    -1,   616,    -1,    -1,
     619,   221,    -1,    -1,    20,   624,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    -1,    -1,
     498,    -1,    -1,    -1,    -1,   644,    -1,    -1,     2,    -1,
     127,    -1,    -1,    -1,    -1,    51,    -1,    11,   657,    -1,
     659,    -1,    -1,    -1,    -1,   664,    20,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    72,    -1,    -1,    33,
      76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   546,    -1,
     167,    -1,   550,    -1,    -1,    -1,   296,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   191,    -1,    -1,    -1,    72,    -1,
     320,    -1,    76,   323,    -1,    -1,    -1,    -1,   328,   728,
      -1,   127,    -1,    -1,   733,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    61,    -1,   221,    -1,    65,    -1,    -1,    -1,
      -1,    -1,    -1,   611,   753,   613,    -1,    -1,   616,    -1,
      -1,   619,    -1,    -1,    -1,   764,   624,    -1,    -1,   768,
      -1,   167,    -1,   127,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   381,    -1,   746,    -1,   104,   644,   106,   107,   108,
      -1,   110,   111,    -1,    -1,   191,   115,    -1,     2,   657,
      -1,   659,    -1,   122,    -1,    -1,   664,    11,    -1,    -1,
     129,   130,   131,   167,    -1,    -1,    20,    -1,    -1,   296,
      -1,    -1,    -1,    -1,    -1,   221,    -1,    -1,    -1,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   191,    -1,   838,
     839,   840,   841,   320,    -1,   808,   323,    51,    -1,    17,
      -1,   328,    20,    -1,    -1,   854,   855,    -1,    -1,    -1,
      28,    -1,    30,    31,    -1,    -1,    -1,   221,    72,    37,
     728,    39,    76,    -1,    -1,   733,    -1,    -1,    -1,    -1,
     843,    -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,    57,
      58,    59,    60,    -1,    -1,   753,    -1,    -1,   498,    -1,
     296,    -1,    -1,    -1,   381,    -1,   764,    -1,    -1,    77,
     768,    79,    -1,    -1,    -1,   878,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   127,   320,    -1,   889,   323,    -1,    -1,
      -1,    -1,   328,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   296,    -1,    -1,    -1,   546,    -1,    -1,    24,
     550,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     128,    -1,    -1,   167,    -1,    -1,   320,    -1,   136,   323,
      -1,    -1,    -1,    -1,   328,    -1,    -1,    -1,    -1,    -1,
     838,   839,   840,   841,    -1,   381,    61,   191,    17,    -1,
      65,    20,    -1,    -1,    -1,    -1,   854,   855,    -1,    28,
      -1,    30,    31,    -1,    -1,    -1,    -1,    -1,    37,    -1,
      39,   611,    -1,   613,    -1,    -1,   616,   221,    -1,   619,
      -1,   498,    -1,    -1,   624,    -1,    55,   381,    57,    58,
      59,    60,    -1,   108,    -1,   110,   111,    -1,    -1,    -1,
     115,    -1,    -1,    -1,   644,    -1,    -1,   122,    77,    -1,
      79,    -1,    -1,    -1,   129,   130,   131,   657,    -1,   659,
      -1,    -1,    -1,    -1,   664,    -1,    -1,    -1,    -1,   546,
      -1,    -1,    -1,   550,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     2,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    11,   296,    -1,    -1,    -1,    -1,    -1,    -1,   128,
      20,    -1,   498,    -1,    -1,    -1,    -1,   136,    -1,    -1,
      -1,    -1,    -1,    33,    -1,    -1,   320,    -1,    -1,   323,
      -1,    -1,    -1,    -1,   328,    -1,    -1,    -1,   728,    -1,
      -1,    51,    -1,   733,   611,    -1,   613,    -1,    -1,   616,
      -1,    -1,   619,    -1,   498,    -1,    -1,   624,    -1,    -1,
     546,    -1,    72,   753,   550,    -1,    76,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   764,    -1,    -1,   644,   768,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   381,    -1,    -1,
     657,    -1,   659,    -1,    -1,    -1,    -1,   664,    -1,    -1,
      -1,    -1,   546,    -1,    -1,    -1,   550,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   127,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   611,    -1,   613,    47,    -1,
     616,    -1,    -1,   619,    53,    54,    -1,    -1,   624,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   838,   839,
     840,   841,    -1,    -1,    -1,    -1,    -1,   167,   644,    -1,
      -1,   728,    -1,    -1,   854,   855,   733,   611,    -1,   613,
      -1,   657,   616,   659,    -1,   619,    -1,    -1,   664,    -1,
     624,   191,    -1,    -1,    -1,    -1,   753,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   764,    -1,    -1,
     644,   768,    -1,    -1,   498,    -1,    -1,    -1,    -1,    -1,
      -1,   221,   131,   657,    -1,   659,    -1,    -1,    -1,    -1,
     664,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   728,   162,   163,   164,   165,   733,    -1,    -1,
      -1,    -1,   546,    -1,    -1,    -1,   550,   176,    -1,    -1,
      -1,    -1,    -1,   132,   133,   134,    -1,   753,   137,    -1,
     139,   838,   839,   840,   841,   194,    -1,    -1,   764,    -1,
      -1,    -1,   768,    -1,   728,    -1,   296,   854,   855,   733,
      -1,    -1,    -1,   212,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,    -1,   753,
     320,    -1,    -1,   323,    -1,    -1,    -1,   611,   328,   613,
     764,    -1,   616,    -1,   768,   619,    -1,    -1,    -1,    -1,
     624,    -1,    -1,    -1,    -1,    -1,   132,   133,    -1,    -1,
      -1,   137,    -1,   139,    -1,    -1,    -1,    -1,    -1,    -1,
     644,    -1,   838,   839,   840,   841,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   657,    -1,   659,    -1,    -1,   854,   855,
     664,   381,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   303,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   838,   839,   840,   841,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   327,    -1,
     854,   855,    -1,    10,    -1,    -1,    -1,    -1,    15,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,
      -1,    -1,    -1,    -1,   728,    -1,    -1,    -1,    -1,   733,
      -1,    -1,     2,    -1,    13,    -1,    -1,    -1,    -1,    18,
      -1,    11,    -1,    22,    23,    24,    -1,    -1,    -1,   753,
      20,    30,    -1,    32,    61,    -1,    -1,    -1,    65,    -1,
     764,    -1,    -1,    33,   768,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,   498,    -1,
      -1,    51,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,    -1,   106,
     107,   108,    72,   110,   111,   112,    76,   114,   115,   116,
     117,   118,   119,   120,   121,   122,    95,   124,   125,   126,
      -1,    -1,   129,   130,   131,    -1,   546,    -1,    -1,    24,
     550,    -1,    -1,   140,   838,   839,   840,   841,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     854,   855,    -1,    -1,    -1,    -1,    -1,   127,    -1,   488,
     489,    -1,    -1,   492,   493,    -1,    61,    -1,    -1,   148,
      65,    -1,    -1,   152,    -1,    -1,    -1,    -1,    -1,   158,
      -1,   160,    -1,    -1,    -1,    -1,    -1,   166,    -1,    -1,
     169,   611,    -1,   613,    -1,    -1,   616,   167,    -1,   619,
     179,    -1,   181,    -1,   624,   184,    -1,    -1,    -1,   104,
      -1,   106,   107,   108,    -1,   110,   111,   112,   197,    -1,
     115,   191,    -1,    -1,   644,    -1,   121,   122,    -1,    -1,
      -1,   126,    -1,    -1,   129,   130,   131,   657,    -1,   659,
      -1,    -1,    -1,    -1,   664,    -1,    -1,    -1,    -1,    -1,
      -1,   221,    -1,    -1,    -1,   234,    -1,    -1,    -1,    -1,
     239,   240,   241,   242,    -1,    -1,    -1,    -1,   597,   598,
      -1,     3,    -1,    -1,    -1,    -1,    -1,   256,    10,   608,
      -1,   610,    -1,    15,    -1,    -1,   615,    -1,    -1,   618,
      -1,    -1,   621,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   728,    -1,
     289,   290,    -1,   733,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   650,    -1,    -1,    -1,    -1,   296,    -1,    -1,    -1,
      -1,    -1,    -1,   753,    -1,   314,    -1,   316,    -1,    -1,
      -1,    -1,    -1,    -1,   764,    -1,    -1,    -1,   768,    -1,
     320,    -1,    -1,   323,    -1,    -1,   335,    -1,    90,    91,
      92,    93,    94,    95,    -1,   344,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   355,    -1,   110,    -1,
      -1,    -1,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,    -1,   126,    -1,    -1,   129,   130,   131,
     132,    -1,   134,    -1,    -1,   137,    -1,    -1,    -1,    -1,
      -1,   381,   391,    -1,    -1,    -1,    -1,    -1,   838,   839,
     840,   841,    -1,    -1,    -1,    -1,   755,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   854,   855,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,     7,     8,    -1,    -1,    -1,
      12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    26,   794,   795,    -1,   797,   798,
      32,    33,    34,    -1,    36,    -1,    24,    -1,    -1,    41,
      42,    -1,    44,   812,    46,    47,    -1,    -1,    -1,    -1,
      -1,   820,    54,   822,    56,    -1,    -1,    -1,    -1,   478,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,
      -1,    -1,    -1,    61,    -1,    -1,    -1,    65,    -1,    -1,
      -1,    -1,    -1,   502,    -1,    -1,    -1,   506,   498,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   105,   523,    -1,    -1,    -1,    -1,   528,
      -1,    -1,    -1,   882,    -1,    -1,   104,    -1,   106,   107,
     108,   123,   110,   111,   112,    -1,    -1,   115,   116,   117,
      -1,   119,   120,   121,   122,   137,   546,   139,   126,   558,
     550,   129,   130,   131,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     1,    -1,     3,     4,     5,     6,     7,     8,
      -1,    10,    -1,    12,    -1,    -1,    15,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    24,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    32,    33,    34,   605,    36,    -1,    -1,
      -1,    -1,    41,    42,    -1,    44,    -1,    46,    47,    -1,
      -1,   611,    -1,   613,    -1,    54,   616,    56,    -1,   619,
     629,     3,    61,    -1,   624,    -1,    65,    -1,    10,    68,
      69,    70,    71,    15,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   644,    -1,    -1,    -1,    -1,    88,
      89,    -1,    -1,    -1,    -1,    -1,    -1,   657,    -1,   659,
      -1,    -1,    -1,    -1,   664,   104,   105,   106,   107,   108,
      -1,   110,   111,   112,   683,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,    -1,    -1,
     129,   130,   131,    -1,    -1,    -1,   135,    -1,   137,    -1,
     139,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    90,    91,
      92,    93,    94,    95,    -1,    -1,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,    -1,    -1,   110,    -1,
      -1,    -1,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,    -1,   126,    -1,    -1,   129,   130,   131,
     132,    -1,   134,   753,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   771,    -1,   764,    -1,    -1,    -1,   768,     0,
       1,   780,     3,     4,     5,     6,     7,     8,    -1,    -1,
      24,    12,    13,    14,    -1,    -1,    17,    18,    19,    20,
      21,    22,    23,    -1,    25,    26,    -1,    28,    -1,    30,
      31,    32,    33,    34,    -1,    36,    37,    -1,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    61,    49,    -1,
      -1,    65,    53,    54,    55,    56,    57,    58,    59,    60,
      -1,    62,    63,    64,    -1,    66,    67,    68,    69,    70,
      71,    -1,    73,    -1,    75,    76,    77,    -1,    79,    80,
      81,    -1,    -1,    84,    -1,    86,    -1,    -1,    89,    -1,
     104,    -1,   106,   107,   108,    -1,   110,   111,    -1,    -1,
      -1,   115,    -1,   104,   105,   106,   107,   121,   122,    -1,
      -1,   112,   126,    -1,    -1,   129,   130,   131,    -1,    -1,
     121,    -1,   123,    -1,   125,   126,    -1,   128,    -1,    -1,
     131,    -1,    -1,    -1,   135,    -1,   137,     1,   139,     3,
       4,     5,     6,     7,     8,    -1,    10,    -1,    12,    13,
      14,    15,    -1,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    -1,    30,    31,    32,    33,
      34,    -1,    36,    37,    -1,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    -1,    49,    -1,    -1,    -1,    53,
      54,    -1,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    -1,    73,
      -1,    75,    76,    77,    -1,    79,    80,    81,    -1,    -1,
      84,    -1,    86,    -1,    -1,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     104,   105,   106,   107,   108,   109,   110,   111,   112,    -1,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,    -1,   128,   129,   130,   131,    -1,    -1,
      -1,   135,   136,   137,     1,   139,     3,     4,     5,     6,
       7,     8,    -1,    -1,    -1,    12,    13,    14,    -1,    -1,
      17,    18,    19,    20,    21,    22,    23,    -1,    25,    26,
      -1,    28,    -1,    30,    31,    32,    33,    34,    -1,    36,
      37,    -1,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    -1,    49,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    58,    59,    60,    -1,    62,    63,    64,    -1,    66,
      67,    68,    69,    70,    71,    -1,    73,    -1,    75,    76,
      77,    -1,    79,    80,    81,    -1,    -1,    84,    -1,    86,
      -1,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,   105,   106,
     107,    -1,    -1,    -1,    -1,   112,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   121,    -1,   123,    -1,   125,   126,
     127,   128,    -1,    -1,   131,    -1,    -1,    -1,   135,   136,
     137,     1,   139,     3,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    12,    13,    14,    -1,    -1,    17,    18,    19,
      20,    21,    22,    23,    -1,    25,    26,    -1,    28,    -1,
      30,    31,    32,    33,    34,    -1,    36,    37,    -1,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    -1,    49,
      -1,    -1,    -1,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    62,    63,    64,    -1,    66,    67,    68,    69,
      70,    71,    -1,    73,    -1,    75,    76,    77,    -1,    79,
      80,    81,    -1,    -1,    84,    -1,    86,    -1,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   104,   105,   106,   107,    -1,    -1,
      -1,    -1,   112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   121,    -1,   123,    -1,   125,   126,    -1,   128,    -1,
      -1,   131,    -1,    -1,    -1,   135,   136,   137,     1,   139,
       3,     4,     5,     6,     7,     8,    -1,    -1,    -1,    12,
      13,    14,    -1,    -1,    17,    18,    19,    20,    21,    22,
      23,    -1,    25,    26,    -1,    28,    -1,    30,    31,    32,
      33,    34,    -1,    36,    37,    -1,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    -1,    49,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    58,    59,    60,    -1,    62,
      63,    64,    -1,    66,    67,    68,    69,    70,    71,    -1,
      73,    -1,    75,    76,    77,    -1,    79,    80,    81,    -1,
      -1,    84,    -1,    86,    -1,    -1,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   104,   105,   106,   107,    -1,    -1,    -1,    -1,   112,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   121,    -1,
     123,    -1,   125,   126,    -1,   128,    -1,    -1,   131,    -1,
      -1,    -1,   135,   136,   137,     1,   139,     3,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    12,    13,    14,    -1,
      -1,    17,    18,    19,    20,    21,    22,    23,    -1,    25,
      26,    -1,    28,    -1,    30,    31,    32,    33,    34,    -1,
      36,    37,    -1,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    -1,    49,    -1,    -1,    -1,    53,    54,    55,
      56,    57,    58,    59,    60,    -1,    62,    63,    64,    -1,
      66,    67,    68,    69,    70,    71,    -1,    73,    -1,    75,
      76,    77,    -1,    79,    80,    81,    -1,    -1,    84,    -1,
      86,    -1,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,   105,
     106,   107,    -1,    -1,    -1,    -1,   112,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   121,    -1,   123,    -1,   125,
     126,    -1,   128,    -1,    -1,   131,    -1,    -1,    -1,   135,
     136,   137,     1,   139,     3,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    12,    13,    14,    -1,    -1,    17,    18,
      19,    20,    21,    22,    23,    -1,    25,    26,    -1,    28,
      -1,    30,    31,    32,    33,    34,    -1,    36,    37,    -1,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    -1,
      49,    -1,    -1,    -1,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    62,    63,    64,    -1,    66,    67,    68,
      69,    70,    71,    -1,    73,    -1,    75,    76,    77,    -1,
      79,    80,    81,    -1,    -1,    84,    -1,    86,    -1,    -1,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   104,   105,   106,   107,    -1,
      -1,    -1,    -1,   112,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   121,    -1,   123,    -1,   125,   126,    -1,   128,
      -1,    -1,   131,    -1,    -1,    -1,   135,   136,   137,     1,
     139,     3,     4,     5,     6,     7,     8,    -1,    -1,    -1,
      12,    13,    14,    -1,    -1,    17,    18,    19,    20,    21,
      22,    23,    -1,    25,    26,    -1,    28,    -1,    30,    31,
      32,    33,    34,    -1,    36,    37,    -1,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    -1,    49,    -1,    -1,
      -1,    53,    54,    55,    56,    57,    58,    59,    60,    -1,
      62,    63,    64,    -1,    66,    67,    68,    69,    70,    71,
      -1,    73,    -1,    75,    76,    77,    -1,    79,    80,    81,
      -1,    -1,    84,    -1,    86,    -1,    -1,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   104,   105,   106,   107,    -1,    -1,    -1,    -1,
     112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   121,
      -1,   123,    -1,   125,   126,    -1,   128,    -1,    -1,   131,
      -1,    -1,    -1,   135,    -1,   137,     1,   139,     3,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    12,    13,    14,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    -1,
      25,    26,    -1,    28,    -1,    30,    31,    32,    33,    34,
      -1,    36,    37,    -1,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    -1,    49,    -1,    -1,    -1,    53,    54,
      -1,    56,    57,    58,    59,    60,    -1,    62,    63,    64,
      -1,    66,    67,    68,    69,    70,    71,    -1,    73,    -1,
      75,    76,    77,    -1,    79,    80,    81,    -1,    -1,    84,
      -1,    86,    -1,    -1,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,
     105,   106,   107,    -1,    -1,    -1,    -1,   112,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   121,    -1,   123,    -1,
     125,   126,    -1,   128,    -1,    -1,   131,    -1,    -1,    -1,
     135,    -1,   137,     1,   139,     3,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    12,    13,    14,    -1,    -1,    17,
      18,    19,    20,    21,    22,    23,    -1,    25,    26,    -1,
      28,    -1,    30,    31,    32,    33,    34,    -1,    36,    37,
      -1,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      -1,    49,    -1,    -1,    -1,    53,    54,    -1,    56,    57,
      58,    59,    60,    -1,    62,    63,    64,    -1,    66,    67,
      68,    69,    70,    71,    -1,    73,    -1,    75,    76,    77,
      -1,    79,    80,    81,    -1,    -1,    84,    -1,    86,    -1,
      -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   104,   105,   106,   107,
      -1,    -1,    -1,    -1,   112,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   121,    -1,   123,    -1,   125,   126,    -1,
     128,    -1,    -1,   131,    -1,    -1,    -1,   135,    -1,   137,
       1,   139,     3,     4,     5,     6,     7,     8,    -1,    -1,
      -1,    12,    13,    14,    -1,    -1,    17,    18,    19,    20,
      21,    22,    23,    -1,    25,    26,    -1,    28,    -1,    30,
      31,    32,    33,    34,    -1,    36,    37,    -1,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    -1,    49,    -1,
      -1,    -1,    53,    54,    -1,    56,    57,    58,    59,    60,
      -1,    62,    63,    64,    -1,    66,    67,    68,    69,    70,
      71,    -1,    73,    -1,    75,    76,    77,    -1,    79,    80,
      81,    -1,    -1,    84,    -1,    86,    -1,    -1,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   104,   105,   106,   107,    -1,    -1,    -1,
      -1,   112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     121,    -1,   123,    -1,   125,   126,    -1,   128,    -1,    -1,
     131,    -1,    -1,    -1,   135,    -1,   137,     1,   139,     3,
       4,     5,     6,     7,     8,    -1,    -1,    -1,    12,    13,
      14,    -1,    -1,    17,    18,    19,    20,    21,    22,    23,
      -1,    25,    26,    -1,    28,    -1,    30,    31,    32,    33,
      34,    -1,    36,    37,    -1,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    -1,    49,    -1,    -1,    -1,    53,
      54,    -1,    56,    57,    58,    59,    60,    -1,    62,    63,
      64,    -1,    66,    67,    68,    69,    70,    71,    -1,    73,
      -1,    75,    76,    77,    -1,    79,    80,    81,    -1,    -1,
      84,    -1,    86,    -1,    -1,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     104,   105,   106,   107,    -1,    -1,    -1,    -1,   112,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   121,    -1,   123,
      -1,   125,   126,    -1,   128,    -1,    -1,   131,    -1,    -1,
      -1,   135,    -1,   137,     1,   139,     3,     4,     5,     6,
       7,     8,    -1,    -1,    -1,    12,    13,    14,    -1,    -1,
      17,    18,    19,    20,    21,    22,    23,    -1,    25,    26,
      -1,    28,    -1,    30,    31,    32,    33,    34,    -1,    36,
      37,    -1,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    -1,    49,    -1,    -1,    -1,    53,    54,    -1,    56,
      57,    58,    59,    60,    -1,    62,    63,    64,    -1,    66,
      67,    68,    69,    70,    71,    -1,    73,    -1,    75,    76,
      77,    -1,    79,    80,    81,    -1,    -1,    84,    -1,    86,
      -1,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,   105,   106,
     107,    -1,    -1,    -1,    -1,   112,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   121,    -1,   123,    -1,   125,   126,
      -1,   128,    -1,    -1,   131,    -1,    -1,    -1,   135,    -1,
     137,     1,   139,     3,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    12,    13,    14,    -1,    -1,    17,    18,    19,
      20,    21,    22,    23,    -1,    25,    26,    -1,    28,    -1,
      30,    31,    32,    33,    34,    -1,    36,    37,    -1,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    -1,    49,
      -1,    -1,    -1,    53,    54,    -1,    56,    57,    58,    59,
      60,    -1,    62,    63,    64,    -1,    66,    67,    68,    69,
      70,    71,    -1,    73,    -1,    75,    76,    77,    -1,    79,
      80,    81,    -1,    -1,    84,    -1,    86,    -1,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   104,   105,   106,   107,    -1,    -1,
      -1,    -1,   112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   121,    -1,   123,    -1,   125,   126,    -1,   128,    -1,
      -1,   131,    -1,    -1,    -1,   135,    -1,   137,     1,   139,
       3,     4,     5,     6,     7,     8,    -1,    -1,    -1,    12,
      13,    14,    -1,    -1,    17,    18,    19,    20,    21,    22,
      23,    -1,    25,    26,    -1,    28,    -1,    30,    31,    32,
      33,    34,    -1,    36,    37,    -1,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    -1,    49,    -1,    -1,    -1,
      53,    54,    -1,    56,    57,    58,    59,    60,    -1,    62,
      63,    64,    -1,    66,    67,    68,    69,    70,    71,    -1,
      73,    -1,    75,    76,    77,    -1,    79,    80,    81,    -1,
      -1,    84,    -1,    86,    -1,    -1,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   104,   105,   106,   107,    -1,    -1,    -1,    -1,   112,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   121,    -1,
     123,    -1,   125,   126,    -1,   128,    -1,    -1,   131,    -1,
      -1,    -1,   135,    -1,   137,     1,   139,     3,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    12,    13,    14,    -1,
      -1,    17,    18,    19,    20,    21,    22,    23,    -1,    25,
      26,    -1,    28,    -1,    30,    31,    32,    33,    34,    -1,
      36,    37,    -1,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    -1,    49,    -1,    -1,    -1,    53,    54,    -1,
      56,    57,    58,    59,    60,    -1,    62,    63,    64,    -1,
      66,    67,    68,    69,    70,    71,    -1,    73,    -1,    75,
      76,    77,    -1,    79,    80,    81,    -1,    -1,    84,    -1,
      86,    -1,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,   105,
     106,   107,    -1,    -1,    -1,    -1,   112,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   121,    -1,   123,    -1,   125,
     126,    -1,   128,    -1,    -1,   131,    -1,    -1,    -1,   135,
      -1,   137,     1,   139,     3,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    12,    13,    14,    -1,    -1,    17,    18,
      19,    20,    21,    22,    23,    -1,    25,    26,    -1,    28,
      -1,    30,    31,    32,    33,    34,    -1,    36,    37,    -1,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    -1,
      49,    -1,    -1,    -1,    53,    54,    -1,    56,    57,    58,
      59,    60,    -1,    62,    63,    64,    -1,    66,    67,    68,
      69,    70,    71,    -1,    73,    -1,    75,    76,    77,    -1,
      79,    80,    81,    -1,    -1,    84,    -1,    86,    -1,    -1,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   104,   105,   106,   107,    -1,
      -1,    -1,    -1,   112,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   121,    -1,   123,    -1,   125,   126,    -1,   128,
      -1,    -1,   131,    -1,    -1,    -1,   135,    -1,   137,     1,
     139,     3,     4,     5,     6,     7,     8,    -1,    -1,    -1,
      12,    13,    14,    -1,    -1,    17,    18,    19,    20,    21,
      22,    23,    -1,    25,    26,    -1,    28,    -1,    30,    31,
      32,    33,    34,    -1,    36,    37,    -1,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    -1,    49,    -1,    -1,
      -1,    53,    54,    -1,    56,    57,    58,    59,    60,    -1,
      62,    63,    64,    -1,    66,    67,    68,    69,    70,    71,
      -1,    73,    -1,    75,    76,    77,    -1,    79,    80,    81,
      -1,    -1,    84,    -1,    86,    -1,    -1,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   104,   105,   106,   107,    -1,    -1,    -1,    -1,
     112,     1,    -1,     3,     4,     5,     6,     7,     8,   121,
      10,   123,    12,   125,   126,    15,   128,    -1,    -1,   131,
      -1,    -1,    -1,   135,    24,   137,    26,   139,    -1,    -1,
      -1,    -1,    32,    33,    34,    -1,    36,    -1,    -1,    -1,
      -1,    41,    42,    -1,    44,    -1,    46,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    -1,    56,    -1,    -1,    -1,
      -1,    61,    -1,    -1,    -1,    65,    -1,    -1,    68,    69,
      70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   104,   105,   106,   107,   108,    -1,
     110,   111,   112,    -1,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,    -1,    -1,   129,
     130,   131,    -1,    -1,    -1,   135,    -1,   137,     1,   139,
       3,     4,     5,     6,     7,     8,    -1,    -1,    -1,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    32,
      33,    34,    -1,    36,    -1,    -1,    -1,    -1,    41,    42,
      -1,    44,    -1,    46,    47,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   104,   105,   106,   107,    -1,    -1,    -1,     1,   112,
       3,     4,     5,     6,     7,     8,    -1,    -1,   121,    12,
     123,    -1,   125,   126,    -1,    -1,    -1,    -1,   131,    -1,
      -1,    -1,   135,    26,   137,    -1,   139,    -1,    -1,    32,
      33,    34,    -1,    36,    -1,    -1,    -1,    -1,    41,    42,
      -1,    44,    -1,    46,    47,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   104,   105,   106,   107,    -1,    -1,    -1,    -1,   112,
       3,     4,     5,     6,     7,     8,    -1,    -1,   121,    12,
     123,    -1,   125,   126,    -1,    -1,    -1,    -1,   131,    -1,
      -1,    -1,   135,    26,   137,    -1,   139,    -1,    -1,    32,
      33,    34,    -1,    36,    -1,    -1,    -1,    -1,    41,    42,
      -1,    44,    -1,    46,    47,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   104,   105,   106,   107,    -1,    -1,    -1,    -1,   112,
       3,     4,     5,     6,     7,     8,    -1,    -1,   121,    12,
     123,    -1,   125,   126,   127,    -1,    -1,    -1,   131,    -1,
      -1,    -1,   135,    26,   137,    -1,   139,   140,    -1,    32,
      33,    34,    -1,    36,    -1,    -1,    -1,    -1,    41,    42,
      -1,    44,    -1,    46,    47,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   104,   105,   106,   107,    -1,    -1,    -1,    -1,   112,
       3,     4,     5,     6,     7,     8,    -1,    -1,   121,    12,
     123,    -1,   125,   126,   127,    -1,    -1,    -1,   131,    -1,
      -1,    -1,   135,    26,   137,    -1,   139,   140,    -1,    32,
      33,    34,    -1,    36,    -1,    -1,    -1,    -1,    41,    42,
      -1,    44,    -1,    46,    47,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   104,   105,   106,   107,    -1,    -1,    -1,    -1,   112,
      -1,    -1,     3,     4,     5,     6,     7,     8,   121,    -1,
     123,    12,   125,   126,    -1,    -1,    -1,    -1,   131,    -1,
      21,    -1,   135,    -1,   137,    26,   139,   140,    -1,    -1,
      -1,    32,    33,    34,    35,    36,    -1,    38,    -1,    -1,
      41,    42,    -1,    44,    -1,    46,    47,    -1,    -1,    -1,
      -1,    52,    53,    54,    -1,    56,    -1,    -1,    -1,    -1,
      -1,    62,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,
      71,    -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   104,   105,   106,   107,    -1,    -1,    -1,
      -1,   112,     3,     4,     5,     6,     7,     8,    -1,    -1,
     121,    12,   123,    -1,   125,   126,    -1,    -1,    -1,    -1,
     131,    -1,    -1,    -1,   135,    26,   137,    -1,   139,    -1,
      -1,    32,    33,    34,    -1,    36,    -1,    -1,    -1,    -1,
      41,    42,    -1,    44,    -1,    46,    47,    -1,    -1,    -1,
      -1,    -1,    -1,    54,    -1,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,
      71,    -1,    -1,    -1,    -1,    -1,    -1,    78,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   104,   105,   106,   107,    -1,    -1,    -1,
      -1,   112,   113,    -1,     3,     4,     5,     6,     7,     8,
     121,    -1,   123,    12,   125,   126,   127,    -1,    -1,    -1,
     131,    -1,    -1,    -1,   135,    -1,   137,    26,   139,    -1,
      -1,    -1,    -1,    32,    33,    34,    -1,    36,    -1,    -1,
      -1,    -1,    41,    42,    -1,    44,    -1,    46,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      69,    70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    78,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   104,   105,   106,   107,    -1,
      -1,    -1,    -1,   112,     3,     4,     5,     6,     7,     8,
      -1,    -1,   121,    12,   123,    -1,   125,   126,   127,    -1,
      -1,    -1,   131,    -1,    -1,    -1,   135,    26,   137,   138,
     139,    -1,    -1,    32,    33,    34,    -1,    36,    -1,    -1,
      -1,    -1,    41,    42,    -1,    44,    -1,    46,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      69,    70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    78,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   104,   105,   106,   107,    -1,
      -1,    -1,    -1,   112,     3,     4,     5,     6,     7,     8,
      -1,    -1,   121,    12,   123,    -1,   125,   126,   127,    -1,
      -1,    -1,   131,    -1,    -1,    -1,   135,    26,   137,   138,
     139,    -1,    -1,    32,    33,    34,    -1,    36,    -1,    -1,
      -1,    -1,    41,    42,    -1,    44,    -1,    46,    47,    -1,
      -1,    -1,    -1,    -1,    53,    54,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      69,    70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,    -1,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   104,   105,   106,   107,    -1,
      -1,    -1,    -1,   112,     3,     4,     5,     6,     7,     8,
      -1,    -1,   121,    12,   123,    -1,   125,   126,    -1,    -1,
      -1,    -1,   131,    -1,    -1,    -1,   135,    26,   137,    -1,
     139,    -1,    -1,    32,    33,    34,    -1,    36,    -1,    -1,
      -1,    -1,    41,    42,    -1,    44,    -1,    46,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      69,    70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   104,   105,   106,   107,    -1,
      -1,    -1,    -1,   112,    -1,    -1,     3,     4,     5,     6,
       7,     8,   121,    -1,   123,    12,   125,   126,   127,    -1,
      -1,    -1,   131,    -1,    -1,    -1,   135,   136,   137,    26,
     139,    -1,    -1,    -1,    -1,    32,    33,    34,    -1,    36,
      -1,    -1,    -1,    -1,    41,    42,    -1,    44,    -1,    46,
      47,    -1,    -1,    -1,    -1,    -1,    -1,    54,    -1,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    69,    70,    71,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,   105,   106,
     107,    -1,    -1,    -1,    -1,   112,     3,     4,     5,     6,
       7,     8,    -1,    -1,   121,    12,   123,    -1,   125,   126,
     127,    -1,    -1,    -1,   131,    -1,    -1,    -1,   135,    26,
     137,    -1,   139,    -1,    -1,    32,    33,    34,    -1,    36,
      -1,    -1,    -1,    -1,    41,    42,    -1,    44,    -1,    46,
      47,    -1,    -1,    -1,    -1,    -1,    -1,    54,    -1,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    69,    70,    71,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,   105,   106,
     107,    -1,    -1,    -1,    -1,   112,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   121,    -1,   123,    -1,   125,   126,
      -1,   128,    -1,    -1,   131,    -1,    -1,    -1,   135,    -1,
     137,    -1,   139,     3,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    25,    26,    -1,    -1,    -1,
      -1,    -1,    32,    33,    34,    -1,    36,    -1,    -1,    -1,
      -1,    41,    42,    -1,    44,    -1,    46,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   104,   105,   106,   107,    -1,    -1,
      -1,    -1,   112,     3,     4,     5,     6,     7,     8,    -1,
      -1,   121,    12,   123,    -1,   125,   126,    -1,    -1,    -1,
      -1,   131,    -1,    -1,    -1,   135,    26,   137,    -1,   139,
      -1,    -1,    32,    33,    34,    -1,    36,    -1,    -1,    -1,
      -1,    41,    42,    -1,    44,    -1,    46,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   104,   105,   106,   107,    -1,    -1,
      -1,    -1,   112,     3,     4,     5,     6,     7,     8,    -1,
      -1,   121,    12,   123,    -1,   125,   126,    -1,    -1,    -1,
      -1,   131,    -1,    -1,    -1,   135,    26,   137,    -1,   139,
      -1,    -1,    32,    33,    34,    -1,    36,    -1,    -1,    -1,
      -1,    41,    42,    -1,    44,    -1,    46,    47,    48,    -1,
      -1,    -1,    -1,    -1,    54,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   104,   105,   106,   107,    -1,    -1,
      -1,    -1,   112,     3,     4,     5,     6,     7,     8,    -1,
      -1,   121,    12,   123,    -1,   125,   126,    -1,    -1,    -1,
      -1,   131,    -1,    -1,    -1,   135,    26,   137,    -1,   139,
      -1,    -1,    32,    33,    34,    -1,    36,    -1,    -1,    -1,
      -1,    41,    42,    -1,    44,    -1,    46,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   104,   105,   106,   107,    -1,    -1,
      -1,    -1,   112,     3,     4,     5,     6,     7,     8,    -1,
      -1,   121,    12,   123,    -1,   125,   126,   127,    -1,    -1,
      -1,   131,    -1,    -1,    -1,   135,    26,   137,    -1,   139,
      -1,    -1,    32,    33,    34,    -1,    36,    -1,    -1,    -1,
      -1,    41,    42,    -1,    44,    -1,    46,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   104,   105,   106,   107,    -1,    -1,
      -1,    -1,   112,     3,     4,     5,     6,     7,     8,    -1,
      -1,   121,    12,   123,    -1,   125,   126,   127,    -1,    -1,
      -1,   131,    -1,    -1,    -1,   135,    26,   137,    -1,   139,
      -1,    -1,    32,    33,    34,    -1,    36,    -1,    -1,    -1,
      -1,    41,    42,    -1,    44,    -1,    46,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   104,   105,   106,   107,    -1,    -1,
      -1,    -1,   112,     3,     4,     5,     6,     7,     8,    -1,
      -1,   121,    12,   123,    -1,   125,   126,   127,    -1,    -1,
      -1,   131,    -1,    -1,    -1,   135,    26,   137,    -1,   139,
      -1,    -1,    32,    33,    34,    -1,    36,    -1,    -1,    -1,
      -1,    41,    42,    -1,    44,    -1,    46,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   104,   105,   106,   107,    -1,    -1,
      -1,    -1,   112,     3,     4,     5,     6,     7,     8,    -1,
      -1,   121,    12,   123,    -1,   125,   126,    -1,    -1,    -1,
      -1,   131,    -1,    -1,    -1,   135,    26,   137,    -1,   139,
      -1,    -1,    32,    33,    34,    -1,    36,    -1,    -1,    -1,
      -1,    41,    42,    -1,    44,    -1,    46,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   104,   105,   106,   107,    -1,    -1,
      -1,    -1,   112,     3,     4,     5,     6,     7,     8,    -1,
      -1,   121,    12,   123,    -1,   125,   126,    -1,    -1,    -1,
      -1,   131,    -1,    -1,    -1,   135,    26,   137,    -1,   139,
      -1,    -1,    32,    33,    34,    -1,    36,    -1,    -1,    -1,
      -1,    41,    42,    -1,    44,    -1,    46,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   104,   105,   106,   107,    -1,    -1,
      -1,    -1,   112,     3,     4,     5,     6,     7,     8,    -1,
      -1,   121,    12,   123,    -1,   125,   126,    -1,    -1,    -1,
      -1,   131,    -1,    -1,    -1,   135,    26,   137,    -1,   139,
      -1,    -1,    32,    33,    34,    -1,    36,    -1,    -1,    -1,
      -1,    41,    42,    -1,    44,    -1,    46,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   104,   105,   106,   107,    -1,    -1,
      -1,    -1,   112,     3,     4,     5,     6,     7,     8,    -1,
      -1,   121,    12,   123,    -1,   125,   126,    -1,    -1,    -1,
      -1,   131,    -1,    -1,    -1,   135,    26,   137,    -1,   139,
      -1,    -1,    32,    33,    34,    -1,    36,    -1,    -1,    -1,
      -1,    41,    42,    -1,    44,    -1,    46,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   104,   105,   106,   107,    -1,    -1,
      -1,    -1,   112,     3,     4,     5,     6,     7,     8,    -1,
      -1,   121,    12,   123,    -1,   125,   126,    -1,    -1,    -1,
      -1,   131,    -1,    -1,    -1,   135,    26,   137,    -1,   139,
      -1,    -1,    32,    33,    34,    -1,    36,    -1,    -1,    -1,
      -1,    41,    42,    -1,    44,    -1,    46,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   104,   105,   106,   107,    -1,    -1,
      -1,    -1,   112,     3,     4,     5,     6,     7,     8,    -1,
      -1,   121,    12,   123,    -1,   125,   126,    -1,    -1,    -1,
      -1,   131,    -1,    -1,    -1,   135,    26,   137,    -1,   139,
      -1,    -1,    32,    33,    34,    -1,    36,    -1,    -1,    -1,
      -1,    41,    42,    -1,    44,    -1,    46,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   104,   105,   106,   107,    -1,    -1,
      -1,    -1,   112,     3,     4,     5,     6,     7,     8,    -1,
      -1,   121,    12,   123,    -1,   125,   126,    -1,    -1,    -1,
      -1,   131,    -1,    -1,    -1,   135,    26,   137,    -1,   139,
      -1,    -1,    32,    33,    34,    -1,    36,    -1,    -1,    -1,
      -1,    41,    42,    -1,    44,    -1,    46,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   104,   105,   106,   107,    -1,    -1,
      -1,    -1,   112,     3,     4,     5,     6,     7,     8,    -1,
      -1,   121,    12,   123,    -1,   125,   126,    -1,    -1,    -1,
      -1,   131,    -1,    -1,    -1,   135,    26,   137,    -1,   139,
      -1,    -1,    32,    33,    34,    -1,    36,    -1,    -1,    -1,
      -1,    41,    42,    -1,    44,    -1,    46,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   104,   105,   106,   107,    -1,    -1,
      -1,    -1,   112,     3,     4,     5,     6,     7,     8,    -1,
      -1,   121,    12,   123,    -1,   125,   126,    -1,    -1,    -1,
      -1,   131,    -1,    -1,    -1,   135,    26,   137,    -1,   139,
      -1,    -1,    32,    33,    34,    -1,    36,    -1,    -1,    -1,
      -1,    41,    42,    -1,    44,    -1,    46,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   104,   105,   106,   107,    -1,    -1,
      -1,    -1,   112,     3,     4,     5,     6,     7,     8,    -1,
      -1,   121,    12,   123,    -1,   125,   126,    -1,    -1,    -1,
      -1,   131,    -1,    -1,    -1,   135,    26,   137,    -1,   139,
      -1,    -1,    32,    33,    34,    -1,    36,    -1,    -1,    -1,
      -1,    41,    42,    -1,    44,    -1,    46,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   104,   105,   106,   107,    -1,    -1,
      -1,    -1,   112,     3,     4,     5,     6,     7,     8,    -1,
      -1,   121,    12,   123,    -1,   125,   126,    -1,    -1,    -1,
      -1,   131,    -1,    -1,    -1,   135,    26,   137,    -1,   139,
      -1,    -1,    32,    33,    34,    -1,    36,    -1,    -1,    -1,
      -1,    41,    42,    -1,    44,    -1,    46,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,    -1,    -1,    -1,    12,    -1,
      -1,    -1,    -1,    -1,   104,   105,   106,   107,    -1,    -1,
      -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    32,    33,
      34,   121,    36,   123,    -1,    -1,   126,    41,    42,    -1,
      44,   131,    46,    47,    -1,   135,    -1,   137,    -1,   139,
      54,    -1,    56,    -1,    -1,    -1,    -1,    10,    -1,    -1,
      -1,    -1,    15,    -1,    68,    69,    70,    71,    -1,    -1,
      -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    90,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   105,    -1,    -1,    -1,   109,    -1,    -1,    61,   113,
      -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,   123,
      -1,    -1,    -1,   127,    10,    -1,    -1,    -1,    -1,    15,
      -1,   135,    85,   137,   138,   139,    89,    -1,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   104,    -1,   106,   107,   108,    -1,   110,   111,   112,
      -1,   114,   115,   116,   117,   118,   119,   120,   121,   122,
      -1,   124,   125,   126,    -1,    61,   129,   130,   131,    65,
      -1,    -1,    -1,    -1,    -1,    -1,    10,   140,    -1,    -1,
      -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    -1,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,    -1,
     106,   107,   108,    -1,   110,   111,   112,    -1,   114,   115,
     116,   117,   118,   119,   120,   121,   122,    61,   124,   125,
     126,    65,    -1,   129,   130,   131,    -1,    -1,    10,    -1,
      -1,    -1,    -1,    15,   140,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    24,    -1,    -1,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     104,    -1,   106,   107,   108,    -1,   110,   111,   112,    -1,
     114,   115,   116,   117,   118,   119,   120,   121,   122,    61,
     124,   125,   126,    65,    -1,   129,   130,   131,    -1,    -1,
      10,    -1,    -1,    -1,    -1,    15,   140,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    24,    -1,    -1,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   104,    -1,   106,   107,   108,    -1,   110,   111,
     112,    -1,   114,   115,   116,   117,   118,   119,   120,   121,
     122,    61,   124,   125,   126,    65,    -1,   129,   130,   131,
      -1,    -1,    10,    -1,    -1,    -1,   138,    15,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    24,    25,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,    -1,
      -1,    -1,    -1,    -1,   104,    -1,   106,   107,   108,    -1,
     110,   111,   112,    -1,   114,   115,   116,   117,   118,   119,
     120,   121,   122,    61,   124,   125,   126,    65,    -1,   129,
     130,   131,    -1,    -1,    10,    -1,    -1,    -1,   138,    15,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    24,    25,
      -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      -1,    -1,    -1,    -1,    -1,    -1,   104,    -1,   106,   107,
     108,    -1,   110,   111,   112,    -1,   114,   115,   116,   117,
     118,   119,   120,   121,   122,    61,   124,   125,   126,    65,
      -1,   129,   130,   131,    -1,    -1,    10,   135,    -1,    -1,
      -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    25,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,    -1,
     106,   107,   108,    -1,   110,   111,   112,    -1,   114,   115,
     116,   117,   118,   119,   120,   121,   122,    61,   124,   125,
     126,    65,    -1,   129,   130,   131,    -1,    -1,    10,   135,
      -1,    -1,    -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    85,    24,    -1,    -1,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     104,    -1,   106,   107,   108,    -1,   110,   111,   112,    -1,
     114,   115,   116,   117,   118,   119,   120,   121,   122,    61,
     124,   125,   126,    65,    -1,   129,   130,   131,    -1,    -1,
      72,   135,    -1,    -1,    -1,    10,    -1,    -1,    -1,    -1,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   104,    -1,   106,   107,   108,    -1,   110,   111,
     112,    -1,   114,   115,   116,   117,   118,   119,   120,   121,
     122,    -1,   124,   125,   126,    -1,    61,   129,   130,   131,
      65,    -1,    -1,   135,    -1,    -1,    -1,    10,    -1,    -1,
      -1,    -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    24,    25,    -1,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,
      -1,   106,   107,   108,    -1,   110,   111,   112,    -1,   114,
     115,   116,   117,   118,   119,   120,   121,   122,    61,   124,
     125,   126,    65,    -1,   129,   130,   131,    -1,    -1,    10,
     135,    -1,    -1,    -1,    15,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    24,    -1,    -1,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   104,    -1,   106,   107,   108,    -1,   110,   111,   112,
      -1,   114,   115,   116,   117,   118,   119,   120,   121,   122,
      61,   124,   125,   126,    65,    -1,   129,   130,   131,    -1,
      -1,    72,   135,    -1,    -1,    -1,    10,    -1,    -1,    -1,
      -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   104,    -1,   106,   107,   108,    -1,   110,
     111,   112,    -1,   114,   115,   116,   117,   118,   119,   120,
     121,   122,    -1,   124,   125,   126,    -1,    61,   129,   130,
     131,    65,    -1,    -1,   135,    -1,    -1,    -1,    72,    -1,
      -1,    -1,    -1,    10,    -1,    -1,    -1,    -1,    15,    -1,
      -1,    -1,    -1,    -1,    -1,    89,    -1,    24,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     104,    -1,   106,   107,   108,    -1,   110,   111,   112,    -1,
     114,   115,   116,   117,   118,   119,   120,   121,   122,    -1,
     124,   125,   126,    -1,    61,   129,   130,   131,    65,    -1,
      -1,   135,    -1,    -1,    -1,    72,    -1,    -1,    -1,    -1,
      10,    -1,    -1,    -1,    -1,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,    -1,   106,
     107,   108,    -1,   110,   111,   112,    -1,   114,   115,   116,
     117,   118,   119,   120,   121,   122,    -1,   124,   125,   126,
      -1,    61,   129,   130,   131,    65,    -1,    -1,   135,    -1,
      -1,    -1,    72,    -1,    -1,    -1,    -1,    10,    -1,    -1,
      -1,    -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   104,    -1,   106,   107,   108,    -1,
     110,   111,   112,    -1,   114,   115,   116,   117,   118,   119,
     120,   121,   122,    -1,   124,   125,   126,    -1,    61,   129,
     130,   131,    65,    -1,    -1,   135,    -1,    -1,    -1,    72,
      -1,    -1,    -1,    -1,    10,    -1,    -1,    -1,    -1,    15,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   104,    -1,   106,   107,   108,    -1,   110,   111,   112,
      -1,   114,   115,   116,   117,   118,   119,   120,   121,   122,
      -1,   124,   125,   126,    -1,    61,   129,   130,   131,    65,
      -1,    -1,   135,    -1,    -1,    -1,    72,    -1,    -1,    -1,
      -1,    10,    -1,    -1,    -1,    -1,    15,    -1,    -1,    -1,
      -1,    -1,    -1,    89,    -1,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,    -1,
     106,   107,   108,    -1,   110,   111,   112,    -1,   114,   115,
     116,   117,   118,   119,   120,   121,   122,    -1,   124,   125,
     126,    -1,    61,   129,   130,   131,    65,    -1,    -1,   135,
      -1,    -1,    -1,    72,    -1,    -1,    -1,    -1,    10,    -1,
      -1,    -1,    -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,
      89,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   104,    -1,   106,   107,   108,
      -1,   110,   111,   112,    -1,   114,   115,   116,   117,   118,
     119,   120,   121,   122,    -1,   124,   125,   126,    -1,    61,
     129,   130,   131,    65,    -1,    -1,   135,    -1,    -1,    -1,
      72,    -1,    -1,    -1,    -1,    10,    -1,    -1,    -1,    -1,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   104,    -1,   106,   107,   108,    -1,   110,   111,
     112,    -1,   114,   115,   116,   117,   118,   119,   120,   121,
     122,    -1,   124,   125,   126,    -1,    61,   129,   130,   131,
      65,    -1,    -1,   135,    -1,    -1,    -1,    10,    -1,    -1,
      -1,    -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    24,    -1,    -1,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,
      -1,   106,   107,   108,    -1,   110,   111,   112,    -1,   114,
     115,   116,   117,   118,   119,   120,   121,   122,    61,   124,
     125,   126,    65,    -1,   129,   130,   131,    -1,    -1,    10,
     135,    -1,    -1,    -1,    15,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    24,    -1,    -1,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    -1,    -1,    -1,    -1,    -1,
      -1,   104,    -1,   106,   107,   108,    -1,   110,   111,   112,
      -1,   114,   115,   116,   117,   118,   119,   120,   121,   122,
      61,   124,   125,   126,    65,    -1,   129,   130,   131,    -1,
      -1,   134,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    10,    -1,    85,    -1,    -1,    15,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,
      -1,    29,    -1,   104,    -1,   106,   107,   108,    -1,   110,
     111,   112,    -1,   114,   115,   116,   117,   118,   119,   120,
     121,   122,    50,   124,   125,   126,    10,    -1,   129,   130,
     131,    15,    -1,    61,    -1,    -1,    -1,    65,    -1,    -1,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      10,    89,    -1,    -1,    -1,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    24,    25,   104,    61,   106,   107,
     108,    65,   110,   111,   112,    35,   114,   115,   116,   117,
     118,   119,   120,   121,   122,    -1,   124,   125,   126,    -1,
      -1,   129,   130,   131,    10,    89,    -1,    -1,    -1,    15,
      -1,    61,    -1,    -1,    -1,    65,    -1,    -1,    24,    -1,
     104,    -1,   106,   107,   108,    -1,   110,   111,   112,    -1,
     114,   115,   116,   117,   118,   119,   120,   121,   122,    89,
     124,   125,   126,    -1,    -1,   129,   130,   131,    -1,    -1,
      -1,    -1,    -1,    -1,   104,    61,   106,   107,   108,    65,
     110,   111,   112,    -1,   114,   115,   116,   117,   118,   119,
     120,   121,   122,    -1,   124,   125,   126,    10,    -1,   129,
     130,   131,    15,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,   104,    -1,
     106,   107,   108,    -1,   110,   111,   112,    -1,   114,   115,
     116,   117,   118,   119,   120,   121,   122,    -1,   124,   125,
     126,    10,   128,   129,   130,   131,    15,    -1,    61,    -1,
      -1,    -1,    65,    -1,    -1,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    10,    89,    -1,    -1,    -1,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,
      -1,   104,    61,   106,   107,   108,    65,   110,   111,   112,
      -1,   114,   115,   116,   117,   118,   119,   120,   121,   122,
      -1,   124,   125,   126,    -1,   128,   129,   130,   131,    10,
      89,    -1,    -1,    -1,    15,    -1,    61,    -1,    -1,    -1,
      65,    -1,    -1,    24,    -1,   104,    -1,   106,   107,   108,
      -1,   110,   111,   112,    -1,   114,   115,   116,   117,   118,
     119,   120,   121,   122,    89,   124,   125,   126,    -1,   128,
     129,   130,   131,    -1,    -1,    -1,    -1,    -1,    -1,   104,
      61,   106,   107,   108,    65,   110,   111,   112,    -1,   114,
     115,   116,   117,   118,   119,   120,   121,   122,    -1,   124,
     125,   126,    10,   128,   129,   130,   131,    15,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,
      -1,    -1,    -1,   104,    -1,   106,   107,   108,    -1,   110,
     111,   112,    -1,   114,   115,   116,   117,   118,   119,   120,
     121,   122,    -1,   124,   125,   126,    10,   128,   129,   130,
     131,    15,    -1,    61,    -1,    -1,    -1,    65,    -1,    -1,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   104,    61,   106,   107,
     108,    65,   110,   111,   112,    -1,   114,   115,   116,   117,
     118,   119,   120,   121,   122,    -1,   124,   125,   126,    -1,
     128,   129,   130,   131,    88,    89,    -1,    10,    -1,    -1,
      -1,    -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     104,    24,   106,   107,   108,    -1,   110,   111,   112,    -1,
     114,   115,   116,   117,   118,   119,   120,   121,   122,    -1,
     124,   125,   126,    -1,    -1,   129,   130,   131,    -1,    -1,
      -1,    10,    -1,    -1,    -1,    -1,    15,    -1,    61,    -1,
      -1,    -1,    65,    -1,    -1,    24,    -1,    -1,    -1,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    10,    89,    -1,    -1,    -1,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,
      -1,   104,    61,   106,   107,   108,    65,   110,   111,   112,
      -1,   114,   115,   116,   117,   118,   119,   120,   121,   122,
      -1,   124,   125,   126,    -1,    -1,   129,   130,   131,    10,
      89,    -1,    -1,    -1,    15,    -1,    61,    -1,    -1,    -1,
      65,    -1,    -1,    24,    -1,   104,    -1,   106,   107,   108,
      -1,   110,   111,   112,    -1,   114,   115,   116,   117,   118,
     119,   120,   121,   122,    89,   124,   125,   126,    -1,   128,
     129,   130,   131,    -1,    -1,    -1,    -1,    -1,    -1,   104,
      61,   106,   107,   108,    65,   110,   111,   112,    -1,   114,
     115,   116,   117,   118,   119,   120,   121,   122,    -1,   124,
     125,   126,    10,   128,   129,   130,   131,    15,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,
      -1,    -1,    -1,   104,    -1,   106,   107,   108,    -1,   110,
     111,   112,    -1,   114,   115,   116,   117,   118,   119,   120,
     121,   122,    -1,   124,   125,   126,    10,   128,   129,   130,
     131,    15,    -1,    61,    -1,    -1,    -1,    65,    -1,    -1,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      10,    89,    -1,    -1,    -1,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    24,    -1,   104,    61,   106,   107,
     108,    65,   110,   111,   112,    -1,   114,   115,   116,   117,
     118,   119,   120,   121,   122,    -1,   124,   125,   126,    -1,
     128,   129,   130,   131,    10,    89,    -1,    -1,    -1,    15,
      -1,    61,    -1,    -1,    -1,    65,    -1,    -1,    24,    -1,
     104,    -1,   106,   107,   108,    -1,   110,   111,   112,    -1,
     114,   115,   116,   117,   118,   119,   120,   121,   122,    89,
     124,   125,   126,    -1,   128,   129,   130,   131,    -1,    -1,
      -1,    -1,    -1,    -1,   104,    61,   106,   107,   108,    65,
     110,   111,   112,    -1,   114,   115,   116,   117,   118,   119,
     120,   121,   122,    -1,   124,   125,   126,    10,   128,   129,
     130,   131,    15,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,   104,    -1,
     106,   107,   108,    -1,   110,   111,   112,    -1,   114,   115,
     116,   117,   118,   119,   120,   121,   122,    -1,   124,   125,
     126,    10,   128,   129,   130,   131,    15,    -1,    61,    -1,
      -1,    -1,    65,    -1,    -1,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    10,    89,    -1,    -1,    -1,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,
      -1,   104,    61,   106,   107,   108,    65,   110,   111,   112,
      -1,   114,   115,   116,   117,   118,   119,   120,   121,   122,
      -1,   124,   125,   126,    -1,   128,   129,   130,   131,    10,
      89,    -1,    -1,    -1,    15,    -1,    61,    -1,    -1,    -1,
      65,    -1,    -1,    24,    -1,   104,    -1,   106,   107,   108,
      -1,   110,   111,   112,    -1,   114,   115,   116,   117,   118,
     119,   120,   121,   122,    89,   124,   125,   126,    -1,   128,
     129,   130,   131,    -1,    -1,    -1,    -1,    -1,    -1,   104,
      61,   106,   107,   108,    65,   110,   111,   112,    -1,   114,
     115,   116,   117,   118,   119,   120,   121,   122,    -1,   124,
     125,   126,    10,   128,   129,   130,   131,    15,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,
      -1,    -1,    -1,   104,    -1,   106,   107,   108,    -1,   110,
     111,   112,    -1,   114,   115,   116,   117,   118,   119,   120,
     121,   122,    -1,   124,   125,   126,    10,   128,   129,   130,
     131,    15,    -1,    61,    -1,    -1,    -1,    65,    -1,    -1,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      10,    89,    -1,    -1,    -1,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    24,    -1,   104,    61,   106,   107,
     108,    65,   110,   111,   112,    -1,   114,   115,   116,   117,
     118,   119,   120,   121,   122,    -1,   124,   125,   126,    -1,
     128,   129,   130,   131,    10,    89,    -1,    -1,    -1,    15,
      -1,    61,    -1,    -1,    -1,    65,    -1,    -1,    24,    -1,
     104,    -1,   106,   107,   108,    -1,   110,   111,   112,    -1,
     114,   115,   116,   117,   118,   119,   120,   121,   122,    89,
     124,   125,   126,    -1,   128,   129,   130,   131,    -1,    -1,
      -1,    -1,    -1,    -1,   104,    61,   106,   107,   108,    65,
     110,   111,   112,    -1,   114,   115,   116,   117,   118,   119,
     120,   121,   122,    -1,   124,   125,   126,    10,   128,   129,
     130,   131,    15,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,   104,    -1,
     106,   107,   108,    -1,   110,   111,   112,    -1,   114,   115,
     116,   117,   118,   119,   120,   121,   122,    -1,   124,   125,
     126,    -1,   128,   129,   130,   131,    -1,    -1,    61,    -1,
      -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    10,
      -1,    -1,    -1,    -1,    15,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    24,    -1,    -1,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   104,    -1,   106,   107,   108,    -1,   110,   111,   112,
      -1,   114,   115,   116,   117,   118,   119,   120,   121,   122,
      61,   124,   125,   126,    65,   128,   129,   130,   131,    -1,
      -1,    10,    -1,    -1,    -1,    -1,    15,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    85,    24,    -1,    -1,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   104,    -1,   106,   107,   108,    -1,   110,
     111,   112,    -1,   114,   115,   116,   117,   118,   119,   120,
     121,   122,    61,   124,   125,   126,    65,    -1,   129,   130,
     131,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    10,    -1,    -1,    -1,    -1,    15,    -1,    -1,
      89,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    27,
      -1,    -1,    -1,    -1,    -1,   104,    -1,   106,   107,   108,
      -1,   110,   111,   112,    -1,   114,   115,   116,   117,   118,
     119,   120,   121,   122,    -1,   124,   125,   126,    -1,   128,
     129,   130,   131,    61,    -1,    -1,    -1,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    10,    11,    -1,    -1,    -1,    15,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,
      -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   104,    -1,   106,   107,
     108,    -1,   110,   111,   112,    -1,   114,   115,   116,   117,
     118,   119,   120,   121,   122,    61,   124,   125,   126,    65,
      -1,   129,   130,   131,    -1,    -1,    10,    -1,    -1,    -1,
      -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    -1,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,    -1,
     106,   107,   108,    -1,   110,   111,   112,    -1,   114,   115,
     116,   117,   118,   119,   120,   121,   122,    61,   124,   125,
     126,    65,    -1,   129,   130,   131,    -1,    -1,    10,    -1,
      -1,    -1,    -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    24,    25,    88,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     104,    -1,   106,   107,   108,    -1,   110,   111,   112,    -1,
     114,   115,   116,   117,   118,   119,   120,   121,   122,    61,
     124,   125,   126,    65,    -1,   129,   130,   131,    -1,    -1,
      10,    -1,    -1,    -1,    -1,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    24,    25,    -1,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   104,    -1,   106,   107,   108,    -1,   110,   111,
     112,    -1,   114,   115,   116,   117,   118,   119,   120,   121,
     122,    61,   124,   125,   126,    65,    -1,   129,   130,   131,
      -1,    -1,    10,    -1,    -1,    -1,    -1,    15,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   104,    -1,   106,   107,   108,    -1,
     110,   111,   112,    -1,   114,   115,   116,   117,   118,   119,
     120,   121,   122,    61,   124,   125,   126,    65,    -1,   129,
     130,   131,    -1,    -1,    72,    -1,    -1,    -1,    -1,    10,
      -1,    -1,    -1,    -1,    15,    -1,    -1,    -1,    -1,    -1,
      -1,    89,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   104,    -1,   106,   107,
     108,    -1,   110,   111,   112,    -1,   114,   115,   116,   117,
     118,   119,   120,   121,   122,    -1,   124,   125,   126,    -1,
      61,   129,   130,   131,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    72,    -1,    -1,    -1,    -1,    10,    11,    -1,    -1,
      -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   104,    -1,   106,   107,   108,    -1,   110,
     111,   112,    -1,   114,   115,   116,   117,   118,   119,   120,
     121,   122,    -1,   124,   125,   126,    -1,    61,   129,   130,
     131,    65,    -1,    -1,    -1,    -1,    -1,    -1,    10,    -1,
      -1,    -1,    -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    24,    -1,    -1,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     104,    -1,   106,   107,   108,    -1,   110,   111,   112,    -1,
     114,   115,   116,   117,   118,   119,   120,   121,   122,    61,
     124,   125,   126,    65,    -1,   129,   130,   131,    -1,    -1,
      72,    -1,    -1,    -1,    -1,    10,    -1,    -1,    -1,    -1,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   104,    -1,   106,   107,   108,    -1,   110,   111,
     112,    -1,   114,   115,   116,   117,   118,   119,   120,   121,
     122,    -1,   124,   125,   126,    -1,    61,   129,   130,   131,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    72,    -1,    -1,
      -1,    -1,    10,    -1,    -1,    -1,    -1,    15,    -1,    -1,
      -1,    -1,    -1,    -1,    89,    -1,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,
      -1,   106,   107,   108,    -1,   110,   111,   112,    -1,   114,
     115,   116,   117,   118,   119,   120,   121,   122,    -1,   124,
     125,   126,    -1,    61,   129,   130,   131,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    72,    -1,    -1,    -1,    -1,    10,
      -1,    -1,    -1,    -1,    15,    -1,    -1,    -1,    -1,    -1,
      -1,    89,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   104,    -1,   106,   107,
     108,    -1,   110,   111,   112,    -1,   114,   115,   116,   117,
     118,   119,   120,   121,   122,    -1,   124,   125,   126,    -1,
      61,   129,   130,   131,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    72,    -1,    -1,    -1,    -1,    10,    -1,    -1,    -1,
      -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   104,    -1,   106,   107,   108,    -1,   110,
     111,   112,    -1,   114,   115,   116,   117,   118,   119,   120,
     121,   122,    -1,   124,   125,   126,    -1,    61,   129,   130,
     131,    65,    -1,    -1,    -1,    -1,    -1,    -1,    72,    -1,
      -1,    -1,    -1,    10,    -1,    -1,    -1,    -1,    15,    -1,
      -1,    -1,    -1,    -1,    -1,    89,    -1,    24,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     104,    -1,   106,   107,   108,    -1,   110,   111,   112,    -1,
     114,   115,   116,   117,   118,   119,   120,   121,   122,    -1,
     124,   125,   126,    -1,    61,   129,   130,   131,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    72,    -1,    -1,    -1,    -1,
      10,    -1,    -1,    -1,    -1,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,    -1,   106,
     107,   108,    -1,   110,   111,   112,    -1,   114,   115,   116,
     117,   118,   119,   120,   121,   122,    -1,   124,   125,   126,
      -1,    61,   129,   130,   131,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    10,    -1,    -1,    -1,    -1,    15,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   104,    -1,   106,   107,   108,    -1,
     110,   111,   112,    -1,   114,   115,   116,   117,   118,   119,
     120,   121,   122,    61,   124,   125,   126,    65,    -1,   129,
     130,   131,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    24,    -1,    -1,   104,    -1,   106,   107,
     108,    61,   110,   111,   112,    65,   114,   115,   116,   117,
     118,   119,   120,   121,   122,    -1,   124,   125,   126,    -1,
      -1,   129,   130,   131,    -1,    -1,    24,    -1,    -1,    89,
      61,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   104,    -1,   106,   107,   108,    -1,
     110,   111,   112,    -1,   114,   115,   116,   117,    89,   119,
     120,   121,   122,    61,   124,   125,   126,    65,    -1,   129,
     130,   131,    -1,   104,    -1,   106,   107,   108,    -1,   110,
     111,   112,    -1,   114,   115,   116,   117,    -1,   119,   120,
     121,   122,    -1,   124,    -1,   126,    -1,    -1,   129,   130,
     131,    -1,    -1,    -1,    -1,    -1,   104,    -1,   106,   107,
     108,    -1,   110,   111,   112,    -1,   114,   115,   116,   117,
      -1,   119,   120,   121,   122,    -1,   124,    -1,   126,    -1,
      -1,   129,   130,   131
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   145,   146,     0,     1,     3,     4,     5,     6,     7,
       8,    12,    13,    14,    17,    18,    19,    20,    22,    23,
      25,    26,    28,    30,    31,    32,    33,    34,    36,    37,
      40,    41,    42,    43,    44,    46,    47,    49,    54,    55,
      56,    57,    59,    60,    63,    64,    66,    67,    68,    69,
      70,    71,    73,    75,    76,    77,    79,    80,    84,    86,
      89,   104,   105,   106,   107,   112,   121,   123,   125,   126,
     128,   131,   135,   137,   139,   147,   148,   149,   150,   151,
     152,   157,   158,   159,   161,   164,   165,   166,   167,   168,
     170,   171,   175,   176,   179,   180,   183,   186,   189,   190,
     213,   216,   217,   235,   236,   237,   238,   239,   240,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   258,
     259,   260,   261,   262,   149,   250,    85,   241,   242,   160,
     161,   241,    12,    32,    33,    34,    71,   135,   139,   186,
     235,   239,   248,   249,   250,   251,   253,   254,    77,   160,
     250,   149,   137,   161,     7,   160,   162,     9,    77,   162,
      53,    87,   169,   250,   250,   250,   137,   161,   187,   137,
     161,   218,   219,   149,   250,   250,   250,   250,     7,   137,
      20,    31,   166,   166,   127,   209,   229,   250,   128,   250,
     250,    25,   152,   163,   250,   250,    70,   137,   149,   250,
     250,   152,   159,   250,   251,   152,   159,   250,   161,   214,
     229,   250,   250,   250,   250,   250,   250,   250,   250,   136,
     147,   153,   229,    78,   113,   209,   230,   231,   250,   229,
     250,   257,    55,   149,    45,   161,    39,    58,   204,    21,
      53,    62,    81,   128,   134,    10,    15,    24,    61,    65,
      89,   104,   106,   107,   108,   110,   111,   112,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   124,   125,   126,
     129,   130,   131,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   132,   133,   137,
     139,    61,    65,   137,   149,   128,   135,   152,   250,   250,
     250,   229,    35,   241,   214,   128,   128,    84,   161,   209,
     232,   233,   234,   250,   135,   214,   180,   161,   137,   163,
      25,    35,   163,    25,    35,    85,   163,   244,    72,   152,
     232,   149,   137,   198,    78,   137,   161,   220,   221,     1,
     108,   223,   224,    35,   109,   163,   232,   162,   161,   109,
     128,   128,   135,   149,   163,   137,   232,   128,   172,   128,
     172,   128,    90,   215,   128,   128,    29,    50,   163,   128,
     136,   147,   109,   136,   250,   109,   138,   109,   138,    35,
     109,   140,   244,    88,   109,   140,     7,   161,   108,   181,
     191,    62,   218,   218,   218,   218,   250,   250,   250,   250,
     169,   250,   169,   250,   250,   250,   250,   250,   250,   250,
      26,    77,   161,   250,   250,   250,   250,   250,   250,   250,
     250,   250,   250,   250,   250,   250,   250,   250,   250,   250,
     250,   250,   250,   250,   250,   250,   250,   250,   250,   250,
     250,   250,   250,   250,   250,   232,   232,   169,   250,   169,
     250,    21,    35,    38,    52,    53,    62,    77,   202,   243,
     246,   250,   262,    25,    35,    25,    35,    72,    35,   140,
     169,   250,   163,   128,   250,    88,    90,   138,   109,   161,
     184,   185,   128,   161,    35,   229,    34,   250,   169,   250,
      34,   250,   169,   250,   137,   163,   149,   250,    27,   138,
     199,   200,   201,   202,   188,   221,   109,   138,     1,   139,
     225,   236,    88,    90,   222,   250,   219,   138,   209,   250,
     177,   232,   138,    16,   173,   139,   225,   236,   109,   131,
     154,   156,   250,   154,   155,   136,   138,   138,   230,   138,
     230,   169,   250,   140,   149,   250,   140,   250,   140,   250,
     135,   229,   135,    21,    53,    62,    77,   193,   203,   218,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     138,   140,    35,    62,   235,   109,   138,    61,    61,    34,
     169,   250,    34,   169,   250,   169,   250,   241,   241,   128,
     250,   209,   250,   234,    90,   109,   136,   181,   250,   138,
     250,    25,   163,    25,   163,   250,    25,   163,   244,    25,
     163,   244,   245,   246,    27,    27,   149,   109,   138,   137,
     161,    21,    53,    62,    77,   205,   138,   221,   108,   224,
     229,   250,    48,   250,    51,    82,   136,   178,   138,   161,
     174,   229,   214,   109,   128,    11,   128,   140,   244,   140,
     244,   149,    88,   136,   153,   182,    62,   192,    10,    15,
      90,    91,    92,    93,    94,    95,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   110,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   126,   129,
     130,   131,   132,   134,   137,   161,   194,   195,   196,   235,
     128,   246,   235,   235,   250,    25,    25,   250,    25,    25,
     140,   140,   163,   163,   250,   185,   135,   163,    72,    34,
     250,    34,   250,    72,    34,   250,   163,    34,   250,   163,
     109,   138,   149,   250,   200,   221,   108,   228,    62,   224,
     222,    35,   140,    25,   149,   229,   108,   152,   140,   250,
     250,    34,   149,   250,   140,    34,   149,   250,   140,   250,
     136,    31,    57,    59,   136,   148,   165,   205,   161,   250,
     111,   137,   197,   197,    72,    34,    34,    72,    34,    34,
      34,    34,   182,   250,   250,   250,   250,   250,   250,   246,
     138,    26,    68,    71,   139,   209,   227,   236,   113,   211,
     222,    83,   212,   250,   225,   236,   149,   163,   250,    11,
     250,   149,   250,   149,   165,   224,   138,   161,   195,   196,
     199,   250,   250,   250,   250,   250,   250,   136,    72,    72,
      72,    72,   228,   140,   229,   209,   210,   250,   250,   152,
     164,   208,   140,   250,    72,    72,    74,   206,   197,   197,
     138,    72,    72,    72,    72,    72,    72,   250,   250,   250,
     250,   211,   222,   209,   226,   227,   236,    35,   140,   236,
     250,   250,   212,   250,   226,   227,   128,   207,   208,   140,
     226
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   144,   145,   146,   146,   147,   147,   148,   148,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   150,   150,   151,
     151,   151,   152,   152,   153,   153,   154,   154,   154,   154,
     155,   155,   156,   156,   157,   157,   157,   158,   159,   159,
     159,   159,   159,   159,   159,   159,   159,   159,   159,   159,
     159,   159,   159,   159,   160,   160,   161,   162,   162,   163,
     163,   164,   164,   165,   165,   165,   165,   165,   165,   165,
     166,   166,   167,   168,   168,   168,   168,   168,   168,   168,
     168,   168,   168,   168,   168,   168,   168,   168,   168,   168,
     168,   168,   168,   168,   168,   169,   170,   170,   170,   170,
     171,   171,   171,   171,   171,   171,   172,   172,   173,   174,
     174,   174,   175,   176,   177,   177,   178,   178,   178,   179,
     179,   180,   180,   180,   181,   181,   182,   182,   182,   183,
     184,   184,   184,   185,   185,   187,   188,   186,   189,   189,
     189,   189,   191,   192,   190,   193,   193,   193,   193,   194,
     194,   195,   195,   195,   195,   195,   195,   195,   195,   195,
     195,   195,   195,   195,   195,   195,   195,   195,   195,   195,
     195,   195,   195,   195,   195,   195,   195,   196,   196,   196,
     196,   196,   196,   196,   196,   196,   196,   196,   196,   197,
     197,   198,   199,   199,   199,   200,   200,   200,   200,   201,
     201,   202,   202,   202,   202,   202,   202,   202,   202,   202,
     203,   203,   203,   203,   203,   203,   204,   204,   205,   205,
     205,   205,   205,   205,   206,   206,   207,   207,   208,   208,
     209,   209,   210,   210,   211,   211,   212,   212,   213,   213,
     213,   214,   214,   215,   215,   215,   216,   216,   216,   216,
     216,   217,   217,   217,   218,   218,   219,   219,   219,   220,
     220,   220,   221,   221,   221,   222,   222,   222,   223,   223,
     224,   224,   224,   224,   225,   225,   225,   225,   226,   226,
     226,   227,   227,   227,   227,   227,   228,   228,   228,   228,
     228,   228,   228,   229,   229,   229,   229,   230,   230,   230,
     231,   231,   232,   232,   233,   233,   234,   234,   234,   234,
     234,   235,   236,   236,   236,   236,   236,   236,   236,   236,
     236,   236,   236,   236,   237,   237,   237,   237,   237,   237,
     237,   237,   237,   237,   237,   237,   237,   237,   237,   237,
     237,   238,   239,   240,   240,   240,   240,   240,   240,   240,
     240,   241,   241,   242,   243,   243,   244,   245,   245,   246,
     246,   246,   247,   247,   248,   249,   250,   250,   250,   250,
     250,   250,   250,   250,   250,   250,   250,   250,   250,   250,
     251,   251,   251,   251,   252,   252,   253,   253,   253,   254,
     254,   254,   255,   255,   255,   255,   256,   256,   256,   256,
     256,   256,   256,   256,   256,   256,   256,   257,   257,   258,
     258,   258,   258,   258,   258,   258,   258,   258,   258,   258,
     258,   258,   258,   258,   258,   258,   258,   258,   258,   258,
     258,   258,   259,   259,   259,   259,   259,   259,   260,   260,
     260,   260,   261,   261,   261,   261,   262,   262,   262,   262,
     262,   262,   262
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     2,     2,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     3,     3,     3,     3,     3,     3,
       2,     3,     3,     2,     2,     3,     1,     5,     6,     0,
       1,     1,     2,     3,     1,     2,     1,     3,     3,     5,
       0,     1,     1,     1,     3,     5,     5,     3,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     0,     1,     1,     1,     1,     2,
       1,     2,     3,     1,     1,     2,     2,     1,     1,     1,
       1,     1,     2,     5,     3,     6,     6,     4,     5,     5,
       3,     3,     6,     5,     6,     5,     6,     3,     4,     6,
       7,     6,     7,     4,     5,     4,     4,     3,     6,     5,
       3,     3,     2,     2,     3,     3,     0,     2,     3,     0,
       1,     3,     3,     5,     0,     2,     3,     2,     3,     6,
       8,     1,     1,     1,     0,     2,     0,     2,     3,     5,
       1,     2,     3,     1,     3,     0,     0,     8,     0,     1,
       2,     2,     0,     0,    10,     3,     3,     5,     5,     1,
       3,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       3,     3,     0,     1,     3,     4,     4,     6,     6,     0,
       1,     1,     1,     1,     1,     2,     2,     1,     1,     1,
       0,     1,     1,     2,     1,     1,     1,     1,     0,     1,
       2,     1,     1,     1,     0,     1,     1,     1,     1,     1,
       2,     1,     0,     1,     2,     2,     0,     2,     3,     4,
       4,     2,     4,     0,     2,     2,     4,     4,     4,     5,
       4,     0,     1,     1,     1,     3,     3,     4,     5,     1,
       1,     3,     1,     2,     3,     0,     2,     2,     0,     4,
       0,     2,     2,     1,     4,     4,     6,     1,     0,     1,
       1,     3,     4,     3,     4,     6,     0,     2,     2,     2,
       2,     2,     2,     1,     1,     3,     3,     1,     1,     1,
       3,     3,     0,     1,     1,     3,     3,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     4,     4,
       4,     5,     2,     2,     6,     6,     4,     9,     9,     7,
       6,     6,     4,     9,     9,     7,     4,     6,     6,     9,
       9,     6,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     1,     4,     1,     3,     4,     1,     3,     2,
       3,     3,     1,     3,     2,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     3,     3,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     4,     4,     4,     3,
       3,     3,     3,     4,     3,     4,     1,     1,     1,     1,
       1,     3,     4,     3,     4,     3,     4,     3,     5,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     2,     2,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     1,     1,     1,
       1,     1,     1
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
      yyerror (&yylloc, context, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, context); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, ParserContext* context)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  YYUSE (context);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, ParserContext* context)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, context);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, ParserContext* context)
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
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , context);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, context); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, ParserContext* context)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (context);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}



struct yypstate
  {
    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

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

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;
    /* Used to determine if this is the first time this instance has
       been used.  */
    int yynew;
  };

/* Initialize the parser data structure.  */
yypstate *
yypstate_new (void)
{
  yypstate *yyps;
  yyps = (yypstate *) malloc (sizeof *yyps);
  if (!yyps)
    return YY_NULLPTR;
  yyps->yynew = 1;
  return yyps;
}

void
yypstate_delete (yypstate *yyps)
{
#ifndef yyoverflow
  /* If the stack was reallocated but the parse did not complete, then the
     stack still needs to be freed.  */
  if (!yyps->yynew && yyps->yyss != yyps->yyssa)
    YYSTACK_FREE (yyps->yyss);
#endif
  free (yyps);
}

#define yynerrs yyps->yynerrs
#define yystate yyps->yystate
#define yyerrstatus yyps->yyerrstatus
#define yyssa yyps->yyssa
#define yyss yyps->yyss
#define yyssp yyps->yyssp
#define yyvsa yyps->yyvsa
#define yyvs yyps->yyvs
#define yyvsp yyps->yyvsp
#define yylsa yyps->yylsa
#define yyls yyps->yyls
#define yylsp yyps->yylsp
#define yyerror_range yyps->yyerror_range
#define yystacksize yyps->yystacksize


/*---------------.
| yypush_parse.  |
`---------------*/

int
yypush_parse (yypstate *yyps, int yypushed_char, YYSTYPE const *yypushed_val, YYLTYPE *yypushed_loc, ParserContext* context)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  if (!yyps->yynew)
    {
      yyn = yypact[yystate];
      goto yyread_pushed_token;
    }

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = *yypushed_loc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      if (!yyps->yynew)
        {
          YYDPRINTF ((stderr, "Return for a new token:\n"));
          yyresult = YYPUSH_MORE;
          goto yypushreturn;
        }
      yyps->yynew = 0;
yyread_pushed_token:
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yypushed_char;
      if (yypushed_val)
        yylval = *yypushed_val;
      if (yypushed_loc)
        yylloc = *yypushed_loc;
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
  *++yylsp = yylloc;
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 431 "chapel.ypp" /* yacc.c:1661  */
    { yyblock = (yyval.pblockstmt); }
#line 4771 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 3:
#line 436 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = new BlockStmt();                                  resetTempID(); }
#line 4777 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 4:
#line 437 "chapel.ypp" /* yacc.c:1661  */
    { (yyvsp[-1].pblockstmt)->appendChapelStmt((yyvsp[0].pblockstmt)); context->generatedStmt = (yyvsp[-1].pblockstmt); resetTempID(); }
#line 4783 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 6:
#line 444 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildPragmaStmt( (yyvsp[-1].vpch), (yyvsp[0].pblockstmt) ); }
#line 4789 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 7:
#line 449 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.vpch) = new Vec<const char*>(); (yyval.vpch)->add(astr((yyvsp[0].pch))); }
#line 4795 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 8:
#line 450 "chapel.ypp" /* yacc.c:1661  */
    { (yyvsp[-2].vpch)->add(astr((yyvsp[0].pch))); }
#line 4801 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 22:
#line 468 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildChapelStmt((yyvsp[-1].pexpr)); }
#line 4807 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 23:
#line 469 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildAtomicStmt((yyvsp[0].pblockstmt)); }
#line 4813 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 24:
#line 470 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildBeginStmt((yyvsp[-1].pcallexpr), (yyvsp[0].pblockstmt)); }
#line 4819 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 25:
#line 471 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildGotoStmt(GOTO_BREAK, (yyvsp[-1].pch)); }
#line 4825 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 26:
#line 472 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildCobeginStmt((yyvsp[-1].pcallexpr), (yyvsp[0].pblockstmt));  }
#line 4831 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 27:
#line 473 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildGotoStmt(GOTO_CONTINUE, (yyvsp[-1].pch)); }
#line 4837 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 28:
#line 474 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildPrimitiveStmt(PRIM_DELETE, (yyvsp[-1].pexpr)); }
#line 4843 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 29:
#line 475 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildLabelStmt((yyvsp[-1].pch), (yyvsp[0].pblockstmt)); }
#line 4849 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 30:
#line 476 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildLocalStmt((yyvsp[0].pblockstmt)); }
#line 4855 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 31:
#line 477 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildOnStmt((yyvsp[-1].pexpr), (yyvsp[0].pblockstmt)); }
#line 4861 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 32:
#line 478 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildSerialStmt((yyvsp[-1].pexpr), (yyvsp[0].pblockstmt)); }
#line 4867 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 33:
#line 479 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildSerialStmt(new SymExpr(gTrue), (yyvsp[0].pblockstmt)); }
#line 4873 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 34:
#line 480 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildSyncStmt((yyvsp[0].pblockstmt)); }
#line 4879 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 35:
#line 481 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildPrimitiveStmt(PRIM_YIELD, (yyvsp[-1].pexpr)); }
#line 4885 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 36:
#line 482 "chapel.ypp" /* yacc.c:1661  */
    { printf("syntax error"); clean_exit(1); }
#line 4891 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 37:
#line 487 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildChapelStmt(new DefExpr(buildModule((yyvsp[-2].pch), new BlockStmt(), yyfilename, (yyvsp[-4].b), (yylsp[-4]).comment))); }
#line 4897 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 38:
#line 489 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildChapelStmt(new DefExpr(buildModule((yyvsp[-3].pch), (yyvsp[-1].pblockstmt), yyfilename, (yyvsp[-5].b), (yylsp[-5]).comment))); }
#line 4903 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 39:
#line 493 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.b) = false; (yyloc).comment = context->latestComment; context->latestComment = NULL; }
#line 4909 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 40:
#line 494 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.b) = false; (yyloc).comment = context->latestComment; context->latestComment = NULL; }
#line 4915 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 41:
#line 495 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.b) = true; (yyloc).comment = context->latestComment; context->latestComment = NULL; }
#line 4921 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 42:
#line 510 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = new BlockStmt(); }
#line 4927 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 43:
#line 511 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = (yyvsp[-1].pblockstmt);              }
#line 4933 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 44:
#line 516 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = new BlockStmt(); (yyval.pblockstmt)->appendChapelStmt((yyvsp[0].pblockstmt)); }
#line 4939 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 45:
#line 517 "chapel.ypp" /* yacc.c:1661  */
    { (yyvsp[-1].pblockstmt)->appendChapelStmt((yyvsp[0].pblockstmt)); }
#line 4945 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 46:
#line 522 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.ponlylist) = new std::vector<OnlyRename*>();
                                         OnlyRename* cur = new OnlyRename();
                                         cur->tag = OnlyRename::SINGLE;
                                         cur->elem = (yyvsp[0].pexpr);
                                         (yyval.ponlylist)->push_back(cur); }
#line 4955 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 47:
#line 527 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.ponlylist) = new std::vector<OnlyRename*>();
                                         OnlyRename* cur = new OnlyRename();
                                         cur->tag = OnlyRename::DOUBLE;
                                         cur->renamed = new std::pair<Expr*, Expr*>((yyvsp[-2].pexpr), (yyvsp[0].pexpr));
                                         (yyval.ponlylist)->push_back(cur); }
#line 4965 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 48:
#line 532 "chapel.ypp" /* yacc.c:1661  */
    { OnlyRename* cur = new OnlyRename();
                                         cur->tag = OnlyRename::SINGLE;
                                         cur->elem = (yyvsp[0].pexpr);
                                         (yyvsp[-2].ponlylist)->push_back(cur); }
#line 4974 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 49:
#line 536 "chapel.ypp" /* yacc.c:1661  */
    { OnlyRename* cur = new OnlyRename();
                                         cur->tag = OnlyRename::DOUBLE;
                                         cur->renamed = new std::pair<Expr*, Expr*>((yyvsp[-2].pexpr), (yyvsp[0].pexpr));
                                         (yyvsp[-4].ponlylist)->push_back(cur); }
#line 4983 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 50:
#line 542 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.ponlylist) = new std::vector<OnlyRename*>();
                                         OnlyRename* cur = new OnlyRename();
                                         cur->tag = OnlyRename::SINGLE;
                                         cur->elem = new UnresolvedSymExpr("");
                                         (yyval.ponlylist)->push_back(cur); }
#line 4993 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 52:
#line 551 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.ponlylist) = new std::vector<OnlyRename*>();
                                         OnlyRename* cur = new OnlyRename();
                                         cur->tag = OnlyRename::SINGLE;
                                         cur->elem = new UnresolvedSymExpr("");
                                         (yyval.ponlylist)->push_back(cur); }
#line 5003 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 54:
#line 560 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildUseStmt((yyvsp[-1].pcallexpr)); }
#line 5009 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 55:
#line 561 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildUseStmt((yyvsp[-3].pexpr), (yyvsp[-1].ponlylist), true); }
#line 5015 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 56:
#line 562 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildUseStmt((yyvsp[-3].pexpr), (yyvsp[-1].ponlylist), false); }
#line 5021 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 57:
#line 566 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildRequireStmt((yyvsp[-1].pcallexpr)); }
#line 5027 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 58:
#line 570 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildAssignment((yyvsp[-3].pexpr), (yyvsp[-1].pexpr), "=");   }
#line 5033 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 59:
#line 571 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildAssignment((yyvsp[-3].pexpr), (yyvsp[-1].pexpr), "+=");  }
#line 5039 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 60:
#line 572 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildAssignment((yyvsp[-3].pexpr), (yyvsp[-1].pexpr), "-=");  }
#line 5045 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 61:
#line 573 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildAssignment((yyvsp[-3].pexpr), (yyvsp[-1].pexpr), "*=");  }
#line 5051 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 62:
#line 574 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildAssignment((yyvsp[-3].pexpr), (yyvsp[-1].pexpr), "/=");  }
#line 5057 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 63:
#line 575 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildAssignment((yyvsp[-3].pexpr), (yyvsp[-1].pexpr), "%=");  }
#line 5063 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 64:
#line 576 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildAssignment((yyvsp[-3].pexpr), (yyvsp[-1].pexpr), "**="); }
#line 5069 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 65:
#line 577 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildAssignment((yyvsp[-3].pexpr), (yyvsp[-1].pexpr), "&=");  }
#line 5075 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 66:
#line 578 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildAssignment((yyvsp[-3].pexpr), (yyvsp[-1].pexpr), "|=");  }
#line 5081 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 67:
#line 579 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildAssignment((yyvsp[-3].pexpr), (yyvsp[-1].pexpr), "^=");  }
#line 5087 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 68:
#line 580 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildAssignment((yyvsp[-3].pexpr), (yyvsp[-1].pexpr), ">>="); }
#line 5093 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 69:
#line 581 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildAssignment((yyvsp[-3].pexpr), (yyvsp[-1].pexpr), "<<="); }
#line 5099 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 70:
#line 582 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildAssignment((yyvsp[-3].pexpr), (yyvsp[-1].pexpr), "<=>"); }
#line 5105 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 71:
#line 583 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildAssignment((yyvsp[-3].pexpr), (yyvsp[-1].pexpr), PRIM_REDUCE_ASSIGN); }
#line 5111 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 72:
#line 584 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildLAndAssignment((yyvsp[-3].pexpr), (yyvsp[-1].pexpr));    }
#line 5117 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 73:
#line 585 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildLOrAssignment((yyvsp[-3].pexpr), (yyvsp[-1].pexpr));     }
#line 5123 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 74:
#line 589 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = NULL; }
#line 5129 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 76:
#line 594 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = (yyvsp[0].pch); }
#line 5135 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 77:
#line 598 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = (yyvsp[0].pch); }
#line 5141 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 78:
#line 599 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = (yyvsp[0].pch); }
#line 5147 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 79:
#line 603 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = (yyvsp[0].pblockstmt); }
#line 5153 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 80:
#line 604 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = (yyvsp[0].pblockstmt); }
#line 5159 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 81:
#line 608 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildPrimitiveStmt(PRIM_RETURN, new SymExpr(gVoid)); }
#line 5165 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 82:
#line 609 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildPrimitiveStmt(PRIM_RETURN, (yyvsp[-1].pexpr)); }
#line 5171 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 83:
#line 613 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildChapelStmt(new BlockStmt()); }
#line 5177 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 85:
#line 615 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = (yyvsp[0].pblockstmt); }
#line 5183 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 86:
#line 616 "chapel.ypp" /* yacc.c:1661  */
    { applyPrivateToBlock((yyvsp[0].pblockstmt)); (yyval.pblockstmt) = (yyvsp[0].pblockstmt); }
#line 5189 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 92:
#line 629 "chapel.ypp" /* yacc.c:1661  */
    {
#ifdef HAVE_LLVM
      if (externC) {
        (yyval.pblockstmt) = buildExternBlockStmt(astr((yyvsp[0].pch)));
      } else {
        USR_FATAL(new BlockStmt(), "extern block syntax is turned off. Use --extern-c flag to turn on.");
      }
#else
      USR_FATAL(new BlockStmt(), "Chapel must be built with llvm in order to use the extern block syntax");
#endif
    }
#line 5205 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 93:
#line 643 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = DoWhileStmt::build((yyvsp[-1].pexpr), (yyvsp[-3].pblockstmt)); }
#line 5211 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 94:
#line 644 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = WhileDoStmt::build((yyvsp[-1].pexpr), (yyvsp[0].pblockstmt)); }
#line 5217 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 95:
#line 645 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildCoforallLoopStmt((yyvsp[-4].pexpr), (yyvsp[-2].pexpr), (yyvsp[-1].pcallexpr), (yyvsp[0].pblockstmt)); }
#line 5223 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 96:
#line 646 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildCoforallLoopStmt((yyvsp[-4].pexpr), zipToTuple((yyvsp[-2].pcallexpr)), (yyvsp[-1].pcallexpr), (yyvsp[0].pblockstmt), true); }
#line 5229 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 97:
#line 647 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildCoforallLoopStmt(NULL, (yyvsp[-2].pexpr), (yyvsp[-1].pcallexpr), (yyvsp[0].pblockstmt)); }
#line 5235 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 98:
#line 648 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = ForLoop::buildForLoop(  (yyvsp[-3].pexpr), (yyvsp[-1].pexpr), (yyvsp[0].pblockstmt), false, false); }
#line 5241 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 99:
#line 649 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = ForLoop::buildForLoop(  (yyvsp[-3].pexpr), (yyvsp[-1].pcallexpr), (yyvsp[0].pblockstmt), false,  true); }
#line 5247 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 100:
#line 650 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = ForLoop::buildForLoop(NULL, (yyvsp[-1].pexpr), (yyvsp[0].pblockstmt), false, false); }
#line 5253 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 101:
#line 651 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = ForLoop::buildForLoop(NULL, (yyvsp[-1].pcallexpr), (yyvsp[0].pblockstmt), false,  true); }
#line 5259 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 102:
#line 652 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildParamForLoopStmt((yyvsp[-3].pch), (yyvsp[-1].pexpr), (yyvsp[0].pblockstmt)); }
#line 5265 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 103:
#line 653 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildForallLoopStmt((yyvsp[-3].pexpr), (yyvsp[-1].pexpr), NULL, (yyvsp[0].pblockstmt)); }
#line 5271 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 104:
#line 654 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildForallLoopStmt((yyvsp[-4].pexpr), (yyvsp[-2].pexpr), (yyvsp[-1].pForallIntents),   (yyvsp[0].pblockstmt)); }
#line 5277 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 105:
#line 655 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildForallLoopStmt((yyvsp[-3].pexpr), zipToTuple((yyvsp[-1].pcallexpr)), NULL, (yyvsp[0].pblockstmt), true); }
#line 5283 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 106:
#line 656 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildForallLoopStmt((yyvsp[-4].pexpr), zipToTuple((yyvsp[-2].pcallexpr)), (yyvsp[-1].pForallIntents),   (yyvsp[0].pblockstmt), true); }
#line 5289 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 107:
#line 657 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildForallLoopStmt(NULL, (yyvsp[-1].pexpr), NULL, (yyvsp[0].pblockstmt)); }
#line 5295 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 108:
#line 658 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildForallLoopStmt(NULL, (yyvsp[-2].pexpr), (yyvsp[-1].pForallIntents),   (yyvsp[0].pblockstmt)); }
#line 5301 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 109:
#line 660 "chapel.ypp" /* yacc.c:1661  */
    {
      if ((yyvsp[-4].pcallexpr)->argList.length != 1)
        USR_FATAL((yyvsp[-2].pexpr), "invalid index expression");
      (yyval.pblockstmt) = buildForallLoopStmt((yyvsp[-4].pcallexpr)->get(1)->remove(), (yyvsp[-2].pexpr), NULL, new BlockStmt((yyvsp[0].pblockstmt)));
    }
#line 5311 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 110:
#line 666 "chapel.ypp" /* yacc.c:1661  */
    {
      if ((yyvsp[-5].pcallexpr)->argList.length != 1)
        USR_FATAL((yyvsp[-3].pexpr), "invalid index expression");
      (yyval.pblockstmt) = buildForallLoopStmt((yyvsp[-5].pcallexpr)->get(1)->remove(), (yyvsp[-3].pexpr), (yyvsp[-2].pForallIntents),   new BlockStmt((yyvsp[0].pblockstmt)));
    }
#line 5321 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 111:
#line 672 "chapel.ypp" /* yacc.c:1661  */
    {
      if ((yyvsp[-4].pcallexpr)->argList.length != 1)
        USR_FATAL((yyvsp[-2].pcallexpr), "invalid index expression");
      (yyval.pblockstmt) = buildForallLoopStmt((yyvsp[-4].pcallexpr)->get(1)->remove(), zipToTuple((yyvsp[-2].pcallexpr)), NULL, new BlockStmt((yyvsp[0].pblockstmt)), true);
    }
#line 5331 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 112:
#line 678 "chapel.ypp" /* yacc.c:1661  */
    {
      if ((yyvsp[-5].pcallexpr)->argList.length != 1)
        USR_FATAL((yyvsp[-3].pcallexpr), "invalid index expression");
      (yyval.pblockstmt) = buildForallLoopStmt((yyvsp[-5].pcallexpr)->get(1)->remove(), zipToTuple((yyvsp[-3].pcallexpr)), (yyvsp[-2].pForallIntents),   new BlockStmt((yyvsp[0].pblockstmt)), true);
    }
#line 5341 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 113:
#line 684 "chapel.ypp" /* yacc.c:1661  */
    {
      if ((yyvsp[-2].pcallexpr)->argList.length > 1)
        (yyval.pblockstmt) = buildForallLoopStmt(NULL, new CallExpr("chpl__ensureDomainExpr", (yyvsp[-2].pcallexpr)), NULL, new BlockStmt((yyvsp[0].pblockstmt)));
      else
        (yyval.pblockstmt) = buildForallLoopStmt(NULL, (yyvsp[-2].pcallexpr)->get(1)->remove(), NULL, new BlockStmt((yyvsp[0].pblockstmt)));
    }
#line 5352 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 114:
#line 691 "chapel.ypp" /* yacc.c:1661  */
    {
      if ((yyvsp[-3].pcallexpr)->argList.length > 1)
        (yyval.pblockstmt) = buildForallLoopStmt(NULL, new CallExpr("chpl__ensureDomainExpr", (yyvsp[-3].pcallexpr)), (yyvsp[-2].pForallIntents),   new BlockStmt((yyvsp[0].pblockstmt)));
      else
        (yyval.pblockstmt) = buildForallLoopStmt(NULL, (yyvsp[-3].pcallexpr)->get(1)->remove(), (yyvsp[-2].pForallIntents),   new BlockStmt((yyvsp[0].pblockstmt)));
    }
#line 5363 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 115:
#line 700 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pcallexpr) = new CallExpr(PRIM_ZIP, (yyvsp[-1].pcallexpr)); }
#line 5369 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 116:
#line 704 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildIfStmt((yyvsp[-2].pexpr), (yyvsp[0].pblockstmt)); }
#line 5375 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 117:
#line 705 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildIfStmt((yyvsp[-1].pexpr), (yyvsp[0].pblockstmt)); }
#line 5381 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 118:
#line 706 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildIfStmt((yyvsp[-4].pexpr), (yyvsp[-2].pblockstmt), (yyvsp[0].pblockstmt)); }
#line 5387 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 119:
#line 707 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildIfStmt((yyvsp[-3].pexpr), (yyvsp[-2].pblockstmt), (yyvsp[0].pblockstmt)); }
#line 5393 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 120:
#line 711 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = TryStmt::build(false, (yyvsp[-1].pexpr)); }
#line 5399 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 121:
#line 712 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = TryStmt::build(true,  (yyvsp[-1].pexpr)); }
#line 5405 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 122:
#line 713 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = TryStmt::build(false, (yyvsp[0].pblockstmt)); }
#line 5411 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 123:
#line 714 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = TryStmt::build(true,  (yyvsp[0].pblockstmt)); }
#line 5417 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 124:
#line 715 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = TryStmt::build(false, (yyvsp[-1].pblockstmt), (yyvsp[0].pblockstmt)); }
#line 5423 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 125:
#line 716 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = TryStmt::build(true,  (yyvsp[-1].pblockstmt), (yyvsp[0].pblockstmt)); }
#line 5429 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 126:
#line 720 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildChapelStmt(); }
#line 5435 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 127:
#line 721 "chapel.ypp" /* yacc.c:1661  */
    { (yyvsp[-1].pblockstmt)->insertAtTail((yyvsp[0].pexpr)); }
#line 5441 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 128:
#line 725 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = CatchStmt::build((yyvsp[-1].pexpr), (yyvsp[0].pblockstmt)); }
#line 5447 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 129:
#line 731 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new DefExpr(newTemp(dtVoid)); }
#line 5453 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 130:
#line 732 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new DefExpr(new VarSymbol((yyvsp[0].pch)), NULL, new UnresolvedSymExpr("Error")); }
#line 5459 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 131:
#line 733 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new DefExpr(new VarSymbol((yyvsp[-2].pch)), NULL, (yyvsp[0].pexpr));   }
#line 5465 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 132:
#line 737 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildPrimitiveStmt(PRIM_THROW, (yyvsp[-1].pexpr)); }
#line 5471 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 133:
#line 741 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildChapelStmt(buildSelectStmt((yyvsp[-3].pexpr), (yyvsp[-1].pblockstmt))); }
#line 5477 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 134:
#line 745 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildChapelStmt(); }
#line 5483 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 135:
#line 746 "chapel.ypp" /* yacc.c:1661  */
    { (yyvsp[-1].pblockstmt)->insertAtTail((yyvsp[0].pexpr)); }
#line 5489 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 136:
#line 751 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CondStmt(new CallExpr(PRIM_WHEN, (yyvsp[-1].pcallexpr)), (yyvsp[0].pblockstmt)); }
#line 5495 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 137:
#line 753 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CondStmt(new CallExpr(PRIM_WHEN), (yyvsp[0].pblockstmt)); }
#line 5501 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 138:
#line 755 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CondStmt(new CallExpr(PRIM_WHEN), (yyvsp[0].pblockstmt)); }
#line 5507 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 139:
#line 762 "chapel.ypp" /* yacc.c:1661  */
    {
      (yyval.pblockstmt) = buildChapelStmt(buildClassDefExpr((yyvsp[-4].pch), NULL, (yyvsp[-5].ptype), (yyvsp[-3].pcallexpr), (yyvsp[-1].pblockstmt), FLAG_UNKNOWN,
                                             (yylsp[-5]).comment));
    }
#line 5516 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 140:
#line 767 "chapel.ypp" /* yacc.c:1661  */
    {
      (yyval.pblockstmt) = buildChapelStmt(buildClassDefExpr((yyvsp[-4].pch), (yyvsp[-6].pch), (yyvsp[-5].ptype), (yyvsp[-3].pcallexpr), (yyvsp[-1].pblockstmt), FLAG_EXTERN,
                                             (yylsp[-5]).comment));
    }
#line 5525 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 141:
#line 774 "chapel.ypp" /* yacc.c:1661  */
    {
             (yyval.ptype)                     = new AggregateType(AGGREGATE_CLASS);
             (yyloc).comment             = context->latestComment;
             context->latestComment = NULL;
           }
#line 5535 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 142:
#line 779 "chapel.ypp" /* yacc.c:1661  */
    {
             (yyval.ptype)                     = new AggregateType(AGGREGATE_RECORD);
             (yyloc).comment             = context->latestComment;
             context->latestComment = NULL;
           }
#line 5545 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 143:
#line 784 "chapel.ypp" /* yacc.c:1661  */
    {
             (yyval.ptype)                     = new AggregateType(AGGREGATE_UNION);
             (yyloc).comment             = context->latestComment;
             context->latestComment = NULL;
           }
#line 5555 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 144:
#line 792 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pcallexpr) = NULL; }
#line 5561 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 145:
#line 793 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pcallexpr) = (yyvsp[0].pcallexpr); }
#line 5567 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 146:
#line 798 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = new BlockStmt(); }
#line 5573 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 147:
#line 800 "chapel.ypp" /* yacc.c:1661  */
    { (yyvsp[-1].pblockstmt)->insertAtTail((yyvsp[0].pblockstmt)); }
#line 5579 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 148:
#line 802 "chapel.ypp" /* yacc.c:1661  */
    { (yyvsp[-2].pblockstmt)->insertAtTail(buildPragmaStmt((yyvsp[-1].vpch), (yyvsp[0].pblockstmt))); }
#line 5585 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 149:
#line 807 "chapel.ypp" /* yacc.c:1661  */
    {
      EnumType* pdt = (yyvsp[-1].penumtype);
      TypeSymbol* pst = new TypeSymbol((yyvsp[-3].pch), pdt);
      (yyvsp[-1].penumtype)->symbol = pst;
      (yyval.pblockstmt) = buildChapelStmt(new DefExpr(pst));
    }
#line 5596 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 150:
#line 817 "chapel.ypp" /* yacc.c:1661  */
    {
      (yyval.penumtype) = new EnumType();
      (yyvsp[0].pdefexpr)->sym->type = (yyval.penumtype);
      (yyval.penumtype)->constants.insertAtTail((yyvsp[0].pdefexpr));
      (yyval.penumtype)->defaultValue = (yyvsp[0].pdefexpr)->sym;
      (yyval.penumtype)->doc = context->latestComment;
      context->latestComment = NULL;
    }
#line 5609 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 151:
#line 826 "chapel.ypp" /* yacc.c:1661  */
    {
      (yyval.penumtype) = (yyvsp[-1].penumtype);
    }
#line 5617 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 152:
#line 830 "chapel.ypp" /* yacc.c:1661  */
    {
      (yyvsp[-2].penumtype)->constants.insertAtTail((yyvsp[0].pdefexpr));
      (yyvsp[0].pdefexpr)->sym->type = (yyvsp[-2].penumtype);
    }
#line 5626 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 153:
#line 837 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pdefexpr) = new DefExpr(new EnumSymbol((yyvsp[0].pch))); }
#line 5632 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 154:
#line 838 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pdefexpr) = new DefExpr(new EnumSymbol((yyvsp[-2].pch)), (yyvsp[0].pexpr)); }
#line 5638 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 155:
#line 843 "chapel.ypp" /* yacc.c:1661  */
    {
      captureTokens = 1;
      captureString.clear();
    }
#line 5647 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 156:
#line 848 "chapel.ypp" /* yacc.c:1661  */
    {
      captureTokens = 0;
      (yyvsp[0].pfnsymbol)->userString = astr(captureString);
    }
#line 5656 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 157:
#line 853 "chapel.ypp" /* yacc.c:1661  */
    {
      (yyvsp[-5].pfnsymbol)->retTag = (yyvsp[-3].retTag);
      if ((yyvsp[-3].retTag) == RET_REF || (yyvsp[-3].retTag) == RET_CONST_REF)
        USR_FATAL("'ref' return types are not allowed in lambdas");
      if ((yyvsp[-3].retTag) == RET_PARAM)
        USR_FATAL("'param' return types are not allowed in lambdas");
      if ((yyvsp[-3].retTag) == RET_TYPE)
        USR_FATAL("'type' return types are not allowed in lambdas");
      if ((yyvsp[-2].pexpr))
        (yyvsp[-5].pfnsymbol)->retExprType = new BlockStmt((yyvsp[-2].pexpr), BLOCK_SCOPELESS);
      if ((yyvsp[-1].pexpr))
        (yyvsp[-5].pfnsymbol)->where = new BlockStmt((yyvsp[-1].pexpr));
      (yyvsp[-5].pfnsymbol)->insertAtTail((yyvsp[0].pblockstmt));
      (yyval.pexpr) = new DefExpr(buildLambda((yyvsp[-5].pfnsymbol)));
    }
#line 5676 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 158:
#line 873 "chapel.ypp" /* yacc.c:1661  */
    {
                  (yyval.pfnsymbol) = new FnSymbol("");

                  (yyloc).comment             = context->latestComment;
                  context->latestComment = NULL;
                }
#line 5687 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 159:
#line 879 "chapel.ypp" /* yacc.c:1661  */
    {
                  (yyval.pfnsymbol) = new FnSymbol("");
                  (yyval.pfnsymbol)->addFlag(FLAG_INLINE);

                  (yyloc).comment             = context->latestComment;
                  context->latestComment = NULL;
                }
#line 5699 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 160:
#line 886 "chapel.ypp" /* yacc.c:1661  */
    {
                  (yyval.pfnsymbol) = new FnSymbol((yyvsp[0].pch));
                  (yyval.pfnsymbol)->addFlag(FLAG_EXPORT);
                  (yyval.pfnsymbol)->addFlag(FLAG_LOCAL_ARGS);

                  (yyloc).comment             = context->latestComment;
                  context->latestComment = NULL;
                }
#line 5712 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 161:
#line 894 "chapel.ypp" /* yacc.c:1661  */
    {
                  (yyval.pfnsymbol) = new FnSymbol((yyvsp[0].pch));
                  (yyval.pfnsymbol)->addFlag(FLAG_EXTERN);
                  (yyval.pfnsymbol)->addFlag(FLAG_LOCAL_ARGS);

                  (yyloc).comment             = context->latestComment;
                  context->latestComment = NULL;
                }
#line 5725 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 162:
#line 905 "chapel.ypp" /* yacc.c:1661  */
    {
      // Sets up to capture tokens while parsing the next grammar nonterminal.
      captureTokens = 1;
      captureString.clear();
    }
#line 5735 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 163:
#line 911 "chapel.ypp" /* yacc.c:1661  */
    {
      // Stop capturing and save the result.
      captureTokens = 0;

      (yyvsp[0].pfnsymbol)->userString = astr(captureString);
    }
#line 5746 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 164:
#line 918 "chapel.ypp" /* yacc.c:1661  */
    {
      FnSymbol* fn = (yyvsp[-6].pfnsymbol);

      fn->copyFlags((yyvsp[-9].pfnsymbol));
      // The user explicitly named this function (controls mangling).
      if (*(yyvsp[-9].pfnsymbol)->name)
        fn->cname = (yyvsp[-9].pfnsymbol)->name;

      if ((yyvsp[-8].procIter) == ProcIter_ITER)
      {
        if (fn->hasFlag(FLAG_EXTERN))
          USR_FATAL_CONT(fn, "'iter' is not legal with 'extern'");
        fn->addFlag(FLAG_ITERATOR_FN);
      }

      (yyval.pblockstmt) = buildFunctionDecl((yyvsp[-6].pfnsymbol), (yyvsp[-4].retTag), (yyvsp[-3].pexpr), (yyvsp[-2].b), (yyvsp[-1].pexpr), (yyvsp[0].pblockstmt), (yylsp[-9]).comment);
      context->latestComment = NULL;
    }
#line 5769 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 165:
#line 940 "chapel.ypp" /* yacc.c:1661  */
    {
      (yyval.pfnsymbol) = buildFunctionSymbol((yyvsp[0].pfnsymbol), (yyvsp[-1].pch), (yyvsp[-2].pt), NULL);
    }
#line 5777 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 166:
#line 944 "chapel.ypp" /* yacc.c:1661  */
    {
      (yyval.pfnsymbol) = buildFunctionSymbol((yyvsp[0].pfnsymbol), (yyvsp[-1].pch), (yyvsp[-2].pt), NULL);
      (yyval.pfnsymbol)->addFlag(FLAG_ASSIGNOP);
    }
#line 5786 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 167:
#line 949 "chapel.ypp" /* yacc.c:1661  */
    {
      (yyval.pfnsymbol) = buildFunctionSymbol((yyvsp[0].pfnsymbol), (yyvsp[-1].pch), (yyvsp[-4].pt), (yyvsp[-3].pexpr));
    }
#line 5794 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 168:
#line 953 "chapel.ypp" /* yacc.c:1661  */
    {
      (yyval.pfnsymbol) = buildFunctionSymbol((yyvsp[0].pfnsymbol), (yyvsp[-1].pch), (yyvsp[-4].pt), (yyvsp[-3].pexpr));
      (yyval.pfnsymbol)->addFlag(FLAG_ASSIGNOP);
    }
#line 5803 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 170:
#line 961 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = (yyvsp[-1].pexpr); }
#line 5809 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 172:
#line 966 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = astr("~", (yyvsp[0].pch)); }
#line 5815 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 173:
#line 967 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = "&"; }
#line 5821 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 174:
#line 968 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = "|"; }
#line 5827 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 175:
#line 969 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = "^"; }
#line 5833 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 176:
#line 970 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = "~"; }
#line 5839 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 177:
#line 971 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = "=="; }
#line 5845 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 178:
#line 972 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = "!="; }
#line 5851 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 179:
#line 973 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = "<="; }
#line 5857 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 180:
#line 974 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = ">="; }
#line 5863 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 181:
#line 975 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = "<"; }
#line 5869 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 182:
#line 976 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = ">"; }
#line 5875 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 183:
#line 977 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = "+"; }
#line 5881 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 184:
#line 978 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = "-"; }
#line 5887 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 185:
#line 979 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = "*"; }
#line 5893 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 186:
#line 980 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = "/"; }
#line 5899 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 187:
#line 981 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = "<<"; }
#line 5905 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 188:
#line 982 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = ">>"; }
#line 5911 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 189:
#line 983 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = "%"; }
#line 5917 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 190:
#line 984 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = "**"; }
#line 5923 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 191:
#line 985 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = "!"; }
#line 5929 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 192:
#line 986 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = "chpl_by"; }
#line 5935 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 193:
#line 987 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = "#"; }
#line 5941 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 194:
#line 988 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = "chpl_align"; }
#line 5947 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 195:
#line 989 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = "<=>"; }
#line 5953 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 196:
#line 990 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = "<~>"; }
#line 5959 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 197:
#line 994 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = "="; }
#line 5965 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 198:
#line 995 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = "+="; }
#line 5971 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 199:
#line 996 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = "-="; }
#line 5977 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 200:
#line 997 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = "*="; }
#line 5983 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 201:
#line 998 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = "/="; }
#line 5989 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 202:
#line 999 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = "%="; }
#line 5995 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 203:
#line 1000 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = "**="; }
#line 6001 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 204:
#line 1001 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = "&="; }
#line 6007 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 205:
#line 1002 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = "|="; }
#line 6013 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 206:
#line 1003 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = "^="; }
#line 6019 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 207:
#line 1004 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = ">>="; }
#line 6025 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 208:
#line 1005 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pch) = "<<="; }
#line 6031 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 209:
#line 1009 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pfnsymbol) = new FnSymbol("_"); (yyval.pfnsymbol)->addFlag(FLAG_NO_PARENS); }
#line 6037 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 210:
#line 1010 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pfnsymbol) = (yyvsp[-1].pfnsymbol); }
#line 6043 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 211:
#line 1014 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pfnsymbol) = (yyvsp[-1].pfnsymbol); }
#line 6049 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 212:
#line 1018 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pfnsymbol) = buildFunctionFormal(NULL, NULL); }
#line 6055 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 213:
#line 1019 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pfnsymbol) = buildFunctionFormal(NULL, (yyvsp[0].pdefexpr)); }
#line 6061 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 214:
#line 1020 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pfnsymbol) = buildFunctionFormal((yyvsp[-2].pfnsymbol), (yyvsp[0].pdefexpr)); }
#line 6067 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 215:
#line 1025 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pdefexpr) = buildArgDefExpr((yyvsp[-3].pt), (yyvsp[-2].pch), (yyvsp[-1].pexpr), (yyvsp[0].pexpr), NULL); }
#line 6073 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 216:
#line 1027 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pdefexpr) = buildArgDefExpr((yyvsp[-3].pt), (yyvsp[-2].pch), (yyvsp[-1].pexpr), NULL, (yyvsp[0].pexpr)); }
#line 6079 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 217:
#line 1029 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pdefexpr) = buildTupleArgDefExpr((yyvsp[-5].pt), (yyvsp[-3].pblockstmt), (yyvsp[-1].pexpr), (yyvsp[0].pexpr)); }
#line 6085 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 218:
#line 1031 "chapel.ypp" /* yacc.c:1661  */
    { USR_FATAL("variable-length argument may not be grouped in a tuple"); }
#line 6091 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 219:
#line 1035 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pt) = INTENT_BLANK; }
#line 6097 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 220:
#line 1036 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pt) = (yyvsp[0].pt); }
#line 6103 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 221:
#line 1040 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pt) = INTENT_IN; }
#line 6109 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 222:
#line 1041 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pt) = INTENT_INOUT; }
#line 6115 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 223:
#line 1042 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pt) = INTENT_OUT; }
#line 6121 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 224:
#line 1043 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pt) = INTENT_CONST; }
#line 6127 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 225:
#line 1044 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pt) = INTENT_CONST_IN; }
#line 6133 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 226:
#line 1045 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pt) = INTENT_CONST_REF; }
#line 6139 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 227:
#line 1046 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pt) = INTENT_PARAM; }
#line 6145 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 228:
#line 1047 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pt) = INTENT_REF; }
#line 6151 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 229:
#line 1048 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pt) = INTENT_TYPE; }
#line 6157 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 230:
#line 1052 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pt) = INTENT_BLANK; }
#line 6163 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 231:
#line 1053 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pt) = INTENT_PARAM; }
#line 6169 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 232:
#line 1054 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pt) = INTENT_REF;   }
#line 6175 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 233:
#line 1055 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pt) = INTENT_CONST_REF;   }
#line 6181 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 234:
#line 1056 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pt) = INTENT_CONST;   }
#line 6187 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 235:
#line 1057 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pt) = INTENT_TYPE;  }
#line 6193 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 236:
#line 1061 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.procIter) = ProcIter_PROC; }
#line 6199 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 237:
#line 1062 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.procIter) = ProcIter_ITER; }
#line 6205 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 238:
#line 1066 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.retTag) = RET_VALUE; }
#line 6211 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 239:
#line 1067 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.retTag) = RET_VALUE; }
#line 6217 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 240:
#line 1068 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.retTag) = RET_CONST_REF; }
#line 6223 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 241:
#line 1069 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.retTag) = RET_REF; }
#line 6229 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 242:
#line 1070 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.retTag) = RET_PARAM; }
#line 6235 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 243:
#line 1071 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.retTag) = RET_TYPE; }
#line 6241 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 244:
#line 1075 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.b) = false; }
#line 6247 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 245:
#line 1076 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.b) = true;  }
#line 6253 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 246:
#line 1079 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = NULL; }
#line 6259 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 249:
#line 1085 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = new BlockStmt((yyvsp[0].pblockstmt)); }
#line 6265 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 250:
#line 1090 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pdefexpr) = new DefExpr(new VarSymbol((yyvsp[0].pch))); }
#line 6271 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 251:
#line 1092 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pdefexpr) = new DefExpr(new VarSymbol(astr("chpl__query", istr(query_uid++)))); }
#line 6277 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 252:
#line 1096 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pdefexpr) = new DefExpr(new VarSymbol(astr("chpl__query", istr(query_uid++)))); }
#line 6283 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 254:
#line 1101 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = (yyvsp[0].pexpr); }
#line 6289 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 255:
#line 1102 "chapel.ypp" /* yacc.c:1661  */
    { (yyvsp[0].pdefexpr)->sym->addFlag(FLAG_PARAM); (yyval.pexpr) = (yyvsp[0].pdefexpr); }
#line 6295 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 256:
#line 1106 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = NULL; }
#line 6301 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 257:
#line 1107 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = (yyvsp[0].pexpr); }
#line 6307 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 258:
#line 1112 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = (yyvsp[-1].pblockstmt); }
#line 6313 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 259:
#line 1114 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = handleConfigTypes((yyvsp[-1].pblockstmt)); }
#line 6319 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 260:
#line 1116 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = convertTypesToExtern((yyvsp[-1].pblockstmt)); }
#line 6325 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 261:
#line 1121 "chapel.ypp" /* yacc.c:1661  */
    {
      VarSymbol* var = new VarSymbol((yyvsp[-1].pch));

      var->addFlag(FLAG_TYPE_VARIABLE);

      var->doc               = context->latestComment;
      context->latestComment = NULL;

      DefExpr* def = new DefExpr(var, (yyvsp[0].pexpr));

      (yyval.pblockstmt) = buildChapelStmt(def);
    }
#line 6342 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 262:
#line 1134 "chapel.ypp" /* yacc.c:1661  */
    {
      VarSymbol* var = new VarSymbol((yyvsp[-3].pch));

      var->addFlag(FLAG_TYPE_VARIABLE);

      var->doc               = context->latestComment;
      context->latestComment = NULL;

      DefExpr* def = new DefExpr(var, (yyvsp[-2].pexpr));

      (yyvsp[0].pblockstmt)->insertAtHead(def);
      (yyval.pblockstmt) = buildChapelStmt((yyvsp[0].pblockstmt));
    }
#line 6360 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 263:
#line 1150 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = NULL; }
#line 6366 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 264:
#line 1152 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = (yyvsp[0].pexpr); }
#line 6372 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 265:
#line 1154 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildForallLoopExprFromArrayType((yyvsp[0].pcallexpr)); }
#line 6378 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 266:
#line 1159 "chapel.ypp" /* yacc.c:1661  */
    {
      std::set<Flag> flags;
      flags.insert((yyvsp[-3].flag));
      flags.insert(FLAG_PARAM);
      (yyval.pblockstmt) = buildVarDecls((yyvsp[-1].pblockstmt), flags, (yylsp[-3]).comment);
      context->latestComment = NULL;
    }
#line 6390 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 267:
#line 1167 "chapel.ypp" /* yacc.c:1661  */
    {
      std::set<Flag> flags;
      flags.insert((yyvsp[-3].flag));
      flags.insert(FLAG_CONST);
      (yyval.pblockstmt) = buildVarDecls((yyvsp[-1].pblockstmt), flags, (yylsp[-3]).comment);
      context->latestComment = NULL;
    }
#line 6402 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 268:
#line 1175 "chapel.ypp" /* yacc.c:1661  */
    {
      std::set<Flag> flags;
      flags.insert((yyvsp[-3].flag));
      flags.insert(FLAG_REF_VAR);
      (yyval.pblockstmt) = buildVarDecls((yyvsp[-1].pblockstmt), flags, (yylsp[-3]).comment);
      context->latestComment = NULL;
    }
#line 6414 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 269:
#line 1183 "chapel.ypp" /* yacc.c:1661  */
    {
      std::set<Flag> flags;
      flags.insert((yyvsp[-4].flag));
      flags.insert(FLAG_CONST);
      flags.insert(FLAG_REF_VAR);
      (yyval.pblockstmt) = buildVarDecls((yyvsp[-1].pblockstmt), flags, (yylsp[-4]).comment);
      context->latestComment = NULL;
    }
#line 6427 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 270:
#line 1192 "chapel.ypp" /* yacc.c:1661  */
    {
      std::set<Flag> flags;
      flags.insert((yyvsp[-3].flag));
      (yyval.pblockstmt) = buildVarDecls((yyvsp[-1].pblockstmt), flags, (yylsp[-3]).comment);
      context->latestComment = NULL;
    }
#line 6438 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 271:
#line 1201 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.flag) = FLAG_UNKNOWN; (yyloc).comment = context->latestComment; context->latestComment = NULL; }
#line 6444 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 272:
#line 1202 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.flag) = FLAG_CONFIG;  (yyloc).comment = context->latestComment; context->latestComment = NULL; }
#line 6450 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 273:
#line 1203 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.flag) = FLAG_EXTERN;  (yyloc).comment = context->latestComment; context->latestComment = NULL; }
#line 6456 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 275:
#line 1209 "chapel.ypp" /* yacc.c:1661  */
    {
      for_alist(expr, (yyvsp[0].pblockstmt)->body)
        (yyvsp[-2].pblockstmt)->insertAtTail(expr->remove());
    }
#line 6465 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 276:
#line 1217 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildChapelStmt(new DefExpr(new VarSymbol((yyvsp[-2].pch)), (yyvsp[0].pexpr), (yyvsp[-1].pexpr))); }
#line 6471 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 277:
#line 1219 "chapel.ypp" /* yacc.c:1661  */
    {
      VarSymbol* var = new VarSymbol((yyvsp[-3].pch));
      var->addFlag(FLAG_ARRAY_ALIAS);
      (yyval.pblockstmt) = buildChapelStmt(new DefExpr(var, (yyvsp[0].pexpr), (yyvsp[-2].pexpr)));
    }
#line 6481 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 278:
#line 1225 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildTupleVarDeclStmt((yyvsp[-3].pblockstmt), (yyvsp[-1].pexpr), (yyvsp[0].pexpr)); }
#line 6487 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 279:
#line 1230 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new DefExpr(new VarSymbol("chpl__tuple_blank")); }
#line 6493 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 280:
#line 1232 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new DefExpr(new VarSymbol((yyvsp[0].pch))); }
#line 6499 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 281:
#line 1234 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = (yyvsp[-1].pblockstmt); }
#line 6505 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 282:
#line 1239 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildChapelStmt((yyvsp[0].pexpr)); }
#line 6511 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 283:
#line 1241 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = buildChapelStmt((yyvsp[-1].pexpr)); }
#line 6517 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 284:
#line 1243 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pblockstmt) = ((yyvsp[0].pblockstmt)->insertAtHead((yyvsp[-2].pexpr)), (yyvsp[0].pblockstmt)); }
#line 6523 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 285:
#line 1249 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = NULL; }
#line 6529 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 286:
#line 1250 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new SymExpr(gNoInit); }
#line 6535 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 287:
#line 1251 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = (yyvsp[0].pexpr); }
#line 6541 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 288:
#line 1255 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = NULL; }
#line 6547 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 289:
#line 1257 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("chpl__ensureDomainExpr", (yyvsp[-1].pcallexpr)); }
#line 6553 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 290:
#line 1261 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = NULL; }
#line 6559 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 291:
#line 1262 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = (yyvsp[0].pexpr); }
#line 6565 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 292:
#line 1263 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = (yyvsp[0].pcallexpr); }
#line 6571 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 293:
#line 1264 "chapel.ypp" /* yacc.c:1661  */
    {printf("bad type specification"); }
#line 6577 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 294:
#line 1285 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pcallexpr) = new CallExpr("chpl__buildArrayRuntimeType",
             new CallExpr("chpl__ensureDomainExpr", (yyvsp[-2].pcallexpr)), (yyvsp[0].pexpr));
    }
#line 6585 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 295:
#line 1289 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pcallexpr) = new CallExpr("chpl__buildArrayRuntimeType",
             new CallExpr("chpl__ensureDomainExpr", (yyvsp[-2].pcallexpr)), (yyvsp[0].pcallexpr));
    }
#line 6593 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 296:
#line 1293 "chapel.ypp" /* yacc.c:1661  */
    {
      if ((yyvsp[-4].pcallexpr)->argList.length != 1)
        USR_FATAL((yyvsp[-2].pexpr), "invalid index expression");
      (yyval.pcallexpr) = new CallExpr("chpl__buildArrayRuntimeType",
             new CallExpr("chpl__ensureDomainExpr", (yyvsp[-2].pexpr)), (yyvsp[0].pexpr), (yyvsp[-4].pcallexpr)->get(1)->remove(),
             new CallExpr("chpl__ensureDomainExpr", (yyvsp[-2].pexpr)->copy()));
    }
#line 6605 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 297:
#line 1300 "chapel.ypp" /* yacc.c:1661  */
    {printf("bad array type specification"); clean_exit(1); }
#line 6611 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 298:
#line 1304 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = NULL; }
#line 6617 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 299:
#line 1305 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = (yyvsp[0].pexpr); }
#line 6623 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 300:
#line 1306 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = (yyvsp[0].pdefexpr); }
#line 6629 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 301:
#line 1311 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("chpl__buildArrayRuntimeType", gNil, (yyvsp[0].pexpr)); }
#line 6635 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 302:
#line 1313 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildFormalArrayType((yyvsp[-2].pcallexpr), (yyvsp[0].pexpr)); }
#line 6641 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 303:
#line 1319 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("chpl__buildArrayRuntimeType", gNil, (yyvsp[0].pexpr)); }
#line 6647 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 304:
#line 1321 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildFormalArrayType((yyvsp[-2].pcallexpr), (yyvsp[0].pexpr)); }
#line 6653 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 305:
#line 1323 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildFormalArrayType((yyvsp[-2].pexpr), (yyvsp[0].pexpr), (yyvsp[-4].pcallexpr)); }
#line 6659 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 306:
#line 1327 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = NULL; }
#line 6665 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 307:
#line 1328 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = (yyvsp[0].pexpr); }
#line 6671 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 308:
#line 1329 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = (yyvsp[0].pdefexpr); }
#line 6677 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 309:
#line 1330 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new UnresolvedSymExpr("_domain"); }
#line 6683 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 310:
#line 1331 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new UnresolvedSymExpr( "_singlevar"); }
#line 6689 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 311:
#line 1332 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new UnresolvedSymExpr( "_syncvar"); }
#line 6695 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 312:
#line 1333 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = (yyvsp[0].pexpr); }
#line 6701 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 313:
#line 1339 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pcallexpr) = new CallExpr(PRIM_ACTUALS_LIST, (yyvsp[0].pexpr)); }
#line 6707 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 314:
#line 1340 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pcallexpr) = new CallExpr(PRIM_ACTUALS_LIST, (yyvsp[0].pdefexpr)); }
#line 6713 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 315:
#line 1341 "chapel.ypp" /* yacc.c:1661  */
    { (yyvsp[-2].pcallexpr)->insertAtTail((yyvsp[0].pexpr)); }
#line 6719 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 316:
#line 1342 "chapel.ypp" /* yacc.c:1661  */
    { (yyvsp[-2].pcallexpr)->insertAtTail((yyvsp[0].pdefexpr)); }
#line 6725 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 317:
#line 1346 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new UnresolvedSymExpr("chpl__tuple_blank"); }
#line 6731 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 318:
#line 1347 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = (yyvsp[0].pexpr); }
#line 6737 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 319:
#line 1348 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = (yyvsp[0].pdefexpr); }
#line 6743 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 320:
#line 1352 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pcallexpr) = new CallExpr(PRIM_ACTUALS_LIST, (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 6749 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 321:
#line 1353 "chapel.ypp" /* yacc.c:1661  */
    { (yyvsp[-2].pcallexpr)->insertAtTail((yyvsp[0].pexpr)); }
#line 6755 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 322:
#line 1357 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pcallexpr) = new CallExpr(PRIM_ACTUALS_LIST); }
#line 6761 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 324:
#line 1362 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pcallexpr) = new CallExpr(PRIM_ACTUALS_LIST, (yyvsp[0].pexpr)); }
#line 6767 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 325:
#line 1363 "chapel.ypp" /* yacc.c:1661  */
    { (yyvsp[-2].pcallexpr)->insertAtTail((yyvsp[0].pexpr)); }
#line 6773 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 326:
#line 1367 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildNamedActual((yyvsp[-2].pch), (yyvsp[0].pdefexpr)); }
#line 6779 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 327:
#line 1368 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildNamedActual((yyvsp[-2].pch), (yyvsp[0].pexpr)); }
#line 6785 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 328:
#line 1369 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildNamedAliasActual((yyvsp[-2].pch), (yyvsp[0].pexpr)); }
#line 6791 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 329:
#line 1370 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = (yyvsp[0].pdefexpr); }
#line 6797 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 331:
#line 1375 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new UnresolvedSymExpr((yyvsp[0].pch)); }
#line 6803 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 337:
#line 1392 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr( "_singlevar", (yyvsp[0].pexpr)); }
#line 6809 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 338:
#line 1394 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("chpl__buildIndexType", (yyvsp[-1].pcallexpr)); }
#line 6815 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 339:
#line 1396 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("chpl__buildDomainRuntimeType", new UnresolvedSymExpr("defaultDist"), (yyvsp[-1].pcallexpr)); }
#line 6821 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 340:
#line 1398 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("chpl__buildSubDomainType", (yyvsp[-1].pcallexpr)); }
#line 6827 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 341:
#line 1400 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("chpl__buildSparseDomainRuntimeType", buildDotExpr((yyvsp[-1].pcallexpr)->copy(), "defaultSparseDist"), (yyvsp[-1].pcallexpr)); }
#line 6833 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 342:
#line 1402 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("chpl__atomicType", (yyvsp[0].pexpr)); }
#line 6839 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 343:
#line 1404 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr( "_syncvar", (yyvsp[0].pexpr)); }
#line 6845 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 344:
#line 1409 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildForLoopExpr((yyvsp[-4].pexpr), (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 6851 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 345:
#line 1411 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildForLoopExpr((yyvsp[-4].pexpr), zipToTuple((yyvsp[-2].pcallexpr)), (yyvsp[0].pexpr), NULL, false, true); }
#line 6857 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 346:
#line 1413 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildForLoopExpr(NULL, (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 6863 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 347:
#line 1415 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildForLoopExpr((yyvsp[-7].pexpr), (yyvsp[-5].pexpr), (yyvsp[0].pexpr), (yyvsp[-2].pexpr)); }
#line 6869 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 348:
#line 1417 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildForLoopExpr((yyvsp[-7].pexpr), zipToTuple((yyvsp[-5].pcallexpr)), (yyvsp[0].pexpr), (yyvsp[-2].pexpr), false, true); }
#line 6875 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 349:
#line 1419 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildForLoopExpr(NULL, (yyvsp[-5].pexpr), (yyvsp[0].pexpr), (yyvsp[-2].pexpr)); }
#line 6881 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 350:
#line 1421 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildForallLoopExpr((yyvsp[-4].pexpr), (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 6887 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 351:
#line 1423 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildForallLoopExpr((yyvsp[-4].pexpr), zipToTuple((yyvsp[-2].pcallexpr)), (yyvsp[0].pexpr), NULL, false, true); }
#line 6893 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 352:
#line 1425 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildForallLoopExpr(NULL, (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 6899 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 353:
#line 1427 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildForallLoopExpr((yyvsp[-7].pexpr), (yyvsp[-5].pexpr), (yyvsp[0].pexpr), (yyvsp[-2].pexpr)); }
#line 6905 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 354:
#line 1429 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildForallLoopExpr((yyvsp[-7].pexpr), zipToTuple((yyvsp[-5].pcallexpr)), (yyvsp[0].pexpr), (yyvsp[-2].pexpr), false, true); }
#line 6911 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 355:
#line 1431 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildForallLoopExpr(NULL, (yyvsp[-5].pexpr), (yyvsp[0].pexpr), (yyvsp[-2].pexpr)); }
#line 6917 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 356:
#line 1433 "chapel.ypp" /* yacc.c:1661  */
    {
      if ((yyvsp[-2].pcallexpr)->argList.length > 1)
        (yyval.pexpr) = buildForallLoopExpr(NULL, new CallExpr("chpl__ensureDomainExpr", (yyvsp[-2].pcallexpr)), (yyvsp[0].pexpr), NULL, true);
      else
        (yyval.pexpr) = buildForallLoopExpr(NULL, (yyvsp[-2].pcallexpr)->get(1)->remove(), (yyvsp[0].pexpr), NULL, true);
    }
#line 6928 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 357:
#line 1440 "chapel.ypp" /* yacc.c:1661  */
    {
      if ((yyvsp[-4].pcallexpr)->argList.length != 1)
        USR_FATAL((yyvsp[-2].pexpr), "invalid index expression");
      (yyval.pexpr) = buildForallLoopExpr((yyvsp[-4].pcallexpr)->get(1)->remove(), (yyvsp[-2].pexpr), (yyvsp[0].pexpr), NULL, true);
    }
#line 6938 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 358:
#line 1446 "chapel.ypp" /* yacc.c:1661  */
    {
      if ((yyvsp[-4].pcallexpr)->argList.length != 1)
        USR_FATAL((yyvsp[-2].pcallexpr), "invalid index expression");
      (yyval.pexpr) = buildForallLoopExpr((yyvsp[-4].pcallexpr)->get(1)->remove(), zipToTuple((yyvsp[-2].pcallexpr)), (yyvsp[0].pexpr), NULL, false, true);
    }
#line 6948 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 359:
#line 1452 "chapel.ypp" /* yacc.c:1661  */
    {
      if ((yyvsp[-7].pcallexpr)->argList.length != 1)
        USR_FATAL((yyvsp[-5].pexpr), "invalid index expression");
      (yyval.pexpr) = buildForallLoopExpr((yyvsp[-7].pcallexpr)->get(1)->remove(), (yyvsp[-5].pexpr), (yyvsp[0].pexpr), (yyvsp[-2].pexpr));
    }
#line 6958 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 360:
#line 1458 "chapel.ypp" /* yacc.c:1661  */
    {
      if ((yyvsp[-7].pcallexpr)->argList.length != 1)
        USR_FATAL((yyvsp[-5].pcallexpr), "invalid index expression");
      (yyval.pexpr) = buildForallLoopExpr((yyvsp[-7].pcallexpr)->get(1)->remove(), zipToTuple((yyvsp[-5].pcallexpr)), (yyvsp[0].pexpr), (yyvsp[-2].pexpr), false, true);
    }
#line 6968 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 361:
#line 1467 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr(new DefExpr(buildIfExpr((yyvsp[-4].pexpr), (yyvsp[-2].pexpr), (yyvsp[0].pexpr)))); }
#line 6974 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 362:
#line 1471 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new SymExpr(gNil); }
#line 6980 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 370:
#line 1487 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("<~>", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 6986 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 371:
#line 1491 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pcallexpr) = NULL; }
#line 6992 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 373:
#line 1496 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pcallexpr) = (yyvsp[-1].pcallexpr); }
#line 6998 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 374:
#line 1502 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pcallexpr) = new CallExpr(PRIM_ACTUALS_LIST);
      addTaskIntent((yyval.pcallexpr), (yyvsp[0].pIntentExpr).iVar, (yyvsp[0].pIntentExpr).tfIntent, (yyvsp[0].pIntentExpr).riExp); }
#line 7005 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 375:
#line 1505 "chapel.ypp" /* yacc.c:1661  */
    { addTaskIntent((yyvsp[-2].pcallexpr), (yyvsp[0].pIntentExpr).iVar, (yyvsp[0].pIntentExpr).tfIntent, (yyvsp[0].pIntentExpr).riExp); }
#line 7011 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 376:
#line 1509 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pForallIntents) = (yyvsp[-1].pForallIntents); }
#line 7017 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 377:
#line 1515 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pForallIntents) = new ForallIntents();
      addForallIntent((yyval.pForallIntents), (yyvsp[0].pIntentExpr).iVar, (yyvsp[0].pIntentExpr).tfIntent, (yyvsp[0].pIntentExpr).riExp); }
#line 7024 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 378:
#line 1518 "chapel.ypp" /* yacc.c:1661  */
    { addForallIntent((yyvsp[-2].pForallIntents), (yyvsp[0].pIntentExpr).iVar, (yyvsp[0].pIntentExpr).tfIntent, (yyvsp[0].pIntentExpr).riExp); }
#line 7030 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 379:
#line 1523 "chapel.ypp" /* yacc.c:1661  */
    {
      (yyval.pIntentExpr).tfIntent = (yyvsp[-1].pt); (yyval.pIntentExpr).iVar = (yyvsp[0].pexpr); (yyval.pIntentExpr).riExp = NULL;
    }
#line 7038 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 380:
#line 1526 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pIntentExpr).riExp = (yyvsp[-2].pexpr), (yyval.pIntentExpr).iVar = (yyvsp[0].pexpr); }
#line 7044 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 381:
#line 1527 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pIntentExpr).riExp = (yyvsp[-2].pexpr), (yyval.pIntentExpr).iVar = (yyvsp[0].pexpr); }
#line 7050 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 383:
#line 1533 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("<~>", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7056 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 384:
#line 1538 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr(PRIM_NEW, (yyvsp[0].pexpr)); }
#line 7062 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 385:
#line 1543 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildLetExpr((yyvsp[-2].pblockstmt), (yyvsp[0].pexpr)); }
#line 7068 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 394:
#line 1559 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr(PRIM_TUPLE_EXPAND, (yyvsp[-1].pexpr)); }
#line 7074 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 395:
#line 1561 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = createCast((yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7080 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 396:
#line 1563 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("chpl_build_bounded_range", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7086 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 397:
#line 1565 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("chpl_build_low_bounded_range", (yyvsp[-1].pexpr)); }
#line 7092 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 398:
#line 1567 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("chpl_build_high_bounded_range", (yyvsp[0].pexpr)); }
#line 7098 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 399:
#line 1569 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("chpl_build_unbounded_range"); }
#line 7104 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 406:
#line 1592 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr((yyvsp[-3].pexpr), (yyvsp[-1].pcallexpr)); }
#line 7110 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 407:
#line 1593 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildSquareCallExpr((yyvsp[-3].pexpr), (yyvsp[-1].pcallexpr)); }
#line 7116 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 408:
#line 1594 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildPrimitiveExpr((yyvsp[-1].pcallexpr)); }
#line 7122 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 409:
#line 1598 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildDotExpr((yyvsp[-2].pexpr), (yyvsp[0].pch)); }
#line 7128 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 410:
#line 1599 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr(PRIM_TYPEOF, (yyvsp[-2].pexpr)); }
#line 7134 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 411:
#line 1600 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildDotExpr((yyvsp[-2].pexpr), "_dom"); }
#line 7140 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 412:
#line 1608 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = (yyvsp[-1].pexpr); }
#line 7146 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 413:
#line 1609 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildOneTuple((yyvsp[-2].pexpr)); }
#line 7152 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 414:
#line 1610 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildTuple((yyvsp[-1].pcallexpr)); }
#line 7158 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 415:
#line 1611 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildTuple((yyvsp[-2].pcallexpr)); }
#line 7164 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 416:
#line 1615 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildIntLiteral((yyvsp[0].pch));    }
#line 7170 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 417:
#line 1616 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildRealLiteral((yyvsp[0].pch));   }
#line 7176 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 418:
#line 1617 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildImagLiteral((yyvsp[0].pch));   }
#line 7182 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 419:
#line 1618 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildStringLiteral((yyvsp[0].pch)); }
#line 7188 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 420:
#line 1619 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildCStringLiteral((yyvsp[0].pch)); }
#line 7194 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 421:
#line 1620 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("chpl__buildDomainExpr", (yyvsp[-1].pcallexpr)); }
#line 7200 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 422:
#line 1621 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("chpl__buildDomainExpr", (yyvsp[-2].pcallexpr)); }
#line 7206 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 423:
#line 1622 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("chpl__buildArrayExpr",  (yyvsp[-1].pcallexpr)); }
#line 7212 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 424:
#line 1623 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("chpl__buildArrayExpr",  (yyvsp[-2].pcallexpr)); }
#line 7218 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 425:
#line 1625 "chapel.ypp" /* yacc.c:1661  */
    {
      (yyval.pexpr) = new CallExpr("chpl__buildAssociativeArrayExpr", (yyvsp[-1].pcallexpr));
    }
#line 7226 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 426:
#line 1629 "chapel.ypp" /* yacc.c:1661  */
    {
      (yyval.pexpr) = new CallExpr("chpl__buildAssociativeArrayExpr", (yyvsp[-2].pcallexpr));
    }
#line 7234 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 427:
#line 1636 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pcallexpr) = new CallExpr(PRIM_ACTUALS_LIST, (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7240 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 428:
#line 1637 "chapel.ypp" /* yacc.c:1661  */
    { (yyvsp[-4].pcallexpr)->insertAtTail((yyvsp[-2].pexpr)); (yyvsp[-4].pcallexpr)->insertAtTail((yyvsp[0].pexpr)); }
#line 7246 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 429:
#line 1641 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("+", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7252 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 430:
#line 1642 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("-", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7258 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 431:
#line 1643 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("*", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7264 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 432:
#line 1644 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("/", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7270 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 433:
#line 1645 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("<<", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7276 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 434:
#line 1646 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr(">>", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7282 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 435:
#line 1647 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("%", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7288 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 436:
#line 1648 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("==", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7294 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 437:
#line 1649 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("!=", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7300 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 438:
#line 1650 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("<=", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7306 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 439:
#line 1651 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr(">=", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7312 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 440:
#line 1652 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("<", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7318 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 441:
#line 1653 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr(">", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7324 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 442:
#line 1654 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("&", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7330 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 443:
#line 1655 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("|", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7336 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 444:
#line 1656 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("^", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7342 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 445:
#line 1657 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("&&", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7348 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 446:
#line 1658 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("||", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7354 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 447:
#line 1659 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("**", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7360 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 448:
#line 1660 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("chpl_by", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7366 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 449:
#line 1661 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("chpl_align", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7372 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 450:
#line 1662 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("#", (yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7378 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 451:
#line 1663 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("chpl__distributed", (yyvsp[0].pexpr), (yyvsp[-2].pexpr)); }
#line 7384 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 452:
#line 1667 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("+", (yyvsp[0].pexpr)); }
#line 7390 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 453:
#line 1668 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("-", (yyvsp[0].pexpr)); }
#line 7396 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 454:
#line 1669 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildPreDecIncWarning((yyvsp[0].pexpr), '-'); }
#line 7402 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 455:
#line 1670 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildPreDecIncWarning((yyvsp[0].pexpr), '+'); }
#line 7408 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 456:
#line 1671 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("!", (yyvsp[0].pexpr)); }
#line 7414 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 457:
#line 1672 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new CallExpr("~", (yyvsp[0].pexpr)); }
#line 7420 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 458:
#line 1676 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildReduceExpr((yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7426 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 459:
#line 1677 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildReduceExpr((yyvsp[-2].pexpr), zipToTuple((yyvsp[0].pcallexpr)), true); }
#line 7432 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 460:
#line 1678 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildReduceExpr((yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7438 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 461:
#line 1679 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildReduceExpr((yyvsp[-2].pexpr), zipToTuple((yyvsp[0].pcallexpr)), true); }
#line 7444 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 462:
#line 1683 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildScanExpr((yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7450 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 463:
#line 1684 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildScanExpr((yyvsp[-2].pexpr), zipToTuple((yyvsp[0].pcallexpr)), true); }
#line 7456 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 464:
#line 1685 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildScanExpr((yyvsp[-2].pexpr), (yyvsp[0].pexpr)); }
#line 7462 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 465:
#line 1686 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = buildScanExpr((yyvsp[-2].pexpr), zipToTuple((yyvsp[0].pcallexpr)), true); }
#line 7468 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 466:
#line 1691 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new UnresolvedSymExpr("SumReduceScanOp"); }
#line 7474 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 467:
#line 1692 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new UnresolvedSymExpr("ProductReduceScanOp"); }
#line 7480 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 468:
#line 1693 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new UnresolvedSymExpr("LogicalAndReduceScanOp"); }
#line 7486 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 469:
#line 1694 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new UnresolvedSymExpr("LogicalOrReduceScanOp"); }
#line 7492 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 470:
#line 1695 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new UnresolvedSymExpr("BitwiseAndReduceScanOp"); }
#line 7498 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 471:
#line 1696 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new UnresolvedSymExpr("BitwiseOrReduceScanOp"); }
#line 7504 "bison-chapel.cpp" /* yacc.c:1661  */
    break;

  case 472:
#line 1697 "chapel.ypp" /* yacc.c:1661  */
    { (yyval.pexpr) = new UnresolvedSymExpr("BitwiseXorReduceScanOp"); }
#line 7510 "bison-chapel.cpp" /* yacc.c:1661  */
    break;


#line 7514 "bison-chapel.cpp" /* yacc.c:1661  */
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
  *++yylsp = yyloc;

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
      yyerror (&yylloc, context, YY_("syntax error"));
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
        yyerror (&yylloc, context, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc, context);
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

  yyerror_range[1] = yylsp[1-yylen];
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp, context);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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
  yyerror (&yylloc, context, YY_("memory exhausted"));
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
                  yytoken, &yylval, &yylloc, context);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp, context);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  yyps->yynew = 1;

yypushreturn:
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
