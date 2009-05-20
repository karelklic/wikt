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
#include "Heading.h"
#include <QSettings>

//===========================================================================
const Heading &Heading::instance()
{
  static Heading instance;
  return instance;
}

//===========================================================================
Heading::Type Heading::fromText(const QString &text) const
{
  QString simpleText = text.simplified();
  if (_textToHeading.contains(simpleText))
    return _textToHeading.value(simpleText);
  else
    return Unknown;
}

//===========================================================================
void Heading::setXHtmlVisibility(Type type, bool visible) const
{
  CHECK(_typeToVisibilitySettingName.contains(type));
  QSettings settings;
  settings.setValue(_typeToVisibilitySettingName.value(type), visible);
}

//===========================================================================
bool Heading::xhtmlVisibility(Type type) const
{
  if (!_typeToVisibilitySettingName.contains(type))
    return true;

  QSettings settings;
  return settings.value(_typeToVisibilitySettingName.value(type), true).toBool();
}

//===========================================================================
Heading::Heading()
{
  _textToHeading.insert("Etymology", Etymology);
  _textToHeading.insert("Etymology 1", Etymology);
  _textToHeading.insert("Etymology 2", Etymology);
  _textToHeading.insert("Etymology 3", Etymology);
  _textToHeading.insert("Etymology 4", Etymology);
  _textToHeading.insert("Etymology 5", Etymology);
  _textToHeading.insert("Translations", Translations);
  _textToHeading.insert("Derived terms", DerivedTerms);
  _textToHeading.insert("Related terms", RelatedTerms);
  _textToHeading.insert("Anagrams", Anagrams);
  _textToHeading.insert("Declension", Inflections);
  _textToHeading.insert("Inflection", Inflections);
  _textToHeading.insert("Conjugation", Inflections);
  _textToHeading.insert("Pronunciation", Pronunciation);
  // see http://en.wiktionary.org/wiki/Wiktionary:Semantic_relations
  _textToHeading.insert("Synonyms", SemanticRelations);
  _textToHeading.insert("Antonyms", SemanticRelations);
  _textToHeading.insert("Hypernyms", SemanticRelations);
  _textToHeading.insert("Hyponyms", SemanticRelations);
  _textToHeading.insert("Meronyms", SemanticRelations);
  _textToHeading.insert("Holonyms", SemanticRelations);
  _textToHeading.insert("Troponyms", SemanticRelations);
  _textToHeading.insert("Coordinate terms", SemanticRelations);
  _textToHeading.insert("See also", SemanticRelations);

  _typeToVisibilitySettingName.insert(Etymology, "view/etymology");
  _typeToVisibilitySettingName.insert(Translations, "view/translations");
  _typeToVisibilitySettingName.insert(DerivedTerms, "view/derivedTerms");
  _typeToVisibilitySettingName.insert(RelatedTerms, "view/relatedTerms");
  _typeToVisibilitySettingName.insert(Anagrams, "view/anagrams");
  _typeToVisibilitySettingName.insert(Inflections, "view/inflections");
  _typeToVisibilitySettingName.insert(Pronunciation, "view/pronunciation");
  _typeToVisibilitySettingName.insert(SemanticRelations, "view/semanticRelations");
}
