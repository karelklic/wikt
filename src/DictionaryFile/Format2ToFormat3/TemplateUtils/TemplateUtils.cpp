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
#include "TemplateUtils.h"

//===========================================================================
void TemplateUtils::getParts(const QString &templateText, QList<QString> &output)
{
  // If linkLevel > 0, the iterator is inside a link.
  // Handles embedded links, because our template evaluation code might
  // cause them.
  int linkLevel = 0;
  QString part;
  QChar last = ' ';
  for (QString::const_iterator it = templateText.begin();
       it != templateText.end(); ++it)
  {
    if (*it == '[' && last == '[')
    {
      ++linkLevel;
      last = ' '; // clear the last, so the algorithm works for [[[[.
      part.append(*it);
      continue;
    }
    else if (*it == ']' && last == ']' && linkLevel > 0)
    {
      --linkLevel;
      last = ' '; // clear the last, so the algorithm works for ]]]].
      part.append(*it);
      continue;
    }
    else if (*it == '|' && linkLevel == 0)
    {
      output.append(part); // *not* to be trimmed
      part.clear();
      last = ' ';
      continue;
    }
    last = *it;
    part.append(*it);
  }
  output.append(part); // *not* to be trimmed
  output[0] = output[0].trimmed();
}

//===========================================================================
void TemplateUtils::_addParameterToList(const QString &paramText, ParameterList &dest)
{
  // Spaces and newlines are stripped from the start and end of parameter
  // values of named parameters, but not of implicitly numbered parameters.
  // Source: http://meta.wikimedia.org/wiki/Help:Template#Parameters
  if (!paramText.contains("="))
  {
    dest.insert(paramText); // *not* to be trimmed
    return;
  }

  int sep = paramText.indexOf("=");
  QString key = paramText.mid(0, sep).trimmed(); // to be trimmed
  QString value = paramText.mid(sep + 1).trimmed(); // to be trimmed
  dest.insert(key, value);
}

//===========================================================================
ParameterList TemplateUtils::getParameterList(const QList<QString> &parts)
{
  ParameterList result;
  for (int i = 1; i < parts.size(); ++i)
    _addParameterToList(parts[i], result);
  return result;
}

//===========================================================================
QString TemplateUtils::evaluateParameter(const QString &parameterText, const ParameterList &params)
{
  PROFILER;
  QList<QString> parts;
  getParts(parameterText, parts);
  // If there is no pipe separator, everything is handled by parameter list.
  // If the name is in the parameter list, the parameter value is returned.
  if (parts.size() < 2 || params.contains(parts[0]))
    return params[parts[0]];

  // Else return default value.
  return parts[1];
}
