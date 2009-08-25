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
#include "formattingfunctions.h"
#include <libwikt/debug.h>
#include <QLocale>

//===========================================================================
static QString formatNum(QString templateText)
{
  bool reverse = false;
  if (templateText.endsWith("|R"))
  {
    reverse = true;
    templateText.remove(templateText.length() - 2, 2);
  }

  QLocale english(QLocale::English, QLocale::UnitedStates);
  if (reverse)
  {
    bool ok;
    double d = english.toDouble(templateText, &ok);
    if (!ok) return templateText;
    return QString::number(d, 'f');
  }
  else
  {
    bool ok;
    double d = templateText.toDouble(&ok);
    if (!ok) return templateText;
    return english.toString(d, 'f');
  }
}

//===========================================================================
bool FormattingFunctions::isFormattingFunction(const QString &templateText)
{
  return templateText.startsWith("lc:") || templateText.startsWith("lcfirst:") || templateText.startsWith("uc:") || templateText.startsWith("ucfirst:") || templateText.startsWith("formatnum:");
}

//===========================================================================
QString FormattingFunctions::evaluate(const QString &templateText)
{
  QString trimmed = templateText.trimmed();
  int sep = trimmed.indexOf(":");
  CHECK(sep != -1);
  QString val = trimmed.mid(sep + 1).trimmed();
  if (val.length() == 0) return "";
  if (trimmed.startsWith("lc:"))
    return val.toLower();
  else if (trimmed.startsWith("lcfirst:"))
    return val.at(0).toLower() + val.mid(1);
  else if (trimmed.startsWith("uc:"))
    return val.toUpper();
  else if (trimmed.startsWith("ucfirst:"))
    return val.at(0).toUpper() + val.mid(1);
  else if (trimmed.startsWith("formatnum:"))
    return formatNum(val);
  dstderr("Unknown function.");
  return templateText;
}


