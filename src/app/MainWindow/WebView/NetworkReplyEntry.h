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
#ifndef NETWORKREPLY_H_
#define NETWORKREPLY_H_

#include <QNetworkReply>
#include <QBuffer>
#include <QTimer>

class NetworkReplyEntry : public QNetworkReply
{
  Q_OBJECT
public:
  /// Standard constructor.
  NetworkReplyEntry(const QNetworkRequest &request, QObject *parent = 0);
  /// Declared in QNetworkReply.
  void abort() {}
  /// Declared in QIODevice. Must be overridden!
  qint64 bytesAvailable() const { return _buffer.bytesAvailable() + QNetworkReply::bytesAvailable(); }

private slots:
  ///
  void checkFinished();

protected:
  /// Declared in QIODevice.
  /// Tried to emit finished() here but does not work occasionally!
  /// (does not send all data when it's large)
  qint64 readData(char *data, qint64 maxSize) { return  _buffer.read(data, maxSize); }
  /// Declared in QIODevice.
  qint64 writeData(const char*, qint64) { return 0; }
  /// Pre-stored reply contents.
  QBuffer _buffer;
  ///
  QTimer _checkFinishedTimer;
};

#endif /* NETWORKREPLY_H_ */
