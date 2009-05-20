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
#include "WikiProcessingView.h"
#include "../Wiki/Parser/ArticleParser.h"
#include "../Wiki/Tree/Article/ArticleNode.h"
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

//===========================================================================
WikiProcessingView::WikiProcessingView()
{
  setAllowedAreas(Qt::NoDockWidgetArea);
  setFeatures(QDockWidget::AllDockWidgetFeatures);

  QFont font;
  font.setFamily("Courier");
  font.setFixedPitch(true);
  font.setPointSize(10);

  _wikiSource = new QTextEdit();
  _wikiSource->setFont(font);
  _wikiSource->setUndoRedoEnabled(true);
  _wikiSource->setPlainText("Enter [[some]] text in ''wiki'' [[syntax]].");
  _result = new QTextEdit();
  _result->setFont(font);
  _result->setReadOnly(true);
  QHBoxLayout *editorLayout = new QHBoxLayout();
  editorLayout->addWidget(_wikiSource);
  editorLayout->addWidget(_result);
  QWidget *editorWidget = new QWidget();
  editorWidget->setLayout(editorLayout);

  _xmlButton = new QPushButton("XML", this);
  connect(_xmlButton, SIGNAL(clicked()), this, SLOT(onXmlButtonClicked()));
  QHBoxLayout *buttonLayout = new QHBoxLayout();
  buttonLayout->addWidget(_xmlButton);
  QWidget *buttonWidget = new QWidget();
  buttonWidget->setLayout(buttonLayout);

  QVBoxLayout *layout = new QVBoxLayout();
  layout->addWidget(buttonWidget);
  layout->addWidget(editorWidget);
  QWidget *layoutWidget = new QWidget();
  layoutWidget->setLayout(layout);
  setWidget(layoutWidget);
}

//===========================================================================
void WikiProcessingView::onXmlButtonClicked()
{
  Node *node = ArticleParser::parse("Word", _wikiSource->toPlainText());
  _result->setPlainText(node->toXml());
  delete node;
}

