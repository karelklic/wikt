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
#include "Format1Parser.h"
#include "Format2Writer.h"
#include <QXmlStreamReader>
#include <QFile>

enum EState {
  STATE_OUTSIDE,
  STATE_PAGE,
  STATE_PAGE_TITLE,
  STATE_PAGE_TEXT
} state = STATE_OUTSIDE;

//===========================================================================
Format1Parser::Format1Parser(const QString& sourceFile, const QString &errataDirectory, const QString& destinationFile)
  : _sourceFile(sourceFile), _errataDirectory(errataDirectory), _destinationFile(destinationFile), _terminate(false), _pageCounter(0)
{
}

//===========================================================================
void Format1Parser::run()
{
  log("Processing started.");
  _writer = new Format2Writer(_destinationFile, _errataDirectory);

  QFile file(_sourceFile);
  file.open(QIODevice::ReadOnly);
  QXmlStreamReader xml(&file);
  while (!xml.atEnd())
  {
    if (_terminate)
    {
      log("Processing terminated.");
      delete _writer;
      return;
    }
    xml.readNext();
    if (xml.isStartElement())
      onStartElement(xml.name());
    else if (xml.isEndElement())
      onEndElement(xml.name());
    else if (xml.isCharacters())
      onCharacters(xml.text());
  }
  if (xml.hasError())
  {
  }

  log("Writing to destination file.");
  _writer->close();
  delete _writer;
  log("Processing done.");
}

//===========================================================================
void Format1Parser::onStartElement(const QStringRef& name)
{
  if (name == "page" && state == STATE_OUTSIDE)
    state = STATE_PAGE;
  else if (name == "title" && state == STATE_PAGE)
  {
    _pageTitle.clear();
    state = STATE_PAGE_TITLE;
  }
  else if (name == "text" && state == STATE_PAGE)
  {
    _pageContents.clear();
    state = STATE_PAGE_TEXT;
  }
}

//===========================================================================
void Format1Parser::onEndElement(const QStringRef& name)
{
  if (name == "page" && state == STATE_PAGE)
  {
    if (!_pageTitle.isEmpty() && !_pageContents.isEmpty())
      _writer->addUnsortedEntry(_pageTitle, _pageContents);
    ++_pageCounter;
    if (_pageCounter % 10000 == 0)
      log(QString("Number of entries processed: %1").arg(_pageCounter));
    state = STATE_OUTSIDE;
  }
  else if (name == "title" && state == STATE_PAGE_TITLE)
  {
    // skip pages from Wikitonary namespace
    // It is much faster to do it here than to do it later after the parsing process.
    if (_pageTitle.contains("Wiktionary:"))
      state = STATE_OUTSIDE;
    else
      state = STATE_PAGE;
  }
  else if (name == "text" && state == STATE_PAGE_TEXT)
    state = STATE_PAGE;
}

//===========================================================================
void Format1Parser::onCharacters(const QStringRef& characters)
{
  if (state == STATE_PAGE_TITLE)
    _pageTitle += characters;
  else if (state == STATE_PAGE_TEXT)
    _pageContents += characters;
}

