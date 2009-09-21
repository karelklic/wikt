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
#include "format2reader.h"
#include <libwikt/fileutils.h>
#include <libwikt/comparsion.h>
#include <libwikt/debug.h>
#include <libwikt/stringutils.h>

//===========================================================================
Format2Reader::Format2Reader(const QString &fileName)
{
  _file.setFileName(fileName);
  _file.open(QIODevice::ReadOnly);
  _file.read((char*)&_entryCount, sizeof(quint32));

  /// Read the offsets.
  qint64 *offsets = new qint64[_entryCount];
  _file.read((char*)offsets, _entryCount * sizeof(qint64));
  for (unsigned i = 0; i < _entryCount; ++i)
  {
    _file.seek(offsets[i]);
    QString name = FileUtils::readString(_file);
    _links.insert(name, offsets[i]);
  }
  delete[] offsets;
}

//===========================================================================
Format2Reader::~Format2Reader()
{
  _file.close();
}

//===========================================================================
QString Format2Reader::sourceTemplate(QString entryName)
{
  // Check template cache.
  QString contents = _templateCache.value(entryName, "random value");
  if (contents != "random value") return contents;

  qint64 offset = _links.value(entryName, 0);
  if (offset <= 0)
  { // Entry not found
    // Try again with underscores instead of spaces, and vice versa.
    offset = _links.value(entryName.replace(" ", "_"), 0);
    if (offset <= 0)
      offset = _links.value(entryName.replace("_", " "), 0);
    if (offset <= 0)
      return "";
  }

  QString result = sourceDirect(offset);

  // Handle redirects.
  if (result.contains("#REDIRECT", Qt::CaseInsensitive))
  {
    int start = result.indexOf("[[");
    if (start == -1) return "REDIRECT_ERROR";
    int end = result.indexOf("]]", start);
    if (end == -1) return "REDIRECT_ERROR";
    QString redirName = result.mid(start + 2, end - start - 2);
    result = sourceTemplate(redirName);
  }

  // Handle templates starting with "*", "#", ":", ";", and "{|".
  // They automatically get a newline at the start.
  // Source: http://meta.wikimedia.org/wiki/Help:Newlines_and_spaces#Automatic_newline_at_the_start
  if (result.startsWith("*") || result.startsWith("#") || result.startsWith(":") || result.startsWith(";") || result.startsWith("{|"))
    result = "\n" + result;

  // Remove <noinclude>..</noinclude> blocks from templates, because those 
  // blocks must not be included during template evaluation.
  result = StringUtils::removeBlock(QRegExp("<noinclude\\s*>"), QRegExp("</noinclude\\s*>"), result);

  // Put template into cache.
  _templateCache.insert(entryName, result);

  return result;
}

//===========================================================================
QString Format2Reader::source(quint32 offset)
{
  _file.seek(sizeof(quint32) + offset * sizeof(qint64)); // index offset
  qint64 entryOffset;
  int bytes = _file.read((char*)&entryOffset, sizeof(qint64));
  CHECK_MSG(bytes == sizeof(qint64), "Error while reading.");
  return sourceDirect(entryOffset);
}

//===========================================================================
QString Format2Reader::sourceDirect(qint64 offset)
{
  bool seeked = _file.seek(offset);
  CHECK_MSG(seeked, "Error while seeking.");
  FileUtils::readString(_file); // name
  return FileUtils::readString(_file); // contents
}

//===========================================================================
bool Format2Reader::exist(QString entryName)
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
Format2Reader::Format2Reader() : _entryCount(0)
{
}
