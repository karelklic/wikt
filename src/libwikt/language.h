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
#ifndef LANGUAGE_H_
#define LANGUAGE_H_

#include <QMap>
#include <QMultiMap>
#include <QString>
#include <QStringList>

class Language
{
public:
  /// List of all languages.
  /// Sorted by English name.
  /// See http://en.wikipedia.org/wiki/List_of_ISO_639-1_codes
  typedef enum {
#include "languagesgenerated.h.inc"
  } Type;

  static Language &instance();

  bool isCode(const QString &text) const;

  /// Converts language code to enumeration type.
  /// This method is case insensitive.
  /// @param code
  ///  Language code such as "en" or "cs".
  /// @return
  ///  If the code is not known, returns Language::Unknown.
  Language::Type fromCode(const QString &code) const;

  Language::Type fromLinkPrefixes(const QStringList &prefixes) const;

  QString toCode(Language::Type lang) const;

  /// To interwiki localized name.
  QString toInterwikiName(Language::Type lang) const;

  Language::Type fromName(const QString &translation) const
  {
    return _nameToType.value(translation, Unknown);
  }

  /// Returns the names of the language that can be used to identify the language.
  QStringList toNames(Language::Type lang) const;

  bool isTranslationVisible(Language::Type lang) const;
  void setTranslationVisible(Language::Type lang, bool visible);

private:
  /// Standard constructor. Initializes data.
  Language();

  /// Code is a language shortcut as "en" or "zh-min-nan".
  /// Used for interwiki links.
  QMap<QString, Type> _codeToType;
  QMultiMap<Type, QString> _typeToCode;

  /// Value is localized name as "Česky" for Czech.
  /// Used exclusively for interwiki.
  QMap<Type, QString> _typeToInterwiki;

  /// English language names used in translation sections of entries.
  /// There can be multiple names used for the same language, as
  /// the dictionary is very large and not perfect.
  QMultiMap<Type, QString> _typeToNames;

  /// English language names used in the translation sections of entries.
  /// Multiple names may point to a single type, because the dictionary
  /// is very large and not perfect.
  QMap<QString, Type> _nameToType;
};

#endif /* LANGUAGE_H_ */
