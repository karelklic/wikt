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
#ifndef TABLEOFCONTENTSITEM_H_
#define TABLEOFCONTENTSITEM_H_

#include <QString>
#include <QList>
#include <QVariant>

namespace TableOfContents {

/// @brief An item in the table of contents panel.
/// Class Model holds a tree of Item objects.
class Item
{
public:
  /// Constructor for the root node.
  Item();
  /// Standard constructor.
  Item(const QString &heading, const QString &xhtmlHeadingId,
      Item *parent);
  ~Item();

  /// Mandatory for model handling.
  void appendChild(Item *child) { _childItems.append(child); }
  /// Mandatory for model handling.
  Item *child(int row) { return _childItems.value(row); }
  /// Mandatory for model handling.
  int childCount() const { return _childItems.count(); }
  /// Mandatory for model handling.
  int columnCount() const { return _itemData.count(); }
  /// Mandatory for model handling.
  QVariant data(int column) const { return _itemData.value(column); }
  /// Mandatory for model handling.
  int row() const;
  /// Mandatory for model handling.
  Item *parent() { return _parentItem; }

  /// Counts all children recursively.
  int allChildCount() const;
  const QString &xhtmlHeadingId() const { return _xhtmlHeadingId; }

private:
  /// Subnodes of this node. This node owns them and
  /// deletes them in the destructor.
  QList<Item*> _childItems;
  QList<QVariant> _itemData;
  Item *_parentItem;
  QString _xhtmlHeadingId;
};

}

#endif /* TABLEOFCONTENTSITEM_H_ */
