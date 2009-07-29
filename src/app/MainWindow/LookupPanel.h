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
#ifndef WIKT_LOOKUP_PANEL_H
#define WIKT_LOOKUP_PANEL_H

#include "DisplayedPageHistory.h"
#include <QDockWidget>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QMenu;
class QToolBar;
class QAction;
QT_END_NAMESPACE

class LookupPanel : public QDockWidget
{
  Q_OBJECT
public:
  /// Standard constructor.
  LookupPanel();
  /// Makes sure that the word edit is always focused.
  virtual void setFocus();
  bool hasFocus() const;
  
  /// History of displayed pages. Used by the Previous and
  /// Next buttons placed on the panel.
  DisplayedPageHistory &history() { return _history; }

  void setText(const QString &text);

signals:
  /// Emitted when the user enters some text to the line edit.
  void wordEntered(const QString &word);
  /// Previous or Next button.
  void historyActivated(const QUrl &url);
  /// Home button.
  void homeActivated();

private slots:
  void editingFinished();
  void historyChanged();
  void goPrevious();
  void goNext();
  void goHome();

private:
  /// A line where user write text for search.
  QLineEdit *_wordEdit;
  /// History of displayed pages, used by Previous and Next actions and
  /// buttons.
  DisplayedPageHistory _history;
  /// Display Title Page action.
  QAction *_homeAct;
  /// Display Previously Displayed Page action.
  QAction *_previousAct;
  /// Display Next Page action.
  QAction *_nextAct;
  /// Tool bar that displays buttons representing the actions.
  QToolBar *_toolBar;
};

#endif

