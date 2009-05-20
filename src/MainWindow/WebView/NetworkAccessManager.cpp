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
#include "NetworkAccessManager.h"
#include "NetworkReplyEntry.h"
#include "NetworkReplyMediaFile.h"
#include "NetworkReplyStylesheet.h"
#include "NetworkReplyTitlePage.h"
#include "NetworkReplyEmbeddedFile.h"
#include "../../Prerequisites.h"

//===========================================================================
NetworkAccessManager::NetworkAccessManager(QObject *parent)
  : QNetworkAccessManager(parent)
{
}

//===========================================================================
QNetworkReply *NetworkAccessManager::createRequest(Operation op,
    const QNetworkRequest &req, QIODevice */*outgoingData*/)
{
  CHECK(op == GetOperation);
  QNetworkReply *reply = 0;
  if (req.url().scheme() == "special")
  {
    if (req.url().host() == "stylesheet")
      reply = new NetworkReplyStylesheet(req, this);
    else if (req.url().host() == "titlepage")
      reply = new NetworkReplyTitlePage(req, this);
  }
  else if (req.url().scheme() == "entry")
    reply = new NetworkReplyEntry(req, this);
  else if (req.url().scheme() == "media")
    reply = new NetworkReplyMediaFile(req, this);
  else if (req.url().scheme() == "embedded")
    reply = new NetworkReplyEmbeddedFile(req, this);

  CHECK_MSG(reply, QString("Unsupported request: %1").arg(req.url().toString()));
  return reply;
}
