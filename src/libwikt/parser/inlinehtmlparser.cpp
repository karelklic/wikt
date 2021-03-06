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
#include "textblockparser.h"
#include "../unicode.h"

HtmlElementNode *InlineHtmlParser::parse(Buffer &buffer)
{
  if (buffer.endOfFile()) return 0;
  // To make it faster for the most common case.
  if (buffer.nextChar() != '<') return 0;

  // Allowed inline paired HTML tags.
  // Sorted alphabetically.
  #define allowedPairedTagCount (sizeof(allowedPairedTags) / sizeof(QString))
  static QString allowedPairedTags[] =
  {
    "b",
    "big",
    "cite",
    "caption",
    "cite",
    "code",
    "del",
    "em",
    "font",
    "i",
    "ins",
    "s",
    "small",
    "span",
    "strike",
    "strong",
    "sub",
    "sup",
    "tt",
    "u",
    "var"
  };
  for (unsigned i = 0; i < allowedPairedTagCount; ++i)
  {
    HtmlElementNode *node = parsePaired(buffer, allowedPairedTags[i]);
    if (node) return node;
  }

  // Try nonpaired tags.
  #define allowedNonpairedTagCount (sizeof(allowedNonpairedTags) / sizeof(QString))
  static QString allowedNonpairedTags[] = { "nowiki", "br" };
  for (unsigned i = 0; i < allowedNonpairedTagCount; ++i)
  {
    HtmlElementNode *node = parseNonpaired(buffer, allowedNonpairedTags[i]);
    if (node) return node;
  }

  return 0;
}

HtmlElementNode *InlineHtmlParser::parsePaired(Buffer &buffer, const QString &tag)
{
  // This method is optimized, because it was a major performance bottleneck
  // of whole parser.

  // Buffer too short. 2 = "<>"
  if (buffer.pos() + 2 + tag.length() > buffer.size())
    return 0;

  int res = Unicode::ucstricmp(
    ((const ushort*)buffer.text().unicode()) + buffer.pos() + 1, 
    ((const ushort*)buffer.text().unicode()) + buffer.pos() + 1 + tag.length(),
    ((const ushort*)tag.unicode()), 
    ((const ushort*)tag.unicode()) + tag.length());

  // Ensure the text does contain current allowedTag.
  if (res != 0) 
    return 0;

  // Ensure the tag name is not just a part of a word,
  // but it is standalone.
  if (buffer.text()[buffer.pos() + tag.length() + 1] != '>' && buffer.text()[buffer.pos() + tag.length() + 1] != ' ')
    return 0;

  // Ensure there is a closing > and it is before another <.
  int openTagLength = -1;
  QString openTagParams;
  int openTagStartParams = buffer.pos() + tag.length() + 1;
  for (int k = openTagStartParams; k < buffer.size(); ++k)
  {
    if (buffer.text()[k] == '>')
    {
      openTagLength = k + 1 - buffer.pos();
      openTagParams = buffer.text().mid(openTagStartParams, k - openTagStartParams);
      break;
    }
    if (buffer.text()[k] == '<')
      return 0;
  }

  if (openTagLength == -1)
    return 0;

  /* Very slow.
  QString openExpr = QString("^<%1([ ]*| ([^<>]+))>").arg(tag);
  QRegExp open(openExpr, Qt::CaseInsensitive);
  int pos = open.indexIn(buffer.text(), buffer.pos(), QRegExp::CaretAtOffset);
  if (pos != buffer.pos()) return 0;
  */

  // find the right closing tag.
  int closingTagLength;
  int closing = indexOfClosingTag(buffer, tag, closingTagLength);
  buffer.skip(openTagLength);

  HtmlElementNode *node = new HtmlElementNode(tag, openTagParams, true);
  // The case of no closing tag.
  if (closing == -1)
  {
    TextBlockParser::parse(*node, buffer);
    return node;
  }

  // Closing tag present.
  Buffer insideBuffer(buffer.read(closing - buffer.pos()));
  TextBlockParser::parse(*node, insideBuffer);
  buffer.skip(closingTagLength);
  return node;
}

HtmlElementNode *InlineHtmlParser::parseNonpaired(Buffer &buffer,
    const QString &tag)
{
  QString expr = QString("^<%1([ ]*| ([^<>/]+))/?>").arg(tag);
  QRegExp ex(expr, Qt::CaseInsensitive);
  int pos = ex.indexIn(buffer.text(), buffer.pos(), QRegExp::CaretAtOffset);
  if (pos != buffer.pos())
    return 0;

  buffer.skip(ex.matchedLength());
  return new HtmlElementNode(tag, ex.cap(2), false);
}

int InlineHtmlParser::indexOfClosingTag(Buffer &buffer, const QString &tag,
    int &closingTagLength)
{
  QString openNextExpr = QString("<%1([ ]*| [^<>]+)>").arg(tag);
  QRegExp openNext(openNextExpr, Qt::CaseInsensitive);
  QString closeExpr = QString("</%1[ ]*>").arg(tag);
  QRegExp close(closeExpr);

  // handle nested tags
  int posNext = buffer.pos(), posEnd = buffer.pos();
  do {
    posNext = openNext.indexIn(buffer.text(), posNext + 1, QRegExp::CaretAtOffset);
    posEnd = close.indexIn(buffer.text(), posEnd + 1, QRegExp::CaretAtOffset);
    if (posNext == -1) break;
    if (posEnd == -1) break;
  } while (posNext < posEnd);

  if (posEnd != -1)
    closingTagLength = close.matchedLength();

  return posEnd;
}
