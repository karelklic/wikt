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
#include "categoriespanel.h"
#include "categoriesitem.h"
#include <QTreeView>

namespace Categories {

//===========================================================================
Panel::Panel() : QDockWidget(tr("Categories")), _model(this)
{
  _treeView = new QTreeView(this);
  _treeView->setModel(&_model);
  _treeView->setHeaderHidden(true);
  _treeView->show();
  setWidget(_treeView);
  setAllowedAreas(Qt::LeftDockWidgetArea);
  setFeatures(QDockWidget::NoDockWidgetFeatures);
  setVisible(false);
  connect(&_model, SIGNAL(modelReset()), this, SLOT(modelChanged()));

  connect(_treeView, SIGNAL(activated(const QModelIndex&)),
      this, SLOT(activated(const QModelIndex&)));
  connect(_treeView, SIGNAL(clicked(const QModelIndex&)),
      this, SLOT(activated(const QModelIndex&)));
}

//===========================================================================
void Panel::modelChanged()
{
  _treeView->expandAll();
  setVisible(_model.rowCount() > 0);
}

//===========================================================================
void Panel::activated(const QModelIndex &index)
{
  if (!index.isValid()) return;
  Item *item = static_cast<Item*>(index.internalPointer());
  emit localLinkClicked("Category:" + item->data(0).toString());
}

}
