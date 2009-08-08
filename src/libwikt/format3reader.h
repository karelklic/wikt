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
#ifndef LIBWIKT_FORMAT3READER_H_
#define LIBWIKT_FORMAT3READER_H_

#include <QString>
#include <QFile>
#include <QMap>

/// @brief Reads entries from Format3 dictionary data file.
class Format3Reader : public QObject
{
  Q_OBJECT
public:
  /// @brief Standard constructor.
  /// @param fileName
  ///   Path to the file. File must exist.
  Format3Reader(const QString &fileName);
  /// @brief Standard destructor. Closes the file.
  ~Format3Reader();

  /// @brief Checks if an entry exists.
  /// @param entryName.
  ///   Name of the entry. Can include namespace prefix (eg. "Citations:").
  /// @return True if entry is found. False otherwise.
  virtual bool exist(QString entryName);
  /// @brief Returns content of an entry.
  /// @param offset
  ///   Offset to list of all entries. 0 <= offset < entryCount().
  virtual QString source(int offset);
  /// @param offset
  ///  Offset between 0 and file size.
  virtual QString sourceDirect(int offset);

  /// Returns number of entries in the file.
  int entryCount() const { return _entryCount; }

  typedef QMap<QString, size_t> EntryMap;
  const EntryMap &entries() const { return _links; }

protected:
  /// Constructor for testing purposes only.
  Format3Reader();

  QFile _file;
  quint32 _entryCount;
  EntryMap _links;
};

#endif /* LIBWIKT_FORMAT3READER_H_ */
