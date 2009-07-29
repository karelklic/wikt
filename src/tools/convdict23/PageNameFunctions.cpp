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
#include "PageNameFunctions.h"

//===========================================================================
bool PageNameFunctions::isPageNameFunction(const QString &templateText)
{
  QString trimmed = templateText.trimmed();
  return trimmed == "SERVER" || trimmed == "SERVERNAME" ||
    trimmed == "PAGENAME" || trimmed == "PAGENAMEE" ||
    trimmed == "BASEPAGENAME" || trimmed == "BASEPAGENAMEE" ||
    trimmed == "SUBPAGENAME"  || trimmed == "SUBPAGENAMEE" ||
    trimmed == "FULLPAGENAME" || trimmed == "FULLPAGENAMEE" ||
    trimmed == "NAMESPACE"    || trimmed == "NAMESPACEE";
}

//===========================================================================
/// Returns the name of the current page, including all levels
/// (Title/Subtitle). This does not include the name of the namespace.
static QString functionPageName(const QString &pageName)
{
  if (pageName.contains(':'))
    return pageName.section(':', 1);
  else
    return pageName;
}

//===========================================================================
/// More URL-friendly percent encoded special characters
/// (To use an article name in an external link).
static QString functionPageNameE(const QString &pageName)
{
  return functionPageName(pageName).replace(' ', '_');
}

//===========================================================================
/// The base name of a subpage ("Title/Other" on
/// "Title/Other/Subtitle"), see
/// http://meta.wikimedia.org/wiki/Help:Link#Subpage_feature.
static QString functionBasePageName(const QString &pageName)
{
  QString name(functionPageName(pageName));
  if (name.contains('/'))
    return name.section('/', 0, -2);
  else
    return name;
}

//===========================================================================
/// The basename of a subpage ("Title/Other" on
/// "Title/Other/Subtitle"), see
/// http://meta.wikimedia.org/wiki/Help:Link#Subpage_feature.
static QString functionBasePageNameE(const QString &pageName)
{
  return functionBasePageName(pageName).replace(' ', '_');
}

//===========================================================================
/// Name of the current page, excluding parent pages ("Subtitle" on
/// "Title/Other/Subtitle") in namespaces supporting subpages, see
/// http://meta.wikimedia.org/wiki/Help:Link#Subpage_feature
static QString functionSubPageName(const QString &pageName)
{
  QString name(functionPageName(pageName));
  if (name.contains('/'))
    return name.section('/', -1, -1);
  else
    return name;
}

//===========================================================================
/// Name of the current page, excluding parent pages ("Subtitle" on
/// "Title/Other/Subtitle") in namespaces supporting subpages, see
/// http://meta.wikimedia.org/wiki/Help:Link#Subpage_feature
static QString functionSubPageNameE(const QString &pageName)
{
  return functionSubPageName(pageName).replace(' ', '_');
}

//===========================================================================
/// Shorthand for NAMESPACE+PAGENAME.
static QString functionFullPageName(const QString &pageName)
{
  return pageName;
}

//===========================================================================
/// Shorthand for NAMESPACE+PAGENAME.
static QString functionFullPageNameE(const QString &pageName)
{
  return functionFullPageName(pageName).replace(' ', '_');
}

//===========================================================================
/// Returns the name of the namespace the current page resides in.
/// Note that this returns an empty string for the main (article) space.
static QString functionNamespace(const QString &pageName)
{
  if (pageName.contains(':'))
    return pageName.section(':', 0, 0);
  else
    return "";
}

//===========================================================================
/// Returns the name of the namespace the current page resides in.
/// Note that this returns an empty string for the main (article) space.
static QString functionNamespaceE(const QString &pageName)
{
  return functionNamespace(pageName).replace(' ', '_');
}

//===========================================================================
QString PageNameFunctions::evaluate(const QString &templateText,
  const QString &pageName)
{
  PROFILER;
  QString trimmed = templateText.trimmed();
  if (trimmed == "SERVER")             return ""; // intentional
  else if (trimmed == "SERVERNAME")    return ""; // intentional
  else if (trimmed == "PAGENAME")      return functionPageName(pageName);
  else if (trimmed == "PAGENAMEE")     return functionPageNameE(pageName);
  else if (trimmed == "BASEPAGENAME")  return functionBasePageName(pageName);
  else if (trimmed == "BASEPAGENAMEE") return functionBasePageNameE(pageName);
  else if (trimmed == "SUBPAGENAME")   return functionSubPageName(pageName);
  else if (trimmed == "SUBPAGENAMEE")  return functionSubPageNameE(pageName);
  else if (trimmed == "FULLPAGENAME")  return functionFullPageName(pageName);
  else if (trimmed == "FULLPAGENAMEE") return functionFullPageNameE(pageName);
  else if (trimmed == "NAMESPACE")     return functionNamespace(pageName);
  else if (trimmed == "NAMESPACEE")    return functionNamespaceE(pageName);

  MSG("Unknown page name function.");
  return templateText;
}
