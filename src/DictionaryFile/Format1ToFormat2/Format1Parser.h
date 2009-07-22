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
#ifndef XMLPARSER_H_
#define XMLPARSER_H_

#include <QThread>
#include <QString>

class Format2Writer;

/// @brief
/// Parses an input file and writes data to a destination file in Format2.
/// Format2 file writing is handled by Format2Writer class.
///
/// Format1 is the XML format of data files published by Wikimedia Foundation.
/// The data files contain "pages-articles" in their names.
/// Example file that can be downloaded:
/// http://download.wikimedia.org/enwiktionary/20090203/enwiktionary-20090203-pages-articles.xml.bz2
class Format1Parser : public QThread
{
  Q_OBJECT
public:
  Format1Parser(const QString &sourceFile, const QString &errataDirectory, const QString &destinationFile);

  void run();
  void requestTermination() { _terminate = true; }
  bool terminated() const { return _terminate; }

signals:
  void log(const QString &message);

private:
  void onStartElement(const QStringRef& name);
  void onEndElement(const QStringRef& name);
  void onCharacters(const QStringRef& characters);

  QString _sourceFile;
  QString _errataDirectory;
  QString _destinationFile;

  bool _terminate;

  QString _pageTitle;
  QString _pageContents;
  int _pageCounter;
  Format2Writer *_writer;
};


#endif /* XMLPARSER_H_ */
