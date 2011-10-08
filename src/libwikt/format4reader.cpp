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
#include "format4reader.h"
#include "fileutils.h"
#include "comparsion.h"
#include "debug.h"

Format4Reader::Format4Reader(const QString &fileName)
{
  _file.setFileName(fileName);
  _file.open(QIODevice::ReadOnly);
  _file.read((char*)&_entryCount, sizeof(quint32));
}

Format4Reader::~Format4Reader()
{
  _file.close();
}

QString Format4Reader::source(const QString &entryName)
{
  int offset = findEntryOffset(0, _entryCount - 1, entryName);
  return (offset < 0) ? "" : source(offset);
}

QString Format4Reader::source(quint32 offset)
{
  _file.seek(sizeof(quint32) + offset * sizeof(qint64)); // index offset
  qint64 entryOffset;
  qint64 bytes = _file.read((char*)&entryOffset, sizeof(qint64));
  CHECK_MSG(bytes == sizeof(qint64), QString("Error while reading. Bytes read: %1, offset: %2").arg(bytes).arg(offset));

  bool seeked = _file.seek(entryOffset);
  CHECK_MSG(seeked, "Error while seeking.");

  FileUtils::readString(_file); // name
  return FileUtils::readCompressed(_file); // contents
}

bool Format4Reader::exist(const QString &entryName)
{
  qint32 offset = findEntryOffset(0, _entryCount - 1, entryName);
  return offset >= 0;
}

QString Format4Reader::name(quint32 offset)
{
  _file.seek(sizeof(quint32) + offset * sizeof(qint64)); // index offset
  qint64 entryOffset;
  qint64 bytes = _file.read((char*)&entryOffset, sizeof(qint64));
  CHECK_MSG(bytes == sizeof(qint64), QString("Error while reading. Bytes read: %1, offset: %2").arg(bytes).arg(offset));

  bool seeked = _file.seek(entryOffset);
  CHECK_MSG(seeked, "Error while seeking.");

  return FileUtils::readString(_file);
}

int Format4Reader::findEntryOffset(int min, int max, const QString &entryName)
{
  if (min == max)
    return name(min) == entryName ? min : -1;
  else if (max - min == 1)
  {
    if (name(min) == entryName)
      return min;
    else
      return name(max) == entryName ? max : -1;
  }

  quint32 middle = min + (max - min) / 2;

  QString nameFromFile = name(middle);
  Comparsion compare;
  if (compare(nameFromFile, entryName))
    return findEntryOffset(middle, max, entryName);
  if (nameFromFile == entryName)
    return middle;
  else
    return findEntryOffset(min, middle, entryName);
}

