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
#include "../Html/HtmlElementNode.h"
#include "../List/ListItemNode.h"
#include "../Table/TableNode.h"
#include "../../Language.h"
#include <QFile>
#include <QSettings>
#include <QList>

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

//===========================================================================
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

    // This algorithm is damn slow.
    // REPLACE in Language with C-style table.
    // Possibly move this code to Language class.
    foreach (ListItemNode *item, listItems)
    {
      QString text = item->toText();
      for (int i = 0; i < Language::Unknown; ++i)
      {
        Language::Type language = (Language::Type)i;
        QString name = Language::instance().toTranslationSectionName(language);
        if (name.length() == 0) continue;

        // Use regular expression because of languages
        // Malay and Malaylam.
        QRegExp regExp(name + "[^a-z]");
        if (regExp.indexIn(text) == -1) continue;

        bool visible = Language::instance().isTranslationVisible(language);
        item->setXHtmlVisibility(visible);
        break;
      }
    }
  }
}
