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
#include "blockhtmlparser.h"
#include "inlinehtmlparser.h"
#include "paragraphparser.h"
#include "blockparser.h"
#include "../unicode.h"

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

int BlockHtmlParser::indexIn(const QString &text, int offset)
{
  // This method is the slowest point of whole parser, so it must be 
  // optimized as much as possible.

  // "- 2" because the smallest tag has 3 characters '<x>'.
  for (int i = offset; i < text.length() - 2; ++i) 
  {
    if (text[i] != '<') continue;

    for (unsigned j = 0; j < allowedTagCount; ++j)
    {
      const QString &tag = allowedTags[j];
      if (i + tag.length() + 1 >= text.length()) 
	continue;

      int res = Unicode::ucstricmp(
        ((const ushort*)text.unicode()) + i + 1, 
        ((const ushort*)text.unicode()) + i + 1 + tag.length(),
        ((const ushort*)tag.unicode()), 
        ((const ushort*)tag.unicode()) + tag.length());

      // Ensure the text does contain current allowedTag.
      if (res != 0) 
	continue;

      // Ensure the tag name is not just a part of a word,
      // but it is standalone.
      if (text[i + tag.length() + 1] != '>' && text[i + tag.length() + 1] != ' ')
	continue;

      // Ensure there is a closing > and it is before another <.
      for (int k = i + tag.length() + 1; k < text.length(); ++k)
      {
	if (text[k] == '>')
	  return i;
	if (text[k] == '<')
	  break;
      }
    }
  }

  return -1;

/* Slow short wrong implementation.
  int offs;
  for (unsigned i = 0; i < allowedTagCount; ++i)
  {
    QString openExpr = QString("<%1([ ]*| ([^<>]+))>").arg(allowedTags[i]);
    QRegExp open = QRegExp(openExpr, Qt::CaseInsensitive);
    if ((offs = open.indexIn(text, offset)) != -1)
      return offs;
  }

  return -1;
*/
}

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
