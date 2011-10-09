/* This file is part of Wikt.
 *
 * Wikt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Wikt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Wikt. If not, see <http://www.gnu.org/licenses/>.
 */
#include "convdict23test.h"
#include <formattingfunctions.h>
#include <namespaceurlfunctions.h>
#include <pagenamefunctions.h>
#include <parserfunctions.h>
#include <templatesolver.h>
#include <templateutils.h>
#include <QMap>

void ConvDict23Test::formattingFunctions_basic()
{
  QCOMPARE(FormattingFunctions::evaluate("lc:OmEgA"), QString("omega"));
  QCOMPARE(FormattingFunctions::evaluate("lc:"), QString(""));
  QCOMPARE(FormattingFunctions::evaluate("lcfirst:Ah"), QString("ah"));
  QCOMPARE(FormattingFunctions::evaluate("lcfirst:AH-"), QString("aH-"));
  QCOMPARE(FormattingFunctions::evaluate("lcfirst:A"), QString("a"));
  QCOMPARE(FormattingFunctions::evaluate("lcfirst:!"), QString("!"));
  QCOMPARE(FormattingFunctions::evaluate("lcfirst:"), QString(""));
  QCOMPARE(FormattingFunctions::evaluate("uc:black magic"), QString("BLACK MAGIC"));
}

void ConvDict23Test::formattingFunctions_formatNum()
{
  QCOMPARE(FormattingFunctions::evaluate("formatnum:-987654321.654321"), QString("-987,654,321.654321"));
  QCOMPARE(FormattingFunctions::evaluate("formatnum:-987,654,321.654321|R"), QString("-987654321.654321"));
}

void ConvDict23Test::namespaceUrlFunctions_ns()
{
  QVERIFY(NamespaceUrlFunctions::isFunction("ns:2"));
  QCOMPARE(NamespaceUrlFunctions::evaluate("ns:2"), QString("User"));
  QCOMPARE(NamespaceUrlFunctions::evaluate("ns:template"), QString("Template"));
  QCOMPARE(NamespaceUrlFunctions::evaluate("ns:4"), QString("Wiktionary"));
  QCOMPARE(NamespaceUrlFunctions::evaluate("ns:project"), QString("Wiktionary"));
}

void ConvDict23Test::namespaceUrlFunctions_fullUrl()
{
  QVERIFY(NamespaceUrlFunctions::isFunction("fullurl:a"));
  QCOMPARE(NamespaceUrlFunctions::evaluate("fullurl:a"), QString("entry:///a"));
  QCOMPARE(NamespaceUrlFunctions::evaluate("fullurl:w:a"), QString("http://en.wikipedia.org/wiki/a"));
  QCOMPARE(NamespaceUrlFunctions::evaluate("fullurl:b:a b"), QString("http://en.wikibooks.org/wiki/a%20b"));
  QCOMPARE(NamespaceUrlFunctions::evaluate(QString::fromWCharArray(L"fullurl:w:háček")), QString("http://en.wikipedia.org/wiki/h%C3%A1%C4%8Dek"));
}

void ConvDict23Test::namespaceUrlFunctions_urlencode()
{
  QVERIFY(NamespaceUrlFunctions::isFunction("urlencode:a"));
  QCOMPARE(NamespaceUrlFunctions::evaluate("urlencode:a"), QString("a"));
  QCOMPARE(NamespaceUrlFunctions::evaluate("urlencode:a a"), QString("a+a"));
  QCOMPARE(NamespaceUrlFunctions::evaluate("urlencode: a a "), QString("a+a"));
  QCOMPARE(NamespaceUrlFunctions::evaluate("urlencode:a+A"), QString("a%2BA"));
  QCOMPARE(NamespaceUrlFunctions::evaluate("urlencode:a/:a"), QString("a%2F%3Aa"));
  QCOMPARE(NamespaceUrlFunctions::evaluate("urlencode:Hello world ~;(*)&"), QString("Hello+world+%7E%3B%28%2A%29%26"));
}

void ConvDict23Test::pageNameFunctions_pageName()
{
  QVERIFY(PageNameFunctions::isPageNameFunction("PAGENAME"));
  QCOMPARE(PageNameFunctions::evaluate("PAGENAME", "Help:Magic words"), QString("Magic words"));
  QCOMPARE(PageNameFunctions::evaluate(" PAGENAME", "User:Anonymous user/sandbox/my page"), QString("Anonymous user/sandbox/my page"));
  QCOMPARE(PageNameFunctions::evaluate("PAGENAME ", "User talk:Anonymous user/sandbox/my page"), QString("Anonymous user/sandbox/my page"));
}

void ConvDict23Test::pageNameFunctions_pageNameE()
{
  QVERIFY(PageNameFunctions::isPageNameFunction("PAGENAMEE"));
  QCOMPARE(PageNameFunctions::evaluate("PAGENAMEE", "Help:Magic words"), QString("Magic_words"));
  QCOMPARE(PageNameFunctions::evaluate(" PAGENAMEE", "User:Anonymous user/sandbox/my page"), QString("Anonymous_user/sandbox/my_page"));
  QCOMPARE(PageNameFunctions::evaluate("PAGENAMEE ", "User talk:Anonymous user/sandbox/my page"), QString("Anonymous_user/sandbox/my_page"));
}

void ConvDict23Test::pageNameFunctions_basePageName()
{
  QVERIFY(PageNameFunctions::isPageNameFunction("BASEPAGENAME"));
  QCOMPARE(PageNameFunctions::evaluate("BASEPAGENAME", "Help:Magic words"), QString("Magic words"));
  QCOMPARE(PageNameFunctions::evaluate(" BASEPAGENAME", "User:Anonymous user/sandbox/my page"), QString("Anonymous user/sandbox"));
  QCOMPARE(PageNameFunctions::evaluate("BASEPAGENAME ", "User talk:Anonymous user/sandbox/my page"), QString("Anonymous user/sandbox"));
}

void ConvDict23Test::pageNameFunctions_basePageNameE()
{
  QVERIFY(PageNameFunctions::isPageNameFunction("BASEPAGENAMEE"));
  QCOMPARE(PageNameFunctions::evaluate("BASEPAGENAMEE", "Help:Magic words"), QString("Magic_words"));
  QCOMPARE(PageNameFunctions::evaluate(" BASEPAGENAMEE", "User:Anonymous user/sandbox/my page"), QString("Anonymous_user/sandbox"));
  QCOMPARE(PageNameFunctions::evaluate("BASEPAGENAMEE ", "User talk:Anonymous user/sandbox/my page"), QString("Anonymous_user/sandbox"));
}

void ConvDict23Test::pageNameFunctions_subPageName()
{
  QVERIFY(PageNameFunctions::isPageNameFunction("SUBPAGENAME"));
  QCOMPARE(PageNameFunctions::evaluate("SUBPAGENAME", "Help:Magic words"), QString("Magic words"));
  QCOMPARE(PageNameFunctions::evaluate(" SUBPAGENAME", "User:Anonymous user/sandbox/my page"), QString("my page"));
  QCOMPARE(PageNameFunctions::evaluate("SUBPAGENAME ", "User talk:Anonymous user/sandbox/my page"), QString("my page"));
}

void ConvDict23Test::pageNameFunctions_subPageNameE()
{
  QVERIFY(PageNameFunctions::isPageNameFunction("SUBPAGENAMEE"));
  QCOMPARE(PageNameFunctions::evaluate("SUBPAGENAMEE", "Help:Magic words"), QString("Magic_words"));
  QCOMPARE(PageNameFunctions::evaluate(" SUBPAGENAMEE",
          "User:Anonymous user/sandbox/my page"),
      QString("my_page"));
  QCOMPARE(PageNameFunctions::evaluate("SUBPAGENAMEE ",
          "User talk:Anonymous user/sandbox/my page"),
      QString("my_page"));
}

void ConvDict23Test::pageNameFunctions_fullPageName()
{
  QVERIFY(PageNameFunctions::isPageNameFunction("FULLPAGENAME"));
  QCOMPARE(PageNameFunctions::evaluate("FULLPAGENAME", "Help:Magic words"), QString("Help:Magic words"));
  QCOMPARE(PageNameFunctions::evaluate(" FULLPAGENAME", "User:Anonymous user/sandbox/my page"), QString("User:Anonymous user/sandbox/my page"));
  QCOMPARE(PageNameFunctions::evaluate("FULLPAGENAME ", "User talk:Anonymous user/sandbox/my page"), QString("User talk:Anonymous user/sandbox/my page"));
}

void ConvDict23Test::pageNameFunctions_fullPageNameE()
{
  QVERIFY(PageNameFunctions::isPageNameFunction("FULLPAGENAMEE"));
  QCOMPARE(PageNameFunctions::evaluate("FULLPAGENAMEE", "Help:Magic words"), QString("Help:Magic_words"));
  QCOMPARE(PageNameFunctions::evaluate(" FULLPAGENAMEE", "User:Anonymous user/sandbox/my page"), QString("User:Anonymous_user/sandbox/my_page"));
  QCOMPARE(PageNameFunctions::evaluate("FULLPAGENAMEE ", "User talk:Anonymous user/sandbox/my page"), QString("User_talk:Anonymous_user/sandbox/my_page"));
}

void ConvDict23Test::pageNameFunctions_nameSpace()
{
  QVERIFY(PageNameFunctions::isPageNameFunction("NAMESPACE"));
  QCOMPARE(PageNameFunctions::evaluate("NAMESPACE", "a"), QString(""));
  QCOMPARE(PageNameFunctions::evaluate("NAMESPACE", "Help:Magic words"), QString("Help"));
  QCOMPARE(PageNameFunctions::evaluate(" NAMESPACE", "User:Anonymous user/sandbox/my page"), QString("User"));
  QCOMPARE(PageNameFunctions::evaluate("NAMESPACE ", "User talk:Anonymous user/sandbox/my page"), QString("User talk"));
}

void ConvDict23Test::pageNameFunctions_nameSpaceE()
{
  QVERIFY(PageNameFunctions::isPageNameFunction("NAMESPACEE"));
  QCOMPARE(PageNameFunctions::evaluate("NAMESPACEE", "Help:Magic words"), QString("Help"));
  QCOMPARE(PageNameFunctions::evaluate(" NAMESPACEE", "User:Anonymous user/sandbox/my page"), QString("User"));
  QCOMPARE(PageNameFunctions::evaluate("NAMESPACEE ", "User talk:Anonymous user/sandbox/my page"), QString("User_talk"));
}

class ParserFunctionsTestReader : public Format2Reader
{
public:
  virtual QString source(QString /*entryName*/) { return ""; }
  virtual bool exist(QString /*entryName*/) { return false; }
};

static QString evaluate(const QString &expr)
{
  ParserFunctionsTestReader reader;
  return ParserFunctions::evaluate(expr, reader, "test entry");
}

void ConvDict23Test::parserFunctions_if()
{
  QCOMPARE(evaluate("#if: | true | false"), QString("false"));
  QCOMPARE(evaluate("#if: string | true | false"), QString("true"));
  QCOMPARE(evaluate("#if:        | true | false"), QString("false"));
  QCOMPARE(evaluate("#if:      \n| true | false"), QString("false"));
  QCOMPARE(evaluate("#if: 1==2   | true | false"), QString("true"));
  QCOMPARE(evaluate("#if: foo | true "), QString("true"));
  QCOMPARE(evaluate("#if: | true "), QString(""));
  QCOMPARE(evaluate("#if: foo | | false"), QString(""));
}

void ConvDict23Test::parserFunctions_ifEq()
{
  QCOMPARE(evaluate("#ifeq:|_|qualifier"), QString(""));
  QCOMPARE(evaluate("#ifeq:||_|qualifier"), QString("_"));
  QCOMPARE(evaluate("#ifeq:-gender-|g|g|ns:0"), QString("ns:0"));
  QCOMPARE(evaluate("#ifeq:||yes|no|strange"), QString("yes"));
}

void ConvDict23Test::parserFunctions_switch()
{
  QCOMPARE(evaluate("#switch: a | foo = Foo | a = ok"), QString("ok"));
  QCOMPARE(evaluate("#switch: a | foo = Foo | #default = Bar | baz = Baz"), QString("Bar"));
  QCOMPARE(evaluate("#switch: a | foo = Foo | baz = Baz | Bar"), QString("Bar"));
  QCOMPARE(evaluate("#switch: a | foo | a | b | c = Foo | Baz"), QString("Foo"));
}

void ConvDict23Test::parserFunctions_expr()
{
  QCOMPARE(evaluate("#expr:"), QString(""));

  // Numbers
  // Differs from MediaWiki which returns 123456789012340.
  QCOMPARE(evaluate("#expr:123456789012345"), QString("1.2345678901234E+14"));
  QCOMPARE(evaluate("#expr:1.23456789012345"), QString("1.2345678901235"));
  // Differs from MediaWiki which returns 1.0E-6.
  QCOMPARE(evaluate("#expr:.000001"), QString("1E-06"));
  // Differs from MediaWiki which returns 1.2345678901234E-6.
  QCOMPARE(evaluate("#expr:.00000123456789012345"), QString("1.2345678901234E-06"));
  QCOMPARE(evaluate("#expr:.123e4"), QString("1230"));
  QCOMPARE(evaluate("#expr:123E-2"), QString("1.23"));
  QCOMPARE(evaluate("#expr:e"), QString("2.718281828459"));
  QCOMPARE(evaluate("#expr:pi"), QString("3.1415926535898"));

  // Exp
  QCOMPARE(evaluate("#expr:exp1.2"), QString("3.3201169227365"));
  QCOMPARE(evaluate("#expr:e^1.2"), QString("3.3201169227365"));

  // Ln
  QCOMPARE(evaluate("#expr:ln2"), QString("0.69314718055995"));
  QCOMPARE(evaluate("#expr:ln2/ln10"), QString("0.30102999566398"));

  // Abs
  QCOMPARE(evaluate("#expr:abs-1.2"), QString("1.2"));

  // Trunc
  QCOMPARE(evaluate("#expr:trunc1.2"), QString("1"));
  QCOMPARE(evaluate("#expr:trunc1.8"), QString("1"));
  QCOMPARE(evaluate("#expr:trunc-1.2"), QString("-1"));

  // Floor
  QCOMPARE(evaluate("#expr:floor1.2"), QString("1"));
  QCOMPARE(evaluate("#expr:floor-1.2"), QString("-2"));

  // Ceil
  QCOMPARE(evaluate("#expr:ceil1.2"), QString("2"));
  QCOMPARE(evaluate("#expr:ceil-1.2"), QString("-1"));

  // Sin
  QCOMPARE(evaluate("#expr:sin.1"), QString("0.099833416646828"));
  QCOMPARE(evaluate("#expr:sin(30*pi/180)"), QString("0.5"));

  // Cos
  QCOMPARE(evaluate("#expr:cos.1"), QString("0.99500416527803"));

  // Tan
  QCOMPARE(evaluate("#expr:tan.1"), QString("0.10033467208545"));

  // ASin
  QCOMPARE(evaluate("#expr:asin.1"), QString("0.10016742116156"));

  // ACos
  QCOMPARE(evaluate("#expr:acos.1"), QString("1.4706289056333"));

  // ATan
  QCOMPARE(evaluate("#expr:atan.1"), QString("0.099668652491162"));

  // Unary + sign
  QCOMPARE(evaluate("#expr:+12"), QString("12"));
  QCOMPARE(evaluate("#expr:++12"), QString("12"));
  QCOMPARE(evaluate("#expr:+-12"), QString("-12"));

  // Unary - sign
  QCOMPARE(evaluate("#expr:-12"), QString("-12"));
  QCOMPARE(evaluate("#expr:-+12"), QString("-12"));
  QCOMPARE(evaluate("#expr:--12"), QString("12"));

  // Not
  QCOMPARE(evaluate("#expr:not 0"), QString("1"));
  QCOMPARE(evaluate("#expr:not 1"), QString("0"));
  QCOMPARE(evaluate("#expr:not 2"), QString("0"));

  // Power
  QCOMPARE(evaluate("#expr:2^7"), QString("128"));
  QCOMPARE(evaluate("#expr:2^-7"), QString("0.0078125"));
  QCOMPARE(evaluate("#expr:(-2)^7"), QString("-128"));
  QCOMPARE(evaluate("#expr:(-2)^8"), QString("256"));
  QCOMPARE(evaluate("#expr:2^1.2"), QString("2.2973967099941"));
  QCOMPARE(evaluate("#expr:2^.5"), QString("1.4142135623731"));
  QCOMPARE(evaluate("#expr:(-2)^1.2"), QString("NAN"));
  QCOMPARE(evaluate("#expr:(-2)^.5"), QString("NAN"));

  // Multiplication
  QCOMPARE(evaluate("#expr:30*7"), QString("210"));
  QCOMPARE(evaluate("#expr:30*-7"), QString("-210"));

  // Division
  QCOMPARE(evaluate("#expr:30/7"), QString("4.2857142857143"));
  QCOMPARE(evaluate("#expr:30/-7"), QString("-4.2857142857143"));
  QCOMPARE(evaluate("#expr:30 div 7"), QString("4.2857142857143"));

  // Modulo
  QCOMPARE(evaluate("#expr:30 mod 7"), QString("2"));
  QCOMPARE(evaluate("#expr:30 mod -7"), QString("2"));
  QCOMPARE(evaluate("#expr:-30 mod 7"), QString("-2"));
  QCOMPARE(evaluate("#expr:-30 mod -7"), QString("-2"));
  QCOMPARE(evaluate("#expr:-8 mod -3"), QString("-2"));
  QCOMPARE(evaluate("#expr:-8 mod 2.9"), QString("0"));
  QCOMPARE(evaluate("#expr:-8 mod 3.2"), QString("-2"));
  QCOMPARE(evaluate("#expr:8.9 mod 3"), QString("2"));

  // Addition
  QCOMPARE(evaluate("#expr:30 + 7"), QString("37"));

  // Subtraction
  QCOMPARE(evaluate("#expr: 30 - 7 "), QString("23"));

  // Round
  QCOMPARE(evaluate("#expr:4.2857 round 3"), QString("4.286"));
  QCOMPARE(evaluate("#expr:4.2857 round 0"), QString("4"));
  QCOMPARE(evaluate("#expr:42857 round -2"), QString("42900"));
  QCOMPARE(evaluate("#expr:4.5 round 0"), QString("5"));
  QCOMPARE(evaluate("#expr:-4.5 round 0"), QString("-5"));

  // Equality
  QCOMPARE(evaluate("#expr:3=03.0"), QString("1"));

  // Inequality
  QCOMPARE(evaluate("#expr:3<>03.0"), QString("0"));
  QCOMPARE(evaluate("#expr:3<>4"), QString("1"));

  // Less than
  QCOMPARE(evaluate("#expr:3<2"), QString("0"));
  QCOMPARE(evaluate("#expr:3<3"), QString("0"));
  QCOMPARE(evaluate("#expr:3<4"), QString("1"));

  // Greater than
  QCOMPARE(evaluate("#expr:3>2"), QString("1"));
  QCOMPARE(evaluate("#expr:3>3"), QString("0"));
  QCOMPARE(evaluate("#expr:3>4"), QString("0"));

  // Less than or equal to
  QCOMPARE(evaluate("#expr:3<=2"), QString("0"));
  QCOMPARE(evaluate("#expr:3<=3"), QString("1"));
  QCOMPARE(evaluate("#expr:3<=4"), QString("1"));

  // Greater than or equal to
  QCOMPARE(evaluate("#expr:3>=2"), QString("1"));
  QCOMPARE(evaluate("#expr:3>=3"), QString("1"));
  QCOMPARE(evaluate("#expr:3>=4"), QString("0"));

  // Logical AND
  QCOMPARE(evaluate("#expr:3 and 4"), QString("1"));
  QCOMPARE(evaluate("#expr:0 and 3"), QString("0"));
  QCOMPARE(evaluate("#expr:-3 and 0"), QString("0"));
  QCOMPARE(evaluate("#expr:0 and 0"), QString("0"));

  // Logical OR
  QCOMPARE(evaluate("#expr:3 or 4"), QString("1"));
  QCOMPARE(evaluate("#expr:0 or 3"), QString("1"));
  QCOMPARE(evaluate("#expr:-3 or 0"), QString("1"));
  QCOMPARE(evaluate("#expr:0 or 0"), QString("0"));

  // More complicated
  QCOMPARE(evaluate("#expr:2*2+1"), QString("5"));
  QCOMPARE(evaluate("#expr:1+2*2"), QString("5"));
  QCOMPARE(evaluate("#expr:1+2*2*2"), QString("9"));
  QCOMPARE(evaluate("#expr:1*2+2*2"), QString("6"));
  QCOMPARE(evaluate("#expr: 2 - 3 + 4 / 5 * 6"), QString("3.8"));
  QCOMPARE(evaluate("#expr:1+2<2*2"), QString("1"));
  QCOMPARE(evaluate("#expr:1+2>2*2"), QString("0"));
  QCOMPARE(evaluate("#expr:2 = 5 < 3 + 4"), QString("1"));
  QCOMPARE(evaluate("#expr:3 * 4 mod 10 * 10"), QString("20"));
  QCOMPARE(evaluate("#expr:(1+2)*2"), QString("6"));
}

class TemplateSolverTestReader : public Format2Reader
{
public:
  QMap<QString, QString> data;
  virtual QString sourceTemplate(QString name) { return data.value(name, ""); }
  virtual bool exist(QString entryName) { return data.contains(entryName); }
};

void ConvDict23Test::templateSolver_declaringDefaultValue()
{
  TemplateSolverTestReader reader;
  reader.data.insert("Template:t", "start-{{{1|pqr}}}-end");
  QCOMPARE(TemplateSolver("", "{{t|a}}", reader).run(), QString("start-a-end"));
  QCOMPARE(TemplateSolver("", "{{t| }}", reader).run(), QString("start- -end"));
  QCOMPARE(TemplateSolver("", "{{t|}}", reader).run(), QString("start--end"));
  QCOMPARE(TemplateSolver("", "{{t|1=no surprise}}", reader).run(), QString("start-no surprise-end"));
  QCOMPARE(TemplateSolver("", "{{t|1=no|surprise}}", reader).run(), QString("start-surprise-end"));
  QCOMPARE(TemplateSolver("", "{{t}}", reader).run(), QString("start-pqr-end"));
  QCOMPARE(TemplateSolver("", "{{t|2=two}}", reader).run(), QString("start-pqr-end"));
}

void ConvDict23Test::templateSolver_moreBraces()
{
  TemplateSolverTestReader reader;
  reader.data.insert("Template:t1", "start-{{{1}}}-end");
  // "&#x007b;" == "{", "&#x007d;" == "}"
  QCOMPARE(TemplateSolver("", "{{{{t1|1}}}}", reader).run(), QString("{1}"));
  QCOMPARE(TemplateSolver("", "{{ {{t1|1}}}}", reader).run(), QString("&#x007b;&#x007b;Template:start-1-end&#x007d;&#x007d;"));
  QCOMPARE(TemplateSolver("", "{{{{t1|1}} }}", reader).run(), QString("&#x007b;&#x007b;Template:start-1-end&#x007d;&#x007d;"));
  QCOMPARE(TemplateSolver("", "{{{{t1|1}} }}}", reader).run(), QString("&#x007b;&#x007b;Template:start-1-end&#x007d;&#x007d;}"));
  QCOMPARE(TemplateSolver("", "{{{{t1|1}} }} {{{5}}}", reader).run(), QString("&#x007b;&#x007b;Template:start-1-end&#x007d;&#x007d; &#x007b;&#x007b;&#x007b;5&#x007d;&#x007d;&#x007d;"));
  QCOMPARE(TemplateSolver("", "{{{{{abc|in}}}}}", reader).run(), QString("&#x007b;&#x007b;Template:in&#x007d;&#x007d;"));
  QCOMPARE(TemplateSolver("", "{{{ {{#if:x|tc|ab}}}}}", reader).run(), QString("&#x007b;&#x007b;&#x007b;tc&#x007d;&#x007d;&#x007d;"));
  QCOMPARE(TemplateSolver("", "{{{{#ifeq:{{{g|{{{gender}}}}}}|g|g|ns:0}}|{{language|{{{1}}}}}}}", reader).run(), QString(""));
}

void ConvDict23Test::templateSolver_formOf()
{
  TemplateSolverTestReader reader;
  reader.data.insert("Template:form of", "{{#if:{{{2|}}}|<span class='use-with-mention'>{{#if:{{{nocap|}}}|{{{1}}}|{{ucfirst:{{{1}}}}}}} of <span class='mention'>{{#if:{{{sc|}}}|{{{{{sc}}}|{{#ifexist:{{{2}}}|[[{{{2}}}#{{{lang|English}}}|{{{3|{{{2}}}}}}]]|{{{2}}}}}}}|{{#ifexist:{{{2}}}|[[{{{2}}}#{{{lang|English}}}|{{{3|{{{2}}}}}}]]|{{{2}}}}}}}</span>{{#if:{{{tr|}}}|&#32;({{{tr}}})}}{{#if:{{{nodot|}}}||.}}</span>|<span class='use-with-mention'><span class='mention'>[[{{{1}}}#{{{lang|English}}}|{{#if:{{{sc|}}}|{{{{{sc}}}|{{{alt|{{{1}}}}}}}}|{{{alt|{{{1}}}}}}}}]]</span></span>{{#if:{{{tr|}}}|&#32;({{{tr}}})}}}}");
  QCOMPARE(TemplateSolver("", "{{form of|lower case form|B}}", reader).run(), QString("<span class='use-with-mention'>Lower case form of <span class='mention'>B</span>.</span>"));
  QCOMPARE(TemplateSolver("", "{{form of|lower case form|[[B]]}}", reader).run(), QString("<span class='use-with-mention'>Lower case form of <span class='mention'>[[B]]</span>.</span>"));
}

void ConvDict23Test::templateSolver_isValidPageName()
{
  TemplateSolverTestReader reader;
  reader.data.insert("Template:isValidPageName", "{{#ifeq:{{{1}}}|-||{{#ifeq:[[:Special:Whatlinkshere/{{{1}}}]]|{{raw:Special:Whatlinkshere/{{{1}}}}}|valid}}}}");
  QCOMPARE(TemplateSolver("", "{{isValidPageName|English}}", reader).run(), QString("valid"));
  QCOMPARE(TemplateSolver("", "{{isValidPageName|[[English]]}}", reader).run(), QString(""));
}

void ConvDict23Test::templateSolver_evaluatedWikiSyntaxSimple()
{
  TemplateSolverTestReader reader;
  reader.data.insert("Template:!", "|");
  reader.data.insert("Template:x2", "{{{1}}}{{{1}}}");
  QCOMPARE(TemplateSolver("", "{{x2|{{{!}}\n{{!}}A\n{{!}}B\n{{!}}-\n{{!}}C\n{{!}}D\n{{!}}}\n}}", reader).run(),
      QString("\n{|\n|A\n|B\n|-\n|C\n|D\n|}\n{|\n|A\n|B\n|-\n|C\n|D\n|}\n"));
}

void ConvDict23Test::templateSolver_newlineAddingInTemplates()
{
  TemplateSolverTestReader reader;
  reader.data.insert("Template:a", "g{{b}}\n{{b}}");
  reader.data.insert("Template:b", "{{{|#*:good}}}");
  QCOMPARE(TemplateSolver("", "{{a}}", reader).run(), QString("g\n#*:good\n#*:good"));
}

void ConvDict23Test::templateSolver_pluralOf()
{
  TemplateSolverTestReader reader;
  reader.data.insert("Template:wlink", "{{#ifeq:{{{w|{{{1}}}}}}|-||{{#ifeq:[[:Special:Whatlinkshere/{{{w|{{{1}}}}}}]]|{{raw:Special:Whatlinkshere/{{{w|{{{1}}}}}}}}|[[{{{w|{{{1}}}}}}]]|{{{w|{{{1}}}}}}}}}}");
  QCOMPARE(TemplateSolver("", "{{wlink|w=[[stadium#English|stadium]]}}", reader).run(), QString("[[stadium#English|stadium]]"));
  QCOMPARE(TemplateSolver("", "{{wlink|w=stadium}}", reader).run(), QString("[[stadium]]"));

  reader.data.insert("Template:plural of", "{{{cap|{{#if:{{{nocap|}}}|p|P}}}}}lural form of {{#if:{{{2|}}}|[[{{{1}}}|{{{2}}}]]|{{wlink|w={{{1}}}}}}}{{{dot|{{#if:{{{nodot|}}}||.}}}}}{{#ifeq:{{NAMESPACE}}||{{#if:{{{nocat|}}}||[[Category:English plurals]]}}}}");
  QCOMPARE(TemplateSolver("", "{{plural of|[[stadium#English|stadium]]}}", reader).run(), QString("Plural form of [[stadium#English|stadium]].[[Category:English plurals]]"));
}

void ConvDict23Test::templateSolver_embeddedLink()
{
  TemplateSolverTestReader reader;
  reader.data.insert("Template:test", "{{#if:a|[[kk}}]]}}");
  QCOMPARE(TemplateSolver("", "{{#if:a|[[kk}}]]}}", reader).run(), QString("[[kk}}]]"));
}

void ConvDict23Test::templateUtils_addParameterToList0()
{
  ParameterList p;
  TemplateUtils::_addParameterToList("a", p);
  TemplateUtils::_addParameterToList(" ", p);
  TemplateUtils::_addParameterToList("", p);
  QCOMPARE(p.size(), 3);
  QCOMPARE(p["1"], QString("a"));
  QCOMPARE(p["2"], QString(" "));
  QCOMPARE(p["3"], QString(""));
}

void ConvDict23Test::templateUtils_addParameterToList1()
{
  ParameterList p;
  TemplateUtils::_addParameterToList("3=1", p);
  TemplateUtils::_addParameterToList("2", p);
  TemplateUtils::_addParameterToList("1=3", p);
  TemplateUtils::_addParameterToList("4", p);
  TemplateUtils::_addParameterToList("5", p);
  TemplateUtils::_addParameterToList("6", p);
  QCOMPARE(p.size(), 4);
  QCOMPARE(p["1"], QString("3"));
  QCOMPARE(p["2"], QString("4"));
  QCOMPARE(p["3"], QString("5"));
}

void ConvDict23Test::templateUtils_getParts()
{
  QList<QString> output;
  TemplateUtils::getParts("context|[[c|c]]|b|", output);
  QCOMPARE(output.size(), 4);
  QCOMPARE(output[0], QString("context"));
  QCOMPARE(output[1], QString("[[c|c]]"));
  QCOMPARE(output[2], QString("b"));
  QCOMPARE(output[3], QString(""));

  // Tricky: embedded links.
  output.clear();
  TemplateUtils::getParts("#if:|[[[[stadium#EnglishpipeEscapeSurestadium]]|]]|[[stadium#EnglishpipeEscapeSurestadium]]", output);
  QCOMPARE(output.size(), 3);
  QCOMPARE(output[0], QString("#if:"));
  QCOMPARE(output[1], QString("[[[[stadium#EnglishpipeEscapeSurestadium]]|]]"));
  QCOMPARE(output[2], QString("[[stadium#EnglishpipeEscapeSurestadium]]"));
}

void ConvDict23Test::templateUtils_evaluateParameter()
{
  ParameterList p;
  QCOMPARE(TemplateUtils::evaluateParameter("lang", p), QString("&#x007b;&#x007b;&#x007b;lang&#x007d;&#x007d;&#x007d;"));
  QCOMPARE(TemplateUtils::evaluateParameter("lang|en", p), QString("en"));
  QCOMPARE(TemplateUtils::evaluateParameter("lang|", p), QString(""));
  QCOMPARE(TemplateUtils::evaluateParameter("lang| ", p), QString(" "));
  QCOMPARE(TemplateUtils::evaluateParameter("lang||", p), QString(""));
  QCOMPARE(TemplateUtils::evaluateParameter("lang|en|cs", p), QString("en"));
  QCOMPARE(TemplateUtils::evaluateParameter("|en|cs", p), QString("en"));
  QCOMPARE(TemplateUtils::evaluateParameter("", p), QString("&#x007b;&#x007b;&#x007b;&#x007d;&#x007d;&#x007d;"));
}

QTEST_APPLESS_MAIN(ConvDict23Test)
