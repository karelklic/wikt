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
#include <parserfunctions.h>
#include <QTest>

#include <QObject>

/// Tests ParserFunctions functions.
class ParserFunctionsTest : public QObject
{
  Q_OBJECT
private slots:
  void parserIf();
  void parserIfEq();
  void parserSwitch();
  void parserExpr();

private:
  /// Evaluates given expression as a ParserFunction.
  /// @return
  ///   The result of ParserFunction call.
  static QString evaluate(const QString &expr);
};

class ParserFunctionsTestReader : public Format2Reader
{
public:
  virtual QString source(QString /*entryName*/) { return ""; }
  virtual bool exist(QString /*entryName*/) { return false; }
};

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

void ParserFunctionsTest::parserIfEq()
{
  QCOMPARE(evaluate("#ifeq:|_|qualifier"), QString(""));
  QCOMPARE(evaluate("#ifeq:||_|qualifier"), QString("_"));
  QCOMPARE(evaluate("#ifeq:-gender-|g|g|ns:0"), QString("ns:0"));
  QCOMPARE(evaluate("#ifeq:||yes|no|strange"), QString("yes"));
}

void ParserFunctionsTest::parserSwitch()
{
  QCOMPARE(evaluate("#switch: a | foo = Foo | a = ok"), QString("ok"));
  QCOMPARE(evaluate("#switch: a | foo = Foo | #default = Bar | baz = Baz"), QString("Bar"));
  QCOMPARE(evaluate("#switch: a | foo = Foo | baz = Baz | Bar"), QString("Bar"));
  QCOMPARE(evaluate("#switch: a | foo | a | b | c = Foo | Baz"), QString("Foo"));
}

void ParserFunctionsTest::parserExpr()
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

QString ParserFunctionsTest::evaluate(const QString &expr)
{
  ParserFunctionsTestReader reader;
  return ParserFunctions::evaluate(expr, reader, "test entry");
}

QTEST_APPLESS_MAIN(ParserFunctionsTest)
#include "parserfunctionstest.moc"
