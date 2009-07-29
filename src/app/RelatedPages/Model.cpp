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
#include "Model.h"
#include "RootItem.h"
#include "ExternalLinksRootItem.h"
#include "InternalLinkItem.h"
#include "InterwikiRootItem.h"
#include <libwikt/Wiki/Tree/Article/ArticleNode.h>

namespace RelatedPages {

//===========================================================================
Model::Model(QObject *parent) : QAbstractItemModel(parent)
{
  _rootItem = new RootItem();
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
void Model::generateFrom(const ArticleNode *node)
{
  QList<const ArticleNode*> nodes;
  nodes.append(node);
  generateFrom(nodes);
}

//===========================================================================
void Model::generateFrom(const QList<const ArticleNode*> &nodes)
{
  PROFILER;
  _lastEntry = nodes.first()->name();
  _rootItem->recreateFrom(nodes);

  // Tell attached views that we changed the model.
  reset();
}

//===========================================================================
void Model::partialUpdateFrom(const QString &entry, const ArticleNode *rootNode)
{
  PROFILER;
  _lastEntry = entry;
  _rootItem->partialUpdateFrom(entry, rootNode);
  // Tell attached views that we changed the model.
  reset();
}

//===========================================================================
void Model::clear()
{
  PROFILER;
  _lastEntry = "";
  _rootItem->clear();
  // Tell attached views that we changed the model.
  reset();
}

//===========================================================================
QModelIndex Model::externalLinksIndex() const
{
  ExternalLinksRootItem *item = _rootItem->externalLinksRootItem();
  if (!item) return QModelIndex();
  return createIndex(item->row(), 0, item);
}

//===========================================================================
QModelIndex Model::interwikiIndex() const
{
  ExternalLinksRootItem *external = _rootItem->externalLinksRootItem();
  if (!external) return QModelIndex();
  InterwikiRootItem *interwiki = external->interwikiRootItem();
  if (!interwiki) return QModelIndex();
  return createIndex(interwiki->row(), 0, interwiki);
}

//===========================================================================
QModelIndex Model::lastEntryIndex() const
{
  PROFILER;
  for (int i = 0; i < _rootItem->childCount(); ++i)
  {
    Item *child = _rootItem->child(i);
    if (child->type() != Item::InternalLink) continue;
    InternalLinkItem *link = static_cast<InternalLinkItem*>(child);
    if (link->data(0).toString() == _lastEntry)
      return createIndex(link->row(), 0, link);
  }

  return QModelIndex();
}

}
