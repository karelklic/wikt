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
#include "NetworkReplyMediaFile.h"
#include "UrlUtils.h"
#include "../MainWindow.h"
#include "../../Wiki/WikiSource.h"
#include "../../Prerequisites.h"
#include <QTimer>
#include <QByteArray>

//===========================================================================
NetworkReplyMediaFile::NetworkReplyMediaFile(const QNetworkRequest &request,
    QObject *parent) : QNetworkReply(parent)
{
  QString fileName = UrlUtils::toEntryName(request.url());
  QByteArray media = MainWindow::instance()->wikiSource()->media(fileName);

  _buffer.open(QBuffer::ReadWrite);
  _buffer.write(media);
  _buffer.seek(0);

  setRequest(request);
  setUrl(request.url());
  setOpenMode(QIODevice::ReadOnly);
  setOperation(QNetworkAccessManager::GetOperation);
  setHeader(QNetworkRequest::ContentTypeHeader, UrlUtils::fileNameToMimeType(fileName));
  setHeader(QNetworkRequest::ContentLengthHeader, _buffer.size());

  QTimer::singleShot(0, this, SIGNAL(metaDataChanged()));
  QTimer::singleShot(0, this, SIGNAL(readyRead()));

  connect(&_checkFinishedTimer, SIGNAL(timeout()),
      this, SLOT(checkFinished()));
  _checkFinishedTimer.start(50);
}

//===========================================================================
void NetworkReplyMediaFile::checkFinished()
{
  if (_buffer.bytesAvailable() + QNetworkReply::bytesAvailable() == 0)
  {
    _checkFinishedTimer.stop();
    QTimer::singleShot(0, this, SIGNAL(finished()));
  }
}
