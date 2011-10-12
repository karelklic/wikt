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
#ifndef CATEGORIESPANEL_H_
#define CATEGORIESPANEL_H_

#include "categoriesmodel.h"
#include <QDockWidget>

QT_BEGIN_NAMESPACE
class QTreeView;
QT_END_NAMESPACE

namespace Categories {

/// Displays categories to which the displayed entry belongs.
class Panel : public QDockWidget
{
  Q_OBJECT
public:
  /// Standard constructor.
  Panel();

  /// Gets the data model for category list that is displayed
  /// in this panel.
  Model &model() { return _model; }

signals:
  void localLinkClicked(const QString &entry);

private slots:
  /// Called when the model was changed.
  void modelChanged();
  /// Called when the user activated a category item by mouse click
  /// or by the keyboard.
  void activated(const QModelIndex &index);

private:
  QTreeView *_treeView;
  Model _model;
};

}

#endif /* CATEGORIESPANEL_H_ */
