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
#include "numberedlistparser.h"
#include <QTest>
#include <QObject>

/// Tests NumberedListParser class.
class NumberedListParserTest : public QObject
{
  Q_OBJECT
private slots:
  void simpleList();
  void embeddedList();
};

//===========================================================================
void NumberedListParserTest::simpleList()
{
  Buffer buffer("# a\n# b\n# c\n");
  NumberedListNode *result = NumberedListParser::parse(buffer);
  QVERIFY(result);
  QCOMPARE(result->count(), 3);
  QCOMPARE(result->child(0)->type(), Node::ListItem);
  QCOMPARE(result->child(0)->toText(), QString("a"));
  QCOMPARE(result->child(1)->type(), Node::ListItem);
  QCOMPARE(result->child(2)->type(), Node::ListItem);
  delete result;
}

//===========================================================================
void NumberedListParserTest::embeddedList()
{
  Buffer buffer("# a\n## bb\n# c\n");
  NumberedListNode *result = NumberedListParser::parse(buffer);
  QVERIFY(result);
  QCOMPARE(result->count(), 2);
  QCOMPARE(result->child(0)->type(), Node::ListItem);
  QCOMPARE(result->child(0)->count(), 2);
  QCOMPARE(result->child(0)->child(0)->type(), Node::TextToken);
  QCOMPARE(result->child(0)->child(1)->type(), Node::NumberedList);
  QCOMPARE(result->child(1)->type(), Node::ListItem);
  delete result;
}
