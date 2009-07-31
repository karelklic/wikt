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
#include "LinkParser.h"
#include "TextBlockParser.h"
#include <QStringList>

//===========================================================================
LinkNode *LinkParser::parse(Buffer &buffer)
{
  if (buffer.endOfFile()) return 0;
  if (!buffer.startsWith("[[")) return 0;
  QString line = buffer.nextLine();

  // If linkLevel > 0, the iterator is inside a link.
  // Handles embedded links, because image links might contain them.
  int linkLevel = 0;
  QString part;
  QStringList parts;
  QChar last = ' ';
  QString::const_iterator it;
  for (it = line.begin() + 2; it != line.end(); ++it)
  {
    if (*it == '[' && last == '[')
    {
      ++linkLevel;
      last = ' '; // clear the last, so the algorithm works for [[[[.
      part.append(*it);
      continue;
    }
    else if (*it == ']' && last == ']')
    {
      if (linkLevel > 0)
      {
        --linkLevel;
        last = ' '; // clear the last, so the algorithm works for ]]]].
        part.append(*it);
        continue;
      }
      else
      {
        // remove the preceding ] already appended to part.
        part.remove(part.length() - 1, 1);
        break;
      }
    }
    else if (*it == '|' && linkLevel == 0)
    {
      parts.append(part); // *not* to be trimmed
      part.clear();
      last = ' ';
      continue;
    }
    last = *it;
    part.append(*it);
  }
  parts.append(part); // *not* to be trimmed
  buffer.skip(it - line.begin() + 1);

  bool forcedLink = parts[0].startsWith(':');
  if (forcedLink)
    parts[0].remove(0, 1);

  bool emptyPipeAtEnd = false;
  if (parts.size() > 1 && parts.last().length() == 0)
  {
    parts.removeLast();
    emptyPipeAtEnd = true;
  }

  LinkNode *linkNode = new LinkNode(emptyPipeAtEnd, forcedLink);
  LinkTargetNode *targetNode = new LinkTargetNode(parts[0].trimmed());
  parts.removeFirst();
  linkNode->append(targetNode);

  foreach(const QString &part, parts)
  {
    LinkOptionsNode *optionNode = new LinkOptionsNode();
    TextBlockParser::parse(*optionNode, part.trimmed());
    linkNode->append(optionNode);
  }

  return linkNode;
}
