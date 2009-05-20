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

  static void writeCompressed(QIODevice &device, const QString &data);
  static QString readCompressed(QIODevice &device);

  static void writeByteArray(QIODevice &device, const QByteArray &data);
  static QByteArray readByteArray(QIODevice &device);
};

#endif /* FILEUTILS_H_ */
