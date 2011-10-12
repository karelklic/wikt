/* This file is part of Wikt. -*- mode: c++; c-file-style: "wikt"; -*-
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
#include "relpagesrootitem.h"
#include "relpagesinternallinkitem.h"
#include "relpagesexternallinksrootitem.h"
#include "mainwindow.h"
#include "wikisource.h"
#include <libwikt/tree/articlenode.h>
#include <libwikt/tree/htmlelementnode.h>
#include <libwikt/tree/linknode.h>
#include <libwikt/tree/linktargetnode.h>

namespace RelatedPages {

RootItem::RootItem() : Item(Root, 0), _externalLinksRootItem(0)
{
  // We must have some data. Never displayed, but the tree view does not
  // work when the root node is empty.
  _itemData.append(QVariant("H1"));
}

void RootItem::recreateFrom(const ArticleNode *node)
{
  qDeleteAll(_childItems);
  _childItems.clear();
  _externalLinksRootItem = 0;

  // Citations and Wikisaurus are handled the same way as
  // their root entry.
  QString entryRoot(node->name());
  if (entryRoot.startsWith("Citations:", Qt::CaseInsensitive))
    entryRoot.remove(0, 10); // strlen("Citations:")
  else if (entryRoot.startsWith("Wikisaurus:", Qt::CaseInsensitive))
    entryRoot.remove(0, 11); // strlen("Wikisaurus:")

  const Node *rootNodeRoot = node;
  if (node->name() != entryRoot)
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
  _externalLinksRootItem->update(node->name(), node);
  appendChild(_externalLinksRootItem);
}

void RootItem::recreateFrom(const QList<const ArticleNode*> &nodes)
{
  qDeleteAll(_childItems);
  _childItems.clear();
  _externalLinksRootItem = 0;

  foreach (const ArticleNode *node, nodes)
  {
    // Citations and Wikisaurus are handled the same way as
    // their root entry.
    QString entryRoot(node->name());
    if (entryRoot.startsWith("Citations:", Qt::CaseInsensitive))
      entryRoot.remove(0, 10); // strlen("Citations:")
    else if (entryRoot.startsWith("Wikisaurus:", Qt::CaseInsensitive))
      entryRoot.remove(0, 11); // strlen("Wikisaurus:")

    // Handle displaying subpages.
    if (entryRoot.contains('/'))
    {
      InternalLinkItem *item = new InternalLinkItem(node->name(), this);
      appendChild(item);
      entryRoot.remove(entryRoot.indexOf('/'), entryRoot.length());
    }

    const Node *rootNodeRoot = node;
    if (node->name() != entryRoot)
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
  }

  _externalLinksRootItem = new ExternalLinksRootItem(this); // deleted in ~Item()
  _externalLinksRootItem->update(nodes.first()->name(), nodes.first());
  appendChild(_externalLinksRootItem);
}

void RootItem::partialUpdateFrom(const QString &entry, const ArticleNode *rootNode)
{
  _externalLinksRootItem->update(entry, rootNode);
}

void RootItem::clear()
{
  qDeleteAll(_childItems);
  _childItems.clear();
  _externalLinksRootItem = 0;
}

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
