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
#ifndef NETWORKACCESSMANAGER_H_
#define NETWORKACCESSMANAGER_H_

#include <QNetworkAccessManager>

/// Protocols:
///  - "http://whatever" opens external browser with that page
///  - "entry://whatever%20word" to display an entry
///  - "notfound://whatever%20word" to get an error page
///  - "special://titlepage" to get the title page
///  - "special://stylesheet" to get get the stylesheet
///  - "embedded://file" to get a file from application's QRC
///  - "media://file" to get a media file such as a pronounciation or image
class NetworkAccessManager : public QNetworkAccessManager
{
public:
  /// Standard constructor.
  NetworkAccessManager(QObject *parent = 0);

protected:
  /// Overridden QNetworkAccessManager implementation.
  QNetworkReply *createRequest(Operation op,
      const QNetworkRequest &req, QIODevice *outgoingData);
};

#endif /* NETWORKACCESSMANAGER_H_ */
