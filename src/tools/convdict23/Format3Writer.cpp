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
#include "Format3Writer.h"
#include <libwikt/DictionaryFile/Comparsion.h>
#include <libwikt/DictionaryFile/FileUtils.h>
#include <libwikt/DictionaryFile/QuickSort.h>

//===========================================================================
Format3Writer::Format3Writer(const QString &targetFileName) : _targetFileName(targetFileName)
{
  _temporaryFile.open();
}

//===========================================================================
void Format3Writer::addEntry(const QString &name, const QString &contents)
{
  PROFILER;
  qint64 offset = _temporaryFile.pos();

  // Save data to the content file.
  FileUtils::writeString(_temporaryFile, name);
  FileUtils::writeString(_temporaryFile, contents);

  // Add an entry to the link list.
  _links.push_back(Link(name, offset));
}

//===========================================================================
void Format3Writer::close()
{
  PROFILER;
  // Sort the links in the memory.
  // Sort comparison operator must not depend on locale, because the dictionary file
  // is the same in all systems.
  QList<Link> sortedLinks(_links);
  quickSort(sortedLinks.begin(), sortedLinks.end(), Comparsion());

  // Final file.
  QFile file(_targetFileName);
  file.open(QIODevice::WriteOnly);
  quint32 entryCount = _links.size();
  file.write((const char*)&entryCount, sizeof(quint32));

  foreach(const Link &it, sortedLinks)
  {
    quint32 realOffset = it.second + 4 + 4 * entryCount;
    file.write((const char*)&realOffset, sizeof(quint32));
  }

  // Follow the links (now sorted), load page from unsorted file and
  // store it to the end of a new file. The file is thus sorted.
  foreach(const Link &it, _links)
  {
    _temporaryFile.seek(it.second);
    QString name = FileUtils::readString(_temporaryFile);
    QString contents = FileUtils::readString(_temporaryFile);
    FileUtils::writeString(file, name);
    FileUtils::writeString(file, contents);
  }

  file.close();
  _temporaryFile.close();
}
