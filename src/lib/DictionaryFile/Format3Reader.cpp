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
#include "Format3Reader.h"
#include "FileUtils.h"
#include "Comparsion.h"

//===========================================================================
Format3Reader::Format3Reader(const QString &fileName)
{
  _file.setFileName(fileName);
  _file.open(QIODevice::ReadOnly);
  _file.read((char*)&_entryCount, sizeof(quint32));

  /// Read the offsets.
  quint32 *offsets = new quint32[_entryCount];
  _file.read((char*)offsets, _entryCount * sizeof(quint32));
  for (unsigned i = 0; i < _entryCount; ++i)
  {
    _file.seek(offsets[i]);
    QString name = FileUtils::readString(_file);
    _links.insert(name, offsets[i]);
  }
  delete[] offsets;
}

//===========================================================================
Format3Reader::~Format3Reader()
{
  _file.close();
}

//===========================================================================
QString Format3Reader::source(int offset)
{
  CHECK_MSG(offset >= 0, "Invalid offset.");
  _file.seek(4 + offset * 4); // index offset
  quint32 entryOffset;
  int bytes = _file.read((char*)&entryOffset, 4);
  CHECK_MSG(bytes == 4, "Error while reading.");
  return sourceDirect(entryOffset);
}

//===========================================================================
QString Format3Reader::sourceDirect(int offset)
{
  PROFILER;
  bool seeked = _file.seek(offset);
  CHECK_MSG(seeked, "Error while seeking.");
  FileUtils::readString(_file); // name
  return FileUtils::readString(_file); // contents
}

//===========================================================================
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

//===========================================================================
Format3Reader::Format3Reader() : _entryCount(0)
{
}

