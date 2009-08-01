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
#include "bulletlistparser.h"
#include "listparser.h"
#include "linkparser.h"

//===========================================================================
BulletListNode *BulletListParser::parse(Buffer &buffer)
{
  if (buffer.endOfFile()) return 0;
  if (buffer.nextChar() != '*') return 0;

  // Read all lines that belong to this list.
  QStringList lines;
  while (!buffer.endOfFile())
  {
    // Common line
    if (buffer.nextChar() == '*')
    {
      lines.append(buffer.readLine());
      continue;
    }

    // Can be a line with category.
    // This behavior is strange, but it is how MediaWiki does it.
    // [[en:stadia]] needs it.
    QString line = buffer.nextLine().trimmed();
    Buffer buf(line);
    LinkNode *link = LinkParser::parse(buf);
    if (!link) break;
    if (link->target().namespace_() == Namespace::Category)
    {
      lines.last().append(buffer.readLine());
      delete link;
      continue;
    }
    delete link;
    break;
  }

  BulletListNode *listNode = new BulletListNode();
  ListParser::parseListItems(lines, *listNode);
  buffer.skipEmptyLines();
  return listNode;
}
