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
#include "htmlsourceview.h"
#include "htmlsyntaxhighlighter.h"
#include <QTextEdit>

//===========================================================================
HtmlSourceView::HtmlSourceView(const QString &contents)
  : QDockWidget(tr("HTML Source View"))
{
  setAllowedAreas(Qt::NoDockWidgetArea);
  setFeatures(QDockWidget::AllDockWidgetFeatures);

  QFont font;
  font.setFamily("Courier");
  font.setFixedPitch(true);
  font.setPointSize(10);

  _editor = new QTextEdit;
  _editor->setFont(font);
  //_highlighter = new HtmlSyntaxHighlighter(_editor->document());
  _editor->setPlainText(contents);
  setWidget(_editor);
}
