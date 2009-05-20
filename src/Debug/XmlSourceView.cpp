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
#include "XmlSourceView.h"
#include "XmlSyntaxHighlighter.h"
#include "../Wiki/WikiSource.h"
#include "../Wiki/Tree/Article/ArticleNode.h"
#include "../MainWindow/MainWindow.h"
#include <QTextEdit>
#include <QLineEdit>
#include <QVBoxLayout>

//===========================================================================
XmlSourceView::XmlSourceView() : QDockWidget(tr("XML Source View"))
{
  setAllowedAreas(Qt::NoDockWidgetArea);
  setFeatures(QDockWidget::AllDockWidgetFeatures);

  QFont font;
  font.setFamily("Courier");
  font.setFixedPitch(true);
  font.setPointSize(10);

  _editor = new QTextEdit();
  _editor->setFont(font);
  _highlighter = new XmlSyntaxHighlighter(_editor->document());

  _wordEdit = new QLineEdit();
  connect(_wordEdit, SIGNAL(editingFinished()), this, SLOT(onEditingFinished()));

  QVBoxLayout *layout = new QVBoxLayout();
  layout->addWidget(_wordEdit);
  layout->addWidget(_editor);
  QWidget *layoutWidget = new QWidget;
  layoutWidget->setLayout(layout);
  setWidget(layoutWidget);
}

//===========================================================================
void XmlSourceView::setWord(const QString &word)
{
  if (_wordEdit->text() != word)
    _wordEdit->setText(word);

  WikiSource *reader = MainWindow::instance()->wikiSource();
  if (!reader->exist(word))
  {
    _editor->setPlainText("");
    return;
  }

  _editor->setPlainText(reader->tree(word)->toXml());
}

//===========================================================================
void XmlSourceView::onEditingFinished()
{
  setWord(_wordEdit->text());
}
