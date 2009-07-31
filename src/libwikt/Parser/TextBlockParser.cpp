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
#include "TextBlockParser.h"
#include "LinkParser.h"
#include "ExternalLinkParser.h"
#include "InlineHtmlParser.h"
#include "HtmlEntityParser.h"
#include "BoldItalicParser.h"

//===========================================================================
Node *parseCycle(Buffer &buffer)
{
  Node *child;
  if ((child = LinkParser::parse(buffer)))
    return child;
  if ((child = ExternalLinkParser::parse(buffer)))
    return child;
  if ((child = InlineHtmlParser::parse(buffer)))
    return child;
  if ((child = HtmlEntityParser::parse(buffer)))
    return child;
  if ((child = BoldItalicParser::parse(buffer)))
    return child;
  return 0;
}

//===========================================================================
void TextBlockParser::parse(Node &node, Buffer &buffer)
{
  if (buffer.endOfFile()) return;
  QString unparsedText;
  do {
    Node *resultNode = parseCycle(buffer);
    if (resultNode)
    {
      // If there is some unsuccessfully parsed text,
      // append it as text before the resultant node.
      if (unparsedText.length() > 0)
      {
        TextTokenNode *unparsedTextNode =
          new TextTokenNode(unparsedText);
        node.append(unparsedTextNode);
        unparsedText.clear();
      }

      node.append(resultNode);
      continue;
    }

    // No node found. Eat input until a node is found.
    unparsedText.append(buffer.readChar());
  } while (!buffer.endOfFile());

  // If there is some unsuccessfully parsed text,
  // append it as text
  if (unparsedText.length() > 0)
  {
    TextTokenNode *unparsedTextNode =
      new TextTokenNode(unparsedText);
    node.append(unparsedTextNode);
  }
}
