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
#include "Language.h"
#include "../Debug/Debug.h"
#include <QSettings>

//===========================================================================
Language &Language::instance()
{
  static Language lang;
  return lang;
}

//===========================================================================
Language::Type Language::fromCode(const QString &code) const
{
  return _interwiki.value(code.toLower(), Unknown);
}

//===========================================================================
Language::Type Language::fromLinkPrefixes(const QStringList &prefixes) const
{
  if (prefixes.empty()) return English;
  QString name = prefixes.first().toLower();
  if (_interwiki.contains(name))
    return _interwiki.value(name);

  return English;
}

//===========================================================================
QString Language::toLocalizedName(Language::Type lang) const
{
  return _localizedNames.value(lang, "Unknown localized name");
}

//===========================================================================
QString Language::toTranslationSectionName(Language::Type lang) const
{
  return _translationSectionNames.value(lang, "");
}

//===========================================================================
bool Language::isTranslationVisible(Language::Type lang) const
{
  QSettings settings;
  QString settingName = "translations" + toTranslationSectionName(lang);
  return settings.value(settingName, true).toBool();
}

//===========================================================================
void Language::setTranslationVisible(Language::Type lang, bool visible)
{
  QSettings settings;
  QString settingName = "translations" + toTranslationSectionName(lang);
  return settings.setValue(settingName, visible);
}

//===========================================================================
Language::Language()
{
#define L1(__enum, __shortcut) \
  _interwiki.insert(__shortcut, __enum)
#define L2(__enum, __shortcut, __localizedName) \
  _interwiki.insert(__shortcut, __enum); \
  _localizedNames.insert(__enum, QString::fromWCharArray(__localizedName))
#define L3(__enum, __shortcut, __localizedName, __translationSectionName) \
  _interwiki.insert(__shortcut, __enum); \
  _localizedNames.insert(__enum, QString::fromWCharArray(__localizedName)); \
  _translationSectionNames.insert(__enum, QString::fromWCharArray(__translationSectionName))
  // Sorted by language name in English.
  // A
  L3(Abkhazian,     "ab",         L"Аҧсуа",            L"Abkhazian");
  L3(Afar,          "aa",         L"Qafár af",         L"Afar");
  L3(Afrikaans,     "af",         L"Afrikaans",        L"Afrikaans");
  L3(Akan,          "ak",         L"Akan",             L"Akan");
  L3(Albanian,      "sq",         L"Shqip",            L"Albanian");
  L3(Amharic,       "am",         L"አማርኛ",                                   L"Amharic");
  L3(AngloSaxon,    "ang",        L"Anglo-Saxon",      L"AngloSaxon");
  L3(Arabic,        "ar",         L"العربية",          L"Arabic");
  L3(Aragonese,     "an",         L"Aragonés",         L"Aragonese");
  L3(Armenian,      "hy",         L"Հայերեն",                    L"Armenian");
  L3(Assamese,      "as",         L"অসমীয়া",                        L"Assamese");
  L3(Asturian,      "ast",        L"Asturianu",        L"Asturian");
  L3(Avaric,        "av",         L"Авар",             L"Avaric");
  L1(Avestan,       "ae"); // mediawiki does not know this language
  L3(Aymara,        "ay",         L"Aymar aru",        L"Aymara");
  L3(Azerbaijani,   "az",         L"Azərbaycan",       L"Azerbaijani");
  // B
  L3(Bambara,       "bm",         L"Bamanankan",       L"Bambara");
  L3(Bashkir,       "ba",         L"Башҡорт",          L"Bashkir");
  L3(Basque,        "eu",         L"Euskara",          L"Basque");
  L3(Belarusian,    "be",         L"Беларуская",       L"Belarusian");
  L3(Bengali,       "bn",         L"বাংলা",                            L"Bengali");
  L3(Bihari,        "bh",         L"भोजपुरी",                          L"Bihari");
  L3(Bislama,       "bi",         L"Bislama",          L"Bislama");
  L3(Bosnian,       "bs",         L"Bosanski",         L"Bosnian");
  L3(Breton,        "br",         L"Brezhoneg",        L"Breton");
  L3(Bulgarian,     "bg",         L"Български",        L"Bulgarian");
  L3(Burmese,       "my",         L"Myanmasa",         L"Burmese");
  // C
  L2(Catalan,       "ca",         L"Català");
  L2(Chamorro,      "ch",         L"Chamoru");
  L2(Chechen,       "ce",         L"Нохчийн");
  L2(Cherokee,      "chr",        L"ᏣᎳᎩ");
  L2(Chichewa,      "ny",         L"Chi-Chewa");
  L2(Chinese,       "zh",         L"中文");
  L2(ChurchSlavic,  "cu",         L"Словѣ́ньскъ / ⰔⰎⰑⰂⰡⰐⰠⰔⰍⰟ");
  L2(Chuvash,       "cv",         L"Чăвашла");
  L2(Cornish,       "kw",         L"Kernewek");
  L2(Corsican,      "co",         L"Corsu");
  L2(Cree,          "cr",         L"Nēhiyawēwin / ᓀᐦᐃᔭᐍᐏᐣ");
  L2(Croatian,      "hr",         L"Hrvatski");
  L3(Czech,         "cs",         L"Česky",            L"Czech");
  // D
  L2(Danish,        "da",         L"Dansk");
  L2(Divehi,        "dv",         L"ދިވެހިބަސް");
  L2(Dutch,         "nl",         L"Nederlands");
  L2(Dzongkha,      "dz",         L"ཇོང་ཁ");
  // E
  L2(English,       "en",         L"English");
  L2(Esperanto,     "eo",         L"Esperanto");
  L2(Estonian,      "et",         L"Eesti");
  L2(Ewe,           "ee",         L"Eʋegbe");
  // F
  L2(Faroese,       "fo",         L"Føroyskt");
  L2(Fijian,        "fj",         L"Na Vosa Vakaviti");
  L2(Finnish,       "fi",         L"Suomi");
  L2(French,        "fr",         L"Français");
  L2(Fualah,        "ff",         L"Fulfulde");
  // G
  L2(Galician,      "gl",         L"Galego");
  L2(Ganda,         "lg",         L"Luganda");
  L2(Georgian,      "ka",         L"ქართული");
  L2(German,        "de",         L"Deutsch");
  L2(Greek,         "el",         L"Ελληνικά");
  L2(Guarani,       "gn",         L"Avañe'ẽ");
  L2(Gujarati,      "gu",         L"ગુજરાતી");
  // H
  L2(Haitian,       "ht",         L"Kreyòl ayisyen");
  L2(Hausa,         "ha",         L"هَوُسَ");
  L2(Hebrew,        "he",         L"עברית");
  L2(Herero,        "hz",         L"Otsiherero");
  L2(Hindi,         "hi",         L"हिन्दी");
  L2(HiriMotu,      "ho",         L"Hiri Motu");
  L2(Hungarian,     "hu",         L"Magyar");
  // I
  L2(Icelandic,     "is",         L"Íslenska");
  L2(Ido,           "io",         L"Ido");
  L2(Igbo,          "ig",         L"Igbo");
  L2(Indonesian,    "id",         L"Bahasa Indonesia");
  L2(Interlingua,   "ia",         L"Interlingua");
  L2(Interlingue,   "ie",         L"Interlingue");
  L2(Inuktitut,     "iu",         L"ᐃᓄᒃᑎᑐᑦ/inuktitut");
  L2(Inupiaq,       "ik",         L"Iñupiak");
  L2(Irish,         "ga",         L"Gaeilge");
  L2(Italian,       "it",         L"Italiano");
  // J
  L2(Japanese,      "ja",         L"日本語");
  L2(Javanese,      "jv",         L"Basa Jawa");
  // K
  L2(Kalaallisut,   "kl",         L"Kalaallisut");
  L2(Kannada,       "kn",         L"ಕನ್ನಡ");
  L2(Kanuri,        "kr",         L"Kanuri");
  L2(Kashmiri,      "ks",         L"कश्मीरी - (كشميري)");
  L2(Kashubian,     "csb",        L"Kaszëbsczi");
  L2(Kazakh,        "kk",         L"Қазақша");
  L2(Khmer,         "km",         L"ភាសាខ្មែរ");
  L2(Kikuyu,        "ki",         L"Gĩkũyũ");
  L2(Kinyarwanda,   "rw",         L"Kinyarwanda");
  L2(Kirghiz,       "ky",         L"Кыргызча");
  L2(Kirundi,       "rn",         L"Kirundi");
  L2(Komi,          "kv",         L"Коми");
  L2(Kongo,         "kg",         L"Kongo");
  L2(Korean,        "ko",         L"한국어");
  L2(Kurdish,       "ku",         L"Kurdî / كوردی");
  L2(Kwanyama,      "kj",         L"Kwanyama");
  // L
  L2(Lao,              "lo",         L"ລາວ");
  L2(Latin,            "la",         L"Latina");
  L2(Latvian,          "lv",         L"Latviešu");
  L2(Limburgish,       "li",         L"Limburgs");
  L2(Lingala,          "ln",         L"Lingála");
  L2(Lithuanian,       "lt",         L"Lietuvių");
  L2(Lojban,           "jbo",        L"Lojban");
  L2(LowSaxon,         "nds",        L"Plattdüütsch");
  L1(LubaKatanga,      "lu");  // not supported in MEdiawiki
  L2(Luxembourgish,    "lb",         L"Lëtzebuergesch");
  // M
  L2(Macedonian,       "mk",         L"Македонски");
  L2(Malagasy,         "mg",         L"Malagasy");
  L2(Malay,            "ms",         L"Bahasa Melayu");
  L2(Malayalam,        "ml",         L"മലയാളം");
  L2(Maltese,          "mt",         L"Malti");
  L2(Manx,             "gv",         L"Gaelg");
  L2(Maori,            "mi",         L"Māori");
  L2(Marathi,          "mr",         L"मराठी");
  L2(Marshallese,      "mh",         L"Ebon");
  L2(MinNan,           "zh-min-nan", L"Bân-lâm-gú");
  L2(Mongolian,        "mn",         L"Монгол");
  // N
  L2(Nauru,            "na",         L"Dorerin Naoero");
  L2(Navajo,           "nv",         L"Diné bizaad");
  L2(Ndonga,           "ng",         L"Oshiwambo");
  L2(Nepali,           "ne",         L"नेपाली");
  L1(NorthNdebele,     "nd"); // not supported by MediaWiki
  L2(NorthernSami,     "se",         L"Sámegiella");
  L2(Norwegian,        "no",         L"Norsk (bokmål)‬");
  L2(NorwegianBokmal,  "nb",         L"Norsk (bokmål)‬");
  L2(NorwegianNynorsk, "nn",         L"Norsk (nynorsk)‬");
  // O
  L2(Occitan,          "oc",         L"Occitan");
  L1(Ojibwa,           "oj"); // not supported in MediaWiki
  L2(Oriya,            "or",         L"ଓଡ଼ିଆ");
  L2(Oromo,            "om",         L"Oromoo");
  L2(Ossetian,         "os",         L"Иронау");
  // P
  L2(Pali,             "pi",         L"पािऴ");
  L2(Panjabi,          "pa",         L"ਪੰਜਾਬੀ");
  L2(Pashto,           "ps",         L"پښتو");
  L2(Persian,          "fa",         L"فارسی");
  L2(Polish,           "pl",         L"Polski");
  L2(Portuguese,       "pt",         L"Português");
  // Q
  L2(Quechua,          "qu",         L"Runa Simi");
  // R
  L2(RaetoRomance,     "rm",         L"Rumantsch");
  L2(Romanian,         "ro",         L"Română");
  L2(Russian,          "ru",         L"Русский");
  // S
  L2(Samoan,           "sm",         L"Gagana Samoa");
  L2(Sango,            "sg",         L"Sängö");
  L2(Sanskrit,         "sa",         L"संस्कृत");
  L2(Sardinian,        "sc",         L"Sardu");
  L2(ScottishGaelic,   "gd",         L"Gàidhlig");
  L2(Serbian,          "sr",         L"Српски / Srpski");
  L2(SerboCroatian,    "sh",         L"Srpskohrvatski / Српскохрватски");
  L2(Shona,            "sn",         L"chiShona");
  L2(SichuanYi,        "ii",         L"ꆇꉙ");
  L2(Sicilian,         "scn",        L"Sicilianu");
  L2(SimpleEnglish,    "simple",     L"Simple English");
  L2(Sindhi,           "sd",         L"سنڌي");
  L2(Sinhala,          "si",         L"සිංහල");
  L2(Slovak,           "sk",         L"Slovenčina");
  L2(Slovenian,        "sl",         L"Slovenščina");
  L2(Somali,           "so",         L"Soomaaliga");
  L1(SouthNdebele,     "nr"); // not supported in MediaWiki
  L2(SouthernSotho,    "st",         L"Sesotho");
  L2(Spanish,          "es",         L"Español");
  L2(Sundanese,        "su",         L"Basa Sunda");
  L2(Swahili,          "sw",         L"Kiswahili");
  L2(Swati,            "ss",         L"SiSwati");
  L2(Swedish,          "sv",         L"Svenska");
  // T
  L2(Tagalog,          "tl",         L"Tagalog");
  L2(Tahitian,         "ty",         L"Reo Mā`ohi");
  L2(Tajik,            "tg",         L"Тоҷикӣ");
  L2(Tamil,            "ta",         L"தமிழ்");
  L2(Tatar,            "tt",         L"Tatarça/Татарча");
  L2(Telugu,           "te",         L"తెలుగు");
  L2(Thai,             "th",         L"ไทย");
  L2(Tibetan,          "bo",         L"བོད་ཡིག");
  L2(Tigrinya,         "ti",         L"ትግርኛ");
  L2(Tonga,            "to",         L"lea faka-Tonga");
  L2(Tsonga,           "ts",         L"Xitsonga");
  L2(Tswana,           "tn",         L"Setswana");
  L2(Turkish,          "tr",         L"Türkçe");
  L2(Turkmen,          "tk",         L"Türkmençe");
  L2(Twi,              "tw",         L"Twi");
  // U
  L2(Uighur,           "ug",         L"Uyghurche‎ / ئۇيغۇرچە");
  L2(Ukrainian,        "uk",         L"Українська");
  L2(UpperSorbian,     "hsb",        L"Hornjoserbsce");
  L2(Urdu,             "ur",         L"اردو");
  L2(Uzbek,            "uz",         L"O'zbek");
  // V
  L2(Venda,            "ve",         L"Tshivenda");
  L2(Vietnamese,       "vi",         L"Tiếng Việt");
  L2(Volapuk,          "vo",         L"Volapük");
  // W
  L2(Walloon,          "wa",         L"Walon");
  L2(Welsh,            "cy",         L"Cymraeg");
  L2(WesternFrisian,   "fy",         L"Frysk");
  L2(Wolof,            "wo",         L"Wolof");
  // X
  L2(Xhosa,            "xh",         L"isiXhosa");
  // Y
  L2(Yiddish,          "yi",         L"ייִדיש");
  L2(Yoruba,           "yo",         L"Yorùbá");
  // Z
  L2(Zhuang,           "za",         L"Sawcuengh");
  L2(Zulu,             "zu",         L"isiZulu");
}
