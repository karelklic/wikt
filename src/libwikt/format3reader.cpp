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
#include "format3reader.h"
#include "fileutils.h"
#include "comparsion.h"
#include "debug.h"

Format3Reader::Format3Reader(const QString &fileName)
{
  _file.setFileName(fileName);
  _file.open(QIODevice::ReadOnly);
  _file.read((char*)&_entryCount, sizeof(quint32));
  CHECK_MSG(_entryCount > 0, "Invalid number of entries read from file.");

  /// Read the offsets.
  qint64 *offsets = new qint64[_entryCount];
  _file.read((char*)offsets, _entryCount * sizeof(qint64));
  for (unsigned i = 0; i < _entryCount; ++i)
  {
    CHECK_MSG(offsets[i] > 0, "Invalid offset read from file.");
    _file.seek(offsets[i]);
    QString name = FileUtils::readString(_file);
    _links.insert(name, offsets[i]);
  }
  delete[] offsets;
}

Format3Reader::~Format3Reader()
{
  _file.close();
}

QString Format3Reader::source(quint32 offset)
{
  _file.seek(sizeof(quint32) + offset * sizeof(qint64)); // index offset
  qint64 entryOffset;
  int bytes = _file.read((char*)&entryOffset, sizeof(qint64));
  CHECK_MSG(bytes == sizeof(qint64), "Error while reading.");
  return sourceDirect(entryOffset);
}

QString Format3Reader::sourceDirect(qint64 offset)
{
  bool seeked = _file.seek(offset);
  CHECK_MSG(seeked, QString("Error while seeking to offset %1").arg(offset));
  FileUtils::readString(_file); // name
  return FileUtils::readString(_file); // contents
}

bool Format3Reader::exist(QString entryName)
{
  if (_links.contains(entryName))
    return true;

  // Entry not found
  // Try again with underscores instead of spaces, and vice versa.
  if (_links.contains(entryName.replace(" ", "_")))
    return true;
  if (_links.contains(entryName.replace("_", " ")))
    return true;

  return false;
}

Format3Reader::Format3Reader() : _entryCount(0)
{
}

