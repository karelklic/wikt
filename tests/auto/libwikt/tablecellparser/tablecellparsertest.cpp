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
#include "tablecellparser.h"
#include <QTest>
#include <QObject>

/// Tests TableCellParser class.
class TableCellParserTest : public QObject
{
  Q_OBJECT
private slots:
  void simpleCells();
  void simpleAttribCells();
  void oneLineCells();
  void multilineCell();
  void embeddedTable();
};

//===========================================================================
void TableCellParserTest::simpleCells()
{
  Buffer buffer("| a\n| b\n|-");
  TableCellNode *result = TableCellParser::parse(buffer);
  QVERIFY(result);
  QCOMPARE(result->count(), 1);
  QCOMPARE(result->toText(), QString("a"));
  delete result;

  result = TableCellParser::parse(buffer);
  QVERIFY(result);
  QCOMPARE(result->toText(), QString("b"));
  delete result;
}

//===========================================================================
void TableCellParserTest::simpleAttribCells()
{
  Buffer buffer("|bgcolor=\"#F8F8FF\" valign=top| [[vymyslet]]\n|\n");
  TableCellNode *result = TableCellParser::parse(buffer);
  QVERIFY(result);
  QVERIFY(result->count() > 1);
  QCOMPARE(result->child(0)->type(), Node::AttributeGroup);
  QCOMPARE(result->child(0)->count(), 2);
  delete result;
}

//===========================================================================
void TableCellParserTest::oneLineCells()
{
  Buffer buffer("| a || b || c\n|-\n");
  TableCellNode *result = TableCellParser::parse(buffer);
  QVERIFY(result);
  //QCOMPARE(result->type(), Node::TextToken);
  QCOMPARE(result->toText(), QString("a"));
  delete result;

  result = TableCellParser::parse(buffer);
  QVERIFY(result);
  QCOMPARE(result->toText(), QString("b"));
  delete result;

  result = TableCellParser::parse(buffer);
  QVERIFY(result);
  QCOMPARE(result->toText(), QString("c"));
  delete result;
}

//===========================================================================
void TableCellParserTest::multilineCell()
{
  Buffer buffer(
      " |\n"
      "<div>\n"
      "embedded\n"
      "</div>\n"
      " |}\n");
  TableCellNode *result = TableCellParser::parse(buffer);
  QVERIFY(result);
  QCOMPARE(result->toText().trimmed(), QString("embedded"));
  delete result;
}

//===========================================================================
void TableCellParserTest::embeddedTable()
{
  Buffer buffer(
      " |\n"
      "<div>\n"
      "{|\n"
      " |embedded\n"
      " |}\n"
      "</div>\n"
      "inside\n"
      " |}\n");
  TableCellNode *result = TableCellParser::parse(buffer);
  QVERIFY(result);
  QCOMPARE(result->toText().simplified(), QString("embedded inside"));
  delete result;
}
