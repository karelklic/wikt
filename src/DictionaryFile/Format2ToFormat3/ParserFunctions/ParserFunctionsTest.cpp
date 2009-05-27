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
#include "ParserFunctionsTest.h"
#include "ParserFunctions.h"
#include "QTest"

//===========================================================================
class ParserFunctionsTestReader : public Format2Reader
{
public:
  virtual QString source(QString /*entryName*/) { return ""; }
  virtual bool exist(QString /*entryName*/) { return false; }
};

//===========================================================================
void ParserFunctionsTest::parserIf()
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

//===========================================================================
void ParserFunctionsTest::parserIfEq()
{
  QCOMPARE(evaluate("#ifeq:|_|qualifier"), QString(""));
  QCOMPARE(evaluate("#ifeq:||_|qualifier"), QString("_"));
  QCOMPARE(evaluate("#ifeq:-gender-|g|g|ns:0"), QString("ns:0"));
  QCOMPARE(evaluate("#ifeq:||yes|no|strange"), QString("yes"));
}

//===========================================================================
void ParserFunctionsTest::parserSwitch()
{
  QCOMPARE(evaluate("#switch: a | foo = Foo | a = ok"), QString("ok"));
  QCOMPARE(evaluate("#switch: a | foo = Foo | #default = Bar | baz = Baz"), QString("Bar"));
  QCOMPARE(evaluate("#switch: a | foo = Foo | baz = Baz | Bar"), QString("Bar"));
  QCOMPARE(evaluate("#switch: a | foo | a | b | c = Foo | Baz"), QString("Foo"));
}

//===========================================================================
void ParserFunctionsTest::parserExpr()
{
  QCOMPARE(evaluate("#expr:"), QString(""));

  QCOMPARE(evaluate("#expr:1"), QString("1"));
  QCOMPARE(evaluate("#expr:1+1"), QString("2"));
  QCOMPARE(evaluate("#expr: 0 + 1 "), QString("1"));
  QCOMPARE(evaluate("#expr: 10 + 1 "), QString("11"));
  QCOMPARE(evaluate("#expr: 10 - 1 "), QString("9"));
  QCOMPARE(evaluate("#expr: -10 "), QString("-10"));
  QCOMPARE(evaluate("#expr: +10 "), QString("10"));

  QCOMPARE(evaluate("#expr:0>1"), QString("0"));
  QCOMPARE(evaluate("#expr:1>0"), QString("1"));
}

//===========================================================================
QString ParserFunctionsTest::evaluate(const QString &expr)
{
  ParserFunctionsTestReader reader;
  return ParserFunctions::evaluate(expr, reader, "test entry");
}
