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
#include "relpagespanel.h"
#include "relpagesinternallinkitem.h"
#include "relpagesexternallinkitem.h"
#include <QTreeView>
#include <QSettings>
#include <QTimer>

namespace RelatedPages {

//===========================================================================
Panel::Panel() : QDockWidget(tr("Related Pages")), _model(this),
  _urlOpeningAllowed(true)
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
  // Update expansion of External Links root node and Interwiki root node.
  // Provides good user experience.
  QSettings settings;
  QModelIndex externalLinks = _model.externalLinksIndex();
  if (externalLinks.isValid())
  {
    bool externalLinksExpanded = settings.value("externalLinksExpanded", false).toBool();
    _treeView->setExpanded(externalLinks, externalLinksExpanded);
  }

  QModelIndex interwiki = _model.interwikiIndex();
  if (interwiki.isValid())
  {
    bool interwikiExpanded = settings.value("interwikiExpanded", false).toBool();
    _treeView->setExpanded(interwiki, interwikiExpanded);
  }

  // Set selected index.
  QModelIndex lastEntry = _model.lastEntryIndex();
  if (lastEntry.isValid())
    _treeView->setCurrentIndex(lastEntry);

  // Set visibility: the panel is hidden when empty, and also when
  // a page from namespace Wikt is displayed.
  setVisible(_model.rowCount() > 0 && !_model.lastEntry().startsWith("Wikt:"));
}

//===========================================================================
void Panel::collapsed(const QModelIndex &index)
{
  if (!index.isValid()) return;
  // Save state (expanded/collapsed) of External Links root node and
  // of Interwiki root node.
  QSettings settings;
  Item *item = static_cast<Item*>(index.internalPointer());
  if (item->type() == Item::ExternalLinksRoot)
    settings.setValue("externalLinksExpanded", false);
  else if  (item->type() == Item::InterwikiRoot)
    settings.setValue("interwikiExpanded", false);
}

//===========================================================================
void Panel::expanded(const QModelIndex &index)
{
  if (!index.isValid()) return;
  // Save state (expanded/collapsed) of External Links root node and
  // of Interwiki root node.
  QSettings settings;
  Item *item = static_cast<Item*>(index.internalPointer());
  if (item->type() == Item::ExternalLinksRoot)
    settings.setValue("externalLinksExpanded", true);
  else if  (item->type() == Item::InterwikiRoot)
    settings.setValue("interwikiExpanded", true);
}

//===========================================================================
void Panel::activated(const QModelIndex &index)
{
  if (!index.isValid()) return;
  Item *item = static_cast<Item*>(index.internalPointer());
  if (item->type() == Item::ExternalLink && _urlOpeningAllowed)
  {
    static_cast<ExternalLinkItem*>(item)->openUrl();

    // Protection from double-click activation.
    // We do not want a link to be opened twice when user
    // double-clicks.
    _urlOpeningAllowed = false;
    QTimer::singleShot(3000, this, SLOT(allowOpeningUrl()));
  }
  else if  (item->type() == Item::InternalLink)
    emit localLinkClicked(static_cast<InternalLinkItem*>(item)->link());
}

//===========================================================================
void Panel::allowOpeningUrl()
{
  _urlOpeningAllowed = true;
}

}

