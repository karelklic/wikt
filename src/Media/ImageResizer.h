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
#ifndef IMAGERESIZER_H_
#define IMAGERESIZER_H_

#include <QThread>
#include <QString>
#include <QSize>
#include <QList>

class ImageResizer : public QThread
{
  Q_OBJECT
public:
  /// Standard constructor.
  /// @param sourceFile
  ///   Format3 dictionary file with all entries.
  /// @param mediaDirectory
  ///   Directory with all media files.
  ImageResizer(const QString& sourceFile, const QString& mediaDirectory);

  void run();
  void requestTermination() { _terminate = true; }
  bool terminated() const { return _terminate; }

signals:
  void log(const QString &message);

private:
  QString _sourceFile;
  QString _mediaDirectory;

  bool _terminate;

  struct Image
  {
    QString _filePath;
    QSize _originalSize;
    QList<QSize> _linkSizes;
    Image() {}
    Image(QString filePath, QSize originalSize) : _filePath(filePath),
      _originalSize(originalSize)
    {
    }
  };
};

#endif /* IMAGERESIZER_H_ */
