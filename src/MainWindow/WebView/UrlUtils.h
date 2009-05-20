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
#ifndef URLUTILS_H_
#define URLUTILS_H_

#include <QString>
#include <QUrl>

class UrlUtils
{
public:
  /// Converts URL to entry name.
  /// @param sectionId
  ///   If not null, will be filled with the text after #
  static QString toEntryName(const QUrl &url, QString *sectionId = 0);
  /// Converts entry name to URL pointing to the dictionary file.
  static QUrl toUrl(const QString &entry, const QString &scheme = "entry");

  static QString fileNameToMimeType(const QString &fileName);
};

#endif /* URLUTILS_H_ */
