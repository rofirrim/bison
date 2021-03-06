                                                                    -*- C -*-

# Graph GLR skeleton for Bison

# Copyright (C) 2002-2017 Free Software Foundation, Inc.

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

m4_include(b4_pkgdatadir/[c.m4])

## ---------------- ##
## Default values.  ##
## ---------------- ##

# Stack parameters.
m4_define_default([b4_stack_depth_max], [10000])
m4_define_default([b4_stack_depth_init],  [200])



## ------------------------ ##
## Pure/impure interfaces.  ##
## ------------------------ ##

b4_define_flag_if([pure])
# If glr.cc is including this file and thus has already set b4_pure_flag,
# do not change the value of b4_pure_flag, and do not record a use of api.pure.
m4_ifndef([b4_pure_flag],
[b4_percent_define_default([[api.pure]], [[false]])
 m4_define([b4_pure_flag],
           [b4_percent_define_flag_if([[api.pure]], [[1]], [[0]])])])

# b4_user_formals
# ---------------
# The possible parse-params formal arguments preceded by a comma.
#
# This is not shared with yacc.c in c.m4 because  GLR relies on ISO C
# formal argument declarations.
m4_define([b4_user_formals],
[m4_ifset([b4_parse_param], [, b4_formals(b4_parse_param)])])


# b4_yyerror_args
# ---------------
# Optional effective arguments passed to yyerror: user args plus yylloc, and
# a trailing comma.
m4_define([b4_yyerror_args],
[b4_pure_if([b4_locations_if([yylocp, ])])dnl
m4_ifset([b4_parse_param], [b4_args(b4_parse_param), ])])


# b4_lyyerror_args
# ----------------
# Same as above, but on the lookahead, hence &yylloc instead of yylocp.
m4_define([b4_lyyerror_args],
[b4_pure_if([b4_locations_if([&yylloc, ])])dnl
m4_ifset([b4_parse_param], [b4_args(b4_parse_param), ])])


# b4_pure_args
# ------------
# Same as b4_yyerror_args, but with a leading comma.
m4_define([b4_pure_args],
[b4_pure_if([b4_locations_if([, yylocp])])[]b4_user_args])


# b4_lpure_args
# -------------
# Same as above, but on the lookahead, hence &yylloc instead of yylocp.
m4_define([b4_lpure_args],
[b4_pure_if([b4_locations_if([, &yylloc])])[]b4_user_args])



# b4_pure_formals
# ---------------
# Arguments passed to yyerror: user formals plus yylocp with leading comma.
m4_define([b4_pure_formals],
[b4_pure_if([b4_locations_if([, YYLTYPE *yylocp])])[]b4_user_formals])


# b4_locuser_formals(LOC = yylocp)
# --------------------------------
m4_define([b4_locuser_formals],
[b4_locations_if([, YYLTYPE *m4_default([$1], [yylocp])])[]b4_user_formals])


# b4_locuser_args(LOC = yylocp)
# -----------------------------
m4_define([b4_locuser_args],
[b4_locations_if([, m4_default([$1], [yylocp])])[]b4_user_args])



## ----------------- ##
## Semantic Values.  ##
## ----------------- ##


# b4_lhs_value([TYPE])
# --------------------
# Expansion of $<TYPE>$.
m4_define([b4_lhs_value],
[b4_symbol_value([(*yyvalp)], [$1])])


# b4_rhs_data(RULE-LENGTH, NUM)
# -----------------------------
# Expand to the semantic stack place that contains value and location
# of symbol number NUM in a rule of length RULE-LENGTH.
m4_define([b4_rhs_data],
[((yyGLRStackItem const *)yyvsp)@{YYFILL (b4_subtract([$2], [$1]))@}.yystate])


# b4_rhs_value(RULE-LENGTH, NUM, [TYPE])
# --------------------------------------
# Expansion of $<TYPE>NUM, where the current rule has RULE-LENGTH
# symbols on RHS.
m4_define([b4_rhs_value],
[b4_symbol_value([b4_rhs_data([$1], [$2]).yysemantics.yysval], [$3])])



## ----------- ##
## Locations.  ##
## ----------- ##

# b4_lhs_location()
# -----------------
# Expansion of @$.
m4_define([b4_lhs_location],
[(*yylocp)])


# b4_rhs_location(RULE-LENGTH, NUM)
# ---------------------------------
# Expansion of @NUM, where the current rule has RULE-LENGTH symbols
# on RHS.
m4_define([b4_rhs_location],
[(b4_rhs_data([$1], [$2]).yyloc)])


## -------------- ##
## Declarations.  ##
## -------------- ##

# b4_shared_declarations
# ----------------------
# Declaration that might either go into the header (if --defines)
# or open coded in the parser body.  glr.cc has its own definition.
m4_define([b4_shared_declarations],
[b4_declare_yydebug[
]b4_percent_code_get([[requires]])[
]b4_token_enums[
]b4_declare_yylstype[
]b4_function_declare(b4_prefix[parse], [int], b4_parse_param)[
]b4_percent_code_get([[provides]])[]dnl
])

## -------------- ##
## Output files.  ##
## -------------- ##

# Unfortunately the order of generation between the header and the
# implementation file matters (for glr.c) because of the current
# implementation of api.value.type=union.  In that case we still use a
# union for YYSTYPE, but we generate the contents of this union when
# setting up YYSTYPE.  This is needed for other aspects, such as
# defining yy_symbol_value_print, since we need to now the name of the
# members of this union.
#
# To avoid this issue, just generate the header before the
# implementation file.  But we should also make them more independant.

# ----------------- #
# The header file.  #
# ----------------- #

b4_defines_if(
[b4_output_begin([b4_spec_defines_file])
b4_copyright([Skeleton interface for Bison GLR parsers in C],
             [2002-2015])[

]b4_cpp_guard_open([b4_spec_defines_file])[
]b4_shared_declarations[
]b4_cpp_guard_close([b4_spec_defines_file])[
]b4_output_end()
])

# ------------------------- #
# The implementation file.  #
# ------------------------- #

b4_output_begin([b4_parser_file_name])
b4_copyright([Skeleton implementation for Bison Graph GLR parsers in C],
             [2002-2015])[

/* C GLR parser skeleton written by Paul Hilfinger.  */

]b4_identification

b4_percent_code_get([[top]])[
]m4_if(b4_api_prefix, [yy], [],
[[/* Substitute the type names.  */
#define YYSTYPE ]b4_api_PREFIX[STYPE]b4_locations_if([[
#define YYLTYPE ]b4_api_PREFIX[LTYPE]])])[
]m4_if(b4_prefix, [yy], [],
[[/* Substitute the variable and function names.  */
#define yyparse ]b4_prefix[parse
#define yylex   ]b4_prefix[lex
#define yyerror ]b4_prefix[error
#define yydebug ]b4_prefix[debug
]]b4_pure_if([], [[
#define yylval  ]b4_prefix[lval
#define yychar  ]b4_prefix[char
#define yynerrs ]b4_prefix[nerrs]b4_locations_if([[
#define yylloc  ]b4_prefix[lloc]])]))[

/* First part of user declarations.  */
]b4_user_pre_prologue[

]b4_null_define[

]b4_defines_if([[#include "@basename(]b4_spec_defines_file[@)"]],
               [b4_shared_declarations])[

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE ]b4_error_verbose_if([1], [0])[
#endif

/* Default (constant) value used for initialization for null
   right-hand sides.  Unlike the standard yacc.c template, here we set
   the default value of $$ to a zeroed-out value.  Since the default
   value is undefined, this behavior is technically correct.  */
static YYSTYPE yyval_default;]b4_locations_if([[
static YYLTYPE yyloc_default][]b4_yyloc_default;])[

/* Copy the second part of user declarations.  */
]b4_user_post_prologue
b4_percent_code_get[]dnl

[#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#ifndef YYFREE
# define YYFREE free
#endif
#ifndef YYMALLOC
# define YYMALLOC malloc
#endif
#ifndef YYREALLOC
# define YYREALLOC realloc
#endif

#define YYSIZEMAX ((size_t) -1)

#ifdef __cplusplus
   typedef bool yybool;
#else
   typedef unsigned char yybool;
#endif
#define yytrue 1
#define yyfalse 0

#ifndef YYSETJMP
# include <setjmp.h>
# define YYJMP_BUF jmp_buf
# define YYSETJMP(Env) setjmp (Env)
/* Pacify clang.  */
# define YYLONGJMP(Env, Val) (longjmp (Env, Val), YYASSERT (0))
#endif

]b4_attribute_define[

#ifndef YYASSERT
# define YYASSERT(Condition) ((void) ((Condition) || (abort (), 0)))
#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  ]b4_final_state_number[
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   ]b4_last[

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  ]b4_tokens_number[
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  ]b4_nterms_number[
/* YYNRULES -- Number of rules.  */
#define YYNRULES  ]b4_rules_number[
/* YYNRULES -- Number of states.  */
#define YYNSTATES  ]b4_states_number[
/* YYMAXRHS -- Maximum number of symbols on right-hand side of rule.  */
#define YYMAXRHS ]b4_r2_max[
/* YYMAXLEFT -- Maximum number of symbols to the left of a handle
   accessed by $0, $-1, etc., in any rule.  */
#define YYMAXLEFT ]b4_max_left_semantic_context[

/* YYTRANSLATE(X) -- Bison symbol number corresponding to X.  */
#define YYUNDEFTOK  ]b4_undef_token_number[
#define YYMAXUTOK   ]b4_user_token_number_max[

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const ]b4_int_type_for([b4_translate])[ yytranslate[] =
{
  ]b4_translate[
};

#if ]b4_api_PREFIX[DEBUG || YYERROR_VERBOSE || ]b4_token_table_flag[
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  ]b4_tname[
};
#endif

#define YYPACT_NINF ]b4_pact_ninf[
#define YYTABLE_NINF ]b4_table_ninf[

]b4_parser_tables_define[

/* YYDPREC[RULE-NUM] -- Dynamic precedence of rule #RULE-NUM (0 if none).  */
static const ]b4_int_type_for([b4_dprec])[ yydprec[] =
{
  ]b4_dprec[
};

/* YYMERGER[RULE-NUM] -- Index of merging function for rule #RULE-NUM.  */
static const ]b4_int_type_for([b4_merger])[ yymerger[] =
{
  ]b4_merger[
};

/* YYCONFLP[YYPACT[STATE-NUM]] -- Pointer into YYCONFL of start of
   list of conflicting reductions corresponding to action entry for
   state STATE-NUM in yytable.  0 means no conflicts.  The list in
   yyconfl is terminated by a rule number of 0.  */
static const ]b4_int_type_for([b4_conflict_list_heads])[ yyconflp[] =
{
  ]b4_conflict_list_heads[
};

/* YYCONFL[I] -- lists of conflicting rule numbers, each terminated by
   0, pointed into by YYCONFLP.  */
]dnl Do not use b4_int_type_for here, since there are places where
dnl pointers onto yyconfl are taken, whose type is "short int *".
dnl We probably ought to introduce a type for confl.
[static const short int yyconfl[] =
{
  ]b4_conflicting_rules[
};

/* Error token number */
#define YYTERROR 1

]b4_locations_if([[
]b4_yylloc_default_define[
# define YYRHSLOC(Rhs, K) ((Rhs)[K].yystate.yyloc)
]])[

]b4_pure_if(
[
#undef yynerrs
#define yynerrs (yystackp->yyerrcnt)
#undef yychar
#define yychar (yystackp->yyrawchar)
#undef yylval
#define yylval (yystackp->yyval)
#undef yylloc
#define yylloc (yystackp->yyloc)
m4_if(b4_prefix[], [yy], [],
[#define b4_prefix[]nerrs yynerrs
#define b4_prefix[]char yychar
#define b4_prefix[]lval yylval
#define b4_prefix[]lloc yylloc])],
[YYSTYPE yylval;]b4_locations_if([[
YYLTYPE yylloc;]])[

int yynerrs;
int yychar;])[

static const int YYEOF = 0;
static const int YYEMPTY = -2;

typedef enum { yyok, yyaccept, yyabort, yyerr } YYRESULTTAG;

#define YYCHK(YYE)                              \
  do {                                          \
    YYRESULTTAG yychk_flag = YYE;               \
    if (yychk_flag != yyok)                     \
      return yychk_flag;                        \
  } while (0)

#if ]b4_api_PREFIX[DEBUG

# ifndef YYFPRINTF
#  define YYFPRINTF fprintf
# endif

]b4_yy_location_print_define[

# define YYDPRINTF(Args)                        \
  do {                                          \
    if (yydebug)                                \
      YYFPRINTF Args;                           \
  } while (0)

]b4_yy_symbol_print_define[

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                  \
  do {                                                                  \
    if (yydebug)                                                        \
      {                                                                 \
        YYFPRINTF (stderr, "%s ", Title);                               \
        yy_symbol_print (stderr, Type, Value]b4_locuser_args([Location])[);        \
        YYFPRINTF (stderr, "\n");                                       \
      }                                                                 \
  } while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;

struct yyGLRStack;
static void yypstack (struct yyGLRStack* yystackp, size_t yyk)
  YY_ATTRIBUTE_UNUSED;
static void yypdumpstack (struct yyGLRStack* yystackp)
  YY_ATTRIBUTE_UNUSED;

#else /* !]b4_api_PREFIX[DEBUG */

# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)

#endif /* !]b4_api_PREFIX[DEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH ]b4_stack_depth_init[
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYMAXDEPTH * sizeof (GLRStackItem)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH ]b4_stack_depth_max[
#endif

/* Minimum number of free items on the stack allowed after an
   allocation.  This is to allow allocation and initialization
   to be completed by functions that call yyexpandGLRStack before the
   stack is expanded, thus insuring that all necessary pointers get
   properly redirected to new data.  */
#define YYHEADROOM 2

#if YYERROR_VERBOSE

#endif /* !YYERROR_VERBOSE */

/** State numbers, as in LALR(1) machine */
typedef int yyStateNum;

/** Rule numbers, as in LALR(1) machine */
typedef int yyRuleNum;

/** Grammar symbol */
typedef int yySymbol;

/** Item references, as in LALR(1) machine */
typedef short int yyItemNum;

typedef struct yyGLRState yyGLRState;
typedef struct yyGLRStateSet yyGLRStateSet;
typedef struct yySemanticOption yySemanticOption;
typedef union yyGLRStackItem yyGLRStackItem;
typedef struct yyGLRStack yyGLRStack;

struct yyGLRState {
  /** Type tag: always true.  */
  yybool yyisState;
  /** Type tag for yysemantics.  If true, yysval applies, otherwise
   *  yyfirstVal applies.  */
  yybool yyresolved;
  /** Number of corresponding LALR(1) machine state.  */
  yyStateNum yylrState;
  /** Preceding state in this stack */
  yyGLRState* yypred;
  /** Source position of the last token produced by my symbol */
  size_t yyposn;
  union {
    /** First in a chain of alternative reductions producing the
     *  non-terminal corresponding to this state, threaded through
     *  yynext.  */
    yySemanticOption* yyfirstVal;
    /** Semantic value for this state.  */
    YYSTYPE yysval;
  } yysemantics;]b4_locations_if([[
  /** Source location for this state.  */
  YYLTYPE yyloc;]])[
};

struct yyGLRStateSet {
  yyGLRState** yystates;
  /** During nondeterministic operation, yylookaheadNeeds tracks which
   *  stacks have actually needed the current lookahead.  During deterministic
   *  operation, yylookaheadNeeds[0] is not maintained since it would merely
   *  duplicate yychar != YYEMPTY.  */
  yybool* yylookaheadNeeds;
  size_t yysize, yycapacity;
};

struct yySemanticOption {
  /** Type tag: always false.  */
  yybool yyisState;
  /** Rule number for this reduction */
  yyRuleNum yyrule;
  /** The last RHS state in the list of states to be reduced.  */
  yyGLRState* yystate;
  /** The lookahead for this reduction.  */
  int yyrawchar;
  YYSTYPE yyval;]b4_locations_if([[
  YYLTYPE yyloc;]])[
  /** Next sibling in chain of options.  To facilitate merging,
   *  options are chained in decreasing order by address.  */
  yySemanticOption* yynext;
};

/** Type of the items in the GLR stack.  The yyisState field
 *  indicates which item of the union is valid.  */
union yyGLRStackItem {
  yyGLRState yystate;
  yySemanticOption yyoption;
};

struct yyGLRStack {
  int yyerrState;
]b4_locations_if([[  /* To compute the location of the error token.  */
  yyGLRStackItem yyerror_range[3];]])[
]b4_pure_if(
[
  int yyerrcnt;
  int yyrawchar;
  YYSTYPE yyval;]b4_locations_if([[
  YYLTYPE yyloc;]])[
])[
  YYJMP_BUF yyexception_buffer;
  yyGLRStackItem* yyitems;
  yyGLRStackItem* yynextFree;
  size_t yyspaceLeft;
  yyGLRState* yysplitPoint;
  yyGLRState* yylastDeleted;
  yyGLRStateSet yytops;
};

#if YYSTACKEXPANDABLE
static void yyexpandGLRStack (yyGLRStack* yystackp);
#endif

#if ]b4_api_PREFIX[DEBUG || YYERROR_VERBOSE
/** A printable representation of TOKEN.  */
static inline const char*
yytokenName (yySymbol yytoken)
{
  if (yytoken == YYEMPTY)
    return "";

  return yytname[yytoken];
}
#endif

/** Fill in YYVSP[YYLOW1 .. YYLOW0-1] from the chain of states starting
 *  at YYVSP[YYLOW0].yystate.yypred.  Leaves YYVSP[YYLOW1].yystate.yypred
 *  containing the pointer to the next state in the chain.  */
static void yyfillin (yyGLRStackItem *, int, int) YY_ATTRIBUTE_UNUSED;
static void
yyfillin (yyGLRStackItem *yyvsp, int yylow0, int yylow1)
{
  int i;
  yyGLRState *s = yyvsp[yylow0].yystate.yypred;
  for (i = yylow0-1; i >= yylow1; i -= 1)
    {
#if ]b4_api_PREFIX[DEBUG
      yyvsp[i].yystate.yylrState = s->yylrState;
#endif
      yyvsp[i].yystate.yyresolved = s->yyresolved;
      if (s->yyresolved)
        yyvsp[i].yystate.yysemantics.yysval = s->yysemantics.yysval;
      else
        /* The effect of using yysval or yyloc (in an immediate rule) is
         * undefined.  */
        yyvsp[i].yystate.yysemantics.yyfirstVal = YY_NULLPTR;]b4_locations_if([[
      yyvsp[i].yystate.yyloc = s->yyloc;]])[
      s = yyvsp[i].yystate.yypred = s->yypred;
    }
}

/* Do nothing if YYNORMAL or if *YYLOW <= YYLOW1.  Otherwise, fill in
 * YYVSP[YYLOW1 .. *YYLOW-1] as in yyfillin and set *YYLOW = YYLOW1.
 * For convenience, always return YYLOW1.  */
static inline int yyfill (yyGLRStackItem *, int *, int, yybool)
     YY_ATTRIBUTE_UNUSED;
static inline int
yyfill (yyGLRStackItem *yyvsp, int *yylow, int yylow1, yybool yynormal)
{
  if (!yynormal && yylow1 < *yylow)
    {
      yyfillin (yyvsp, *yylow, yylow1);
      *yylow = yylow1;
    }
  return yylow1;
}

static void
yyuserMerge (int yyn, YYSTYPE* yy0, YYSTYPE* yy1)
{
  YYUSE (yy0);
  YYUSE (yy1);

  switch (yyn)
    {
]b4_mergers[
      default: break;
    }
}

#if YYERROR_VERBOSE

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
static size_t
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      size_t yyn = 0;
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
    return strlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

#endif /* !YYERROR_VERBOSE */

                              /* Bison grammar-table manipulation.  */


/** Number of symbols composing the right hand side of rule #RULE.  */
static inline int
yyrhsLength (yyRuleNum yyrule)
{
  return yyr2[yyrule];
}

/** Left-hand-side symbol for rule #YYRULE.  */
static inline yySymbol
yylhsNonterm (yyRuleNum yyrule)
{
  return yyr1[yyrule];
}

#define yypact_value_is_default(Yystate) \
  ]b4_table_value_equals([[pact]], [[Yystate]], [b4_pact_ninf])[

/** True iff LR state YYSTATE has only a default reduction (regardless
 *  of token).  */
static inline yybool
yyisDefaultedState (yyStateNum yystate)
{
  return yypact_value_is_default (yypact[yystate]);
}

/** The default reduction for YYSTATE, assuming it has one.  */
static inline yyRuleNum
yydefaultAction (yyStateNum yystate)
{
  return yydefact[yystate];
}

#define yytable_value_is_error(Yytable_value) \
  ]b4_table_value_equals([[table]], [[Yytable_value]], [b4_table_ninf])[

/** Set *YYACTION to the action to take in YYSTATE on seeing YYTOKEN.
 *  Result R means
 *    R < 0:  Reduce on rule -R.
 *    R = 0:  Error.
 *    R > 0:  Shift to state R.
 *  Set *YYCONFLICTS to a pointer into yyconfl to a 0-terminated list
 *  of conflicting reductions.
 */
static inline void
yygetLRActions (yyStateNum yystate, int yytoken,
                int* yyaction, const short int** yyconflicts)
{
  int yyindex = yypact[yystate] + yytoken;
  if (yypact_value_is_default (yypact[yystate])
      || yyindex < 0 || YYLAST < yyindex || yycheck[yyindex] != yytoken)
    {
      *yyaction = -yydefact[yystate];
      *yyconflicts = yyconfl;
    }
  else if (! yytable_value_is_error (yytable[yyindex]))
    {
      *yyaction = yytable[yyindex];
      *yyconflicts = yyconfl + yyconflp[yyindex];
    }
  else
    {
      *yyaction = 0;
      *yyconflicts = yyconfl + yyconflp[yyindex];
    }
}

/** Compute post-reduction state.
 * \param yystate   the current state
 * \param yysym     the nonterminal to push on the stack
 */
static inline yyStateNum
yyLRgotoState (yyStateNum yystate, yySymbol yysym)
{
  int yyr = yypgoto[yysym - YYNTOKENS] + yystate;
  if (0 <= yyr && yyr <= YYLAST && yycheck[yyr] == yystate)
    return yytable[yyr];
  else
    return yydefgoto[yysym - YYNTOKENS];
}

static inline yybool
yyisShiftAction (int yyaction)
{
  return 0 < yyaction;
}

static inline yybool
yyisErrorAction (int yyaction)
{
  return yyaction == 0;
}

#define YYCHK1(YYE)                                                          \
  do {                                                                       \
    switch (YYE) {                                                           \
    case yyok:                                                               \
      break;                                                                 \
    case yyabort:                                                            \
      goto yyabortlab;                                                       \
    case yyaccept:                                                           \
      goto yyacceptlab;                                                      \
    case yyerr:                                                              \
      goto yyuser_error;                                                     \
    default:                                                                 \
      goto yybuglab;                                                         \
    }                                                                        \
  } while (0)

/*----------.
| yyparse.  |
`----------*/


// Mini pool implementation
//
#undef DEBUG_POOL

#ifdef DEBUG_POOL

#define DEFINE_CHECK_DOUBLE_FREE(TYPENAME) \
static void check_double_free_##TYPENAME(minipool_##TYPENAME##_t *mp, TYPENAME *d) \
{ \
  minipool_##TYPENAME##_item_t *current = mp->free; \
  while (current != NULL) \
  { \
      if ((TYPENAME*)current == d) \
      { \
          internal_error("%s pool: double free with '%p'\n", #TYPENAME, d); \
      } \
      current = current->next; \
  } \
}

#define CHECK_DOUBLE_FREE(TYPENAME, POOL, PTR) \
  check_double_free_##TYPENAME(POOL, PTR);

#else

#define DEFINE_CHECK_DOUBLE_FREE(TYPENAME)
#define CHECK_DOUBLE_FREE(TYPENAME, POOL, PTR)

#endif

#define DEFINE_POOL(TYPENAME) \
\
typedef union minipool_##TYPENAME##_item_tag { \
  union minipool_##TYPENAME##_item_tag *next; \
  TYPENAME datum; \
} minipool_##TYPENAME##_item_t; \
\
typedef struct minipool_##TYPENAME##_arena_tag { \
  minipool_##TYPENAME##_item_t *storage; \
  struct minipool_##TYPENAME##_arena_tag *next; \
} minipool_##TYPENAME##_arena_t; \
\
typedef struct minipool_##TYPENAME##_tag { \
  minipool_##TYPENAME##_arena_t *arena; \
  int arena_size; \
  minipool_##TYPENAME##_item_t *free; \
} minipool_##TYPENAME##_t; \
\
static minipool_##TYPENAME##_arena_t *minipool_##TYPENAME##_arena_new(int arena_size) { \
  minipool_##TYPENAME##_arena_t *arena = malloc(sizeof(*arena)); \
  arena->next = NULL; \
  arena->storage = malloc(sizeof(*arena->storage) * arena_size); \
 \
  for (int i = 1; i < arena_size; i++) { \
    arena->storage[i - 1].next = &arena->storage[i]; \
  } \
  arena->storage[arena_size - 1].next = NULL; \
 \
  return arena; \
} \
\
void minipool_##TYPENAME##_init(minipool_##TYPENAME##_t *mp, int arena_size) { \
  mp->arena_size = arena_size; \
  mp->arena = minipool_##TYPENAME##_arena_new(arena_size); \
 \
  mp->free = mp->arena->storage; \
} \
\
TYPENAME *minipool_##TYPENAME##_alloc(minipool_##TYPENAME##_t *mp) { \
  if (mp->free == NULL) { \
    minipool_##TYPENAME##_arena_t *arena = minipool_##TYPENAME##_arena_new(mp->arena_size); \
    arena->next = mp->arena; \
    mp->arena = arena; \
    mp->free = mp->arena->storage; \
  } \
 \
  minipool_##TYPENAME##_item_t *current = mp->free; \
  mp->free = current->next; \
 \
  return &current->datum; \
} \
\
DEFINE_CHECK_DOUBLE_FREE(TYPENAME) \
\
void minipool_##TYPENAME##_free(minipool_##TYPENAME##_t *mp, TYPENAME *d) { \
  minipool_##TYPENAME##_item_t *current = \
      (minipool_##TYPENAME##_item_t *)((char *)d - offsetof(minipool_##TYPENAME##_item_t, datum)); \
 \
  CHECK_DOUBLE_FREE(TYPENAME, mp, d); \
  current->next = mp->free; \
  mp->free = current; \
} \
\
void minipool_##TYPENAME##_destroy(minipool_##TYPENAME##_t *mp) { \
  minipool_##TYPENAME##_arena_t *arena = mp->arena; \
  do { \
    minipool_##TYPENAME##_arena_t *arena_to_free = arena; \
    arena = arena->next; \
    free(arena_to_free->storage); \
    free(arena_to_free); \
  } while (arena != NULL); \
}

// A stack node represents a node of the GSS
struct stack_node_tag;
typedef struct stack_node_tag stack_node_t;

// A stack node edge represents an edge of the GSS
struct stack_node_edge_tag;
typedef struct stack_node_edge_tag stack_node_edge_t;

// Payload of an edge
typedef struct payload_tag payload_t;

// The GSS itself, it keeps a list
// of active parsers which are themselves
// nodes of the GSS
typedef struct stack_node_set_tag stack_node_set_t;

// Simple reference counting mechanism.
typedef struct ref_count_tag refcount_t;
struct ref_count_tag
{
    int refs;
    void (*walk)(void *, void (*)(void*));
    void (*destroy)(void*);
};

static inline void decref_(void *p)
{
    if (p == NULL)
        return;

    refcount_t* r = (refcount_t*)p;
    if (0 == --(r->refs))
    {
        (r->walk)(p, decref_);
        (r->destroy)(p);
    }
}

#define incref(p) ({ __typeof__((p)) _t = (p); _t->_ref.refs++; _t; })
#define decref(p) ({ __typeof__((p)) _t = (p); decref_(&(_t->_ref));  })

// p = q; but updating references
// #define assignref(p, q) ({ __typeof__(p) _p = p; decref(_p); __typeof__(q) _q = q; if (_q != NULL) incref(_q); _p = _q; })

#define newrefcounted(type) ({ \
        type *_t = minipool_##type##_alloc(&mp_##type); \
        _t->_ref.refs = 1; \
        _t->_ref.walk = walk_##type; \
        _t->_ref.destroy = destroy_##type; \
        _t; })

// A stack node represents a state and a
// set of predecessors in the GSS. These
// predecessors are accessible through
// the edges of this node

typedef
struct stack_node_edge_set_tag
{
    stack_node_edge_t *edge;
    struct stack_node_edge_set_tag *next;
} stack_node_edge_set_t;

DEFINE_POOL(stack_node_edge_set_t);
minipool_stack_node_edge_set_t_t mp_stack_node_edge_set_t;

struct stack_node_tag
{
    /* private */ refcount_t _ref;

    yyStateNum state;
    stack_node_edge_set_t *preds;
};

DEFINE_POOL(stack_node_t);
minipool_stack_node_t_t mp_stack_node_t;

// A stack node edge refers to another stack node and has a payload
struct stack_node_edge_tag
{
    /* private */ refcount_t _ref;
    stack_node_t* target;

    payload_t *payload;
};

DEFINE_POOL(stack_node_edge_t);
minipool_stack_node_edge_t_t mp_stack_node_edge_t;

struct stack_node_set_tag
{
    stack_node_t *stack;
    stack_node_set_t *next;
};

DEFINE_POOL(stack_node_set_t);
minipool_stack_node_set_t_t mp_stack_node_set_t;

// Two kinds of payloads for edges: those that immediately encode the
// semantic value and those that defer the semantic value and only encode
// the arguments and the rule that can be used to compute the semantic value
typedef enum payload_kind_tag payload_kind_t;
enum payload_kind_tag
{
    P_INVALID = 0,
    P_SHIFT,
    P_DEFINITIVE_REDUCE,
    P_DEFERRED_REDUCE,
};

// Immediate payload
typedef struct payload_shift_tag payload_shift_t;
struct payload_shift_tag
{
    size_t yyposn;
    YYSTYPE yyval;
    ]b4_locations_if([YYLTYPE yyloc;])[
};

// Deferred payload
typedef struct payload_reduce_node_tag payload_reduce_node_t;
struct payload_reduce_node_tag
{
    payload_t* payload;
    struct payload_reduce_node_tag *next;
};
DEFINE_POOL(payload_reduce_node_t);
minipool_payload_reduce_node_t_t mp_payload_reduce_node_t;

typedef struct payload_reduce_tag payload_reduce_t;
struct payload_reduce_tag
{
    yyRuleNum rule;
    YYSTYPE yyval;
    ]b4_locations_if([YYLTYPE yyloc;])[
    payload_reduce_node_t *values;
};

// The payload of an edge
struct payload_tag
{
    /* private */ refcount_t _ref;
    payload_kind_t kind;
    payload_t *next;
    union {
        payload_shift_t s;
        payload_reduce_t r;
    };
};

DEFINE_POOL(payload_t);
minipool_payload_t_t mp_payload_t;

static void walk_payload_t(void *p, void (*callback)(void*))
{
    if (p == NULL)
        return;

    payload_t* payload = (payload_t*)p;

    if (payload->kind == P_DEFERRED_REDUCE
            || payload->kind == P_DEFINITIVE_REDUCE)
    {
        payload_reduce_node_t* pn = payload->r.values;
        while (pn != NULL)
        {
            callback(pn->payload);
            pn = pn->next;
        }
    }

    callback(payload->next);
}

static void destroy_payload_t(void *p)
{
    payload_t* payload = (payload_t*)p;
    if (payload->kind == P_DEFERRED_REDUCE
            || payload->kind == P_DEFINITIVE_REDUCE)
    {
        payload_reduce_node_t* pn = payload->r.values;
        while (pn != NULL)
        {
            payload_reduce_node_t* current_pn = pn;
            pn = pn->next;

            minipool_payload_reduce_node_t_free(&mp_payload_reduce_node_t, current_pn);
        }
    }
    minipool_payload_t_free(&mp_payload_t, payload);
}

static inline payload_t* new_payload(payload_kind_t kind)
{
    payload_t *payload = newrefcounted(payload_t);
    payload->kind = kind;
    payload->next = NULL;
    return payload;
}

static stack_node_set_t *gss;

static inline void gss_init(void)
{
    gss = NULL;
}

static inline void gss_add_stack(stack_node_t* stack)
{
    stack_node_set_t *new_item = minipool_stack_node_set_t_alloc(&mp_stack_node_set_t);
    new_item->stack = stack;
    new_item->next = gss;

    gss = new_item;
}

static inline void gss_destroy(void)
{
    stack_node_set_t *it = gss;
    while (it != NULL)
    {
        decref(it->stack);
        stack_node_set_t *current = it;
        it = it->next;
        minipool_stack_node_set_t_free(&mp_stack_node_set_t, current);
    }
    gss = NULL;
}

// A path, computed when performing reductions
typedef
struct path_tag
{
    stack_node_edge_t *edge;
    struct path_tag *next;
} path_t;

DEFINE_POOL(path_t);
minipool_path_t_t mp_path_t;

typedef struct queue_item_tag queue_item_t;
struct queue_item_tag
{
    stack_node_t* stack;
    path_t *path;
    int rule;
};

DEFINE_POOL(queue_item_t);
minipool_queue_item_t_t mp_queue_item_t;

static void destroy_queue_item_t(queue_item_t* q)
{
    path_t *path_it = q->path;
    while (path_it != NULL)
    {
        path_t *current_path_it = path_it;
        path_it = path_it->next;
        minipool_path_t_free(&mp_path_t, current_path_it);
    }
    minipool_queue_item_t_free(&mp_queue_item_t, q);
}

typedef struct path_queue_tag path_queue_t;
typedef struct path_queue_node_tag
{
    queue_item_t* item;
    struct path_queue_node_tag* next;
    struct path_queue_node_tag* prev;
} path_queue_node_t;

DEFINE_POOL(path_queue_node_t);
minipool_path_queue_node_t_t mp_path_queue_node_t;

struct path_queue_tag
{
    path_queue_node_t *tail;
    path_queue_node_t *head;
};

static path_queue_t path_queue;

static inline void path_queue_init(void)
{
    path_queue.head = NULL;
    path_queue.tail = NULL;
}

static inline yybool path_queue_is_empty(void)
{
    return path_queue.tail == NULL;
}

static inline void path_queue_add(queue_item_t* qi)
{
    path_queue_node_t *pqn = minipool_path_queue_node_t_alloc(&mp_path_queue_node_t);
    pqn->item = qi;
    pqn->prev = NULL;

    pqn->next = path_queue.tail;
    if (path_queue.tail != NULL)
    {
        path_queue.tail->prev = pqn;
    }

    path_queue.tail = pqn;

    if (path_queue.head == NULL)
    {
        path_queue.head = pqn;
    }
}

static inline queue_item_t* path_queue_dequeue(void)
{
    path_queue_node_t *pqn = path_queue.head;
    queue_item_t* qi = pqn->item;

    path_queue.head = path_queue.head->prev;
    if (path_queue.head == NULL)
    {
        path_queue.tail = NULL;
    }

    minipool_path_queue_node_t_free(&mp_path_queue_node_t, pqn);

    return qi;
}

static inline void path_queue_destroy(void)
{
    while (!path_queue_is_empty())
    {
        queue_item_t* q = path_queue_dequeue();
        destroy_queue_item_t(q);
    }
}

typedef struct path_predecessor_tag path_predecessor_t;

struct path_predecessor_tag
{
    path_predecessor_t* pred;
    stack_node_edge_t* edge;
};

static inline void compute_paths_rec(
        stack_node_t* stack,
        stack_node_edge_t* edge, int rule,
        int length,
        path_predecessor_t* pred,
        stack_node_edge_t* contains_link)
{
    path_predecessor_t p;
    p.pred = pred;
    p.edge = edge;

    if (length == 0)
    {
        if (contains_link != NULL)
        {
            // We have to check if the current path contains the link
            yybool found = yyfalse;
            path_predecessor_t* it = &p;
            while (it != NULL)
            {
                if (it->edge == contains_link)
                {
                    found = yytrue;
                    break;
                }

                it = it->pred;
            }
            // Do nothing
            if (!found)
                return;
        }
        // create the queue item
        queue_item_t* qi = minipool_queue_item_t_alloc(&mp_queue_item_t);
        qi->stack = stack;
        qi->rule = rule;

        // assemble the path
        path_predecessor_t* it;

        // copy the path
        path_t* head = NULL;
        path_t* tail = NULL;
        for (it = &p; it != NULL; it = it->pred)
        {
            path_t *new_path = minipool_path_t_alloc(&mp_path_t);
            new_path->edge = it->edge;
            new_path->next = NULL;
            if (head == NULL)
            {
                head = new_path;
                tail = new_path;
            }
            else
            {
                tail->next = new_path;
                tail = new_path;
            }
        }
        qi->path = head;

        path_queue_add(qi);
    }
    else
    {
        stack_node_edge_set_t *edge_set = edge->target->preds;
        while (edge_set != NULL)
        {
            stack_node_edge_t* pred_edge = edge_set->edge;
            compute_paths_rec(stack, pred_edge, rule, length - 1, &p, contains_link);
            edge_set = edge_set->next;
        }
    }
}

static inline void compute_paths(stack_node_t* current_stack, int rule, int length)
{
    YYDPRINTF((stderr, "Computing paths of length %d for rule r%d\n", length, rule - 1));
    YYASSERT(current_stack != NULL);
    YYASSERT(rule > 0);
    YYASSERT(length >= 0);

    if (length > 0)
    {
        stack_node_edge_set_t *edge_set = current_stack->preds;
        while (edge_set != NULL)
        {
            stack_node_edge_t* pred_edge = edge_set->edge;
            compute_paths_rec(current_stack, pred_edge, rule, length - 1, NULL, /* contains_link */ NULL);
            edge_set = edge_set->next;
        }
    }
    else
    {
        // Add a degenerate path
        queue_item_t* qi = minipool_queue_item_t_alloc(&mp_queue_item_t);
        qi->stack = current_stack;
        qi->rule = rule;
        qi->path = NULL;

        path_queue_add(qi);
    }
}

static inline void compute_paths_that_use_link(stack_node_t* current_stack,
        stack_node_edge_t* contains_link,
        int rule, int length)
{
    YYDPRINTF((stderr, "Computing paths of length %d for rule r%d that use a given link\n", length, rule - 1));
    YYASSERT(current_stack != NULL);
    YYASSERT(rule > 0);
    YYASSERT(length >= 0);

    // No path will be able to use that link
    if (length == 0)
        return;

    stack_node_edge_set_t *edge_set = current_stack->preds;
    while (edge_set != NULL)
    {
        stack_node_edge_t* pred_edge = edge_set->edge;
        compute_paths_rec(current_stack, pred_edge, rule, length - 1, NULL, contains_link);
        edge_set = edge_set->next;
    }
}

static inline int get_rule_length(int rule)
{
    return yyrhsLength(rule);
}

]

m4_undefine([b4_rhs_value])
m4_define([b4_rhs_value],
[b4_symbol_value([in_yyvalp@{$2 - 1@}], [$3])])

m4_undefine([b4_rhs_location])
m4_define([b4_rhs_location],
[in_yylocp@{$2 - 1@}])

[
static inline void
user_action (yyRuleNum yyn,
        /* out */
        YYSTYPE* yyvalp]b4_locations_if([, YYLTYPE *yylocp])[,
        /* in */
        size_t yyrhslen, 
        YYSTYPE* in_yyvalp]b4_locations_if([, YYLTYPE *in_yylocp])[
        /* user args */
        ]b4_user_formals[)
{
    YYDPRINTF((stderr, "Running user action for rule r%d\n", yyn - 1));
]b4_parse_param_use([yyvalp], [yylocp])dnl
[  YYUSE (yyrhslen);
   YYUSE(in_yyvalp);
   YYUSE(in_yylocp);
# undef yyerrok
# define yyerrok (yystackp->yyerrState = 0)
# undef YYACCEPT
# define YYACCEPT YYASSERT(0 && "YYACCEPT not supported")
# undef YYABORT
# define YYABORT YYASSERT(0 && "YYABORT not supported")
# undef YYERROR
# define YYERROR YYASSERT(0 && "YYERROR not supported")
# undef YYRECOVERING
# define YYRECOVERING() YYASSERT(0 && "YYRECOVERING not supported")
# undef yyclearin
# define yyclearin YYASSERT(0 && "yyclearin not supported")
# undef YYFILL
# define YYFILL(N) YYASSERT(0 && "YYFILL not supported")
# undef YYBACKUP
# define YYBACKUP(Token, Value) YYASSERT(0 && "YYBACKUP not supported")

  if (yyrhslen == 0)
    *yyvalp = yyval_default;
  else
    *yyvalp = yyvalp[0];
]b4_locations_if([[
  /* FIXME: compute default location */
  if (yyrhslen == 0)
  {
    *yylocp = yyloc_default;
    }
  else
  {
    *yylocp = in_yylocp[0];
    }
  /* YYLLOC_DEFAULT ((*yylocp), (yyvsp - yyrhslen), yyrhslen); */
]])[
  switch (yyn)
    {
      ]b4_user_actions[
      default: break;
    }
# undef yyerrok
# undef YYABORT
# undef YYACCEPT
# undef YYERROR
# undef YYBACKUP
# undef yyclearin
# undef YYRECOVERING
}

static inline char payload_is_reduce(payload_t* p)
{
    return p->kind == P_DEFERRED_REDUCE
        || p->kind == P_DEFINITIVE_REDUCE;
}

static inline char payload_is_shift(payload_t* p)
{
    return p->kind == P_SHIFT;
}


// FIXME: can we do this faster?
static inline stack_node_t* gss_find_stack_node_in_range(int dest_state, stack_node_set_t* begin, stack_node_set_t* end)
{
    stack_node_set_t *it = begin;
    while (it != end)
    {
        stack_node_t* stack = it->stack;
        if (stack->state == dest_state)
            return stack;

        it = it->next;
    }
    return NULL;
}

static inline stack_node_t* gss_find_stack_node(int dest_state)
{
    return gss_find_stack_node_in_range(dest_state, gss, NULL);
}

#if ]b4_api_PREFIX[DEBUG

static void print_indent(int level)
{
    int i;
    for (i = 0; i < level; i++)
    {
        fprintf(stderr, "|");
    }
}

static inline void print_payload(payload_t* p, int level);

static inline void print_single_payload(payload_t* p, int level)
{
    switch (p->kind)
    {
        case P_SHIFT:
            {
                print_indent(level);
                fprintf(stderr, "- Shift %zd [%p]\n",
                        p->s.yyposn,
                        p);
                break;
            }
        case P_DEFINITIVE_REDUCE:
        case P_DEFERRED_REDUCE:
            {
                print_indent(level);
                fprintf(stderr, "- %s Reduce Rule: r%d [%p]\n",
                        p->kind == P_DEFINITIVE_REDUCE ? "Definitive" : "Deferred",
                        p->r.rule - 1,
                        p);
                print_indent(level);
                fprintf(stderr, "- Payloads of reduce rule\n");
                payload_reduce_node_t* prn = p->r.values;
                while (prn != NULL)
                {
                    print_payload(prn->payload, level + 1);
                    prn = prn->next;
                }
                break;
            }
        default:
            YYASSERT(yyfalse);
    }
}

static inline void print_payload(payload_t* p, int level)
{
    payload_t* d;
    int i = 0;
    print_indent(level);
    fprintf(stderr, "- Payloads\n");
    for (d = p; d != NULL; d = d->next)
    {
        print_indent(level + 1);
        fprintf(stderr, "- Payload %d [refs=%d]\n", i, d->_ref.refs);
        print_single_payload(d, level + 2);
        i++;
    }
}

static inline void print_edge(stack_node_edge_t* edge, int level)
{
    print_payload(edge->payload, level);
}

static inline void print_stack_rec(stack_node_t* stack, int level)
{
    print_indent(level);
    fprintf(stderr, "- State %d [%p]\n", stack->state, stack);

    if (stack->preds == NULL)
    {
        // Do nothing
        print_indent(level + 1);
        fprintf(stderr, "<<empty stack>>\n");
    }
    else
    {
        // More than one predecessor
        int i = 0;
        stack_node_edge_set_t* preds = stack->preds;
        while (preds != NULL)
        {
            print_indent(level + 1);
            fprintf(stderr, "- Predecessor %d [%p]\n", i, preds->edge);
            print_edge(preds->edge, level + 2);

            print_stack_rec(preds->edge->target, level);

            preds = preds->next;
            i++;
        }
    }
}

static inline void print_stacks(void)
{
    if (!yydebug)
        return;

    stack_node_set_t *it = gss;
    int num_active_stacks = 0;
    while (it != NULL)
    {
        num_active_stacks++;
        it = it->next;
    }


    YYDPRINTF((stderr, "There are %d active stacks\n", num_active_stacks));

    it = gss;
    int i = 0;
    while (it != NULL)
    {
        stack_node_t* current_stack = it->stack;
        fprintf(stderr, "************\n");
        fprintf(stderr, "Stack #%d\n", i);
        fprintf(stderr, "************\n");
        print_stack_rec(current_stack, 0);
        fprintf(stderr, "\n\n");
        i++;
        it = it->next;
    }

}

static inline int stack_id(stack_node_t* stack)
{
    stack_node_set_t *it = gss;
    int i = 0;
    while (it != NULL)
    {
        stack_node_t* current_stack = it->stack;
        if (current_stack == stack)
            return i;
        i++;
        it = it->next;
    }
    return -1;
}
#endif

static inline void evaluate_payload(payload_t* p]b4_user_formals[);
static inline stack_node_t* new_stack(yyStateNum state);
static inline YYSTYPE get_yyval_of_payload(payload_t* p);

]b4_locations_if([
static inline YYLTYPE get_yyloc_of_payload(payload_t* p);
])[

static inline stack_node_edge_t* stack_node_add_link(stack_node_t* target,
        stack_node_t* source,
        payload_t *payload);

static inline void enqueue_reductions(stack_node_t* stack, int token)
{
    YYDPRINTF((stderr, "Enqueueing reductions for stack #%d\n", stack_id(stack)));
    if (yyisDefaultedState(stack->state))
    {
        // Default reduction
        int rule = yydefaultAction (stack->state);
        if (rule != 0)
        {
            int len = get_rule_length(rule);
            YYDPRINTF((stderr, "Stack #%d [%p] in state s%d has a default action with rule r%d, length is %d\n", stack_id(stack), stack, stack->state, rule - 1, len));
            compute_paths(stack, rule, len);
        }
    }
    else
    {
        int action = 0;
        const short int* conflicts;
        yygetLRActions(stack->state, token, &action, &conflicts);

        if (yyisShiftAction(action))
        {
            // Do nothing
        }
        else if (yyisErrorAction(action))
        {
            // Do nothing
        }
        else
        {
            int rule = -action;
            int len = get_rule_length(rule);

            YYDPRINTF((stderr, "Immediate action for stack #%d [%p] in state s%d is a reduce with rule r%d, length is %d. Conflicts? %s\n", stack_id(stack), stack, stack->state, rule - 1,
                        len,
                        *conflicts == 0 ? "no" : "yes"));
            // It should be a reduce

            YYDPRINTF((stderr, "Reducing stack #%d [%p] by rule r%d\n", stack_id(stack), stack, rule - 1));

            compute_paths(stack, rule, len);
        }

        if (*conflicts != 0)
        {
            YYDPRINTF((stderr, "Stack #%d [%p] has conflicts\n", stack_id(stack), stack));
        }

        while (*conflicts != 0)
        {
            // These are always reduces
            //
            // FIXME:
            // for each path p of lengh len(a) from stack
            //   enqueue(p, "N->a") into path_queue

            int rule = *conflicts;

            int len = get_rule_length(rule);

            YYDPRINTF((stderr, "Stack #%d [%p] has a conflictive reduction with rule r%d with length %d\n", stack_id(stack), stack, rule - 1, len));


            compute_paths(stack, rule, len);

            conflicts++;
        }
    }
    YYDPRINTF((stderr, "Done enqueuing reductions for stack #%d\n", stack_id(stack)));
}

static inline void enqueue_limited_reductions(stack_node_edge_t* link, int token)
{
#if ]b4_api_PREFIX[DEBUG
    print_stacks();
#endif

    stack_node_set_t *it = gss;
    while (it != NULL)
    {
        stack_node_t* current_stack = it->stack;

        if (yyisDefaultedState(current_stack->state))
        {
            // Default reduction
            int rule = yydefaultAction (current_stack->state);
            if (rule != 0)
            {
                int len = get_rule_length(rule);
                compute_paths_that_use_link(current_stack, link, rule, len);
            }
        }
        else
        {
            int action = 0;
            const short int* conflicts;
            yygetLRActions(current_stack->state, token, &action, &conflicts);

            if (yyisShiftAction(action))
            {
                // do nothing
            }
            else if (yyisErrorAction(action))
            {
                // do nothing
            }
            else
            {
                // It should be a reduce
                int rule = -action;
                int len = get_rule_length(rule);
                compute_paths_that_use_link(current_stack, link, rule, len);
            }

            while (*conflicts != 0)
            {
                // These are always reduces
                int rule = *conflicts;
                int len = get_rule_length(rule);
                compute_paths_that_use_link(current_stack, link, rule, len);

                conflicts++;
            }
        }

        it = it->next;
    }
}

static void walk_stack_node_edge_t(void *p, void (*callback)(void *p))
{
    if (p == NULL)
        return;

    stack_node_edge_t* edge = (stack_node_edge_t*)p;

    callback(edge->target);
    callback(edge->payload);
}

static void destroy_stack_node_edge_t(void *p)
{
    stack_node_edge_t *sne = (stack_node_edge_t*)p;
    minipool_stack_node_edge_t_free(&mp_stack_node_edge_t, sne);
}

static inline stack_node_edge_t* stack_node_add_link(stack_node_t* target,
        stack_node_t* source,
        payload_t *payload)
{
    YYASSERT(target != NULL);
    YYASSERT(source != NULL);

    stack_node_edge_t* new_edge = newrefcounted(stack_node_edge_t);
    new_edge->target = incref(target);
    new_edge->payload = payload;

    stack_node_edge_set_t* edge_set = minipool_stack_node_edge_set_t_alloc(&mp_stack_node_edge_set_t);
    edge_set->next = source->preds;
    edge_set->edge = incref(new_edge);

    source->preds = edge_set;

    return new_edge;
}

static void walk_stack_node_t(void *p, void (*callback)(void*))
{
    if (p == NULL)
        return;

    stack_node_t* stack = (stack_node_t*)p;

    stack_node_edge_set_t* edge_set = stack->preds;
    while (edge_set != NULL)
    {
        callback(edge_set->edge);
        edge_set = edge_set->next;
    }
}

static void destroy_stack_node_t(void *p)
{
    stack_node_t* stack = (stack_node_t*)p;

    stack_node_edge_set_t *edge_set = stack->preds;
    while (edge_set != NULL)
    {
        stack_node_edge_set_t *current_edge_set = edge_set;
        edge_set = edge_set->next;

        decref(current_edge_set->edge);
        minipool_stack_node_edge_set_t_free(&mp_stack_node_edge_set_t, current_edge_set);
    }

    minipool_stack_node_t_free(&mp_stack_node_t, stack);
}

static inline stack_node_t* new_stack(yyStateNum state)
{
    stack_node_t* stack = newrefcounted(stack_node_t);
    stack->state = state;
    stack->preds = NULL;

    YYDPRINTF((stderr, "New stack [%p]\n", stack));

    return stack;
}

static inline char identical_payloads(payload_t *pd0, payload_t *pd1)
{
    if (pd0 == pd1)
        return 1;

    if ((pd0 == NULL) != (pd1 == NULL))
      return 0;

    if (payload_is_reduce(pd0)
            && payload_is_reduce(pd1))
    {
        if (pd0->r.rule != pd1->r.rule)
            return 0;

        payload_reduce_node_t *pn0 = pd0->r.values;
        payload_reduce_node_t *pn1 = pd1->r.values;

        while (pn0 != NULL && pn1 != NULL)
        {
            if (!identical_payloads(pn0->payload, pn1->payload))
                return 0;
            pn0 = pn0->next;
            pn1 = pn1->next;
        }
        if (pn0 != pn1)
            return 0;

        return 1;
    }
    else if (payload_is_shift(pd0)
            && payload_is_shift(pd1))
    {
        return pd0->s.yyposn == pd1->s.yyposn;
    }
    else
    {
        return 0;
    }
}

static inline void reduce_via_path(queue_item_t* qi, int token)
{
    YYDPRINTF((stderr, "Reducing stack #%d via path for rule r%d\n", stack_id(qi->stack), qi->rule - 1));
#if ]b4_api_PREFIX[DEBUG
    // if (yydebug)
    // {
    //     fprintf(stderr, "Path has length %d: ", qi->path.length);
    //     int j;
    //     for (j = 0; j < qi->path.length; j++)
    //     {
    //         stack_node_edge_t* edge = qi->path.edges[j];
    //         fprintf(stderr, "s%d [%p]<-", edge->target->state, edge->target);
    //     }
    //     fprintf(stderr, "[s%d, %p]", qi->stack->state, qi->stack);
    //     fprintf(stderr, "\n");
    // }
#endif

    stack_node_t* left_sibling = qi->stack;
    if (qi->path != NULL)
        left_sibling = qi->path->edge->target;

    YYDPRINTF((stderr, "Leftmost stack node in the path is in state s%d. Rule used %d\n", left_sibling->state, qi->rule));

    yyStateNum state = yyLRgotoState (left_sibling->state,
            yylhsNonterm (qi->rule));

    YYDPRINTF((stderr, "Goto state for stack #%d [%p] in state s%d [%p] using rule r%d is s%d\n", stack_id(qi->stack), qi->stack, left_sibling->state, left_sibling, qi->rule - 1, state));

    // Create a deferred payload
    payload_t *add_payload = new_payload(P_DEFERRED_REDUCE);
    add_payload->r.rule = qi->rule;

    payload_reduce_node_t *head = NULL;
    payload_reduce_node_t *tail = NULL;
    path_t *current_path = qi->path;
    for (; current_path != NULL; current_path = current_path->next)
    {
        payload_reduce_node_t *payload_reduce_node = minipool_payload_reduce_node_t_alloc(&mp_payload_reduce_node_t);
        payload_reduce_node->payload = incref(current_path->edge->payload);
        payload_reduce_node->next = NULL;

        if (head == NULL)
        {
            head = payload_reduce_node;
            tail = payload_reduce_node;
        }
        else
        {
            tail->next = payload_reduce_node;
            tail = payload_reduce_node;
        }
    }

    add_payload->r.values = head;

    if (yydebug)
    {
        YYDPRINTF((stderr, "New deferred payload:\n"));
        print_payload(add_payload, 1);
        YYDPRINTF((stderr, "\n"));
    }

    stack_node_t* right_sibling = gss_find_stack_node(state);
    if (right_sibling != NULL)
    {
        YYDPRINTF((stderr, "There is already the stack #%d [%p] in the state s%d\n", stack_id(right_sibling), right_sibling, state));
        // there is already a stack right_sibling with the goto state
        // of the current rule
        stack_node_edge_t* link = NULL;

        // look for a link from right_sibling to left_sibling
        stack_node_edge_set_t* edge_set = right_sibling->preds;
        while (edge_set != NULL)
        {
            if (edge_set->edge->target == left_sibling)
            {
                link = edge_set->edge;
                break;
            }
            edge_set = edge_set->next;
        }

        if (link != NULL)
        {
            YYDPRINTF((stderr, "There is already a link from the stack #%d [%p] to the current stack node\n", stack_id(right_sibling), right_sibling));
            // there is already a link from right_sibling to left_sibling

            // Update in place so this propagates to other stacks that are referring to this payload
            payload_t* payload_tail = link->payload;
            YYDPRINTF((stderr, "Payloads before merging:\n"));
            if (yydebug)
            {
                print_payload(link->payload, 1);
            }
            YYDPRINTF((stderr, "\n"));

            char repeated_payload = 0;
            while (payload_tail->next != NULL)
            {
                if (identical_payloads(add_payload, payload_tail))
                {
                    repeated_payload = 1;
                    break;
                }
                payload_tail = payload_tail->next;
            }
            if (!repeated_payload
                    && !identical_payloads(add_payload, payload_tail))
            {
                payload_tail->next = add_payload;

                YYDPRINTF((stderr, "Merged payloads:\n"));
                if (yydebug)
                {
                    print_payload(link->payload, 1);
                }
                YYDPRINTF((stderr, "\n"));

            }
            else
            {
                YYDPRINTF((stderr, "Not merging payload because it is repeated.\n"));
                decref(add_payload);
            }
        }
        else
        {
            YYDPRINTF((stderr, "There is NOT a link from the stack #%d [%p] to the current stack\n", stack_id(right_sibling), right_sibling));
            // FIXME:
            YYDPRINTF((stderr, "Adding the link\n"));
            link = stack_node_add_link(left_sibling, right_sibling, add_payload);

            YYDPRINTF((stderr, "Enqueueing reductions enabled by the new link\n"));
            enqueue_limited_reductions(link, token);
            YYDPRINTF((stderr, "Done\n"));
        }
    }
    else
    {
        YYDPRINTF((stderr, "There is NOT a stack already in state s%d\n", state));
        YYDPRINTF((stderr, "Creating new stack in state s%d\n", state));
        right_sibling = new_stack(state);

        YYDPRINTF((stderr, "Adding a link to the newly created stack\n"));

        /* stack_node_edge_t* link = */ stack_node_add_link(left_sibling, right_sibling, add_payload);

        YYDPRINTF((stderr, "Adding stack into set of stacks\n"));
        gss_add_stack(right_sibling);
    }
}

static inline void do_reductions(int token
        ]b4_user_formals[)
{
    YYDPRINTF((stderr, "Doing reductions\n"));
#if ]b4_api_PREFIX[DEBUG
    print_stacks();
#endif

    YYASSERT(path_queue_is_empty());

    while (gss->next == NULL)
    {
        YYDPRINTF((stderr, "Attempting deterministic reduction because there is only one stack.\n"));
        stack_node_t* current_stack = gss->stack;
        if (yydebug)
        {
            print_stack_rec(current_stack, 0);
        }

        char do_reduction = 0;
        int rule = 0;
        int len = 0;
        const short int* conflicts = NULL;
        if (yyisDefaultedState(current_stack->state))
        {
            rule = yydefaultAction(current_stack->state);
            if (rule != 0)
            {
                len = get_rule_length(rule);
                YYDPRINTF((stderr, "Stack #%d [%p] in state s%d has a default action with rule r%d, length is %d\n", stack_id(current_stack), current_stack, current_stack->state, rule - 1, len));
                do_reduction = 1;
            }
        }
        else
        {
            int action = 0;
            yygetLRActions(current_stack->state, token, &action, &conflicts);

            if (yyisShiftAction(action))
            {
                // Do nothing
            }
            else if (yyisErrorAction(action))
            {
                // Do nothing
            }
            else 
            {
                // Reduction
                rule = -action;
                len = get_rule_length(rule);
                do_reduction = (*conflicts == 0);

                YYDPRINTF((stderr, "Immediate action for stack #%d [%p] in state s%d is a reduce with rule r%d, length is %d. Conflicts? %s\n", stack_id(current_stack), current_stack, current_stack->state, rule - 1,
                            len,
                            *conflicts == 0 ? "no" : "yes"));
            }
        }

        if (do_reduction)
        {
            // Do a deterministic reduction.
            // FIXME - Encapsulate this in a function
            YYSTYPE yyval;
            ]b4_locations_if([YYLTYPE yyloc;])[

            YYSTYPE in_yyval[len + 1];
            ]b4_locations_if([
                    YYLTYPE in_yyloc@{len + 1@};
            ])[

            char deterministic_reduction_possible = 1;
            stack_node_t* popped_stack = current_stack;
            int i = len - 1;
            while (i >= 0)
            {
                if (popped_stack->preds->next != NULL)
                {
                    deterministic_reduction_possible = 0;
                    YYDPRINTF((stderr, "Deterministic reduction: not possible because stack [%p] in state s%d has more than one predecessor.\n\n", popped_stack, popped_stack->state));
                    break;
                }

                payload_t *current_payload = popped_stack->preds->edge->payload;

                evaluate_payload(current_payload]b4_user_args[);
                in_yyval[i] = get_yyval_of_payload(current_payload);
                ]b4_locations_if([in_yyloc@{i@} = get_yyloc_of_payload(current_payload);])[

                    popped_stack = popped_stack->preds->edge->target;
                i--;
            }

            if (!deterministic_reduction_possible)
                break;

            YYDPRINTF((stderr, "Deterministic reduction is possible using rule %d, length is %d\n", rule - 1, len));

            yyStateNum reduced_state = yyLRgotoState (popped_stack->state, yylhsNonterm(rule));
            YYDPRINTF((stderr, "Deterministic reduction: New state is s%d\n", reduced_state));
            YYDPRINTF((stderr, "Deterministic reduction: Leftmost stack node is in state s%d. Rule used %d\n", popped_stack->state, rule));

            stack_node_t* reduced_stack = new_stack(reduced_state);

            user_action(rule,
                    &yyval ]b4_locations_if([, &yyloc])[,
                    len, in_yyval ]b4_locations_if([, in_yyloc])[
                    ]b4_user_args[);

            payload_t *add_payload = new_payload(P_DEFINITIVE_REDUCE);
            add_payload->r.rule = rule;
            add_payload->r.yyval = yyval;
            add_payload->r.yyloc = yyloc;
            add_payload->r.values = NULL;

            /* stack_node_edge_t *link = */ stack_node_add_link(popped_stack, reduced_stack, add_payload);

            decref(current_stack);

            gss->stack = reduced_stack;

            YYDPRINTF((stderr, "Deterministic reduction finished\n"));
            if (yydebug)
            {
                print_stack_rec(gss->stack, 0);
            }
            YYDPRINTF((stderr, "\n"));
        }
        else if (conflicts == NULL || (*conflicts == 0))
        {
            YYDPRINTF((stderr, "Deterministic reduction: no more deterministic reductions are possible.\n\n"));
            // We are done
            return;
        }
        else
        {
            YYDPRINTF((stderr, "Deterministic reduction: not possible because of conflicting actions.\n\n"));
            // Move on to non-deterministic reduction.
            break;
        }
    }

    YYDPRINTF((stderr, "Non-deterministic reduction\n"));
    // int first_stack_reduced = 0;
    stack_node_set_t* final_it = NULL;
    for (;;)
    {
        stack_node_set_t* initial_gss = gss;

        stack_node_set_t *it = gss;

        while (it != final_it)
        {
            stack_node_t* current_stack = it->stack;
            YYDPRINTF((stderr, "Reducing stack [%p]. Currently in state %d\n", current_stack, current_stack->state));

            enqueue_reductions(current_stack, token);
            it = it->next;
        }

        YYDPRINTF((stderr, "\n"));

        while (!path_queue_is_empty())
        {
            queue_item_t* qi = path_queue_dequeue();

            reduce_via_path(qi, token);

            destroy_queue_item_t(qi);
        }

        YYASSERT(path_queue_is_empty());

        // No stack has been added by reduce_via_path
        if (initial_gss == gss)
        {
            YYDPRINTF((stderr, "No more stacks to reduce\n\n"));
            break;
        }
        else
        {
            YYDPRINTF((stderr, "There are more stacks to reduce\n\n"));
        }

        YYDPRINTF((stderr, "\n"));

#if ]b4_api_PREFIX[DEBUG
        {
            int num_stacks = 0;
            it = gss;
            while (it != final_it)
            {
                num_stacks++;
                it = it->next;
            }
            YYDPRINTF((stderr, "There are %d more stacks to potentially reduce\n", num_stacks));
        }
#endif
        final_it = initial_gss;
    }
}

static inline void do_shifts(int token,
        size_t yyposn,
        YYSTYPE *yyval
        ]b4_locations_if([, YYLTYPE *yyloc])[)
{
    YYDPRINTF((stderr, "Doing shifts\n"));

#if ]b4_api_PREFIX[DEBUG
    print_stacks();
#endif

    stack_node_set_t *old_gss = gss;
    // Clear gss
    gss = NULL;

    if (old_gss->next == NULL)
    {
        YYDPRINTF((stderr, "Simple shift\n"));
        stack_node_t* current_stack = old_gss->stack;

        int action = 0;
        const short int* conflicts;
        yygetLRActions(current_stack->state, token, &action, &conflicts);

        if (!yyisShiftAction(action))
        {
            YYDPRINTF((stderr, "Stack s%d [%p] does not have to shift, so it dies\n", current_stack->state, current_stack));
            decref(current_stack);
            minipool_stack_node_set_t_free(&mp_stack_node_set_t, old_gss);
        }
        else
        {
            int dest_state = action;

            stack_node_t* right_sibling = new_stack(dest_state);

            payload_t *payload = new_payload(P_SHIFT);
            payload->s.yyposn = yyposn;
            payload->s.yyval = *yyval;
            ]b4_locations_if([payload->s.yyloc = *yyloc;])[
                stack_node_add_link(current_stack, right_sibling, payload);
            decref(current_stack);

            old_gss->stack = right_sibling;
            gss = old_gss;
        }
    }
    else
    {
        YYDPRINTF((stderr, "Multi stack shift\n"));
        stack_node_set_t *it = old_gss;
        stack_node_set_t *prev = NULL;
        while (it != NULL)
        {
            stack_node_t* current_stack = it->stack;

            int action = 0;
            const short int* conflicts;
            yygetLRActions(current_stack->state, token, &action, &conflicts);

            if (yyisShiftAction(action))
            {
                prev = it;
                it = it->next;
            }
            else
            {
                stack_node_set_t* current_it = it;
                if (prev != NULL)
                {
                    prev->next = it->next;
                }
                else
                {
                    old_gss = it->next;
                }
                it = it->next;
                // Free dead stack
                decref(current_stack);
                // Free dead stack item
                minipool_stack_node_set_t_free(&mp_stack_node_set_t, current_it);
                YYDPRINTF((stderr, "Stack s%d [%p] does not have to shift, so it dies\n", current_stack->state, current_stack));
            }
        }

        it = old_gss;
        while (it != NULL)
        {
            stack_node_t* current_stack = it->stack;

            int action = 0;
            const short int* conflicts;
            yygetLRActions(current_stack->state, token, &action, &conflicts);

            // Only real shifts at this point
            YYASSERT(yyisShiftAction(action));

            int dest_state = action;
            YYDPRINTF((stderr, "Shifting stack [%p]. Currently in state s%d, New state is s%d\n", current_stack, current_stack->state, dest_state));

            stack_node_t* right_sibling = gss_find_stack_node(dest_state);
            if (right_sibling == NULL)
            {
                YYDPRINTF((stderr, "Adding new stack node in state s%d\n", dest_state));
                right_sibling = new_stack(dest_state);
                YYDPRINTF((stderr, "Adding newly created stack to set of stacks\n"));
                gss_add_stack(right_sibling);
            }
            else
            {
                YYDPRINTF((stderr, "Reusing existing stack node already in state s%d\n", dest_state));
            }

            payload_t *payload = new_payload(P_SHIFT);
            payload->s.yyposn = yyposn;
            payload->s.yyval = *yyval;
            ]b4_locations_if([payload->s.yyloc = *yyloc;])[
            stack_node_add_link(current_stack, right_sibling, payload);
            decref(current_stack);

            it = it->next;
        }

        // Free old stack set
        it = old_gss;
        while (it != NULL)
        {
            stack_node_set_t* current_it = it;
            it = it->next;
            minipool_stack_node_set_t_free(&mp_stack_node_set_t, current_it);
        }
    }
}

static inline YYSTYPE get_yyval_of_payload(payload_t* p)
{
    switch (p->kind)
    {
        case P_SHIFT:
            return p->s.yyval;
        case P_DEFINITIVE_REDUCE:
            return p->r.yyval;
        default:
            YYASSERT(yyfalse);
    }
}

static inline void set_yyval_of_payload(payload_t* p, YYSTYPE yyval)
{
    switch (p->kind)
    {
        case P_SHIFT:
            p->s.yyval = yyval;
            break;
        case P_DEFINITIVE_REDUCE:
            p->r.yyval = yyval;
            break;
        default:
            YYASSERT(yyfalse);
    }
}

]b4_locations_if([

static inline YYLTYPE get_yyloc_of_payload(payload_t* p)
{
    switch (p->kind)
    {
        case P_SHIFT:
            return p->s.yyloc;
        case P_DEFINITIVE_REDUCE:
            return p->r.yyloc;
        default:
            YYASSERT(yyfalse);
    }
}

])[

static inline void evaluate_single_payload(payload_t* d]b4_user_formals[)
{
    switch (d->kind)
    {
        case P_DEFERRED_REDUCE:
            {
                payload_reduce_node_t *pn = d->r.values;
                while (pn != NULL)
                {
                    evaluate_payload(pn->payload]b4_user_args[);
                    pn = pn->next;
                }

                int rule = d->r.rule;

                int len = get_rule_length(rule);

                YYSTYPE yyval;
                ]b4_locations_if([YYLTYPE yyloc;])[
                YYSTYPE in_yyval[len + 1];
                ]b4_locations_if([
                YYLTYPE in_yyloc@{len + 1@};
                ])[

                pn = d->r.values;
                int i = 0;
                while (pn != NULL)
                {
                   in_yyval[i] = get_yyval_of_payload(pn->payload);
                   ]b4_locations_if([in_yyloc@{i@} = get_yyloc_of_payload(pn->payload);])[
                   pn = pn->next;
                   i++;
                }

                user_action(rule,
                        &yyval ]b4_locations_if([, &yyloc])[,
                        len, in_yyval ]b4_locations_if([, in_yyloc])[
                        ]b4_user_args[);

                d->kind = P_DEFINITIVE_REDUCE;
                d->r.yyval = yyval;
                ]b4_locations_if([d->r.yyloc = yyloc;])[

                pn = d->r.values;
                while (pn != NULL)
                {
                    decref(pn->payload);
                    pn->payload = NULL;
                    pn = pn->next;
                }
                // d->r.values = NULL;

                break;
            }
        case P_SHIFT:
        case P_DEFINITIVE_REDUCE:
            break;
        default:
            YYASSERT(yyfalse);
    }
}

static inline void merge_payloads(int yyn, payload_t* p0, payload_t* p1)
{
  YYASSERT(p0->kind == P_SHIFT
          || p0->kind == P_DEFINITIVE_REDUCE);
  YYASSERT(p1->kind == P_SHIFT
          || p1->kind == P_DEFINITIVE_REDUCE);

  YYSTYPE yyval0 = get_yyval_of_payload(p0);
  YYSTYPE yyval1 = get_yyval_of_payload(p1);

  yyuserMerge(yyn, &yyval0, &yyval1);

  set_yyval_of_payload(p0, yyval0);
  set_yyval_of_payload(p1, yyval1);
}

static inline int get_rule_of_payload(payload_t* p)
{
  YYASSERT(p->kind == P_DEFERRED_REDUCE || p->kind == P_DEFINITIVE_REDUCE);

  return p->r.rule;
}

static inline int compare_rules(payload_t* pd0, payload_t* pd1)
{
  yyRuleNum r0 = get_rule_of_payload(pd0);
  yyRuleNum r1 = get_rule_of_payload(pd1);

  int p0 = yydprec[r0], p1 = yydprec[r1];

  if (p0 == p1)
    {
      if (yymerger[r0] == 0 || yymerger[r0] != yymerger[r1])
        return 0;
      else
        return 1;
    }
  if (p0 == 0 || p1 == 0)
    return 0;
  if (p0 < p1)
    return 3;
  if (p1 < p0)
    return 2;
  return 0;
}

static inline void evaluate_payload(payload_t* p]b4_user_formals[)
{
    YYASSERT(p != NULL);
    if (p->next != NULL)
    {
        // First check priority
        char need_to_merge = 0;

        payload_t* pd_best = p;
        payload_t* pd_current = pd_best->next;

        while (pd_current != NULL)
        {
            // YYASSERT(!identical_payloads(pd_current, pd_best));
            switch (compare_rules(pd_best, pd_current))
            {
                case 0:
                    YYASSERT(0 && "ambiguity");
                    break;
                case 1:
                    need_to_merge = 1;
                    break;
                case 2:
                    break;
                case 3:
                    pd_best = pd_current;
                    need_to_merge = 0;
                    break;
                default:
                    YYASSERT(0);
            }
            pd_current = pd_current->next;
        }

        if (need_to_merge)
        {
            int r = get_rule_of_payload(pd_best);
            int bestprec = yydprec[r];
            evaluate_single_payload(pd_best]b4_user_args[);

            for (pd_current = pd_best->next; pd_current != NULL; pd_current = pd_current->next)
            {
                r = get_rule_of_payload(pd_current);
                if (bestprec == yydprec[r])
                {
                    evaluate_single_payload(pd_current]b4_user_args[);
                    merge_payloads(yymerger[r], pd_best, pd_current);
                }
            }
        }
        else
        {
            evaluate_single_payload(pd_best]b4_user_args[);
        }

        // pd_best is the payload we want here, so propagate it to p
        if (p != pd_best)
        {
            p->kind = pd_best->kind;
            set_yyval_of_payload(p, get_yyval_of_payload(pd_best));
        }

        // Now make sure this payload represents a single semantic value.
        decref(p->next);
        p->next = NULL;
    }
    else
    {
        evaluate_single_payload(p]b4_user_args[);
    }
}

static void init_pools(void)
{
    minipool_stack_node_t_init(&mp_stack_node_t, 1024);
    minipool_stack_node_edge_t_init(&mp_stack_node_edge_t, 1024);
    minipool_stack_node_set_t_init(&mp_stack_node_set_t, 1024);

    minipool_payload_t_init(&mp_payload_t, 1024);
    minipool_payload_reduce_node_t_init(&mp_payload_reduce_node_t, 1024);

    minipool_stack_node_edge_set_t_init(&mp_stack_node_edge_set_t, 1024);

    minipool_queue_item_t_init(&mp_queue_item_t, 64);
    minipool_path_t_init(&mp_path_t, 64);
    minipool_path_queue_node_t_init(&mp_path_queue_node_t, 1024);
}

static void destroy_pools(void)
{
    minipool_stack_node_t_destroy(&mp_stack_node_t);
    minipool_stack_node_edge_t_destroy(&mp_stack_node_edge_t);
    minipool_stack_node_set_t_destroy(&mp_stack_node_set_t);

    minipool_payload_t_destroy(&mp_payload_t);
    minipool_payload_reduce_node_t_destroy(&mp_payload_reduce_node_t);

    minipool_stack_node_edge_set_t_destroy(&mp_stack_node_edge_set_t);

    minipool_queue_item_t_destroy(&mp_queue_item_t);
    minipool_path_t_destroy(&mp_path_t);
    minipool_path_queue_node_t_destroy(&mp_path_queue_node_t);
}

static inline void report_syntax_error(int token]b4_user_formals[)
{
#if ! YYERROR_VERBOSE
  yyerror (]b4_lyyerror_args[YY_("syntax error"));
#else
    const char *token_desc = yytokenName(token);

    size_t length_token_name = yytnamerr(YY_NULLPTR, token_desc);
    char *token_name = YYMALLOC((length_token_name + 1) * sizeof(*token_name));
    yytnamerr(token_name, token_desc);
    token_name[length_token_name] = '\0';

    const char msg_pattern[] = "syntax error, unexpected ";
    int total_chars = strlen(msg_pattern) + strlen(token_name) + 1;
    char *message = YYMALLOC(total_chars * sizeof(char));
    snprintf(message, total_chars, "%s%s", msg_pattern, token_name);

    yyerror (]b4_lyyerror_args[message);

    YYFREE(message);
#endif /* YYERROR_VERBOSE */
  yynerrs += 1;
}

]b4_function_define([yyparse], [int], b4_parse_param)[
{
    // Initialize GSS
    gss_init();

    init_pools();

    path_queue_init();
    stack_node_t* initial_stack = new_stack(0);
    gss_add_stack(initial_stack);

    size_t yyposn = 0;
    yychar = YYEMPTY;
    yylval = yyval_default;]b4_locations_if([
    yylloc = yyloc_default;])[
]m4_ifdef([b4_initial_action], [
b4_dollar_pushdef([yylval], [], [yylloc])dnl
  /* User initialization code.  */
  b4_user_initial_action
b4_dollar_popdef])[]dnl
[
    for (;;)
    {
        // Final state
        if (gss != NULL && gss->next == NULL
                && gss->stack->state == YYFINAL)
        {
            YYDPRINTF ((stderr, "Stack #0 [%p] in accepting state. Exiting\n", gss->stack));
            break;
        }

        yychar = ]b4_lex[;

        yySymbol yytoken;
        if (yychar <= YYEOF)
        {
            yychar = yytoken = YYEOF;
            YYDPRINTF ((stderr, "Now at end of input.\n"));
        }
        else
        {
            yytoken = YYTRANSLATE (yychar);
            YYDPRINTF((stderr, "----------------------------------------\n"));
            YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
            YYDPRINTF((stderr, "----------------------------------------\n"));
        }

        do_reductions(yytoken]b4_user_args[);
        do_shifts(yytoken, yyposn, &yylval]b4_locations_if([, &yylloc])[);
        yyposn++;

        if (gss == NULL)
        {
            YYDPRINTF((stderr, "No stack is alive, leaving\n"));
            report_syntax_error(yytoken]b4_user_args[);
            break;
        }

        YYDPRINTF((stderr, "**************************************************************\n"));
        YYDPRINTF((stderr, "**************************************************************\n"));
    }

#if ]b4_api_PREFIX[DEBUG
    YYDPRINTF((stderr, "Final stacks\n"));
    print_stacks();
#endif

    int yyresult;

    if (gss != NULL && gss->next == NULL
            && gss->stack->state == YYFINAL)
    {
        if (gss->stack->preds != NULL)
            evaluate_payload(gss->stack->preds->edge->payload]b4_user_args[);
        yyresult = 0;
    }
    else
    {
        yyresult = 1;
    }

    path_queue_destroy();
    gss_destroy();

    // Destroy pools
    destroy_pools();

    return yyresult;

}

/* DEBUGGING ONLY */
#if ]b4_api_PREFIX[DEBUG
static void
yy_yypstack (yyGLRState* yys)
{
  if (yys->yypred)
    {
      yy_yypstack (yys->yypred);
      YYFPRINTF (stderr, " -> ");
    }
  YYFPRINTF (stderr, "%d@@%lu", yys->yylrState,
             (unsigned long int) yys->yyposn);
}

static void
yypstates (yyGLRState* yyst)
{
  if (yyst == YY_NULLPTR)
    YYFPRINTF (stderr, "<null>");
  else
    yy_yypstack (yyst);
  YYFPRINTF (stderr, "\n");
}

static void
yypstack (yyGLRStack* yystackp, size_t yyk)
{
  yypstates (yystackp->yytops.yystates[yyk]);
}

#define YYINDEX(YYX)                                                         \
    ((YYX) == YY_NULLPTR ? -1 : (yyGLRStackItem*) (YYX) - yystackp->yyitems)


static void
yypdumpstack (yyGLRStack* yystackp)
{
  yyGLRStackItem* yyp;
  size_t yyi;
  for (yyp = yystackp->yyitems; yyp < yystackp->yynextFree; yyp += 1)
    {
      YYFPRINTF (stderr, "%3lu. ",
                 (unsigned long int) (yyp - yystackp->yyitems));
      if (*(yybool *) yyp)
        {
          YYASSERT (yyp->yystate.yyisState);
          YYASSERT (yyp->yyoption.yyisState);
          YYFPRINTF (stderr, "Res: %d, LR State: %d, posn: %lu, pred: %ld",
                     yyp->yystate.yyresolved, yyp->yystate.yylrState,
                     (unsigned long int) yyp->yystate.yyposn,
                     (long int) YYINDEX (yyp->yystate.yypred));
          if (! yyp->yystate.yyresolved)
            YYFPRINTF (stderr, ", firstVal: %ld",
                       (long int) YYINDEX (yyp->yystate
                                             .yysemantics.yyfirstVal));
        }
      else
        {
          YYASSERT (!yyp->yystate.yyisState);
          YYASSERT (!yyp->yyoption.yyisState);
          YYFPRINTF (stderr, "Option. rule: %d, state: %ld, next: %ld",
                     yyp->yyoption.yyrule - 1,
                     (long int) YYINDEX (yyp->yyoption.yystate),
                     (long int) YYINDEX (yyp->yyoption.yynext));
        }
      YYFPRINTF (stderr, "\n");
    }
  YYFPRINTF (stderr, "Tops:");
  for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
    YYFPRINTF (stderr, "%lu: %ld; ", (unsigned long int) yyi,
               (long int) YYINDEX (yystackp->yytops.yystates[yyi]));
  YYFPRINTF (stderr, "\n");
}
#endif

#undef yylval
#undef yychar
#undef yynerrs]b4_locations_if([
#undef yylloc])

m4_if(b4_prefix, [yy], [],
[[/* Substitute the variable and function names.  */
#define yyparse ]b4_prefix[parse
#define yylex   ]b4_prefix[lex
#define yyerror ]b4_prefix[error
#define yylval  ]b4_prefix[lval
#define yychar  ]b4_prefix[char
#define yydebug ]b4_prefix[debug
#define yynerrs ]b4_prefix[nerrs]b4_locations_if([[
#define yylloc  ]b4_prefix[lloc]])])[

]b4_epilogue[]dnl
b4_output_end()
