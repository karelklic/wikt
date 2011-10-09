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
#include "parsertest.h"
#include <libwikt/parser/buffer.h>
#include <libwikt/parser/blockhtmlparser.h>
#include <libwikt/parser/bolditalicparser.h>
#include <libwikt/parser/bulletlistparser.h>
#include <libwikt/parser/htmlentityparser.h>
#include <libwikt/parser/inlinehtmlparser.h>
#include <libwikt/parser/linkparser.h>
#include <libwikt/parser/numberedlistparser.h>
#include <libwikt/parser/paragraphparser.h>
#include <libwikt/parser/tablecellparser.h>
#include <libwikt/parser/tableparser.h>

void ParserTest::buffer_read()
{
  // Test reading 0 bytes.
  Buffer buffer("alfa beta");
  QCOMPARE(buffer.read(0), QString(""));
  QCOMPARE(buffer.pos(), 0);
}

void ParserTest::buffer_nextLine()
{
  Buffer buffer("* a\n* b\n* c\n");
  QCOMPARE(buffer.nextLine(), QString("* a"));
}

void ParserTest::buffer_readLine()
{
  Buffer buffer("* a\n* b\n* c\n");
  QCOMPARE(buffer.readLine(), QString("* a"));
  QCOMPARE(buffer.readLine(), QString("* b"));
  QCOMPARE(buffer.readLine(), QString("* c"));
}

void ParserTest::blockHtmlParser_indexIn()
{
  QCOMPARE(BlockHtmlParser::indexIn("", 0), -1);
  QCOMPARE(BlockHtmlParser::indexIn("0123456789", 0), -1);
  QCOMPARE(BlockHtmlParser::indexIn("text <div>a new div</div>", 0), 5);
  QCOMPARE(BlockHtmlParser::indexIn("text <div2>a new div</div>", 0), -1);
  QCOMPARE(BlockHtmlParser::indexIn("text <div id=\"a\">div</div>", 2), 5);
  QCOMPARE(BlockHtmlParser::indexIn("text <td rowspan=\"3\" style=\"font-size:250%;border:1px solid black;background:white;text-align:center;vertical-align:middle;width:50px;font-family:Times New Roman, Times;\">10<sup>9</sup></td>", 0), 5);
}

void ParserTest::boldItalic_embedded0()
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

void ParserTest::boldItalic_embedded1()
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

void ParserTest::boldItalic_embedded2()
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

void ParserTest::boldItalic_embedded3()
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

void ParserTest::boldItalic_embedded4()
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

void ParserTest::boldItalic_embedded5()
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

void ParserTest::boldItalic_embedded6()
{
  Buffer buffer("''italic'''''bold'''");
  Node *result = BoldItalicParser::parse(buffer);
  QVERIFY(result);
  QCOMPARE(buffer.pos(), 10);
  QCOMPARE(result->type(), Node::Italics);
  QCOMPARE(result->toText(), QString("italic"));
  delete result;
}

void ParserTest::bulletList_simpleList()
{
  Buffer buffer("* a\n* b\n* c\n");
  BulletListNode *result = BulletListParser::parse(buffer);
  QVERIFY(result);
  QCOMPARE(result->count(), 3);
  QCOMPARE(result->child(0)->type(), Node::ListItem);
  QCOMPARE(result->child(0)->toText(), QString("a"));
  QCOMPARE(result->child(1)->type(), Node::ListItem);
  QCOMPARE(result->child(2)->type(), Node::ListItem);
  delete result;
}

void ParserTest::bulletList_embeddedList()
{
  Buffer buffer("* a\n** bb\n* c\n");
  BulletListNode *result = BulletListParser::parse(buffer);
  QVERIFY(result);
  QCOMPARE(result->count(), 2);
  QCOMPARE(result->child(0)->type(), Node::ListItem);
  QCOMPARE(result->child(0)->count(), 2);
  QCOMPARE(result->child(0)->child(0)->type(), Node::TextToken);
  QCOMPARE(result->child(0)->child(1)->type(), Node::BulletList);
  QCOMPARE(result->child(1)->type(), Node::ListItem);
  delete result;
}

void ParserTest::htmlEntity_nbsp()
{
  Buffer buffer("&nbsp;");
  HtmlEntityNode *result = HtmlEntityParser::parse(buffer);
  QVERIFY(result);
  QVERIFY(buffer.endOfFile());
  delete result;
}

void ParserTest::inlineHtml_emptySpan()
{
  Buffer buffer("<span></span>");
  HtmlElementNode *result = InlineHtmlParser::parsePaired(buffer, "span");
  QVERIFY(result);
  QVERIFY(buffer.endOfFile());
  delete result;
}
void ParserTest::inlineHtml_spanWithAttributes()
{
  Buffer buffer("<span id=\"tmp\">a</span>");
  HtmlElementNode *result = InlineHtmlParser::parsePaired(buffer, "span");
  QVERIFY(result);
  QVERIFY(buffer.endOfFile());
  delete result;
}

void ParserTest::inlineHtml_indexOfClosingTag()
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

void ParserTest::inlineHtml_brTag()
{
  Buffer buffer("<br clear=\"left\" />");
  HtmlElementNode *node = InlineHtmlParser::parseNonpaired(buffer, "br");
  QVERIFY(node);
  QCOMPARE(node->paired(), false);
  QCOMPARE(node->params(), QString("clear=\"left\""));
  delete node;
}


void ParserTest::link_simple()
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

void ParserTest::link_media()
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

void ParserTest::link_withSpace()
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

void ParserTest::link_withSlash()
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

/* ListParser:
 QString input =
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


void ParserTest::numberedList_simple()
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

void ParserTest::numberedList_embedded()
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

void ParserTest::paragraph_startingWithLink()
{
  Buffer buffer("[[simple]] ");
  ParagraphNode *result = ParagraphParser::parse(buffer);
  QVERIFY(result);
}

void ParserTest::paragraph_simple()
{
  Node node(Node::Paragraph);
  Buffer buffer("a\n");
  bool success = ParagraphParser::parse(node, buffer);
  QVERIFY(success);
  QCOMPARE(node.count(), 1);
  QCOMPARE(node.toText(), QString("a"));
}

void ParserTest::tableCell_simpleCells()
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

void ParserTest::tableCell_simpleAttribCells()
{
  Buffer buffer("|bgcolor=\"#F8F8FF\" valign=top| [[vymyslet]]\n|\n");
  TableCellNode *result = TableCellParser::parse(buffer);
  QVERIFY(result);
  QVERIFY(result->count() > 1);
  QCOMPARE(result->child(0)->type(), Node::AttributeGroup);
  QCOMPARE(result->child(0)->count(), 2);
  delete result;
}

void ParserTest::tableCell_oneLineCells()
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

void ParserTest::tableCell_multilineCell()
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

void ParserTest::tableCell_embeddedTable()
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

void ParserTest::table_simplest()
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

void ParserTest::table_simpleWithHeader()
{
  Buffer input("{|\n|-\n! header1\n| A\n| B\n|-\n! header2\n| C\n| D\n|}");
  TableNode *result = TableParser::parse(input);
  QVERIFY(result);
  QCOMPARE(result->count(), 2); // rows
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

void ParserTest::table_withTd()
{
  Buffer input("{|\n|-\n<td>B</td>\n|}");
  TableNode *result = TableParser::parse(input);
  QVERIFY(result);
  QCOMPARE(result->count(), 1); // rows
  QCOMPARE(result->child(0)->type(), Node::TableRow);
  QCOMPARE(result->child(0)->count(), 1);
  //cstdout(QString::number((int)result->child(0)->child(0)->type()));
  QCOMPARE(result->child(0)->child(0)->type(), Node::HtmlElement);
  QCOMPARE(result->child(0)->child(0)->toText(), QString("B"));
}

QTEST_APPLESS_MAIN(ParserTest)
