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
  L3(Catalan,       "ca",         L"Català",           L"Catalan");
  L3(Chamorro,      "ch",         L"Chamoru",          L"Chamorro");
  L3(Chechen,       "ce",         L"Нохчийн",          L"Chechen");
  L3(Cherokee,      "chr",        L"ᏣᎳᎩ",           L"Cherokee");
  L3(Chichewa,      "ny",         L"Chi-Chewa",        L"Chichewa");
  L3(Chinese,       "zh",         L"中文",              L"Chinese");
  L3(ChurchSlavic,  "cu",         L"Словѣ́ньскъ / ⰔⰎⰑⰂⰡⰐⰠⰔⰍⰟ",  L"Church Slavic");
  L3(Chuvash,       "cv",         L"Чăвашла",          L"Chuvash");
  L3(Cornish,       "kw",         L"Kernewek",         L"Cornish");
  L3(Corsican,      "co",         L"Corsu",            L"Corsican");
  L3(Cree,          "cr",         L"Nēhiyawēwin / ᓀᐦᐃᔭᐍᐏᐣ",   L"Cree");
  L3(Croatian,      "hr",         L"Hrvatski",         L"Croatian");
  L3(Czech,         "cs",         L"Česky",            L"Czech");
  // D
  L3(Danish,        "da",         L"Dansk",            L"Danish");
  L3(Divehi,        "dv",         L"ދިވެހިބަސް",            L"Divehi");
  L3(Dutch,         "nl",         L"Nederlands",       L"Dutch");
  L3(Dzongkha,      "dz",         L"ཇོང་ཁ",      L"Dzongkha");
  // E
  L3(English,       "en",         L"English",          L"English");
  L3(Esperanto,     "eo",         L"Esperanto",        L"Esperanto");
  L3(Estonian,      "et",         L"Eesti",            L"Estonian");
  L3(Ewe,           "ee",         L"Eʋegbe",           L"Ewe");
  // F
  L3(Faroese,       "fo",         L"Føroyskt",         L"Faroese");
  L3(Fijian,        "fj",         L"Na Vosa Vakaviti", L"Fijian");
  L3(Finnish,       "fi",         L"Suomi",            L"Finnish");
  L3(French,        "fr",         L"Français",         L"French");
  L3(Fualah,        "ff",         L"Fulfulde",         L"Fualah");
  // G
  L3(Galician,      "gl",         L"Galego",           L"Galician");
  L3(Ganda,         "lg",         L"Luganda",          L"Ganda");
  L3(Georgian,      "ka",         L"ქართული",          L"Georgian");
  L3(German,        "de",         L"Deutsch",          L"German");
  L3(Greek,         "el",         L"Ελληνικά",         L"Greek");
  L3(Guarani,       "gn",         L"Avañe'ẽ",          L"Guaraní");
  L3(Gujarati,      "gu",         L"ગુજરાતી",                         L"Gujarati");
  // H
  L3(Haitian,       "ht",         L"Kreyòl ayisyen",   L"Haitian");
  L3(Hausa,         "ha",         L"هَوُسَ",              L"Hausa");
  L3(Hebrew,        "he",         L"עברית",            L"Hebrew");
  L3(Herero,        "hz",         L"Otsiherero",       L"Herero");
  L3(Hindi,         "hi",         L"हिन्दी",                             L"Hindi");
  L3(HiriMotu,      "ho",         L"Hiri Motu",        L"HiriMotu");
  L3(Hungarian,     "hu",         L"Magyar",           L"Hungarian");
  // I
  L3(Icelandic,     "is",         L"Íslenska",         L"Icelandic");
  L3(Ido,           "io",         L"Ido",              L"Ido");
  L3(Igbo,          "ig",         L"Igbo",             L"Igbo");
  L3(Indonesian,    "id",         L"Bahasa Indonesia", L"Indonesian");
  L3(Interlingua,   "ia",         L"Interlingua",      L"Interlingua");
  L3(Interlingue,   "ie",         L"Interlingue",      L"Interlingue");
  L3(Inuktitut,     "iu",         L"ᐃᓄᒃᑎᑐᑦ/inuktitut", L"Inuktitut");
  L3(Inupiaq,       "ik",         L"Iñupiak",          L"Inupiaq");
  L3(Irish,         "ga",         L"Gaeilge",          L"Irish");
  L3(Italian,       "it",         L"Italiano",         L"Italian");
  // J
  L3(Japanese,      "ja",         L"日本語",            L"Japanese");
  L3(Javanese,      "jv",         L"Basa Jawa",        L"Javanese");
  // K
  L3(Kalaallisut,   "kl",         L"Kalaallisut",      L"Kalaallisut");
  L3(Kannada,       "kn",         L"ಕನ್ನಡ",              L"Kannada");
  L3(Kanuri,        "kr",         L"Kanuri",           L"Kanuri");
  L3(Kashmiri,      "ks",         L"कश्मीरी - (كشميري)",       L"Kashmiri");
  L3(Kashubian,     "csb",        L"Kaszëbsczi",       L"Kashubian");
  L3(Kazakh,        "kk",         L"Қазақша",          L"Kazakh");
  L3(Khmer,         "km",         L"ភាសាខ្មែរ", L"Khmer");
  L3(Kikuyu,        "ki",         L"Gĩkũyũ",           L"Kikuyu");
  L3(Kinyarwanda,   "rw",         L"Kinyarwanda",      L"Kinyarwanda");
  L3(Kirghiz,       "ky",         L"Кыргызча",         L"Kirghiz");
  L3(Kirundi,       "rn",         L"Kirundi",          L"Kirundi");
  L3(Komi,          "kv",         L"Коми",             L"Komi");
  L3(Kongo,         "kg",         L"Kongo",            L"Kongo");
  L3(Korean,        "ko",         L"한국어",                                  L"Korean");
  L3(Kurdish,       "ku",         L"Kurdî / كوردی",    L"Kurdish");
  L3(Kwanyama,      "kj",         L"Kwanyama",         L"Kwanyama");
  // L
  L3(Lao,              "lo",         L"ລາວ",                        L"Lao");
  L3(Latin,            "la",         L"Latina",        L"Latin");
  L3(Latvian,          "lv",         L"Latviešu",      L"Latvian");
  L3(Limburgish,       "li",         L"Limburgs",      L"Limburgish");
  L3(Lingala,          "ln",         L"Lingála",       L"Lingala");
  L3(Lithuanian,       "lt",         L"Lietuvių",      L"Lithuanian");
  L3(Lojban,           "jbo",        L"Lojban",        L"Lojban");
  L3(LowSaxon,         "nds",        L"Plattdüütsch",  L"Low Saxon");
  L1(LubaKatanga,      "lu");  // not supported in MEdiawiki
  L3(Luxembourgish,    "lb",         L"Lëtzebuergesch", L"Luxembourgish");
  // M
  L3(Macedonian,       "mk",         L"Македонски",    L"Macedonian");
  L3(Malagasy,         "mg",         L"Malagasy",      L"Malagasy");
  L3(Malay,            "ms",         L"Bahasa Melayu", L"Malay");
  L3(Malayalam,        "ml",         L"മലയാളം",                  L"Malayalam");
  L3(Maltese,          "mt",         L"Malti",         L"Maltese");
  L3(Manx,             "gv",         L"Gaelg",         L"Manx");
  L3(Maori,            "mi",         L"Māori",         L"Maori");
  L3(Marathi,          "mr",         L"मराठी",                      L"Marathi");
  L3(Marshallese,      "mh",         L"Ebon",          L"Marshallese");
  L3(MinNan,           "zh-min-nan", L"Bân-lâm-gú",    L"Min Nan");
  L3(Mongolian,        "mn",         L"Монгол",        L"Mongolian");
  // N
  L3(Nauru,            "na",         L"Dorerin Naoero", L"Nauru");
  L3(Navajo,           "nv",         L"Diné bizaad",   L"Navajo");
  L3(Ndonga,           "ng",         L"Oshiwambo",     L"Ndonga");
  L3(Nepali,           "ne",         L"नेपाली",                      L"Nepali");
  L1(NorthNdebele,     "nd"); // not supported by MediaWiki
  L3(NorthernSami,     "se",         L"Sámegiella",    L"NorthernSami");
  L3(Norwegian,        "no",         L"Norsk (bokmål)‬", L"Norwegian");
  L2(NorwegianBokmal,  "nb",         L"Norsk (bokmål)‬");
  L2(NorwegianNynorsk, "nn",         L"Norsk (nynorsk)‬");
  // O
  L3(Occitan,          "oc",         L"Occitan",        L"Occitan");
  L1(Ojibwa,           "oj"); // not supported in MediaWiki
  L3(Oriya,            "or",         L"ଓଡ଼ିଆ",           L"Oriya");
  L3(Oromo,            "om",         L"Oromoo",         L"Oromo");
  L3(Ossetian,         "os",         L"Иронау",         L"Ossetian");
  // P
  L3(Pali,             "pi",         L"पािऴ",                       L"Pali");
  L3(Panjabi,          "pa",         L"ਪੰਜਾਬੀ",                       L"Panjabi");
  L3(Pashto,           "ps",         L"پښتو",          L"Pashto");
  L3(Persian,          "fa",         L"فارسی",          L"Persian");
  L3(Polish,           "pl",         L"Polski",         L"Polish");
  L3(Portuguese,       "pt",         L"Português",      L"Portuguese");
  // Q
  L3(Quechua,          "qu",         L"Runa Simi",      L"Quechua");
  // R
  L3(RaetoRomance,     "rm",         L"Rumantsch",      L"Raeto Romance");
  L3(Romanian,         "ro",         L"Română",         L"Romanian");
  L3(Russian,          "ru",         L"Русский",        L"Russian");
  // S
  L3(Samoan,           "sm",         L"Gagana Samoa",   L"Samoan");
  L3(Sango,            "sg",         L"Sängö",          L"Sango");
  L3(Sanskrit,         "sa",         L"संस्कृत",                       L"Sanskrit");
  L3(Sardinian,        "sc",         L"Sardu",          L"Sardinian");
  L3(ScottishGaelic,   "gd",         L"Gàidhlig",       L"Scottish Gaelic");
  L3(Serbian,          "sr",         L"Српски / Srpski", L"Serbian");
  L3(SerboCroatian,    "sh",         L"Srpskohrvatski / Српскохрватски", L"Serbo Croatian");
  L3(Shona,            "sn",         L"chiShona",       L"Shona");
  L3(SichuanYi,        "ii",         L"ꆇꉙ",           L"Sichuan Yi");
  L3(Sicilian,         "scn",        L"Sicilianu",      L"Sicilian");
  L3(SimpleEnglish,    "simple",     L"Simple English", L"Simple English");
  L3(Sindhi,           "sd",         L"سنڌي",          L"Sindhi");
  L3(Sinhala,          "si",         L"සිංහල",          L"Sinhala");
  L3(Slovak,           "sk",         L"Slovenčina",     L"Slovak");
  L3(Slovenian,        "sl",         L"Slovenščina",    L"Slovenian");
  L3(Somali,           "so",         L"Soomaaliga",     L"Somali");
  L1(SouthNdebele,     "nr"); // not supported in MediaWiki
  L3(SouthernSotho,    "st",         L"Sesotho",        L"SouthernSotho");
  L3(Spanish,          "es",         L"Español",        L"Spanish");
  L3(Sundanese,        "su",         L"Basa Sunda",     L"Sundanese");
  L3(Swahili,          "sw",         L"Kiswahili",      L"Swahili");
  L3(Swati,            "ss",         L"SiSwati",        L"Swati");
  L3(Swedish,          "sv",         L"Svenska",        L"Swedish");
  // T
  L3(Tagalog,          "tl",         L"Tagalog",        L"Tagalog");
  L3(Tahitian,         "ty",         L"Reo Mā`ohi",     L"Tahitian");
  L3(Tajik,            "tg",         L"Тоҷикӣ",         L"Tajik");
  L3(Tamil,            "ta",         L"தமிழ்",                        L"Tamil");
  L3(Tatar,            "tt",         L"Tatarça/Татарча", L"Tatar");
  L3(Telugu,           "te",         L"తెలుగు",          L"Telugu");
  L3(Thai,             "th",         L"ไทย",            L"Thai");
  L3(Tibetan,          "bo",         L"བོད་ཡིག", L"Tibetan");
  L3(Tigrinya,         "ti",         L"ትግርኛ",                                 L"Tigrinya");
  L3(Tonga,            "to",         L"lea faka-Tonga",  L"Tonga");
  L3(Tsonga,           "ts",         L"Xitsonga",        L"Tsonga");
  L3(Tswana,           "tn",         L"Setswana",        L"Tswana");
  L3(Turkish,          "tr",         L"Türkçe",          L"Turkish");
  L3(Turkmen,          "tk",         L"Türkmençe",       L"Turkmen");
  L3(Twi,              "tw",         L"Twi",             L"Twi");
  // U
  L3(Uighur,           "ug",         L"Uyghurche‎ / ئۇيغۇرچە",  L"Uighur");
  L3(Ukrainian,        "uk",         L"Українська",      L"Ukrainian");
  L3(UpperSorbian,     "hsb",        L"Hornjoserbsce",   L"Upper Sorbian");
  L3(Urdu,             "ur",         L"اردو",            L"Urdu");
  L3(Uzbek,            "uz",         L"O'zbek",          L"Uzbek");
  // V
  L3(Venda,            "ve",         L"Tshivenda",       L"Venda");
  L3(Vietnamese,       "vi",         L"Tiếng Việt",      L"Vietnamese");
  L3(Volapuk,          "vo",         L"Volapük",         L"Volapuk");
  // W
  L3(Walloon,          "wa",         L"Walon",           L"Walloon");
  L3(Welsh,            "cy",         L"Cymraeg",         L"Welsh");
  L3(WesternFrisian,   "fy",         L"Frysk",           L"Western Frisian");
  L3(Wolof,            "wo",         L"Wolof",           L"Wolof");
  // X
  L3(Xhosa,            "xh",         L"isiXhosa",        L"Xhosa");
  // Y
  L3(Yiddish,          "yi",         L"ייִדיש",           L"Yiddish");
  L3(Yoruba,           "yo",         L"Yorùbá",          L"Yoruba");
  // Z
  L3(Zhuang,           "za",         L"Sawcuengh",       L"Zhuang");
  L3(Zulu,             "zu",         L"isiZulu",         L"Zulu");
}
