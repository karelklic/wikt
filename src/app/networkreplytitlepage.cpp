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
#include "networkreplytitlepage.h"
#include "mainwindow.h"
#include "wikisource.h"
#include <libwikt/version.h>
#include <libwikt/prerequisites.h>
#include <QTimer>

//===========================================================================
NetworkReplyTitlePage::NetworkReplyTitlePage(const QNetworkRequest &request,
    QObject *parent) : QNetworkReply(parent)
{
  QString page = MainWindow::instance()->wikiSource()->source("Wikt:Title Page");
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
