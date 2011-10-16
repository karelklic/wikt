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
#include <libwikt/comparsion.h>
#include <libwikt/quicksort.h>
#include <libwikt/fileutils.h>
#include <libwikt/stringutils.h>
#include <libwikt/debug.h>
#include <QXmlStreamReader>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDirIterator>
#include <QTemporaryFile>
#include <QList>
#include <QPair>
#include <QMap>

/// Offsets to entries.
typedef QPair<QString, qint64> Link;
static QList<Link> links;

/// Key is entry name and Value is the new entry contents.
static QMap<QString, QString> errata;

/// Temporary file with entries without indices.
static QTemporaryFile temporaryFile;

/// @param directory
///   The directory with a new contents for some entries.
static void loadErrata(const QString &directory)
{
  // Find and read all files with entry fixes.
  QDirIterator dir(directory, QDir::Files | QDir::NoSymLinks,
                   QDirIterator::Subdirectories);
  while (dir.hasNext())
  {
    dir.next();
    QFile file(dir.filePath());
    file.open(QFile::ReadOnly);
    errata.insert(dir.fileName(), QString::fromUtf8(file.readAll()));
    file.close();
  }
}

static QString substituteSpecialCharacters(QString input)
{
  return input.replace("{", "&#123;").replace("}", "&#125;")
    .replace("|", "&#124;").replace("[", "&#91;").replace("]", "&#93;")
    .replace("=", "&#61;");
}

// Substitute special wiki characters in <nowiki> sections with
// html chars and removes the <nowiki> tags.
static QString substituteSpecialCharactersNoWiki(QString input)
{
  QString open("<nowiki>"), close("</nowiki>");
  int start = input.indexOf(open);
  if (start == -1) return input;
  int end = input.indexOf(close, start);
  if (end == -1)
  {
    QString before = input.mid(0, start);
    QString mid = input.mid(start + open.length());
    QString content = substituteSpecialCharacters(mid);
    return substituteSpecialCharactersNoWiki(before + content);
  }

  QString before = input.mid(0, start);
  QString mid = input.mid(start + open.length(), end - start - open.length());
  QString content = substituteSpecialCharacters(mid);
  QString after = input.mid(end + close.length());
  return substituteSpecialCharactersNoWiki(before + content + after);
}

/// @brief Adds entry to the file.
///
/// Some entries may be ignored because of their namespace. Entries from Wiktionary
/// namespace are ignored for now.
///
/// The contents of the entry can be changed before saving.
///
/// Prep modifies entry content:
///  - <nowiki> sections are converted to HTML entities and the tags are removed.
///  - <noinclude> blocks are removed with their content
///  - HTML comments <!-- --> are removed with their content
///  - <includeonly> tags are removed, but not the contents between them
///
/// @param name
///   Name of entry. Includes the optional namespace.
/// @param contents
///   Entry contents in wiki syntax.
static void addPrepEntry(const QString &name, QString contents)
{
  // Skip pages from Wikitonary namespace.
  if (name.contains("Wiktionary:")) return;

  // Apply errata if it exists.
  contents = errata.value(name, contents);

  // Remove comments from contents.
  contents = StringUtils::removeBlock(QRegExp("<!--"), QRegExp("-->"), contents);

  // Remove includeonly tags, but not the content between them.
  contents.remove(QRegExp("<includeonly\\s*>"))
    .remove(QRegExp("</includeonly\\s*>"));

  // Remove __TOC__ magic word, because we handle Table of Contents in
  // a separate window.
  contents.remove("__TOC__");

  // Do not remove <nowiki/> tags. They are used as a separator between wikisyntax
  // that cannot be parsed together.

  // Substitute special wiki characters in <nowiki> sections with
  // html chars and removes the <nowiki> tags.
  contents = substituteSpecialCharactersNoWiki(contents);

  if (!temporaryFile.isOpen())
      temporaryFile.open();
  qint64 offset = temporaryFile.pos();

  // Save data to the content file.
  FileUtils::writeString(temporaryFile, name);
  FileUtils::writeString(temporaryFile, contents);

  // Add an entry to the link list.
  links.push_back(Link(name, offset));
}

static void buildPrep(const QString &destinationFile)
{
  // Sort the links in the memory.
  // Sort comparison operator must not depend on locale, because the dictionary file
  // is the same in all systems.
  QList<Link> sortedLinks(links);
  quickSort(sortedLinks.begin(), sortedLinks.end(), Comparsion());

  // Final file.
  QFile file(destinationFile);
  file.open(QIODevice::WriteOnly);
  quint32 entryCount = links.size();
  file.write((const char*)&entryCount, sizeof(quint32));

  foreach(const Link &it, sortedLinks)
  {
    qint64 realOffset = it.second + sizeof(quint32) + entryCount * sizeof(qint64);
    file.write((const char*)&realOffset, sizeof(qint64));
  }

  // Follow the links (now sorted), load page from unsorted file and
  // store it to the end of a new file. The file is thus sorted.
  foreach(const Link &it, links)
  {
    temporaryFile.seek(it.second);
    QString name = FileUtils::readString(temporaryFile);
    QString contents = FileUtils::readString(temporaryFile);
    CHECK_MSG(file.pos() == it.second + sizeof(quint32) + entryCount * sizeof(qint64), "Data corruption.");
    FileUtils::writeString(file, name);
    FileUtils::writeString(file, contents);
  }

  file.close();
  temporaryFile.close();
}


static enum
{
  STATE_OUTSIDE,
  STATE_PAGE,
  STATE_PAGE_TITLE,
  STATE_PAGE_TEXT
} state = STATE_OUTSIDE;

static QString pageTitle;
static QString pageContents;
static int pageCounter = 0;
static QTextStream out(stdout, QIODevice::WriteOnly);

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

static void onEndElement(const QStringRef& name)
{
  if (name == "page" && state == STATE_PAGE)
  {
    if (!pageTitle.isEmpty() && !pageContents.isEmpty())
      addPrepEntry(pageTitle, pageContents);

    ++pageCounter;
    if (pageCounter % 10000 == 0)
      out << QString("Number of entries processed: %1").arg(pageCounter) << endl;

    state = STATE_OUTSIDE;
  }
  else if (name == "title" && state == STATE_PAGE_TITLE)
  {
    // Skip pages from Wikitonary and Transwiki namespaces.  Pages in
    // these namespaces are not a part of Wikt.  It is much more
    // efficient to do it now than to do it later after the parsing
    // process.
    if (pageTitle.contains("Wiktionary:"))
      state = STATE_OUTSIDE;
    else
      state = STATE_PAGE;
  }
  else if (name == "text" && state == STATE_PAGE_TEXT)
    state = STATE_PAGE;
}

static void onCharacters(const QStringRef& characters)
{
  if (state == STATE_PAGE_TITLE)
    pageTitle += characters;
  else if (state == STATE_PAGE_TEXT)
    pageContents += characters;
}

static void processXml(const QString &src)
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
    cstderr("Xml error.");
    exit(1);
  }
}

void commandXmlToPrep(const QString &xmlFile, const QString &prepFile,
                      const QString &errataDir)
{
  out << "Processing started." << endl;
  loadErrata(errataDir);
  processXml(xmlFile);
  out << "Writing to destination file." << endl;
  buildPrep(prepFile);
  out << "Done." << endl;
}
