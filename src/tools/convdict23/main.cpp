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
#include "format2reader.h"
#include "format3writer.h"
#include "templatesolver.h"
#include "galleryconverter.h"
#include <libwikt/debug.h>
#include <QCoreApplication>
#include <QTextStream>
#include <QStringList>
#include <QRegExp>

void usage()
{
    cstderr(QString("Usage: %1 [OPTIONS] [SOURCE] [DESTINATION]\n").arg(QCoreApplication::arguments().first()));
    cstderr("Limits:");
    cstderr("  -f,  --from=NUMBER   sets the starting offset");
    cstderr("  -t,  --to=NUMBER     sets the ending offset");
    cstderr("       --names         displays names of entries");
}

int main(int argc, char **argv)
{
  QCoreApplication a(argc, argv);
  QStringList args = a.arguments();
  args.removeFirst(); // application name

  QString source, destination, from, to;
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
      case 1: destination = s; break;
      }
      ++pos;
    }
  }

  if (pos != 2)
  {
    usage();
    return 1;
  }

  cstdout("Reading indices...");
  Format2Reader reader(source);
  cstdout("Processing entries...");

  int pageCounter = 0;
  Format3Writer writer(destination);

  // Sets the starting point.
  Format2Reader::EntryMap::const_iterator it = reader.entries().constBegin();
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
  Format2Reader::EntryMap::const_iterator itend = reader.entries().constEnd();
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
      cstdout(QString("Entry #%1: %2").arg(pageCounter).arg(it.key()));

    // Skip template pages.
    if (it.key().startsWith("Template:")) continue;

    // Evaluate templates in common pages.
    QString content = reader.sourceDirect(it.value());
    TemplateSolver solver(it.key(), content, reader);
    content = solver.run();

    // Convert galleries to tables with images.
    content = GalleryConverter::convert(content);

    // If the entry is a Category and if it is marked as hidden by
    // __HIDDENCAT__, do not store this category to the output file.
    // Hidden categories exist for maintenance reasons and should not be
    // present in Wikt.
    if (it.key().startsWith("Category:") && content.contains("__HIDDENCAT__"))
      continue;

    // Remove noinclude tags, but not the content between them.
    // Noinclude is not required anymore in this moment, because
    // the template evaluation step is finished and no inclusion
    // is performed after this step.
    //
    // It is important to keep the content between noinclude open and close 
    // tags in the entry. The content is valid part of a word.
    content.remove(QRegExp("<noinclude\\s*>")).remove(QRegExp("</noinclude\\s*>"));

    // Write the entry.
    writer.addEntry(it.key(), content);

    // Logging.
    ++pageCounter;
    if (pageCounter % 10 == 0)
      cstdout(QString("Processed: %1").arg(pageCounter));
  }
  writer.close();
  cstdout("Done.");
  return 0;
}
