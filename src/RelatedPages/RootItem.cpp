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
#include "RootItem.h"
#include "InternalLinkItem.h"
#include "ExternalLinksRootItem.h"
#include "../Wiki/Tree/Article/ArticleNode.h"
#include "../Wiki/Tree/Html/HtmlElementNode.h"
#include "../Wiki/Tree/Link/LinkNode.h"
#include "../Wiki/Tree/Link/LinkTargetNode.h"
#include "../Wiki/WikiSource.h"
#include "../MainWindow/MainWindow.h"

namespace RelatedPages {

//===========================================================================
RootItem::RootItem() : Item(Root, 0), _externalLinksRootItem(0)
{
  // We must have some data. Never displayed, but the tree view does not
  // work when the root node is empty.
  _itemData.append(QVariant("H1"));
}

//===========================================================================
void RootItem::recreateFrom(const QString &entry, const Node *rootNode)
{
  qDeleteAll(_childItems);
  _childItems.clear();
  _externalLinksRootItem = 0;

  // Citations and Wikisaurus are handled the same way as
  // their root entry.
  QString entryRoot(entry);
  if (entryRoot.startsWith("Citations:", Qt::CaseInsensitive))
    entryRoot.remove(0, 10); // strlen("Citations:")
  else if (entryRoot.startsWith("Wikisaurus:", Qt::CaseInsensitive))
    entryRoot.remove(0, 11); // strlen("Wikisaurus:")

  const Node *rootNodeRoot = rootNode;
  if (entry != entryRoot)
  {
    // Parser must be created through the pointer,
    // because the tree it creates lives only until
    // the parser is destroyed.
    rootNodeRoot = MainWindow::instance()->wikiSource()->tree(entryRoot);
  }

  // Append itself or a root item if "Citations:" or "Wikisaurus:"
  // is the current item.
  InternalLinkItem *item = new InternalLinkItem(entryRoot, this);
  appendEntryWithCitationsWikisaurus(item);

  // Append See also section from the root item.
  QList<const HtmlElementNode*> htmlElements;
  rootNodeRoot->findChildren(htmlElements);
  foreach(const HtmlElementNode *element, htmlElements)
  {
    if (!element->isSeeAlsoNode()) continue;
    // See also node found. Now find the links.
    QList<const LinkNode*> links;
    element->findChildren(links);
    foreach(const LinkNode* link, links)
    {
      item = new InternalLinkItem(link->xhtmlTitle(),
          link->target().toText(), this);
      appendEntryWithCitationsWikisaurus(item);
    }
  }

  _externalLinksRootItem = new ExternalLinksRootItem(this); // deleted in ~Item()
  _externalLinksRootItem->update(entry, rootNode);
  appendChild(_externalLinksRootItem);
}

//===========================================================================
void RootItem::partialUpdateFrom(const QString &entry, const Node *rootNode)
{
  _externalLinksRootItem->update(entry, rootNode);
}

//===========================================================================
void RootItem::generateForTitlePage()
{
  qDeleteAll(_childItems);
  _childItems.clear();
  _externalLinksRootItem = 0;
}

//===========================================================================
void RootItem::appendEntryWithCitationsWikisaurus(InternalLinkItem *item)
{
  appendChild(item);

  // Append Citations if those exist.
  QString citationsEntryName("Citations:" + item->link());
  if (MainWindow::instance()->wikiSource()->exist(citationsEntryName))
  {
    item = new InternalLinkItem(citationsEntryName, this);
    appendChild(item);
  }

  // Append Wikisaurus
  QString wikisaurusEntryName("Wikisaurus:" + item->link());
  if (MainWindow::instance()->wikiSource()->exist(wikisaurusEntryName))
  {
    item = new InternalLinkItem(wikisaurusEntryName, this);
    appendChild(item);
  }
}

}
