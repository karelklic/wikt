
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++
   
      Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008 Free Software
   Foundation, Inc.
   
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


/* First part of user declarations.  */

/* Line 311 of lalr1.cc  */
#line 9 "exprparser.ypp"

#include <math.h>
#include "exprdriver.h"

#define yylex exprlex


/* Line 311 of lalr1.cc  */
#line 49 "exprparser.tab.cpp"


#include "exprparser.tab.hpp"

/* User implementation prologue.  */

/* Line 317 of lalr1.cc  */
#line 27 "exprparser.ypp"

yy::ExprParser::token_type exprlex(yy::ExprParser::semantic_type* yylval,
        yy::ExprParser::location_type* /*yylloc*/, ExprDriver& /*driver*/);


/* Line 317 of lalr1.cc  */
#line 64 "exprparser.tab.cpp"

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE(e) ((void) (e))

/* Enable debugging if requested.  */
#if YYDEBUG

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)	\
do {							\
  if (yydebug_)						\
    {							\
      *yycdebug_ << Title << ' ';			\
      yy_symbol_print_ ((Type), (Value), (Location));	\
      *yycdebug_ << std::endl;				\
    }							\
} while (false)

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug_)				\
    yy_reduce_print_ (Rule);		\
} while (false)

# define YY_STACK_PRINT()		\
do {					\
  if (yydebug_)				\
    yystack_print_ ();			\
} while (false)

#else /* !YYDEBUG */

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_REDUCE_PRINT(Rule)
# define YY_STACK_PRINT()

#endif /* !YYDEBUG */

#define yyerrok		(yyerrstatus_ = 0)
#define yyclearin	(yychar = yyempty_)

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


/* Line 380 of lalr1.cc  */
#line 1 "[Bison:b4_percent_define_default]"

namespace yy {

/* Line 380 of lalr1.cc  */
#line 133 "exprparser.tab.cpp"
#if YYERROR_VERBOSE

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  ExprParser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
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
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

#endif

  /// Build a parser object.
  ExprParser::ExprParser (ExprDriver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {
  }

  ExprParser::~ExprParser ()
  {
  }

#if YYDEBUG
  /*--------------------------------.
  | Print this symbol on YYOUTPUT.  |
  `--------------------------------*/

  inline void
  ExprParser::yy_symbol_value_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yyvaluep);
    switch (yytype)
      {
         default:
	  break;
      }
  }


  void
  ExprParser::yy_symbol_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    *yycdebug_ << (yytype < yyntokens_ ? "token" : "nterm")
	       << ' ' << yytname_[yytype] << " ("
	       << *yylocationp << ": ";
    yy_symbol_value_print_ (yytype, yyvaluep, yylocationp);
    *yycdebug_ << ')';
  }
#endif

  void
  ExprParser::yydestruct_ (const char* yymsg,
			   int yytype, semantic_type* yyvaluep, location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yymsg);
    YYUSE (yyvaluep);

    YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
      {
  
	default:
	  break;
      }
  }

  void
  ExprParser::yypop_ (unsigned int n)
  {
    yystate_stack_.pop (n);
    yysemantic_stack_.pop (n);
    yylocation_stack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  ExprParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  ExprParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  ExprParser::debug_level_type
  ExprParser::debug_level () const
  {
    return yydebug_;
  }

  void
  ExprParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif

  int
  ExprParser::parse ()
  {
    /// Lookahead and lookahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    /* State.  */
    int yyn;
    int yylen = 0;
    int yystate = 0;

    /* Error handling.  */
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the lookahead.
    semantic_type yylval;
    /// Location of the lookahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location_type yyerror_range[2];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stacks.  The initial state will be pushed in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystate_stack_ = state_stack_type (0);
    yysemantic_stack_ = semantic_stack_type (0);
    yylocation_stack_ = location_stack_type (0);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* New state.  */
  yynewstate:
    yystate_stack_.push (yystate);
    YYCDEBUG << "Entering state " << yystate << std::endl;

    /* Accept?  */
    if (yystate == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without lookahead.  */
    yyn = yypact_[yystate];
    if (yyn == yypact_ninf_)
      goto yydefault;

    /* Read a lookahead token.  */
    if (yychar == yyempty_)
      {
	YYCDEBUG << "Reading a token: ";
	yychar = yylex (&yylval, &yylloc, driver);
      }


    /* Convert token to internal form.  */
    if (yychar <= yyeof_)
      {
	yychar = yytoken = yyeof_;
	YYCDEBUG << "Now at end of input." << std::endl;
      }
    else
      {
	yytoken = yytranslate_ (yychar);
	YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
      }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yytoken)
      goto yydefault;

    /* Reduce or error.  */
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
	if (yyn == 0 || yyn == yytable_ninf_)
	goto yyerrlab;
	yyn = -yyn;
	goto yyreduce;
      }

    /* Shift the lookahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the token being shifted.  */
    yychar = yyempty_;

    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus_)
      --yyerrstatus_;

    yystate = yyn;
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystate];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yyval = yysemantic_stack_[yylen - 1];
    else
      yyval = yysemantic_stack_[0];

    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }
    YY_REDUCE_PRINT (yyn);
    switch (yyn)
      {
	  case 2:

/* Line 678 of lalr1.cc  */
#line 51 "exprparser.ypp"
    { (yyval.num) = (yysemantic_stack_[(2) - (1)].num); driver.setResult((yysemantic_stack_[(2) - (1)].num)); }
    break;

  case 3:

/* Line 678 of lalr1.cc  */
#line 53 "exprparser.ypp"
    { (yyval.num) = (yysemantic_stack_[(1) - (1)].num);          }
    break;

  case 4:

/* Line 678 of lalr1.cc  */
#line 54 "exprparser.ypp"
    { (yyval.num) = (yysemantic_stack_[(3) - (1)].num) + (yysemantic_stack_[(3) - (3)].num);     }
    break;

  case 5:

/* Line 678 of lalr1.cc  */
#line 55 "exprparser.ypp"
    { (yyval.num) = (yysemantic_stack_[(3) - (1)].num) - (yysemantic_stack_[(3) - (3)].num);     }
    break;

  case 6:

/* Line 678 of lalr1.cc  */
#line 56 "exprparser.ypp"
    { (yyval.num) = -(yysemantic_stack_[(2) - (2)].num);         }
    break;

  case 7:

/* Line 678 of lalr1.cc  */
#line 57 "exprparser.ypp"
    { (yyval.num) = (yysemantic_stack_[(2) - (2)].num);          }
    break;

  case 8:

/* Line 678 of lalr1.cc  */
#line 58 "exprparser.ypp"
    { (yyval.num) = ((yysemantic_stack_[(3) - (1)].num) < (yysemantic_stack_[(3) - (3)].num) ? 1 : 0); }
    break;

  case 9:

/* Line 678 of lalr1.cc  */
#line 59 "exprparser.ypp"
    { (yyval.num) = ((yysemantic_stack_[(3) - (1)].num) > (yysemantic_stack_[(3) - (3)].num) ? 1 : 0); }
    break;

  case 10:

/* Line 678 of lalr1.cc  */
#line 60 "exprparser.ypp"
    { (yyval.num) = ((yysemantic_stack_[(3) - (1)].num) <= (yysemantic_stack_[(3) - (3)].num) ? 1 : 0); }
    break;

  case 11:

/* Line 678 of lalr1.cc  */
#line 61 "exprparser.ypp"
    { (yyval.num) = ((yysemantic_stack_[(3) - (1)].num) >= (yysemantic_stack_[(3) - (3)].num) ? 1 : 0); }
    break;

  case 12:

/* Line 678 of lalr1.cc  */
#line 62 "exprparser.ypp"
    { (yyval.num) = (yysemantic_stack_[(3) - (1)].num) * (yysemantic_stack_[(3) - (3)].num); }
    break;

  case 13:

/* Line 678 of lalr1.cc  */
#line 63 "exprparser.ypp"
    { (yyval.num) = (yysemantic_stack_[(3) - (1)].num) / (yysemantic_stack_[(3) - (3)].num); }
    break;

  case 14:

/* Line 678 of lalr1.cc  */
#line 64 "exprparser.ypp"
    { (yyval.num) = (yysemantic_stack_[(3) - (2)].num); }
    break;

  case 15:

/* Line 678 of lalr1.cc  */
#line 65 "exprparser.ypp"
    { double i = pow(10, (yysemantic_stack_[(3) - (3)].num)); (yyval.num) = round((yysemantic_stack_[(3) - (1)].num) * i) / i; }
    break;

  case 16:

/* Line 678 of lalr1.cc  */
#line 66 "exprparser.ypp"
    { (yyval.num) = pow((yysemantic_stack_[(3) - (1)].num), (yysemantic_stack_[(3) - (3)].num)); }
    break;

  case 17:

/* Line 678 of lalr1.cc  */
#line 67 "exprparser.ypp"
    { (yyval.num) = (int)(yysemantic_stack_[(3) - (1)].num) % (int)(yysemantic_stack_[(3) - (3)].num); }
    break;

  case 18:

/* Line 678 of lalr1.cc  */
#line 68 "exprparser.ypp"
    { (yyval.num) = ((yysemantic_stack_[(3) - (1)].num) == (yysemantic_stack_[(3) - (3)].num) ? 1 : 0); }
    break;

  case 19:

/* Line 678 of lalr1.cc  */
#line 69 "exprparser.ypp"
    { (yyval.num) = ((yysemantic_stack_[(3) - (1)].num) != (yysemantic_stack_[(3) - (3)].num) ? 1 : 0); }
    break;

  case 20:

/* Line 678 of lalr1.cc  */
#line 70 "exprparser.ypp"
    { (yyval.num) = ((yysemantic_stack_[(3) - (1)].num) && (yysemantic_stack_[(3) - (3)].num) ? 1 : 0); }
    break;

  case 21:

/* Line 678 of lalr1.cc  */
#line 71 "exprparser.ypp"
    { (yyval.num) = ((yysemantic_stack_[(3) - (1)].num) || (yysemantic_stack_[(3) - (3)].num) ? 1 : 0); }
    break;

  case 22:

/* Line 678 of lalr1.cc  */
#line 72 "exprparser.ypp"
    { (yyval.num) = ((yysemantic_stack_[(2) - (2)].num) ? 0 : 1); }
    break;

  case 23:

/* Line 678 of lalr1.cc  */
#line 73 "exprparser.ypp"
    { (yyval.num) = ceil((yysemantic_stack_[(2) - (2)].num)); }
    break;

  case 24:

/* Line 678 of lalr1.cc  */
#line 74 "exprparser.ypp"
    { (yyval.num) = floor((yysemantic_stack_[(2) - (2)].num)); }
    break;

  case 25:

/* Line 678 of lalr1.cc  */
#line 75 "exprparser.ypp"
    { (yyval.num) = ((yysemantic_stack_[(2) - (2)].num) > 0 ? (yysemantic_stack_[(2) - (2)].num) : -(yysemantic_stack_[(2) - (2)].num)); }
    break;

  case 26:

/* Line 678 of lalr1.cc  */
#line 76 "exprparser.ypp"
    { (yyval.num) = log((yysemantic_stack_[(2) - (2)].num)); }
    break;

  case 27:

/* Line 678 of lalr1.cc  */
#line 77 "exprparser.ypp"
    { (yyval.num) = trunc((yysemantic_stack_[(2) - (2)].num)); }
    break;

  case 28:

/* Line 678 of lalr1.cc  */
#line 78 "exprparser.ypp"
    { (yyval.num) = exp((yysemantic_stack_[(2) - (2)].num)); }
    break;

  case 29:

/* Line 678 of lalr1.cc  */
#line 79 "exprparser.ypp"
    { (yyval.num) = sin((yysemantic_stack_[(2) - (2)].num)); }
    break;

  case 30:

/* Line 678 of lalr1.cc  */
#line 80 "exprparser.ypp"
    { (yyval.num) = cos((yysemantic_stack_[(2) - (2)].num)); }
    break;

  case 31:

/* Line 678 of lalr1.cc  */
#line 81 "exprparser.ypp"
    { (yyval.num) = tan((yysemantic_stack_[(2) - (2)].num)); }
    break;

  case 32:

/* Line 678 of lalr1.cc  */
#line 82 "exprparser.ypp"
    { (yyval.num) = asin((yysemantic_stack_[(2) - (2)].num)); }
    break;

  case 33:

/* Line 678 of lalr1.cc  */
#line 83 "exprparser.ypp"
    { (yyval.num) = acos((yysemantic_stack_[(2) - (2)].num)); }
    break;

  case 34:

/* Line 678 of lalr1.cc  */
#line 84 "exprparser.ypp"
    { (yyval.num) = atan((yysemantic_stack_[(2) - (2)].num)); }
    break;

  case 35:

/* Line 678 of lalr1.cc  */
#line 85 "exprparser.ypp"
    { (yyval.num) = 3.1415926535898; }
    break;

  case 36:

/* Line 678 of lalr1.cc  */
#line 86 "exprparser.ypp"
    { (yyval.num) = 2.718281828459; }
    break;



/* Line 678 of lalr1.cc  */
#line 669 "exprparser.tab.cpp"
	default:
          break;
      }
    YY_SYMBOL_PRINT ("-> $$ =", yyr1_[yyn], &yyval, &yyloc);

    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    yysemantic_stack_.push (yyval);
    yylocation_stack_.push (yyloc);

    /* Shift the result of the reduction.  */
    yyn = yyr1_[yyn];
    yystate = yypgoto_[yyn - yyntokens_] + yystate_stack_[0];
    if (0 <= yystate && yystate <= yylast_
	&& yycheck_[yystate] == yystate_stack_[0])
      yystate = yytable_[yystate];
    else
      yystate = yydefgoto_[yyn - yyntokens_];
    goto yynewstate;

  /*------------------------------------.
  | yyerrlab -- here on detecting error |
  `------------------------------------*/
  yyerrlab:
    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	error (yylloc, yysyntax_error_ (yystate, yytoken));
      }

    yyerror_range[0] = yylloc;
    if (yyerrstatus_ == 3)
      {
	/* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

	if (yychar <= yyeof_)
	  {
	  /* Return failure if at end of input.  */
	  if (yychar == yyeof_)
	    YYABORT;
	  }
	else
	  {
	    yydestruct_ ("Error: discarding", yytoken, &yylval, &yylloc);
	    yychar = yyempty_;
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
    if (false)
      goto yyerrorlab;

    yyerror_range[0] = yylocation_stack_[yylen - 1];
    /* Do not reclaim the symbols of the rule which action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    yystate = yystate_stack_[0];
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;	/* Each real token shifted decrements this.  */

    for (;;)
      {
	yyn = yypact_[yystate];
	if (yyn != yypact_ninf_)
	{
	  yyn += yyterror_;
	  if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
	    {
	      yyn = yytable_[yyn];
	      if (0 < yyn)
		break;
	    }
	}

	/* Pop the current state because it cannot handle the error token.  */
	if (yystate_stack_.height () == 1)
	YYABORT;

	yyerror_range[0] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    yyerror_range[1] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the lookahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yyloc);

    /* Shift the error token.  */
    YY_SYMBOL_PRINT ("Shifting", yystos_[yyn],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);

    yystate = yyn;
    goto yynewstate;

    /* Accept.  */
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    /* Abort.  */
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (yychar != yyempty_)
      yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval, &yylloc);

    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (yystate_stack_.height () != 1)
      {
	yydestruct_ ("Cleanup: popping",
		   yystos_[yystate_stack_[0]],
		   &yysemantic_stack_[0],
		   &yylocation_stack_[0]);
	yypop_ ();
      }

    return yyresult;
  }

  // Generate an error message.
  std::string
  ExprParser::yysyntax_error_ (int yystate, int tok)
  {
    std::string res;
    YYUSE (yystate);
#if YYERROR_VERBOSE
    int yyn = yypact_[yystate];
    if (yypact_ninf_ < yyn && yyn <= yylast_)
      {
	/* Start YYX at -YYN if negative to avoid negative indexes in
	   YYCHECK.  */
	int yyxbegin = yyn < 0 ? -yyn : 0;

	/* Stay within bounds of both yycheck and yytname.  */
	int yychecklim = yylast_ - yyn + 1;
	int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
	int count = 0;
	for (int x = yyxbegin; x < yyxend; ++x)
	  if (yycheck_[x + yyn] == x && x != yyterror_)
	    ++count;

	// FIXME: This method of building the message is not compatible
	// with internationalization.  It should work like yacc.c does it.
	// That is, first build a string that looks like this:
	// "syntax error, unexpected %s or %s or %s"
	// Then, invoke YY_ on this string.
	// Finally, use the string as a format to output
	// yytname_[tok], etc.
	// Until this gets fixed, this message appears in English only.
	res = "syntax error, unexpected ";
	res += yytnamerr_ (yytname_[tok]);
	if (count < 5)
	  {
	    count = 0;
	    for (int x = yyxbegin; x < yyxend; ++x)
	      if (yycheck_[x + yyn] == x && x != yyterror_)
		{
		  res += (!count++) ? ", expecting " : " or ";
		  res += yytnamerr_ (yytname_[x]);
		}
	  }
      }
    else
#endif
      res = YY_("syntax error");
    return res;
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const signed char ExprParser::yypact_ninf_ = -21;
  const signed char
  ExprParser::yypact_[] =
  {
        50,   -21,    50,   -21,   -21,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
       1,    86,    13,   -21,   -21,   -21,   -21,   -21,   -21,   -21,
     -21,   -21,   -21,   -21,   -21,   -21,   -21,   -21,   -21,   -21,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,   -21,    99,    99,    42,    42,
      42,    42,    42,    42,    70,   103,   103,   -20,   -20,   -20,
     -20
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  ExprParser::yydefact_[] =
  {
         0,     3,     0,    36,    35,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     7,     6,    34,    32,    33,    31,    30,
      29,    26,    25,    28,    24,    27,    23,    22,     1,     2,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    14,    20,    21,    11,    10,
       8,     9,    19,    18,    15,     4,     5,    17,    13,    12,
      16
  };

  /* YYPGOTO[NTERM-NUM].  */
  const signed char
  ExprParser::yypgoto_[] =
  {
       -21,   -21,    -2
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const signed char
  ExprParser::yydefgoto_[] =
  {
        -1,    20,    21
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char ExprParser::yytable_ninf_ = -1;
  const unsigned char
  ExprParser::yytable_[] =
  {
        22,    38,    54,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    55,     0,
       0,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,     0,     0,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,     1,     2,     0,     3,     4,    48,    49,
      50,    51,    52,    53,    54,     0,     0,     5,     6,     0,
       0,     0,     0,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    39,    49,    50,    51,
      52,    53,    54,     0,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    51,    52,    53,    54
  };

  /* YYCHECK.  */
  const signed char
  ExprParser::yycheck_[] =
  {
         2,     0,    22,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     5,    -1,
      -1,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    -1,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,     3,     4,    -1,     6,     7,    16,    17,
      18,    19,    20,    21,    22,    -1,    -1,    17,    18,    -1,
      -1,    -1,    -1,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,     0,    17,    18,    19,
      20,    21,    22,    -1,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    19,    20,    21,    22
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  ExprParser::yystos_[] =
  {
         0,     3,     4,     6,     7,    17,    18,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      39,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,     0,     0,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,     5,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  ExprParser::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  ExprParser::yyr1_[] =
  {
         0,    38,    39,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  ExprParser::yyr2_[] =
  {
         0,     2,     2,     1,     3,     3,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     1,     1
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const ExprParser::yytname_[] =
  {
    "\"end of file\"", "error", "$undefined", "NUM", "LEFT_PAREN",
  "RIGHT_PAREN", "E", "PI", "AND", "OR", "LARGER_EQUAL", "LESSER_EQUAL",
  "LESSER", "LARGER", "NEQUALS", "EQUALS", "ROUND", "PLUS", "MINUS", "MOD",
  "DIVIDE", "MULTIPLY", "POW", "ATAN", "ASIN", "ACOS", "TAN", "COS", "SIN",
  "LN", "ABS", "EXP", "FLOOR", "TRUNC", "CEIL", "NOT", "POS", "NEG",
  "$accept", "input", "exp", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const ExprParser::rhs_number_type
  ExprParser::yyrhs_[] =
  {
        39,     0,    -1,    40,     0,    -1,     3,    -1,    40,    17,
      40,    -1,    40,    18,    40,    -1,    18,    40,    -1,    17,
      40,    -1,    40,    12,    40,    -1,    40,    13,    40,    -1,
      40,    11,    40,    -1,    40,    10,    40,    -1,    40,    21,
      40,    -1,    40,    20,    40,    -1,     4,    40,     5,    -1,
      40,    16,    40,    -1,    40,    22,    40,    -1,    40,    19,
      40,    -1,    40,    15,    40,    -1,    40,    14,    40,    -1,
      40,     8,    40,    -1,    40,     9,    40,    -1,    35,    40,
      -1,    34,    40,    -1,    32,    40,    -1,    30,    40,    -1,
      29,    40,    -1,    33,    40,    -1,    31,    40,    -1,    28,
      40,    -1,    27,    40,    -1,    26,    40,    -1,    24,    40,
      -1,    25,    40,    -1,    23,    40,    -1,     7,    -1,     6,
      -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned char
  ExprParser::yyprhs_[] =
  {
         0,     0,     3,     6,     8,    12,    16,    19,    22,    26,
      30,    34,    38,    42,    46,    50,    54,    58,    62,    66,
      70,    74,    78,    81,    84,    87,    90,    93,    96,    99,
     102,   105,   108,   111,   114,   117,   119
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned char
  ExprParser::yyrline_[] =
  {
         0,    51,    51,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86
  };

  // Print the state stack on the debug stream.
  void
  ExprParser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (state_stack_type::const_iterator i = yystate_stack_.begin ();
	 i != yystate_stack_.end (); ++i)
      *yycdebug_ << ' ' << *i;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  ExprParser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    /* Print the symbols being reduced, and their result.  */
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
	       << " (line " << yylno << "):" << std::endl;
    /* The symbols being reduced.  */
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
		       yyrhs_[yyprhs_[yyrule] + yyi],
		       &(yysemantic_stack_[(yynrhs) - (yyi + 1)]),
		       &(yylocation_stack_[(yynrhs) - (yyi + 1)]));
  }
#endif // YYDEBUG

  /* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
  ExprParser::token_number_type
  ExprParser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
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
      35,    36,    37
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int ExprParser::yyeof_ = 0;
  const int ExprParser::yylast_ = 125;
  const int ExprParser::yynnts_ = 3;
  const int ExprParser::yyempty_ = -2;
  const int ExprParser::yyfinal_ = 38;
  const int ExprParser::yyterror_ = 1;
  const int ExprParser::yyerrcode_ = 256;
  const int ExprParser::yyntokens_ = 38;

  const unsigned int ExprParser::yyuser_token_number_max_ = 292;
  const ExprParser::token_number_type ExprParser::yyundef_token_ = 2;


/* Line 1054 of lalr1.cc  */
#line 1 "[Bison:b4_percent_define_default]"

} // yy

/* Line 1054 of lalr1.cc  */
#line 1156 "exprparser.tab.cpp"


/* Line 1056 of lalr1.cc  */
#line 89 "exprparser.ypp"

void yy::ExprParser::error(const yy::ExprParser::location_type& l, const std::string& m)
{
  driver.error(l, m);
}

