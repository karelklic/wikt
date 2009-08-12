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
#include <libwikt/parser/tableparser.h>
#include <QTest>
#include <QObject>

/// Tests TableParser class.
class TableParserTest : public QObject
{
  Q_OBJECT
private slots:
  void simplestTable();
  void simplestTableWithHeader();
};

//===========================================================================
void TableParserTest::simplestTable()
{
  Buffer input("{|\n|-\n| A\n| B\n|-\n| C\n| D\n|}");
  TableNode *result = TableParser::parse(input);
  QVERIFY(result);
  QCOMPARE(result->count(), 2);
  QCOMPARE(result->child(0)->type(), Node::TableRow);
  QCOMPARE(result->child(0)->count(), 2);
  QCOMPARE(result->child(0)->child(0)->type(), Node::TableCell);
  QCOMPARE(result->child(0)->child(0)->toText(), QString("A"));
  QCOMPARE(result->child(0)->child(1)->type(), Node::TableCell);
  QCOMPARE(result->child(1)->type(), Node::TableRow);
  QCOMPARE(result->child(1)->count(), 2);
  delete result;
}

//===========================================================================
void TableParserTest::simplestTableWithHeader()
{
  Buffer input("{|\n|-\n! header1\n| A\n| B\n|-\n! header2\n| C\n| D\n|}");
  TableNode *result = TableParser::parse(input);
  QVERIFY(result);
  QCOMPARE(result->count(), 2);
  QCOMPARE(result->child(0)->type(), Node::TableRow);
  QCOMPARE(result->child(0)->count(), 3);
  QCOMPARE(result->child(0)->child(0)->type(), Node::TableHead);
  QCOMPARE(result->child(0)->child(1)->type(), Node::TableCell);
  QCOMPARE(result->child(0)->child(1)->toText(), QString("A"));
  QCOMPARE(result->child(0)->child(2)->type(), Node::TableCell);
  QCOMPARE(result->child(1)->type(), Node::TableRow);
  QCOMPARE(result->child(1)->count(), 3);
  delete result;
}

QTEST_APPLESS_MAIN(TableParserTest)
#include "tableparsertest.moc"
