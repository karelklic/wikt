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
#ifndef WIKT_MAIN_MENU_BAR_H
#define WIKT_MAIN_MENU_BAR_H

#include <libwikt/Prerequisites.h>
#include <QMenuBar>
QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
QT_END_NAMESPACE
class MainWindow;

/// Handles the application's main menu and some simple and debug actions.
class MenuBar : public QMenuBar
{
  Q_OBJECT
public:
  MenuBar(MainWindow *parent);
  ~MenuBar();

private slots:
  // Edit
  void find();
  void findNext();
  void options();
  // View
  void viewEtymologyToggled(bool checked);
  void viewPronunciationToggled(bool checked);
  void viewInflectionsToggled(bool checked);
  void viewTranslationsToggled(bool checked);
  void viewSemanticRelationsToggled(bool checked);
  void viewRelatedDerivedToggled(bool checked);
  void viewAnagramsToggled(bool checked);
  // Development
  /// Shows a floating subwindow with current page's HTML source.
  void pageHtml();
  void algorithmWikiProcessing();
  /// Shows a window with performance measurement results.
  void profilerResults();
  // Help
  /// Displays an about application box.
  void about();

private:
  MainWindow *_parent;
  QMenu *_fileMenu;
  QMenu *_editMenu;
  QMenu *_viewMenu;
  QMenu *_developmentMenu;
  QMenu *_helpMenu;

  // File
  QAction *_quitAct;

  // Edit
  QAction *_cut;
  QAction *_copy;
  QAction *_paste;
  QAction *_selectAll;
  QAction *_find;
  QAction *_findNext;
  QAction *_options;

  // View
  QAction *_viewEtymologyAct;
  QAction *_viewPronunciationAct;
  QAction *_viewInflectionsAct;
  QAction *_viewTranslationsAct;
  QAction *_viewSemanticRelationsAct;
  QAction *_viewRelatedDerivedAct;
  QAction *_viewAnagramsAct;

  // Development
  QAction *_pageHtmlAct;
  QAction *_algorithmWikiProcessingAct;
  QAction *_testAct;
  QAction *_profilerAct;

  // Help
  QAction *_aboutAct;
};

#endif
