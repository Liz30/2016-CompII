
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "decaf_grammar.y"


#include <stdio.h>
#include "Value.h"
#include "Variable.h"
#include "Expression.h"
#include "Statement.h"
#include "MethodDef.h"
#include "ClassDef.h"
#include "decaf_tokens.h"

#define YYERROR_VERBOSE 1

extern ClassDef *class_def;

int yylex(YYSTYPE*, YYLTYPE*);
void yyerror(const char *message);

VariableDefList *SetType(VariableDefList *list, Type type)
{
	VariableDefList::iterator it = list->begin();

	while (it != list->end()) {
		VariableDef *var = *it;

		var->variable_type = type;
		it++;
	}

	return list;
}



/* Line 189 of yacc.c  */
#line 108 "decaf_grammar.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     K_CLASS = 259,
     K_BREAK = 260,
     K_CONTINUE = 261,
     K_WHILE = 262,
     K_FOR = 263,
     K_IF = 264,
     K_ELSE = 265,
     K_RETURN = 266,
     K_READ = 267,
     K_PRINT = 268,
     K_TRUE = 269,
     K_FALSE = 270,
     K_INT = 271,
     K_VOID = 272,
     K_BOOLEAN = 273,
     BOOL_OP_OR = 274,
     BOOL_OP_AND = 275,
     BIT_SHIFT_OP = 276,
     REL_OP = 277,
     ARITH_OP_SUM = 278,
     ARITH_OP_MUL = 279,
     CHAR_CONSTANT = 280,
     INT_CONSTANT = 281,
     REAL_CONSTANT = 282,
     STRING_CONSTANT = 283
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 35 "decaf_grammar.y"

	Expression		*expression;
	Statement		*statement;
	VariableDef		*variable_def;
	MethodDef		*method_def;
	ParameterDef		*parameter_def;
	ParameterDefList	*parameter_def_list;
	VariableDefList		*variable_def_list;
	StatementList		*statement_list;
	MethodDefList		*method_def_list;
	ClassDef		*class_def;
	Type 			type;
	ExpressionOperator	oper;
	ExpressionList		*expression_list;
	ResultValue		constant;
	LValue			lvalue;
	char			*string;
	int			integer;
	bool			boolean;



/* Line 214 of yacc.c  */
#line 195 "decaf_grammar.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 220 "decaf_grammar.cpp"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   158

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  102
/* YYNRULES -- Number of states.  */
#define YYNSTATES  169

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   283

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    38,     2,     2,     2,     2,     2,     2,
      36,    37,     2,     2,    32,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    31,
       2,    35,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    33,     2,    34,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    29,     2,    30,     2,     2,     2,     2,
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
      25,    26,    27,    28
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,    12,    14,    15,    17,    18,    21,
      23,    26,    28,    30,    34,    38,    40,    43,    48,    51,
      52,    59,    61,    63,    65,    66,    70,    72,    75,    80,
      82,    83,    85,    86,    89,    91,    95,    97,    99,   102,
     104,   107,   110,   112,   114,   116,   119,   122,   125,   127,
     131,   136,   139,   142,   144,   146,   147,   151,   153,   157,
     159,   161,   163,   167,   169,   172,   176,   177,   184,   187,
     188,   194,   204,   208,   210,   213,   215,   217,   219,   220,
     224,   226,   230,   232,   236,   238,   242,   244,   248,   250,
     254,   256,   259,   262,   264,   269,   271,   275,   277,   279,
     281,   283,   285
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      40,     0,    -1,    41,    -1,     4,    46,    29,    42,    43,
      30,    -1,    44,    -1,    -1,    45,    -1,    -1,    44,    47,
      -1,    47,    -1,    45,    51,    -1,    51,    -1,     3,    -1,
      61,    48,    31,    -1,    48,    32,    49,    -1,    49,    -1,
       3,    50,    -1,     3,    33,    26,    34,    -1,    35,    90,
      -1,    -1,    52,     3,    36,    53,    37,    56,    -1,    61,
      -1,    17,    -1,    54,    -1,    -1,    54,    32,    55,    -1,
      55,    -1,    61,     3,    -1,    29,    57,    58,    30,    -1,
      59,    -1,    -1,    62,    -1,    -1,    59,    60,    -1,    60,
      -1,    61,    48,    31,    -1,    16,    -1,    18,    -1,    62,
      63,    -1,    63,    -1,    64,    31,    -1,    65,    31,    -1,
      74,    -1,    76,    -1,    77,    -1,    79,    31,    -1,    80,
      31,    -1,    81,    31,    -1,    56,    -1,    72,    35,    83,
      -1,    66,    36,    67,    37,    -1,    13,    69,    -1,    12,
      71,    -1,     3,    -1,    68,    -1,    -1,    68,    32,    83,
      -1,    83,    -1,    69,    32,    70,    -1,    70,    -1,    28,
      -1,    83,    -1,    71,    32,    72,    -1,    72,    -1,     3,
      73,    -1,    33,    83,    34,    -1,    -1,     9,    36,    83,
      37,    56,    75,    -1,    10,    56,    -1,    -1,     7,    36,
      83,    37,    56,    -1,     8,    36,    78,    31,    83,    31,
      78,    37,    56,    -1,    78,    32,    64,    -1,    64,    -1,
      11,    82,    -1,     5,    -1,     6,    -1,    83,    -1,    -1,
      83,    19,    84,    -1,    84,    -1,    84,    20,    85,    -1,
      85,    -1,    85,    22,    86,    -1,    86,    -1,    86,    21,
      87,    -1,    87,    -1,    87,    23,    88,    -1,    88,    -1,
      88,    24,    89,    -1,    89,    -1,    38,    89,    -1,    23,
      89,    -1,    72,    -1,    66,    36,    67,    37,    -1,    90,
      -1,    36,    83,    37,    -1,    26,    -1,    25,    -1,    27,
      -1,    91,    -1,    14,    -1,    15,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   110,   110,   114,   119,   120,   124,   125,   129,   130,
     134,   135,   139,   143,   147,   148,   154,   159,   167,   168,
     173,   183,   184,   188,   189,   193,   197,   204,   208,   212,
     213,   216,   217,   220,   225,   229,   233,   234,   238,   239,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   255,
     259,   260,   261,   265,   269,   270,   274,   275,   279,   280,
     284,   285,   289,   290,   294,   298,   299,   303,   307,   308,
     312,   316,   321,   322,   326,   330,   334,   338,   339,   343,
     344,   347,   348,   352,   353,   357,   358,   362,   363,   366,
     367,   371,   372,   373,   374,   375,   376,   379,   380,   381,
     382,   386,   387
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "\"'identificador'\"", "\"'class'\"",
  "\"'break'\"", "\"'continue'\"", "\"'while'\"", "\"'for'\"", "\"'if'\"",
  "\"'else'\"", "\"'return'\"", "\"'read'\"", "\"'print'\"", "\"'true'\"",
  "\"'false'\"", "\"'int'\"", "\"'void'\"", "\"'boolean'\"",
  "\"operador booleano 'or'\"", "\"operador booleano 'and'\"",
  "\"operador de corrimiento de bits\"",
  "\"operador relacional '>', '<', '>=', '<=', '==' o '!='\"",
  "\"operador aritmetico '+' o '-'\"",
  "\"operador aritmetico '*', '/', '%' \"", "\"constante caracter\"",
  "\"constante entera\"", "\"constante real\"", "\"constante de cadena\"",
  "'{'", "'}'", "';'", "','", "'['", "']'", "'='", "'('", "')'", "'!'",
  "$accept", "program", "class_def", "optional_field_decl_list",
  "optional_method_decl_list", "field_decl_list", "method_decl_list",
  "class_name", "field_decl", "var_list", "var", "optional_initialization",
  "method_decl", "return_type", "opt_parameter_decl_list",
  "parameter_decl_list", "parameter_decl", "block", "opt_var_decl_list",
  "opt_statement_list", "var_decl_list", "var_decl", "type",
  "statement_list", "statement", "assign", "method_call", "method_name",
  "opt_method_call_argument_list", "method_call_argument_list",
  "print_argument_list", "print_argument", "read_argument_list", "lvalue",
  "opt_array_dimension", "if_statement", "opt_else", "while_statement",
  "for_statement", "for_assignment_list", "return_statement",
  "break_statement", "continue_statement", "opt_expr", "expr", "bool_term",
  "relational_expr", "bit_shift_expr", "arith_expr", "arith_term",
  "factor", "constant", "bool_constant", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   123,
     125,    59,    44,    91,    93,    61,    40,    41,    33
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    39,    40,    41,    42,    42,    43,    43,    44,    44,
      45,    45,    46,    47,    48,    48,    49,    49,    50,    50,
      51,    52,    52,    53,    53,    54,    54,    55,    56,    57,
      57,    58,    58,    59,    59,    60,    61,    61,    62,    62,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    64,
      65,    65,    65,    66,    67,    67,    68,    68,    69,    69,
      70,    70,    71,    71,    72,    73,    73,    74,    75,    75,
      76,    77,    78,    78,    79,    80,    81,    82,    82,    83,
      83,    84,    84,    85,    85,    86,    86,    87,    87,    88,
      88,    89,    89,    89,    89,    89,    89,    90,    90,    90,
      90,    91,    91
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     6,     1,     0,     1,     0,     2,     1,
       2,     1,     1,     3,     3,     1,     2,     4,     2,     0,
       6,     1,     1,     1,     0,     3,     1,     2,     4,     1,
       0,     1,     0,     2,     1,     3,     1,     1,     2,     1,
       2,     2,     1,     1,     1,     2,     2,     2,     1,     3,
       4,     2,     2,     1,     1,     0,     3,     1,     3,     1,
       1,     1,     3,     1,     2,     3,     0,     6,     2,     0,
       5,     9,     3,     1,     2,     1,     1,     1,     0,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     2,     2,     1,     4,     1,     3,     1,     1,     1,
       1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,    12,     0,     1,     5,    36,    37,
       7,     4,     9,     0,    22,     0,     6,    11,     0,    21,
       8,    19,     0,    15,     3,    10,     0,     0,     0,    16,
      13,     0,    24,     0,   101,   102,    98,    97,    99,    18,
     100,    14,     0,    23,    26,     0,    17,     0,     0,    27,
      30,    20,    25,    32,    29,    34,     0,    66,    75,    76,
       0,     0,     0,    78,     0,     0,    48,     0,    31,    39,
       0,     0,     0,     0,    42,    43,    44,     0,     0,     0,
      33,     0,     0,    64,     0,     0,     0,     0,     0,     0,
       0,    93,    74,    77,    80,    82,    84,    86,    88,    90,
      95,    66,    52,    63,    60,    51,    59,    61,    28,    38,
      40,    41,    55,     0,    45,    46,    47,    35,     0,     0,
      73,     0,     0,    92,     0,    91,    55,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    54,    57,    49,    65,
       0,     0,     0,     0,    96,     0,    79,    81,    83,    85,
      87,    89,    62,    58,    50,     0,    70,     0,    72,    69,
      94,    56,     0,     0,    67,     0,    68,     0,    71
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    10,    15,    11,    16,     5,    12,    22,
      23,    29,    17,    18,    42,    43,    44,    66,    53,    67,
      54,    55,    13,    68,    69,    70,    71,    90,   135,   136,
     105,   106,   102,    91,    83,    74,   164,    75,    76,   121,
      77,    78,    79,    92,   107,    94,    95,    96,    97,    98,
      99,   100,    40
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -84
static const yytype_int8 yypact[] =
{
       4,    16,    43,   -84,   -84,    32,   -84,    -1,   -84,   -84,
      23,    -1,   -84,    42,   -84,    33,    23,   -84,    64,   -84,
     -84,    -3,    22,   -84,   -84,   -84,    37,    53,    72,   -84,
     -84,    42,    -1,    49,   -84,   -84,   -84,   -84,   -84,   -84,
     -84,   -84,    47,    56,   -84,    82,   -84,    62,    -1,   -84,
      -1,   -84,   -84,    63,    -1,   -84,    42,     1,   -84,   -84,
      59,    66,    67,    21,   101,    86,   -84,    75,    63,   -84,
      76,    77,    70,    80,   -84,   -84,   -84,    87,    88,    90,
     -84,    24,    21,   -84,    21,   101,    21,    21,    21,    21,
      81,   -84,   -84,   104,   105,   106,   108,   103,   107,   -84,
     -84,    94,    98,   -84,   -84,   100,   -84,   104,   -84,   -84,
     -84,   -84,    21,    21,   -84,   -84,   -84,   -84,   -16,    -9,
     -84,    46,    -8,   -84,    -6,   -84,    21,    21,    21,    21,
      21,    21,    21,   101,    86,    96,   102,   104,   104,   -84,
      62,    21,   101,    62,   -84,    99,   105,   106,   108,   103,
     107,   -84,   -84,   -84,   -84,    21,   -84,    19,   -84,   125,
     -84,   104,   101,    62,   -84,   -23,   -84,    62,   -84
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,   126,    83,
     109,   -84,   122,   -84,   -84,   -84,    93,   -47,   -84,   -84,
     -84,    89,    10,   -84,    74,   -80,   -84,   -46,    18,   -84,
     -84,    11,   -84,   -52,   -84,   -84,   -84,   -84,   -84,   -15,
     -84,   -84,   -84,   -84,   -61,    25,    20,    17,    26,    27,
     -83,   121,   -84
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -54
static const yytype_int16 yytable[] =
{
      51,    73,    93,   127,   123,   120,   125,    72,     1,   142,
     127,   127,   103,   127,   167,     8,    73,     9,   139,     4,
      19,   118,    72,   119,    57,   122,    19,   124,   140,   143,
      27,   144,    28,    73,    82,    34,    35,   -53,   127,     8,
      14,     9,    45,     6,    87,    21,    36,    37,    38,   151,
     162,   137,   138,    30,    31,   117,    31,    88,    45,    89,
      56,     7,   158,    24,    56,   137,    57,    26,    58,    59,
      60,    61,    62,    32,    63,    64,    65,   141,   142,    33,
     157,   152,   120,    46,    47,    49,    34,    35,    48,    57,
      73,    50,    50,   156,   161,    84,   159,    36,    37,    38,
      34,    35,    85,    86,   101,   108,   112,   110,   111,    87,
      73,    36,    37,    38,   104,   113,   166,   126,   114,   115,
     168,   116,    88,   127,    89,   128,   131,    82,   129,   130,
     133,   132,   134,   154,   155,   163,   160,    20,    25,    81,
      41,    52,   109,    80,   145,   153,   148,   165,   147,    39,
       0,     0,   146,     0,     0,     0,   149,     0,   150
};

static const yytype_int16 yycheck[] =
{
      47,    53,    63,    19,    87,    85,    89,    53,     4,    32,
      19,    19,    64,    19,    37,    16,    68,    18,    34,     3,
      10,    82,    68,    84,     3,    86,    16,    88,    37,    37,
      33,    37,    35,    85,    33,    14,    15,    36,    19,    16,
      17,    18,    32,     0,    23,     3,    25,    26,    27,   132,
      31,   112,   113,    31,    32,    31,    32,    36,    48,    38,
      50,    29,   142,    30,    54,   126,     3,     3,     5,     6,
       7,     8,     9,    36,    11,    12,    13,    31,    32,    26,
     141,   133,   162,    34,    37,     3,    14,    15,    32,     3,
     142,    29,    29,   140,   155,    36,   143,    25,    26,    27,
      14,    15,    36,    36,     3,    30,    36,    31,    31,    23,
     162,    25,    26,    27,    28,    35,   163,    36,    31,    31,
     167,    31,    36,    19,    38,    20,    23,    33,    22,    21,
      32,    24,    32,    37,    32,    10,    37,    11,    16,    56,
      31,    48,    68,    54,   126,   134,   129,   162,   128,    28,
      -1,    -1,   127,    -1,    -1,    -1,   130,    -1,   131
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,    40,    41,     3,    46,     0,    29,    16,    18,
      42,    44,    47,    61,    17,    43,    45,    51,    52,    61,
      47,     3,    48,    49,    30,    51,     3,    33,    35,    50,
      31,    32,    36,    26,    14,    15,    25,    26,    27,    90,
      91,    49,    53,    54,    55,    61,    34,    37,    32,     3,
      29,    56,    55,    57,    59,    60,    61,     3,     5,     6,
       7,     8,     9,    11,    12,    13,    56,    58,    62,    63,
      64,    65,    66,    72,    74,    76,    77,    79,    80,    81,
      60,    48,    33,    73,    36,    36,    36,    23,    36,    38,
      66,    72,    82,    83,    84,    85,    86,    87,    88,    89,
      90,     3,    71,    72,    28,    69,    70,    83,    30,    63,
      31,    31,    36,    35,    31,    31,    31,    31,    83,    83,
      64,    78,    83,    89,    83,    89,    36,    19,    20,    22,
      21,    23,    24,    32,    32,    67,    68,    83,    83,    34,
      37,    31,    32,    37,    37,    67,    84,    85,    86,    87,
      88,    89,    72,    70,    37,    32,    56,    83,    64,    56,
      37,    83,    31,    10,    75,    78,    56,    37,    56
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, &yylloc, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, &yylloc)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */





/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
    YYLTYPE yyerror_range[2];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;
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
     `$$ = $1'.

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

/* Line 1455 of yacc.c  */
#line 110 "decaf_grammar.y"
    { class_def = (yyvsp[(1) - (1)].class_def); ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 115 "decaf_grammar.y"
    { (yyval.class_def) = new ClassDef((yyvsp[(2) - (6)].string), (yyvsp[(4) - (6)].variable_def_list), (yyvsp[(5) - (6)].method_def_list)); ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 119 "decaf_grammar.y"
    { (yyval.variable_def_list) = (yyvsp[(1) - (1)].variable_def_list); ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 120 "decaf_grammar.y"
    { (yyval.variable_def_list) = 0; ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 124 "decaf_grammar.y"
    { (yyval.method_def_list) = (yyvsp[(1) - (1)].method_def_list); ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 125 "decaf_grammar.y"
    { (yyval.method_def_list) = 0; ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 129 "decaf_grammar.y"
    { (yyval.variable_def_list) = (yyvsp[(1) - (2)].variable_def_list); (yyval.variable_def_list)->insert((yyval.variable_def_list)->end(), (yyvsp[(2) - (2)].variable_def_list)->begin(), (yyvsp[(2) - (2)].variable_def_list)->end()); delete (yyvsp[(2) - (2)].variable_def_list);;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 130 "decaf_grammar.y"
    { (yyval.variable_def_list) = (yyvsp[(1) - (1)].variable_def_list); ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 134 "decaf_grammar.y"
    { (yyval.method_def_list) = (yyvsp[(1) - (2)].method_def_list); (yyval.method_def_list)->push_back((yyvsp[(2) - (2)].method_def)); ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 135 "decaf_grammar.y"
    { (yyval.method_def_list) = new MethodDefList; (yyval.method_def_list)->push_back((yyvsp[(1) - (1)].method_def)); ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 139 "decaf_grammar.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 143 "decaf_grammar.y"
    { (yyval.variable_def_list) = SetType((yyvsp[(2) - (3)].variable_def_list), (yyvsp[(1) - (3)].type)); ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 147 "decaf_grammar.y"
    { (yyval.variable_def_list) = (yyvsp[(1) - (3)].variable_def_list); (yyval.variable_def_list)->push_back((yyvsp[(3) - (3)].variable_def)); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 148 "decaf_grammar.y"
    { 
						(yyval.variable_def_list) = new VariableDefList;
						(yyval.variable_def_list)->push_back((yyvsp[(1) - (1)].variable_def));
					;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 154 "decaf_grammar.y"
    { 
							(yyval.variable_def) = new VariableDef((yyvsp[(1) - (2)].string), (yylsp[(1) - (2)]).last_line, (yylsp[(1) - (2)]).first_column);
							(yyval.variable_def)->initial_value = (yyvsp[(2) - (2)].expression);
						;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 159 "decaf_grammar.y"
    { 
							(yyval.variable_def) = new VariableDef((yyvsp[(1) - (4)].string), (yylsp[(1) - (4)]).last_line, (yylsp[(1) - (4)]).first_column); 
							(yyval.variable_def)->is_array_def = true;
							(yyval.variable_def)->array_dimension = (yyvsp[(3) - (4)].integer);
						;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 167 "decaf_grammar.y"
    { (yyval.expression) = (yyvsp[(2) - (2)].expression); ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 168 "decaf_grammar.y"
    { (yyval.expression) = 0; ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 174 "decaf_grammar.y"
    {
			(yyval.method_def) = new MethodDef((yyvsp[(2) - (6)].string)); 
			(yyval.method_def)->method_return_type = (yyvsp[(1) - (6)].type);
			(yyval.method_def)->method_parameters = (yyvsp[(4) - (6)].parameter_def_list);
			(yyval.method_def)->method_body =  (yyvsp[(6) - (6)].statement);
		;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 183 "decaf_grammar.y"
    { (yyval.type) = (yyvsp[(1) - (1)].type); ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 184 "decaf_grammar.y"
    { (yyval.type) = Void; ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 188 "decaf_grammar.y"
    { (yyval.parameter_def_list) = (yyvsp[(1) - (1)].parameter_def_list); ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 189 "decaf_grammar.y"
    { (yyval.parameter_def_list) = 0; ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 193 "decaf_grammar.y"
    {
									(yyval.parameter_def_list) = (yyvsp[(1) - (3)].parameter_def_list);
									(yyval.parameter_def_list)->push_back((yyvsp[(3) - (3)].parameter_def));
								;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 197 "decaf_grammar.y"
    { 
									(yyval.parameter_def_list) = new ParameterDefList;
									(yyval.parameter_def_list)->push_back((yyvsp[(1) - (1)].parameter_def));
								;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 204 "decaf_grammar.y"
    { (yyval.parameter_def) = new ParameterDef((yyvsp[(2) - (2)].string), (yyvsp[(1) - (2)].type)); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 209 "decaf_grammar.y"
    { (yyval.statement) = new BlockStatement((yyvsp[(2) - (4)].variable_def_list), (yyvsp[(3) - (4)].statement_list) ); ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 212 "decaf_grammar.y"
    { (yyval.variable_def_list) = (yyvsp[(1) - (1)].variable_def_list); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 213 "decaf_grammar.y"
    { (yyval.variable_def_list) = 0; ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 216 "decaf_grammar.y"
    { (yyval.statement_list) = (yyvsp[(1) - (1)].statement_list); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 217 "decaf_grammar.y"
    { (yyval.statement_list) = 0; ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 220 "decaf_grammar.y"
    {
						(yyval.variable_def_list) = (yyvsp[(1) - (2)].variable_def_list);
						(yyval.variable_def_list)->insert((yyval.variable_def_list)->end(), (yyvsp[(2) - (2)].variable_def_list)->begin(), (yyvsp[(2) - (2)].variable_def_list)->end());
						delete (yyvsp[(2) - (2)].variable_def_list);
					;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 225 "decaf_grammar.y"
    { (yyval.variable_def_list) = (yyvsp[(1) - (1)].variable_def_list); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 229 "decaf_grammar.y"
    { (yyval.variable_def_list) = SetType((yyvsp[(2) - (3)].variable_def_list), (yyvsp[(1) - (3)].type)); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 233 "decaf_grammar.y"
    { (yyval.type) = Int; ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 234 "decaf_grammar.y"
    { (yyval.type) = Boolean; ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 238 "decaf_grammar.y"
    { (yyval.statement_list) = (yyvsp[(1) - (2)].statement_list); (yyval.statement_list)->push_back((yyvsp[(2) - (2)].statement)); ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 239 "decaf_grammar.y"
    { (yyval.statement_list) = new StatementList; (yyval.statement_list)->push_back((yyvsp[(1) - (1)].statement)); ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 243 "decaf_grammar.y"
    { (yyval.statement) = (yyvsp[(1) - (2)].statement); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 244 "decaf_grammar.y"
    { (yyval.statement) = (yyvsp[(1) - (2)].statement); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 245 "decaf_grammar.y"
    { (yyval.statement) = (yyvsp[(1) - (1)].statement); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 246 "decaf_grammar.y"
    { (yyval.statement) = (yyvsp[(1) - (1)].statement); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 247 "decaf_grammar.y"
    { (yyval.statement) = (yyvsp[(1) - (1)].statement); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 248 "decaf_grammar.y"
    { (yyval.statement) = (yyvsp[(1) - (2)].statement); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 249 "decaf_grammar.y"
    { (yyval.statement) = (yyvsp[(1) - (2)].statement); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 250 "decaf_grammar.y"
    { (yyval.statement) = (yyvsp[(1) - (2)].statement); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 251 "decaf_grammar.y"
    { (yyval.statement) = (yyvsp[(1) - (1)].statement); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 255 "decaf_grammar.y"
    { (yyval.statement) = new AssignmentStatement((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression), (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 259 "decaf_grammar.y"
    { (yyval.statement) = new MethodCallStatement((yyvsp[(1) - (4)].string), (yyvsp[(3) - (4)].expression_list), (yylsp[(1) - (4)]).first_line, (yylsp[(1) - (4)]).first_column); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 260 "decaf_grammar.y"
    { (yyval.statement) = new MethodCallStatement("print", (yyvsp[(2) - (2)].expression_list), (yylsp[(1) - (2)]).first_line, (yylsp[(1) - (2)]).first_column); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 261 "decaf_grammar.y"
    { (yyval.statement) = new MethodCallStatement("read", (yyvsp[(2) - (2)].expression_list), (yylsp[(1) - (2)]).first_line, (yylsp[(1) - (2)]).first_column); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 265 "decaf_grammar.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 269 "decaf_grammar.y"
    { (yyval.expression_list) = (yyvsp[(1) - (1)].expression_list); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 270 "decaf_grammar.y"
    { (yyval.expression_list) = 0; ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 274 "decaf_grammar.y"
    { (yyval.expression_list) = (yyvsp[(1) - (3)].expression_list); (yyval.expression_list)->push_back((yyvsp[(3) - (3)].expression)); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 275 "decaf_grammar.y"
    { (yyval.expression_list) = new ExpressionList; (yyval.expression_list)->push_back((yyvsp[(1) - (1)].expression)); ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 279 "decaf_grammar.y"
    { (yyval.expression_list) = (yyvsp[(1) - (3)].expression_list); (yyval.expression_list)->push_back((yyvsp[(3) - (3)].expression)); ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 280 "decaf_grammar.y"
    { (yyval.expression_list) = new ExpressionList; (yyval.expression_list)->push_back((yyvsp[(1) - (1)].expression)); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 284 "decaf_grammar.y"
    { (yyval.expression) = new ConstantExpression((yyvsp[(1) - (1)].string)); ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 285 "decaf_grammar.y"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 289 "decaf_grammar.y"
    { (yyval.expression_list) = (yyvsp[(1) - (3)].expression_list); (yyval.expression_list)->push_back((yyvsp[(3) - (3)].expression)); ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 290 "decaf_grammar.y"
    { (yyval.expression_list) = new ExpressionList; (yyval.expression_list)->push_back((yyvsp[(1) - (1)].expression)); ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 294 "decaf_grammar.y"
    { (yyval.expression) = new LValueExpression((yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].expression)); ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 298 "decaf_grammar.y"
    { (yyval.expression) = (yyvsp[(2) - (3)].expression); ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 299 "decaf_grammar.y"
    { (yyval.expression) = 0; ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 303 "decaf_grammar.y"
    { (yyval.statement) = new IfStatement((yyvsp[(3) - (6)].expression), (yyvsp[(5) - (6)].statement), (yyvsp[(6) - (6)].statement), (yylsp[(1) - (6)]).first_line, (yylsp[(1) - (6)]).first_column); ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 307 "decaf_grammar.y"
    { (yyval.statement) = (yyvsp[(2) - (2)].statement); ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 308 "decaf_grammar.y"
    { (yyval.statement) = 0; ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 312 "decaf_grammar.y"
    { (yyval.statement) = new WhileStatement((yyvsp[(3) - (5)].expression), (yyvsp[(5) - (5)].statement), (yylsp[(1) - (5)]).first_line, (yylsp[(1) - (5)]).first_column); ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 317 "decaf_grammar.y"
    { (yyval.statement) = new ForStatement((yyvsp[(3) - (9)].statement), (yyvsp[(5) - (9)].expression), (yyvsp[(7) - (9)].statement), (yyvsp[(9) - (9)].statement), (yylsp[(1) - (9)]).first_line, (yylsp[(1) - (9)]).first_column); ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 321 "decaf_grammar.y"
    { (yyval.statement) = (yyvsp[(1) - (3)].statement); ((BlockStatement *)(yyval.statement))->AddStatement((yyvsp[(3) - (3)].statement)); ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 322 "decaf_grammar.y"
    { (yyval.statement) = new BlockStatement((yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column); ((BlockStatement *)(yyval.statement))->AddStatement((yyvsp[(1) - (1)].statement)); ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 326 "decaf_grammar.y"
    { (yyval.statement) = new ReturnStatement((yyvsp[(2) - (2)].expression), (yylsp[(1) - (2)]).first_line, (yylsp[(1) - (2)]).first_column); ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 330 "decaf_grammar.y"
    { (yyval.statement) = new BreakStatement((yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column); ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 334 "decaf_grammar.y"
    { (yyval.statement) = new ContinueStatement((yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column); ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 338 "decaf_grammar.y"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 339 "decaf_grammar.y"
    { (yyval.expression) = 0; ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 343 "decaf_grammar.y"
    { (yyval.expression) = new BinaryExpression((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression), (yyvsp[(2) - (3)].oper)); ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 344 "decaf_grammar.y"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 347 "decaf_grammar.y"
    { (yyval.expression) = new BinaryExpression((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression), (yyvsp[(2) - (3)].oper)); ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 348 "decaf_grammar.y"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 352 "decaf_grammar.y"
    { (yyval.expression) = new BinaryExpression((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression), (yyvsp[(2) - (3)].oper)); ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 353 "decaf_grammar.y"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 357 "decaf_grammar.y"
    { (yyval.expression) = new BinaryExpression((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression), (yyvsp[(2) - (3)].oper)); ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 358 "decaf_grammar.y"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 362 "decaf_grammar.y"
    { (yyval.expression) = new BinaryExpression((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression), (yyvsp[(2) - (3)].oper)); ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 363 "decaf_grammar.y"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 366 "decaf_grammar.y"
    { (yyval.expression) = new BinaryExpression((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression), (yyvsp[(2) - (3)].oper)); ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 367 "decaf_grammar.y"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 371 "decaf_grammar.y"
    { (yyval.expression) = new UnaryExpression((yyvsp[(2) - (2)].expression), OpNot); ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 372 "decaf_grammar.y"
    { (yyval.expression) = new UnaryExpression((yyvsp[(2) - (2)].expression), (yyvsp[(1) - (2)].oper)); ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 373 "decaf_grammar.y"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 374 "decaf_grammar.y"
    { (yyval.expression) = new MethodCallExpression((yyvsp[(1) - (4)].string), (yyvsp[(3) - (4)].expression_list)); ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 375 "decaf_grammar.y"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 376 "decaf_grammar.y"
    { (yyval.expression) = (yyvsp[(2) - (3)].expression); ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 379 "decaf_grammar.y"
    { (yyval.expression) = new ConstantExpression((yyvsp[(1) - (1)].integer)); ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 380 "decaf_grammar.y"
    { (yyval.expression) = new ConstantExpression((yyvsp[(1) - (1)].integer)); ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 381 "decaf_grammar.y"
    { (yyval.expression) = new ConstantExpression((yyvsp[(1) - (1)].integer)); ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 382 "decaf_grammar.y"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 386 "decaf_grammar.y"
    { (yyval.expression) = new ConstantExpression(true); ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 387 "decaf_grammar.y"
    { (yyval.expression) = new ConstantExpression(false); ;}
    break;



/* Line 1455 of yacc.c  */
#line 2350 "decaf_grammar.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

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
		      yytoken, &yylval, &yylloc);
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

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



