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
#ifndef INTERESTINGPAGESITEM_H_
#define INTERESTINGPAGESITEM_H_

#include <Prerequisites.h>
#include <QString>
#include <QList>
#include <QVariant>

namespace InterestingPages {

/// @brief An item in Interesting Pages panel.
/// InterestingPages::Model class holds a tree of this class instances.
class Item
{
public:
  enum Type {
    Root,
    LanguagesOfTheWorld,
    Link
  };

  /// Standard constructor to be called by inherited classes.
  Item(Type type, Item *parent);
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
  /// Add data.
  void appendData(const QVariant &variant) { _itemData.append(variant); }
  /// Mandatory for model handling.
  int row() const;
  /// Mandatory for model handling.
  Item *parent() { return _parentItem; }
  /// Returns item node type.
  Type type() const { return _type; }

protected:
  QList<Item*> _childItems;
  QList<QVariant> _itemData;
  Item *_parentItem;
  Type _type;
};

}

#endif /* INTERESTINGPAGESITEM_H_ */
