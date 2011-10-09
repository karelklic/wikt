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
#include <namespaceurlfunctions.h>
#include <QTest>
#include <QObject>

/// Tests NamespaceUrlFunctions methods.
class NamespaceUrlFunctionsTest : public QObject
{
  Q_OBJECT
private slots:
  void ns();
  void fullUrl();
  void urlencode();
};

void NamespaceUrlFunctionsTest::ns()
{
  QVERIFY(NamespaceUrlFunctions::isFunction("ns:2"));
  QCOMPARE(NamespaceUrlFunctions::evaluate("ns:2"), QString("User"));
  QCOMPARE(NamespaceUrlFunctions::evaluate("ns:template"), QString("Template"));
  QCOMPARE(NamespaceUrlFunctions::evaluate("ns:4"), QString("Wiktionary"));
  QCOMPARE(NamespaceUrlFunctions::evaluate("ns:project"), QString("Wiktionary"));
}

void NamespaceUrlFunctionsTest::fullUrl()
{
  QVERIFY(NamespaceUrlFunctions::isFunction("fullurl:a"));
  QCOMPARE(NamespaceUrlFunctions::evaluate("fullurl:a"), QString("entry://a"));
  QCOMPARE(NamespaceUrlFunctions::evaluate("fullurl:w:a"), QString("http://en.wikipedia.org/wiki/a"));
  QCOMPARE(NamespaceUrlFunctions::evaluate("fullurl:b:a b"), QString("http://en.wikibooks.org/wiki/a%20b"));
  QCOMPARE(NamespaceUrlFunctions::evaluate(QString::fromWCharArray(L"fullurl:w:háček")), QString("http://en.wikipedia.org/wiki/h%C3%A1%C4%8Dek"));
}

void NamespaceUrlFunctionsTest::urlencode()
{
  QVERIFY(NamespaceUrlFunctions::isFunction("urlencode:a"));
  QCOMPARE(NamespaceUrlFunctions::evaluate("urlencode:a"), QString("a"));
  QCOMPARE(NamespaceUrlFunctions::evaluate("urlencode:a a"), QString("a+a"));
  QCOMPARE(NamespaceUrlFunctions::evaluate("urlencode: a a "), QString("a+a"));
  QCOMPARE(NamespaceUrlFunctions::evaluate("urlencode:a+A"), QString("a%2BA"));
  QCOMPARE(NamespaceUrlFunctions::evaluate("urlencode:a/:a"), QString("a%2F%3Aa"));
  QCOMPARE(NamespaceUrlFunctions::evaluate("urlencode:Hello world ~;(*)&"), QString("Hello+world+%7E%3B%28%2A%29%26"));
}

QTEST_APPLESS_MAIN(NamespaceUrlFunctionsTest)
#include "namespaceurlfunctionstest.moc"
