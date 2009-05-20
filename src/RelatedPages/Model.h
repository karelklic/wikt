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
#ifndef RELATEDPAGESMODEL_H_
#define RELATEDPAGESMODEL_H_

#include "../Prerequisites.h"
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
class Node;
class Format3Reader;

namespace RelatedPages {

class RootItem;

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
  /// @param entry
  ///   The name of existing entry in the dictionary.
  /// @param rootNode
  ///   The tree of nodes built from the entry contents.
  void generateFrom(const QString &entry, const Node *rootNode);

  /// When user clicks the Related Pages panel, this gets only
  /// partial update.
  void partialUpdateFrom(const QString &entry, const Node *rootNode);

  void generateForTitlePage();

  QModelIndex externalLinksIndex() const;
  QModelIndex interwikiIndex() const;
  QModelIndex lastEntryIndex() const;

private:
  RootItem *_rootItem;
  QString _lastEntry;
};

}

#endif /* RELATEDPAGESMODEL_H_ */
