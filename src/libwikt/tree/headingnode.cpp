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
#include "headingnode.h"
#include "../debug.h"
#include <QRegExp>

static int uniqueHeaderCounter = 0;

//===========================================================================
HeadingNode::HeadingNode(int level) : Node(Node::Heading), _level(level),
  _headingType(Heading::Uninitialized)
{
  CHECK(level >= 1 && level <= 6);
  _uniqueId = ++uniqueHeaderCounter;
}

//===========================================================================
QString HeadingNode::toXHtml() const
{
  if (!_xhtmlVisible) return "";
  return QString("<h%1 id=\"%2\">%3</h%1>")
    .arg(_level)
    .arg(getXHtmlUniqueId())
    .arg(childrenToXHtml());
}

//===========================================================================
QString HeadingNode::toXml(int indentLevel) const
{
  QString indent(indentLevel, ' ');
  return indent + QString("<heading level=\"%1\">\n").arg(_level) +
    childrenToXml(indentLevel+1) +
    indent + "</heading>\n";
}

//===========================================================================
Heading::Type HeadingNode::headingType() const
{
  if (_headingType != Heading::Uninitialized)
    return _headingType;

  _headingType = Heading::instance().fromText(toText());
  return _headingType;
}

//===========================================================================
bool HeadingNode::xhtmlVisible()
{
  return Heading::instance().xhtmlVisibility(headingType());
}

//===========================================================================
QString HeadingNode::getXHtmlUniqueId() const
{
  QString result;
  if (_level > 2)
    result = QString("header%1").arg(_uniqueId);
  else
  {
    result = childrenToText().trimmed().toLower();
    // Languages like "Scotish Gaelic" has a space in its name.
    result.replace(' ', '_');
    result.replace(QRegExp("[^a-zA-Z0-9_]"), "");
    if (result == "")
      result = QString("header%1").arg(_uniqueId);
  }

  // Lets check if its nonempty, lower case, alphabet or simple numeric.
  CHECK_MSG(QRegExp("[a-z][a-z0-9_]*").exactMatch(result),
      "Assumption on header id failed (" + result + ").");

  return result;
}
