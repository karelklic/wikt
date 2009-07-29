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

#include <libwikt/Prerequisites.h>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
class ArticleNode;
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

  /// @brief Rebuilds model to represent a certain entry.
  /// @param node
  ///   The tree of nodes that represents the entry contents.
  void generateFrom(const ArticleNode *node);

  /// @brief Rebuilds model to represent a list of entries.
  /// Used when user searches for a list of words (writes a sentence to
  /// the search box).
  void generateFrom(const QList<const ArticleNode*> &nodes);

  /// When user clicks the Related Pages panel, this gets only
  /// partial update.
  void partialUpdateFrom(const QString &entry, const ArticleNode *rootNode);

  void clear();

  QModelIndex externalLinksIndex() const;
  QModelIndex interwikiIndex() const;
  QModelIndex lastEntryIndex() const;

  /// Returns the name of the last entry used to update the model.
  /// Empty string is returned if the model is cleared or newly
  /// initialized.
  const QString &lastEntry() const { return _lastEntry; }

private:
  RootItem *_rootItem;
  QString _lastEntry;
};

}

#endif /* RELATEDPAGESMODEL_H_ */
