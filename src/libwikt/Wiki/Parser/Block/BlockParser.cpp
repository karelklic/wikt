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
#include "BlockParser.h"
#include "../Heading/HeadingParser.h"
#include "../Paragraph/ParagraphParser.h"
#include "../List/ListParser.h"
#include "../Table/TableParser.h"
#include "../Html/BlockHtmlParser.h"

//===========================================================================
void BlockParser::parse(Node &parent, Buffer &buffer)
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
        TextTokenNode *unparsedTextNode = new TextTokenNode(unparsedText);
        parent.append(unparsedTextNode);
        unparsedText.clear();
      }

      parent.append(resultNode);
      continue;
    }

    // No node found. Eat input until a node is found.
    unparsedText.append(buffer.readChar());
  } while (!buffer.endOfFile());

  // If there is some unsuccessfully parsed text,
  // append it as text.
  if (unparsedText.length() > 0)
  {
    TextTokenNode *unparsedTextNode = new TextTokenNode(unparsedText);
    parent.append(unparsedTextNode);
  }
}

//===========================================================================
Node *BlockParser::parseCycle(Buffer &buffer)
{
  Node *node;
  if ((node = HeadingParser::parse(buffer)))
    return node;
  if ((node = ListParser::parse(buffer)))
    return node;
  if ((node = TableParser::parse(buffer)))
    return node;
  if ((node = BlockHtmlParser::parse(buffer)))
    return node;
  if ((node = ParagraphParser::parse(buffer)))
    return node;
  return 0;
}
