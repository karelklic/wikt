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
#include "ArticleNode.h"
#include "../Heading/HeadingNode.h"
#include <QFile>
#include <QSettings>

//===========================================================================
QString ArticleNode::toXHtml() const
{
  PROFILER;
  if (!_xhtmlVisible) return "";
  return QString("<h1>%1</h1>%3")
    .arg(_name)
    .arg(childrenToXHtml());
}

//===========================================================================
QString ArticleNode::toXml(int indentLevel) const
{
  QString indent(indentLevel, ' ');
  return indent + "<article>\n" +
    childrenToXml(indentLevel+1) +
    indent + "</article>\n";
}

//===========================================================================
void ArticleNode::updateSectionVisibility()
{
  static const int DISABLED = MAX_HEADING_LEVEL + 1;
  int invisibleLevel = DISABLED;
  foreach(Node *node, children())
  {
    if (node->type() == Node::Heading)
    {
      HeadingNode *heading = dynamic_cast<HeadingNode*>(node);
      if (heading->level() <= invisibleLevel)
        invisibleLevel = (heading->xhtmlVisible() ? DISABLED : heading->level());
    }
    node->setXHtmlVisibility(invisibleLevel == DISABLED);
  }
}
