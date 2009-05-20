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
#include "Format3ToFormat4Converter.h"
#include "Format3Reader.h"
#include "Format4Writer.h"
#include "LinkConverter/LinkConverter.h"
#include "../../Media/MediaReader.h"
#include "../../Prerequisites.h"

//===========================================================================
Format3ToFormat4Converter::Format3ToFormat4Converter(const QString& sourceFile,
  const QString &sourceMediaFile, const QString& destinationFile)
  : _sourceFile(sourceFile), _sourceMediaFile(sourceMediaFile),
  _destinationFile(destinationFile), _pageCounter(0), _terminate(false)
{
}

//===========================================================================
void Format3ToFormat4Converter::receiveLog(const QString &message)
{
  log(message);
}

//===========================================================================
void Format3ToFormat4Converter::run()
{
  log("Processing started.");
  log("Reading indices, please wait...");
  Format3Reader reader(_sourceFile);
  log("Reading indices done.");
  log("Processing entries...");
  Format4Writer writer(_destinationFile);
  MediaReader mediaReader(_sourceMediaFile);
  LinkConverter linkConverter(reader, mediaReader);
  for (Format3Reader::EntryMap::const_iterator it = reader.entries().constBegin();
       it != reader.entries().constEnd();
       ++it)
  {
    QString content = linkConverter.convertedContents(it.value());

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
