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
#include <QString>
#include <QRegExp>

void commandPrepToMid(const QString &prepFile, const QString &midFile,
                      qint64 from /*= -1*/, qint64 to /*= -1*/,
                      bool showNames /*= false*/)
{
  cstdout("Reading indices...");
  Format2Reader reader(prepFile);
  cstdout("Processing entries...");
  Format3Writer writer(midFile);
  // Sets the starting point.
  Format2Reader::EntryMap::const_iterator it = reader.entries().constBegin();
  if (from > 0)
    it += from;

  // Set the end point.
  Format2Reader::EntryMap::const_iterator itend = reader.entries().constEnd();
  if (to > 0)
    itend = reader.entries().constBegin() + (int)to;

  // The main loop over all processed entries.
  size_t index = 0;
  for (; it != itend; ++it)
  {
    // Logging.
    ++index;
    if (index % 10 == 0)
      cstdout(QString("Processed: %1/%2")
              .arg(index)
              .arg(reader.entries().size()));
    if (showNames)
      cstdout(QString("Entry #%1: %2").arg(index).arg(it.key()));

    // Skip template pages.
    if (it.key().startsWith("Template:"))
      continue;

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
    // It is important to keep the content between noinclude open and
    // close tags in the entry. The content is valid part of a word.
    content.remove(QRegExp("<noinclude\\s*>")).remove(QRegExp("</noinclude\\s*>"));

    // Write the entry.
    writer.addEntry(it.key(), content);
  }
  writer.close();
  cstdout("Done.");
}
