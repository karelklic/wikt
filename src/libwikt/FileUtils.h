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
#ifndef FILEUTILS_H_
#define FILEUTILS_H_

#include <QIODevice>
#include <QString>

class FileUtils
{
public:
  static void writeString(QIODevice &device, const QString &data);
  static QString readString(QIODevice &device);

  /// Compresses the data and writes the compressed data to the current device.
  static void writeCompressed(QIODevice &device, const QString &data);
  /// Reads a block of compressed data from the device, and uncompresses it.
  static QString readCompressed(QIODevice &device);

  /// Writes a byte array to the device.
  ///
  /// If the byte array contain compressed data and it is written to the device
  /// by this method, it can be later read by method readCompressed() from
  /// the device.
  static void writeByteArray(QIODevice &device, const QByteArray &data);

  /// Reads a byte array from the device.
  ///
  /// This method can read data written by method writeCompressed(). The returned
  /// data will be compressed in this case.
  static QByteArray readByteArray(QIODevice &device);
};

#endif /* FILEUTILS_H_ */
