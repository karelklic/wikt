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

  // Return the first value.
  return codes.first();
}

//===========================================================================
QString Language::toLocalizedName(Language::Type lang) const
{
  return _typeToInterwiki.value(lang, "Unknown localized name");
}

//===========================================================================
template<typename T>
static inline QList<T> reverse(const QList<T> &l)
{
    QList<T> ret;
    for (int i=l.size() - 1; i>=0; --i)
        ret.append(l.at(i));
    return ret;
}

//===========================================================================
QStringList Language::toTranslationSectionNames(Language::Type lang) const
{
  return _typeToTranslations.values(lang);
}

//===========================================================================
bool Language::isTranslationVisible(Language::Type lang) const
{
  QStringList names = toTranslationSectionNames(lang);
  if (names.empty())
    return true;

  QSettings settings;
  QString settingName = "translations" + names.first();
  return settings.value(settingName, true).toBool();
}

//===========================================================================
void Language::setTranslationVisible(Language::Type lang, bool visible)
{
  QStringList names = toTranslationSectionNames(lang);
  if (names.empty())
    return;

  QSettings settings;
  QString settingName = "translations" + names.first();
  return settings.setValue(settingName, visible);
}

//===========================================================================
Language::Language()
{
#include "LanguagesGenerated.cpp.inc"
}
