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
#include "linktargetnode.h"
#include "texttokennode.h"
#include "../urlutils.h"
#include <QRegExp>
#include <assert.h>

//===========================================================================
LinkTargetNode::LinkTargetNode(const QString &text) : Node(Node::LinkTarget), 
  _namespace(Namespace::Main), _project(Project::Wiktionary), _text(text)
{
  _language = NULL;

  QString remainder(text);
  int offs = remainder.indexOf(':');
  if (offs != -1)
  {
    QString prefix = remainder.left(offs).trimmed();
    if (Namespace::instance().isPrefix(prefix))
    {
      _namespace = Namespace::instance().fromPrefix(prefix);
      remainder.remove(0, offs + 1);
    }
    else if (_language = language_from_interwiki_prefix(prefix.toUtf8().constData()))
      remainder.remove(0, offs + 1);
    else if (Project::instance().isPrefix(prefix))
    {
      _project = Project::instance().fromPrefix(prefix);
      remainder.remove(0, offs + 1);
    }
  }
  
  if (!_language)
    _language = language_from_iso_639_3_code("eng"); /* English */
  assert(_language);

  QStringList entryHeading = remainder.split('#');
  _entry = entryHeading.first().trimmed();

  if (entryHeading.size() > 1)
    _heading = entryHeading.last().trimmed();

  // Handle links such as [[#English|something]].
  /*if (_entry.length() == 0)
  {
    _text.prepend(thisEntry);
    offs = thisEntry.indexOf(':');
    if (offs != -1)
    {
      QString prefix = thisEntry.left(offs).trimmed();
      if (Namespace::instance().isPrefix(prefix))
	_namespace = Namespace::instance().fromPrefix(prefix);
    }
    }*/
}

//===========================================================================
QString LinkTargetNode::toXHtmlLink() const
{
  if (_namespace == Namespace::Image || _namespace == Namespace::Media || _namespace == Namespace::File)
    return UrlUtils::toUrl(_entry, "media").toString();

  return UrlUtils::toUrl(_text).toString();
}

//===========================================================================
QString LinkTargetNode::toXml(int indentLevel) const
{
  QString indent(indentLevel, ' ');

  return indent + QString("<link_target namespace=\"%1\" language=\"%2\" project=\"%3\">%4</link_target>\n")
      .arg(Namespace::instance().toLocalizedName(_namespace))
      .arg(_language->iso639_3_code)
      .arg(Project::instance().toUrl(_project, _language->interwiki_prefix))
      .arg(_text);
}

