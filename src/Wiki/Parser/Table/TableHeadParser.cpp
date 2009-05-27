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
#include "TableHeadParser.h"
#include "TableParser.h"
#include "TableCellParser.h"
#include "../Block/BlockParser.h"
#include "../TextBlock/TextBlockParser.h"

//===========================================================================
TableHeadNode *TableHeadParser::parse(Buffer &buffer)
{
  // Test if we are really starting a cell.
  if (buffer.endOfFile()) return 0;
  QRegExp startHead("^ *! *");
  QString line = buffer.nextLine();
  if (startHead.indexIn(line, 0) == -1) return 0;

  TableHeadNode *headNode = new TableHeadNode();

  buffer.skip(startHead.matchedLength());
  QString restOfLine = line.mid(startHead.matchedLength());

  // Unify the cell separator. Both || and !! can be used.
  // Do it also in the underlying buffer. If it would not be done,
  // the following cells would be parsed as common cells instead of
  // header cells.
  restOfLine.replace("||", "!!");
  buffer.text().remove(buffer.pos(), restOfLine.length());
  buffer.text().insert(buffer.pos(), restOfLine);

  // Handle attributes.
  QRegExp singlePipeRegExp("\\| *");
  int singlePipe = singlePipeRegExp.indexIn(restOfLine);
  int doublePipe = restOfLine.indexOf("!!");
  int linkStart = restOfLine.indexOf("[[");

  if (singlePipe != -1 &&
      (singlePipe < doublePipe || doublePipe == -1) && // the pipe is not a part of double pipe
      (singlePipe < linkStart || linkStart == -1)) // the pipe is not a part of link
  {
    QString attributes = restOfLine.mid(0, singlePipe);
    // Skip the attributes and also skip the pipe.
    buffer.skip(singlePipe + singlePipeRegExp.matchedLength());
    restOfLine = restOfLine.mid(singlePipe + singlePipeRegExp.matchedLength());
    AttributeGroupNode *attribNode = TableParser::parseAttributes(attributes);
    if (attribNode)
      headNode->append(attribNode);
  }

  // Find the end of the cell. First look on the initial line.
  doublePipe = restOfLine.indexOf("!!");
  if (doublePipe != -1)
  {
    QString cellContents = restOfLine.mid(0, doublePipe);
    buffer.skip(doublePipe + 1); // remove one pipe of two
    TableCellParser::parseInsideCell(*headNode, cellContents.trimmed());
    return headNode;
  }

  // Second, look in the following lines.
  QRegExp startRow("^ *\\|\\-");
  QRegExp endTable("^ *\\|\\} *");
  QRegExp startCell("^ *\\| *");
  QString headContents = restOfLine + "\n";
  buffer.skip(restOfLine.length() + 1);
  while (!buffer.endOfFile())
  {
    line = buffer.nextLine();

    // Handle embedded tables.
    if (line.startsWith("{|"))
    {
      int pos = buffer.pos();
      Node *table = TableParser::parse(buffer);
      if (table) delete table;
      QString tableText = buffer.text().mid(pos, buffer.pos() - pos);
      headContents.append(tableText);
      continue;
    }

    if (startRow.indexIn(line, 0) != -1) break;
    if (endTable.indexIn(line, 0) != -1) break;
    if (startCell.indexIn(line, 0) != -1) break;
    if (startHead.indexIn(line, 0) != -1) break;
    buffer.skip(line.length() + 1);
    headContents.append(line + "\n");
  }

  TableCellParser::parseInsideCell(*headNode, headContents);
  return headNode;
}
