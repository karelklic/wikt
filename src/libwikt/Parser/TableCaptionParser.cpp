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
#include "TableCaptionParser.h"
#include "TableParser.h"
#include "TableCellParser.h"
#include "BlockParser.h"
#include "TextBlockParser.h"

//===========================================================================
TableCaptionNode *TableCaptionParser::parse(Buffer &buffer)
{
  // Test if we are really starting a cell.
  if (buffer.endOfFile()) return 0;

  QRegExp startCaption("^ *\\|\\+ *");
  QString line = buffer.nextLine();
  if (startCaption.indexIn(line, 0) == -1) return 0;

  TableCaptionNode *captionNode = new TableCaptionNode();

  buffer.skip(startCaption.matchedLength());
  QString restOfLine = line.mid(startCaption.matchedLength());

  // Handle attributes.
  QRegExp singlePipeRegExp("\\| *");
  int singlePipe = singlePipeRegExp.indexIn(restOfLine);
  int doublePipe = restOfLine.indexOf("||");
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
      captionNode->append(attribNode);
  }

  // Look in the following lines.
  QRegExp startHead("^ *! *");
  QRegExp startCell("^ *\\| *");
  QRegExp startRow("^ *\\|\\-");
  QRegExp endTable("^ *\\|\\} *");
  QString captionContents = restOfLine + "\n";
  buffer.skip(restOfLine.length() + 1);
  while (!buffer.endOfFile())
  {
    line = buffer.nextLine();

    if (startRow.indexIn(line, 0) != -1) break;
    if (endTable.indexIn(line, 0) != -1) break;
    if (startCell.indexIn(line, 0) != -1) break;
    if (startHead.indexIn(line, 0) != -1) break;
    buffer.skip(line.length() + 1);
    captionContents.append(line + "\n");
  }

  TableCellParser::parseInsideCell(*captionNode, captionContents);
  return captionNode;
}
