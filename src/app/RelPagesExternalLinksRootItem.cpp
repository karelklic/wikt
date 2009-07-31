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
#include "RelPagesExternalLinksRootItem.h"
#include "RelPagesInterwikiRootItem.h"
#include "RelPagesExternalLinkItem.h"
#include <libwikt/Wiki/Tree/Node.h>
#include <QUrl>

namespace RelatedPages {

//===========================================================================
ExternalLinksRootItem::ExternalLinksRootItem(Item *parent)
  : Item(ExternalLinksRoot, parent), _interwikiRootItem(0)
{
  _itemData.append(QVariant("External links"));
}

//===========================================================================
void ExternalLinksRootItem::update(const QString &entry, const Node *rootNode)
{
  qDeleteAll(_childItems);
  _childItems.clear();
  _interwikiRootItem = 0;

  ExternalLinkItem *item;
  item = new ExternalLinkItem(
      QString("View on Wiktionary ") + QChar(0x21d7),
      QUrl("http://en.wiktionary.org/wiki/" + entry),
      this);
  appendChild(item);
  item = new ExternalLinkItem(
      QString("Edit on Wiktionary ") + QChar(0x21d7),
      QUrl("http://en.wiktionary.org/w/index.php?title=" + entry + "&action=edit"),
      this);
  appendChild(item);
  item = new ExternalLinkItem(
      QString("History on Wiktionary ") + QChar(0x21d7),
      QUrl("http://en.wiktionary.org/w/index.php?title=" + entry + "&action=history"),
      this);
  appendChild(item);

  // Append Interwiki section.
  _interwikiRootItem = new InterwikiRootItem(this); // deleted in ~Item()
  _interwikiRootItem->fill(rootNode);
  if (_interwikiRootItem->childCount() == 0)
  {
    delete _interwikiRootItem;
    _interwikiRootItem = 0;
  }
  else
    appendChild(_interwikiRootItem);
}

}
