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
#include "MediaWriter.h"
#include <Prerequisites.h>
#include <QFile>
#include <QDirIterator>
#include <QCoreApplication>
#include <QTextStream>

//===========================================================================
int main(int argc, char **argv)
{
  QCoreApplication a(argc, argv);

  if (argc != 3)
  {
    QTextStream err(stderr, QIODevice::WriteOnly);
    err << "Invalid number of arguments." << endl;
    err << QString("Usage: %1 [SOURCE] [DESTINATION]").arg(argv[0]) << endl;
    err << "SOURCE - Media directory" << endl;;
    err << "DESTINATION - Output file .eim" << endl;
    return -1;
  }

  QTextStream out(stdout, QIODevice::WriteOnly);
  out << "Processing entries..." << endl;

  QDirIterator dir(argv[1], QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
  int pageCounter = 0;
  MediaWriter writer(argv[2]);
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
