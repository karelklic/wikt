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
#include "HtmlElementNode.h"
#include "TableNode.h"
#include "AttributeGroupNode.h"

//===========================================================================
HtmlElementNode::HtmlElementNode(const QString &name, const QString &params,
    bool paired) : Node(Node::HtmlElement), _name(name),
    _paired(paired)
{
  // Normalize parameters.
  _params = params.trimmed();
}

//===========================================================================
QString HtmlElementNode::toXHtml() const
{
  if (!_xhtmlVisible) return "";
  // See also is displayed in the Related Pages side panel.
  if (isSeeAlsoNode()) return "";

  if (_paired)
  {
    return QString("<%1%2>%3</%1>")
      .arg(_name,  _params.length() == 0 ? "" : " " + _params, childrenToXHtml());
  }
  else
  {
    // Nowiki tag is not rendered in XHTML.
    if (_name.compare("nowiki", Qt::CaseInsensitive))
      return "";

    return QString("<%1%2/>")
      .arg(_name, _params.length() == 0 ? "" : " " + _params);
  }
}

//===========================================================================
QString HtmlElementNode::toXml(int indentLevel) const
{
  QString indent(indentLevel, ' ');
  return QString("%1<htmlElement name=\"%2\" params=\"%3\" "
      "isTranslationDivNode=\"%5\">\n%4%1</htmlElement>\n")
    .arg(indent)
    .arg(_name)
    .arg(_params)
    .arg(childrenToXml(indentLevel+1))
    .arg(findTranslationTable() ? "true" : "false");
}

//===========================================================================
bool HtmlElementNode::isSeeAlsoNode() const
{
  // it is either <div class="disambig-see-also">...</div> or
  // <div class="disambig-see-also-2">...</div>.
  return _name == "div" && _params.contains("disambig-see-also");
}

//===========================================================================
TableNode *HtmlElementNode::findTranslationTable() const
{
  if (_name != "div" || !_params.contains("NavFrame"))
    return 0;

  // Find NavContent child node.
  HtmlElementNode *navContent = 0;
  foreach (Node *node, children())
  {
    if (node->type() != Node::HtmlElement)
      continue;
    HtmlElementNode *element = dynamic_cast<HtmlElementNode*>(node);
    if (element->name() != "div")
      continue;
    if (!element->params().contains("NavContent"))
      continue;
    navContent = element;
    break;
  }

  if (!navContent)
    return 0;

  // Find the translation table in the NavContent.
  TableNode *transTable = 0;
  foreach (Node *node, navContent->children())
  {
    if (node->type() != Node::Table)
      continue;
    TableNode *tableNode = dynamic_cast<TableNode*>(node);
    if (!tableNode->hasAttributeGroupChild())
      continue;
    const AttributeGroupNode *attribs = tableNode->getAttributeGroupChild();
    if (!attribs->hasAttribute("class"))
      continue;
    if (!attribs->getAttributeText("class").contains("translations"))
      continue;

    transTable = tableNode;
    break;
  }

  return transTable;
}
