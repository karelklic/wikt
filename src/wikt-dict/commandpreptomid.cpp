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
#include <qalgorithms.h>
#include <QRegExp>

void commandPrepToMid(const QString &prepFile, const QString &midFile,
                      qint64 from, qint64 to,
                      bool showNames, bool showTemplateUsage,
                      bool debug)
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
    if (index % 10 == 0 && !showNames)
    {
      cstdout(QString("Processed: %1/%2")
              .arg(index)
              .arg(reader.entries().size()));
    }

    if (index % 1000 == 0 && showTemplateUsage)
    {
      QList<QPair<int, QString> > usageList = templateUsageList();
      cstdout("Most used templates:");
      for (QList<QPair<int, QString> >::const_iterator usageIt = usageList.begin(); usageIt != usageList.end() && usageIt != usageList.begin() + 10; ++usageIt)
      {
        cstdout(QString("  %1: %2").arg(usageIt->first).arg(usageIt->second));
      }
    }

    if (index % 1000 == 0)
    {
      cstdout(QString("Cross entry template cache: %1 entries").arg(crossEntryCache.size()));

      // Limit max cache size to 2M entries ~~ approx. 2GB of RAM
      if (crossEntryCache.size() > 2000000)
        crossEntryCache.clear();
    }

    if (showNames)
      cstdout(QString("Entry #%1: %2").arg(index).arg(it.key()));

    ++index;

    // Skip template pages.
    if (it.key().startsWith("Template:"))
      continue;

    // Evaluate templates in common pages.
    QString content = reader.sourceDirect(it.value());
    content = templateSolver(it.key(), content, reader, showTemplateUsage, debug);

    // If the entry is a Category and if it is marked as hidden by
    // __HIDDENCAT__, do not store this category to the output file.
    // Hidden categories exist for maintenance reasons and should not be
    // present in Wikt.
    if (it.key().startsWith("Category:") && content.contains("__HIDDENCAT__"))
      continue;

    // Convert galleries to tables with images.
    content = GalleryConverter::convert(content);

    // Remove noinclude tags, but not the content between them.
    // Noinclude is not required anymore in this moment, because
    // the template evaluation step is finished and no inclusion
    // is performed after this step.
    //
    // It is important to keep the content between noinclude open and
    // close tags in the entry. The content is valid part of a word.
    content.remove(QRegExp("</?noinclude\\s*>"));

    // Write the entry.
    writer.addEntry(it.key(), content);
  }
  writer.close();
  cstdout("Done.");
}
