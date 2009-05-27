%{
/* This is the the input file for flex.
 * This source file is licensed unter the GNU General Public License
 * http://www.gnu.org/copyleft/gpl.html
 */

#include <stdio.h>
#include <string.h>
#include <sstream>

#include "ExprDriver.h"
#include "ExprParser.tab.hpp"

// Announce to Flex the prototype we want for lexing function, ...
#define YY_DECL yy::ExprParser::token_type exprlex( \
        yy::ExprParser::semantic_type* yylval,    \
        yy::ExprParser::location_type* yylloc,    \
        ExprDriver& driver)
        
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
[0-9]+\.[0-9]* { /* trailing decimal point is allowed */
           /* atof can *not* be used, because it is locale-sensitive */
           std::stringstream ss;
           ss.imbue(std::locale("C"));
           ss << yytext;
           ss >> yylval->num;
           return token::NUM;   
         }  
         
[0-9]+ {
           /* atof can *not* be used, because it is locale-sensitive */
           std::stringstream ss;
           ss.imbue(std::locale("C"));
           ss << yytext;
           ss >> yylval->num;
           return token::NUM; 
         } 
         
\+       { return token::PLUS; }
\-       { return token::MINUS; }
\<       { return token::LESSER; }
\>       { return token::LARGER; }
\*       { return token::MULTIPLY; }
\/       { return token::DIVIDE; }
div      { return token::DIVIDE; }
\(       { return token::LEFTPAREN; }
\)       { return token::RIGHTPAREN; }
mod      { return token::MOD; }
round    { return token::ROUND; }
\^       { return token::POW; }
=        { return token::EQUALS; }


%%
void ExprDriver::scan_begin()
{
 expr_flex_debug = 0;
 expr_scan_string(_input.c_str());
}

void ExprDriver::scan_end()
{
}
