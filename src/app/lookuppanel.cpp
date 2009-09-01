/* This file is part of Wikt. -*- mode: c++; c-file-style: "wikt"; -*-
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
#include "lookuppanel.h"
#include "mainwindow.h"
#include <QLineEdit>
#include <QAction>
#include <QVBoxLayout>
#include <QToolBar>
#include <QToolButton>
#include <QMenu>

//===========================================================================
LookupPanel::LookupPanel() : QDockWidget(tr("Search"))
{
  _wordEdit = new QLineEdit(this);
  connect(_wordEdit, SIGNAL(returnPressed()), this, SLOT(editingFinished()));
  _toolBar = new QToolBar(this);
  _toolBar->setFloatable(false);
  _toolBar->setAllowedAreas(Qt::NoToolBarArea);
  _toolBar->setMovable(false);
  // remove excessive space around small buttons
  _toolBar->setStyleSheet("QToolButton{margin:0}");

  // Go Home button.
  _homeAct = new QAction(QIcon(":/images/go-home.svg"), tr("Title page"), this);
  _toolBar->addAction(_homeAct);
  connect(_homeAct, SIGNAL(triggered()), this, SLOT(goHome()));

  // Previous Entry button. Backspace added as an important
  // shortcut.
  _previousAct = new QAction(QIcon(":/images/go-previous.svg"), tr("Previous"), this);
  QList<QKeySequence> previousActShortcuts;
  previousActShortcuts.append(QKeySequence::Back);
  previousActShortcuts.append(Qt::Key_Backspace);
  _previousAct->setShortcuts(previousActShortcuts);
  connect(_previousAct, SIGNAL(triggered()), this, SLOT(goPrevious()));
  _toolBar->addAction(_previousAct);

  // Next Entry button.
  _nextAct = new QAction(QIcon(":/images/go-next.svg"), tr("Next"), this);
  _nextAct->setShortcut(QKeySequence::Forward);
  connect(_nextAct, SIGNAL(triggered()), this, SLOT(goNext()));
  _toolBar->addAction(_nextAct);

  // Update displayed entry history and register a slot catching its changes.
  historyChanged();
  connect(&_history, SIGNAL(changed()), this, SLOT(historyChanged()));

  // Vertical fixed layout without margins.
  QWidget *layoutWidget = new QWidget(this);
  QVBoxLayout *layout = new QVBoxLayout(layoutWidget);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);
  layout->setSizeConstraint(QLayout::SetMaximumSize);
  layout->addWidget(_wordEdit);
  layout->addWidget(_toolBar);
  layoutWidget->setMaximumHeight(_wordEdit->height() + _toolBar->height());
  layoutWidget->setLayout(layout);
  setWidget(layoutWidget);

  // Not movable, no title bar.
  setAllowedAreas(Qt::LeftDockWidgetArea);
  setFeatures(QDockWidget::NoDockWidgetFeatures);
  setContentsMargins(0, 4, 2, 4);
  setTitleBarWidget(new QWidget(this)); // no title bar
}

//===========================================================================
void LookupPanel::setFocus()
{
  QDockWidget::setFocus();
  _wordEdit->setFocus();
}

//===========================================================================
bool LookupPanel::hasFocus() const
{
  return _wordEdit->hasFocus();
}

//===========================================================================
void LookupPanel::setText(const QString &text)
{
  _wordEdit->setText(text);
}

//===========================================================================
void LookupPanel::editingFinished()
{
  QString text(_wordEdit->text().trimmed());
  if (text.isEmpty()) return;
  emit wordEntered(text);
}

//===========================================================================
void LookupPanel::historyChanged()
{
  _previousAct->setEnabled(_history.canGoBack());
  _nextAct->setEnabled(_history.canGoForward());
}

//===========================================================================
void LookupPanel::goPrevious()
{
  if (!_history.canGoBack()) return;
  _history.back();
  emit historyActivated(_history.current());
}

//===========================================================================
void LookupPanel::goNext()
{
  if (!_history.canGoForward()) return;
  _history.forward();
  emit historyActivated(_history.current());
}

//===========================================================================
void LookupPanel::goHome()
{
  emit homeActivated();
}
