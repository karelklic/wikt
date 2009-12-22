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
#ifndef MEDIAREADER_H_
#define MEDIAREADER_H_

#include <QString>
#include <QFile>
#include <QByteArray>

/// @brief Reads entries from media file (sounds, images).
class MediaReader : public QObject
{
public:
  /// @brief Standard constructor.
  /// @param fileName
  ///   Path to the file. File must exist.
  MediaReader(const QString &fileName);
  /// @brief Standard destructor.
  ~MediaReader();

  /// @brief Reads contents of entry with particular name.
  /// @param entryName
  ///   Name of the entry without namespace prefix (without "Media:", "Image:").
  /// @return
  ///   Contents of the entry.
  ///   If the entry is not found, empty buffer.
  QByteArray source(const QString &entryName);
  /// @brief Checks if an entry exists.
  /// @param entryName.
  ///   Name of the entry. Can include namespace prefix (eg. "Citations:").
  /// @return True if entry is found. False otherwise.
  bool exist(const QString &entryName);
  /// @brief Returns content of an entry.
  /// @param offset
  ///   Offset to list of all entries. 0 <= offset < entryCount().
  QByteArray source(quint32 offset);
  /// @brief Returns name of an entry.
  /// @param offset
  ///   Offset to list of all entries. 0 <= offset < entryCount().
  QString name(quint32 offset);
  /// Returns number of entries in the file.
  quint32 entryCount() const { return _entryCount; }

protected:
  /// Constructor for testing purposes only.
  MediaReader();

  /// Returns -1 if entry does not exist.
  qint32 findEntryOffset(quint32 min, quint32 max, const QString &entryName);

  quint32 _entryCount;
  QFile _file;
};

#endif /* MEDIAREADER_H_ */
