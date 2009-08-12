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
#include <libwikt/parser/bolditalicparser.h>
#include <QTest>
#include <QObject>

/// Tests BoldItalicParser.
class BoldItalicParserTest : public QObject
{
  Q_OBJECT
private slots:
  /// "''abc'''d'''''"
  void embedded0();
  /// "'''abc''d'''''"
  void embedded1();
  /// "'''abc ''d'' '''"
  void embedded2();
  /// "'''''abc''d'''"
  void embedded3();
  /// "'''''abc'''d''"
  void embedded4();
  /// "'''''abc''''' not parsed"
  void embedded5();
  /// "''italic'''''bold'''"
  void embedded6();
};

//===========================================================================
void BoldItalicParserTest::embedded0()
{
  Buffer buffer("''abc'''d'''''");
  Node *result = BoldItalicParser::parse(buffer);
  QVERIFY(result);
  QCOMPARE(result->type(), Node::Italics);
  QCOMPARE(result->count(), 2);
  QCOMPARE(result->child(0)->type(), Node::TextToken);
  QCOMPARE(result->child(0)->toText(), QString("abc"));
  QCOMPARE(result->child(1)->type(), Node::Bold);
  QCOMPARE(result->child(1)->toText(), QString("d"));
  delete result;
}

//===========================================================================
void BoldItalicParserTest::embedded1()
{
  Buffer buffer("'''abc''d'''''");
  Node *result = BoldItalicParser::parse(buffer);
  QVERIFY(result);
  QCOMPARE(result->type(), Node::Bold);
  QCOMPARE(result->count(), 2);
  QCOMPARE(result->child(0)->type(), Node::TextToken);
  QCOMPARE(result->child(0)->toText(), QString("abc"));
  QCOMPARE(result->child(1)->type(), Node::Italics);
  QCOMPARE(result->child(1)->toText(), QString("d"));
  delete result;
}

//===========================================================================
void BoldItalicParserTest::embedded2()
{
  Buffer buffer("'''abc ''d'' '''");
  Node *result = BoldItalicParser::parse(buffer);
  QVERIFY(result);
  QCOMPARE(result->type(), Node::Bold);
  QCOMPARE(result->count(), 3);
  QCOMPARE(result->child(0)->type(), Node::TextToken);
  QCOMPARE(result->child(0)->toText(), QString("abc "));
  QCOMPARE(result->child(1)->type(), Node::Italics);
  QCOMPARE(result->child(1)->toText(), QString("d"));
  QCOMPARE(result->child(2)->type(), Node::TextToken);
  QCOMPARE(result->child(2)->toText(), QString(" "));
  delete result;
}

//===========================================================================
void BoldItalicParserTest::embedded3()
{
  Buffer buffer("'''''abc''d'''");
  Node *result = BoldItalicParser::parse(buffer);
  QVERIFY(result);
  QCOMPARE(result->type(), Node::Bold);
  QCOMPARE(result->count(), 2);
  QCOMPARE(result->child(0)->type(), Node::Italics);
  QCOMPARE(result->child(0)->toText(), QString("abc"));
  QCOMPARE(result->child(1)->type(), Node::TextToken);
  QCOMPARE(result->child(1)->toText(), QString("d"));
  delete result;
}

//===========================================================================
void BoldItalicParserTest::embedded4()
{
  Buffer buffer("'''''abc'''d''");
  Node *result = BoldItalicParser::parse(buffer);
  QVERIFY(result);
  QCOMPARE(result->type(), Node::Italics);
  QCOMPARE(result->count(), 2);
  QCOMPARE(result->child(0)->type(), Node::Bold);
  QCOMPARE(result->child(0)->toText(), QString("abc"));
  QCOMPARE(result->child(1)->type(), Node::TextToken);
  QCOMPARE(result->child(1)->toText(), QString("d"));
  delete result;
}

//===========================================================================
void BoldItalicParserTest::embedded5()
{
  Buffer buffer("'''''abc''''' not parsed");
  Node *result = BoldItalicParser::parse(buffer);
  QVERIFY(result);
  QCOMPARE(buffer.pos(), 13);
  QCOMPARE(result->type(), Node::Italics);
  QCOMPARE(result->count(), 1);
  QCOMPARE(result->child(0)->type(), Node::Bold);
  QCOMPARE(result->child(0)->toText(), QString("abc"));
  delete result;
}

//===========================================================================
void BoldItalicParserTest::embedded6()
{
  Buffer buffer("''italic'''''bold'''");
  Node *result = BoldItalicParser::parse(buffer);
  QVERIFY(result);
  QCOMPARE(buffer.pos(), 10);
  QCOMPARE(result->type(), Node::Italics);
  QCOMPARE(result->toText(), QString("italic"));
  delete result;
}

QTEST_APPLESS_MAIN(BoldItalicParserTest)
#include "bolditalicparsertest.moc"
