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
#ifndef NAMESPACEUTILS_H_
#define NAMESPACEUTILS_H_

#include <QString>
#include <QMap>
#include <QStringList>

/// Namespace in MediaWiki. Every entry belongs to some namespace.
/// If the namespace is not present, the entry falls into Main namespace.
class Namespace
{
public:
  typedef enum
  {
    Media,
    Special,
    Main,
    Talk,
    User,
    UserTalk,
    Wiktionary,
    WiktionaryTalk,
    Wikipedia,
    WikipediaTalk,
    Image,
    ImageTalk,
    MediaWiki,
    MediaWikiTalk,
    Template,
    TemplateTalk,
    Help,
    HelpTalk,
    Category,
    CategoryTalk,
    File,
    FileTalk,
    Appendix,
    AppendixTalk,
    Concordance,
    ConcordanceTalk,
    Index,
    IndexTalk,
    Rhymes,
    RhymesTalk,
    Transwiki,
    TranswikiTalk,
    Wikisaurus,
    WikisaurusTalk,
    WT,
    WTTalk,
    Citations,
    CitationsTalk,
    /// Namespace is not known.
    Unknown
  } Type;

  static const Namespace &instance();

  /// Prefix is a string that represents a namespace in link.
  bool isPrefix(const QString &text) const;

  /// Prefix is a string that represents a namespace in link.
  Type fromPrefix(const QString &prefix) const;

  /// Namespace code is a number or text. It is a parameter of {{ns:}}
  /// template function.
  /// This function is case insensitive.
  /// @return
  ///   Unknown for unknown or empty code.
  Type fromCode(const QString &code) const;

  /// Detects a namespace from entry name.
  /// This function is case insensitive.
  /// For example returns Main for "cs:myslet", Project for "Wiktionary:Main page",
  /// Category for "cs:Kategorie:Anglická substantiva".
  /// @return
  ///   Main namespace if no known namespace is detected.
  Type fromEntry(const QString &name) const;

  /// Detects a namespace from link target text.
  /// This function is case insensitive.
  /// For example returns Main for "cs:myslet", Project for "Wiktionary:Main page",
  /// Category for "cs:Kategorie:Anglická substantiva".
  /// @return
  ///   Main namespace if no known namespace is detected.
  Type fromLinkPrefixes(const QStringList &prefixes) const;

  /// Returns localized presentation name for a namespace.
  /// For Main namespace the name is empty string.
  QString toLocalizedName(Type ns) const;

protected:
  /// Standard constructor. Initializes data.
  Namespace();

  QMap<QString, Type> _codeToNamespace;

  /// Link prefixes denoting the namespace
  QMap<QString, Type> _prefixToNamespace;

  /// Localized names to be displayed to users
  QMap<Type, QString> _namespaceToName;
};

#endif /* NAMESPACEUTILS_H_ */
