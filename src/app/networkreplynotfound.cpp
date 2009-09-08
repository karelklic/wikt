/* This file is part of Wikt. -*- mode: c++; c-file-style: "wikt"; -*-
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
#include "networkreplynotfound.h"
#include <libwikt/urlutils.h>
#include <QTimer>

//===========================================================================
NetworkReplyNotFound::NetworkReplyNotFound(const QNetworkRequest &request, QObject *parent) : QNetworkReply(parent)
{
  QString entry = UrlUtils::toEntryName(request.url());

  QString notFound;
  notFound += tr(
    "<html>"
    "<head>"
    "<link rel=\"stylesheet\" type=\"text/css\" href=\"special://stylesheet\" />"
    "</head>"
    "<body>"
    "<h1>Entry not found</h1>"
    "<p>No definition of '%1' found.</p>"
    "<p>Suggestions:</p>"
    "<ul><li>Check that the term is written correctly.</li>"
    "<li>Try a related term or synonym.</li></ul></body></html>").arg(entry);

  _buffer.open(QBuffer::ReadWrite);
  _buffer.write(notFound.toUtf8());
  _buffer.seek(0);

  setRequest(request);
  setUrl(request.url());
  setOpenMode(QIODevice::ReadOnly);
  setOperation(QNetworkAccessManager::GetOperation);
  setHeader(QNetworkRequest::ContentTypeHeader, "text/html;charset=utf-8");
  setHeader(QNetworkRequest::ContentLengthHeader, _buffer.size());

  QTimer::singleShot(0, this, SIGNAL(metaDataChanged()));
  QTimer::singleShot(0, this, SIGNAL(readyRead()));

  connect(&_checkFinishedTimer, SIGNAL(timeout()), this, SLOT(checkFinished()));
  _checkFinishedTimer.start(50);
}

//===========================================================================
void NetworkReplyNotFound::checkFinished()
{
  if (_buffer.bytesAvailable() + QNetworkReply::bytesAvailable() == 0)
  {
    _checkFinishedTimer.stop();
    QTimer::singleShot(0, this, SIGNAL(finished()));
  }
}
