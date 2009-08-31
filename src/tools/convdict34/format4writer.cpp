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
#include "format4writer.h"
#include <libwikt/fileutils.h>
#include <libwikt/comparsion.h>
#include <libwikt/quicksort.h>
#include <libwikt/debug.h>
#include <QStringList>

//===========================================================================
Format4Writer::Format4Writer(const QString &targetFileName) : _targetFileName(targetFileName)
{
  _temporaryFile.open();
}

//===========================================================================
void Format4Writer::addEntry(const QString &name, const QString &contents)
{
  qint64 offset = _temporaryFile.pos();

  // Save data to the content file.
  FileUtils::writeString(_temporaryFile, name);
  FileUtils::writeCompressed(_temporaryFile, contents);

  // Add an entry to the link list.
  _links.push_back(Link(name, offset));
}

//===========================================================================
void Format4Writer::addCategory(const QString &name, const QString &contents, const QStringList &subcategories, const QStringList &entries)
{
  qint64 offset = _temporaryFile.pos();

  // Save data to the content file.
  FileUtils::writeString(_temporaryFile, name);

  QString fullContents(contents);
  if (subcategories.size() > 0)
  {
    fullContents += "\n==Subcategories==\n";
    foreach (const QString &subcategory, subcategories)
      fullContents += QString("* %1\n").arg(subcategory);
    fullContents += "\n";
  }
  if (entries.size() > 0)
  {
    fullContents += "\n==Entries==\n";
    foreach (const QString &entry, entries)
      fullContents += QString("* %1\n").arg(entry);
    fullContents += "\n";
  }

  FileUtils::writeCompressed(_temporaryFile, fullContents);

  // Add an entry to the link list.
  _links.push_back(Link(name, offset));
}

//===========================================================================
void Format4Writer::close()
{
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
    qint64 realOffset = it.second + sizeof(quint32) + entryCount * sizeof(qint64);
    file.write((const char*)&realOffset, sizeof(qint64));
  }

  // Follow the links (now sorted), load page from unsorted file and
  // store it to the end of a new file. The file is thus sorted.
  foreach(const Link &it, _links)
  {
    _temporaryFile.seek(it.second);
    QString name = FileUtils::readString(_temporaryFile);
    QByteArray contents = FileUtils::readByteArray(_temporaryFile);
    FileUtils::writeString(file, name);
    FileUtils::writeByteArray(file, contents);
  }

  file.close();
  _temporaryFile.close();
}
