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
#include "namespaceurlfunctions.h"
#include <libwikt/urlutils.h>
#include <libwikt/project.h>
#include <libwikt/namespace.h>

//===========================================================================
bool NamespaceUrlFunctions::isFunction(const QString &templateText)
{
  return templateText.startsWith("ns:", Qt::CaseInsensitive) ||
    templateText.startsWith("localurl:", Qt::CaseInsensitive) ||
    templateText.startsWith("localurle:", Qt::CaseInsensitive) ||
    templateText.startsWith("fullurl:", Qt::CaseInsensitive) ||
    templateText.startsWith("fullurle:", Qt::CaseInsensitive) ||
    templateText.startsWith("urlencode:", Qt::CaseInsensitive);
}

//===========================================================================
/// Gets the magic namespace template name and returns the localized
/// name for the namespace.
/// For example:
/// * functionNs("ns:2") == "User"
/// * functionNs("ns:template") == "Template"
static QString functionNs(const QString &templateText)
{
  int sep = templateText.indexOf(":");
  CHECK_MSG(sep != -1, "Missing separator.");

  // Ignore any parameters. Parameters are separated by '|'.
  QString value = templateText.section('|', 0, 0);
  // Get the value after "ns:" in a normalized form.
  value = value.section(':', 1).trimmed();
  Namespace::Type ns = Namespace::instance().fromCode(value);
  CHECK(ns != Namespace::Unknown);
  return Namespace::instance().toLocalizedName(ns);
}

//===========================================================================
static QString functionLocalUrl(const QString &templateText)
{
  QString pageNameWithPrefix = templateText.section(':', 1); // after "localurl:"
  return UrlUtils::toUrl(pageNameWithPrefix).toString();
}

//===========================================================================
static QString functionFullUrl(const QString &templateText)
{
  QString pageNameWithPrefix = templateText.section(':', 1); // after "fullurl:"
  QString prefixOnly = templateText.section(':', 1, 1); // prefix such as "meta"

  if (Project::instance().isProjectPrefix(prefixOnly))
  {
    QString entryUrlSuffix = QString::fromAscii(QUrl::toPercentEncoding(
        templateText.section(':', 2))); // can be empty!

    Project::Type project = Project::instance().fromPrefix(prefixOnly);
    return Project::instance().toUrl(project, Language::English) + entryUrlSuffix;
  }

  // It links to wiktionary; return local url instead of external one.
  return UrlUtils::toUrl(pageNameWithPrefix).toString();
}

//===========================================================================
/// Encodes the text to a form suitable for use in a url by converting
/// spaces to + and escaping other characters as required.
static QString functionUrlEncode(const QString &templateText)
{
  QString text = templateText.section(':', 1).trimmed();
  text = QUrl::toPercentEncoding(text, QByteArray(" "), QByteArray("~"));
  return text.replace(" ", "+");
}

//===========================================================================
QString NamespaceUrlFunctions::evaluate(const QString &templateText)
{
  PROFILER;
  QString trimmed = templateText.trimmed();
  if (trimmed.startsWith("ns:", Qt::CaseInsensitive))
    return functionNs(templateText);
  else if (trimmed.startsWith("localurl:", Qt::CaseInsensitive) ||
      trimmed.startsWith("localurle:", Qt::CaseInsensitive))
    return functionLocalUrl(templateText);
  else if (trimmed.startsWith("fullurl:", Qt::CaseInsensitive) ||
      trimmed.startsWith("fullurle:", Qt::CaseInsensitive))
    return functionFullUrl(templateText);
  else if (trimmed.startsWith("urlencode:", Qt::CaseInsensitive))
    return functionUrlEncode(templateText);

  MSG("Unknown namespace url function.");
  return templateText;
}
