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
    return -1;
  }

  QTextStream out(stdout, QIODevice::WriteOnly);
  out << "Reading indices..." << endl;
  Format2Reader reader(argv[1]);
  out << "Processing entries..." << endl;

  int pageCounter = 0;
  Format3Writer writer(argv[2]);
  for (Format2Reader::EntryMap::const_iterator it = reader.entries().constBegin(); it != reader.entries().constEnd(); ++it)
  {
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

    // Write the entry.
    writer.addEntry(it.key(), content);

    // Logging.
    ++pageCounter;
    if (pageCounter % 10 == 0)
      out << QString("Processed: %1").arg(pageCounter) << endl;
  }
  writer.close();
  out << "Done." << endl;
  return 0;
}
