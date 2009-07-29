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
#include "HeadingParser.h"
#include "../TextBlock/TextBlockParser.h"

//===========================================================================
Node *HeadingParser::parse(Buffer &buffer)
{
  if (buffer.endOfFile()) return 0;
  QString line = buffer.nextLine();
  QRegExp rx("^([=]+)([^=]*)([=]+)[ ]*$");
  int pos = rx.indexIn(line);
  if (pos == -1)
    return 0;

  buffer.skip(line.length() + 1); // + newline
  int level = qMin(rx.cap(1).length(), rx.cap(3).length());
  HeadingNode *node = new HeadingNode(level);
  TextBlockParser::parse(*node, rx.cap(2));
  buffer.skipEmptyLines();
  return node;
}
