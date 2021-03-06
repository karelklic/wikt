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
#ifndef NETWORKREPLYEMBEDDEDFILE_H_
#define NETWORKREPLYEMBEDDEDFILE_H_

#include <QNetworkReply>
#include <QFile>
#include <QTimer>

class NetworkReplyEmbeddedFile : public QNetworkReply
{
  Q_OBJECT
public:
  /// Standard constructor.
  NetworkReplyEmbeddedFile(const QNetworkRequest &request, QObject *parent = 0);
  /// Declared in QNetworkReply.
  void abort() {}
  /// Declared in QIODevice. Must be overridden!
  qint64 bytesAvailable() const { return _file.bytesAvailable() + QNetworkReply::bytesAvailable(); }

private slots:
  ///
  void checkFinished();

protected:
  /// Declared in QIODevice.
  /// Tried to emit finished() here but does not work occasionally!
  /// (does not send all data when it's large)
  qint64 readData(char *data, qint64 maxSize) { return _file.read(data, maxSize); }
  /// Declared in QIODevice.
  qint64 writeData(const char*, qint64) { return 0; }
  /// File contents.
  QFile _file;
  ///
  QTimer _checkFinishedTimer;
};

#endif /* NETWORKREPLYEMBEDDEDFILE_H_ */
