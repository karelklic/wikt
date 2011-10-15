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
#include "mediawriter.h"
#include <libwikt/debug.h>
#include <QFile>
#include <QDirIterator>
#include <QCoreApplication>
#include <QTextStream>

void commandPackMedia(const QString &mediaDir, const QString &mediaFile)
{
  QTextStream out(stdout, QIODevice::WriteOnly);
  out << "Processing entries..." << endl;

  QDirIterator dir(mediaDir, QDir::Files | QDir::NoSymLinks,
                   QDirIterator::Subdirectories);
  int pageCounter = 0;
  MediaWriter writer(mediaFile);
  while (dir.hasNext())
  {
    dir.next();
    QFile file(dir.filePath());
    file.open(QIODevice::ReadOnly);
    QByteArray contents = file.readAll();
    writer.addEntry(dir.fileName(), contents);

    // Logging.
    ++pageCounter;
    if (pageCounter % 10 == 0)
      out << QString("Number of entries processed: %1").arg(pageCounter) << endl;
  }
  out << "Building destination file..." << endl;
  writer.close();
  out << "Processing done." << endl;
}
