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
#include "categoriesmodel.h"
#include "categoriesitem.h"
#include <libwikt/tree/articlenode.h>

namespace Categories {

//===========================================================================
Model::Model(QObject *parent) : QAbstractItemModel(parent)
{
  _rootItem = new Item();
}

//===========================================================================
Model::~Model()
{
  delete _rootItem;
}

//===========================================================================
QVariant Model::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
      return QVariant();
  if (role != Qt::DisplayRole)
      return QVariant();
  Item *item = static_cast<Item*>(index.internalPointer());
  return item->data(index.column());
}

//===========================================================================
Qt::ItemFlags Model::flags(const QModelIndex &index) const
{
  if (!index.isValid()) return 0;
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

//===========================================================================
QModelIndex Model::index(int row, int column, const QModelIndex &parent) const
{
  if (!hasIndex(row, column, parent))
    return QModelIndex();

  Item *parentItem;
  if (!parent.isValid())
    parentItem = _rootItem;
  else
    parentItem = static_cast<Item*>(parent.internalPointer());

    Item *childItem = parentItem->child(row);
  if (childItem)
      return createIndex(row, column, childItem);
  else
      return QModelIndex();
}

//===========================================================================
QModelIndex Model::parent(const QModelIndex &index) const
{
  if (!index.isValid())
      return QModelIndex();

  Item *childItem = static_cast<Item*>(index.internalPointer());
  Item *parentItem = childItem->parent();

  if (parentItem == _rootItem)
      return QModelIndex();
  return createIndex(parentItem->row(), 0, parentItem);
}

//===========================================================================
int Model::rowCount(const QModelIndex &parent) const
{
  Item *parentItem;
  if (parent.column() > 0)
    return 0;

  if (!parent.isValid())
    parentItem = _rootItem;
  else
    parentItem = static_cast<Item*>(parent.internalPointer());
  return parentItem->childCount();
}

//===========================================================================
int Model::columnCount(const QModelIndex &parent) const
{
  if (parent.isValid())
      return static_cast<Item*>(parent.internalPointer())->columnCount();
  else
      return _rootItem->columnCount();
}

//===========================================================================
void Model::generateFrom(const ArticleNode &node)
{
  // Clear the model.
  delete _rootItem;
  _rootItem = new Item();

  QStringList categories;
  node.getCategories(categories);
  foreach (const QString &category, categories)
  {
    Item *item = new Item(category, _rootItem);
    _rootItem->appendChild(item);
  }

  // Tell attached views that we changed the model.
  reset();
}

//===========================================================================
void Model::clear()
{
  // Clear the model.
  delete _rootItem;
  _rootItem = new Item();

  // Tell attached views that we changed the model.
  reset();
}

}

