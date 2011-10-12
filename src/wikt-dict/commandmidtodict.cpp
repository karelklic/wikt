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
#include "references.h"
#include <libwikt/format3reader.h>
#include <libwikt/mediareader.h>
#include <libwikt/debug.h>
#include <libwikt/namespace.h>
#include <libwikt/parser/articleparser.h>
#include <QTextStream>

void commandMidToDict(const QString &midFile, const QString &mediaFile,
                      const QString &dictFile, qint64 from /*= -1*/,
                      qint64 to /*= -1*/, bool showNames /*= false*/)
{
  QTextStream out(stdout, QIODevice::WriteOnly);
  cstdout("Reading indices from " + midFile + "...");
  Format3Reader reader(midFile);
  cstdout("Processing entries...");

  int pageCounter = 0;
  MediaReader mediaReader(mediaFile);
  Format4Writer writer(dictFile);
  LinkConverter linkConverter(reader, mediaReader);
  TitlePageGenerator titlePageGenerator;
  StatsPageGenerator statsPageGenerator;

  // Sets the starting point.
  Format3Reader::EntryMap::const_iterator it = reader.entries().constBegin();
  if (from > 0)
    it += from;

  // Set the end point.
  Format3Reader::EntryMap::const_iterator itend = reader.entries().constEnd();
  if (to > 0)
    itend = reader.entries().constBegin() + (int)to;

  // The main loop over all processed entries.
  for (; it != itend; ++it)
  {
    if (showNames)
    {
      cstdout(QString("Entry #%1: %2")
        .arg(pageCounter)
        .arg(it.key()));
    }

    QString content = linkConverter.convertedContents(it.value());
    content = handleReferences(it.key(), content);
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
}

