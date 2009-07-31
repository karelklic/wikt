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
#ifndef HEADING_H_
#define HEADING_H_

#include "../Prerequisites.h"
#include <QString>
#include <QMap>
#include <QStringList>

class Heading
{
public:
  typedef enum
  {
    Uninitialized,
    Unknown,
    Etymology,
    Translations,
    DerivedTerms,
    RelatedTerms,
    Anagrams,
    Inflections, // Declension, Inflection, Conjugation
    Pronunciation,
    SemanticRelations, // Synonyms, Antonyms, Holonyms...
    PartOfSpeech // Noun, Verb, Adjective...
  } Type;

  static const Heading &instance();

  Type fromText(const QString &text) const;

  void setXHtmlVisibility(Type type, bool visible) const;
  bool xhtmlVisibility(Type type) const;

protected:
  /// Standard constructor. Initializes data.
  Heading();

  QMap<QString, Type> _textToHeading;
  QMap<Type, QString> _typeToVisibilitySettingName;
};

#endif /* HEADING_H_ */
