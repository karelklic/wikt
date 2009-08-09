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
#include "format4writer.h"
#include "linkconverter.h"
#include "titlepagegenerator.h"
#include "licensepagesgenerator.h"
#include "statspagegenerator.h"
#include <libwikt/format3reader.h>
#include <libwikt/mediareader.h>
#include <libwikt/debug.h>
#include <QCoreApplication>
#include <QTextStream>
#include <QStringList>

//===========================================================================
void usage()
{
    QTextStream err(stderr, QIODevice::WriteOnly);
    err << QString("Usage: %1 [OPTIONS] [SOURCE] [SOURCEMEDIA] [DESTINATION]").arg(QCoreApplication::arguments().first()) << endl << endl;
    err << "Limits:" << endl;
    err << "  -f,  --from=NUMBER   sets the starting offset" << endl;
    err << "  -t,  --to=NUMBER     sets the ending offset" << endl;
}

//===========================================================================
int main(int argc, char **argv)
{
  QCoreApplication a(argc, argv);
  QStringList args = a.arguments();
  args.removeFirst(); // application name

  QString source, sourceMedia, destination, from, to;
  int pos = 0;
  foreach (const QString &s, args)
  {
    if (s.startsWith("-f="))
      from = s.mid(3);
    else if (s.startsWith("--from="))
      from = s.mid(7);
    else if (s.startsWith("-t="))
      to = s.mid(3);
    else if (s.startsWith("--to="))
      to = s.mid(5);
    else 
    {
      switch (pos)
      {
      case 0: source = s; break;
      case 1: sourceMedia = s; break;
      case 2: destination = s; break;
      }
      ++pos;
    }
  }

  if (pos != 3)
  {
    usage();
    return 1;
  }

  QTextStream out(stdout, QIODevice::WriteOnly);
  out << "Reading indices from " << source << "..." << endl;
  Format3Reader reader(source);
  out << "Processing entries..." << endl;

  int pageCounter = 0;
  MediaReader mediaReader(sourceMedia);
  Format4Writer writer(destination);
  LinkConverter linkConverter(reader, mediaReader);
  TitlePageGenerator titlePageGenerator;
  StatsPageGenerator statsPageGenerator;

  // Sets the starting point.
  Format3Reader::EntryMap::const_iterator it = reader.entries().constBegin();
  if (!from.isNull())
  {
    bool ok = false;
    int fromint = from.toInt(&ok);
    if (!ok)
    {
      usage();
      return 1;
    }

    it += fromint;
  }

  // Set the end point.
  Format3Reader::EntryMap::const_iterator itend = reader.entries().constEnd();
  if (!to.isNull())
  {
    bool ok = false;
    int toint = to.toInt(&ok);
    if (!ok)
    {
      usage();
      return 1;
    }

    itend = reader.entries().constBegin() + toint;
  }

  for (; it != itend; ++it)
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
