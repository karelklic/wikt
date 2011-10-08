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
#include "urlutils.h"
#include "debug.h"

QString UrlUtils::toEntryName(const QUrl &url, QString *sectionId)
{
  QString result;
  QString text(url.host());
  if (url.path().length() > 0)
    text.append(url.path().mid(1));
  for (int i = 0; i < text.length(); ++i)
  {
    // "x" is used as the escape character.
    if (text[i] != 'x')
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

QUrl UrlUtils::toUrl(const QString &entry, const QString &scheme)
{
  dstdout(QString("Encoding %1").arg(entry));
  // The entry must be pre-encoded, because otherwise the conversion to
  // URL would fail. Entry contains ':', '!' characters and many others
  // invalid in URL. The case-sesnsitivity must be retained
  // (URLs do not retain it).
  QString preencoded;
  for (int i = 0; i < entry.length(); ++i)
  {
    ushort c = entry[i].unicode();
    // Use "x" as the escape character.
    // "-" cannot be used, because URL cannot start with it.
    if ((c >= 'a' && c <= 'z' && c != 'x') || (c >= '0' && c <= '9') || c == '.')
      preencoded.append(entry[i]);
    else
      preencoded.append(QString("x%1").arg(c, 4, 16, QChar('0')));
  }

  QUrl result;
  result.setUrl(QString("%1:///%2").arg(scheme).arg(preencoded));
  CHECK_MSG(result.isValid(), QString("Invalid url created from scheme \"%1\""
				      " and preencoded entry \"%2\": \"%3\".").arg(scheme).arg(preencoded).arg(result.toString()));
  return result;
}

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
    dstderr(QString("Unknown mimetype for filename \"%1\".").arg(fileName));
  return "";
}

