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
#include "TemplateUtilsTest.h"
#include "TemplateUtils.h"
#include <QTest>

//===========================================================================
void TemplateUtilsTest::addParameterToList0()
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

//===========================================================================
void TemplateUtilsTest::addParameterToList1()
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

//===========================================================================
void TemplateUtilsTest::getParts()
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

//===========================================================================
void TemplateUtilsTest::evaluateParameter()
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
