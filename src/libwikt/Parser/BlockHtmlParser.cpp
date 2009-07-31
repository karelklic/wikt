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
#include "BlockHtmlParser.h"
#include "InlineHtmlParser.h"
#include "ParagraphParser.h"
#include "BlockParser.h"

// Allowed block HTML tags.
// Sorted alphabetically.
#define allowedTagCount (sizeof(allowedTags) / sizeof(QString))
static QString allowedTags[] =
{
  "blockquote",
  "center",
  "dd",
  "div",
  "dl",
  "dt",
  "h1", "h2", "h3", "h4", "h5", "h6",
  "li",
  "ol",
  "p",
  "pre",
  "table",
  "td",
  "th",
  "tr",
  "ul"
};

//===========================================================================
HtmlElementNode *BlockHtmlParser::parse(Buffer &buffer)
{
  if (buffer.endOfFile()) return 0;
  // To make it faster for the most common case.
  if (buffer.nextChar() != '<') return 0;

  for (unsigned i = 0; i < allowedTagCount; ++i)
  {
    HtmlElementNode *node = parse(buffer, allowedTags[i]);
    if (node) return node;
  }

  return 0;
}

//===========================================================================
int BlockHtmlParser::indexIn(const QString &text, int offset)
{
  int offs;
  for (unsigned i = 0; i < allowedTagCount; ++i)
  {
    QString openExpr = QString("<%1([ ]*| ([^<>]+))>").arg(allowedTags[i]);
    QRegExp open = QRegExp(openExpr, Qt::CaseInsensitive);
    if ((offs = open.indexIn(text, offset)) != -1)
      return offs;
  }

  return -1;
}

//===========================================================================
HtmlElementNode *BlockHtmlParser::parse(Buffer &buffer, const QString &tag)
{
  // Parse opening tag.
  QString openExpr = QString("^<%1([ ]*| ([^<>]+))>").arg(tag);
  QRegExp open = QRegExp(openExpr, Qt::CaseInsensitive);

  int pos = open.indexIn(buffer.text(), buffer.pos(), QRegExp::CaretAtOffset);
  if (pos != buffer.pos()) return 0;

  HtmlElementNode *node = new HtmlElementNode(tag, open.cap(2), true);

  // find the right closing tag.
  int closingTagLength;
  int closing = InlineHtmlParser::indexOfClosingTag(buffer, tag, closingTagLength);
  buffer.skip(open.matchedLength());

  // The case of no closing tag.
  if (closing == -1)
  {
    // TODO: some error message or log something.
    BlockParser::parse(*node, buffer);
    return node;
  }

  // Closing tag present.
  Buffer insideBuffer(buffer.read(closing - buffer.pos()));
  ParagraphParser::parse(*node, insideBuffer);
  BlockParser::parse(*node, insideBuffer);
  buffer.skip(closingTagLength);
  return node;
}
