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
#include <libwikt/parser/linkparser.h>
#include <libwikt/format3reader.h>
#include <libwikt/tree/linknode.h>
#include <libwikt/tree/linktargetnode.h>
#include <QCoreApplication>
#include <QTextStream>
#include <QProcess>
#include <QDir>
#include <QFileInfo>

QTextStream out(stdout, QIODevice::WriteOnly);
QString destinationDir;

static QString getMediaFilePath(const LinkNode &node)
{
  QString result = destinationDir;
  QString entry = node.target().entry();
  CHECK_MSG(entry.length() > 0, node.toText());
  if (entry.length() <= 0) return result + "/error";
  QChar first = entry[0].toLower();
  if (first.isLetterOrNumber())
    result.append("/").append(first);
  else
    result.append("/_");

  if (entry.length() > 1)
  {
    QChar second = entry[1].toLower();
    if (second.isLetterOrNumber())
      result.append("/").append(second);
    else
      result.append("/_");
  }

  result.append("/").append(entry);
  return result;
}

static void processLink(const LinkNode &node, const QString &entryName)
{
  // Skip existing files.
  QString mediaFile = getMediaFilePath(node);
  if (QFile::exists(mediaFile))
    return;

  // Download web page about the media file.
  QString fileName = node.target().entry();
  fileName.replace(' ', '_'); // does not work without this
  out << QString("Downloading %1...").arg(fileName);
  QString url = "http://en.wiktionary.org/wiki/File:" + fileName;
  int ret = QProcess::execute("wget", QStringList() << "-q" << "-O" << "/tmp/wiktreceived" << url);
  if (ret != 0)
  {
    out << QString("failed, wget failed on url %1, entry %2").arg(url).arg(entryName) << endl;
    return;
  }

  QFile file("/tmp/wiktreceived");
  file.open(QIODevice::ReadOnly);
  QString fileContents = QString::fromUtf8(file.readAll());
  file.close();
  QString linkStartText("<a href=\"http://upload.wikimedia.org/");
  int linkStart = fileContents.indexOf(linkStartText);
  if (linkStart <= 0)
  {
    out << QString("failed, link not found for %1, entry %2").arg(fileName).arg(entryName) << endl;
    return;
  }
  int linkEnd = fileContents.indexOf('\"', linkStart + linkStartText.length());
  if (linkEnd <= 0) 
  {
    out << "failed, linkEnd failure" << endl;
    return;
  }

  url = fileContents.mid(linkStart + 9, linkEnd - linkStart - 9);
  ret = QProcess::execute("wget", QStringList() << "-q" << "-O" << "/tmp/wiktreceived" << url);
  if (ret != 0)
  {
    out << QString("failed, wget failed on url %1, entry %2").arg(url).arg(entryName) << endl;
    return;
  }

  QFileInfo fileInfo(mediaFile);
  QDir dir;
  dir.mkpath(fileInfo.path());
  bool success = dir.rename("/tmp/wiktreceived", mediaFile);
  if (!success)
  {
    out << "failed, rename file failed" << endl;
    return;
  }

  out << "ok" << endl;
}

static void processContent(const QString &name, const QString &content)
{
  for (int i = 0; i < content.length(); ++i)
  {
    if (content[i] != '[') continue;
    Buffer buffer(content.mid(i));
    LinkNode *node = LinkParser::parse(buffer);
    if (!node) continue;

    // Handle images and sounds.
    if (node->target().namespace_() == Namespace::Image ||
        node->target().namespace_() == Namespace::Media ||
        node->target().namespace_() == Namespace::File)
    {
      processLink(*node, name);
    }

    delete node;
    // Set the position in the source *after* the processed link.
    // [[a]]$
    // 012345
    i += buffer.pos() - 1;
  }
}


int main(int argc, char **argv)
{
  QCoreApplication app(argc, argv);

  if (argc != 3)
  {
    QTextStream err(stderr, QIODevice::WriteOnly);
    err << "Invalid number of arguments." << endl;
    err << QString("Usage: %1 [SOURCE] [DESTINATION]").arg(argv[0]) << endl;
    err << "SOURCE << Format3 file" << endl;
    err << "DESTINATION << Directory to store the media files" << endl;
    return -1;
  }

  out << "Reading indices..." << endl;
  Format3Reader reader(argv[1]);
  out << "Processing entries..." << endl;
  destinationDir = argv[2];
  int pageCounter = 0;
  for (QMap<QString, qint64>::const_iterator it = reader.entries().begin(); it != reader.entries().end(); ++it)
  {
    QString contents = reader.sourceDirect(it.value());
    processContent(it.key(), contents);

    // Logging.
    ++pageCounter;
    if (pageCounter % 1000 == 0)
      out << QString("Number of entries processed: %1").arg(pageCounter) << endl;
  }
}
