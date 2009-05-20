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
  ParserFunctionsTestReader reader;
  QCOMPARE(ParserFunctions::evaluate("#if: | true | false", reader), QString("false"));
  QCOMPARE(ParserFunctions::evaluate("#if: string | true | false", reader), QString("true"));
  QCOMPARE(ParserFunctions::evaluate("#if:        | true | false", reader), QString("false"));
  QCOMPARE(ParserFunctions::evaluate("#if:      \n| true | false", reader), QString("false"));
  QCOMPARE(ParserFunctions::evaluate("#if: 1==2   | true | false", reader), QString("true"));
  QCOMPARE(ParserFunctions::evaluate("#if: foo | true ", reader), QString("true"));
  QCOMPARE(ParserFunctions::evaluate("#if: | true ", reader), QString(""));
  QCOMPARE(ParserFunctions::evaluate("#if: foo | | false", reader), QString(""));
}

//===========================================================================
void ParserFunctionsTest::parserIfEq()
{
  ParserFunctionsTestReader reader;
  QCOMPARE(ParserFunctions::evaluate("#ifeq:|_|qualifier", reader), QString(""));
  QCOMPARE(ParserFunctions::evaluate("#ifeq:||_|qualifier", reader), QString("_"));
  QCOMPARE(ParserFunctions::evaluate("#ifeq:-gender-|g|g|ns:0", reader), QString("ns:0"));
  QCOMPARE(ParserFunctions::evaluate("#ifeq:||yes|no|strange", reader), QString("yes"));
}

//===========================================================================
void ParserFunctionsTest::parserSwitch()
{
  ParserFunctionsTestReader reader;
  QCOMPARE(ParserFunctions::evaluate("#switch: a | foo = Foo | a = ok", reader), QString("ok"));
  QCOMPARE(ParserFunctions::evaluate("#switch: a | foo = Foo | #default = Bar | baz = Baz", reader), QString("Bar"));
  QCOMPARE(ParserFunctions::evaluate("#switch: a | foo = Foo | baz = Baz | Bar", reader), QString("Bar"));
  QCOMPARE(ParserFunctions::evaluate("#switch: a | foo | a | b | c = Foo | Baz", reader), QString("Foo"));
}

//===========================================================================
void ParserFunctionsTest::parserExpr()
{
  ParserFunctionsTestReader reader;
  QCOMPARE(ParserFunctions::evaluate("#expr:1", reader), QString("1"));
  QCOMPARE(ParserFunctions::evaluate("#expr:1+1", reader), QString("2"));
  QCOMPARE(ParserFunctions::evaluate("#expr: 0 + 1 ", reader), QString("1"));
  QCOMPARE(ParserFunctions::evaluate("#expr: 10 + 1 ", reader), QString("11"));
  QCOMPARE(ParserFunctions::evaluate("#expr: 10 - 1 ", reader), QString("9"));
  QCOMPARE(ParserFunctions::evaluate("#expr: -10 ", reader), QString("-10"));
  QCOMPARE(ParserFunctions::evaluate("#expr: +10 ", reader), QString("10"));
}
