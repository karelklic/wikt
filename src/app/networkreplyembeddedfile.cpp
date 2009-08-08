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
#include "networkreplyembeddedfile.h"
#include "mainwindow.h"
#include "wikisource.h"
#include <libwikt/urlutils.h>
#include <libwikt/debug.h>
#include <QTimer>
#include <QFile>

//===========================================================================
NetworkReplyEmbeddedFile::NetworkReplyEmbeddedFile(const QNetworkRequest &request, QObject *parent) : QNetworkReply(parent)
{
  QString entry = UrlUtils::toEntryName(request.url());

  _file.setFileName(":/" + entry);
  CHECK_MSG(_file.exists(), _file.fileName());
  _file.open(QIODevice::ReadOnly);
  CHECK(_file.isOpen() && _file.isReadable());

  setRequest(request);
  setUrl(request.url());
  setOpenMode(QIODevice::ReadOnly);
  setOperation(QNetworkAccessManager::GetOperation);
  setHeader(QNetworkRequest::ContentTypeHeader, UrlUtils::fileNameToMimeType(entry));
  setHeader(QNetworkRequest::ContentLengthHeader, _file.size());

  QTimer::singleShot(0, this, SIGNAL(metaDataChanged()));
  QTimer::singleShot(0, this, SIGNAL(readyRead()));

  connect(&_checkFinishedTimer, SIGNAL(timeout()),
      this, SLOT(checkFinished()));
  _checkFinishedTimer.start(50);
}

//===========================================================================
void NetworkReplyEmbeddedFile::checkFinished()
{
  if (_file.bytesAvailable() + QNetworkReply::bytesAvailable() == 0)
  {
    _checkFinishedTimer.stop();
    QTimer::singleShot(0, this, SIGNAL(finished()));
  }
}

