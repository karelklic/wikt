/* This file is part of Wikt.
 * Originally written 2004 by Timwi.
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
#include <libwikt/parser/listparser.h>
#include <QTest>
#include <QObject>

/// Tests that a parser handles list tasks properly.
class ListParserTest : public QObject
{
  Q_OBJECT
private slots:
  void parseListItems();
};

//===========================================================================
void ListParserTest::parseListItems()
{
}

/*QString input =
  "Here's a ''definition list'':\n"
  "; Word : Definition of the word\n"
  "; A longer phrase needing definition\n"
  ": Phrase defined\n"
  "; A word : Which has a definition\n"
  ": Also a second one\n"
  ": And even a third\n";
//BisonParser parser("definitionList", input);
//Node *result = parser.parse();
//QCOMPARE(result->count(), 2);*/

QTEST_APPLESS_MAIN(ListParserTest)
#include "listparsertest.moc"
