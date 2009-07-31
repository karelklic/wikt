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
#ifndef HTMLENTITYNODE_H_
#define HTMLENTITYNODE_H_

#include "Node.h"

/// Represents entities like &nbsp; &#8203; &amp; etc.
class HtmlEntityNode : public Node
{
public:
  HtmlEntityNode(const QString &text)
    : Node(Node::HtmlEntity), _text(text) {}
  virtual QString toXHtml() const;
  virtual QString toXml(int indentLevel) const;

protected:
  QString _text;
};


#endif /* HTMLENTITYNODE_H_ */
