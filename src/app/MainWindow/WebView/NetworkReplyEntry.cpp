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
#include "NetworkReplyEntry.h"
#include "../MainWindow.h"
#include "../../WikiSource.h"
#include <libwikt/UrlUtils.h>
#include <libwikt/Prerequisites.h>
#include <QTimer>

//===========================================================================
NetworkReplyEntry::NetworkReplyEntry(const QNetworkRequest &request,
    QObject *parent) : QNetworkReply(parent)
{
  QString entry = UrlUtils::toEntryName(request.url());
  QString page;
  page += "<html>";
  page += "<head>";
  page += "  <link rel=\"stylesheet\" type=\"text/css\" href=\"special://stylesheet\" />";
  page += "  <script type=\"text/javascript\" src=\"embedded://images/enwikt.js\"></script>";
  page += "</head>";
  page += "<body>";
  page += MainWindow::instance()->wikiSource()->xhtml(entry);
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

  connect(&_checkFinishedTimer, SIGNAL(timeout()),
      this, SLOT(checkFinished()));
  _checkFinishedTimer.start(50);
}

//===========================================================================
void NetworkReplyEntry::checkFinished()
{
  if (_buffer.bytesAvailable() + QNetworkReply::bytesAvailable() == 0)
  {
    _checkFinishedTimer.stop();
    QTimer::singleShot(0, this, SIGNAL(finished()));
  }
}
