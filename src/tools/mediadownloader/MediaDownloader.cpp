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
#include "MediaDownloader.h"
#include <libwikt/Wiki/Parser/ArticleParser.h>
#include <libwikt/Wiki/Tree/Link/LinkNode.h>
#include <libwikt/Wiki/Tree/Link/LinkTargetNode.h>
#include <QDir>
#include <QUrl>
#include <QNetworkRequest>
#include <QApplication>
#include <QEventLoop>
#include <QNetworkReply>

//===========================================================================
MediaDownloader::MediaDownloader(const QString& sourceFile, const QString& destinationDir) : _sourceFile(sourceFile), _destinationDir(destinationDir), _pageCounter(0), _downloadsInProgress(0), _out(stdout, QIODevice::WriteOnly)
{
  _networkAccessManager = new QNetworkAccessManager(this);
  connect(_networkAccessManager, SIGNAL(finished(QNetworkReply*)),
      this, SLOT(downloadFinished(QNetworkReply*)));

  _timer.setInterval(50);
  connect(&_timer, SIGNAL(timeout()), this, SLOT(processEntry()));
}

//===========================================================================
void MediaDownloader::start()
{
  _out << "Processing started." << endl;
  _out << "Reading indices, please wait..." << endl;
  _reader = new Format3Reader(_sourceFile);
  _iterator = _reader->entries().constBegin();
  _out << "Reading indices done." << endl;

  _out << "Processing entries..." << endl;
  _timer.start();
}

//===========================================================================
void MediaDownloader::downloadFinished(QNetworkReply *reply)
{
  CHECK(_downloadsInProgress > 0);
  --_downloadsInProgress;

  if (reply->header(QNetworkRequest::ContentTypeHeader).toString().contains("text/html"))
  {
    // Find media link in the web page.
    QString contents = QString::fromUtf8(reply->readAll());
    QString linkStartText("<a href=\"http://upload.wikimedia.org/");
    int linkStart = contents.indexOf(linkStartText);
    if (linkStart <= 0)
    {
      CERR("Link not found for " +
          QString::fromUtf8(reply->request().rawHeader("Target-File-Name")));
      return;
    }
    int linkEnd = contents.indexOf('\"', linkStart + linkStartText.length());
    CHECK(linkEnd >= 0);
    if (linkEnd <= 0) return;
    QUrl url = QUrl::fromEncoded(contents.mid(linkStart + 9, linkEnd - linkStart - 9).toAscii());

    // Download media.
    ++_downloadsInProgress;
    QNetworkRequest fileRequest(url);
    //COUT(QString::fromAscii(url.toEncoded()));
    fileRequest.setRawHeader("Target-File-Name", reply->request().rawHeader("Target-File-Name"));
    fileRequest.setRawHeader("Wikt-Sent-File-Request", "True");
    _networkAccessManager->get(fileRequest);
  }
  else if (reply->request().hasRawHeader("Wikt-Sent-File-Request"))
  {
    QString fileName = QString::fromUtf8(reply->request().rawHeader("Target-File-Name"));

    // Make sure target directory exist.
    QFileInfo fileInfo(fileName);
    QDir dir(fileInfo.path());
    dir.mkpath(fileInfo.path());

    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    file.write(reply->readAll());
    file.close();
  }
  else
  {
    CERR("Invalid response for " + reply->request().url().toString());
  }
}

//===========================================================================
void MediaDownloader::processEntry()
{
  if (_downloadsInProgress > 0) return;
  CHECK(_downloadsInProgress == 0);
  if (_pageCounter == _reader->entries().size())
  {
    //COUT(_reader->entries().size());
    _timer.stop();
    emit finished();
    return;
  }

  QString contents = _reader->sourceDirect(_iterator.value());
  processContent(_iterator.key(), contents);

  ++_iterator;

  // Logging.
  ++_pageCounter;
  if (_pageCounter % 1000 == 0)
    _out << QString("Number of entries processed: %1").arg(_pageCounter) << endl;

  // Do not wait for another timer tick if there is no download.
  // Second condition limits recursion, which would be too deep otherwise.
  if (_downloadsInProgress == 0 && (_pageCounter % 100) != 0)
    processEntry();
}

//===========================================================================
void MediaDownloader::processContent(const QString &name, const QString &content)
{
  ArticleNode *node = ArticleParser::parse(name, content);
  if (!node)
    _out << QString("Error parsing \"%1\"").arg(name) << endl;
  else
  {
    QList<const LinkNode*> allLinks;
    node->findChildren(allLinks);

    // Find and remove duplicates.
    // Find and remove non-image non-media links.
    QList<const LinkNode*> links;
    foreach(const LinkNode *link, allLinks)
    {
      if (link->target().namespace_() != Namespace::Image &&
          link->target().namespace_() != Namespace::Media)
        continue;

      bool found = false;
      foreach (const LinkNode *link2, links)
      {
        if (link->target().entry() == link2->target().entry())
        {
          found = true;
          break;
        }
      }
      if (!found)
        links.append(link);
    }

    // Check every link.
    foreach(const LinkNode *link, links)
      processLink(*link);

    delete node;
  }
}

//===========================================================================
void MediaDownloader::processLink(const LinkNode &node)
{
  // Skip existing files.
  if (QFile::exists(getMediaFilePath(node)))
    return;

  // Download web page about the media file.
  QString fileName = node.target().entry();
  fileName.replace(' ', '_'); // does not work without this
  _out << QString("Downloading %1").arg(fileName) << endl;
  ++_downloadsInProgress;
  //QString urlTextUser("http://en.wiktionary.org/wiki/File:" + fileName);
  QByteArray urlText = QString("http://en.wiktionary.org/wiki/File:").toAscii() + QUrl::toPercentEncoding(fileName, "", " ");
  QUrl url = QUrl::fromEncoded(urlText);
  //COUT("Url: " + QString::fromAscii(url.toEncoded()));
  QNetworkRequest fileRequest(url);
  fileRequest.setRawHeader("File-Name", fileName.toUtf8());
  fileRequest.setRawHeader("Target-File-Name", getMediaFilePath(node).toUtf8());
  _networkAccessManager->get(fileRequest);
}

//===========================================================================
QString MediaDownloader::getMediaFilePath(const LinkNode &node) const
{
  QString result = _destinationDir;

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
