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
#include "GalleryConverter.h"
#include <QRegExp>
#include <QStringList>

//===========================================================================
QString GalleryConverter::convert(QString source)
{
  // See http://en.wikipedia.org/wiki/Wikipedia:Gallery_tag for
  // explanation and a list of parameters which we do not support for now.
  QRegExp startTag("<gallery([ ]*| ([^<>]+))>");
  int start = startTag.indexIn(source);
  if (start == -1) return source;
  int stop = source.indexOf("</gallery>", start, Qt::CaseInsensitive);
  if (stop == -1) return source;

  QString output;
  output += "{|\n";

  QString gallery = source.mid(start + startTag.matchedLength(),
      stop - start - startTag.matchedLength());
  QStringList imageLines = gallery.split('\n');
  int columnCounter = 0;
  foreach (const QString &imageLine, imageLines)
  {
    QString line = imageLine.trimmed();
    if (!line.startsWith("Image:")) continue;
    output += QString("| [[%1|thumb]]\n").arg(line);
    if (columnCounter == 3)
    {
      output += "|-\n";
      columnCounter = 0;
    }
    ++columnCounter;
  }

  output += "|}";

  // Remove gallery tag from the source.
  source.remove(start, stop - start + strlen("</gallery>"));
  // Insert a table with images instead of it.
  source.insert(start, output);

  return convert(source); // Call it recursively until all galleries are transformed.
}
