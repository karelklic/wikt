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
#include "UrlUtils.h"
#include "Prerequisites.h"

//===========================================================================
QString UrlUtils::toEntryName(const QUrl &url, QString *sectionId)
{
  QString result;
  QString text(url.host());
  if (url.path().length() > 0)
    text.append(url.path());
  for (int i = 0; i < text.length(); ++i)
  {
    if (text[i] != '_')
      result.append(text[i]);
    else
    {
      QString num = text.mid(i + 1, 4);
      QChar c(num.toUInt(0, 16));
      result.append(c);
      i += 4;
    }
  }

  if (sectionId)
  {
    // ToLower because we want to be case-insensitive here.
    // Also the HeadingNode class toLower on the id.
    *sectionId = result.section('#', 1).toLower();
    // Languages like "Scotish Gaelic" has a space in its name.
    sectionId->replace(' ', '_');
  }

  /// Handle "a#welsh" as "a".
  return result.section('#', 0, 0);
}

//===========================================================================
QUrl UrlUtils::toUrl(const QString &entry, const QString &scheme)
{
  QString encoded;
  for (int i = 0; i < entry.length(); ++i)
  {
    ushort c = entry[i].unicode();
    if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') ||
        c == '.' || c == '-' ||
        c == '$' || c == '+' || c == '!' || c == '!')
      encoded.append(entry[i]);
    else
      encoded.append(QString("_%1").arg(c, 4, 16, QChar('0')));
  }

  QUrl result;
  result.setScheme(scheme);
  result.setHost(encoded);
  return result;
}

//===========================================================================
QString UrlUtils::fileNameToMimeType(const QString &fileName)
{
  if (fileName.endsWith(".png", Qt::CaseInsensitive))
    return "image/png";
  else if (fileName.endsWith(".jpg", Qt::CaseInsensitive))
    return "image/jpeg";
  else if (fileName.endsWith(".jpeg", Qt::CaseInsensitive))
    return "image/jpeg";
  else if (fileName.endsWith(".svg", Qt::CaseInsensitive))
    return "image/svg+xml";
  else if (fileName.endsWith(".js", Qt::CaseInsensitive))
    return "text/javascript";
  else if (fileName.endsWith(".gif", Qt::CaseInsensitive))
    return "image/gif";
  else
    MSG("Unsupported mimetype.");
  return "";
}

