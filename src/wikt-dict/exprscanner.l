%{
/* This is the the input file for flex.
 * This source file is licensed unter the GNU General Public License
 * http://www.gnu.org/copyleft/gpl.html
 */

#include <stdio.h>
#include <string.h>
#include <sstream>

#include "exprdriver.h"
#include "exprparser.tab.hpp"

// Announce to Flex the prototype we want for lexing function, ...
#define YY_DECL yy::ExprParser::token_type exprlex( \
        yy::ExprParser::semantic_type* yylval,    \
        yy::ExprParser::location_type* /*yylloc*/,    \
        ExprDriver& /*driver*/)
        
/* By default yylex returns int, we use token_type.
   Unfortunately yyterminate by default returns 0, which is
   not of token_type.  */
#define yyterminate() return token::END
%}

%option noyywrap nounput batch debug
%option prefix="expr"

%{
  typedef yy::ExprParser::token token;
%}

%%
[0-9]+\.[0-9]*([eE][\+\-]?[0-9]+)? { /* trailing decimal point is allowed */
           /* atof can *not* be used, because it is locale-sensitive */
           std::stringstream ss;
           ss.imbue(std::locale("C"));
           ss << yytext;
           ss >> yylval->num;
           return token::NUM;   
         }

[0-9]*\.[0-9]+([eE][\+\-]?[0-9]+)? { /* trailing decimal point is allowed */
           /* atof can *not* be used, because it is locale-sensitive */
           std::stringstream ss;
           ss.imbue(std::locale("C"));
           ss << yytext;
           ss >> yylval->num;
           return token::NUM;   
         }
         
[0-9]+([eE][\+\-]?[0-9]+)? {
           /* atof can *not* be used, because it is locale-sensitive */
           std::stringstream ss;
           ss.imbue(std::locale("C"));
           ss << yytext;
           ss >> yylval->num;
           return token::NUM; 
         } 
         
\+       { return token::PLUS; }
\-       { return token::MINUS; }
\<=      { return token::LESSER_EQUAL; }
\<       { return token::LESSER; }
\>=      { return token::LARGER_EQUAL; }
\>       { return token::LARGER; } 
\*       { return token::MULTIPLY; }
\/       { return token::DIVIDE; }
div      { return token::DIVIDE; }
\(       { return token::LEFT_PAREN; }
\)       { return token::RIGHT_PAREN; }
mod      { return token::MOD; }
round    { return token::ROUND; }
\^       { return token::POW; }
=        { return token::EQUALS; }
\!=      { return token::NEQUALS; }
\<\>     { return token::NEQUALS; }
and      { return token::AND; }
or       { return token::OR; }
not      { return token::NOT; }
ceil     { return token::CEIL; }
abs      { return token::ABS; }
floor    { return token::FLOOR; }
ln       { return token::LN; }
trunc    { return token::TRUNC; }
sin      { return token::SIN; }
cos      { return token::COS; }
tan      { return token::TAN; }
asin     { return token::ASIN; }
acos     { return token::ACOS; }
atan     { return token::ATAN; }
 /* Double x in exxp is used because of unicode string is encoded with the use of 
    x as escape character. User writes #expr:exp1.2, but the expression scanner receives 
    exxp1.2. */
exxp     { return token::EXP; } 
e        { return token::E; }
pi       { return token::PI; }

[ \t\n]

.        yyterminate();

%%
void ExprDriver::scan_begin()
{
 expr_flex_debug = 0;
 expr_scan_string(_input.c_str());
}

void ExprDriver::scan_end()
{
}
