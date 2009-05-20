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
#ifndef NETWORKREPLYTITLEPAGE_H_
#define NETWORKREPLYTITLEPAGE_H_

#include <QNetworkReply>
#include <QBuffer>

class NetworkReplyTitlePage : public QNetworkReply
{
public:
  /// Standard constructor.
  NetworkReplyTitlePage(const QNetworkRequest &request, QObject *parent = 0);
  /// Declared in QNetworkReply.
  void abort() {}
  /// Declared in QIODevice. Must be overridden!
  qint64 bytesAvailable() const { return _buffer.bytesAvailable(); }

protected:
  /// Declared in QIODevice.
  qint64 readData(char *data, qint64 maxSize);
  /// Declared in QIODevice.
  qint64 writeData(const char *data, qint64 maxSize) { return _buffer.write(data, maxSize); }
  /// Pre-stored reply contents.
  QBuffer _buffer;
};

#endif /* NETWORKREPLYTITLEPAGE_H_ */
