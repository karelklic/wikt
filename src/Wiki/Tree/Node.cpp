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
#include "Node.h"
#include "Attribute/AttributeGroupNode.h"

//===========================================================================
Node::Node(Type type) : _xhtmlVisible(true), _type(type)
{
}

//===========================================================================
Node::~Node()
{
  qDeleteAll(_children);
}

//===========================================================================
QString Node::toXHtml() const
{
  if (!_xhtmlVisible) return "";
  return childrenToXHtml();
}

//===========================================================================
QString Node::toXml(int indentLevel) const
{
  return childrenToXml(indentLevel);
}

//===========================================================================
QString Node::toText() const
{
  QString result;
  foreach (Node *node, _children)
    result += node->toText();
  return result;
}

//===========================================================================
QString Node::childrenToXHtml(bool skipAttributeGroup) const
{
  QString result;
  foreach (Node *node, _children)
  {
    if (skipAttributeGroup && node->type() == Node::AttributeGroup) continue;
    result.append(node->toXHtml());
  }
  return result;
}

//===========================================================================
QString Node::childrenToXml(int indentLevel) const
{
  QString ret;
  for (int i = 0; i < _children.count(); ++i)
    ret.append(_children.at(i)->toXml(indentLevel));
  return ret;
}

//===========================================================================
QString Node::childrenToText() const
{
  QString ret;
  foreach (Node *node, _children)
    ret.append(node->toText());
  return ret;
}

//===========================================================================
QString Node::toXmlEscaped(const QString &text)
{
  QString result;
  result.reserve(text.size());
  const QChar *data = text.data();
  while (!data->isNull())
  {
    if (data->unicode() == '<')      result += "&lt;";
    else if (data->unicode() == '>') result += "&gt;";
    else if (data->unicode() == '&') result += "&amp;";
    else if (data->unicode() == '"') result += "&quot;";
    else result += *data;
    ++data;
  }
  return result;
}

//===========================================================================
bool Node::hasAttributeGroupChild() const
{
  foreach (const Node *node, _children)
  {
    if (node->type() == Node::AttributeGroup)
      return true;
  }
  return false;
}

//===========================================================================
const AttributeGroupNode *Node::getAttributeGroupChild() const
{
  foreach (const Node *node, _children)
  {
    if (node->type() == Node::AttributeGroup)
      return dynamic_cast<const AttributeGroupNode*>(node);
  }
  return 0;
}
