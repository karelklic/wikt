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
#include "ParserFunctions.h"
#include "ExprParser/ExprDriver.h"
#include "TemplateUtils.h"
#include <libwikt/Unicode.h>
#include <libwikt/Prerequisites.h>
#include <QTextStream>

//===========================================================================
static QString functionIf(const QList<QString> &parts)
{
  if (parts.size() < 2) return "";
  int sep = parts[0].indexOf(":"); // is valid from definition, never -1
  QString expression = parts[0].mid(sep + 1).trimmed();
  if (expression != "")
    return parts[1].trimmed();
  else
    return parts.size() > 2 ? parts[2].trimmed() : "";
}

//===========================================================================
static QString functionIfEq(const QList<QString> &parts)
{
  if (parts.size() < 3) return "";
  int sep = parts[0].indexOf(":"); // is valid from definition, never -1
  QString first = parts[0].mid(sep + 1).trimmed();
  if (first == parts[1])
    return parts[2].trimmed();
  else
    return parts.size() > 3 ? parts[3].trimmed() : "";
}

//===========================================================================
static QString functionIfExist(const QList<QString> &parts, Format2Reader &reader)
{
  int sep = parts[0].indexOf(":"); // is valid from definition, never -1
  QString pageName = parts[0].mid(sep + 1).trimmed();
  if (reader.exist(pageName))
    return parts.size() > 1 ? parts[1].trimmed() : "";
  else
    return parts.size() > 2 ? parts[2].trimmed() : "";
}

//===========================================================================
/// #switch implementation.
/// Spaces are stripped both from index values and from results.
/// Source: http://meta.wikimedia.org/wiki/Help:Newlines_and_spaces#Switch
static QString functionSwitch(const QList<QString> &parts)
{
  // handle empty switch {{#switch: expr}}
  if (parts.size() <= 1) return "";

  // get the comparison string and store it to "expression".
  int sep = parts[0].indexOf(":"); // is valid from definition, never -1
  QString expression = parts[0].mid(sep + 1).trimmed();

  // find the right case
  QString defaultValue;
  for (int i = 1; i < parts.size(); ++i)
  {
    int sepIndex = parts[i].indexOf("=");
    if (sepIndex != -1) // Case type: "case = result"
    {
      QString case_ = parts[i].mid(0, sepIndex).trimmed();
      QString result = parts[i].mid(sepIndex + 1).trimmed();
      if (expression == case_)
        return result;
      else if (case_.compare("#default", Qt::CaseInsensitive) == 0)
        defaultValue = result;
    }
    else // Case type: "case" without '='
    {
      // last case is the default value that is returned
      if (i == parts.size() - 1) return parts[i].trimmed();

      // not the last case, but matches
      // look for the nearest following part with "=" and
      // change the expression to that
      if (expression == parts[i].trimmed())
      {
        for (int j = i + 1; j < parts.size(); ++j)
        {
          int sepIndexJ = parts[j].indexOf("=");
          if (sepIndexJ != -1)
          {
            // change comparison value so that it will be reached later
            QString case_ = parts[j].mid(0, sepIndexJ).trimmed();
            expression = case_;
            break;
          }
        }
      }
    }
  }
  return defaultValue;
}

//===========================================================================
static QString functionExpr(const QList<QString> &parts, const QString &entryName)
{
  int sep = parts[0].indexOf(":"); // is valid from definition, never -1
  QString expression = parts[0].mid(sep + 1).trimmed();

  // Empty expression returns empty string as a result.
  if (expression.length() == 0)
    return "";

  ExprDriver driver(entryName, false); // do not report errors for now
  driver.parse(Unicode::escape(expression));
  return driver.resultString();
}

//===========================================================================
// http://www.mediawiki.org/wiki/Help:Extension:ParserFunctions#.23ifexpr:
static QString functionIfExpr(const QList<QString> &parts, const QString &entryName)
{
  QString exprResult = functionExpr(parts, entryName);
  QString exprResultNormalized = exprResult.trimmed();

  if (exprResultNormalized.length() > 0 && exprResultNormalized != "0")
    return parts.size() > 1 ? parts[1].trimmed() : "";
  else
    return parts.size() > 2 ? parts[2].trimmed() : "";
}

//===========================================================================
bool ParserFunctions::isParserFunction(const QString &templateText)
{
  return templateText.startsWith("#if:", Qt::CaseInsensitive) ||
         templateText.startsWith("#ifeq:", Qt::CaseInsensitive) ||
         templateText.startsWith("#ifexpr:", Qt::CaseInsensitive) ||
         templateText.startsWith("#ifexist:", Qt::CaseInsensitive) ||
         templateText.startsWith("#switch:", Qt::CaseInsensitive) ||
         templateText.startsWith("#expr:", Qt::CaseInsensitive);
}

//===========================================================================
QString ParserFunctions::evaluate(const QString &templateText,
    Format2Reader &reader, const QString &entryName)
{
  PROFILER;
  QList<QString> parts;
  TemplateUtils::getParts(templateText, parts);
  if (parts[0].startsWith("#if:", Qt::CaseInsensitive))
    return functionIf(parts);
  else if (parts[0].startsWith("#ifeq:", Qt::CaseInsensitive))
    return functionIfEq(parts);
  else if (parts[0].startsWith("#ifexpr:", Qt::CaseInsensitive))
    return functionIfExpr(parts, entryName);
  else if (parts[0].startsWith("#ifexist:", Qt::CaseInsensitive))
    return functionIfExist(parts, reader);
  else if (parts[0].startsWith("#switch:", Qt::CaseInsensitive))
    return functionSwitch(parts);
  else if (parts[0].startsWith("#expr:", Qt::CaseInsensitive))
    return functionExpr(parts, entryName);
  MSG("Function not supported.");
  return templateText;
}
