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
#include "findpanel.h"
#include "mainwindow.h"
#include "webview.h"
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QApplication>
#include <QKeyEvent>
#include <QLabel>

FindPanel::FindPanel(QWidget *parent) : QDockWidget(tr("Find"), parent)
{
  _close = new QPushButton(QIcon(":/images/emblem-unreadable.svg"), "", this);
  _close->setFlat(true);
  _close->setIconSize(QSize(18, 18));
  connect(_close, SIGNAL(clicked(bool)), this, SLOT(hide()));

  QLabel *search = new QLabel(tr("Find:"), this);

  _textEdit = new QLineEdit(this);
  connect(_textEdit, SIGNAL(textChanged(const QString&)), this, SLOT(textChanged(const QString&)));
  connect(_textEdit, SIGNAL(returnPressed()), this, SLOT(nextClicked()));

  _previous = new QPushButton(QIcon(":/images/go-previous.svg"), tr("Previous"), this);
  _previous->setEnabled(false);
  connect(_previous, SIGNAL(clicked(bool)), this, SLOT(previousClicked()));

  _next = new QPushButton(QIcon(":/images/go-next.svg"), tr("Next"), this);
  _next->setEnabled(false);
  connect(_next, SIGNAL(clicked(bool)), this, SLOT(nextClicked()));

  _caseSensitive = new QCheckBox(tr("Case sensitive"), this);

  QWidget *layoutWidget = new QWidget(this);
  QHBoxLayout *layout = new QHBoxLayout(layoutWidget);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);
  layout->setSizeConstraint(QLayout::SetMaximumSize);
  layout->addWidget(_close);
  layout->addSpacing(4);
  layout->addWidget(search);
  layout->addSpacing(3);
  layout->addWidget(_textEdit);
  layout->addSpacing(3);
  layout->addWidget(_previous);
  layout->addWidget(_next);
  layout->addSpacing(10);
  layout->addWidget(_caseSensitive);
  layoutWidget->setLayout(layout);
  layoutWidget->setMaximumHeight(_textEdit->height());
  setWidget(layoutWidget);

  setFeatures(QDockWidget::NoDockWidgetFeatures);
  setContentsMargins(0, 4, 0, 4);
  setTitleBarWidget(new QWidget(this)); // no title bar
}

void FindPanel::setVisible(bool visible)
{
  QDockWidget::setVisible(visible);
  if (visible)
  {
    QDockWidget::setFocus();
    _textEdit->setFocus();
    _textEdit->selectAll();
  }
}

bool FindPanel::hasFocus() const
{
  return _textEdit->hasFocus() || QDockWidget::hasFocus();
}

void FindPanel::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Escape)
  {
    event->accept();
    hide();
  }
  QDockWidget::keyPressEvent(event);
}

void FindPanel::previousClicked()
{
  if (_textEdit->text() == "") return;

  QWebPage::FindFlags flags = QWebPage::FindBackward | QWebPage::FindWrapsAroundDocument;
  if (_caseSensitive->isChecked())
    flags |= QWebPage::FindCaseSensitively;

  bool found = MainWindow::instance()->webView()->findText(_textEdit->text(),
      flags);
  if (!found)
  {
    _textEdit->setStyleSheet("background-color:#ff6666");
    QApplication::beep();
  }
  else
    _textEdit->setStyleSheet("backgroud-color:white");
}

void FindPanel::nextClicked()
{
  if (_textEdit->text() == "") return;

  QWebPage::FindFlags flags = QWebPage::FindWrapsAroundDocument;
  if (_caseSensitive->isChecked())
    flags |= QWebPage::FindCaseSensitively;

  bool found = MainWindow::instance()->webView()->findText(_textEdit->text(),
      flags);
  if (!found)
  {
    _textEdit->setStyleSheet("background-color:#ff6666");
    QApplication::beep();
  }
  else
    _textEdit->setStyleSheet("backgroud-color:white");
}

void FindPanel::textChanged(const QString &text)
{
  _previous->setEnabled(text.length() != 0);
  _next->setEnabled(text.length() != 0);
  if (text.length() == 0) return;

  nextClicked();
}
