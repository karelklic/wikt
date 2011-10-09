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
#include <formattingfunctions.h>
#include <QTest>
#include <QObject>

/// Tests FormattingFunctions functions.
class FormattingFunctionsTest : public QObject
{
  Q_OBJECT
private slots:
  void basic();
  void formatNum();
};

void FormattingFunctionsTest::basic()
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

void FormattingFunctionsTest::formatNum()
{
  QCOMPARE(FormattingFunctions::evaluate("formatnum:-987654321.654321"), QString("-987,654,321.654321"));
  QCOMPARE(FormattingFunctions::evaluate("formatnum:-987,654,321.654321|R"), QString("-987654321.654321"));
}

QTEST_APPLESS_MAIN(FormattingFunctionsTest)
#include "formattingfunctionstest.moc"
