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
#ifndef RELATEDPAGESPANEL_H_
#define RELATEDPAGESPANEL_H_

#include "relpagesmodel.h"
#include <QDockWidget>

QT_BEGIN_NAMESPACE
class QTreeView;
QT_END_NAMESPACE

namespace RelatedPages {

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
  /// Allows external URL opening again.
  void allowOpeningUrl();

private:
  QTreeView *_treeView;
  Model _model;
  /// Protection from double-click activation.
  /// We do not want a link to be opened twice when user
  /// doubleclicks.
  bool _urlOpeningAllowed;
};

}

#endif /* RELATEDPAGESPANEL_H_ */
