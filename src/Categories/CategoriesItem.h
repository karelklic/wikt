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
#ifndef CATEGORIESITEM_CPP_
#define CATEGORIESITEM_CPP_

#include <QString>
#include <QList>
#include <QVariant>

namespace Categories {

/// @brief An item in the category panel.
/// Class Model builds and holds the tree of Item objects.
class Item
{
public:
  /// Constructor for the root node.
  Item();
  /// Standard constructor.
  /// @param title
  ///   Name of the category this item represents.
  ///   The name must be without the category namespace prefix.
  ///   That is without the "Category:" for the English Wiktionary.
  /// @param parent
  ///   The parent item of this item.
  Item(const QString &title, Item *parent);
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

private:
  QList<Item*> _childItems;
  QList<QVariant> _itemData;
  Item *_parentItem;
};

}

#endif /* CATEGORIESITEM_CPP_ */
