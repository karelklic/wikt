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
#include "mediadownloader.h"
#include <QCoreApplication>
#include <QTextStream>

//===========================================================================
int main(int argc, char **argv)
{
  QCoreApplication app(argc, argv);

  if (argc != 3)
  {
    QTextStream err(stderr, QIODevice::WriteOnly);
    err << "Invalid number of arguments." << endl;
    err << QString("Usage: %1 [SOURCE] [DESTINATION]").arg(argv[0]) << endl;
    err << "SOURCE << Format3 file" << endl;
    err << "DESTINATION << Directory to store the media files" << endl;
    return -1;
  }

  QTextStream out(stdout, QIODevice::WriteOnly);
  out << "Reading indices..." << endl;
  Format3Reader reader(argv[1]);
  out << "Processing entries..." << endl;

  MediaDownloader downloader(argv[1], argv[2]);
  downloader.connect(&downloader, SIGNAL(finished()), &app, SLOT(quit()));
  downloader.start();

  return app.exec();
}
