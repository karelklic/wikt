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
#include "TemplateSolverTest.h"
#include "TemplateSolver.h"
#include <QTest>
#include <QMap>

//===========================================================================
class TemplateSolverTestReader : public Format2Reader
{
public:
  QMap<QString, QString> data;
  virtual QString source(QString entryName) { return data.value(entryName, ""); }
  virtual bool exist(QString entryName) { return data.contains(entryName); }
};

//===========================================================================
void TemplateSolverTest::declaringDefaultValue()
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

//===========================================================================
void TemplateSolverTest::moreBraces()
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

//===========================================================================
void TemplateSolverTest::formOf()
{
  TemplateSolverTestReader reader;
  reader.data.insert("Template:form of", "{{#if:{{{2|}}}|<span class='use-with-mention'>{{#if:{{{nocap|}}}|{{{1}}}|{{ucfirst:{{{1}}}}}}} of <span class='mention'>{{#if:{{{sc|}}}|{{{{{sc}}}|{{#ifexist:{{{2}}}|[[{{{2}}}#{{{lang|English}}}|{{{3|{{{2}}}}}}]]|{{{2}}}}}}}|{{#ifexist:{{{2}}}|[[{{{2}}}#{{{lang|English}}}|{{{3|{{{2}}}}}}]]|{{{2}}}}}}}</span>{{#if:{{{tr|}}}|&#32;({{{tr}}})}}{{#if:{{{nodot|}}}||.}}</span>|<span class='use-with-mention'><span class='mention'>[[{{{1}}}#{{{lang|English}}}|{{#if:{{{sc|}}}|{{{{{sc}}}|{{{alt|{{{1}}}}}}}}|{{{alt|{{{1}}}}}}}}]]</span></span>{{#if:{{{tr|}}}|&#32;({{{tr}}})}}}}");
  QCOMPARE(TemplateSolver("", "{{form of|lower case form|B}}", reader).run(), QString("<span class='use-with-mention'>Lower case form of <span class='mention'>B</span>.</span>"));
  QCOMPARE(TemplateSolver("", "{{form of|lower case form|[[B]]}}", reader).run(), QString("<span class='use-with-mention'>Lower case form of <span class='mention'>[[B]]</span>.</span>"));
}

//===========================================================================
void TemplateSolverTest::isValidPageName()
{
  TemplateSolverTestReader reader;
  reader.data.insert("Template:isValidPageName", "{{#ifeq:{{{1}}}|-||{{#ifeq:[[:Special:Whatlinkshere/{{{1}}}]]|{{raw:Special:Whatlinkshere/{{{1}}}}}|valid}}}}");
  QCOMPARE(TemplateSolver("", "{{isValidPageName|English}}", reader).run(), QString("valid"));
  QCOMPARE(TemplateSolver("", "{{isValidPageName|[[English]]}}", reader).run(), QString(""));
}

//===========================================================================
void TemplateSolverTest::evaluatedWikiSyntaxSimple()
{
  TemplateSolverTestReader reader;
  reader.data.insert("Template:!", "|");
  reader.data.insert("Template:x2", "{{{1}}}{{{1}}}");
  QCOMPARE(TemplateSolver("", "{{x2|{{{!}}\n{{!}}A\n{{!}}B\n{{!}}-\n{{!}}C\n{{!}}D\n{{!}}}\n}}", reader).run(),
      QString("\n{|\n|A\n|B\n|-\n|C\n|D\n|}\n{|\n|A\n|B\n|-\n|C\n|D\n|}\n"));
}

//===========================================================================
void TemplateSolverTest::newlineAddingInTemplates()
{
  TemplateSolverTestReader reader;
  reader.data.insert("Template:a", "g{{b}}\n{{b}}");
  reader.data.insert("Template:b", "{{{|#*:good}}}");
  QCOMPARE(TemplateSolver("", "{{a}}", reader).run(), QString("g\n#*:good\n#*:good"));
}

//===========================================================================
void TemplateSolverTest::pluralOf()
{
  TemplateSolverTestReader reader;
  reader.data.insert("Template:wlink", "{{#ifeq:{{{w|{{{1}}}}}}|-||{{#ifeq:[[:Special:Whatlinkshere/{{{w|{{{1}}}}}}]]|{{raw:Special:Whatlinkshere/{{{w|{{{1}}}}}}}}|[[{{{w|{{{1}}}}}}]]|{{{w|{{{1}}}}}}}}}}");
  QCOMPARE(TemplateSolver("", "{{wlink|w=[[stadium#English|stadium]]}}", reader).run(), QString("[[stadium#English|stadium]]"));
  QCOMPARE(TemplateSolver("", "{{wlink|w=stadium}}", reader).run(), QString("[[stadium]]"));

  reader.data.insert("Template:plural of", "{{{cap|{{#if:{{{nocap|}}}|p|P}}}}}lural form of {{#if:{{{2|}}}|[[{{{1}}}|{{{2}}}]]|{{wlink|w={{{1}}}}}}}{{{dot|{{#if:{{{nodot|}}}||.}}}}}{{#ifeq:{{NAMESPACE}}||{{#if:{{{nocat|}}}||[[Category:English plurals]]}}}}");
  QCOMPARE(TemplateSolver("", "{{plural of|[[stadium#English|stadium]]}}", reader).run(), QString("Plural form of [[stadium#English|stadium]].[[Category:English plurals]]"));
}

//===========================================================================
void TemplateSolverTest::embeddedLink()
{
  TemplateSolverTestReader reader;
  reader.data.insert("Template:test", "{{#if:a|[[kk}}]]}}");
  QCOMPARE(TemplateSolver("", "{{#if:a|[[kk}}]]}}", reader).run(), QString("[[kk}}]]"));
}
