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
#ifndef RELATEDPAGESEXTERNALLINKSROOTITEM_H_
#define RELATEDPAGESEXTERNALLINKSROOTITEM_H_

#include "relpagesitem.h"
#include <QString>
class Node;

namespace RelatedPages {

class InterwikiRootItem;

class ExternalLinksRootItem : public Item
{
public:
  /// Standard constructor.
  ExternalLinksRootItem(Item *parent);

  void update(const QString &entry, const Node *rootNode);

  InterwikiRootItem *interwikiRootItem() const { return _interwikiRootItem; }

protected:
  InterwikiRootItem *_interwikiRootItem;
};

}

#endif /* RELATEDPAGESEXTERNALLINKSROOTITEM_H_ */
