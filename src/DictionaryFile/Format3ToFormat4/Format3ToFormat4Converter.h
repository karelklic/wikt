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
#ifndef FORMAT3TOFORMAT4CONVERTER_H_
#define FORMAT3TOFORMAT4CONVERTER_H_

#include <QThread>
#include <QString>

/// Converts data file from format3 to format4.
///   - checks links and converts some of them
///   - compresses the whole dictionary
class Format3ToFormat4Converter : public QThread
{
  Q_OBJECT
public:
  Format3ToFormat4Converter(const QString &sourceFile,
    const QString &sourceMediaFile,
    const QString &destinationFile);

  void run();
  void requestTermination() { _terminate = true; }
  bool terminated() const { return _terminate; }

signals:
  void log(const QString &message);

private slots:
  void receiveLog(const QString &message);

private:
  QString _sourceFile;
  QString _sourceMediaFile;
  QString _destinationFile;

  int _pageCounter;
  bool _terminate;
};

#endif /* FORMAT3TOFORMAT4CONVERTER_H_ */
