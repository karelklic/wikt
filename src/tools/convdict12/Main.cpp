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
#include <QCoreApplication>
#include <QXmlStreamReader>
#include <QFile>
#include <QTextStream>
#include "Format2.h"

enum EState
{
  STATE_OUTSIDE,
  STATE_PAGE,
  STATE_PAGE_TITLE,
  STATE_PAGE_TEXT
} state = STATE_OUTSIDE;

QString pageTitle;
QString pageContents;
int pageCounter = 0;
QTextStream out(stdout, QIODevice::WriteOnly);

//===========================================================================
static void onStartElement(const QStringRef& name)
{
  if (name == "page" && state == STATE_OUTSIDE)
    state = STATE_PAGE;
  else if (name == "title" && state == STATE_PAGE)
  {
    pageTitle.clear();
    state = STATE_PAGE_TITLE;
  }
  else if (name == "text" && state == STATE_PAGE)
  {
    pageContents.clear();
    state = STATE_PAGE_TEXT;
  }
}

//===========================================================================
static void onEndElement(const QStringRef& name)
{
  if (name == "page" && state == STATE_PAGE)
  {
    if (!pageTitle.isEmpty() && !pageContents.isEmpty())
      Format2_addEntry(pageTitle, pageContents);

    ++pageCounter;
    if (pageCounter % 10000 == 0)
      out << QString("Number of entries processed: %1").arg(pageCounter) << endl;

    state = STATE_OUTSIDE;
  }
  else if (name == "title" && state == STATE_PAGE_TITLE)
  {
    // skip pages from Wikitonary namespace
    // It is much faster to do it here than to do it later after the parsing process.
    if (pageTitle.contains("Wiktionary:"))
      state = STATE_OUTSIDE;
    else
      state = STATE_PAGE;
  }
  else if (name == "text" && state == STATE_PAGE_TEXT)
    state = STATE_PAGE;
}

//===========================================================================
static void onCharacters(const QStringRef& characters)
{
  if (state == STATE_PAGE_TITLE)
    pageTitle += characters;
  else if (state == STATE_PAGE_TEXT)
    pageContents += characters;
}

//===========================================================================
static void processFormat1(const QString &src)
{
  QFile file(src);
  file.open(QIODevice::ReadOnly);
  QXmlStreamReader xml(&file);
  while (!xml.atEnd())
  {
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
}

//===========================================================================
int main(int argc, char **argv)
{
  QCoreApplication a(argc, argv);

  if (argc != 4)
  {
    QTextStream err(stderr, QIODevice::WriteOnly);
    err << "Invalid number of arguments." << endl;
    err << "Usage: %1 [SOURCE] [ERRATADIR] [DESTINATION]" << endl;
    return -1;
  }

  out << "Processing started." << endl;
  Format2_loadErrata(argv[2]);
  processFormat1(argv[1]);
  out << "Writing to destination file." << endl;
  Format2_build(argv[3]);
  out << "Done." << endl;

  return 0;
}
