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
#include "WikiSourceView.h"
#include "../MainWindow/MainWindow.h"
#include <libwikt/Wiki/WikiSource.h>
#include <QTextEdit>
#include <QLineEdit>
#include <QVBoxLayout>

//===========================================================================
WikiSourceView::WikiSourceView()
{
  setAllowedAreas(Qt::NoDockWidgetArea);
  setFeatures(QDockWidget::AllDockWidgetFeatures);

  QFont font;
  font.setFamily("Courier");
  font.setFixedPitch(true);
  font.setPointSize(10);

  _editor = new QTextEdit(this);
  _editor->setFont(font);

  _wordEdit = new QLineEdit(this);
  connect(_wordEdit, SIGNAL(editingFinished()), this, SLOT(onEditingFinished()));

  QWidget *layoutWidget = new QWidget(this);
  QVBoxLayout *layout = new QVBoxLayout(layoutWidget);
  layout->addWidget(_wordEdit);
  layout->addWidget(_editor);
  layoutWidget->setLayout(layout);
  setWidget(layoutWidget);
}

//===========================================================================
void WikiSourceView::setWord(const QString &word)
{
  if (_wordEdit->text() != word)
    _wordEdit->setText(word);

  WikiSource *reader = MainWindow::instance()->wikiSource();
  if (!reader->exist(word))
  {
    _editor->setPlainText("");
    return;
  }

  _editor->setPlainText(reader->source(word));
}

//===========================================================================
void WikiSourceView::onEditingFinished()
{
  setWord(_wordEdit->text());
}

