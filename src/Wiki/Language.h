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
#include <QString>
#include <QStringList>

class Language
{
public:
  /// List of all languages.
  /// Sorted by English name.
  /// See http://en.wikipedia.org/wiki/List_of_ISO_639-1_codes
  typedef enum {
    // A
    Abkhazian,
    Afar,
    Afrikaans,
    Akan,
    Albanian,
    Amharic,
    AngloSaxon,
    Arabic,
    Aragonese,
    Armenian,
    Assamese,
    Asturian,
    Avaric,
    Avestan,
    Aymara,
    Azerbaijani,
    // B
    Bambara,
    Bashkir,
    Basque,
    Belarusian,
    Bengali,
    Bihari,
    Bislama,
    Bosnian,
    Breton,
    Bulgarian,
    Burmese,
    // C
    Catalan,
    Chamorro,
    Chechen,
    Cherokee,
    Chichewa,
    Chinese,
    ChurchSlavic,
    Chuvash,
    Cornish,
    Corsican,
    Cree,
    Croatian,
    Czech,
    // D
    Danish,
    Divehi,
    Dutch,
    Dzongkha,
    // E
    English,
    Esperanto,
    Estonian,
    Ewe,
    // F
    Faroese,
    Fijian,
    Finnish,
    French,
    Fualah,
    // G
    Galician,
    Ganda,
    Georgian,
    German,
    Greek,
    Guarani,
    Gujarati,
    // H
    Haitian,
    Hausa,
    Hebrew,
    Herero,
    Hindi,
    HiriMotu,
    Hungarian,
    // I
    Icelandic,
    Ido,
    Igbo,
    Indonesian,
    Interlingua,
    Interlingue,
    Inuktitut,
    Inupiaq,
    Irish,
    Italian,
    // J
    Japanese,
    Javanese,
    // K
    Kalaallisut,
    Kannada,
    Kanuri,
    Kashmiri,
    Kashubian,
    Kazakh,
    Khmer,
    Kikuyu,
    Kinyarwanda,
    Kirghiz,
    Kirundi,
    Komi,
    Kongo,
    Korean,
    Kurdish,
    Kwanyama,
    // L
    Lao,
    Latin,
    Latvian,
    Limburgish,
    Lingala,
    Lithuanian,
    Lojban,
    LowSaxon,
    LubaKatanga,
    Luxembourgish,
    // M
    Macedonian,
    Malagasy,
    Malay,
    Malayalam,
    Maltese,
    Manx,
    Maori,
    Marathi,
    Marshallese,
    MinNan,
    Mongolian,
    // N
    Nauru,
    Navajo,
    Ndonga,
    Nepali,
    NorthNdebele,
    NorthernSami,
    Norwegian,
    NorwegianBokmal,
    NorwegianNynorsk,
    // O
    Occitan,
    Ojibwa,
    Oriya,
    Oromo,
    Ossetian,
    // P
    Pali,
    Panjabi,
    Pashto,
    Persian,
    Polish,
    Portuguese,
    // Q
    Quechua,
    // R
    RaetoRomance,
    Romanian,
    Russian,
    // S
    Samoan,
    Sango,
    Sanskrit,
    Sardinian,
    ScottishGaelic,
    Serbian,
    SerboCroatian,
    Shona,
    SichuanYi,
    Sicilian,
    SimpleEnglish,
    Sindhi,
    Sinhala,
    Slovak,
    Slovenian,
    Somali,
    SouthNdebele,
    SouthernSotho,
    Spanish,
    Sundanese,
    Swahili,
    Swati,
    Swedish,
    // T
    Tagalog,
    Tahitian,
    Tajik,
    Tamil,
    Tatar,
    Telugu,
    Thai,
    Tibetan,
    Tigrinya,
    Tonga,
    Tsonga,
    Tswana,
    Turkish,
    Turkmen,
    Twi,
    // U
    Uighur,
    Ukrainian,
    UpperSorbian,
    Urdu,
    Uzbek,
    // V
    Venda,
    Vietnamese,
    Volapuk,
    // W
    Walloon,
    Welsh,
    WesternFrisian,
    Wolof,
    // X
    Xhosa,
    // Y
    Yiddish,
    Yoruba,
    // Z
    Zhuang,
    Zulu,
    // -
    Unknown
  } Type;

  static const Language &instance();

  /// Converts language code (interwiki) to Language.
  /// This method is case insensitive.
  /// @param code
  ///  Language code such as "en" or "cs".
  /// @return
  ///  If the code is not known, returns Language::Unknown.
  Language::Type fromCode(const QString &code) const;

  Language::Type fromLinkPrefixes(const QStringList &prefixes) const;

  /// To interwiki style localized name.
  QString toLocalizedName(Language::Type lang) const;

protected:
  /// Standard constructor. Initializes data.
  Language();

  /// Key is language shortcut as "en" or "zh-min-nan".
  /// Used for interwiki.
  QMap<QString, Type> _interwiki;
  /// Value is localized name as "Česky" for Czech.
  /// Used for interwiki.
  QMap<Type, QString> _localizedNames;
};

#endif /* LANGUAGE_H_ */
