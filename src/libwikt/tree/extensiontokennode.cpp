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
#include "extensiontokennode.h"

//===========================================================================
ExtensionTokenNode::ExtensionTokenNode(const QString &name, const QString &value)
  : Node(Node::ExtensionToken), _name(name), _value(value)
{
}

//===========================================================================
QString ExtensionTokenNode::toXml(int indentLevel) const
{
  QString indent(indentLevel, ' ');
  return indent +
    QString("<extension_token name=\"%1\" value=\"%2\">%3</extension_token>\n")
      .arg(_name).arg(_value).arg(childrenToXml(indentLevel+1));
}
