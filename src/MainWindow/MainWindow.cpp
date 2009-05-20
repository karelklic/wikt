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
#include "MainWindow.h"
#include "MenuBar.h"
#include "LookupPanel.h"
#include "Coordinator.h"
#include "FindPanel.h"
#include "WebView/WebView.h"
#include "../RelatedPages/Panel.h"
#include "../TableOfContents/TocPanel.h"
#include "../Categories/CategoriesPanel.h"
#include "../Wiki/WikiSource.h"
#include "../Media/MediaPlayer.h"
#include <QDockWidget>
#include <QStatusBar>

static MainWindow *instance = 0;

//===========================================================================
MainWindow::MainWindow()
{
  ::instance = this;
  statusBar()->showMessage(tr("Ready"));

  setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);

  // Warning! Be careful when changing the sequence of allocation and setup.
  _coordinator = new Coordinator(this);

  _webView = new WebView(this);
  setCentralWidget(_webView);

  _wikiSource = new WikiSource(this);

  _lookupPanel = new LookupPanel();
  addDockWidget(Qt::LeftDockWidgetArea, _lookupPanel);

  _relatedPagesPanel = new RelatedPages::Panel();
  addDockWidget(Qt::LeftDockWidgetArea, _relatedPagesPanel);

  _tableOfContentsPanel = new TableOfContents::Panel();
  addDockWidget(Qt::LeftDockWidgetArea, _tableOfContentsPanel);

  _categoriesPanel = new Categories::Panel();
  addDockWidget(Qt::LeftDockWidgetArea, _categoriesPanel);

  _findPanel = new FindPanel(this);
  addDockWidget(Qt::BottomDockWidgetArea, _findPanel);
  _findPanel->hide();

  _mainMenuBar = new MenuBar(this);
  setMenuBar(_mainMenuBar);

  _mediaPlayer = new MediaPlayer(this);

  setWindowTitle(tr("Wikt"));
  _lookupPanel->setFocus();

  _coordinator->homeActivated();
  connect(_lookupPanel, SIGNAL(wordEntered(const QString&)),
      _coordinator, SLOT(textEnteredToLookup(const QString&)));
  connect(_lookupPanel, SIGNAL(historyActivated(const QUrl&)),
      _coordinator, SLOT(historyActivated(const QUrl&)));
  connect(_lookupPanel, SIGNAL(homeActivated()),
      _coordinator, SLOT(homeActivated()));
  connect(_webView, SIGNAL(localLinkClickedInView(const QUrl&)),
      _coordinator, SLOT(localLinkClickedInView(const QUrl&)));
  connect(_relatedPagesPanel, SIGNAL(localLinkClicked(const QString&)),
      _coordinator, SLOT(localLinkClickedInRelatedPagesPanel(const QString&)));
  connect(_categoriesPanel, SIGNAL(localLinkClicked(const QString&)),
      _coordinator, SLOT(categoryClickedInCategoriesPanel(const QString&)));
  connect(_tableOfContentsPanel, SIGNAL(activated(const QString&)),
      _coordinator, SLOT(tableOfContentsClicked(const QString&)));
  connect(_webView->page(), SIGNAL(linkHovered(const QString&, const QString&,const QString&)),
      this, SLOT(linkHovered(const QString&, const QString&,const QString&)));
}

//===========================================================================
MainWindow::~MainWindow()
{
}

//===========================================================================
MainWindow *MainWindow::instance()
{
  return ::instance;
}

//===========================================================================
void MainWindow::setTitle(const QString &text)
{
  if (text.length() == 0)
    setWindowTitle(tr("Wikt"));
  else
    setWindowTitle(QString(tr("%1 - Wikt")).arg(text));
}

//===========================================================================
void MainWindow::linkHovered(const QString &link, const QString &/*title*/,
    const QString &/*textContent*/)
{
  statusBar()->showMessage(link);
}
