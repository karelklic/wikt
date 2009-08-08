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
#ifndef CATEGORIESMODEL_H_
#define CATEGORIESMODEL_H_

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
class Node;
class Format3Reader;

namespace Categories {

class Item;

/// Builds and manages a tree of Item objects that represents
/// a list of categories referred to by some page.
class Model : public QAbstractItemModel
{
  Q_OBJECT
public:
  Model(QObject *parent = 0);
  ~Model();

  QVariant data(const QModelIndex &index, int role) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
  QModelIndex parent(const QModelIndex &index) const;
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;

  /// @brief Updates model to match a certain entry.
  void generateFrom(const Node *node);
  /// Removes all nodes.
  void clear();

private:
  Item *_rootItem;
};

}

#endif /* CATEGORIESMODEL_H_ */
