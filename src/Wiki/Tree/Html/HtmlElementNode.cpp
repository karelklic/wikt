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

    return QString("<%1%2/>").arg(_name, _params.length() == 0 ? "" : " " + _params);
  }
}

//===========================================================================
QString HtmlElementNode::toXml(int indentLevel) const
{
  QString indent(indentLevel, ' ');
  return QString("%1<%2 %3>\n%4%1</%2>\n")
    .arg(indent, _name, _params, childrenToXml(indentLevel+1));
}

//===========================================================================
bool HtmlElementNode::isSeeAlsoNode() const
{
  // it is either <div class="disambig-see-also">...</div> or
  // <div class="disambig-see-also-2">...</div>.
  return _name == "div" && _params.contains("disambig-see-also");
}
