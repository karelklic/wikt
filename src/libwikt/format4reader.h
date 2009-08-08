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
#ifndef FORMAT4READER_H_
#define FORMAT4READER_H_

#include <QString>
#include <QFile>

/// @brief Reads entries from Format4 dictionary data file.
class Format4Reader
{
public:
  /// @brief Standard constructor.
  /// @param fileName
  ///   Path to the file. File must exist.
  Format4Reader(const QString &fileName);
  /// @brief Standard destructor. Closes the file.
  ~Format4Reader();

  /// @brief Reads contents of entry with particular name.
  /// @param entryName
  ///   Name of the entry. Can include namespace prefix (eg. "Citations:").
  /// @return
  ///   Contents of the entry in the wiki format.
  ///   If the entry is not found, empty string is returned.
  QString source(const QString &entryName);
  /// @brief Checks if an entry exists.
  /// @param entryName.
  ///   Name of the entry. Can include namespace prefix (eg. "Citations:").
  /// @return True if entry is found. False otherwise.
  bool exist(const QString &entryName);
  /// @brief Returns content of an entry.
  /// @param offset
  ///   Offset to list of all entries. 0 <= offset < entryCount().
  QString source(int offset);
  /// @brief Returns name of an entry.
  /// @param offset
  ///   Offset to list of all entries. 0 <= offset < entryCount().
  QString name(int offset);
  /// Returns number of entries in the file.
  int entryCount() const { return _entryCount; }

protected:
  /// Returns -1 if entry does not exist.
  qint32 findEntryOffset(quint32 min, quint32 max, const QString &entryName);

  quint32 _entryCount;
  QFile _file;
};

#endif /* FORMAT4READER_H_ */
