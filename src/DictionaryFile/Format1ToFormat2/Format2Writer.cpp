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
#include "Format2Writer.h"
#include "../Comparsion.h"
#include "../QuickSort.h"
#include "../FileUtils.h"
#include "../../Prerequisites.h"
#include <QDirIterator>

//===========================================================================
Format2Writer::Format2Writer(const QString &targetFileName, const QString &errataDirectory)
  : _targetFileName(targetFileName)
{
  _temporaryFile.open();

  // Find and read all files with entry fixes.
  QDirIterator dir(errataDirectory, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
  while (dir.hasNext())
  {
    dir.next();

    QFile file(dir.filePath());
    file.open(QFile::ReadOnly);
    QString text = QString::fromUtf8(file.readAll());
    file.close();

    _errata.insert(dir.fileName(), text);
  }
}

//===========================================================================
QString removeBlock(const QString &startTag, const QString &stopTag, QString text)
{
  int start = text.indexOf(startTag);
  while (start != -1)
  {
    int end = text.indexOf(stopTag, start);
    if (end == -1)
      text.remove(start, text.length());
    else
      text.remove(start, end - start + stopTag.length());
    start = text.indexOf(startTag);
  }

  return text;
}

//===========================================================================
QString substituteSpecialCharacters(QString input)
{
  return input.replace("{", "&#123;").replace("}", "&#125;")
    .replace("|", "&#124;").replace("[", "&#91;").replace("]", "&#93;")
    .replace("=", "&#61;");
}

//===========================================================================
// substitute special wiki characters in <nowiki> sections with
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

//===========================================================================
void Format2Writer::addUnsortedEntry(const QString &name, QString contents)
{
  // Skip pages from Wikitonary namespace.
  if (name.contains("Wiktionary:")) return;

  // Apply errata if it exists.
  contents = _errata.value(name, contents);

  // Remove <noinclude> and comment parts from contents.
  contents = removeBlock("<noinclude>", "</noinclude>", contents);
  contents = removeBlock("<!--", "-->", contents);

  // Remove includeonly tags, but not the content between them.
  contents.remove("<includeonly>").remove("</includeonly>");

  // Remove __TOC__, because we handle Table of Contents in a separate window.
  contents.remove("__TOC__");

  // Do not remove <nowiki/> tags. They are used as a separator between wikisyntax
  // that cannot be parsed together.

  // Substitute special wiki characters in <nowiki> sections with
  // html chars and removes the <nowiki> tags.
  contents= substituteSpecialCharactersNoWiki(contents);

  qint64 offset = _temporaryFile.pos();

  // Save data to the content file.
  FileUtils::writeString(_temporaryFile, name);
  FileUtils::writeString(_temporaryFile, contents);

  // Add an entry to the link list.
  _links.push_back(Link(name, offset));
}

//===========================================================================
void Format2Writer::close()
{
  // Sort the links in the memory.
  // Sort comparison operator must not depend on locale, because the dictionary file
  // is the same in all systems.
  QList<Link> sortedLinks(_links);
  quickSort(sortedLinks.begin(), sortedLinks.end(), Comparsion());

  // Final file.
  QFile file(_targetFileName);
  file.open(QIODevice::WriteOnly);
  quint32 entryCount = _links.size();
  file.write((const char*)&entryCount, sizeof(quint32));

  foreach(const Link &it, sortedLinks)
  {
    quint32 realOffset = it.second + 4 + 4 * entryCount;
    file.write((const char*)&realOffset, sizeof(quint32));
  }

  // Follow the links (now sorted), load page from unsorted file and
  // store it to the end of a new file. The file is thus sorted.
  foreach(const Link &it, _links)
  {
    _temporaryFile.seek(it.second);
    QString name = FileUtils::readString(_temporaryFile);
    QString contents = FileUtils::readString(_temporaryFile);
    CHECK_MSG(file.pos() == it.second + 4 + 4 * entryCount, "Data corruption.");
    FileUtils::writeString(file, name);
    FileUtils::writeString(file, contents);
  }

  file.close();
  _temporaryFile.close();
}
