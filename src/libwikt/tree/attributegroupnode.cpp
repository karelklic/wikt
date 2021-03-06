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
#include "attributegroupnode.h"
#include "attributenode.h"

QString AttributeGroupNode::toXHtml() const
{
  QString result;
  foreach (Node *node, children())
  {
    result.append(" ");
    result.append(node->toXHtml());
  }
  return result;
}

QString AttributeGroupNode::toXml(int indentLevel) const
{
  QString indent(indentLevel, ' ');
  return indent + "<attribute_group>\n" +
    childrenToXml(indentLevel+1) +
    indent + "</attribute_group>\n";
}

bool AttributeGroupNode::hasAttribute(const QString &name) const
{
  foreach (const Node *node, children())
  {
    const AttributeNode *attributeNode = dynamic_cast<const AttributeNode*>(node);
    if (!attributeNode) continue;
    if (attributeNode->name() == name) return true;
  }
  return false;
}

QString AttributeGroupNode::getAttributeText(const QString &name) const
{
  foreach (const Node *node, children())
  {
    const AttributeNode *attributeNode = dynamic_cast<const AttributeNode*>(node);
    if (!attributeNode) continue;
    if (attributeNode->name() == name)
      return attributeNode->value();
  }
  return "";
}
