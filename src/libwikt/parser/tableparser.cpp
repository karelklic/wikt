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
#include "tableparser.h"
#include "tablerowparser.h"
#include "tablecellparser.h"
#include "tablecaptionparser.h"
#include "tableheadparser.h"

TableNode *TableParser::parse(Buffer &buffer)
{
  if (buffer.endOfFile()) return 0;
  QString line = buffer.nextLine();
  QRegExp startTable("^\\{\\|[ ]*");
  if (startTable.indexIn(line, 0) == -1) return 0;

  line.remove(0, startTable.matchedLength());
  buffer.skip(startTable.matchedLength());

  TableNode *tableNode = new TableNode();

  // Parse the initial line as it maybe contain attributes.
  AttributeGroupNode *groupNode = parseAttributes(line);
  if (groupNode)
    tableNode->append(groupNode);
  buffer.skip(line.length() + 1);

  // The first line is handled, now parse the following lines.
  QString unparsedText;
  TableRowNode *defaultRowNode = 0;
  do {
    // Check if we reached the end of the table.
    // If it is so, break the loop and exit.
    line = buffer.nextLine();
    QRegExp end("^ *\\|\\} *");
    int pos;
    if ((pos = end.indexIn(line, 0)) == 0)
    {
      buffer.skip(end.matchedLength());
      buffer.skipEmptyLines();
      break;
    }

    // table row
    Node *node = TableRowParser::parse(buffer);
    if (node)
    {
      if (defaultRowNode)
      {
        tableNode->append(defaultRowNode);
        // Do not delete it, because now it is owned by tableNode.
        // Just null the pointer, so next lost cells are handled in
        // a new row.
        defaultRowNode = 0;
      }
      tableNode->append(node);
      continue;
    }

    // table caption
    node = TableCaptionParser::parse(buffer);
    if (node)
    {
      tableNode->append(node);
      continue;
    }

    // table cell
    node = TableCellParser::parse(buffer);
    if (node)
    {
      if (!defaultRowNode)
        defaultRowNode = new TableRowNode();
      defaultRowNode->append(node);
      continue;
    }

    // table head
    node = TableHeadParser::parse(buffer);
    if (node)
    {
      if (!defaultRowNode)
        defaultRowNode = new TableRowNode();
      defaultRowNode->append(node);
      continue;
    }

    // No node found. Eat input until a node is found.
    // Eat one line at a time.
    unparsedText.append(buffer.readLine());
  } while (!buffer.endOfFile());

  // Handle living defaultRowNode, which catches cells without rows.
  if (defaultRowNode)
  {
    tableNode->append(defaultRowNode);
    // Do not delete it, because now it is owned by tableNode.
  }

  // If there is some unsuccessfully parsed text,
  // append it as text
  if (unparsedText.length() > 0)
  {
    TextTokenNode *unparsedTextNode =
      new TextTokenNode(unparsedText);
    tableNode->append(unparsedTextNode);
  }

  return tableNode;
}

AttributeGroupNode *TableParser::parseAttributes(QString text)
{
  AttributeGroupNode *groupNode = new AttributeGroupNode();
  parseAttributes(groupNode, text, "([a-zA-Z_\\-:]+)[ ]*=[ ]*\"([^\"]*)\"");
  parseAttributes(groupNode, text, "([a-zA-Z_\\-:]+)[ ]*=[ ]*'([^']*)'");
  parseAttributes(groupNode, text, "([a-zA-Z_\\-:]+)[ ]*=[ ]*([^ '\"]*)");
  if (groupNode->count() > 0)
    return groupNode;
  else
    delete groupNode;
  return 0;
}

void TableParser::parseAttributes(AttributeGroupNode *parent,
    QString &text, const QString &regex)
{
  QRegExp ex(regex);
  int pos = 0;
  while ((pos = ex.indexIn(text, pos)) != -1)
  {
    AttributeNode *attNode = new AttributeNode(ex.cap(1), false);
    TextTokenNode *valueNode = new TextTokenNode(ex.cap(2));
    attNode->append(valueNode);
    parent->append(attNode);
    text.remove(pos, ex.matchedLength());
  }
}
