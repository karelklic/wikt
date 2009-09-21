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
#include "stringutils.h"

namespace StringUtils {

//===========================================================================
QString removeBlock(const QRegExp &startTag, const QRegExp &stopTag, QString text)
{
  int start = text.indexOf(startTag);
  while (start != -1)
  {
    int end = stopTag.indexIn(text, start);
    if (end == -1)
      text.remove(start, text.length());
    else
      text.remove(start, end - start + stopTag.matchedLength());
    start = text.indexOf(startTag);
  }

  return text;
}

}
