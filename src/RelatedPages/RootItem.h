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
#ifndef RELATEDPAGESROOTITEM_H_
#define RELATEDPAGESROOTITEM_H_

#include "Item.h"
class Node;

namespace RelatedPages {

class ExternalLinksRootItem;
class InternalLinkItem;

class RootItem : public Item
{
public:
  /// Standard constructor.
  RootItem();

  /// @brief Updates the tree to match a certain entry.
  /// @param entry
  ///   The name of existing entry in the dictionary.
  /// @param rootNode
  ///   The tree of nodes built from the entry contents.
  void recreateFrom(const QString &entry, const Node *rootNode);

  /// Does not touch internal links.
  /// Changes just the external links.
  void partialUpdateFrom(const QString &entry, const Node *rootNode);

  void generateForTitlePage();

  ExternalLinksRootItem *externalLinksRootItem() const { return _externalLinksRootItem; }

private:
  void appendEntryWithCitationsWikisaurus(InternalLinkItem *item);

  ExternalLinksRootItem *_externalLinksRootItem;
};

}

#endif /* RELATEDPAGESROOTITEM_H_ */
