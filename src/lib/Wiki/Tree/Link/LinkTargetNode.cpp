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
#include "LinkTargetNode.h"
#include "../TextTokenNode.h"
#include "../../../UrlUtils.h"
#include <QRegExp>

//===========================================================================
LinkTargetNode::LinkTargetNode(const QString &text) : Node(Node::LinkTarget),
  _text(text)
{
  QStringList list = text.split(':');
  QStringList entryHeading = list.last().split('#');
  _entry = entryHeading.first().trimmed();
  if (entryHeading.size() > 1)
    _heading = entryHeading.last().trimmed();

  list.removeLast(); // remove entry name

  // trim all prefixes. Mediawiki does the same.
  // Handles links such as [[ Category: Czech nouns ]]
  for (int i = 0; i < list.size(); ++i)
    list[i] = list[i].trimmed();

  // The list contains only prefixes.
  _namespace = Namespace::instance().fromLinkPrefixes(list);
  _language = Language::instance().fromLinkPrefixes(list);
  _project = Project::instance().fromLinkPrefixes(list);
}

//===========================================================================
QString LinkTargetNode::toXHtmlLink() const
{
  if (_namespace == Namespace::Image ||
      _namespace == Namespace::Media)
    return UrlUtils::toUrl(_entry, "media").toString();

  return UrlUtils::toUrl(_text).toString();
}

//===========================================================================
QString LinkTargetNode::toXml(int indentLevel) const
{
  QString indent(indentLevel, ' ');

  QStringList languages = Language::instance().toNames(_language);
  QString language = QString().setNum(_language);
  if (languages.size() > 0)
    language = languages.first();

  return indent + QString("<link_target namespace=\"%1\" language=\"%2\" "
      "project=\"%3\">%4</link_target>\n")
      .arg(Namespace::instance().toLocalizedName(_namespace))
      .arg(language)
      .arg(Project::instance().toUrl(_project, _language))
      .arg(_text);
}

