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
#ifndef INTERESTINGPAGESPANEL_H_
#define INTERESTINGPAGESPANEL_H_

#include "InterestingPagesModel.h"
#include <QDockWidget>

QT_BEGIN_NAMESPACE
class QTreeView;
QT_END_NAMESPACE

namespace InterestingPages {

class Panel : public QDockWidget
{
  Q_OBJECT
public:
  Panel();

  Model &model() { return _model; }
  const Model &model() const { return _model; }

signals:
  void localLinkClicked(const QString &entry);

private slots:
  void modelChanged();
  void collapsed(const QModelIndex &index);
  void expanded(const QModelIndex &index);
  void activated(const QModelIndex &index);

private:
  QTreeView *_treeView;
  Model _model;
};

}

#endif /* INTERESTINGPAGESPANEL_H_ */
