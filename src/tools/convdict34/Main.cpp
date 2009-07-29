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
#include <QCoreApplication>
#include <QTextStream>
#include <DictionaryFile/Format3Reader.h>
#include "Format4Writer.h"
#include "LinkConverter.h"
#include "TitlePageGenerator.h"
#include "LicensePagesGenerator.h"
#include "StatsPageGenerator.h"
#include <Media/MediaReader.h>
#include <Prerequisites.h>

//===========================================================================
int main(int argc, char **argv)
{
  QCoreApplication a(argc, argv);

  if (argc != 4)
  {
    QTextStream err(stderr, QIODevice::WriteOnly);
    err << "Invalid number of arguments." << endl;
    err << QString("Usage: %1 [SOURCE] [SOURCEMEDIA] [DESTINATION]").arg(argv[0]) << endl;
    return -1;
  }

  QTextStream out(stdout, QIODevice::WriteOnly);
  out << "Reading indices..." << endl;
  Format3Reader reader(argv[1]);
  out << "Processing entries..." << endl;

  int pageCounter = 0;
  Format4Writer writer(argv[3]);
  MediaReader mediaReader(argv[2]);
  LinkConverter linkConverter(reader, mediaReader);
  TitlePageGenerator titlePageGenerator;
  StatsPageGenerator statsPageGenerator;
  for (Format3Reader::EntryMap::const_iterator it = reader.entries().constBegin(); it != reader.entries().constEnd(); ++it)
  {
    QString content = linkConverter.convertedContents(it.value());
    titlePageGenerator.visit(it.key());
    statsPageGenerator.visit(it.key(), content);

    // Write the entry.
    writer.addEntry(it.key(), content);

    // Logging.
    ++pageCounter;
    if (pageCounter % 1000 == 0)
      out << QString("Number of entries processed: %1").arg(pageCounter) << endl;
  }

  titlePageGenerator.write(writer);
  statsPageGenerator.write(writer);
  LicensePagesGenerator licensePagesGenerator;
  licensePagesGenerator.write(writer);

  writer.close();
  out << "Done." << endl;
  return 0;
}
