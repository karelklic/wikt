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
#ifndef LIBWIKT_PROJECT_H_
#define LIBWIKT_PROJECT_H_

#include "languages.h"
#include <QString>
#include <QMap>
#include <QStringList>

class Project
{
public:
  typedef enum
  {
    Meta,
    Wiktionary,
    Wikipedia,
    Wikisource,
    Wikiquote,
    Wikibooks,
    Wikinews,
    Wikiversity,
    Commons,
    Wikispecies,
    Wikimedia,
    MediaWiki,
    Mediazilla,
    Unknown
  } Type;

  static const Project &instance();

  /// Checks if a string is project prefix.
  /// Project prefixes are used in links.
  /// This method is case insensitive.
  /// Example:
  ///  - w, wikipedia: prefixes to Wikipedia.
  ///  - m, meta: prefixes to Meta.
  /// @param prefix
  ///   Text to be checked, without trailing colon ("w", not "w:").
  bool isPrefix(const QString &prefix) const;

  /// Converts project prefix to URL.
  /// For example "w" converted to Wikipedia.
  /// This method is case insensitive.
  /// @param prefix
  ///   Prefix to be converted, without trailing colon ("w", not "w:").
  /// @return
  ///  Project associated with the prefix.
  Type fromPrefix(const QString &prefix) const;

  Type fromLinkPrefixes(const QStringList &prefixes) const;

  /// Gets project's URL.
  /// For example Wikipedia project has "http://en.wikipedia.org/wiki/".
  QString toUrl(Type project, const char *interwiki_prefix) const;

protected:
  /// Standard constructor.
  Project();

  /// Project prefix such as "w" or "wikipedia".
  QMap<QString, Type> _prefix;
  /// URL such as "http://en.wikipedia.org/wiki/".
  QMap<Type, QString> _url;
};

#endif /* LIBWIKT_PROJECT_H_ */
