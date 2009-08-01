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
#include "parameterlist.h"

//===========================================================================
ParameterList::ParameterList() : _positionalParameterCount(0)
{
}

//===========================================================================
void ParameterList::insert(QString key, QString value)
{
  _parameters.insert(key, value);
}

//===========================================================================
void ParameterList::insert(QString value)
{
  insert(QString::number(_positionalParameterCount + 1), value);
  _positionalParameterCount += 1;
}

//===========================================================================
QString ParameterList::operator[](QString key) const
{
  if (_parameters.contains(key))
    return _parameters[key];

  return QString("&#x007b;&#x007b;&#x007b;%1&#x007d;&#x007d;&#x007d;").arg(key);
}

