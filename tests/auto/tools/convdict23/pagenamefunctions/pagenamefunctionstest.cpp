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
#include <pagenamefunctions.h>
#include <QTest>
#include <QObject>

/// Tests PageNameFunctions class methods.
class PageNameFunctionsTest : public QObject
{
  Q_OBJECT
private slots:
  void pageName();
  void pageNameE();
  void basePageName();
  void basePageNameE();
  void subPageName();
  void subPageNameE();
  void fullPageName();
  void fullPageNameE();
  void nameSpace();
  void nameSpaceE();
};

void PageNameFunctionsTest::pageName()
{
  QVERIFY(PageNameFunctions::isPageNameFunction("PAGENAME"));
  QCOMPARE(PageNameFunctions::evaluate("PAGENAME", "Help:Magic words"), QString("Magic words"));
  QCOMPARE(PageNameFunctions::evaluate(" PAGENAME", "User:Anonymous user/sandbox/my page"), QString("Anonymous user/sandbox/my page"));
  QCOMPARE(PageNameFunctions::evaluate("PAGENAME ", "User talk:Anonymous user/sandbox/my page"), QString("Anonymous user/sandbox/my page"));
}

void PageNameFunctionsTest::pageNameE()
{
  QVERIFY(PageNameFunctions::isPageNameFunction("PAGENAMEE"));
  QCOMPARE(PageNameFunctions::evaluate("PAGENAMEE", "Help:Magic words"), QString("Magic_words"));
  QCOMPARE(PageNameFunctions::evaluate(" PAGENAMEE", "User:Anonymous user/sandbox/my page"), QString("Anonymous_user/sandbox/my_page"));
  QCOMPARE(PageNameFunctions::evaluate("PAGENAMEE ", "User talk:Anonymous user/sandbox/my page"), QString("Anonymous_user/sandbox/my_page"));
}

void PageNameFunctionsTest::basePageName()
{
  QVERIFY(PageNameFunctions::isPageNameFunction("BASEPAGENAME"));
  QCOMPARE(PageNameFunctions::evaluate("BASEPAGENAME", "Help:Magic words"), QString("Magic words"));
  QCOMPARE(PageNameFunctions::evaluate(" BASEPAGENAME", "User:Anonymous user/sandbox/my page"), QString("Anonymous user/sandbox"));
  QCOMPARE(PageNameFunctions::evaluate("BASEPAGENAME ", "User talk:Anonymous user/sandbox/my page"), QString("Anonymous user/sandbox"));
}

void PageNameFunctionsTest::basePageNameE()
{
  QVERIFY(PageNameFunctions::isPageNameFunction("BASEPAGENAMEE"));
  QCOMPARE(PageNameFunctions::evaluate("BASEPAGENAMEE", "Help:Magic words"), QString("Magic_words"));
  QCOMPARE(PageNameFunctions::evaluate(" BASEPAGENAMEE", "User:Anonymous user/sandbox/my page"), QString("Anonymous_user/sandbox"));
  QCOMPARE(PageNameFunctions::evaluate("BASEPAGENAMEE ", "User talk:Anonymous user/sandbox/my page"), QString("Anonymous_user/sandbox"));
}

void PageNameFunctionsTest::subPageName()
{
  QVERIFY(PageNameFunctions::isPageNameFunction("SUBPAGENAME"));
  QCOMPARE(PageNameFunctions::evaluate("SUBPAGENAME", "Help:Magic words"), QString("Magic words"));
  QCOMPARE(PageNameFunctions::evaluate(" SUBPAGENAME", "User:Anonymous user/sandbox/my page"), QString("my page"));
  QCOMPARE(PageNameFunctions::evaluate("SUBPAGENAME ", "User talk:Anonymous user/sandbox/my page"), QString("my page"));
}

void PageNameFunctionsTest::subPageNameE()
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

void PageNameFunctionsTest::fullPageName()
{
  QVERIFY(PageNameFunctions::isPageNameFunction("FULLPAGENAME"));
  QCOMPARE(PageNameFunctions::evaluate("FULLPAGENAME", "Help:Magic words"), QString("Help:Magic words"));
  QCOMPARE(PageNameFunctions::evaluate(" FULLPAGENAME", "User:Anonymous user/sandbox/my page"), QString("User:Anonymous user/sandbox/my page"));
  QCOMPARE(PageNameFunctions::evaluate("FULLPAGENAME ", "User talk:Anonymous user/sandbox/my page"), QString("User talk:Anonymous user/sandbox/my page"));
}

void PageNameFunctionsTest::fullPageNameE()
{
  QVERIFY(PageNameFunctions::isPageNameFunction("FULLPAGENAMEE"));
  QCOMPARE(PageNameFunctions::evaluate("FULLPAGENAMEE", "Help:Magic words"), QString("Help:Magic_words"));
  QCOMPARE(PageNameFunctions::evaluate(" FULLPAGENAMEE", "User:Anonymous user/sandbox/my page"), QString("User:Anonymous_user/sandbox/my_page"));
  QCOMPARE(PageNameFunctions::evaluate("FULLPAGENAMEE ", "User talk:Anonymous user/sandbox/my page"), QString("User_talk:Anonymous_user/sandbox/my_page"));
}


void PageNameFunctionsTest::nameSpace()
{
  QVERIFY(PageNameFunctions::isPageNameFunction("NAMESPACE"));
  QCOMPARE(PageNameFunctions::evaluate("NAMESPACE", "a"), QString(""));
  QCOMPARE(PageNameFunctions::evaluate("NAMESPACE", "Help:Magic words"), QString("Help"));
  QCOMPARE(PageNameFunctions::evaluate(" NAMESPACE", "User:Anonymous user/sandbox/my page"), QString("User"));
  QCOMPARE(PageNameFunctions::evaluate("NAMESPACE ", "User talk:Anonymous user/sandbox/my page"), QString("User talk"));
}

void PageNameFunctionsTest::nameSpaceE()
{
  QVERIFY(PageNameFunctions::isPageNameFunction("NAMESPACEE"));
  QCOMPARE(PageNameFunctions::evaluate("NAMESPACEE", "Help:Magic words"), QString("Help"));
  QCOMPARE(PageNameFunctions::evaluate(" NAMESPACEE", "User:Anonymous user/sandbox/my page"), QString("User"));
  QCOMPARE(PageNameFunctions::evaluate("NAMESPACEE ", "User talk:Anonymous user/sandbox/my page"), QString("User_talk"));
}

QTEST_APPLESS_MAIN(PageNameFunctionsTest)
#include "pagenamefunctionstest.moc"
