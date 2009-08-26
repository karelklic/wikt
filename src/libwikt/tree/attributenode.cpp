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
#include "attributenode.h"

//===========================================================================
AttributeNode::AttributeNode(const QString &name, bool isNull) : Node(Node::Attribute), _name(name), _isNull(isNull)
{
}

//===========================================================================
QString AttributeNode::toXHtml() const
{
  return QString("%1=\"%2\"")
    .arg(_name)
    .arg(childrenToXHtml());
}

//===========================================================================
QString AttributeNode::toXml(int indentLevel) const
{
  QString indent(indentLevel, ' ');
  return indent +
    QString("<attribute name=\"%1\" isNull=\"%2\">\n")
      .arg(_name)
      .arg(_isNull ? "true" : "false") +
    childrenToXml(indentLevel+1) +
    indent + "</attribute>\n";
}
