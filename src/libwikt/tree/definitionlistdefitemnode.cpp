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
#include "definitionlistdefitemnode.h"

//===========================================================================
DefinitionListDefItemNode::DefinitionListDefItemNode() : Node(Node::DefinitionListDefItem)
{
}

//===========================================================================
QString DefinitionListDefItemNode::toXHtml() const
{
  if (!_xhtmlVisible) return "";
  return QString("<dd>%1</dd>").arg(childrenToXHtml());
}

//===========================================================================
QString DefinitionListDefItemNode::toXml(int indentLevel) const
{
  QString indent(indentLevel, ' ');
  return indent + QString("<dditem>\n") +
    childrenToXml(indentLevel+1) +
    indent + "</dditem>\n";
}
