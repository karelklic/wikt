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
#include "InterestingPagesPanel.h"
#include "InterestingPagesItem.h"
#include "InterestingPagesLinkItem.h"
#include "MainWindow.h"
#include "Coordinator.h"
#include <QTreeView>
#include <QSettings>
#include <QTimer>

namespace InterestingPages {

//===========================================================================
Panel::Panel() : QDockWidget(tr("Interesting Pages")), _model(this)
{
  _treeView = new QTreeView(this);
  _treeView->setModel(&_model);
  _treeView->setHeaderHidden(true);
  _treeView->show();
  setWidget(_treeView);
  setAllowedAreas(Qt::LeftDockWidgetArea);
  setFeatures(QDockWidget::NoDockWidgetFeatures);
  connect(&_model, SIGNAL(modelReset()), this, SLOT(modelChanged()));
  connect(_treeView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(activated(const QModelIndex&)));
  connect(_treeView, SIGNAL(activated(const QModelIndex&)), this, SLOT(activated(const QModelIndex&)));
  connect(_treeView, SIGNAL(collapsed(const QModelIndex&)), this, SLOT(collapsed(const QModelIndex&)));
  connect(_treeView, SIGNAL(expanded(const QModelIndex&)), this, SLOT(expanded(const QModelIndex&)));
}

//===========================================================================
void Panel::modelChanged()
{
  // Update expansion of nodes, as it provides good user experience.
  QSettings settings;
  QModelIndex languagesOfTheWorld = _model.languagesRootItemIndex();
  if (languagesOfTheWorld.isValid())
  {
    bool languagesExpanded = settings.value("languagesOfTheWorldExpanded", false).toBool();
    _treeView->setExpanded(languagesOfTheWorld, languagesExpanded);
  }

  setVisible(MainWindow::instance()->coordinator()->state() == Coordinator::HomeActivated ||
      MainWindow::instance()->coordinator()->text().startsWith("Wikt:"));
}

//===========================================================================
void Panel::collapsed(const QModelIndex &index)
{
  if (!index.isValid()) return;
  QSettings settings;
  Item *item = static_cast<Item*>(index.internalPointer());
  if (item->type() == Item::LanguagesOfTheWorld)
    settings.setValue("languagesOfTheWorldExpanded", false);
}

//===========================================================================
void Panel::expanded(const QModelIndex &index)
{
  if (!index.isValid()) return;
  QSettings settings;
  Item *item = static_cast<Item*>(index.internalPointer());
  if (item->type() == Item::LanguagesOfTheWorld)
    settings.setValue("languagesOfTheWorldExpanded", true);
}

//===========================================================================
void Panel::activated(const QModelIndex &index)
{
  if (!index.isValid()) return;
  Item *item = static_cast<Item*>(index.internalPointer());
  if (item->type() == Item::Link)
    emit localLinkClicked(static_cast<LinkItem*>(item)->link());
}

}

