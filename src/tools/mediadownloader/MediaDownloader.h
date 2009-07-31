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
#ifndef MEDIADOWNLOADER_H_
#define MEDIADOWNLOADER_H_

#include <libwikt/Format3Reader.h>
#include <QTimer>
#include <QString>
#include <QNetworkAccessManager>
#include <QByteArray>
#include <QTextStream>

class LinkNode;

/// Downloads media used in a dictionary from internet to
/// selected directory.
///
/// http://meta.wikimedia.org/wiki/Wikix
class MediaDownloader : public QObject
{
  Q_OBJECT
public:
  /// Standard constructor.
  /// @param sourceFile
  ///   Format3 file with dictionary entries.
  MediaDownloader(const QString& sourceFile,
    const QString& destinationDir);

  void start();

signals:
  void finished();

private slots:
  void processEntry();
  void downloadFinished(QNetworkReply *reply);

private:
  /// Analyzes all links in an entry and checks if they links to images or sounds.
  /// @param name
  ///  Entry name such as "apple".
  /// @param content
  ///  Entry content in wiki format.
  void processContent(const QString &name, const QString &content);
  /// Checks if the link target is worth downloading and starts the download
  /// if it is so.
  /// @param entryName
  void processLink(const LinkNode &node, const QString &entryName);
  /// Returns a path to file on the local filesystem that represents
  /// certain link.
  QString getMediaFilePath(const LinkNode &node) const;

  QString _sourceFile;
  QString _destinationDir;

  QTimer _timer;

  Format3Reader *_reader;
  int _pageCounter;
  Format3Reader::EntryMap::const_iterator _iterator;

  QNetworkAccessManager *_networkAccessManager;
  int _downloadsInProgress;

  /// Console output.
  mutable QTextStream _out;
};

#endif /* MEDIADOWNLOADER_H_ */
