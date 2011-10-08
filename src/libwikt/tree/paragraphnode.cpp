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
#include "paragraphnode.h"
#include "texttokennode.h"
#include "linknode.h"
#include "linktargetnode.h"

QString ParagraphNode::toXHtml() const
{
  if (!_xhtmlVisible) return "";

  // Empty paragraphs are not rendered in XHtml.
  QString childrenXHtml = childrenToXHtml();
  if (childrenXHtml.trimmed() == "") return "";

  // Standard XHtml output.
  return QString("<p>%1</p>").arg(childrenXHtml);
}

QString ParagraphNode::toXml(int indentLevel) const
{
  QString indent(indentLevel, ' ');
  return indent +
    "<para>\n" +
    childrenToXml(indentLevel+1) +
    indent + "</para>\n";
}

