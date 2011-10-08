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
#include "externallinkparser.h"

ExternalLinkNode *ExternalLinkParser::parse(Buffer &buffer)
{
  if (buffer.endOfFile()) return 0;
  if (!buffer.startsWith("[http://") && !buffer.startsWith("[entry://")) return 0;

  buffer.readChar(); // [
  QChar c = buffer.readChar();
  QString link;
  while (c != ' ' && c != ']')
  {
    link.append(c);
    if (buffer.endOfFile()) break;
    c = buffer.readChar();
  }

  QString title;
  while (c != ']')
  {
    title.append(c);
    if (buffer.endOfFile()) break;
    c = buffer.readChar();
  }

  title = title.trimmed();
  return new ExternalLinkNode(link, title.length() == 0 ? link : title);
}
