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
#include "heading.h"
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
  if (!_typeToVisibilitySettingName.contains(type)) return true;

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
  // See http://en.wiktionary.org/wiki/Wiktionary:Semantic_relations
  _textToHeading.insert("Synonyms", SemanticRelations);
  _textToHeading.insert("Antonyms", SemanticRelations);
  _textToHeading.insert("Hypernyms", SemanticRelations);
  _textToHeading.insert("Hyponyms", SemanticRelations);
  _textToHeading.insert("Meronyms", SemanticRelations);
  _textToHeading.insert("Holonyms", SemanticRelations);
  _textToHeading.insert("Troponyms", SemanticRelations);
  _textToHeading.insert("Coordinate terms", SemanticRelations);
  _textToHeading.insert("See also", SemanticRelations);
  // Parts of speech.
  _textToHeading.insert("Abbreviation", PartOfSpeech);
  _textToHeading.insert("Abjad", PartOfSpeech);
  _textToHeading.insert("Abugida", PartOfSpeech);
  _textToHeading.insert("Acronym", PartOfSpeech);
  _textToHeading.insert("Adjective", PartOfSpeech);
  _textToHeading.insert("Adverb", PartOfSpeech);
  _textToHeading.insert("Article", PartOfSpeech);
  _textToHeading.insert("Cardinal number", PartOfSpeech);
  _textToHeading.insert("Circumfix", PartOfSpeech);
  _textToHeading.insert("Classifier", PartOfSpeech);
  _textToHeading.insert("Clitic", PartOfSpeech);
  _textToHeading.insert("Conjunction", PartOfSpeech);
  _textToHeading.insert("Contraction", PartOfSpeech);
  _textToHeading.insert("Coordinator", PartOfSpeech);
  _textToHeading.insert("Counter", PartOfSpeech);
  _textToHeading.insert("Determiner", PartOfSpeech);
  _textToHeading.insert("Determiner", PartOfSpeech);
  _textToHeading.insert("Han character", PartOfSpeech);
  _textToHeading.insert("Hanja", PartOfSpeech);
  _textToHeading.insert("Hanzi", PartOfSpeech);
  _textToHeading.insert("Hiragana character", PartOfSpeech);
  _textToHeading.insert("Infix", PartOfSpeech);
  _textToHeading.insert("Initialism", PartOfSpeech);
  _textToHeading.insert("Interfix", PartOfSpeech);
  _textToHeading.insert("Interjection", PartOfSpeech);
  _textToHeading.insert("Interrogative", PartOfSpeech);
  _textToHeading.insert("Kanji", PartOfSpeech);
  _textToHeading.insert("Katakana character", PartOfSpeech);
  _textToHeading.insert("Letter", PartOfSpeech);
  _textToHeading.insert("Noun", PartOfSpeech);
  _textToHeading.insert("Numeral", PartOfSpeech);
  _textToHeading.insert("Number", PartOfSpeech);
  _textToHeading.insert("Participle", PartOfSpeech);
  _textToHeading.insert("Particle", PartOfSpeech);
  _textToHeading.insert("Phrase", PartOfSpeech);
  _textToHeading.insert("Postposition", PartOfSpeech);
  _textToHeading.insert("Prefix", PartOfSpeech);
  _textToHeading.insert("Preposition", PartOfSpeech);
  _textToHeading.insert("Pronoun", PartOfSpeech);
  _textToHeading.insert("Proper noun", PartOfSpeech);
  _textToHeading.insert("Proverb", PartOfSpeech);
  _textToHeading.insert("Suffix", PartOfSpeech);
  _textToHeading.insert("Symbol", PartOfSpeech);
  _textToHeading.insert("Verb", PartOfSpeech);

  _typeToVisibilitySettingName.insert(Etymology, "view/etymology");
  _typeToVisibilitySettingName.insert(Translations, "view/translations");
  _typeToVisibilitySettingName.insert(DerivedTerms, "view/derivedTerms");
  _typeToVisibilitySettingName.insert(RelatedTerms, "view/relatedTerms");
  _typeToVisibilitySettingName.insert(Anagrams, "view/anagrams");
  _typeToVisibilitySettingName.insert(Inflections, "view/inflections");
  _typeToVisibilitySettingName.insert(Pronunciation, "view/pronunciation");
  _typeToVisibilitySettingName.insert(SemanticRelations, "view/semanticRelations");
}
