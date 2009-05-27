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
#include "../../Debug/Debug.h"
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
  return _codeToType.value(code.toLower(), Unknown);
}

//===========================================================================
Language::Type Language::fromLinkPrefixes(const QStringList &prefixes) const
{
  if (prefixes.empty()) return English;
  QString name = prefixes.first().toLower();
  if (_codeToType.contains(name))
    return _codeToType.value(name);

  return English;
}

//===========================================================================
QString Language::toCode(Language::Type lang) const
{
  QList<QString> codes = _typeToCode.values(lang);
  if (codes.empty())
    return "";

  // Return the first inserted value, which is the last in the values list.
  return codes.last();
}

//===========================================================================
QString Language::toLocalizedName(Language::Type lang) const
{
  return _typeToInterwiki.value(lang, "Unknown localized name");
}

//===========================================================================
QString Language::toTranslationSectionName(Language::Type lang) const
{
  QList<QString> names = _typeToTranslations.values(lang);
  if (names.empty())
    return "";

  // Return the first inserted value, which is the last in the values list.
  return names.last();
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
#include "LanguagesGenerated.cpp.inc"
}
