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
#include "fileutils.h"
#include "debug.h"
#include <QByteArray>

//===========================================================================
void FileUtils::writeString(QIODevice &device, const QString &data)
{
  QByteArray utf8(data.toUtf8());

  // The format conversions are not working without this.
  // It forces "stable" UTF-8 encoding that does not change.
  QString another = QString::fromUtf8(utf8);
  QByteArray utf8Next(another.toUtf8());

  quint32 count = (quint32)utf8Next.count();
  size_t bytes = device.write((const char*)&count, sizeof(quint32));
  CHECK_MSG(bytes == 4, "Error while writing to file.");
  if (count == 0) return;
  bytes = device.write(utf8Next);
  CHECK_MSG(bytes == count, "Error while writing to file.");
}

//===========================================================================
QString FileUtils::readString(QIODevice &device)
{
  quint32 count;
  qint64 bytes = device.read((char*)&count, sizeof(quint32));
  CHECK_MSG(bytes == 4, "Error while reading from file.");
  if (count == 0) return "";
  CHECK(count > 0);
  QByteArray utf8 = device.read(count);
  return QString::fromUtf8(utf8);
}

//===========================================================================
void FileUtils::writeCompressed(QIODevice &device, const QString &data)
{
  QByteArray utf8(data.toUtf8());

  // The format conversions are not working without this.
  // It forces "stable" UTF-8 encoding that does not change.
  QString another = QString::fromUtf8(utf8);
  QByteArray utf8Next(another.toUtf8());

  QByteArray compressed = qCompress(utf8Next, 9);

  quint32 count = (quint32)compressed.count();
  qint64 bytes = device.write((const char*)&count, sizeof(quint32));
  CHECK_MSG(bytes == 4, "Error while writing to file.");
  if (count == 0) return;

  bytes = device.write(compressed);
  CHECK_MSG(bytes == compressed.size(), "Error while writing to file.");
}

//===========================================================================
QString FileUtils::readCompressed(QIODevice &device)
{
  quint32 count;
  qint64 bytes = device.read((char*)&count, sizeof(quint32));
  CHECK_MSG(bytes == sizeof(quint32), "Error while reading from file.");
  if (count == 0) return "";

  QByteArray compressed = device.read(count);
  QByteArray utf8 = qUncompress(compressed);
  return QString::fromUtf8(utf8);
}

//===========================================================================
void FileUtils::writeByteArray(QIODevice &device, const QByteArray &data)
{
  qint32 len = data.length();
  device.write((char*)&len, sizeof(qint32));
  device.write(data);
}

//===========================================================================
QByteArray FileUtils::readByteArray(QIODevice &device)
{
  qint32 len;
  device.read((char*)&len, sizeof(qint32));
  return device.read(len);
}
