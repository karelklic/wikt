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
#include "Format2ToFormat3Converter.h"
#include "Format2Reader.h"
#include "Format3Writer.h"
#include "TemplateSolver/TemplateSolver.h"
#include "GalleryConverter.h"
#include "../../Prerequisites.h"

//===========================================================================
Format2ToFormat3Converter::Format2ToFormat3Converter(const QString& sourceFile,
  const QString& destinationFile) : _sourceFile(sourceFile),
  _destinationFile(destinationFile), _pageCounter(0), _terminate(false)
{
}

//===========================================================================
void Format2ToFormat3Converter::receiveLog(const QString &message)
{
  log(message);
}

//===========================================================================
void Format2ToFormat3Converter::run()
{
  log("Processing started.");
  log("Reading indices, please wait...");
  Format2Reader reader(_sourceFile);
  log("Done.");
  log("Processing entries.");
  Format3Writer writer(_destinationFile);
  for (Format2Reader::EntryMap::const_iterator it = reader.entries().constBegin();
       it != reader.entries().constEnd();
       ++it)
  {
    // DEBUG: it = reader.entries().find(QString::fromStdWString(L"अग्नि"));
    // Skip template pages.
    if (it.key().startsWith("Template:")) continue;

    // Evaluate templates in common pages.
    QString content = reader.sourceDirect(it.value());
    TemplateSolver solver(it.key(), content, reader);
    connect(&solver, SIGNAL(log(const QString&)), this, SLOT(receiveLog(const QString&)));
    content = solver.run();

    // Convert galleries to tables with images.
    content = GalleryConverter::convert(content);

    // Write the entry.
    writer.addEntry(it.key(), content);

    // Logging.
    ++_pageCounter;
    if (_pageCounter % 1000 == 0)
      log(QString("Number of entries processed: %1").arg(_pageCounter));

    // Termination.
    if (_terminate)
    {
      log("Processing terminated.");
      return;
    }
  }
  writer.close();
  log("Processing done.");
}
