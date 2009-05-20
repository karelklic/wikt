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
#include "NetworkReplyTitlePage.h"
#include "../MainWindow.h"
#include "../../Version.h"
#include "../../Prerequisites.h"
#include <QTimer>

//===========================================================================
NetworkReplyTitlePage::NetworkReplyTitlePage(const QNetworkRequest &request,
    QObject *parent) : QNetworkReply(parent)
{
  QString page;
  page += "<html>";
  page += "<head>";
  page += "  <link rel=\"stylesheet\" type=\"text/css\" href=\"special://stylesheet\" />";
  page += "</head>";
  page += "<body>";
  page += "  <h1>Wikt <small>"WIKT_VERSION"</small></h1>";
  page += "  <p>Entries are based on Wiktionary, a collaborative project to";
  page += "     produce a free-content multilingual dictionary. All the";
  page += "     content is licensed under the GNU Free Documentation License.</p>";
  page += "</body>";
  page += "</html>";
  _buffer.open(QBuffer::ReadWrite);
  _buffer.write(page.toUtf8());
  _buffer.seek(0);

  setRequest(request);
  setUrl(request.url());
  setOpenMode(QIODevice::ReadOnly);
  setOperation(QNetworkAccessManager::GetOperation);
  setHeader(QNetworkRequest::ContentTypeHeader, "text/html;charset=utf-8");
  setHeader(QNetworkRequest::ContentLengthHeader, _buffer.size());

  QTimer::singleShot(0, this, SIGNAL(metaDataChanged()));
  QTimer::singleShot(0, this, SIGNAL(readyRead()));
}

//===========================================================================
qint64 NetworkReplyTitlePage::readData(char *data, qint64 maxSize)
{
  qint64 length = _buffer.read(data, maxSize);
  if (_buffer.bytesAvailable() == 0)
    QTimer::singleShot(0, this, SIGNAL(finished()));
  return length;
}
