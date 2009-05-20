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
#ifndef MEDIAPACKER_H_
#define MEDIAPACKER_H_

#include <QThread>
#include <QString>

class MediaPacker : public QThread
{
  Q_OBJECT
public:
  MediaPacker(const QString& sourceDir, const QString& destinationFile);

  void run();
  void requestTermination() { _terminate = true; }
  bool terminated() const { return _terminate; }

signals:
  void log(const QString &message);

private slots:
  void receiveLog(const QString &message);

private:
  QString _sourceDir;
  QString _destinationFile;

  int _pageCounter;
  bool _terminate;
};


#endif /* MEDIAPACKER_H_ */
