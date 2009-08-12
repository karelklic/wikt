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
#include <libwikt/parser/linkparser.h>
#include <QTest>
#include <QObject>

/// Tests LinkParser.
class LinkParserTest : public QObject
{
  Q_OBJECT
private slots:
  void simpleLink();
  void mediaLink();
  void linkWithSpace();
  void linkWithSlash();
};

//===========================================================================
void LinkParserTest::simpleLink()
{
  Buffer buffer("[[simple]] ");
  LinkNode *result = LinkParser::parse(buffer);
  QVERIFY(result);
  QCOMPARE(buffer.pos(), 10);
  QVERIFY(!result->emptyPipeAtEnd());
  QVERIFY(!result->forcedLink());
  QCOMPARE(result->count(), 1); // link target
  QCOMPARE(result->child(0)->toText(), QString("simple"));
  delete result;
}

//===========================================================================
void LinkParserTest::mediaLink()
{
  Buffer buffer("[[:Media:Cs-myslet.ogg|audio]]");
  LinkNode *result = LinkParser::parse(buffer);
  QVERIFY(result);
  QVERIFY(buffer.endOfFile());
  QVERIFY(!result->emptyPipeAtEnd());
  QVERIFY(result->forcedLink());
  QCOMPARE(result->count(), 2); // link target and option
  QCOMPARE(result->child(0)->toText(), QString("Media:Cs-myslet.ogg"));
  delete result;
}

//===========================================================================
void LinkParserTest::linkWithSpace()
{
  Buffer buffer("[[ Category: Czech nouns ]]");
  LinkNode *result = LinkParser::parse(buffer);
  QVERIFY(result);
  QVERIFY(buffer.endOfFile());
  QVERIFY(!result->emptyPipeAtEnd());
  QVERIFY(!result->forcedLink());
  QCOMPARE(result->count(), 1);
  QCOMPARE(result->child(0)->toText(), QString("Category: Czech nouns"));
  delete result;
}

//===========================================================================
void LinkParserTest::linkWithSlash()
{
  Buffer buffer("[[Wikisaurus:penis/more]]");
  LinkNode *result = LinkParser::parse(buffer);
  QVERIFY(result);
  QVERIFY(buffer.endOfFile());
  QVERIFY(!result->emptyPipeAtEnd());
  QVERIFY(!result->forcedLink());
  QCOMPARE(result->count(), 1);
  QCOMPARE(result->child(0)->toText(), QString("Wikisaurus:penis/more"));
  delete result;
}

QTEST_APPLESS_MAIN(LinkParserTest)
#include "linkparsertest.moc"
