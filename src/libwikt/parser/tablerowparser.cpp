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
#include "tablerowparser.h"
#include "tableparser.h"
#include "tablecellparser.h"
#include "tableheadparser.h"
#include "blockhtmlparser.h"

//===========================================================================
TableRowNode *TableRowParser::parse(Buffer &buffer)
{
  // Test if we are really starting a row.
  if (buffer.endOfFile()) return 0;
  QRegExp startRow("^ *\\|\\-[ ]*");
  QString line = buffer.nextLine();
  if (startRow.indexIn(line, 0) == -1) return 0;

  // Handle all the attributes on the row line.
  TableRowNode *rowNode = new TableRowNode();
  AttributeGroupNode *groupNode = TableParser::parseAttributes(
      line.mid(startRow.matchedLength()));
  if (groupNode)
    rowNode->append(groupNode);
  buffer.skip(line.length() + 1);

  // Now parse all columns.
  // The first line is handled, now parse the following lines.
  QString unparsedText;
  do {
    // Check if we reached the end of the row.
    // If it is so, break the loop and exit.
    line = buffer.nextLine();
    // "|}" end of table or "|-" next row.
    QRegExp end("^ *(\\|\\}|\\|\\-) *");
    int pos;
    if ((pos = end.indexIn(line, 0)) == 0)
      break;

    // table cell
    Node *cellNode = TableCellParser::parse(buffer);
    if (cellNode) { rowNode->append(cellNode); continue; }
    // table head
    Node *headNode = TableHeadParser::parse(buffer);
    if (headNode) { rowNode->append(headNode); continue; }
    // TD tag
    Node *tagNode = BlockHtmlParser::parse(buffer);
    if (tagNode) { rowNode->append(tagNode); continue; }

    // No node found. Eat input until a node is found.
    unparsedText.append(buffer.readLine());
  } while (!buffer.endOfFile());

  // If there is some unsuccessfully parsed text,
  // append it as text
  if (unparsedText.length() > 0)
  {
    TextTokenNode *unparsedTextNode = new TextTokenNode(unparsedText);
    rowNode->append(unparsedTextNode);
  }

  return rowNode;
}

