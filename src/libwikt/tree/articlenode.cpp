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
#include "articlenode.h"
#include "headingnode.h"
#include "htmlelementnode.h"
#include "listitemnode.h"
#include "linknode.h"
#include "linktargetnode.h"
#include "tablenode.h"
#include "../language.h"
#include <QFile>
#include <QSettings>
#include <QList>

QString ArticleNode::toXHtml() const
{
  if (!_xhtmlVisible) return "";
  return QString("<h1>%1</h1>%3")
    .arg(_name)
    .arg(childrenToXHtml());
}

QString ArticleNode::toXml(int indentLevel) const
{
  QString indent(indentLevel, ' ');
  return indent + "<article>\n" +
    childrenToXml(indentLevel+1) +
    indent + "</article>\n";
}

void ArticleNode::updateSectionVisibility()
{
  static const int DISABLED = MAX_HEADING_LEVEL + 1;
  int invisibleLevel = DISABLED;

  // Check top-level nodes only.
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

void ArticleNode::updateTranslationSettings()
{
  // Check top-level nodes only.
  foreach(Node *node, children())
  {
    if (node->type() != Node::HtmlElement)
      continue;
    HtmlElementNode *elem = dynamic_cast<HtmlElementNode*>(node);
    TableNode *table = elem->findTranslationTable();
    if (!table)
      continue;

    QList<ListItemNode*> listItems;
    table->findChildren(listItems);

    foreach (ListItemNode *item, listItems)
    {
      QString text = item->toText();
      text = text.section(':', 0, 0).trimmed(); // everything before the first ':'
      Language::Type language = Language::instance().fromName(text);
      bool visible = Language::instance().isTranslationVisible(language);
      item->setXHtmlVisibility(visible);
    }
  }
}

void ArticleNode::getCategories(QStringList &list) const
{
  QList<const LinkNode*> links;
  findChildren(links);

  foreach(const LinkNode *link, links)
  {
    if (link->target().namespace_() != Namespace::Category) continue;
    if (link->target().language() != Language::English) continue;
    if (link->target().project() != Project::Wiktionary) continue;
    if (link->forcedLink()) continue;

    // Check if it is not already in the destination list.
    if (list.contains(link->target().entry())) continue;
    list.append(link->target().entry());
  }
  
  list.sort();
}
