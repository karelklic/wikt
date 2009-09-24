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
#include <libwikt/parser/blockhtmlparser.h>
#include <QTest>
#include <QObject>

class BlockHtmlParserTest : public QObject
{
  Q_OBJECT
private slots:
  void indexIn();
};

//===========================================================================
void BlockHtmlParserTest::indexIn()
{
  QCOMPARE(BlockHtmlParser::indexIn("", 0), -1);
  QCOMPARE(BlockHtmlParser::indexIn("0123456789", 0), -1);
  QCOMPARE(BlockHtmlParser::indexIn("text <div>a new div</div>", 0), 5);
  QCOMPARE(BlockHtmlParser::indexIn("text <div2>a new div</div>", 0), -1);
  QCOMPARE(BlockHtmlParser::indexIn("text <div id=\"a\">div</div>", 2), 5);
  QCOMPARE(BlockHtmlParser::indexIn("text <td rowspan=\"3\" style=\"font-size:250%;border:1px solid black;background:white;text-align:center;vertical-align:middle;width:50px;font-family:Times New Roman, Times;\">10<sup>9</sup></td>", 0), 5);
}

QTEST_APPLESS_MAIN(BlockHtmlParserTest)
#include "blockhtmlparsertest.moc"
