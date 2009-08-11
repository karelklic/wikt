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
#include "inlinehtmlparser.h"
#include <QTest>
#include <QObject>

/// Tests InlineHtmlParser.
class InlineHtmlParserTest : public QObject
{
  Q_OBJECT
private slots:
  void emptySpan();
  void spanWithAttributes();
  /// Test the indexOfClosingTag method on all inputs.
  void indexOfClosingTag();
  /// Test the parsing of <br clear="left" />
  void brTag();
};

//===========================================================================
void InlineHtmlParserTest::emptySpan()
{
  Buffer buffer("<span></span>");
  HtmlElementNode *result = InlineHtmlParser::parsePaired(buffer, "span");
  QVERIFY(result);
  QVERIFY(buffer.endOfFile());
  delete result;
}
//===========================================================================
void InlineHtmlParserTest::spanWithAttributes()
{
  Buffer buffer("<span id=\"tmp\">a</span>");
  HtmlElementNode *result = InlineHtmlParser::parsePaired(buffer, "span");
  QVERIFY(result);
  QVERIFY(buffer.endOfFile());
  delete result;
}

//===========================================================================
void InlineHtmlParserTest::indexOfClosingTag()
{
  // Simple open and close.
  Buffer buffer("<span id=\"tmp\">a</span>");
  int closingTagLength;
  int closing = InlineHtmlParser::indexOfClosingTag(buffer, "span",
      closingTagLength);
  QCOMPARE(closing, 16);
  QCOMPARE(closingTagLength, QString("</span>").length());

  // Embedded one more tag.
  buffer = Buffer("<span><span>a</span></span>");
  closing = InlineHtmlParser::indexOfClosingTag(buffer, "span",
      closingTagLength);
  QCOMPARE(closing, 20);
  QCOMPARE(closingTagLength, QString("</span>").length());

  // Embedded two tags.
  buffer = Buffer("<span><span><span>a</span></span></span>");
  closing = InlineHtmlParser::indexOfClosingTag(buffer, "span",
      closingTagLength);
  QCOMPARE(closing, 33);
  QCOMPARE(closingTagLength, QString("</span>").length());
}

//===========================================================================
void InlineHtmlParserTest::brTag()
{
  Buffer buffer("<br clear=\"left\" />");
  HtmlElementNode *node = InlineHtmlParser::parseNonpaired(buffer, "br");
  QVERIFY(node);
  QCOMPARE(node->paired(), false);
  QCOMPARE(node->params(), QString("clear=\"left\""));
  delete node;
}
