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
#include "categorybuilder.h"
#include <libwikt/format3reader.h>
#include <libwikt/mediareader.h>
#include <libwikt/debug.h>
#include <libwikt/namespace.h>
#include <libwikt/parser/articleparser.h>
#include <QCoreApplication>
#include <QTextStream>
#include <QStringList>

//===========================================================================
void usage()
{
    QTextStream err(stderr, QIODevice::WriteOnly);
    err << QString("Usage: %1 [OPTIONS] [SOURCE] [SOURCEMEDIA] [DESTINATION]")
      .arg(QCoreApplication::arguments().first()) << endl << endl;
    err << "Limits:" << endl;
    err << "  -f,  --from=NUMBER   sets the starting offset" << endl;
    err << "  -t,  --to=NUMBER     sets the ending offset" << endl;
    err << "       --names         displays names of entries" << endl;
}

//===========================================================================
int main(int argc, char **argv)
{
  QCoreApplication a(argc, argv);
  QStringList args = a.arguments();
  args.removeFirst(); // application name

  QString source, sourceMedia, destination, from, to;
  bool names = false;
  int pos = 0;
  foreach (const QString &s, args)
  {
    if (s == "--names")
      names = true;
    else if (s.startsWith("-f="))
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
  cstdout("Reading indices from " + source + "...");
  Format3Reader reader(source);
  cstdout("Processing entries...");

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

  // The main loop over all processed entries.
  for (; it != itend; ++it)
  {
    if (names)
    {
      cstdout(QString("Entry #%1: %2")
        .arg(pageCounter)
        .arg(it.key()));
    }

    QString content = linkConverter.convertedContents(it.value());
    ArticleNode *node = ArticleParser::parse(it.key(), content);

    titlePageGenerator.visit(it.key());
    statsPageGenerator.visit(it.key(), *node);
    CatBuilder_process(it.key(), *node);

    delete node;

    // Handle categories
    if (Namespace::instance().fromEntry(it.key()) == Namespace::Category)
      CatBuilder_addContents(it.key(), content);
    else
    {
      // Write the entry.
      writer.addEntry(it.key(), content);
    }

    // Logging.
    ++pageCounter;
    if (pageCounter % 1000 == 0)
      cstdout(QString("Number of entries processed: %1").arg(pageCounter));
  }

  cstdout("Writing categories.");
  CatBuilder_writeAll(writer);

  cstdout("Writing generated pages.");
  titlePageGenerator.write(writer);
  statsPageGenerator.write(writer);
  LicensePagesGenerator licensePagesGenerator;
  licensePagesGenerator.write(writer);

  writer.close();
  cstdout("Done.");
  return 0;
}
