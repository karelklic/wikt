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
#include "tocitem.h"

namespace TableOfContents {

//===========================================================================
Item::Item() : _parentItem(0)
{
  // We must have some data. Never displayed, but the tree view does not
  // work when the root node is empty.
  _itemData.append(QVariant("H1"));
}

//===========================================================================
Item::Item(const QString &heading,
    const QString &xhtmlHeadingId, Item *parent)
  : _xhtmlHeadingId(xhtmlHeadingId)
{
  _parentItem = parent;
  _itemData.append(QVariant(heading));
}

//===========================================================================
Item::~Item()
{
  qDeleteAll(_childItems);
}

//===========================================================================
int Item::row() const
{
  if (_parentItem)
      return _parentItem->_childItems.indexOf(const_cast<Item*>(this));
  return 0;
}

//===========================================================================
int Item::allChildCount() const
{
  int ret = childCount();
  foreach(Item *child, _childItems)
    ret += child->allChildCount();
  return ret;
}

}
