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
#include "ParagraphParser.h"
#include "../TextBlock/TextBlockParser.h"
#include "../Html/BlockHtmlParser.h"

//===========================================================================
ParagraphNode *ParagraphParser::parse(Buffer &buffer)
{
  if (buffer.endOfFile()) return 0;
  QString paragraph = getText(buffer);
  if (paragraph.length() == 0) return 0;

  ParagraphNode *parNode = new ParagraphNode();
  // Create our own paragraph buffer, so the embedded nodes (like
  // links, spans etc.) do not leave the paragraph.
  TextBlockParser::parse(*parNode, paragraph);

  buffer.skipEmptyLines();
  return parNode;
}

//===========================================================================
bool ParagraphParser::parse(Node &parent, Buffer &buffer)
{
  if (buffer.endOfFile()) return false;
  QString paragraph = getText(buffer);
  if (paragraph.length() == 0) return false;

  TextBlockParser::parse(parent, paragraph);
  buffer.skipEmptyLines();
  return true;
}

//===========================================================================
bool ParagraphParser::lineBelongsToParagraph(const QString &line,
    const QString &currentParagraphText)
{
  // Empty line terminates the paragraph.
  if (line.trimmed().length() == 0) return false;

  // Start of table terminates the paragraph.
  if (line.startsWith("{|")) return false;

  bool validParagraphChar = (line[0] != ' ' && line[0] != ':' &&
    line[0] != ';' && line[0] != '*' && line[0] != '#' && line[0] != '=');

  // No important wiki-syntax at the beginning of the line:
  // the paragraph continues
  if (validParagraphChar) return true;

  // Now it looks like the paragraph should end.
  // But we must check if we are inside a link.
  // If we are inside a link, the character doesn't count.
  if (currentParagraphText.lastIndexOf("[[") > currentParagraphText.lastIndexOf("]]"))
    return true;

  // Paragraph ends because the line starts with special character.
  return false;
}

//===========================================================================
QString ParagraphParser::getText(Buffer &buffer)
{
  QString paragraph;
  QString line = buffer.nextLine();
  int openBlockOffs; // for DIVs, CENTERs etc.
  while (lineBelongsToParagraph(line, paragraph))
  {
    // Handle block tags like DIVs and CENTERs inside of a paragraph.
    // They cause paragraph to end.
    if ((openBlockOffs = BlockHtmlParser::indexIn(line, 0)) != -1)
    {
      paragraph += line.mid(0, openBlockOffs);
      buffer.skip(openBlockOffs);
      break;
    }

    paragraph += line;
    buffer.skip(line.length() + 1); // 1 = newline
    if (buffer.endOfFile()) break;
    line = buffer.nextLine();
  }

  return paragraph;
}
