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
#include "listparser.h"
#include "bulletlistparser.h"
#include "numberedlistparser.h"
#include "definitionlistparser.h"
#include "textblockparser.h"

//===========================================================================
Node *ListParser::parse(Buffer &buffer)
{
  Node *result;
  if ((result = BulletListParser::parse(buffer)))
    return result;
  if ((result = NumberedListParser::parse(buffer)))
    return result;
  if ((result = DefinitionListParser::parse(buffer)))
    return result;
  return 0;
}

//===========================================================================
Node *createItemNode(const QChar &itemNodeTypeChar)
{
  Node *itemNode = 0;
  if (itemNodeTypeChar == '*' || itemNodeTypeChar == '#')
    itemNode = new ListItemNode();
  else if (itemNodeTypeChar == ';')
    itemNode = new DefinitionListTermItemNode();
  else if (itemNodeTypeChar == ':')
    itemNode = new DefinitionListDefItemNode();
  ASSERT(itemNode);
  return itemNode;
}

//===========================================================================
void ListParser::parseListItems(QStringList &lines, Node &listNode)
{
  while (!lines.empty())
  {
    QChar itemNodeTypeChar(lines[0][0]);

    // Embedded bullet list.
    if (lines[0].length() > 1 &&
        lines[0][1] == '*')
    {
      Buffer listBuffer;
      while (!lines.empty() &&
          lines[0].length() > 1 &&
          lines[0][1] == '*')
      {
        listBuffer.append(lines[0].remove(0, 1) + '\n');
        lines.removeFirst();
      }
      Node *insideItemNode = BulletListParser::parse(listBuffer);
      ASSERT(insideItemNode);
      if (listNode.count() == 0)
        listNode.append(createItemNode(itemNodeTypeChar));
      listNode.last()->append(insideItemNode);
    }
    // Embedded numbered list.
    else if (lines[0].length() > 1 &&
        lines[0][1] == '#')
    {
      Buffer listBuffer;
      while (!lines.empty() &&
          lines[0].length() > 1 &&
          lines[0][1] == '#')
      {
        listBuffer.append(lines[0].remove(0, 1) + '\n');
        lines.removeFirst();
      }
      Node *insideItemNode = NumberedListParser::parse(listBuffer);
      ASSERT(insideItemNode);
      if (listNode.count() == 0)
        listNode.append(createItemNode(itemNodeTypeChar));
      listNode.last()->append(insideItemNode);
    }
    // Embedded definition list.
    else if (lines[0].length() > 1 &&
        (lines[0][1] == ';' || lines[0][1] == ':'))
    {
      Buffer listBuffer;
      while (!lines.empty() &&
          lines[0].length() > 1 &&
          (lines[0][1] == ';' || lines[0][1] == ':'))
      {
        listBuffer.append(lines[0].remove(0, 1) + '\n');
        lines.removeFirst();
      }
      Node *insideItemNode = DefinitionListParser::parse(listBuffer);
      ASSERT(insideItemNode);
      if (listNode.count() == 0)
        listNode.append(createItemNode(itemNodeTypeChar));
      listNode.last()->append(insideItemNode);
    }
    // Just a line of text.
    else
    {
      Buffer textBuffer(lines[0].remove(0, 1).trimmed());
      lines.removeFirst();

      // Only add list item if it is not empty. MediaWiki does the same.
      if (textBuffer.text().length() > 0)
      {
        listNode.append(createItemNode(itemNodeTypeChar));
        TextBlockParser::parse(*listNode.last(), textBuffer);
      }
    }
  }
}
